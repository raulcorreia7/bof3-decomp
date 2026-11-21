#include "engine/game/00/game_00.h"

/* func_801984E8 */
MATCH void Game_EndFishing(void) {
    RECT rect;
    s32* ptr_503C = &D_8014503C;

    *ptr_503C = *ptr_503C + 1;
    func_801DE1C0();
    UI_ModeSet(1u);
    Camera_Update();
    Area_DrawScene();
    rect.w = 64;
    rect.x = 0;
    rect.h = 120;
    rect.y = (g_GfxBufferIndex * SCREEN_HEIGHT) + 80;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 0x340, 0x100);
    GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(DR_MOVE));
    func_801E0BD0();
    g_EncounterSteps = 0;
    g_GameStateIndex = GAME_REQUEST_IDLE;
    {
        u16 tmp_3B92 = g_GameEntrySubstate;
        u16 tmp_625A = g_AreaWalkFlags;
        tmp_3B92 += 1;
        tmp_625A &= 0xFFBF;
        g_Game.walk_flags   = tmp_625A;
        g_GameEntrySubstate = tmp_3B92;
    }
}
