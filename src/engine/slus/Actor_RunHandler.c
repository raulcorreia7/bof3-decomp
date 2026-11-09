#include "engine/slus/slus.h"

/* Handler ABI of the reviewed dispatch table this unit owns (0x801821D0, 16 bytes). */

/* The unit's reviewed .rodata placement: the four handler addresses that D_801821D0 points at. */
static GameFunc const s_dispatch[] = {
    Actor_InitMovement,
    (GameFunc)Actor_StepMovement,
    Actor_StepScroll,
    (GameFunc)Actor_RiseToGround,
};

/* forwards the caller's seven arguments to the handler the work area's dispatch byte at +0x04 selects and returns the handler's byte result. */
MATCH s8 Actor_RunHandler(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags) {
    return ((GameFunc*)(void*)&D_801821D0)[g_Task->unk_04](entry, dir_x, dir_y, vz_start, vz_delta, landing_script,
                                                           flags);
}
