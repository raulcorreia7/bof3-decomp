#include "area135_14.h"

MATCH void func_801F4464(void) {
    if (g_Self != &D_80143F48) {
        SELF(Actor)->pos.x.fixed = g_PartyActors[3].pos.x.fixed;
        SELF(Actor)->pos.y.fixed = g_PartyActors[3].pos.y.fixed;
        SELF(Actor)->pos.z.fixed = g_PartyActors[3].pos.z.fixed;
    } else {
        g_AreaCameraSpeed   = 0x20;
        g_AreaScrollTargetX = g_PartyActors[3].pos.x.fixed;
        g_AreaScrollTargetY = g_PartyActors[3].pos.y.fixed;
    }
}
