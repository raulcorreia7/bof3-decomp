#include "game_00.h"

MATCH void Battle_LoadPartySprites(void) {
    u8            ready;
    volatile u16* coord_a;
    s32           sum;
    volatile u16* coord_b;
    s32           index;
    volatile u8*  flags;
    u16*          state;
    u16           count;
    s8            dy;
    s32           span;

    ready = Battle_LoadPartyScripts();
    func_801A06D8();
    func_801992B8();
    if (ready != 0) {
        SND_SetBankLayout(1);
        flags = &g_Battle.outcome.options;
        if ((*flags & 0x1) == 0) {
            coord_a  = (volatile u16*)&g_AreaTargetCellX;
            index    = g_Battle.scroll_dir;
            *coord_a = *coord_a + s_BattleScrollCellSteps[index].dx;
            dy       = s_BattleScrollCellSteps[index].dy;
            FAKE_BARRIER(); /* FAKE: keeps the delta load before the span math. */
            span                   = D_801CD954;
            g_AreaCameraStep       = 0x40;
            span                   = span - g_AreaCameraHeight;
            g_AreaCameraHeightStep = span >> 4;
            coord_b                = (volatile u16*)&g_AreaTargetCellY;
            sum                    = *coord_b + dy;
            *coord_b               = sum;
        }
        if ((*flags & 0x10) == 0) {
            if (g_Battle.scroll_dir & 0x2) {
                EMI_GetArchiveId(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_BPLU);
            } else {
                EMI_GetArchiveId(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_BPLD);
            }
        }
        state                    = &g_GameEntrySubstate;
        count                    = *state;
        g_AreaDrawMode           = 4;
        g_AreaCameraRefreshCount = 2;
        D_8014933F               = g_Battle.scroll_dir & 0x1;
        count++;
        *state = count;
    }
}
