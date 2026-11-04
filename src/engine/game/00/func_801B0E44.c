#include "game_00.h"

/* nonmatching unmeasured: s1-held D_1F800008 pointer folds to absolute. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_801B0E44(void) {
    u8   saved_dir;
    s32  diff;
    u8   divisor;
    s32* pos2;
    s32* pos3;
    s32  x;
    s32  y;
    s32  result;
    /* FAKE: retail's frame is 16 bytes larger than the statements need. */
    STACK_PADS(s32, 16);

    saved_dir = g_SpadWork->route_index_08;
    result    = func_801B9598();
    if ((g_SpadWork->route_index_08 == 2) || (g_SpadWork->route_index_08 == 6)) {
        g_SpadWork->unk_09 = 0x20;
    } else {
        g_SpadWork->unk_09 = 0x10;
    }
    divisor            = g_RouteSpeedScale[g_GameState->counter_11C.u8_value];
    g_SpadWork->unk_09 = (u8)(g_SpadWork->unk_09 / (u32)(divisor & BYTE_MASK));
    if (g_SpadWork->state_70.byte == 0) {
        SP_REF(s32, 0x8) =
            g_SpadWork->x.fixed + g_FacingOffsets[g_SpadWork->route_index_08].x * divisor * g_SpadWork->unk_09;
        SP_REF(s32, 0xC) =
            g_SpadWork->y.fixed + g_FacingOffsets[g_SpadWork->route_index_08].y * divisor * g_SpadWork->unk_09;
    } else {
        SP_REF(s32, 0x8) =
            g_SpadWork->x.fixed + g_FacingOffsets[g_SpadWork->route_index_08].x * divisor * g_SpadWork->unk_09 * 2;
        SP_REF(s32, 0xC) =
            g_SpadWork->y.fixed + g_FacingOffsets[g_SpadWork->route_index_08].y * divisor * g_SpadWork->unk_09 * 2;
    }
    if (g_GameStateIndex != GAME_REQUEST_SCENE_CAMERA) {
        if (Area_IsStepBlocked(SP_REF(s32, 0x8), SP_REF(s32, 0xC)) != 0) {
            result = 0;
            if (g_SpadWork->unk_01 == 2) {
                return 0xFF;
            }
        }
    }
    switch (result & BYTE_MASK) {
        case 2:
            pos2   = (s32*)&D_1F800008;
            result = Area_ReadStepHeight(*(s32*)&D_1F800008, SP_REF(s32, 0xC), g_SpadWork->route_index_08);
            func_801B13BC();
            if (((u8*)pos2)[-8] != 0) {
                if ((s16)result >= 0x41) {
                    if (!(func_801A0048(SP_REF(s16, 0x4), SP_REF(s16, 0x6)) & BYTE_MASK) &&
                        (g_SpadWork == (void*)g_BattlePartyBattlers)) {
                        if (Area_SetCellPalette(D_80145EC6, D_80145ECA) & BYTE_MASK) {
                            SND_PlayCue(D_801CD0F4[((u8*)pos2)[-7]]);
                            Actor_RequestScript((g_SpadWork->route_index_08 >> 1) + 0x10);
                        } else {
                            Actor_RequestScript(g_SpadWork->route_index_08);
                        }
                        g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
                    }
                    g_AreaCameraStep = 0;
                    return 4;
                }
                x = ((s16*)pos2)[-2];
                y = ((s16*)pos2)[-1];
            } else {
                diff = g_SpadWork->z.part.integer - (s16)result;
                if (diff < 0) {
                    diff = -diff;
                }
                if (diff >= 0x81) {
                    if (!(func_801A0048(SP_REF(s16, 0x4), SP_REF(s16, 0x6)) & BYTE_MASK)) {
                        g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
                    }
                    g_AreaCameraStep = 0;
                    return 1;
                }
                x = SP_REF(s16, 0x4);
                y = SP_REF(s16, 0x6);
            }
            if (func_801A0048(x, y) & BYTE_MASK) {
                return 0;
            }
            g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
            g_AreaWalkFlags |= 0x20 | AREA_WALK_ENTRY_PENDING;
            return 0;
        case 3:
            pos3   = (s32*)&D_1F800008;
            result = Area_ReadStepHeight(pos3[0], pos3[1], g_SpadWork->route_index_08);
            if (SP_REF(u8, 0x0) != 0) {
                if ((s16)result >= 0x41) {
                    g_AreaCameraStep           = 0;
                    g_SpadWork->route_index_08 = saved_dir;
                    return 1;
                }
                Area_ReadHeight(pos3[0], pos3[1]);
                return 0;
            }
            return 0;
        case 4:
            func_801B13BC();
            if (!(func_801A0048(SP_REF(s16, 0x4), SP_REF(s16, 0x6)) & BYTE_MASK)) {
                g_AreaWalkFlags |= 0x80 | AREA_WALK_ENTRY_PENDING;
                return 2;
            }
            return 1;
        case 5:
            func_801B13BC();
            if (!(func_801A0048(SP_REF(s16, 0x4), SP_REF(s16, 0x6)) & BYTE_MASK)) {
                g_AreaWalkFlags |= 0x100 | AREA_WALK_ENTRY_PENDING;
                return 3;
            }
            return 1;
        case 6:
            return 5;
        case 7:
            return 6;
        case 0:
            return 1;
        default:
            return 0;
    }
}
#else
INCLUDE_ASM(func_801B0E44);
#endif
