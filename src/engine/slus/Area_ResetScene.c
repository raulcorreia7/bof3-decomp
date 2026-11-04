#include "engine/slus/slus.h"

/* resets the mode work record: clears the counters g_AreaCameraStep/g_AreaCameraHeightStep and the words at
 * +0x0C..+0x14 of the work area, sets byte +0x11C of the mode work area to 3, then runs func_80167428 (when the 0xF000
 * field of D_8014625C is set) or arms the work flag byte at +0x01.
 */
MATCH void Area_ResetScene(void) {
    Actor*        work;
    PartyBattler* mode_work;

    work                        = g_SpadWork;
    mode_work                   = g_GameState;
    g_AreaCameraStep            = 0;
    g_AreaCameraHeightStep      = 0;
    work->unk_0C                = 0;
    work->unk_10                = 0;
    work->vz                    = 0;
    *(u8*)&mode_work->hp_change = 3; /* FAKE: retail stores the byte. */
    if (D_8014625C & INPUT_DIRECTIONAL) {
        func_80167428();
    } else {
        g_SpadWork->unk_01 = 1;
    }
}
