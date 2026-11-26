#include "boss055_16.h"

MATCH void func_800C204C(void) {
    u8 result;

    result = func_801E3160();
    if (result != 0u) {
        SELF(EnemyBattler)->header.mode++;
        SELF(EnemyBattler)->header.step = 0u;
    }
}
