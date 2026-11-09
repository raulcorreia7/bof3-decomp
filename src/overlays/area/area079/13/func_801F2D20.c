#include "area079_13.h"

MATCH void func_801F2D20(void) {
    s8 choice = g_MessageChoice;

    g_MessageRequest = D_801F4C70[choice];
    switch (choice) {
        case 0:
            D_80146867 = 11;
            break;
        case 1:
            D_80146867 = 12;
            break;
        case 2:
            D_80146867 = 13;
            break;
        case 3:
            D_80146867 = 14;
            break;
        case 4:
            D_80146867 = 15;
            break;
        case 5:
            D_80146867 = 16;
            break;
    }
}
