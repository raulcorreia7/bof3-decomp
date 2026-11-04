#include "engine/slus/slus.h"

/* Handler ABI of the reviewed dispatch table this unit owns (0x801821D0,
 * 16 bytes): four handler entries taking the caller's seven arguments and
 * returning a byte result code. The seventh argument is a word in the slot:
 * func_8015C750 reads it with lw (0x38(sp)), so the table's type says s32.
 * func_8015C540 keeps its own u8 declaration because widening that unit's
 * parameter moves its bytes. */

/* The unit's reviewed .rodata placement: the four handler addresses that
 * D_801821D0 points at. The body reads them through the registered symbol. */
static GameFunc const s_dispatch[] = {
    Actor_InitMovement,
    (GameFunc)Actor_StepMovement,
    Actor_StepScroll,
    (GameFunc)Actor_RiseToGround,
};

/* forwards the caller's seven arguments to the handler the work
 * area's dispatch byte at +0x04 selects and returns the handler's byte result.
 */
MATCH s8 Actor_RunHandler(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_step, u8 landing_script, u8 flags) {
    return ((GameFunc*)(void*)&D_801821D0)[g_SpadWork->unk_04](entry, dir_x, dir_y, vz_start, vz_step, landing_script,
                                                               flags);
}
