#include "game_00.h"

/* Opcodes 0x80 to 0x8C of the actor script table: the record group that drives
 * the scene around the actor - script-active and fade flags, actor placement,
 * the area camera scroll, palette tints, the XA music stream, and spawning a
 * helper record. Named from the case bodies. */
/* Opcodes 0x80 to 0x8C of the actor script table: the record group that drives
 * the scene around the actor - script-active and fade flags, actor placement,
 * the area camera scroll, palette tints, the XA music stream, and spawning a
 * helper record. Named from the case bodies. */
typedef enum ActorScriptStageOp {
    ACTOR_SCRIPT_STAGE_SET_SCRIPT_ACTIVE   = 0x80, /* set GAME_FLAG_SCRIPT_ACTIVE */
    ACTOR_SCRIPT_STAGE_CLEAR_SCRIPT_ACTIVE = 0x81, /* clear GAME_FLAG_SCRIPT_ACTIVE */
    ACTOR_SCRIPT_STAGE_FADE_WHITE          = 0x82, /* set ACTOR_FLAG_FADE_WHITE on the cursor */
    ACTOR_SCRIPT_STAGE_FADE_BLACK          = 0x83, /* set ACTOR_FLAG_FADE_BLACK on the cursor */
    ACTOR_SCRIPT_STAGE_SET_TARGET_POS      = 0x84, /* args: [sel] [kind]; set SCRATCH_WORK to a position */
    ACTOR_SCRIPT_STAGE_CAMERA_SCROLL       = 0x85, /* advance the camera scroll to the held cell, ramp height */
    ACTOR_SCRIPT_STAGE_SET_RECORD_INDEX    = 0x86, /* args: [index]; pick the actor/game record, halt cursor */
    ACTOR_SCRIPT_STAGE_TINT_DARK           = 0x87, /* tint-darken handler for the actor kind (D_801C8904) */
    ACTOR_SCRIPT_STAGE_TINT_LIGHT          = 0x88, /* tint-lighten handler for the actor kind (D_801C88FC) */
    ACTOR_SCRIPT_STAGE_START_XA            = 0x89, /* args: [xa_id_u16]; SND_StartXAStream */
    ACTOR_SCRIPT_STAGE_SOUND_64020         = 0x8A, /* args: [id_u16]; the empty sound stub func_80164020 */
    ACTOR_SCRIPT_STAGE_WAIT_XA_IDLE        = 0x8B, /* wait while the XA stream is not idle */
    ACTOR_SCRIPT_STAGE_SPAWN_HELPER        = 0x8C, /* args: [flag]; func_8015CC00 claims a slot at the actor */
} ActorScriptStageOp;

#ifdef NON_MATCHING
NON_MATCHING u8 func_801AB458(GameCursorState* state, const u8* table, u8 value) {
    u8    byte;
    u8    flag;
    u8    slot;
    s32   delta_x;
    s32   delta_y;
    u32   sel;
    u32   span_y;
    s32   step;
    s32   span;
    s32   buf[3];
    void* entry;
    u32*  list;

    byte = table[state->index_0A];
    switch (byte) {
        case ACTOR_SCRIPT_STAGE_SET_SCRIPT_ACTIVE:
            g_Game.flags |= GAME_FLAG_SCRIPT_ACTIVE;
            break;
        case ACTOR_SCRIPT_STAGE_CLEAR_SCRIPT_ACTIVE:
            g_Game.flags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            break;
        case ACTOR_SCRIPT_STAGE_FADE_WHITE:
            state->flags |= ACTOR_FLAG_FADE_WHITE;
            break;
        case ACTOR_SCRIPT_STAGE_FADE_BLACK:
            state->flags |= ACTOR_FLAG_FADE_BLACK;
            break;
        case ACTOR_SCRIPT_STAGE_SET_TARGET_POS: {
            volatile Actor* work;

            func_801ABF30(buf, table[state->index_0A + 1], table[state->index_0A + 2]);
            work              = SCRATCH_WORK;
            work->pos.x.fixed = buf[0];
            work->pos.y.fixed = buf[1];
            work->pos.z       = buf[2];
            state->index_0A += 2;
            break;
        }
        case ACTOR_SCRIPT_STAGE_CAMERA_SCROLL: {
            s32* base;

            base = &D_80145EC4;
            if ((g_AreaScrollTargetX != base[0]) || (g_AreaScrollTargetY != base[1])) {
                delta_x = g_AreaScrollTargetX - base[0];
                delta_x = ABS(delta_x);
                sel     = (u32)delta_x >> 15;
                delta_y = g_AreaScrollTargetY - base[1];
                delta_y = ABS(delta_y);
                span_y  = (u32)delta_y >> 15;
                if ((sel & BYTE_MASK) < (span_y & BYTE_MASK)) {
                    sel = span_y;
                }
                Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
                g_AreaScrollTargetX = base[0];
                g_AreaScrollTargetY = base[1];
                span                = Area_SampleHeight(base[0], base[1]);
                g_AreaCameraStep    = 0x20;
                step                = sel & BYTE_MASK;
                if (step == 0) {
                    g_AreaCameraHeightStep = 0;
                } else {
                    g_AreaCameraHeightStep = (s16)(((s16)span - (s32)g_AreaCameraHeight) / (step * 4));
                }
                state->index_0A--;
                break;
            }
            if (g_AreaCameraMoving != 0) {
                state->index_0A--;
                break;
            }
            span = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
            Area_AdvanceScroll((s16)span);
            break;
        }
        case ACTOR_SCRIPT_STAGE_SET_RECORD_INDEX:
            if (Actor_GetOwner() == 1) {
                entry                             = g_AreaLoads[g_GameAreaId];
                byte                              = table[state->index_0A + 1];
                list                              = *(u32**)((u8*)entry + 0x18);
                g_Game.current->u.field.index_124 = list[byte];
            } else {
                state->unk_03 = table[state->index_0A + 1];
            }
            state->index_0A = 0xFFFF;
            break;
        case ACTOR_SCRIPT_STAGE_TINT_DARK:
            func_801ACBC4();
            break;
        case ACTOR_SCRIPT_STAGE_TINT_LIGHT:
            func_801AC9D0();
            break;
        case ACTOR_SCRIPT_STAGE_START_XA:
            SND_StartXAStream((table[state->index_0A + 1] << 8) | table[state->index_0A + 2], 1);
            state->index_0A += 2;
            break;
        case ACTOR_SCRIPT_STAGE_SOUND_64020:
            func_80164020((table[state->index_0A + 1] << 8) | table[state->index_0A + 2], 1);
            state->index_0A += 2;
            break;
        case ACTOR_SCRIPT_STAGE_WAIT_XA_IDLE:
            if ((SND_IsXAIdle() & BYTE_MASK) != 0) {
                break;
            }
            state->index_0A--;
            break;
        case ACTOR_SCRIPT_STAGE_SPAWN_HELPER: {
            volatile Actor* work;

            flag               = table[state->index_0A + 1];
            slot               = g_Game.current->chr.character_id;
            work               = SCRATCH_WORK;
            work->param.unk_0B = func_8015CC00(flag - 0x90, -((flag ^ 0x94) == 0) & 0xA, D_80181B28[g_CharSlot[slot]], work->pos.x.fixed, work->pos.y.fixed, work->pos.z.fixed);
            state->index_0A += 1;
            break;
        }
        default:
            break;
    }
    return value;
}
#else
INCLUDE_ASM(func_801AB458);
#endif
