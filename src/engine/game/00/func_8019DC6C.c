#include "game_00.h"

typedef struct GameSpawnState {
    s8  count;
    s8  pad_01;
    s16 offset;
} GameSpawnState;

typedef struct GameSpawn {
    VECTOR pos;
    VECTOR vel;
} GameSpawn;

MATCH void func_8019DC6C(void) {
    u8              scratch[32];
    GameSpawn*      rec;
    GameSpawnState* state;
    s32             i;

    Camera_SetMatrix(scratch);
    state = MEM_PTR(GameSpawnState, 0x800E4D40u);
    rec   = MEM_PTR(GameSpawn, 0x800E4D44u);
    i     = 0;
    do {
        func_8019DAA0((s32*)rec, state->offset, state->count);
        if (TASK(Actor)->timer >= 12u) {
            rec->pos.vx += rec->vel.vx * 2;
            rec->pos.vy += rec->vel.vy * 2;
            rec->pos.vz += rec->vel.vz * 2;
        } else {
            rec->pos.vx += rec->vel.vx;
            rec->pos.vy += rec->vel.vy;
            rec->pos.vz += rec->vel.vz;
        }
        rec += 1;
        i++;
    } while ((i & BYTE_MASK) < 8u);
    if (TASK(Actor)->timer >= 12u) {
        state->offset += 0x80;
    } else {
        state->count -= 5;
    }
}
