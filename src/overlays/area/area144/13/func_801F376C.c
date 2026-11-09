#include "area144_13.h"

MATCH void func_801F376C(u8 from, u8 to, u8 dest) {
    D_801F3D80[dest].x = (D_801F3D80[from].x + D_801F3D80[to].x) >> 1;
    D_801F3D80[dest].y = (D_801F3D80[from].y + D_801F3D80[to].y) >> 1;
    D_801F3D80[dest].z = (D_801F3D80[from].z + D_801F3D80[to].z) >> 1;
}
