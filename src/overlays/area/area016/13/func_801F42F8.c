#include "area016_13.h"

MATCH void func_801F42F8(void) {
    u8**   slots;
    Actor* scratch;
    u16    value;
    u8*    cell;
    u16    y;

    Area_FindSceneRecord(0x46);

    slots             = SP_PTR(u8*, 0u);
    slots[0x11][0x48] = 0;
    slots             = SP_PTR(u8*, 0u);
    slots[0x11][0x24] = 0;
    slots             = SP_PTR(u8*, 0u);
    slots[0x11][0x29] = 5;

    slots                = SP_PTR(u8*, 0u);
    scratch              = (Actor*)slots[0x11];
    scratch->vx          = (s16)D_801F51B8[scratch->direction_08].x;
    scratch->vy          = (s16)D_801F51B8[scratch->direction_08].y;
    scratch->pos.x.fixed = D_80145EC4[0];
    scratch->pos.y.fixed = D_80145EC4[1];

    if (scratch->unk_06 != 0) {
        COORD_INT(scratch->pos.x) -= (s32)(D_801F51B8[scratch->direction_08].x << 16) >> 29;
        value = COORD_INT(scratch->pos.y) - ((s32)(D_801F51B8[scratch->direction_08].y << 16) >> 29);
        COORD_INT(scratch->pos.y) = value;
        if (scratch->unk_06 == 1) {
            if (scratch->vx == 0) {
                COORD_INT(scratch->pos.x) += 2;
            } else {
                COORD_INT(scratch->pos.y) = value + 2;
            }
        } else {
            if (scratch->vx == 0) {
                COORD_INT(scratch->pos.x) -= 2;
            } else {
                COORD_INT(scratch->pos.y) = value - 2;
            }
        }
    }

    slots   = SP_PTR(u8*, 0u);
    scratch = (Actor*)slots[0x11];
    COORD_INT(scratch->pos.x) -= (s32)(D_801F51B8[scratch->direction_08].x << 16) >> 25;
    y                         = COORD_INT(scratch->pos.y) - ((s32)(D_801F51B8[scratch->direction_08].y << 16) >> 25);
    scratch->unk_0B           = 0;
    slots                     = SP_PTR(u8*, 0u);
    cell                      = slots[0x11];
    COORD_INT(scratch->pos.y) = y;
    cell[1] += 1;

    slots = SP_PTR(u8*, 0u);
    Actor_SelectScript(D_801F51C8[slots[0x11][8] * 2]);

    slots             = SP_PTR(u8*, 0u);
    slots[0x11][0x2A] = D_801F51C9[slots[0x11][8] * 2];
    func_8014D290();
}
