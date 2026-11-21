#include "engine/slus/slus.h"

/* captures the current vertical-blank counter for the boot frame.
 */
MATCH void SYS_CaptureDrawTime(void) {
    g_SysDrawTime = VSync(1);
}
