/* The step after Actor_SpawnRandomGroup: gives the spawned actor a velocity from
 * its facing, backs its position off along it and selects the walk script for
 * that facing. Members: Actor_StartWalking in area016, 033, 045, 065, 087,
 * 088, 151 and 152. Every change here must verify every member. */

/* `steps` is the image's table of velocity per facing; `scripts` and `script_slots` are
 * the first and second bytes of its script pairs per facing. A bare statement macro, used
 * as a member's whole body after it declares `u8** slots`, `Actor* scratch`, `u16 value`,
 * `u8* cell` and `u16 y`: an inline grows the stack frame by 16 bytes and a do/while
 * block by 8. */
#define ACTOR_START_WALKING(steps, scripts, script_slots)                                                              \
    Area_FindSceneRecord(0x46);                                                                                        \
                                                                                                                       \
    slots             = SP_PTR(u8*, 0u);                                                                               \
    slots[0x11][0x48] = 0;                                                                                             \
    slots             = SP_PTR(u8*, 0u);                                                                               \
    slots[0x11][0x24] = 0;                                                                                             \
    slots             = SP_PTR(u8*, 0u);                                                                               \
    slots[0x11][0x29] = 5;                                                                                             \
                                                                                                                       \
    slots                = SP_PTR(u8*, 0u);                                                                            \
    scratch              = (Actor*)slots[0x11];                                                                        \
    scratch->vx          = (s16)(steps)[scratch->direction_08].x;                                                      \
    scratch->vy          = (s16)(steps)[scratch->direction_08].y;                                                      \
    scratch->pos.x.fixed = D_80145EC4[0];                                                                              \
    scratch->pos.y.fixed = D_80145EC4[1];                                                                              \
                                                                                                                       \
    if (scratch->unk_06 != 0) {                                                                                        \
        COORD_INT(scratch->pos.x) -= (s32)((steps)[scratch->direction_08].x << 16) >> 29;                              \
        value                     = COORD_INT(scratch->pos.y) - ((s32)((steps)[scratch->direction_08].y << 16) >> 29); \
        COORD_INT(scratch->pos.y) = value;                                                                             \
        if (scratch->unk_06 == 1) {                                                                                    \
            if (scratch->vx == 0) {                                                                                    \
                COORD_INT(scratch->pos.x) += 2;                                                                        \
            } else {                                                                                                   \
                COORD_INT(scratch->pos.y) = value + 2;                                                                 \
            }                                                                                                          \
        } else {                                                                                                       \
            if (scratch->vx == 0) {                                                                                    \
                COORD_INT(scratch->pos.x) -= 2;                                                                        \
            } else {                                                                                                   \
                COORD_INT(scratch->pos.y) = value - 2;                                                                 \
            }                                                                                                          \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    slots   = SP_PTR(u8*, 0u);                                                                                         \
    scratch = (Actor*)slots[0x11];                                                                                     \
    COORD_INT(scratch->pos.x) -= (s32)((steps)[scratch->direction_08].x << 16) >> 25;                                  \
    y                         = COORD_INT(scratch->pos.y) - ((s32)((steps)[scratch->direction_08].y << 16) >> 25);     \
    scratch->param.unk_0B     = 0;                                                                                     \
    slots                     = SP_PTR(u8*, 0u);                                                                       \
    cell                      = slots[0x11];                                                                           \
    COORD_INT(scratch->pos.y) = y;                                                                                     \
    cell[1] += 1;                                                                                                      \
                                                                                                                       \
    slots = SP_PTR(u8*, 0u);                                                                                           \
    Actor_SelectScript((scripts)[slots[0x11][8] * 2]);                                                                 \
                                                                                                                       \
    slots             = SP_PTR(u8*, 0u);                                                                               \
    slots[0x11][0x2A] = (script_slots)[slots[0x11][8] * 2];                                                            \
    func_8014D290();
