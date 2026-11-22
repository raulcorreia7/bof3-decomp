#include "area103_13.h"

MATCH void func_801F2C48(void) {
    func_801F349C();
    g_Task->timer  = 128;
    g_Task->unk_0A = 0;
    g_Task->header.mode++;
    SND_SEPlay(512);
    SND_SEPlay(522);
}
