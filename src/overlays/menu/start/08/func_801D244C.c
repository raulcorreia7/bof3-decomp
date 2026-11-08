#include "start_08.h"

extern u8 D_80148656; /* local: u8 read; a sibling copy is s8 */

MATCH void func_801D244C(void) {
    Menu_DrawClutStrip(D_80144953);
    func_801D29A4();
    D_80148656 = 0;
    D_80148654 = 8;
    D_80148651 += 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
}
