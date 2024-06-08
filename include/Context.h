#pragma once
#ifndef CONTEXT_H
// #include <stdio.h>
#define CONTEXT_H

#define KB 1024
#define MB KB *KB
#define MemorySize MB * 128

typedef char byte;
typedef unsigned char ubyte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef unsigned char undefined1;
typedef unsigned int undefined;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long undefined8;

typedef long double FPR;
typedef long long GPR;
typedef unsigned long long uGPR;

typedef union
{
    FPR fpr;
    GPR gpr;
} GPRFPR;

typedef int bool;
#define true 1
#define false 0
typedef struct
{
    GPR at;
    GPR zero;
    GPR v0;
    GPR v1;
    GPR a0;
    GPR a1;
    GPR a2;
    GPR a3;
    GPR t0;
    GPR t1;
    GPR t2;
    GPR t3;
    GPR t4;
    GPR t5;
    GPR t6;
    GPR t7;
    GPR s0;
    GPR s1;
    GPR s2;
    GPR s3;
    GPR s4;
    GPR s5;
    GPR s6;
    GPR s7;
    GPR t8;
    GPR t9;
    GPR k0;
    GPR k1;
    GPR gp;
    GPR sp;
    GPR fp;
    GPR ra;

    FPR f0;
    FPR f1;
    FPR f2;
    FPR f3;
    FPR f4;
    FPR f5;
    FPR f6;
    FPR f7;
    FPR f8;
    FPR f9;
    FPR f10;
    FPR f11;
    FPR f12;
    FPR f13;
    FPR f14;
    FPR f15;
    FPR f16;
    FPR f17;
    FPR f18;
    FPR f19;
    FPR f20;
    FPR f21;
    FPR f22;
    FPR f23;
    FPR f24;
    FPR f25;
    FPR f26;
    FPR f27;
    FPR f28;
    FPR f29;
    FPR f30;
    FPR f31;

    int pc;
    GPR hi;
    GPR lo;
    GPR hi1;
    GPR lo1;
    GPR sa;

    void *mem;

    bool InterruptsEnabled;
} RecompContext;

// ===================================
// CPU Instructions
// ===================================

#define ADD(ctx, rd, rs, rt) rd = (rs + rt);
#define ADDU(ctx, rd, rs, rt) rd = (uint)rs + (uint)rt;
#define ADDI(ctx, rs, rt, offset) rs = (rt + offset);
#define ADDIU(ctx, a, b, value) a = b + value;

#define AND(ctx, rd, rs, rt) rd = (int)rs & (int)rt;
#define ANDI(ctx, rd, rs, value) rd = (int)rs & (short)value;

#define BEQ(ctx, a, b, branch) \
    if (a == b)                \
        goto branch;
#define BEQL(ctx, a, b, branch) \
    if (a == b)                 \
        goto branch;
#define BGEZ(ctx, a, branch) \
    if (a >= 0)              \
        goto branch;
#define BGEZAL(ctx, a, branch) \
    if (a >= 0)                \
        ctx->ra = ctx->pc + 4; \
    goto branch;

#define BGEZALL(ctx, a, branch) \
    if (a >= 0)                 \
    {                           \
        ctx->ra = ctx->pc + 4;  \
        goto branch;            \
    }
#define BGEZL(ctx, a, branch) BGEZ(ctx, a, branch);

#define BGTZ(ctx, a, branch) \
    if (a > 0)               \
        goto branch;
#define BGTZL(ctx, a, branch) BGTZ(ctx, a, branch);

#define BLEZ(ctx, a, branch) \
    if (a <= 0)              \
        goto branch;
#define BLEZL(ctx, a, branch) BLEZ(ctx, a, branch)

#define BLTZ(ctx, a, branch) \
    if (a < 0)               \
        goto branch;
#define BLZAL(ctx, a, branch)  \
    if (a < 0)                 \
    {                          \
        ctx->ra = ctx->pc + 4; \
        goto branch;           \
    }
#define BLZALL(ctx, a, branch) BLZAL(ctx, a, branch)
#define BLTZ(ctx, a, branch) \
    if (a < 0)               \
        goto branch;

#define BLTZL(ctx, a, branch) BLTZ(ctx, a, branch)
#define BNE(ctx, a, b, branch) \
    if (a != b)                \
        goto branch;
