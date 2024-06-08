#include <stdio.h>
#include "Context.h"

typedef struct
{
	int length;
	int memoryLocation;
	char name[32];
} SectionMetaData;

void *LoadFile(const char *path)
{
	FILE *file = fopen(path, "r");

	if (file == NULL)
	{
		printf("File at path %s is null\n", path);
		return NULL;
	}

	// Get the meta file size
	fseek(file, 0L, SEEK_END);
	long length = ftell(file);
	rewind(file);

	// Load into memory
	char *data = malloc(length);
	if (data == NULL)
	{
		printf("Failed to malloc data");
		return NULL;
	}
	int result = fread(data, 1, length, file);

	fclose(file);
	return data;
}

void LoadSections(RecompContext *ctx)
{
	const char *SectionPath = "SectionData/MainElf/";
	const char *SectionMetaPath = "SectionData/MainElf/SectionMeta.bin";

	FILE *metaFile = fopen(SectionMetaPath, "r");

	if (metaFile == NULL)
	{
		printf("Failed to open section meta file at path \"$s\"\n", SectionMetaPath);
		return;
	}

	// Get the meta file size
	fseek(metaFile, 0L, SEEK_END);
	long length = ftell(metaFile);
	rewind(metaFile);

	// Get the number of sections
	int numSections = length / sizeof(SectionMetaData);

	// Create a new section data array from the file
	SectionMetaData *sections = malloc(sizeof(SectionMetaData) * numSections);
	fread(sections, sizeof(SectionMetaData) * numSections, numSections, metaFile);
	fclose(metaFile);

	// Load that many sections
	char filePath[0x200];
	for (size_t i = 0; i < numSections; i++)
	{
		if (sections[i].length == 0 && sections[i].memoryLocation == 0)
			continue;

		strcpy(filePath, SectionPath);
		strcat(filePath, sections[i].name);


		printf("Loading file %s.\n", filePath);
		void *fileData = LoadFile(filePath);

		if (fileData == NULL)
		{
			printf("Failed to load file %s.\n", filePath);
			continue;;
		}

		// // Load file into ctx mem
		memcpy(ctx->mem + sections[i].memoryLocation, fileData, sections[i].length);
		memset(filePath, 0, sizeof(filePath));
		free(fileData);
	}

	// Cleanup memory
	free(sections);
}

RecompContext oldCtx;

