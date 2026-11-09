#include "battle_03.h"

/* advances the local battle state byte after refreshing the local and global battle substates. */
MATCH void func_801DF3B8(void) {
    PartyMember* work;

    func_801DEFE4();
    func_801DEDE4();
    work = g_Task;
    work->header.mode += 1;
}
