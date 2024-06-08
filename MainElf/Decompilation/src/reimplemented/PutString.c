#include "Context.h"
#include "FunctionList.h"

void PutString(RecompContext *ctx)
{
	printf("Running function 'PutString'\n");
	printf("\t%s\n", ctx->mem + ctx->a1);
}
