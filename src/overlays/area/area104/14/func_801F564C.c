#include "area104_14.h"
#include "scenario/state.h"

extern u8 D_80146871;
extern u8 D_80145E9A;
extern u8 D_80145E9B;

void func_801F5418(s32 value, s32 flag);
void func_801F555C(s16 x, s16 y, u8 row);

MATCH void func_801F564C(void) {
    s32 value;
    s32 flag;

    if (g_AreaDrawFlags & 0x1B) {
        if (!(D_80146871 & 0x40)) {
            if (D_80145E9A == 0) {
                func_801F555C(0xDC, 0x10, 0);
                func_801F5418(0x40, 0);
                flag  = 1;
                value = 0x40;
                value -= D_80145E9B;
                value &= 0xFF;
            } else {
                if (g_FrameCount & 2) {
                    func_801F555C(0xDC, 0x10, 1);
                } else {
                    func_801F555C(0xDC, 0x10, 2);
                }
                value = 0x40;
                flag  = 0;
            }
        } else {
            func_801F555C(0xDC, 0x10, 0);
            func_801F5418(0x40, 0);
            value = 0x40;
            flag  = 1;
        }
        func_801F5418(value, flag);
    }
}
