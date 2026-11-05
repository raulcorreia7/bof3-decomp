#ifndef OVERLAY_WORLD00_AREA024_14_H
#define OVERLAY_WORLD00_AREA024_14_H

/* The area024 world overlay's local declarations: its sprite, spin and scratch
 * work records, handler table and prototypes. Only this image includes the
 * file. */

#include "overlays/area/world00.h"

#define WORLD00_AREA024_WORK_BASE      MEM_PTR(volatile AreaSprite, 0x800E4800u)
#define WORLD00_AREA024_SPIN_WORK_BASE MEM_PTR(u8, 0x800E5000u)
#define WORLD00_AREA024_STATE_BASE     MEM_PTR(volatile s16, 0x800E4940u)
#define WORLD00_AREA024_STATE_OFFSET   MEM_PTR(volatile s16, 0x800E4944u)
#define WORLD00_AREA024_VERTEX_DST     MEM_PTR(volatile u8, 0x800E4BC8u)
#define WORLD00_AREA024_PTR_7AA8       MEM(volatile u8*, 0x80147AA8u)
#define WORLD00_AREA024_PTR_7AAC       MEM(volatile u8*, 0x80147AACu)
#define WORLD00_AREA024_SCRATCH_PTR    SP_REF(volatile Area024Scratch*, 0x44u)

#define g_SpadWork                     ((volatile Area024Scratch*)g_SpadWork)

typedef struct AreaSprite {
    u8                flags_00; /* set to 1 when the sprite is armed */
    u8                flags_01;
    u8                flags_02; /* set to 4 */
    u8                flags_03; /* set to 0x40 */
    /* 0x04 */ s32    origin_x; /* the camera x, copied from the scratch record */
    /* 0x08 */ s32    origin_y; /* the camera y */
    /* 0x0C */ s32    origin_z; /* the camera z */
    u8                unk_10[4];
    /* 0x14 */ VECTOR normal;    /* the sprite's normal */
    /* 0x24 */ u16    half_size; /* the projected half-size */
} AreaSprite;

ASSERT_SIZE(AreaSprite, 0x28);

typedef struct Area024Scratch {
    u8             unk_00[0x01]; /* byte 0x00 */
    /* 0x01 */ u8  dispatch;     /* indexes the D_801F4200 handler table */
    u8             unk_02[0x07];
    /* 0x09 */ u8  step_count; /* the step counter */
    u8             unk_0A[0x2A];
    /* 0x34 */ s32 pos_x;
    /* 0x38 */ s32 pos_y;
    /* 0x3C */ s32 pos_z;
} Area024Scratch;

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

typedef struct AreaSpin {
    /* 0x00 */ s32     origin_x; /* the camera x, copied from the scratch record */
    /* 0x04 */ s32     origin_y; /* the camera y */
    /* 0x08 */ s32     origin_z; /* the camera z */
    u8                 unk_0C[4];
    /* 0x10 */ SVECTOR vertex_a;   /* the first rotated vertex offset */
    /* 0x18 */ SVECTOR vertex_b;   /* the second rotated vertex offset */
    /* 0x20 */ s16     angle_lo;   /* the angle accumulator's low half */
    /* 0x22 */ s16     angle_hi;   /* the angle accumulator's high half */
    /* 0x24 */ s16     spin_angle; /* the spin angle */
    s16                unk_26;
    /* 0x28 */ s16     scale; /* the vertex scale */
    /* 0x2A */ s16     fade;  /* the triangle fade */
} AreaSpin;

ASSERT_SIZE(AreaSpin, 0x2C);

extern volatile u8 D_80147A58;
extern VECTOR      D_801F2C04;
extern Callback    D_801F4214[];

void Matrix_SetIdentity(MATRIX* matrix);
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

#endif
