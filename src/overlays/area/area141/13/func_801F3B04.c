#include "area141_13.h"

MATCH void func_801F3B04(void) {
    u8 i;

    if (D_80143F03 == 0) {
        func_801F4300(&D_801F4D94, 1);
        func_801F4300(&D_801F4D94 + 5, 1);
    }
    if (D_80143F03 == 1) {
        if (SYS_TestFlag(g_SceneEventFlags, 122) == 0) {
            i = 2;
            do {
                func_801F4300(i * 5 + &D_801F4D94, 1);
                i++;
            } while (i < 4);
        } else {
            i = 2;
            do {
                func_801F4300(i * 5 + &D_801F4D94, 0);
                i++;
            } while (i < 4);
        }
        if (SYS_TestFlag(g_SceneEventFlags, 123) == 0) {
            i = 4;
            do {
                func_801F4300(i * 5 + &D_801F4D94, 1);
                i++;
            } while (i < 6);
        } else {
            i = 4;
            do {
                func_801F4300(i * 5 + &D_801F4D94, 0);
                i++;
            } while (i < 6);
        }
        if (SYS_TestFlag(g_SceneEventFlags, 124) == 0) {
            i = 6;
            do {
                func_801F4300(i * 5 + &D_801F4D94, 1);
                i++;
            } while (i < 8);
        } else {
            i = 6;
            do {
                func_801F4300(i * 5 + &D_801F4D94, 0);
                i++;
            } while (i < 8);
        }
    }
    if (D_80143F03 == 2) {
        func_801F4300(D_801F4DBC, 1);
    }
}
