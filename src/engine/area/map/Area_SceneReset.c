#include "engine/slus/slus.h"

/* resets the mode work record: clears the counters g_AreaCameraSpeed/g_AreaCameraHeightDelta and the words at
 * +0x0C..+0x14 of the work area, sets byte +0x11C of the mode work area to 3, then runs func_80167428 (when the 0xF000
 * field of g_Game.input is set) or arms the work flag byte at +0x01.
 */
MATCH void Area_SceneReset(void) {
    Actor*       work;
    PartyMember* mode_work;

    work                    = SELF(Actor);
    mode_work               = g_Game.current;
    g_AreaCameraSpeed       = 0;
    g_AreaCameraHeightDelta = 0;
    setVector(work, 0, 0, 0);
    *(u8*)&mode_work->u.turn.hp_change = 3; /* FAKE: retail stores the byte. */
    if (g_Game.input & INPUT_DIRECTIONAL) {
        func_80167428();
    } else {
        SELF(Actor)->header.mode = 1;
    }
}
