#include "engine/slus/slus.h"

/* streams BIN/ETC/GAME.EMI (slot 0x262) and calls its entry once the loader is
 * ready.
 */
MATCH void SYS_EnterFrontend(void) {
    EMI_LoadArchive(EMI_SLOT_GAME);
    while (EMI_IsReady() == 0) {
        SYS_ThreadWait(1);
    }
    func_801D0C04(); /* GAME.EMI entry */
}
