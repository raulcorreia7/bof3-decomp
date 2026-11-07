#include "area170_13.h"

MATCH void func_801F388C(s32 x, s32 y, s8 kind) {
    if (kind == 1) {
        func_801F3774(x + 2, y + 5, x + 8, y + 5, 0xC8, 0, 0, 0);
        func_801F3774(x + 5, y + 2, x + 5, y + 8, 0xC8, 0, 0, 0);
    } else if (kind == -1) {
        func_801F3774(x + 2, y + 5, x + 8, y + 5, 0, 0, 0xC8, 0);
    }
}
