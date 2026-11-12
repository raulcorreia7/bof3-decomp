#include "area135_14.h"

/* The message state byte and timer sit before the request halfword. */
MATCH void func_801F37C4(void) {
    u8* message;

    message = (u8*)&g_MessageRequest;
    /* FAKE: opaque base keeps one register for the state bytes across the layout call. */
    FAKE_OPAQUE(message);
    if (*(u16*)message != MESSAGE_NONE) {
        UI_UpdateLayout();
        if (message[-8] == 2) {
            message[-8] = 7;
        }
        if (message[-8] == 7) {
            message[-2] = 10;
        }
    }
}