#define BNEL(ctx, a, b, branch) \
    if (a != b)                 \
        goto branch;

#define BREAK ;
#define SYNC ;
#define SYNCL ;

#define DADD(ctx, out, a, b) out = (long)a + (long)b;
#define DADDI(ctx, out, a, imm) out = (long)a + (short)imm;
#define DADDU(ctx, out, a, b) out = (ulong)a + (ulong)b;
#define DADDIU(ctx, out, a, imm) out = (ulong)a + (ulong)imm;

#define DIV(ctx, a, b)         \
    ctx->hi = (int)a / (int)b; \
    ctx->lo = (int)a % (int)b;
#define DIVU(ctx, a, b)          \
    ctx->hi = (uint)a / (uint)b; \
    ctx->lo = (uint)a % (uint)b;

#define DSLL(ctx, rd, rt, sa) rd = (long)rt << (long)sa;
#define DSLL32(ctx, rd, rt, sa) rd = (long)rt << (32 + (long)sa);
#define DSLLV(ctx, rd, rt, rs) rd = (long)rt << (long)rs;
#define DSRA(ctx, rd, rt, sa) rd = (long)rt >> (long)sa;
#define DSRA32(ctx, rd, rt, sa) rd = (long)rt >> ((long)sa + 32);
#define DSRAV(ctx, rd, rt, rs) rd = (long)rt >> (long)rs;
#define DSRL(ctx, rd, rt, sa) rd = (long)rt >> (long)sa;
#define DSRL32(ctx, rd, rt, sa) rd = (long)rt >> ((long)sa + 32);
#define DSRLV(ctx, rd, rt, rs) rd = (long)rt >> (long)rs;

#define DSUB(ctx, rd, rs, rt) rd = (long)rs - (long)rt;
#define DSUBU(ctx, rd, rs, rt) rd = (ulong)rs - (ulong)rt;

#define LB(ctx, rt, offset, base)                         \
    if (offset + base >= 0 && offset + base < MemorySize) \
        rt = *(byte *)(ctx->mem + base + (short)offset);  \
    else                                                  \
        rt = 0;
#define LBU(ctx, rt, offset, base)                        \
    if (offset + base >= 0 && offset + base < MemorySize) \
        rt = *(ubyte *)(ctx->mem + base + (short)offset); \
    else                                                  \
        rt = 0;

#define LD(ctx, rt, offset, base)                         \
    if (offset + base >= 0 && offset + base < MemorySize) \
        rt = *(long *)(ctx->mem + base + (short)offset);  \
    else                                                  \
        rt = 0;
// Not the most accurate but it should work
#define LDL(ctx, rt, offset, base)                        \
    if (offset + base >= 0 && offset + base < MemorySize) \
        rt = *(long *)(ctx->mem + base + (short)offset);  \
    else                                                  \
        rt = 0;
// Not the most accurate but it should work
#define LDR(ctx, rt, offset, base)                        \
    if (offset + base >= 0 && offset + base < MemorySize) \
        rt = *(long *)(ctx->mem + base + (short)offset);  \
    else                                                  \
        rt = 0;

#define LH(ctx, rt, offset, base)                         \
    if (offset + base >= 0 && offset + base < MemorySize) \
        rt = *(short *)(ctx->mem + base + (short)offset); \
    else                                                  \
        rt = 0;
#define LHU(ctx, rt, offset, base)                         \
    if (offset + base >= 0 && offset + base < MemorySize)  \
        rt = *(ushort *)(ctx->mem + base + (short)offset); \
    else                                                   \
        rt = 0;

#define LUI(ctx, dst, value) dst = (int)value << 0x10;

#define LW(ctx, rt, offset, base)                                                   \
    if (offset + base >= 0 && offset + base < MemorySize)                           \
        rt = *(int *)(ctx->mem + base + (short)offset);                             \
    else                                                                            \
    {                                                                               \
        rt = 0;                                                                     \
        printf("Failed to load register with offset %d and base %x\n", offset, base); \
    }
#define LWL(ctx, rt, offset, base)                        \
    if (offset + base >= 0 && offset + base < MemorySize) \
        rt = *(int *)(ctx->mem + base + (short)offset);   \
    \ 
        else rt = 0;
