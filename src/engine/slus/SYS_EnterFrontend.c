#include "engine/slus/slus.h"

/* streams BIN/ETC/GAME.EMI (slot 0x262) and calls its entry once the loader is
 * ready.
 */
MATCH void SYS_EnterFrontend(void) {
    EMI_LoaderStreamInitSlot(EMI_SLOT_GAME);
    while (EMI_LoaderIsReady() == 0) {
        CallbackWait(1);
    }
    func_801D0C04(); /* GAME.EMI entry */
}
