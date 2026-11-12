#include "game_00.h"

MATCH void func_801AD734(void) {
    Actor* work;
    u32    choice;
    s8     value;

    choice = RANDOM_MASK(0xF);
    if ((g_Task->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
        func_8015BAC4(((g_Game.members[0].facing ^ 0x4) & 0x7));
    }
    g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
    if ((FIELD(u8, GAME_WORK_AREA_PTR, 0x94u) & 0x80) == 0) {
        FIELD(u8, GAME_WORK_AREA_PTR, 0x94u) |= 0x80;
        switch ((u8)choice) {
            case 0:
            case 1:
            case 2:
            case 3:
                func_801ADAC0(1);
                g_Task->unk_04 = 1;
                break;
            case 4:
            case 5:
            case 6:
                func_801ADAC0(1);
                Party_AddZenny(1, 0);
                func_801ADCF4(((s32)(-(((s32)GAME_WORK_AREA_PTR - (s32)g_Actors) * 0xD79435E5)) >> 3));
                g_Task->unk_04 = 2;
                break;
            case 7:
                func_801ADAC0(1);
                Party_AddZenny(10, 0);
                func_801ADCF4(((s32)(-(((s32)GAME_WORK_AREA_PTR - (s32)g_Actors) * 0xD79435E5)) >> 3));
                g_Task->unk_04 = 3;
                break;
            default:
                func_801ADAC0(3);
                g_Task->unk_04 = 1;
                break;
        }
    } else {
        if (choice >= 8) {
            func_801ADAC0(1);
        } else {
            func_801ADAC0(3);
        }
        g_Task->unk_04 = 1;
    }
    value                   = -0x50;
    work                    = g_Task;
    work->tint.bytes.unk_5E = value;
    work->tint.bytes.unk_5F = value;
    work->tint.bytes.unk_5D = value;
}
