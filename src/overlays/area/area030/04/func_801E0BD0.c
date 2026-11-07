#include "area030_04.h"

/* Runs the AREA030 per-frame update chain. */
MATCH void func_801E0BD0(void) {
    func_80199440();
    Fishing_UpdateFish();
    Area_StepCamera();
    func_801BDAB8();
    func_801E09B4();
    Actor_DispatchAll();
    Area_DrawScene();
}
