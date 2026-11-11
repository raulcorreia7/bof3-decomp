#include "area121_14.h"
#include "scenario/state.h"

MATCH void func_801F5B90(void) {
    s32 value;
    s32 flag;

    if (g_AreaDrawFlags & 0x1B) {
        if (!(g_SceneState.flags_01 & SCENE_STATE_SCRIPT_ACTIVE)) {
            if (g_Game.members[0].timer == 0) {
                func_801F5AA0(0xDC, 0x10, 0);
                func_801F595C(0x40, 0);
                flag  = 1;
                value = 0x40;
                value -= g_Game.members[0].param.unk_0B;
                value &= 0xFF;
            } else {
                if (g_FrameCount & 2) {
                    func_801F5AA0(0xDC, 0x10, 1);
                } else {
                    func_801F5AA0(0xDC, 0x10, 2);
                }
                value = 0x40;
                flag  = 0;
            }
        } else {
            func_801F5AA0(0xDC, 0x10, 0);
            func_801F595C(0x40, 0);
            value = 0x40;
            flag  = 1;
        }
        func_801F595C(value, flag);
    }
}
