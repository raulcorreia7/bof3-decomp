#include "boss055_16.h"

MATCH void func_800C2948(void) {
    Boss055Scripts scripts;

    scripts = D_800C1810;
    if (D_801EB4E0->unk_0B != 0) {
        Actor_SelectScript(scripts.byte[D_801463BE]);
    }
    func_801E30F8();
    Area_AddActor();
    func_800C3284();
}
