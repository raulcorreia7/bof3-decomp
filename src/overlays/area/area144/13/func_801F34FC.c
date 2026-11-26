#include "area144_13.h"

MATCH u8 func_801F34FC(void) {
    MATRIX world;
    MATRIX screen;
    Actor* task;
    u8*    record;
    u16    i;
    u8     active;

    active = 0;
    Camera_SetMatrix(&world);
    for (i = 0; i < 14; i++) {
        Camera_ProjectPoint((s32*)&D_801F3D80[i], (DVECTOR*)(AREA_WORK + 0xA8) + i);
    }
    Camera_SetMatrix(&screen);
    record = (u8*)AREA_WORK;
    for (i = 0; i < 6; record += 0x1C, i++) {
        if (record[0x18] == 0) {
            continue;
        }
        active = 1;
        switch (record[0x17]) {
            case 0:
                if (record[0x19] == 0) {
                    SND_SEPlay(D_801F3E60[D_801F4960]);
                    D_801F4960++;
                    if (D_801F4960 >= 3) {
                        D_801F4960 = 0;
                    }
                    record[0x19] = 15;
                    record[0x17]++;
                } else {
                    record[0x19]--;
                }
                continue;
            case 1:
                record[0x14] -= 0x10;
                record[0x16] -= 0x10;
                if (record[0x19] == 10) {
                    task   = SELF(Actor);
                    g_Self = (Actor*)&g_Game;
                    Script_Select(record[0x1A]);
                    g_Self = task;
                }
                if (--record[0x19] == 0) {
                    record[0x19] = 15;
                    record[0x17]++;
                }
                break;
            case 2:
                record[0x15] -= 0x10;
                if (--record[0x19] == 0) {
                    record[0x18] = 0;
                }
                break;
            case 3:
                record[0x15] -= 0x8;
                if (--record[0x19] == 0) {
                    record[0x18] = 0;
                }
                break;
            default:
                continue;
        }
        func_801F3124(record);
    }
    return active;
}
