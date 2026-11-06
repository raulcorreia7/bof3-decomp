#include "area041_13.h"

MATCH void func_801F4288(u8* arg0) {
    SYS_SetFlag(g_SaveData.scene_event_flags, D_801F5651[arg0[0x7A]]);
    SND_PlayCue(0x201);
}
