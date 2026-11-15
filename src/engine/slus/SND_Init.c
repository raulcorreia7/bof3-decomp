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
    g_SndVabIds[1]             = 1;
    g_SndVabIds[2]             = 2;
    g_SndVabIds[3]             = 3;
    g_SndVabIds[4]             = 4;
    g_SndVabIds[5]             = 5;
    g_SndVabIds[6]             = 6;
    g_SndVabIds[0]             = 0;
    g_SelectionEffectVoices[0] = -1;
    g_SelectionEffectVoices[1] = -1;
    g_SelectionEffectVoices[2] = -1;
    g_SelectionEffectVoices[3] = -1;
    g_SelectionEffectVoices[4] = -1;
    g_SelectionEffectVoices[5] = -1;
    g_SelectionEffectVoices[6] = -1;
    SND_InstallSequenceFuncs();
    D_8018B410                 = 0xFFFF;
    D_8018B414                 = 3;
    D_80148A04                 = 0x7FF;
    D_80148A06                 = 0x7FF;
    D_8018B418                 = 0x7FF;
    D_8018B41A                 = 0x7FF;
    /* FAKE: the volatile store keeps D_8018B414 ahead of the voice word. */
    VOL(u32, D_8018B450.voice) = (SPU_16CH | SPU_17CH | SPU_18CH | SPU_19CH | SPU_20CH | SPU_21CH | SPU_22CH | SPU_23CH);
    D_8018B454                 = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    D_80148A0C                 = 0x3FFF;
    D_80148A0E                 = 0x3FFF;
    D_8018B458                 = 0x3FFF;
    D_8018B45A                 = 0x3FFF;
    SpuSetVoiceAttr(&D_8018B450);
}
