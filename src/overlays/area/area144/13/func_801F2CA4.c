#include "area144_13.h"

MATCH void func_801F2CA4(void) {
    if (func_801F34FC() == 0) {
        func_801F30CC();
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
        SELF(Actor)->header.mode++;
    }
}