#define LWR(ctx, rt, offset, base)                        \
    if (offset + base >= 0 && offset + base < MemorySize) \
        rt = *(int *)(ctx->mem + base + (short)offset);   \
    \ 
        else rt = 0;
#define LWU(ctx, rt, offset, base)                        \
    if (offset + base >= 0 && offset + base < MemorySize) \
        rt = *(uint *)(ctx->mem + base + (short)offset);  \
    else                                                  \
        rt = 0;

#define MFHI(ctx, rd) rd = ctx->hi;
#define MFLO(ctx, rd) rd = ctx->lo;

#define MOVN(ctx, rd, rs, rt) \
    if (rt != 0)              \
        rd = rs;
#define MOVZ(ctx, rd, rs, rt) \
    if (rt == 0)              \
        rd = rs;
#define MOVS(ctx, fd, fs) fs = fs;

#define MTHI(ctx, rs) ctx->hi = rs;
#define MTLO(ctx, rs) ctx->lo = rs;

#define MULT(ctx, rs, rt)               \
    {                                   \
        GPR result = rs * rt;           \
        ctx->hi = result >> 32;         \
        ctx->lo = result & 0xffffffffu; \
    }
#define MULTU(ctx, rs, rt)                \
    {                                     \
        GPR result = (uGPR)rs * (uGPR)rt; \
        ctx->hi = result >> 32;           \
        ctx->lo = result & 0xffffffffu;   \
    }

#define NOR(ctx, rd, rs, rt) rd = ~(rs | rt);
#define OR(ctx, rd, rs, rt) rd = rs | rt;
#define ORI(ctx, rt, rs, immediate) rt = (int)rs | (ushort)immediate;

#define SB(ctx, rt, offset, base)                         \
    if (offset + base >= 0 && offset + base < MemorySize) \
        *(byte *)(ctx->mem + (short)offset + base) = (byte)rt;
#define SD(ctx, rt, offset, base)                         \
    if (offset + base >= 0 && offset + base < MemorySize) \
        *(long *)(ctx->mem + (short)offset + base) = (long)rt;
#define SDL(ctx, rt, offset, base)                        \
    if (offset + base >= 0 && offset + base < MemorySize) \
        *(long *)(ctx->mem + (short)offset + base) = (long)rt; // Inaccurate implementation
#define SDR(ctx, rt, offset, base) SDL(ctx, rt, offset, base)
#define SH(ctx, rt, offset, base)                         \
    if (offset + base >= 0 && offset + base < MemorySize) \
        *(short *)(ctx->mem + (short)offset + base) = (short)rt;

#define SW(ctx, rt, offset, base)                         \
    if (offset + base >= 0 && offset + base < MemorySize) \
        *(int *)(ctx->mem + base + (short)offset) = (int)rt;
#define SWL(ctx, rt, offset, base)                        \
    if (offset + base >= 0 && offset + base < MemorySize) \
        *(int *)(ctx->mem + base + (short)offset) = (int)rt;
#define SWR(ctx, rt, offset, base)                        \
    if (offset + base >= 0 && offset + base < MemorySize) \
        *(int *)(ctx->mem + base + (short)offset) = (int)rt;

#define SLL(ctx, rd, rt, sa) rd = (int)rt << sa;
#define SLLV(ctx, rd, rt, rs) rd = (int)rt << rs;

#define SLT(ctx, rd, rs, rt) rd = rs < rt;
#define SLTI(ctx, rd, rs, imm) rd = rs < (short)imm;
#define SLTIU(ctx, rd, rs, imm) rd = rs < (short)imm;
#define SLTU(ctx, rd, rs, rt) rd = (uGPR)rs < (uGPR)rt;

// Shifting may break things
#define SRA(ctx, rd, rt, sa) rd = (int)rt >> sa;
#define SRL(ctx, rd, rt, rs) rd = (int)rt >> rs;
#define SRLV(ctx, rd, rt, rs) rd = (int)rt >> rs;

#define SUB(ctx, rd, rs, rt) rd = (int)rs - (int)rt;
#define SUBU(ctx, rd, rs, rt) rd = (uGPR)rs - (uGPR)rt;

#define EI(ctx) ctx->InterruptsEnabled = true;
#define DI(ctx) ctx->InterruptsEnabled = false;

