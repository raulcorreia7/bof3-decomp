#include "start_08.h"

MATCH void func_801D8D64(void) {
    /* Pointer form: retail keeps one base register across the count load and
     * the store, which a symbol access would re-materialize. */
    u8* timer = &D_80148654;
    u8  count;

    Menu_DrawClutStrip(D_80144953);
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        D_80148652 += 1;
    }
}
