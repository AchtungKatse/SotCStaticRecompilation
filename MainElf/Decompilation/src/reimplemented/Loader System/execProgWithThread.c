#include "Context.h"
#include "FunctionList.h"
#include "reimplemented/Threads/ProgramData.h"
#include <stdio.h>
#include <string.h>

char ModuleName[0x40];

void ExecProgWithThreadBuffer(void *parameters)
{
	RecompContext *context = parameters;
	printf("Module name: %s\n", ModuleName);
	printf("Module name ptr: %p\n", ModuleName);
	printf("Exec Prog memory: %p\n", context->mem);
	_execProgWithThread(context, ModuleName);
}

void execProgWithThread(RecompContext *ctx, char *path, int threadID)
{
	ThreadParam baseThreadParm;

	printf("execProgWithThread: %p\n", path);

	ctx->a0 = path;
	GetProgramNameAndOffset(ctx, path);
	ProgramData *progData = ctx->mem + ctx->v0;
	if (progData != 0)
	{
		memset(&baseThreadParm, 0, 0x30);
		baseThreadParm.function = ExecProgWithThreadBuffer;
		baseThreadParm.stack = (void *)(((ctx->sp + 0xf) / 0x10) * 0x10);
		// iGpffff8094 = (int)baseThreadParm.stack + progData->offset;
		baseThreadParm.gpRegister = ctx->gp;
		baseThreadParm.initialPriority = threadID;
		baseThreadParm.stackSize = progData->offset;

		memset(ModuleName, 0, sizeof(ModuleName));
		strcpy(ModuleName, progData->path);

		RecompContext *threadCtx = malloc(sizeof(RecompContext));
		memset(threadCtx, 0, sizeof(RecompContext));
		
		threadCtx->sp = MB * 38;
		threadCtx->gp = MB * 40;

		threadCtx->mem = ctx->mem;
		printf("Thread context memory: %p\n", threadCtx->mem);
		printf("Program data name: %s (0x%x)\n", ctx->mem + ctx->v0, ctx->v0);

		printf("Module name: %p\n", ModuleName);

		baseThreadParm.stack = threadCtx;
		CreateThread(&baseThreadParm);

		ctx->a0 = threadID;
		LoaderSysEntryExternalThreadList(ctx);
		return baseThreadParm.stack;
	}
	return 0;
}
