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

#ifdef NON_MATCHING
NON_MATCHING void SAVE_BuildSlotImage(void) {
    s32 mode;
    s32 slot;
    s32 i;
    s32 j;
    s32 name_index;
    s32 col;
    u16 n;
    u16 sum;
    u32 count;
    u8* dst;
    u8* src;
    u8* dst_text;
    u8* src_text;
    u8* work;

    SAVE_FormatSlot();
    func_801EF27C(1, 0x13, g_UiFormatBuffer);
    *(ShopStateHeader*)&D_801448D8 = *(ShopStateHeader*)&g_SceneState;
    j                              = 0;
    D_80144948                     = 0;
    g_SavedScriptVars[0]           = g_ScriptVars[0];
    g_SavedScriptVars[1]           = g_ScriptVars[1];
    g_SavedScriptVars[2]           = g_ScriptVars[2];
    g_SavedScriptVars[3]           = g_ScriptVars[3];
    g_SaveEntryX                   = (u32)D_80145EC4;
    g_SaveEntryY                   = (u32)D_80145EC8;
    g_SaveAreaId                   = g_GameAreaId;
    g_SaveEntryFacing              = g_Game.members[0].facing;
    n                              = 0;
    j                              = 0;
    do {
        j                                        = n;
        *(u16*)((j * 2) + (&D_801448D8 + 0xCBC)) = (u16)g_InputMasks[j];
        n                                        = n + 1;
    } while ((u32)n < 9U);
    work     = (u8*)&g_SaveData;
    dst_text = work + 0xCA0;
    src_text = work + 0x90;
    strncpy((s8*)dst_text, (s8*)src_text, 5);
    slot = 0;
    col  = 0 & HALF_MASK;
    do {
        name_index = slot & HALF_MASK;
        if (g_PartyFieldOrder[col] == 4) {
            mode = SHOP_WORK->field_74C & 0x7F;
            if ((mode != 5) && (mode != 0xC)) {
                dst_text[col + 5] = 0xB;
            } else {
                name_index = slot & HALF_MASK;
                goto store_row; /* the kind-4 arm reaches the same store with its own index */
            }
        } else {
        store_row:
            dst_text[name_index + 5] = (u8)g_PartyFieldOrder[name_index];
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
    D_80145025                         = (u8)g_Game.flags;
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
    func_801D6CE4(g_SaveSlotFirst, (u8*)&g_SaveData);
}
#else
INCLUDE_ASM(SAVE_BuildSlotImage);
#endif
