#include "shop_00.h"

/* The 16-byte shop state header copied into the work block. */
typedef struct ShopStateHeader {
    u8 bytes[16];
} ShopStateHeader;

/* The 0xCA0-offset record inside the shop work block. */
typedef struct ShopWorkRecord {
    u8  pad_00[0x8];
    u8  field_08;
    u8  field_09;
    u8  field_0A;
    u8  pad_0B;
    s32 field_0C;
    u8  pad_10[4];
    s32 field_14;
} ShopWorkRecord;

/* The shop work block, sparse: only the cells this unit reads. */
typedef struct ShopWork {
    u8  pad_00[0x6E8];
    s32 field_6E8;
    u8  pad_6EC[0x8E];
    u8  field_7A;
    u8  field_7B;
    u8  pad_7C[0xD0];
    u8  field_74C;
} ShopWork;

/* The work block the shop state is published through. */
#define SHOP_WORK_BASE           0x801448D8u
#define SHOP_WORK_RECORD(offset) ((ShopWorkRecord*)(SHOP_WORK_BASE + (offset)))
#define SHOP_WORK                ((ShopWork*)SHOP_WORK_BASE)

/* nonmatching unmeasured: tried the first draft (39.90%); 16-byte struct copy (49.74%); byte-array copy for the unaligned
 * lwl/lwr (56.85%); u16 loop counter and u16 destination store (63.45%); the FIELD offset views replaced by typed
 * fields and the work-text pointer, the first-draft pointer juggling removed (61.62%). residual is the register
 * allocation of the second row loop: retail homes the work base in s2, the row base in s3 and the constants in
 * t0/t1/a0-a3, the candidate homes them in s0 and v1. resume: a source shape that gives the work base the s2 home and
 * the loop constants their own registers, without keeping the work-text pointer alive past the row loop. */
#ifdef NON_MATCHING
NON_MATCHING void SAVE_BuildSlotImage(void) {
    s32 mode;
    s32 slot;
    s32 i;
    s32 j;
    s32 idx;
    s32 col;
    u16 n;
    u16 sum;
    u32 count;
    u8* dst;
    u8* src;
    u8* dst_text;
    u8* src_text;
    u8* work;

    func_801D7080();
    func_801EF27C(1, 0x13, g_UiFormatBuffer);
    *(ShopStateHeader*)&D_801448D8 = *(ShopStateHeader*)&g_SceneState;
    j                              = 0;
    D_80144948                     = 0;
    D_801448F8                     = g_ScriptVars[0];
    D_801448F9                     = g_ScriptVars[1];
    D_801448FA                     = g_ScriptVars[2];
    D_801448FB                     = g_ScriptVars[3];
    D_80144900                     = (u32)D_80145EC4;
    D_80144904                     = (u32)D_80145EC8;
    D_801448FC                     = g_GameAreaId;
    D_801448FF                     = D_80145E98;
    n                              = 0;
    j                              = 0;
    do {
        j                                        = n;
        *(u16*)((j * 2) + (&D_801448D8 + 0xCBC)) = (u16)(&g_InputMasks)[j];
        n                                        = n + 1;
    } while ((u32)n < 9U);
    work     = &D_801448D8;
    dst_text = work + 0xCA0;
    src_text = work + 0x90;
    strncpy((s8*)dst_text, (s8*)src_text, 5);
    slot = 0;
    col  = 0 & HALF_MASK;
    do {
        idx = slot & HALF_MASK;
        if (D_80144F5A[col] == 4) {
            mode = SHOP_WORK->field_74C & 0x7F;
            if ((mode != 5) && (mode != 0xC)) {
                dst_text[col + 5] = 0xB;
            } else {
                idx = slot & HALF_MASK;
                goto store_row; /* the kind-4 arm reaches the same store with its own index */
            }
        } else {
        store_row:
            dst_text[idx + 5] = (u8)D_80144F5A[idx];
        }
        slot += 1;
        col = slot & HALF_MASK;
    } while ((u32)(slot & HALF_MASK) < 3U);
    src                                = g_SceneEventFlags;
    SHOP_WORK_RECORD(0xCA0u)->field_08 = src_text[6];
    SHOP_WORK_RECORD(0xCA0u)->field_0C = SHOP_WORK->field_6E8;
    SHOP_WORK_RECORD(0xCA0u)->field_09 = SHOP_WORK->field_7A;
    SHOP_WORK_RECORD(0xCA0u)->field_0A = SHOP_WORK->field_7B;
    SHOP_WORK_RECORD(0xCA0u)->field_14 = *(s32*)(src_text + 8);
    sum                                = 0;
    dst                                = g_SaveBuffer;
    src                                = g_SceneEventFlags - 0x650;
    i                                  = 0;
    SHOP_WORK_RECORD(0xCA0u)->field_14 = SYS_TestFlag(g_SceneEventFlags, 0x92U);
    D_80145025                         = (u8)g_GameFlags;
    do {
        i += 1;
        count = i & HALF_MASK;
        *dst  = *src;
        dst += 1;
        sum += *src;
        src += 1;
    } while (count < SAVE_BLOCK_SIZE);
    if (count < 0x1E00U) {
        do {
            *dst = 0;
            i += 1;
            dst += 1;
        } while ((u32)(i & HALF_MASK) < 7680U);
    }
    D_800C1A70 = sum;
    if (g_SaveSlotFirst == g_SaveSlotCount) {
        g_SaveSlotCount += 1;
    }
    func_801D6CE4(g_SaveSlotFirst, &D_801448D8);
}
#else
INCLUDE_ASM(SAVE_BuildSlotImage);
#endif
