#include "area086_13.h"
#include "area/spad.h"

extern u8  D_801F3664[];
extern u16 D_801F3668[];

MATCH void func_801F2C48(void) {
    COORD_FRAC(g_Task->pos.x) = D_801F3664[COORD_INT(g_Task->pos.x)];
    COORD_INT(g_Task->pos.z)  = D_801F3668[COORD_INT(g_Task->pos.y)];
    g_Task->header.step++;
    func_801F2DE8();
    func_801F3070();
}
