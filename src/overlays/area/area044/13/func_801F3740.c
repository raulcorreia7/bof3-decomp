#include "area044_13.h"
#include "menu/save_data.h"

MATCH void func_801F3740(void) {
    u8 state;
    u8 state_type;
    u8 slot;

    state      = g_ScriptVars[3];
    state_type = state & 3;
    slot       = (state & 0x30) >> 4;

    switch (g_SceneEventStep) {
        case 0:
            if (slot == 0) {
                if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x17) != 0) {
                    func_801F318C(FACING_LEFT, 1);
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 1));
                    g_ScriptVars[3]  = (g_ScriptVars[3] & 0x0F) | 0x20;
                    g_SceneEventStep = 1;
                    break;
                }
            } else if (slot == 2) {
                if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x17) == 0) {
                    func_801F318C(FACING_RIGHT, 1);
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 1));
                    g_ScriptVars[3] &= 0x0F;
                    g_SceneEventStep = 1;
                    break;
                }
            }
            g_SceneEventStep = 10;
            break;

        case 1:
            if (D_80147AF9 != 0) {
                break;
            }
            func_801F2DF4();
            /* fallthrough */
        case 10: {
            s8* step;

            if (state_type == 0) {
                if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x17) != 0) {
                    func_801F318C(FACING_DOWN, 0);
                    g_ScriptVars[3] = (g_ScriptVars[3] & 0xF0) | 2;
                    goto advance;
                }
            } else if (state_type == 2) {
                if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x17) == 0) {
                    func_801F318C(FACING_UP, 0);
                    g_ScriptVars[3] &= 0xF0;
                    goto advance;
                }
            }
            goto tail;
        advance:
            SND_PlayCue((g_SceneEventStep == 1) ? EMI_CUE_ID(SND_BANK_AREA, 0x0E) : EMI_CUE_ID(SND_BANK_AREA, 1));
            g_SceneEventStep = 11;
        tail:
            step = &g_SceneEventStep;
            if (*step != 11) {
                if (*step == 1) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
                }
                *step = 20;
            }
        } break;

        case 11:
            if (D_80147A61 == 0) {
                func_801F2DF4();
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
                g_SceneEventStep = 20;
            }
            break;

        case 20:
            g_SceneEventMode = SCENE_EVENT_NONE;
            g_SceneEventStep = 0;
            Game_ClearScriptActive();
            break;
    }
}