void PrintRegisters(RecompContext *ctx)
{
	memcpy(&oldCtx, ctx, sizeof(RecompContext));
	memset(&oldCtx, 0xFF, sizeof(RecompContext));
	printf("\nCTX Registers:\n");
	if (ctx->at != oldCtx.at)
		printf("at: %x\n", ctx->at);
	if (ctx->zero != oldCtx.zero)
		printf("zero: %x\n", ctx->zero);
	if (ctx->v0 != oldCtx.v0)
		printf("v0: %x\n", ctx->v0);
	if (ctx->v1 != oldCtx.v1)
		printf("v1: %x\n", ctx->v1);
	if (ctx->a0 != oldCtx.a0)
		printf("a0: %x\n", ctx->a0);
	if (ctx->a1 != oldCtx.a1)
		printf("a1: %x\n", ctx->a1);
	if (ctx->a2 != oldCtx.a2)
		printf("a2: %x\n", ctx->a2);
	if (ctx->a3 != oldCtx.a3)
		printf("a3: %x\n", ctx->a3);
	if (ctx->t0 != oldCtx.t0)
		printf("t0: %x\n", ctx->t0);
	if (ctx->t1 != oldCtx.t1)
		printf("t1: %x\n", ctx->t1);
	if (ctx->t2 != oldCtx.t2)
		printf("t2: %x\n", ctx->t2);
	if (ctx->t3 != oldCtx.t3)
		printf("t3: %x\n", ctx->t3);
	if (ctx->t4 != oldCtx.t4)
		printf("t4: %x\n", ctx->t4);
	if (ctx->t5 != oldCtx.t5)
		printf("t5: %x\n", ctx->t5);
	if (ctx->t6 != oldCtx.t6)
		printf("t6: %x\n", ctx->t6);
	if (ctx->t7 != oldCtx.t7)
		printf("t7: %x\n", ctx->t7);
	if (ctx->s0 != oldCtx.s0)
		printf("s0: %x\n", ctx->s0);
	if (ctx->s1 != oldCtx.s1)
		printf("s1: %x\n", ctx->s1);
	if (ctx->s2 != oldCtx.s2)
		printf("s2: %x\n", ctx->s2);
	if (ctx->s3 != oldCtx.s3)
		printf("s3: %x\n", ctx->s3);
	if (ctx->s4 != oldCtx.s4)
		printf("s4: %x\n", ctx->s4);
	if (ctx->s5 != oldCtx.s5)
		printf("s5: %x\n", ctx->s5);
	if (ctx->s6 != oldCtx.s6)
		printf("s6: %x\n", ctx->s6);
	if (ctx->s7 != oldCtx.s7)
		printf("s7: %x\n", ctx->s7);
	if (ctx->t8 != oldCtx.t8)
		printf("t8: %x\n", ctx->t8);
	if (ctx->t9 != oldCtx.t9)
		printf("t9: %x\n", ctx->t9);
	if (ctx->k0 != oldCtx.k0)
		printf("k0: %x\n", ctx->k0);
	if (ctx->k1 != oldCtx.k1)
		printf("k1: %x\n", ctx->k1);
	if (ctx->gp != oldCtx.gp)
		printf("gp: %x\n", ctx->gp);
	if (ctx->sp != oldCtx.sp)
		printf("sp: %x\n", ctx->sp);
	if (ctx->fp != oldCtx.fp)
		printf("fp: %x\n", ctx->fp);
	if (ctx->ra != oldCtx.ra)
		printf("ra: %x", ctx->ra);
	printf("\n");

	memcpy(&oldCtx, ctx, sizeof(RecompContext));
}

