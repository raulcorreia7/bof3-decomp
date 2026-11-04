#include "area121_14.h"

MATCH void func_801F2D30(void) {
    g_CurrentActor->flags_74 &= 0xFE;
    g_CurrentActor->unk_77 = 0;
    g_CurrentActor->unk_7E = 0;
    SND_PlayCue(0x217);
    Game_SetScriptActive();
    *g_ScriptVars = 0;
    D_80146865    = 0;
    D_80146866    = 0;
    D_80146867    = 0;
    D_80146875    = 0;
    D_80146874    = 4;
}
