#include "boss055_16.h"

MATCH void func_800C2AA8(void) {
    Boss055Scripts scripts;

    scripts = D_800C181C;
    if (D_801EB4E0->word_08.byte.unk_0B != 0) {
        Actor_SelectScript(scripts.byte[D_801463BE]);
    }
    func_801E30F8();
    Area_AddActor();
    func_800C3284();
}
