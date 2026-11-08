#include "area049_13.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_8011700C(void) {
    /* Retail reads the handler record from the entry $v0; the uninitialised local reads it. */
    u8* entity;

    SYS_DISPATCH_TASK(D_8011818C, 1, entity);
}

MATCH void func_80117048(void) {
    ((Actor*)g_Task)->pos.x.fixed = TO_COORD(11) + COORD_HALF;
    ((Actor*)g_Task)->pos.y.fixed = TO_COORD(84) + COORD_HALF;
    ((Actor*)g_Task)->pos.z.fixed = TO_COORD(256);
    func_801172D0();
    ((Actor*)g_Task)->header.mode += 1;
}

MATCH void func_801170A4(void) {
    if (!(func_80117410() & BYTE_MASK)) {
        Actor_Clear();
    }
}

/* blocker: instruction scheduling; first diff: hoisted move for the zeroed channels before the tpage store. */
INCLUDE_ASM(func_801170D8);

INCLUDE_ASM(func_801172D0);

INCLUDE_ASM(func_80117410);

INCLUDE_ASM(func_80117514);

INCLUDE_ASM(func_8011759C);

MATCH void func_80117610(void) {
    SYS_DISPATCH_TASK(D_8011819C, 1, g_Task);
    func_80117900();
}

MATCH void func_8011765C(void) {
    g_GameFlags |= GAME_FLAG_MENU_LOCK;
    func_801172D0();
    ((Actor*)g_Task)->timer = 180;
    ((Actor*)g_Task)->header.mode += 1;
}

INCLUDE_ASM(func_801176B8);

INCLUDE_ASM(func_80117768);

INCLUDE_ASM(func_80117818);

INCLUDE_ASM(func_80117864);

#include "overlays/area/Area_FindFreeWorkRow.h"

INCLUDE_ASM(func_80117900);

MATCH void func_80117A30(void) {
    SYS_DISPATCH_BYTE(D_801181AC, TASK_BYTES[0x2]);
}

INCLUDE_ASM(func_80117A74);

INCLUDE_ASM(func_80117ACC);

INCLUDE_ASM(func_80117B60);

MATCH void func_80117BF4(void) {
    SYS_DISPATCH_BYTE(D_801181B4, TASK_BYTES[0x2]);
}

/* func_80117C38 */
MATCH void Scene_AdvanceState(void) {
    Scene_AdvanceActorState();
}

INCLUDE_ASM(func_80117C58);

MATCH void func_80117DF0(void) {
    if (!(g_FrameCount & 1)) {
        ((Actor*)g_Task)->timer += 1;
    }
    if (((Actor*)g_Task)->timer >= 128U) {
        Actor_Clear();
    }
    func_80117E78(128 - ((Actor*)g_Task)->timer, 0);
}

INCLUDE_ASM(func_80117E78);
