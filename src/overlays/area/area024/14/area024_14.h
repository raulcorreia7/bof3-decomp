#ifndef OVERLAY_WORLD00_AREA024_14_H
#define OVERLAY_WORLD00_AREA024_14_H

/* The area024 world overlay's local declarations: its sprite, spin and scratch
 * work records, handler table and prototypes. Only this image includes the
 * file. */

#include "common/vector.h"
#include "overlays/area/shared/AreaSprite.h"
#include "overlays/area/worlds/world00.h"
#include "area/effects.h"

#define WORLD00_AREA024_WORK_BASE      MEM_PTR(volatile AreaSprite, AREA_WORK)
#define WORLD00_AREA024_SPIN_WORK_BASE MEM_PTR(u8, 0x800E5000u)
#define WORLD00_AREA024_STATE_BASE     MEM_PTR(volatile s16, 0x800E4940u)
#define WORLD00_AREA024_STATE_OFFSET   MEM_PTR(volatile s16, 0x800E4944u)
#define WORLD00_AREA024_VERTEX_DST     MEM_PTR(volatile u8, 0x800E4BC8u)
#define WORLD00_AREA024_PTR_7AA8       MEM(volatile u8*, 0x80147AA8u)
#define WORLD00_AREA024_PTR_7AAC       MEM(volatile u8*, 0x80147AACu)
#define WORLD00_AREA024_SCRATCH_PTR    SP_REF(volatile Actor*, 0x44u)

extern VECTOR   D_801F2C04;
extern Callback D_801F4214[];

void func_801F2C58(void);
void func_801F2CB0(void);
void func_801F2D5C(void);
void func_801F2DB4(void);
void func_801F2DD8(void);
void func_801F2DF8(AreaSprite* sprite);
void func_801F2FD4(AreaSprite* sprite);
void func_801F3080(void);
s32  func_801F30EC(void);
void func_801F31B4(void);
void func_801F3250(void);
void func_801F32D4(void);
void func_801F32F4(void);
void func_801F3314(void);
void func_801F362C(void);
void func_801F3708(void* vertices, const void* rotated, s16* transform);
void func_801F3944(const SpinEffect* spin);
void func_801F3BE4(SpinEffect* spin);
void func_801F3D0C(void);
void func_801F3D5C(void);
s32  func_801F3E48(u8 shade);
void func_801F41EC(void);

s16 func_801F4158(DVECTOR* a, DVECTOR* b, DVECTOR* c);

#endif
