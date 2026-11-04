#include "area088_13.h"

MATCH void func_801F2E04(void) {
    func_801F2F28(MEM_PTR(u8, AREA_WORK_WINDOW));
    func_801F3258(MEM_PTR(u8, AREA_WORK_WINDOW));
    D_800E4B3E -= 6;
    if (--g_SpadWork->unk_09 == 0) {
        g_SpadWork->unk_01++;
    }
}
