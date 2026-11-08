#include "boss055_16.h"

MATCH void func_800C2340(u8 arg0, u8 index, u8 value) {
    func_800C238C(arg0, index);
    TASK_BYTES[0xB] = 1;
    D_801463BE      = value;
}
