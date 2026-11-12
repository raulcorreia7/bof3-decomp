#include "game_00.h"

#define CUR(s)       FIELD(u16, (s), 0xAu)
#define PACK24(c, o) (((s32)(s8)(c)[o] << 0x10) | ((c)[(o) + 1] << 8))

#ifdef NON_MATCHING
NON_MATCHING u8 func_801AAB00(void* sub, s32 target, u8 value) {
    u8* code;
    u8* cmd;
    u8  slot;
    s32 want;
    s32 cur;
    s32 val;
    u16 next;

    code = (u8*)target;
    switch (code[CUR(sub)]) {
        case 0xC0:
            if (Actor_GetOwner() != 1) {
                g_CurrentActor->unk_93 = GFX_AllocPaletteFade(g_Task, (code + CUR(sub))[1], (code + CUR(sub))[2], (code + CUR(sub))[3], (code + CUR(sub))[4]);
            } else {
                g_Game.current->unk_13D = GFX_AllocPaletteFade(g_Task, (code + CUR(sub))[1], (code + CUR(sub))[2], (code + CUR(sub))[3], (code + CUR(sub))[4]);
            }
            CUR(sub) += 4;
            break;
        default:
            break;
        case 0xC1:
            if (Actor_GetOwner() != 1) {
                slot = g_CurrentActor->unk_93;
                g_PaletteFades[slot].offset.red += (code + CUR(sub))[1];
                g_PaletteFades[g_CurrentActor->unk_93].offset.green += (code + CUR(sub))[2];
                slot = g_CurrentActor->unk_93;
            } else {
                slot = g_Game.current->unk_13D;
                g_PaletteFades[slot].offset.red += (code + CUR(sub))[1];
                g_PaletteFades[g_Game.current->unk_13D].offset.green += (code + CUR(sub))[2];
                slot = g_Game.current->unk_13D;
            }
            g_PaletteFades[slot].offset.blue += (code + CUR(sub))[3];
            CUR(sub) += 3;
            break;
        case 0xC2:
            if (Actor_GetOwner() != 1) {
                slot = g_CurrentActor->unk_93;
                g_PaletteFades[slot].offset.red -= (code + CUR(sub))[1];
                g_PaletteFades[g_CurrentActor->unk_93].offset.green -= (code + CUR(sub))[2];
                slot = g_CurrentActor->unk_93;
            } else {
                slot = g_Game.current->unk_13D;
                g_PaletteFades[slot].offset.red -= (code + CUR(sub))[1];
                g_PaletteFades[g_Game.current->unk_13D].offset.green -= (code + CUR(sub))[2];
                slot = g_Game.current->unk_13D;
            }
            g_PaletteFades[slot].offset.blue -= (code + CUR(sub))[3];
            CUR(sub) += 3;
            break;
        case 0xC3:
            LOBU(g_Task->vx) = (code + CUR(sub))[1];
            g_Task->scale.x += PACK24(code + CUR(sub), 2);
            g_Task->scale.y += PACK24(code + CUR(sub), 4);
            CUR(sub) += 5;
            break;
        case 0xC4:
            LOBU(g_Task->vx) = (code + CUR(sub))[1];
            g_Task->scale.x -= PACK24(code + CUR(sub), 2);
            g_Task->scale.y -= PACK24(code + CUR(sub), 4);
            CUR(sub) += 5;
            break;
        case 0xC5:
            if ((code + CUR(sub))[1] & 0x80) {
                *(u8*)g_Task |= ACTOR_FLAG_SEMI_TRANSPARENT;
            } else {
                *(u8*)g_Task &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
            }
            g_Task->tint.signed_bytes.flags = (code + CUR(sub))[1] & 3;
            CUR(sub) += 1;
            break;
        case 0xC6:
            g_Task->tint.bytes.unk_5D += (code + CUR(sub))[1];
            g_Task->tint.bytes.unk_5E += (code + CUR(sub))[2];
            g_Task->tint.bytes.unk_5F += (code + CUR(sub))[3];
            CUR(sub) += 3;
            break;
        case 0xC7:
            LOBU(g_Task->vx) = 2;
            g_Task->scale.x += PACK24(code + CUR(sub), 1);
            g_Task->scale.y += PACK24(code + CUR(sub), 3);
            g_Task->pos.x.fixed += PACK24(code + CUR(sub), 5);
            g_Task->pos.y.fixed += PACK24(code + CUR(sub), 7);
            g_Task->pos.z.fixed += PACK24(code + CUR(sub), 9);
            CUR(sub) += 0xA;
            break;
        case 0xC8:
            next = CUR(sub) + 2;
            cmd  = code + CUR(sub);
            slot = g_Task->direction_08;
            if (slot != cmd[1]) {
                target = cmd[2];
                want   = slot + 1;
                if (!(target & 0x80)) {
                    want = slot - 1;
                }
                g_Task->direction_08 = want & 7;
                if (Actor_GetOwner() != 1) {
                    func_8015BAC4(g_Task->direction_08);
                } else {
                    Actor_SelectScript(g_Task->direction_08);
                }
                FIELD(s8, sub, 0x1u) = target & 0xF;
                next                 = CUR(sub) - 1;
            }
            CUR(sub) = next;
            value    = g_Task->direction_08;
            break;
        case 0xC9:
            g_Task->unk_2B = (code + CUR(sub))[1];
            CUR(sub) += 1;
            break;
        case 0xCA:
            g_CurrentActor->unk_94 = (code + CUR(sub))[1];
            CUR(sub) += 1;
            break;
        case 0xCB:
            cmd = code + CUR(sub);
            Area_SelectSceneRecord(cmd[2] | (cmd[1] << 8));
            Actor_SelectScript((code + CUR(sub))[3]);
            FIELD(s8, g_Task, 0x2Au) = (code + CUR(sub))[4] & 1;
            CUR(sub) += 4;
            break;
        case 0xCC:
            if ((*(u16*)sub & 0x30) == 0x10) {
                CUR(sub) -= 1;
            }
            break;
        case 0xCD:
            GFX_FreePaletteFadeTarget(g_Task);
            break;
        case 0xCE:
            cur  = g_Task->direction_08 & 7;
            want = g_Game.members[0].facing ^ 4;
            if (cur != want) {
                val = cur + 1;
                if (((want - cur) << 0x18) <= 0) {
                    val = cur - 1;
                }
                g_Task->direction_08 = val & 7;
                if (Actor_GetOwner() != 1) {
                    func_8015BAC4(g_Task->direction_08);
                } else {
                    Actor_SelectScript(g_Task->direction_08);
                }
                FIELD(s8, sub, 0x1u) = 2;
                CUR(sub) -= 1;
            }
            value = g_Task->direction_08;
            break;
    }
    return value;
}
#else
INCLUDE_ASM(func_801AAB00);
#endif
