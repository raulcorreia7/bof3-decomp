#include "plp349_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CF5EC[SELF(Actor)->header.step]();
}

MATCH void PlChar_StartTurnTeepo(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/shared/PlChar_RunStepScriptTeepo.h"

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CF5F8, 2, g_Self);
}

MATCH void func_801CE654(void) {
    SYS_DISPATCH_TASK(D_801CF600, 3, g_Self);
}

MATCH void func_801CE698(void) {
    u8 direction;

    direction = SELF(Actor)->direction;
    if (!(direction & 1)) {
        SELF(Actor)->direction = (direction - 1) & 7;
        if (!(func_801CF184() & 0xFF)) {
            SELF(Actor)->direction = (SELF(Actor)->direction + 2) & 7;
            if (!(func_801CF184() & 0xFF)) {
                SELF(Actor)->direction = (SELF(Actor)->direction - 2) & 7;
            }
        }
    }
    /* FAKE: retail reads SND_SEPlay as void(s32). */
    ((void (*)(s32))SND_SEPlay)(SELF(Actor)->unk_2C + 0x100);
    Script_Request((((s32)(SELF(Actor)->direction - 1) / 2) + 0x42) & 0xFF);
    SELF(Actor)->param.unk_0B = 0;
    SELF(Actor)->unk_06       = 0;
    SELF(Actor)->unk_0A       = 8;
    SELF(Actor)->unk_03       = 1;
}

#include "overlays/plchar/shared/PlChar_RunPersonalAction.h"

#include "overlays/plchar/shared/PlChar_AdvancePaletteScript.h"

#include "overlays/plchar/shared/PlChar_StartFacingScript.h"

#include "overlays/plchar/shared/PlChar_ClearSlotRefIfUnused.h"

MATCH s32 func_801CEC18(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(PlChar_SpawnLinkedActor);
}

/* func_801CEE24 */
#include "overlays/plchar/shared/PlChar_SpawnLinkedActor.h"

MATCH void func_801CEF10(void) {
    SYS_DISPATCH_TASK(D_801CF614, 3, g_Self);
}

MATCH void func_801CEF54(void) {
    /* FAKE: retail reads SND_SEPlay as void(s32). */
    ((void (*)(s32))SND_SEPlay)(SELF(Actor)->unk_2C + 0x100);
    Script_Request(((SELF(Actor)->direction - 1) / 2) + 0x42);
    SELF(Actor)->unk_0A = 8;
    SELF(Actor)->unk_03 = 1;
}

#include "overlays/plchar/shared/PlChar_UpdateLinkedFacing.h"

#include "overlays/plchar/shared/PlChar_ClearPanelModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801CF184);

MATCH void func_801CF328(void) {
    SYS_DISPATCH_TASK(D_801CF620, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CF534(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801CF544(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801CF554(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801CF564(void) {
    D_801CF62C[SELF(Actor)->unk_2C]();
}

MATCH void func_801CF5A8(void) {
    D_801CF638[SELF(Actor)->unk_2C]();
}
