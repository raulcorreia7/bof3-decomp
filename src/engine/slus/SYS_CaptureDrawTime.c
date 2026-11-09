#include "engine/slus/slus.h"

/* captures the current vertical-blank counter for the boot frame.
 */
MATCH void SYS_CaptureDrawTime(void) {
    D_80143EFC = VSync(1);
}
