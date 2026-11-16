#include "area/effects.h"

u32 MATH_AverageAngle(u16 a, u16 b);

/* Link directions follow the nodes; the shifted offset keeps the chain pointer first in the add. */
#define CHAIN_DIR(chain, i) (*(u16*)((u8*)(chain) + ((i) << 1) + sizeof((chain)->node)))

/* func_801F8D98 */
/* Chain_Update (func_801F88B8 in scena07, func_801F8D98 in scena08, func_801F2F28 in area088): shifts the node history, puts the task position first, projects every node to the screen and sets the node angles from the neighbour directions. Every change must verify every member. */
MATCH void Chain_Update(void* table) {
    Chain* chain;
    s8     i;
    s8     j;
    s32    prev;
    u16    size[2];
    u16    scale[2];
    MATRIX camera;

    chain = table;
    for (i = 30; i >= 0; i--) {
        chain->node[i + 1] = chain->node[i];
    }
    chain->node[0].pos[0] = g_Task->pos.x.fixed;
    chain->node[0].pos[1] = g_Task->pos.y.fixed;
    chain->node[0].pos[2] = g_Task->pos.z.fixed;
    Area_SetCameraMatrix(&camera);
    for (i = 0; i < 32; i++) {
        Area_ProjectPoint(chain->node[i].pos, (DVECTOR*)chain->node[i].screen);
        size[0] = size[1] = chain->size;
        Game_ProjectWorldPoint(&chain->node[i], size, scale);
        chain->node[i].size = scale[0];
    }
    for (i = 0; i < 31; i++) {
        scale[0] = chain->node[i].screen[0] - chain->node[i + 1].screen[0];
        scale[1] = chain->node[i].screen[1] - chain->node[i + 1].screen[1];
        if ((s16)scale[0] != 0 || (s16)scale[1] != 0) {
            CHAIN_DIR(chain, i) = ratan2((s16)scale[1], (s16)scale[0]);
        } else {
            CHAIN_DIR(chain, i) = 0x1000;
        }
    }
    for (i = 0; i < 31; i++) {
        if (CHAIN_DIR(chain, i) != 0x1000) {
            continue;
        }
        for (j = i + 1; j < 31; j++) {
            if (CHAIN_DIR(chain, j) != 0x1000) {
                CHAIN_DIR(chain, i) = CHAIN_DIR(chain, j);
                goto next;
            }
        }
        for (j = 0; j < i; j++) {
            if (CHAIN_DIR(chain, j) != 0x1000) {
                CHAIN_DIR(chain, i) = CHAIN_DIR(chain, j);
                goto next;
            }
        }
        CHAIN_DIR(chain, j) = 0;
    next:;
    }
    chain->node[0].angle = CHAIN_DIR(chain, 0);
    for (i = 1; i < 31; i++) {
        prev                 = i - 1;
        chain->node[i].angle = MATH_AverageAngle(CHAIN_DIR(chain, prev), CHAIN_DIR(chain, i));
    }
    chain->node[31].angle = CHAIN_DIR(chain, 30);
}
