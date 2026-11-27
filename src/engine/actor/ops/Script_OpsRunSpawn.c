#include "engine/game/00/game_00.h"

/* The retail caller loads the fifth argument with lh, so the declaration keeps
 * s16 although the definition names it u16; the low halfword is identical. */

/* func_801AB8B0 */
/* Runs one helper-spawn opcode. */
/* Opcodes 0x90 to 0x9F of the actor script: spawn a helper actor. */
typedef enum ActorScriptSpawn {
    ACTOR_SCRIPT_SPAWN_CLAIM_AT_SCREEN_FIRST = 0x90, /* args: [dx] [dy]; Actor_ClaimSlot at the screen position; 0x91 to 0x95 pick the next types */
    ACTOR_SCRIPT_SPAWN_AT_ACTOR_FIRST        = 0x98, /* args: [dx] [dy]; Actor_SpawnHelper at the actor; 0x99 to 0x9D pick the next types */
    ACTOR_SCRIPT_SPAWN_WAIT_ALIVE            = 0x9F, /* hold the cursor while the spawned actor is in use */
} ActorScriptSpawn;

MATCH s32 Script_OpsRunSpawn(ScriptState* state, u8* table, s32 value) {
    switch (table[state->cursor]) {
        case ACTOR_SCRIPT_SPAWN_CLAIM_AT_SCREEN_FIRST:
        case 0x91:
        case 0x92:
        case 0x93:
        case 0x94:
        case 0x95:
            SELF(Actor)->param.unk_0B =
                Actor_ClaimSlot(table[state->cursor] - 0x90, (s8)table[state->cursor + 1], (s8)table[state->cursor + 2], (s16)SELF(Actor)->screen_x, SELF(Actor)->screen_y);
            state->cursor += 2;
            break;
        case ACTOR_SCRIPT_SPAWN_AT_ACTOR_FIRST:
        case 0x99:
        case 0x9A:
        case 0x9B:
        case 0x9C:
        case 0x9D:
            SELF(Actor)->param.unk_0B = Actor_SpawnHelper(table[state->cursor] - 0x98, (s8)table[state->cursor + 1], (s8)table[state->cursor + 2], SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed,
                                                          SELF(Actor)->pos.z.fixed);
            state->cursor += 2;
            break;
        case ACTOR_SCRIPT_SPAWN_WAIT_ALIVE:
            if (ACTOR_IN_USE(g_SpawnedActors[SELF(Actor)->param.actor_slot])) {
                state->cursor -= 1;
            }
            break;
        default:
            break;
    }
    return value & BYTE_MASK;
}
