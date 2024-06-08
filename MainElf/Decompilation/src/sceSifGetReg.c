#include "Context.h"

undefined sceSifGetReg(RecompContext* ctx){
printf("Running function 'sceSifGetReg'\n");
	ctx->v1 = 0x20000;
	return;
	ADDIU(ctx, ctx->v1, 0, 122);
	SYSCALL(0);
}
