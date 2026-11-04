#include "game_00.h"

MATCH void func_801A1384(void* entity) {
    u8* rec;
    u8* sub;
    u8  sel;
    u8  rate;
    u8  savedFlag;
    u16 savedState;
    u8  savedRoute;
    u8  mode;

    rec        = entity;
    savedRoute = g_SpadWork->direction_08;
    savedState = LOHU(rec[0x7E]);
    savedFlag  = rec[0x76];
    if (g_SpadWork->unk_09 != 0) {
        goto only_update; /* the pending entity update runs alone */
    }
    mode = rec[0x78];
    rate = g_RouteSpeedScale[mode];
    if (rec[0x7B] == 0) {
        ORDER_LOCK(sub = rec + 0x74); /* FAKE: order lock holds the pointer setup. */
        if (mode != 0) {
            sel = func_801A8D38(sub, (*(s32**)((u8*)g_AreaLoads[g_GameAreaId] + 0x10))[rec[0x77]]);
            if (rec[0x75] != 0) {
                func_801A275C(sub);
            }
            if (sel == GAME_NONE) {
                return;
            }
            if (g_SpadWork->direction_08 != sel) {
                g_SpadWork->direction_08 = sel;
                rec[0x74] |= ACTOR_FLAG_MOVING;
            }
            if (rec[0x7B] != 0) {
                Actor* spad;
                g_SpadWork->unk_0A = (u8)(0x10 / (s32)rate);
                rec[0x7B]--;
                if (((g_SpadWork->option_flags & ACTOR_OPT_NO_TARGET) == 0) &&
                    ((func_801A3AC8((Actor*)rec) << 0x18) != 0)) {
                    g_SpadWork->direction_08 &= 7;
                    rec[0x76] = savedFlag;
                    rec[0x7B] = 0;
                    rec[0x74] |= ACTOR_FLAG_MOVING | ACTOR_FLAG_SCRIPT_REQUEST;
                    spad            = g_SpadWork;
                    LOHU(rec[0x7E]) = savedState;
                    spad->unk_09    = 0;
                    return;
                }
            } else if ((g_SpadWork->unk_06 == 0x0A) && ((LOW(rec[0x74]) & 0x88) == 8)) {
                g_SpadWork->unk_0A    = (u8)(0x10 / (s32)rate);
                ((s32*)g_SpadWork)[3] = 0;
                ((s32*)g_SpadWork)[4] = 0;
                ((s32*)g_SpadWork)[5] = 0;
            }
            if ((rec[0x74] & ACTOR_FLAG_FADE_WHITE) != 0) {
                g_SpadWork->unk_03 = g_SpadWork->unk_01;
                g_SpadWork->unk_01 = 8;
                g_SpadWork->unk_04 = 0;
            }
            if ((rec[0x74] & ACTOR_FLAG_FADE_BLACK) != 0) {
                g_SpadWork->unk_03 = g_SpadWork->unk_01;
                g_SpadWork->unk_01 = 9;
                g_SpadWork->unk_04 = 0;
            }
        }
    } else {
        if (((g_SpadWork->option_flags & ACTOR_OPT_NO_TARGET) == 0) && ((func_801A3AC8((Actor*)rec) << 0x18) != 0)) {
            g_SpadWork->direction_08 &= 7;
            rec[0x74]          = rec[0x74] | ACTOR_FLAG_MOVING | ACTOR_FLAG_SCRIPT_REQUEST;
            g_SpadWork->unk_09 = 0;
            return;
        }
        g_SpadWork->unk_0A = (u8)(0x10 / (s32)rate);
        rec[0x7B]--;
        func_801ABBA8(rec + 0x74, g_SpadWork->direction_08 & 7);
        g_SpadWork->direction_08 |= 8;
        rec[0x74] |= ACTOR_FLAG_MOVING;
    }
    func_801A2AE4((Actor*)rec, savedRoute);
only_update:
    func_801A253C((Actor*)rec);
}
