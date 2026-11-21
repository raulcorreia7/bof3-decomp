#include "engine/game/00/game_00.h"

/* Opcodes 0xB0 to 0xBE of the actor script: sound. */
typedef enum ActorScriptSound {
    ACTOR_SCRIPT_SOUND_PLAY_SE           = 0xB0, /* args: [id]; SND_PlaySE */
    ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_1    = 0xB1, /* args: [id]; SND_PlaySE of id | 0x100 */
    ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_2    = 0xB2, /* args: [id]; SND_PlaySE of id | 0x200 */
    ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_3    = 0xB3, /* args: [id]; SND_PlaySE of id | 0x300 */
    ACTOR_SCRIPT_SOUND_PLAY_BGM          = 0xB4, /* args: [id]; SND_PlayBGM */
    ACTOR_SCRIPT_SOUND_FADE_OUT_BGM      = 0xB5, /* args: [id]; SND_FadeOutBGM */
    ACTOR_SCRIPT_SOUND_PLAY_SEQUENCE     = 0xB8, /* args: [a] [b] [c]; SND_PlaySequence */
    ACTOR_SCRIPT_SOUND_STOP_SEQUENCE     = 0xB9, /* args: [a] [b]; SND_StopSequence */
    ACTOR_SCRIPT_SOUND_FADE_IN_SEQUENCE  = 0xBA, /* args: [a] [b] [c] [d]; SND_FadeInSequence */
    ACTOR_SCRIPT_SOUND_START_DECRESCENDO = 0xBB, /* args: [a] [b] [c] [d]; SND_StartDecrescendo */
    ACTOR_SCRIPT_SOUND_QUEUE_SE_VOLUME   = 0xBC, /* args: [se_u16] [a] [b]; SND_QueueSeVolume */
    ACTOR_SCRIPT_SOUND_PLAY_CUE          = 0xBD, /* args: [cue_u16] [index]; func_8015D820 */
    ACTOR_SCRIPT_SOUND_START_BGM         = 0xBE, /* args: [id]; SND_StartBGM */
} ActorScriptSound;

/* func_801A96E4 */
/* Runs one sound opcode. */
MATCH void Script_RunSoundOps(ScriptState* state, u8* base) {
    switch (*(base + state->cursor)) {
        case ACTOR_SCRIPT_SOUND_PLAY_SE:
            SND_PlaySE(*(base + state->cursor + 1));
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_1:
            SND_PlaySE(*(base + state->cursor + 1) | 0x100);
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_2:
            SND_PlaySE(*(base + state->cursor + 1) | 0x200);
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_3:
            SND_PlaySE(*(base + state->cursor + 1) | 0x300);
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_BGM:
            SND_PlayBGM(*(base + state->cursor + 1), 0x64, 8);
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_FADE_OUT_BGM:
            SND_FadeOutBGM(*(base + state->cursor + 1), 0x64, 8);
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_SEQUENCE:
            SND_PlaySequence(*(base + state->cursor + 1), *(base + state->cursor + 2), *(base + state->cursor + 3), *(base + state->cursor + 3));
            state->cursor += 3;
            break;
        case ACTOR_SCRIPT_SOUND_STOP_SEQUENCE:
            SND_StopSequence(*(base + state->cursor + 1), *(base + state->cursor + 2));
            state->cursor += 2;
            break;
        case ACTOR_SCRIPT_SOUND_FADE_IN_SEQUENCE:
            SND_FadeInSequence(*(base + state->cursor + 1), *(base + state->cursor + 2), *(base + state->cursor + 3), *(base + state->cursor + 4));
            state->cursor += 4;
            break;
        case ACTOR_SCRIPT_SOUND_START_DECRESCENDO:
            SND_StartDecrescendo(*(base + state->cursor + 1), *(base + state->cursor + 2), *(base + state->cursor + 3), *(base + state->cursor + 4));
            state->cursor += 4;
            break;
        case ACTOR_SCRIPT_SOUND_QUEUE_SE_VOLUME:
            SND_QueueSeVolume(*(base + state->cursor + 2) | (*(base + state->cursor + 1) << 8), *(base + state->cursor + 3), *(base + state->cursor + 4));
            state->cursor += 4;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_CUE:
            Actor_PlayCueByDistance(*(base + state->cursor + 2) | (*(base + state->cursor + 1) << 8), *(base + state->cursor + 3));
            state->cursor += 3;
            break;
        case ACTOR_SCRIPT_SOUND_START_BGM:
            SND_StartBGM(*(base + state->cursor + 1), 0x64, 8);
            state->cursor += 1;
            break;
        default:
            break;
    }
}
