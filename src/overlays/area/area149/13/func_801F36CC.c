#include "area149_13.h"

MATCH void func_801F36CC(void) {
    s32 y;
    s32 x;

    if (g_GameLastAreaId == 0x94) {
        D_80147A8E += 22;
        y = g_AreaFocus.y.fixed;
        /* FAKE: keeps the focus x load after the integer-half store; pure C differs in 11 rows. */
        FAKE_BARRIER();
        x                          = g_PartyActors[0].pos.x.fixed;
        g_PartyActors[0].unk_77    = 1;
        g_PartyActors[0].unk_7E    = 0;
        g_AreaFocus.z.part.integer = Area_HeightSample(x, y);
        g_AreaSceneMode            = 1;
        if (SYS_TestFlag(&g_SceneFlagWords[14 * 8], 0x11) != 0) {
            g_SceneEventMode = 0x21;
            g_SceneEventStep = 0;
            D_801448EE       = 0x5A;
        }
    }
    if (g_GameLastAreaId == 0xA7) {
        g_PartyActors[0].unk_77 = 2;
        g_AreaSceneMode         = 2;
        g_SceneEventMode        = 0x21;
        g_SceneEventStep        = 0xA;
        g_PartyActors[0].unk_7E = 0;
        D_801448EE              = 0x5A;
    }
}
