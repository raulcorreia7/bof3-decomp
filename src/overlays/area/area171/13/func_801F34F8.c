#include "area171_13.h"

MATCH void func_801F34F8(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        D_801448EB = 0xA;
        D_801448EC = 5;
        D_801448ED = 0xFF;
    }
}
