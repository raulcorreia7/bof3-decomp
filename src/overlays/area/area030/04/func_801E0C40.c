#include "area030_04.h"

/* Runs the AREA030 event step sequence. */

MATCH void func_801E0C40(void) {
    Area_UpdateCamera();
    func_801BDAB8();
    func_801E09B4();
    Actor_DispatchAll();
    Area_DrawScene();
}
