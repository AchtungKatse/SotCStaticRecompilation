#include "Context.h"

void memset_ps2(RecompContext* ctx, int dst, int value, int len)
{
    memset(ctx->mem + dst, value, len);
}