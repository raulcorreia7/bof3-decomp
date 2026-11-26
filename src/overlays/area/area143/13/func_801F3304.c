#include "area143_13.h"
#include "game/functions.h"

MATCH void func_801F3304(void) {
    s32 current;
    s32 height;
    s32 top;
    s32 value;
    s32 point1;
    s32 point2;
    s32 point3;
    s32 point4;
    s32 point5;
    s32 point6;
    s32 point7;
    s32 point8;

    current                  = SELF(Actor)->pos.z.fixed;
    height                   = current + 8;
    SELF(Actor)->pos.z.fixed = height;
    if (height < 0x100) {
        top = height;
    } else {
        top = 0x100;
    }

    point1 = current - 0x18;
    if (point1 < 0) {
        point1 = 0;
    }
    value = 0x100;
    if (point1 < 0x100) {
        value = point1;
    }
    point1 = value;
    point2 = current - 0x38;
    if (point2 < 0) {
        point2 = 0;
    }
    value = 0x100;
    if (point2 < 0x100) {
        value = point2;
    }
    point2 = value;
    point3 = current - 0x58;
    if (point3 < 0) {
        point3 = 0;
    }
    value = 0x100;
    if (point3 < 0x100) {
        value = point3;
    }
    point3 = value;
    point4 = current - 0x78;
    if (point4 < 0) {
        point4 = 0;
    }
    value = 0x100;
    if (point4 < 0x100) {
        value = point4;
    }
    point4 = value;
    point5 = current - 0x98;
    if (point5 < 0) {
        point5 = 0;
    }
    value = 0x100;
    if (point5 < 0x100) {
        value = point5;
    }
    point5 = value;
    point6 = SELF(Actor)->pos.z.fixed - 0xC0;
    if (point6 < 0) {
        point6 = 0;
    }
    value = 0x100;
    if (point6 < 0x100) {
        value = point6;
    }
    point6 = value;
    point7 = SELF(Actor)->pos.z.fixed - 0xE0;
    if (point7 < 0) {
        point7 = 0;
    }
    value = 0x100;
    if (point7 < 0x100) {
        value = point7;
    }
    point7 = value;
    point8 = SELF(Actor)->pos.z.fixed - 0x100;
    if (point8 < 0) {
        point8 = 0;
    }
    value = 0x100;
    if (point8 < 0x100) {
        value = point8;
    }
    point8 = value;

    func_801F3584(top, point1, 1);
    func_801F3584(point1, point2, 0);
    func_801F3584(point2, point3, 1);
    func_801F3584(point3, point4, 0);
    func_801F3584(point4, point5, 1);
    func_801F3584(point5, point6, 0);
    func_801F3584(point6, point7, 1);
    func_801F3584(point7, point8, 0);

    if (top >= 0x100 && SELF(Actor)->param.unk_0B == 0) {
        Area_CellSetPalette(0xB, 0x22);
        SELF(Actor)->param.unk_0B = 1;
    }
    if (point8 >= 0x100) {
        g_AreaSceneMode = 2;
        func_80196070();
    }
}
