#include "area175_13.h"

/* func_801F3374 */
MATCH void Area_FadeOutScreenTint(void) {
    TASK(Actor)->timer -= 1;
    if (TASK(Actor)->timer != 0) {
        TASK(Actor)->tint.bytes.rgb.r -= 6;
        TASK(Actor)->tint.bytes.rgb.g -= 6;
        TASK(Actor)->tint.bytes.rgb.b -= 6;
    } else {
        TASK(Actor)->header.mode = 4;
    }
    Area_DrawScreenTint();
}
