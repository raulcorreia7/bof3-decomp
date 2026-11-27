#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801B0E44(void) {
    u8         saved_dir;
    s32        diff;
    u8         divisor;
    GameState* game;
    u32        walk_flags;
    /* FAKE: Keep the case-2 flag word in the return register; six words otherwise swap v0 and v1. */
    FAKE_REG(u32, entry_flags, "v0");
    /* FAKE: Pin the scratch position; the unpinned draft swaps the result and pointer registers. */
    FAKE_REG(s32*, pos2, "s1");
    s32 x;
    s32 y;
    s32 result;
    /* FAKE: retail's frame is 16 bytes larger than the statements need. */
    FAKE_STACK_PADS(s32, 16);

    saved_dir = SELF(Actor)->direction;
    result    = func_801B9598();
    if ((SELF(Actor)->direction == FACING_UP_RIGHT) || (SELF(Actor)->direction == FACING_DOWN_LEFT)) {
        SELF(Actor)->timer = 32;
    } else {
        SELF(Actor)->timer = 16;
    }
    divisor            = g_RouteSpeedScale[g_Game.current->u.field.counter.unsigned_value];
    SELF(Actor)->timer = (u8)(SELF(Actor)->timer / (u32)(divisor & BYTE_MASK));
    if (SELF(Actor)->voice_flags.scene_flag == 0) {
        SP_REF(s32, 0x8) = SELF(Actor)->pos.x.fixed + g_FacingOffsets[SELF(Actor)->direction].x * divisor * SELF(Actor)->timer;
        SP_REF(s32, 0xC) = SELF(Actor)->pos.y.fixed + g_FacingOffsets[SELF(Actor)->direction].y * divisor * SELF(Actor)->timer;
    } else {
        SP_REF(s32, 0x8) = SELF(Actor)->pos.x.fixed + g_FacingOffsets[SELF(Actor)->direction].x * divisor * SELF(Actor)->timer * 2;
        SP_REF(s32, 0xC) = SELF(Actor)->pos.y.fixed + g_FacingOffsets[SELF(Actor)->direction].y * divisor * SELF(Actor)->timer * 2;
    }
    if (g_GameStateIndex != GAME_REQUEST_SCENE_CAMERA) {
        if (((s32 (*)(s32, s32))Area_IsStepBlocked)(SP_REF(s32, 0x8), SP_REF(s32, 0xC)) != 0) {
            result = 0;
            if (SELF(Actor)->header.mode == 2) {
                return 0xFF;
            }
        }
    }
    switch (result & BYTE_MASK) {
        case 2:
            pos2 = (s32*)&g_ScratchPad.cells.halves[4];
            /* FAKE: Keep the position address in a register for the route-byte reads. */
            FAKE_OPAQUE(pos2);
            /* FAKE: The caller truncates the height after the scratch flag test. */
            result = ((s32 (*)(s32, s32, s32))Area_HeightReadStep)(pos2[0], SP_REF(s32, 0xC), SELF(Actor)->direction);
            func_801B13BC();
            if (((u8*)pos2)[-8] != 0) {
                if ((s16)result >= 0x41) {
                    if (!(Area_RequestLinkAtCell(SP_REF(s16, 0x4), SP_REF(s16, 0x6)) & BYTE_MASK) && (g_Self == (void*)g_Game.members)) {
                        if (Area_CellSetPalette(g_Game.members[0].pos.x.part.integer, g_Game.members[0].pos.y.part.integer) & BYTE_MASK) {
                            SND_SEPlay(D_801CD0F4[((u8*)pos2)[-7]]);
                            Script_Request((SELF(Actor)->direction >> 1) + 0x10);
                        } else {
                            Script_Request(SELF(Actor)->direction);
                        }
                        g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
                    }
                    g_AreaCameraSpeed = 0;
                    return 4;
                }
                x = ((s16*)pos2)[-2];
                y = ((s16*)pos2)[-1];
            } else {
                diff = COORD_INT(SELF(Actor)->pos.z) - (s16)result;
                diff = ABS(diff);
                if (diff >= 0x81) {
                    if (!(Area_RequestLinkAtCell(SP_REF(s16, 0x4), SP_REF(s16, 0x6)) & BYTE_MASK)) {
                        g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
                    }
                    g_AreaCameraSpeed = 0;
                    return 1;
                }
                x = SP_REF(s16, 0x4);
                y = SP_REF(s16, 0x6);
            }
            if (Area_RequestLinkAtCell(x, y) & BYTE_MASK) {
                return 0;
            }
            game             = &g_Game;
            entry_flags      = game->walk_flags;
            g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
            entry_flags |= 0x20 | AREA_WALK_ENTRY_PENDING;
            g_Game.walk_flags = entry_flags;
            return 0;
        case 3:
            pos2 = (s32*)&g_ScratchPad.cells.halves[4];
            /* FAKE: Keep the position address live across the first height read. */
            FAKE_OPAQUE(pos2);
            /* FAKE: The caller truncates the height after the scratch flag test. */
            result = ((s32 (*)(s32, s32, s32))Area_HeightReadStep)(pos2[0], pos2[1], SELF(Actor)->direction);
            if (SP_REF(u8, 0x0) != 0) {
                if ((s16)result >= 0x41) {
                    g_AreaCameraSpeed      = 0;
                    SELF(Actor)->direction = saved_dir;
                    return 1;
                }
                Area_HeightRead(pos2[0], pos2[1]);
                return 0;
            }
            return 0;
        case 4:
            func_801B13BC();
            if (!(Area_RequestLinkAtCell(SP_REF(s16, 0x4), SP_REF(s16, 0x6)) & BYTE_MASK)) {
                game       = &g_Game;
                walk_flags = game->walk_flags;
                walk_flags |= 0x80 | AREA_WALK_ENTRY_PENDING;
                game->walk_flags = walk_flags;
                return 2;
            }
            return 1;
        case 5:
            func_801B13BC();
            if (!(Area_RequestLinkAtCell(SP_REF(s16, 0x4), SP_REF(s16, 0x6)) & BYTE_MASK)) {
                game       = &g_Game;
                walk_flags = game->walk_flags;
                walk_flags |= 0x100 | AREA_WALK_ENTRY_PENDING;
                game->walk_flags = walk_flags;
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