int main(int argc, char **argv)
{
	RecompContext *ctx = malloc(sizeof(RecompContext));
	memset(ctx, 0, sizeof(RecompContext));
	// const long MemorySize = 0x20000ul << 0x10ul; 
	printf("Allocated memory: 0x%x\n", MemorySize);
	ctx->mem = malloc(MemorySize);
	ctx->gp = MB * 64;
	ctx->sp = MB * 32;

	LoadSections(ctx);

	PrintRegisters(ctx);
	ADDIU(ctx, ctx->sp, ctx->sp, -48);
	SD(ctx, ctx->s1, 8, ctx->sp);
	DADDU(ctx, ctx->s1, ctx->zero, ctx->zero);
	SD(ctx, ctx->s2, 16, ctx->sp);
	DADDU(ctx, ctx->s2, ctx->a0, ctx->zero);
	SD(ctx, ctx->s4, 32, ctx->sp);
	SD(ctx, ctx->s0, 0, ctx->sp);
	SD(ctx, ctx->s3, 24, ctx->sp);
	SD(ctx, ctx->ra, 40, ctx->sp);
	DADDU(ctx, ctx->s4, ctx->a1, ctx->zero);
	LUI(ctx, ctx->a0, 19);
	DADDU(ctx, ctx->a1, ctx->s2, ctx->zero);
	ADDIU(ctx, ctx->a0, ctx->a0, 28040);
	BLEZ(ctx, ctx->s2, Branch_0x29);
	DADDU(ctx, ctx->s0, ctx->s4, ctx->zero);
	LUI(ctx, ctx->s3, 19);
	LW(ctx, ctx->a2, 0, ctx->s0);

Branch_0x21:
	ADDIU(ctx, ctx->s0, ctx->s0, 4);
	DADDU(ctx, ctx->a1, ctx->s1, ctx->zero);
	ADDIU(ctx, ctx->s1, ctx->s1, 1);
	printf("ld: argc %d: %s", ctx->s1, ctx->a2);
	ADDIU(ctx, ctx->a0, ctx->s3, 28064);
	SLT(ctx, ctx->v1, ctx->s1, ctx->s2);
	BNEL(ctx, ctx->v1, ctx->zero, Branch_0x21);
	LW(ctx, ctx->a2, 0, ctx->s0);
Branch_0x29:
	PrintRegisters(ctx);
	BEQ(ctx, ctx->s2, ctx->zero, Branch_0x39);
	LUI(ctx, ctx->s0, 20);
	LW(ctx, ctx->a1, 0, ctx->s4);
	ADDIU(ctx, ctx->s0, ctx->s0, -12400);
	ADDIU(ctx, ctx->a2, ctx->zero, 16);
	strncpy(*(char**)(ctx->a0), *(char**)(ctx->a1), *(int*)(ctx->a2));
	DADDU(ctx, ctx->a0, ctx->s0, ctx->zero);
	BEQ(ctx, ctx->zero, ctx->zero, Branch_0x41);
	SB(ctx, ctx->zero, 15, ctx->s0);
Branch_0x39:
	LUI(ctx, ctx->v0, 20);
	SB(ctx, ctx->zero, -12400, ctx->v0);
Branch_0x41:
	GetThreadId(ctx);
	InitDisp(ctx);
	SW(ctx, ctx->v0, -31980, ctx->gp);
	LUI(ctx, ctx->a1, 2047);
	LUI(ctx, ctx->a0, 512);
	ctx->v0 = initmemprintf(ctx);
	ORI(ctx, ctx->a1, ctx->a1, -256);
	// WarmUpCdDrive(ctx);
	LUI(ctx, ctx->v0, 23);
	ADDIU(ctx, ctx->v0, ctx->v0, -23656);
	LUI(ctx, ctx->v1, 4);
	ADDIU(ctx, ctx->v1, ctx->v1, 0);
	ADDU(ctx, ctx->v0, ctx->v0, ctx->v1);
	ADDIU(ctx, ctx->a0, ctx->zero, -16);
	ADDIU(ctx, ctx->v0, ctx->v0, 15);
	AND(ctx, ctx->v0, ctx->v0, ctx->a0);
	InitException(ctx);
	SW(ctx, ctx->v0, -32096, ctx->gp);
	LoaderSysInitExternalIntcHandlerList(ctx);
	LoaderSysInitExternalThreadList(ctx);
	LoaderSysInitExternalSemaList(ctx);
	ctx->v0 = LoaderSysInitExternalIopMemoryList(ctx);
	LW(ctx, ctx->a0, -31980, ctx->gp);
	ChangeThreadPriority(ctx);
	ADDIU(ctx, ctx->a1, ctx->zero, 1);
	LUI(ctx, ctx->a1, 19);
	ADDIU(ctx, ctx->a1, ctx->a1, 28088);
	ADDIU(ctx, ctx->a0, ctx->zero, -256);
	PutStringS(ctx->a0, ctx->mem + ctx->a1);
	printf("Starting loader loop");
	SW(ctx, ctx->sp, -31984, ctx->gp);
	ctx->v0 = loaderLoop(ctx);
	LD(ctx, ctx->s0, 0, ctx->sp);
	DADDU(ctx, ctx->v0, ctx->zero, ctx->zero);
	LD(ctx, ctx->s1, 8, ctx->sp);
	LD(ctx, ctx->s2, 16, ctx->sp);
	LD(ctx, ctx->s3, 24, ctx->sp);
	LD(ctx, ctx->s4, 32, ctx->sp);
	LD(ctx, ctx->ra, 40, ctx->sp);
	ADDIU(ctx, ctx->sp, ctx->sp, 48);
	return;
}
