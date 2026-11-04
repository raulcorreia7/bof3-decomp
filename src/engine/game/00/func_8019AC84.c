#include "game_00.h"

MATCH void func_8019AC84(void) {
    Actor* work;

    func_8019A904();
    work         = (Actor*)SCRATCH_WORK;
    work->unk_10 = ((work->unk_0C - g_AreaCameraOffsetZ) << 0x10) / work->unk_09;
}
