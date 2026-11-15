#include "area048_13.h"

MATCH void func_801F4AB4(void) {
    switch (D_8014686B) {
        case 8:
            g_CurrentActor->unk_77 = 8;
            break;
        case 6:
            g_CurrentActor->unk_77 = 7;
            break;
        case 2:
            g_CurrentActor->unk_77 = 6;
            break;
        default:
            g_CurrentActor->unk_77 = 9;
            break;
    }
    g_CurrentActor->unk_7E = 0xFFFE;
}
