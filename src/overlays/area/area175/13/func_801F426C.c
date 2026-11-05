#include "area175_13.h"

MATCH void func_801F426C(void) {
    Actor* scratch;
    Actor* check;

    scratch = g_SpadWork;
    scratch->unk_0A--;
    if (scratch->unk_0A != 0) {
        check = g_SpadWork;
        check->x.fixed += D_801F5378[check->unk_0A & 0xF] << 11;
        check->y.fixed -= D_801F5378[check->unk_0A & 0xF] << 11;
        g_CurrentActor->unk_7E -= 2;
    } else {
        g_SpadWork->unk_04 = 0;
    }
}
