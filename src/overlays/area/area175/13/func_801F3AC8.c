#include "area175_13.h"

/* Answer handler of a 500 zenny offer: choice 0 requests message 0x6F and clears D_801448ED; any other choice
 * with g_Zenny >= 500 requests 0x7D and sets D_801448ED, otherwise requests 0x7C and writes 0xFF to byte 0x7A of
 * g_ScriptWorkRecord. No image references the function, and the texts of messages 0x6F, 0x7C and 0x7D are not
 * decoded, so the offer is unnamed: needs: name 801F3AC8 the caller or the text of message 0x7D. */
MATCH void func_801F3AC8(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = 0x6F;
        D_801448ED       = 0;
    } else if (g_Zenny >= 500u) {
        g_MessageRequest = 0x7D;
        D_801448ED       = 1;
    } else {
        g_MessageRequest                   = 0x7C;
        g_ScriptWorkRecord->callback_index = 0xFF;
    }
}
