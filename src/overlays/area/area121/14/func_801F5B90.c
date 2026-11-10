#include "area121_14.h"
#include "scenario/state.h"

void func_801F595C(s32 arg0, s32 arg1);

MATCH void func_801F5B90(void) {
    s32 arg0;
    s32 arg1;

    if (g_AreaDrawFlags & 0x1B) {
        if (!(g_SceneState.flags_01 & SCENE_STATE_SCRIPT_ACTIVE)) {
            if (g_Game.members[0].timer == 0) {
                func_801F5AA0(0xDC, 0x10, 0);
                func_801F595C(0x40, 0);
                arg1 = 1;
                arg0 = 0x40;
                arg0 -= g_Game.members[0].param.unk_0B;
                arg0 &= 0xFF;
            } else {
                if (g_FrameCount & 2) {
                    func_801F5AA0(0xDC, 0x10, 1);
                } else {
                    func_801F5AA0(0xDC, 0x10, 2);
                }
                arg0 = 0x40;
                arg1 = 0;
            }
        } else {
            func_801F5AA0(0xDC, 0x10, 0);
            func_801F595C(0x40, 0);
            arg0 = 0x40;
            arg1 = 1;
        }
        func_801F595C(arg0, arg1);
    }
}
