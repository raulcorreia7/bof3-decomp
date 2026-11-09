#include "engine/slus/slus.h"

/* switches the stack to the top of the scratchpad, runs the three
 * front-end frame steps, clears the gameui bytes D_8014832C and D_8014832D, then
 * restores the interrupted stack pointer.
 */
MATCH void Area_DrawScene(void) {
    unsigned long stack;

    stack = GetSp();
    SetSp(SCRATCH_PAD + SCRATCH_PAD_SIZE);
    Area_RunBundleRecords();
    Area_DrawActors();
    func_8014BC70();
    D_8014832C = 0;
    D_8014832D = 0;
    SetSp(stack);
}
