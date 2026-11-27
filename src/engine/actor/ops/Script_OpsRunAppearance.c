#include "engine/game/00/game_00.h"

#define CUR(s)       FIELD(u16, (s), 0xAu)
#define PACK24(c, o) (((s32)(s8)(c)[o] << 0x10) | ((c)[(o) + 1] << 8))

/* Opcodes 0xC0 to 0xCE of the actor script: palette fade, scale, tint, turning. */
typedef enum ActorScriptAppearance {
    ACTOR_SCRIPT_APPEARANCE_START_PALETTE_FADE   = 0xC0, /* args: [r] [g] [b] [steps]; claim a palette fade for the actor */
    ACTOR_SCRIPT_APPEARANCE_ADD_PALETTE_FADE     = 0xC1, /* args: [r] [g] [b]; raise the fade offset */
    ACTOR_SCRIPT_APPEARANCE_SUB_PALETTE_FADE     = 0xC2, /* args: [r] [g] [b]; lower the fade offset */
    ACTOR_SCRIPT_APPEARANCE_ADD_SCALE            = 0xC3, /* args: [mode] [x_hi] [x_lo] [y_hi] [y_lo]; grow the scale */
    ACTOR_SCRIPT_APPEARANCE_SUB_SCALE            = 0xC4, /* args: [mode] [x_hi] [x_lo] [y_hi] [y_lo]; shrink the scale */
    ACTOR_SCRIPT_APPEARANCE_SET_TRANSPARENCY     = 0xC5, /* args: [flags]; semi-transparent bit and blend mode */
    ACTOR_SCRIPT_APPEARANCE_ADD_TINT             = 0xC6, /* args: [r] [g] [b]; raise the tint */
    ACTOR_SCRIPT_APPEARANCE_ADD_SCALE_AND_MOVE   = 0xC7, /* args: scale x y, position x y z; grow and shift together */
    ACTOR_SCRIPT_APPEARANCE_TURN_TO              = 0xC8, /* args: [facing] [dir]; turn one step toward the facing, repeat until reached */
    ACTOR_SCRIPT_APPEARANCE_SET_UNK_2B           = 0xC9, /* args: [value]; store in the actor record */
    ACTOR_SCRIPT_APPEARANCE_SET_UNK_94           = 0xCA, /* args: [value]; store in the current actor */
    ACTOR_SCRIPT_APPEARANCE_SELECT_SCENE_SCRIPT  = 0xCB, /* args: [scene_hi] [scene_lo] [script] [flag]; select a scene record and its script */
    ACTOR_SCRIPT_APPEARANCE_WAIT_UNTIL_MOVE_ENDS = 0xCC, /* hold the cursor while the interaction is moving */
    ACTOR_SCRIPT_APPEARANCE_FREE_PALETTE_FADE    = 0xCD, /* release the actor palette fade */
    ACTOR_SCRIPT_APPEARANCE_TURN_TO_PARTY        = 0xCE, /* turn one step toward the party leader facing the actor */
} ActorScriptAppearance;

