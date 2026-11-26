#include "area175_13.h"

/* func_801F3374 */
MATCH void Area_FadeOutScreenTint(void) {
    SELF(Actor)->timer -= 1;
    if (SELF(Actor)->timer != 0) {
        SELF(Actor)->tint.bytes.rgb.r -= 6;
        SELF(Actor)->tint.bytes.rgb.g -= 6;
        SELF(Actor)->tint.bytes.rgb.b -= 6;
    } else {
        SELF(Actor)->header.mode = 4;
    }
    Area_DrawScreenTint();
}
