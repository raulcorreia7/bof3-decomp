#include "engine/slus/slus.h"

/* initializes the sound system: builds the SE table, starts the
 * ticker and reverb, opens the reserved voice and the seven SEP/VAB slots,
 * then seeds the reverb and voice parameter words.
 */
MATCH void SND_Init(void) {
    SsInit();
    SsSetTableSize((s8*)D_80148A50, 2, 4);
    SsSetTickMode(SS_TICK60);
    SsUtSetReverbType(SS_REV_TYPE_ROOM);
    SsUtReverbOn();
    SsSetAutoKeyOffMode(0);
    SsSetReservedVoice(0x10);
    D_80148FB1           = 1;
    D_80148FB2           = 2;
    D_80148FB3           = 3;
    D_80148FB4           = 4;
    D_80148FB5           = 5;
    D_80148FB6           = 6;
    D_80148FB0           = 0;
    *g_SelectionFxVoices = -1;
    D_80148FC1           = -1;
    D_80148FC2           = -1;
    D_80148FC3           = -1;
    D_80148FC4           = -1;
    D_80148FC5           = -1;
    D_80148FC6           = -1;
    SND_InstallSequenceFuncs();
    D_8018B410 = 0xFFFF;
    D_8018B414 = 3;
    D_80148A04 = 0x7FF;
    D_80148A06 = 0x7FF;
    D_8018B418 = 0x7FF;
    D_8018B41A = 0x7FF;
    /* FAKE: the volatile store keeps D_8018B414 ahead of the voice word. */
    VOL(u32, D_8018B450.voice) =
        (SPU_16CH | SPU_17CH | SPU_18CH | SPU_19CH | SPU_20CH | SPU_21CH | SPU_22CH | SPU_23CH);
    D_8018B454 = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    D_80148A0C = 0x3FFF;
    D_80148A0E = 0x3FFF;
    D_8018B458 = 0x3FFF;
    D_8018B45A = 0x3FFF;
    SpuSetVoiceAttr(&D_8018B450);
}
