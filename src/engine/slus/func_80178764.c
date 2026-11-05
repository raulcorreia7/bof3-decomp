#include "engine/slus/slus.h"
/* blocker: this compiler folds constant returns to `move v0,zero`; retail loads the immediate. first diff: li v0,0 at 0x80178768. */
INCLUDE_ASM(func_80178764);
