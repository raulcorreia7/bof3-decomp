#include "engine/game/00/game_00.h"

/* Opcodes 0xB0 to 0xBE of the actor script: sound. */
typedef enum ActorScriptSound {
    ACTOR_SCRIPT_SOUND_PLAY_SE           = 0xB0, /* args: [id]; SND_SEPlay */
    ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_1    = 0xB1, /* args: [id]; SND_SEPlay of id | 0x100 */
    ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_2    = 0xB2, /* args: [id]; SND_SEPlay of id | 0x200 */
    ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_3    = 0xB3, /* args: [id]; SND_SEPlay of id | 0x300 */
    ACTOR_SCRIPT_SOUND_PLAY_BGM          = 0xB4, /* args: [id]; SND_BGMPlay */
    ACTOR_SCRIPT_SOUND_FADE_OUT_BGM      = 0xB5, /* args: [id]; SND_BGMFadeOut */
    ACTOR_SCRIPT_SOUND_PLAY_SEQUENCE     = 0xB8, /* args: [a] [b] [c]; SND_SeqPlay */
    ACTOR_SCRIPT_SOUND_STOP_SEQUENCE     = 0xB9, /* args: [a] [b]; SND_SeqStop */
    ACTOR_SCRIPT_SOUND_FADE_IN_SEQUENCE  = 0xBA, /* args: [a] [b] [c] [d]; SND_SeqFadeIn */
    ACTOR_SCRIPT_SOUND_START_DECRESCENDO = 0xBB, /* args: [a] [b] [c] [d]; SND_StartDecrescendo */
    ACTOR_SCRIPT_SOUND_QUEUE_SE_VOLUME   = 0xBC, /* args: [se_u16] [a] [b]; SND_SEQueueVolume */
    ACTOR_SCRIPT_SOUND_PLAY_CUE          = 0xBD, /* args: [cue_u16] [index]; func_8015D820 */
    ACTOR_SCRIPT_SOUND_START_BGM         = 0xBE, /* args: [id]; SND_BGMStart */
} ActorScriptSound;

/* func_801A96E4 */
/* Runs one sound opcode. */
MATCH void Script_OpsRunSound(ScriptState* state, u8* base) {
    switch (*(base + state->cursor)) {
        case ACTOR_SCRIPT_SOUND_PLAY_SE:
            SND_SEPlay(*(base + state->cursor + 1));
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_1:
            SND_SEPlay(*(base + state->cursor + 1) | 0x100);
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_2:
            SND_SEPlay(*(base + state->cursor + 1) | 0x200);
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_SE_PAGE_3:
            SND_SEPlay(*(base + state->cursor + 1) | 0x300);
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_BGM:
            SND_BGMPlay(*(base + state->cursor + 1), 0x64, 8);
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_FADE_OUT_BGM:
            SND_BGMFadeOut(*(base + state->cursor + 1), 0x64, 8);
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_SEQUENCE:
            SND_SeqPlay(*(base + state->cursor + 1), *(base + state->cursor + 2), *(base + state->cursor + 3), *(base + state->cursor + 3));
            state->cursor += 3;
            break;
        case ACTOR_SCRIPT_SOUND_STOP_SEQUENCE:
            SND_SeqStop(*(base + state->cursor + 1), *(base + state->cursor + 2));
            state->cursor += 2;
            break;
        case ACTOR_SCRIPT_SOUND_FADE_IN_SEQUENCE:
            SND_SeqFadeIn(*(base + state->cursor + 1), *(base + state->cursor + 2), *(base + state->cursor + 3), *(base + state->cursor + 4));
            state->cursor += 4;
            break;
        case ACTOR_SCRIPT_SOUND_START_DECRESCENDO:
            SND_StartDecrescendo(*(base + state->cursor + 1), *(base + state->cursor + 2), *(base + state->cursor + 3), *(base + state->cursor + 4));
            state->cursor += 4;
            break;
        case ACTOR_SCRIPT_SOUND_QUEUE_SE_VOLUME:
            SND_SEQueueVolume(*(base + state->cursor + 2) | (*(base + state->cursor + 1) << 8), *(base + state->cursor + 3), *(base + state->cursor + 4));
            state->cursor += 4;
            break;
        case ACTOR_SCRIPT_SOUND_PLAY_CUE:
            Actor_PlayCueByDistance(*(base + state->cursor + 2) | (*(base + state->cursor + 1) << 8), *(base + state->cursor + 3));
            state->cursor += 3;
            break;
        case ACTOR_SCRIPT_SOUND_START_BGM:
            SND_BGMStart(*(base + state->cursor + 1), 0x64, 8);
            state->cursor += 1;
            break;
        default:
            break;
    }
}
