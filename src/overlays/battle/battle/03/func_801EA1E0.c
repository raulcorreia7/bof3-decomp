#include "battle_03.h"

MATCH void func_801EA1E0(s32 panel_arg0, s32 panel_arg1, s32 panel_arg2, s32 panel_arg3, s32 panel_arg4, s32 panel_arg5, s32 panel_arg6, u8* selector) {
    BattlePanelTaskForwarders local;

    local = g_BattlePanelTaskForwarders;
    local.handlers[*selector](panel_arg0, panel_arg1, panel_arg2, panel_arg3, panel_arg4, panel_arg5, panel_arg6, selector);
}
