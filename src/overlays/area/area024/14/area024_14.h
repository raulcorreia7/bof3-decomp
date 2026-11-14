#ifndef OVERLAY_WORLD00_AREA024_14_H
#define OVERLAY_WORLD00_AREA024_14_H

/* The area024 world overlay's local declarations: its sprite, spin and scratch
 * work records, handler table and prototypes. Only this image includes the
 * file. */

#include "common/vector.h"
#include "overlays/area/AreaSprite.h"
#include "overlays/area/world00.h"
#include "shared/WorldSpin.h"

#define WORLD00_AREA024_WORK_BASE      MEM_PTR(volatile AreaSprite, AREA_WORK)
#define WORLD00_AREA024_SPIN_WORK_BASE MEM_PTR(u8, 0x800E5000u)
#define WORLD00_AREA024_STATE_BASE     MEM_PTR(volatile s16, 0x800E4940u)
#define WORLD00_AREA024_STATE_OFFSET   MEM_PTR(volatile s16, 0x800E4944u)
#define WORLD00_AREA024_VERTEX_DST     MEM_PTR(volatile u8, 0x800E4BC8u)
#define WORLD00_AREA024_PTR_7AA8       MEM(volatile u8*, 0x80147AA8u)
#define WORLD00_AREA024_PTR_7AAC       MEM(volatile u8*, 0x80147AACu)
#define WORLD00_AREA024_SCRATCH_PTR    SP_REF(volatile Area024Scratch*, 0x44u)

#define g_Task                         ((volatile Area024Scratch*)g_Task)

typedef struct Area024Scratch {
    u8            unk_00[0x01]; /* byte 0x00 */
    /* 0x01 */ u8 dispatch;     /* indexes the D_801F4200 handler table */
    u8            unk_02[0x07];
    /* 0x09 */ u8 step_count; /* the step counter */
    u8            unk_0A[0x2A];
    Point3l      pos;
} Area024Scratch;

ASSERT_SIZE(Area024Scratch, 0x40);
ASSERT_OFFSET(Area024Scratch, pos, 0x34);

/* Per-sprite transform state at 0x800E4940 (0x18-byte stride): the halfword
 * translation base at +0x00 and the rotation angles at +0x10. */
typedef struct AreaTransform {
    /* 0x00 */ u16     base_x;
    /* 0x02 */ u16     base_y;
    /* 0x04 */ u16     base_z;
    u8                 pad_06[0x0A];
    /* 0x10 */ SVECTOR rotation;
} AreaTransform;

ASSERT_SIZE(AreaTransform, 0x18);

extern volatile u8 D_80147A58;
extern VECTOR      D_801F2C04;
extern Callback    D_801F4214[];

void func_801F2C58(void);
void func_801F2CB0(void);
void func_801F2D5C(void);
void func_801F2DB4(void);
void func_801F2DD8(void);
void func_801F2DF8(const void* sprite);
void func_801F2FD4(void* sprite);
void func_801F3080(void);
s32  func_801F30EC(void);
void func_801F31B4(void);
void func_801F3250(void);
void func_801F32D4(void);
void func_801F32F4(void);
void func_801F3314(void);
void func_801F362C(void);
void func_801F3708(void* vertices, const void* rotated, s16* transform);
void func_801F3944(const void* spin);
void func_801F3BE4(void* spin);
void func_801F3D0C(void);
void func_801F3D5C(void);
s32  func_801F3E48(u8 shade);
void func_801F41EC(void);

s16 func_801F4158(DVECTOR* a, DVECTOR* b, DVECTOR* c);

#endif
