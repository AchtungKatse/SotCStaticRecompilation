#include "Context.h"
#include "FunctionList.h"

int LoaderSysFSeek(RecompContext* ctx){
printf("Running function 'LoaderSysFSeek'\n");
	ADDIU(ctx, ctx->sp, ctx->sp, -16);
	SD(ctx, ctx->ra, 0, ctx->sp);
	LD(ctx, ctx->ra, 0, ctx->sp);
	ADDIU(ctx, ctx->sp, ctx->sp, 16);
	sceLseek(ctx);
}
