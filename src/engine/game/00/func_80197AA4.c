#include "game_00.h"

MATCH void func_80197AA4(void) {
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

    ready = (u8)func_801BEE5C();
    func_801A06D8();
    func_801992B8();
    if (ready != 0) {
        SND_SetBankLayout(1);
        flags = &g_BattleOptions;
        if ((*flags & 1) == 0) {
            coord_a  = (volatile u16*)&D_8014930A;
            index    = g_BattleScrollDir;
            *coord_a = *coord_a + D_801C7B74[index].dx;
            dy       = D_801C7B74[index].dy;
            MATCH_BARRIER(); /* FAKE: keeps the delta load before the span math. */
            span                   = (s32)D_801CD954;
            g_AreaCameraStep       = 0x40;
            span                   = span - (s32)g_AreaCameraHeight;
            g_AreaCameraHeightStep = span >> 4;
            coord_b                = (volatile u16*)&D_8014930E;
            sum                    = *coord_b + dy;
            *coord_b               = sum;
        }
        if ((*flags & 0x10) == 0) {
            if (g_BattleScrollDir & 2) {
                EMI_StreamFamilyArchive(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_BPLU);
            } else {
                EMI_StreamFamilyArchive(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_BPLD);
            }
        }
        state                    = &g_GameEntrySubstate;
        count                    = *state;
        g_AreaDrawMode           = 4;
        g_AreaCameraRefreshCount = 2;
        D_8014933F               = g_BattleScrollDir & 1;
        count++;
        *state = count;
    }
}
