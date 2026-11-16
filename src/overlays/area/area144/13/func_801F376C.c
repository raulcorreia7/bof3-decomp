#include "area144_13.h"

MATCH void func_801F376C(u8 from, u8 to, u8 dest) {
    D_801F3D80[dest].vx = (D_801F3D80[from].vx + D_801F3D80[to].vx) >> 1;
    D_801F3D80[dest].vy = (D_801F3D80[from].vy + D_801F3D80[to].vy) >> 1;
    D_801F3D80[dest].vz = (D_801F3D80[from].vz + D_801F3D80[to].vz) >> 1;
}
