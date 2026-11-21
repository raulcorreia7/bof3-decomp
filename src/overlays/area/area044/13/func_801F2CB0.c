#include "area044_13.h"

/* Place the first two work records at the script row's cells; states 0 and 2 clear the vars and flags. */
MATCH void func_801F2CB0(void) {
    u8  mode;
    u8  index;
    u8  row;
    u8* flags;

    mode = g_GameCellType;
    if (mode == 0 || mode == 2) {
        flags           = g_SceneEventFlags;
        g_ScriptVars[2] = 0;
        g_ScriptVars[3] = 0;
        SYS_ClearFlag(flags, 0x16);
        SYS_ClearFlag(flags, 0x17);
    } else if (mode == 1) {
        index = (g_ScriptVars[3] & 3) * 2;
        row   = (g_ScriptVars[3] & 0x30) >> 3;

        g_PartyActors[0].pos.x.part.integer  = D_801F3FB4[index];
        g_PartyActors[0].pos.x.part.fraction = COORD_HALF;
        g_PartyActors[0].pos.y.part.integer  = D_801F3FB4[index + 1];
        g_PartyActors[0].pos.y.part.fraction = COORD_HALF;
        g_PartyActors[0].pos.z.part.integer  = 0x80;
        g_PartyActors[0].interaction_flags |= 0x80;

        g_PartyActors[1].pos.x.part.integer  = D_801F3FBC[row];
        g_PartyActors[1].pos.x.part.fraction = COORD_HALF;
        g_PartyActors[1].pos.y.part.integer  = D_801F3FBC[row + 1];
        g_PartyActors[1].pos.y.part.fraction = COORD_HALF;
        g_PartyActors[1].pos.z.part.integer  = 0x80;
        g_PartyActors[1].interaction_flags |= 0x80;
        func_801F2DF4();
    }
}
