#include "Context.h"
#include "FunctionList.h"

undefined LoaderSysFSeek64(RecompContext* ctx){
printf("Running function 'LoaderSysFSeek64'\n");
	ADDIU(ctx, ctx->sp, ctx->sp, -16);
	SD(ctx, ctx->ra, 0, ctx->sp);
	LD(ctx, ctx->ra, 0, ctx->sp);
	ADDIU(ctx, ctx->sp, ctx->sp, 16);
	sceLseek64(ctx);
}
