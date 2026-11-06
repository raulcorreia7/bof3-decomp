#include "shared/etc.h"

extern s8  D_8014854C;
extern s8  D_8014854D;
extern s8  D_8014854E;
extern s8  D_8014854F;
extern s16 D_80148550;
extern s16 D_80148552;
extern u8  D_80148556;
extern s8  D_80148571;
extern s8  D_80148572;
extern s16 D_80148576;
extern s8  D_80148595;
extern s8  D_80148596;
extern s16 D_80148598;
extern s16 D_8014859A;
extern s8  D_80148656;

u8 Party_CountOrder(u8 mode);

MATCH void func_801D2AC8(void) {
    u8  i;
    s8* panel;

    for (i = 0; i < (Party_CountOrder(PARTY_ORDER_KIND_WALKING)); i++) {
        if (i == D_80148656) {
            D_80148333[((i + 4) * 9) << 2]   = 5;
            D_80148333[((i + 0xC) * 9) << 2] = 3;
        } else {
            D_80148333[((i + 4) * 9) << 2]   = 7;
            D_80148333[((i + 0xC) * 9) << 2] = 5;
        }
    }
    panel                       = &D_8014854C;
    g_MenuPanelTasks[15].unk_01 = 6;
    g_MenuPanelTasks[15].unk_02 = 6;
    g_MenuPanelTasks[15].state  = 2;
    *panel                      = 1;
    panel += 0x24;
    g_MenuPanelTasks[15].pos.x  = BATTLE_PARTY_STRIDE;
    g_MenuPanelTasks[15].pos.y  = 0x74;
    g_MenuPanelTasks[16].unk_02 = 7;
    g_MenuPanelTasks[16].unk_01 = 6;
    g_BattleChoicePhase         = 2;
    g_MenuPanelTasks[15].unk_0A = D_80148656;
    *panel                      = 1;
    D_80148574                  = -100;
    g_MenuPanelTasks[16].pos.y  = 0x78;
    g_MenuPanelTasks[17].unk_02 = 8;
    g_MenuPanelTasks[16].unk_0A = D_80148656;
    g_MenuPanelTasks[17].unk_01 = 6;
    D_80148597                  = 2;
    panel += 0x24;
    *panel                      = 1;
    D_80148598                  = -100;
    g_MenuPanelTasks[17].pos.y  = 0xA8;
    g_MenuPanelTasks[17].unk_0A = D_80148656;
}