/* func_801AAB00 */
/* Runs one appearance opcode. */
#ifdef NON_MATCHING
NON_MATCHING u8 Script_OpsRunAppearance(void* sub, s32 target, u8 value) {
    u8* code;
    u8* cmd;
    u8  slot;
    s32 want;
    s32 cur;
    s32 val;
    u16 next;

    code = (u8*)target;
    switch (code[CUR(sub)]) {
        case ACTOR_SCRIPT_APPEARANCE_START_PALETTE_FADE:
            if (Actor_GetOwner() != 1) {
                g_CurrentActor->unk_93 = GFX_PaletteAllocFade(SELF(void), (code + CUR(sub))[1], (code + CUR(sub))[2], (code + CUR(sub))[3], (code + CUR(sub))[4]);
            } else {
                g_Game.current->palette_fade = GFX_PaletteAllocFade(SELF(void), (code + CUR(sub))[1], (code + CUR(sub))[2], (code + CUR(sub))[3], (code + CUR(sub))[4]);
            }
            CUR(sub) += 4;
            break;
        default:
            break;
        case ACTOR_SCRIPT_APPEARANCE_ADD_PALETTE_FADE:
            if (Actor_GetOwner() != 1) {
                g_PaletteFades[g_CurrentActor->unk_93].offset.r += (code + CUR(sub))[1];
                g_PaletteFades[g_CurrentActor->unk_93].offset.g += (code + CUR(sub))[2];
                g_PaletteFades[g_CurrentActor->unk_93].offset.b += (code + CUR(sub))[3];
            } else {
                g_PaletteFades[g_Game.current->palette_fade].offset.r += (code + CUR(sub))[1];
                g_PaletteFades[g_Game.current->palette_fade].offset.g += (code + CUR(sub))[2];
                g_PaletteFades[g_Game.current->palette_fade].offset.b += (code + CUR(sub))[3];
            }
            CUR(sub) += 3;
            break;
        case ACTOR_SCRIPT_APPEARANCE_SUB_PALETTE_FADE:
            if (Actor_GetOwner() != 1) {
                g_PaletteFades[g_CurrentActor->unk_93].offset.r -= (code + CUR(sub))[1];
                g_PaletteFades[g_CurrentActor->unk_93].offset.g -= (code + CUR(sub))[2];
                g_PaletteFades[g_CurrentActor->unk_93].offset.b -= (code + CUR(sub))[3];
            } else {
                g_PaletteFades[g_Game.current->palette_fade].offset.r -= (code + CUR(sub))[1];
                g_PaletteFades[g_Game.current->palette_fade].offset.g -= (code + CUR(sub))[2];
                g_PaletteFades[g_Game.current->palette_fade].offset.b -= (code + CUR(sub))[3];
            }
            CUR(sub) += 3;
            break;
        case ACTOR_SCRIPT_APPEARANCE_ADD_SCALE:
            LOBU(SELF(Actor)->vx) = (code + CUR(sub))[1];
            SELF(Actor)->scale.x += PACK24(code + CUR(sub), 2);
            SELF(Actor)->scale.y += PACK24(code + CUR(sub), 4);
            CUR(sub) += 5;
            break;
        case ACTOR_SCRIPT_APPEARANCE_SUB_SCALE:
            LOBU(SELF(Actor)->vx) = (code + CUR(sub))[1];
            SELF(Actor)->scale.x -= PACK24(code + CUR(sub), 2);
            SELF(Actor)->scale.y -= PACK24(code + CUR(sub), 4);
            CUR(sub) += 5;
            break;
        case ACTOR_SCRIPT_APPEARANCE_SET_TRANSPARENCY:
            if ((code + CUR(sub))[1] & 0x80) {
                *SELF(u8) |= ACTOR_FLAG_SEMI_TRANSPARENT;
            } else {
                *SELF(u8) &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
            }
            SELF(Actor)->tint.steps.flags = (code + CUR(sub))[1] & 3;
            CUR(sub) += 1;
            break;
        case ACTOR_SCRIPT_APPEARANCE_ADD_TINT:
            SELF(Actor)->tint.bytes.rgb.r += (code + CUR(sub))[1];
            SELF(Actor)->tint.bytes.rgb.g += (code + CUR(sub))[2];
            SELF(Actor)->tint.bytes.rgb.b += (code + CUR(sub))[3];
            CUR(sub) += 3;
            break;
        case ACTOR_SCRIPT_APPEARANCE_ADD_SCALE_AND_MOVE:
            LOBU(SELF(Actor)->vx) = 2;
            SELF(Actor)->scale.x += PACK24(code + CUR(sub), 1);
            SELF(Actor)->scale.y += PACK24(code + CUR(sub), 3);
            SELF(Actor)->pos.x.fixed += PACK24(code + CUR(sub), 5);
            SELF(Actor)->pos.y.fixed += PACK24(code + CUR(sub), 7);
            SELF(Actor)->pos.z.fixed += PACK24(code + CUR(sub), 9);
            CUR(sub) += 0xA;
            break;
        case ACTOR_SCRIPT_APPEARANCE_TURN_TO:
            cmd  = code + CUR(sub);
            slot = SELF(Actor)->direction;
            if (slot == cmd[1]) {
                CUR(sub) += 2;
            } else {
                target = cmd[2];
                want   = slot + 1;
                if (!(target & 0x80)) {
                    want = slot - 1;
                }
                SELF(Actor)->direction = want & 7;
                if (Actor_GetOwner() != 1) {
                    Script_DispatchSelector(SELF(Actor)->direction);
                } else {
                    Script_Select(SELF(Actor)->direction);
                }
                FIELD(s8, sub, 0x1u) = target & 0xF;
                CUR(sub) -= 1;
            }
            value = SELF(Actor)->direction;
            break;
        case ACTOR_SCRIPT_APPEARANCE_SET_UNK_2B:
            SELF(Actor)->unk_2B = (code + CUR(sub))[1];
            CUR(sub) += 1;
            break;
        case ACTOR_SCRIPT_APPEARANCE_SET_UNK_94:
            g_CurrentActor->unk_94 = (code + CUR(sub))[1];
            CUR(sub) += 1;
            break;
        case ACTOR_SCRIPT_APPEARANCE_SELECT_SCENE_SCRIPT:
            cmd = code + CUR(sub);
            Area_SceneSelectRecord(cmd[2] | (cmd[1] << 8));
            Script_Select((code + CUR(sub))[3]);
            FIELD(s8, g_Self, 0x2Au) = (code + CUR(sub))[4] & 1;
            CUR(sub) += 4;
            break;
        case ACTOR_SCRIPT_APPEARANCE_WAIT_UNTIL_MOVE_ENDS:
            if ((*(u16*)sub & 0x30) == 0x10) {
                CUR(sub) -= 1;
            }
            break;
        case ACTOR_SCRIPT_APPEARANCE_FREE_PALETTE_FADE:
            GFX_PaletteFreeFadeTarget(SELF(void));
            break;
        case ACTOR_SCRIPT_APPEARANCE_TURN_TO_PARTY:
            cur  = SELF(Actor)->direction & 7;
            want = g_Game.members[0].facing ^ 4;
            slot = cur;
            if (slot != want) {
                val = slot + 1;
                if (((want - cur) << 0x18) <= 0) {
                    val = slot - 1;
                }
                SELF(Actor)->direction = val & 7;
                if (Actor_GetOwner() != 1) {
                    Script_DispatchSelector(SELF(Actor)->direction);
                } else {
                    Script_Select(SELF(Actor)->direction);
                }
                FIELD(s8, sub, 0x1u) = 2;
                CUR(sub) -= 1;
            }
            value = SELF(Actor)->direction;
            break;
    }
    return value;
}
#else
INCLUDE_ASM(Script_OpsRunAppearance);
#endif
