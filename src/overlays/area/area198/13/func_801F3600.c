#include "area198_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3600(void) {
    u8 flags;
    /* FAKE: retail's 0x20 frame has an 8-byte slot that no local explains; pure C gives 0x18. */
    FAKE_STACK_PADS(u8, 8);

    if ((g_FrameCount & 7) == 0) {
        if (g_ScriptVars[0] >= 3) {
            flags = ((PartyMember*)g_Task)->param.unk_0B;
            if ((flags & 7) == 0) {
                SND_PlayCue(0);
            }
            func_801F36B4();
            if (g_ScriptVars[0] >= 4) {
                func_801F36B4();
            }
        }
    }
    g_ScriptState->cursor -= 2;
}
#else
INCLUDE_ASM(func_801F3600);
#endif
