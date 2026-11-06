#include "area175_13.h"

MATCH void func_801F3D94(void) {
    u8 selection;

    /* The caller stores the selected slot as an unsigned byte. */
    selection = MEM(u8, &g_MessageChoice);
    MESSAGE_REQUEST_CLEAR();
    D_801F2944 = selection;
}
