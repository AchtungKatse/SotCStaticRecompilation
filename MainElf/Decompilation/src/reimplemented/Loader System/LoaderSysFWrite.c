#include "Context.h"
#include "FunctionList.h"

undefined LoaderSysFWrite(RecompContext* ctx){
printf("Running function 'LoaderSysFWrite'\n");
	ADDIU(ctx, ctx->sp, ctx->sp, -16);
	SD(ctx, ctx->ra, 0, ctx->sp);
	LD(ctx, ctx->ra, 0, ctx->sp);
	ADDIU(ctx, ctx->sp, ctx->sp, 16);
	sceWrite(ctx);
}
