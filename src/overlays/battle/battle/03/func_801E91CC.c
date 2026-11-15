#include "battle_03.h"

MATCH void func_801E91CC(void) {
    MenuPanelTask* panel = g_MenuCurrentPanel;

    Battle_SetPartyCount((s16)panel->pos.x, (s16)panel->pos.y);
}
