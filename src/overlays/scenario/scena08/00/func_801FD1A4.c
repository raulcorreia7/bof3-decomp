#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FD1A4(void) {
    SpawnedActor* record;
    u8*           progress;
    u8            progress_value;
    u16*          countdown;
    u16           countdown_value;
    u8            object_index;

    switch (D_80146875) {
        case 0:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            Area_StartScrollRoute(0);
            D_80146875 = 1;
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            break;
        case 1:
            progress       = &g_ScriptVars[0];
            progress_value = *progress;
            if ((progress_value & 0xFF) != 0x14) {
                break;
            }
            *progress  = progress_value + 1;
            D_80146876 = 0x78;
            D_80146875 = 2;
            break;
        case 2:
            countdown       = &D_80146876;
            countdown_value = *countdown - 1;
            *countdown      = countdown_value;
            if (countdown_value != 0) {
                break;
            }
            D_80146875 = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            Game_ClearScriptActive();
            Game_RequestAreaChange(0xD, TO_COORD(25), TO_COORD(16), 0x84);
            SYS_SetFlag(g_SceneFlags, 0xF);
            goto reset;
        case 4:
            break;
        case 5:
            Scene_SetupParty(5);
            D_80146875 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            object_index              = Actor_FindFreeSpawned();
            D_1F800000.cells.bytes[0] = object_index;
            if (object_index != 0xFF) {
                record               = &g_SpawnedActors[object_index];
                record->header.flags = 1;
                record->type         = 0x5F;
                record->header.mode  = 6;
            }
            D_80146876 = 0x1E;
            D_80146875 = 7;
            break;
        case 7:
            countdown       = &D_80146876;
            countdown_value = *countdown - 1;
            *countdown      = countdown_value;
            if (countdown_value != 0) {
                break;
            }
            g_ScriptVars[0] = 0;
            Game_ClearScriptActive();
            SND_PlayCue(0x203);
            SYS_SetFlag(g_SceneFlags, 0x10);
            Game_RequestAreaChange(0xF, TO_COORD_HALF(25), TO_COORD(81), 1);
        reset:
            D_80146874 = 0;
            D_80146875 = 0;
            break;
    }
}
