#include "area172_13.h"

MATCH void func_801F342C(void) {
    u8*    cell_1;
    u8*    cell_2;
    Actor* scratch;
    Actor* check;

    scratch = (Actor*)g_SpadWork;
    scratch->unk_0C += 8;
    func_801F4060(scratch->unk_0C);
    /* FAKE: retail splits each re-read across a cell copy so the row stays
     * in one register. */
    cell_1  = g_SpadWork;
    scratch = (Actor*)cell_1;
    scratch->unk_09--;
    if (scratch->unk_09 != 0) {
        return;
    }
    cell_2          = g_SpadWork;
    scratch         = (Actor*)cell_2;
    scratch->unk_32 = 0x140;
    scratch->unk_09 = 0x10;
    check           = (Actor*)g_SpadWork;
    scratch->unk_0C = 0x100;
    scratch->unk_10 = 0x100;
    check->unk_01++;
    g_AreaDrawFlags = 0x1F;
}
