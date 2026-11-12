#include "area021_13.h"

MATCH void func_801F2C10(void) {
    s8  sel;
    u16 request;

    sel = g_MessageChoice;
    if (sel == 0) {
        if (g_Zenny < 20) {
            request = 0x17;
        } else {
            Party_SpendZenny(20, 0);
            request = 0x11;
        }
    } else {
        request = 0x18;
    }
    g_MessageRequest = request;
}
