#include "game_00.h"

MATCH void func_8019C910(void) {
    if (Actor_StepAnimOnce() != 0u) {
        Actor_Clear();
        return;
    }
    func_8014D290();
}