#define SWC1(ctx, ft, offset, base) *(float *)(ctx->mem + base + (short)offset) = ft;
// #define DIV()

#define XOR(ctx, rd, rs, rt) rd = (int)rs ^ (int)rt;
#define XORI(ctx, rd, rs, imm) rd = (int)rs ^ (ushort)imm;

#define SQ(ctx, rt, offset, base)                       \
    {                                                   \
        *(GPR *)(ctx->mem + base + (short)offset) = rt; \
    }
#define LQ(ctx, rt, offset, base)                       \
    {                                                   \
        rt = *(GPR *)(ctx->mem + base + (short)offset); \
    }

inline void JALR(RecompContext *ctx, void (*jump)(void))
{
    printf("Jumping to function %p\n", jump);
    jump();
}

inline void JR(RecompContext *ctx, void *jump(void))
{
    jump();
}

#define NOP() ;
#define PREF(ctx, hint, offset, base) ;
#define SYSCALL(a) ;
#define CACHE(...)
#define norelocation(...)

// ===================================
// EE Specific Instructions
// ===================================

// inline void MADD1(RecompContext *ctx, GPR rd, GPR rs, GPR rt) {rd = (int)rs * (int)rt; ctx->lo += rd; }
// inline void MADDU(RecompContext* ctx, GPR rd, GPR rs, GPR rt) {}

#define MFHI1(ctx, rd) rd = ctx->hi1;
#define MFLO1(ctx, rd) rd = ctx->lo1;

#define MFSA(ctx, rd) rd = ctx->sa;

#define MTHI1(ctx, rs) ctx->hi1 = rs;
#define MTLO1(ctx, rs) ctx->lo1 = rs;

#define MTSA(ctx, rs) ctx->sa = rs;
#define MTSAB(ctx, rs, imm) ctx->sa = (rs ^ (short)imm) * 8;

#define MTSAH(ctx, rs, imm) ctx->sa = (rs ^ (short)imm) * 16;

#define DIV1(ctx, rs, rt) \
    ctx->lo1 = rs / rt;   \
    ctx->hi1 = rs % rt;

// ===================================
// COP1 Instructions
// ===================================

#define ABSS(ctx, fd, fs) fs = (float)(fs < 0 ? -fs : fs);
#define ADDS(ctx, fd, fs, ft) fd = (float)fs + (float)ft;
// inline void ADDAS(RecompContext* ctx, FPR fd, FPR fs, FPR ft) {fd = fs + ft;}

#define MULS(ctx, fd, fs, ft) fd = (float)fs * (float)ft;
#define CVTSW(ctx, fd, fs)   \
    {                        \
        GPRFPR reg;          \
        reg.gpr = (GPR)fs;   \
        fd = (float)reg.fpr; \
    }

#define CVTWS(ctx, fd, fs)   \
    {                        \
        GPRFPR reg;          \
        reg.gpr = (int)fs;   \
        fd = (float)reg.fpr; \
    }

#define MTC1(ctx, rt, fs) \
    {                     \
        GPRFPR reg;       \
        reg.gpr = rt;     \
        fs = reg.fpr;     \
    }

#define MFC0(ctx, rt, rd) rt = rd;

#define MULT1(ctx, rd, rs, rt) rd = (int)rs * (int)rt;
#define SRAV(ctx, rd, rt, rs) rd = rt >> rs;
#define MTC0(ctx, rt, rd) rd = rt;

#define LWC1(ctx, ft, offset, base) ft = *(float *)(offset + base);
#define CFC2(ctx, rt, fs) \
    {                     \
        GPRFPR reg;       \
        reg.fpr = fs;     \
        rt = reg.gpr;     \
    }

#define POR(ctx, rd, rs, rt) rd = rs | rt;
#define CTC2(ctx, rt, fs) \
    {                     \
        GPRFPR reg;       \
        reg.gpr = rt;     \
        fs = reg.fpr;     \
    }

#define DIVS(ctx, fd, fs, ft) fd = fs / ft;
#define MULTU1(ctx, rs, rt)      \
    ctx->lo = (int)rs * (int)rt; \
    ctx->hi = ((long)rs * (long)rt) >> 0x20;
#define MULTU1(ctx, rs, rt, rd) rd = rs * rt;
#define ERET(ctx)

#endif