#ifndef PSX_PSYQ_H
#define PSX_PSYQ_H

/* The PsyQ SDK headers (@source: wiki:data/programs#psyq-sdk) */

/*
 * Include PsyQ headers for type definitions only (SVECTOR, RECT, etc.).
 * PsyQ function declarations in these headers are tolerated; the
 * config/symbols.toml rows provide the original-binary addresses at link time.
 * This header includes no game header except types.h.
 */
#include "types.h"

/* clang-format off */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <kernel.h>
#include <libcd.h>
#include <libetc.h>
#include <libsnd.h>
#include <libspu.h>
/* clang-format on */

struct EXEC;

/* Declarations the retail release provided that its 3.7 headers omit. Every
 * name here has a retail address and a reader; nothing else belongs here. */

/* retail 0x8017B2B4 reads no argument and returns a zero-extended byte; 3.7
 * libgpu.h getTPage and setDrawTPage call it with none. */
/* func_8017B2B4 (slus), func_801D40F8 (logo) */
extern s32  GetGraphType(void);
/* retail 0x8017B438 reads a0 as a log string and a1 as RECT; 3.7 SYS.OBJ
 * exports it and libgpu.h does not declare it. */
/* func_8017B438 (slus), func_801D427C (logo) */
extern void checkRECT(char* log, RECT* rect);

/* Game-only: SDK internals the game calls; no staged header declares them. */
s32         _SpuInit(s32); /* 0x80168F20 */
extern void SeAutoPan(s16 voice, s16 pan_from, s16 pan_to, s16 delta);
extern void SetAutoPan(s16 voice);
extern void SeAutoVol(s16 voice, s16 vol_from, s16 vol_to, s16 delta);
extern void SetAutoVol(s16 voice);
void        _SsVmSetSeqVol(s16 seq, u16 vol_l, u16 vol_r, s32 mode);       /* 0x801729D0 */
extern s16  SsVabOpenHeadWithMode(s32 arg0, s16 arg1, s32 arg2, s32 arg3); /* 0x80173CB0 */
void        __main(void);
s32         SetPatchPad(void);
extern s32  RemovePatchPad(void);
s32         _Pad1(void);
s32         _IsVSync(void);
s32         InitPAD2(s32, s32, s32, s32);  /* 0x801D7CE4 */
void        StartPAD2(void);               /* 0x801D7CF4 */
s32         PAD_init2(s32, s32, s32, s32); /* 0x801D7D14 */
s32         SysEnqIntRP(s32, s32*);        /* 0x801D7D24 */
s32         SysDeqIntRP(s32, s32*);        /* 0x801D7D34 */
s32         _patch_pad(void);              /* 0x801D7D6C */

/* RotTrans into a matrix translation: PsyQ takes a VECTOR, MATRIX.t is long t[3]. */
#define RotTransMatrix(pos, matrix, flag) RotTrans(pos, (VECTOR*)(matrix).t, flag)

/* The packed x,y pair of vertex n of a primitive, as RotTransPers writes it. */
#define POLY_XY(prim, n)                  ((DVECTOR*)&(prim)->x##n)

#endif
