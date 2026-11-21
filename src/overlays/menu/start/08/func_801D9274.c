#include "start_08.h"

MATCH u8* func_801D9274(const u8* name, u8 mode) {
    s32 resource;

    if (mode != 0) {
        UI_MessageSetVariable(0, 0xC, name);
    }
    switch (mode) {
        case 0:
            resource = 0x35;
            break;
        case 1:
            resource = 0x36;
            break;
        case 3:
            resource = 0x37;
            break;
        case 2:
            resource = 0x38;
            break;
        case 4:
            resource = 0x39;
            break;
        case 5:
        default:
            resource = 0x3A;
            break;
    }
    return UI_MessageGetText(resource);
}
