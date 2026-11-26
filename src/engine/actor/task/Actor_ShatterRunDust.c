#include "engine/game/00/game_00.h"

typedef struct ShatterDust {
    s8  brightness;
    s8  pad_01;
    s16 size;
} ShatterDust;

typedef struct ShatterPuff {
    VECTOR pos;
    VECTOR vel;
} ShatterPuff;

/* func_8019DC6C */
/* Moves and draws the eight dust puffs, growing them first and then fading them. */
MATCH void Actor_ShatterRunDust(void) {
    u8           scratch[32];
    ShatterPuff* rec;
    ShatterDust* state;
    s32          i;

    Camera_SetMatrix(scratch);
    state = MEM_PTR(ShatterDust, 0x800E4D40u);
    rec   = MEM_PTR(ShatterPuff, 0x800E4D44u);
    i     = 0;
    do {
        Actor_ShatterDrawPuff((s32*)rec, state->size, state->brightness);
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
        state->size += 0x80;
    } else {
        state->brightness -= 5;
    }
}
