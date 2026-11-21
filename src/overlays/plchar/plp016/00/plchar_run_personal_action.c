#include "plp016_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_RunPersonalAction.h"

#include "overlays/plchar/shared/PlChar_AdvancePaletteScript.h"

#include "overlays/plchar/shared/PlChar_StartFacingScript.h"

#include "overlays/plchar/shared/PlChar_ClearSlotRefIfUnused.h"

MATCH s32 func_801CFD24(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(PlChar_SpawnLinkedActor);
}
