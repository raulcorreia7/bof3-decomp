#include "area030_04.h"

/* Runs the AREA030 event step sequence: scene update, effect
 * update, local state update, audio cue flush, and controller poll. */

MATCH void func_801E0C40(void) {
    Area_StepCamera();
    func_801BDAB8();
    func_801E09B4();
    Actor_DispatchAll();
    Area_DrawScene();
}
