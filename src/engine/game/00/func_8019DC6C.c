#include "game_00.h"

typedef struct GameSpawnState {
    s8  count_00;
    s8  pad_01;
    s16 offset_02;
} GameSpawnState;

typedef struct GameSpawn {
    s32 x_00;
    s32 y_04;
    s32 z_08;
    s32 pad_0C;
    s32 vx_10;
    s32 vy_14;
    s32 vz_18;
    s32 pad_1C;
} GameSpawn;

MATCH void func_8019DC6C(void) {
    u8               scratch[32];
    GameSpawn* rec;
    GameSpawnState*  state;
    s32              i;

    Area_SetCameraMatrix(scratch);
    state = MEM_PTR(GameSpawnState, 0x800E4D40u);
    rec   = MEM_PTR(GameSpawn, 0x800E4D44u);
    i     = 0;
    do {
        func_8019DAA0((s32*)rec, state->offset_02, state->count_00);
        if (g_Task->timer >= 12u) {
            rec->x_00 += rec->vx_10 * 2;
            rec->y_04 += rec->vy_14 * 2;
            rec->z_08 += rec->vz_18 * 2;
        } else {
            rec->x_00 += rec->vx_10;
            rec->y_04 += rec->vy_14;
            rec->z_08 += rec->vz_18;
        }
        rec += 1;
        i++;
    } while ((i & BYTE_MASK) < 8u);
    if (g_Task->timer >= 12u) {
        state->offset_02 += 0x80;
    } else {
        state->count_00 -= 5;
    }
}
