#include "engine/game/00/game_00.h"

MATCH void Game_MenuReturn(void) {
    u8  sep_index;
    u8  seq_index;
    u8* request;
    u8* pending;

    Game_MenuUpdateFrame();
    UI_ModeSet(2u);
    UI_WindowWaitEffect(0u);
    SYS_ThreadWait(1u);
    if (D_80148661 != 0u) {
        EMI_PartyLoadArchives(g_PartyFieldOrder[0], g_PartyFieldOrder[1], g_PartyFieldOrder[2], 0u);
        while (EMI_IsReady() == 0) {
            SYS_ThreadWait(1u);
        }
        D_80148661 = 0u;
    }
    g_EmiStreamFlags = 0x20;
    EMI_ArchiveLoadFamily(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    while (EMI_IsReady() == 0) {
        SYS_ThreadWait(1u);
    }
    if (g_GameRequestFlags & AREA_LOAD_FLAG_FAIRY_VILLAGE) {
        EMI_ArchiveLoad(EMI_SLOT_COMMU00);
        while (EMI_IsReady() == 0) {
            SYS_ThreadWait(1u);
        }
        func_801F03D0();
    }
    UI_ModeSet(3u);
    Area_WaitWindowEffect(1u);
    if ((D_80143F20 == 0x6Eu) && !(SND_VoiceTestEffectsBusy(&sep_index, &seq_index) & BYTE_MASK)) {
        SND_SeqFadeIn(sep_index, seq_index, 0x14, 0x10);
    }
    request = &D_8014869C;
    if (*request != 0u) {
        pending  = &D_8014504A;
        *request = 0u;
        if ((*pending == 0u) && ((g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) || (LOHU(g_GameAreaId) == AREA_ID_DESERT_OF_DEATH_MAP))) {
            *pending   = 1u;
            D_80145040 = g_Game.members[0].pos.x.fixed;
            D_80145044 = g_Game.members[0].pos.y.fixed;
            D_80145048 = g_GameAreaId;
            D_8014504B = (g_Game.members[0].facing + s_DirectionJitters[RANDOM_MASK(3)]) & 0xF;
            Game_RequestAreaChange(g_GameEntryAreaId, g_GameEntryPosX, g_GameEntryPosY, g_GameEntryFacing);
        } else {
            u8* clear = &D_8014504A;

            *clear = 0u;
            SYS_ClearFlag(clear - 0x122, 119u);
            Game_RequestAreaChange(D_80145048, D_80145040, D_80145044, FACING_DOWN_RIGHT);
        }
    } else if (D_8014869D != 0u) {
        Game_RequestAreaChange(D_8014869D, TO_COORD(67), TO_COORD(22), FACING_DOWN_RIGHT);
        D_8014869D = 0u;
    } else {
        g_GameStateIndex = GAME_REQUEST_IDLE;
    }
    UI_PanelResetTasks();
    g_GameEntryState    = GAME_MODE_FIELD;
    g_GameEntrySubstate = 0u;
}
