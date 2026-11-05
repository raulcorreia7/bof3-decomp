/* Runs one frame of the spawn work: advances the frame counter at g_Task
 * +0x06 and claims a spawn slot every fourth frame, runs the per-image spawn
 * step (AREA_SPAWN_TICK) and the slot pass, then decrements the timer at
 * g_Task +0x09. When the timer reaches zero the pending spawn is installed:
 * the work coordinates at +0x64/+0x68/+0x6C move to +0x18/+0x1C/gravity, the
 * velocity cells +0x0C/+0x10 take -0x1000/-0x400, and the spawn index at +0x01
 * advances. One definition shared by the world area overlays; the spawn step is
 * a named setting in each member's image header. Every change here must verify
 * every member address.
 */
/* func_801F3AA8 (area098/13), func_801F3598 (area188/13) */
MATCH void Area_AdvanceSpawnTimer(void) {
    u8 temp_v0;
    u8 temp_v1;

    temp_v1        = g_Task->unk_06;
    g_Task->unk_06 = temp_v1 + 1;
    if (!(temp_v1 & 3)) {
        Area_ClaimSpawnSlot();
    }
    AREA_SPAWN_TICK();
    Area_StepSpawnSlots();
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        s32 x;
        s32 y;
        s32 z;
        u8  t;

        x          = g_Task->unk_64;
        y          = g_Task->unk_68;
        g_Task->vx = -0x1000;
        g_Task->vy = -0x400;
        ORDER_FENCE(); /* FAKE: the order fence keeps the unk_01/unk_6C loads below the constant stores. */
        t               = g_Task->mode;
        z               = g_Task->unk_6C;
        t               = t + 1;
        g_Task->unk_18  = x;
        g_Task->unk_1C  = y;
        g_Task->gravity = z;
        ORDER_FENCE(); /* FAKE: the order fence keeps the byte store last in retail's schedule. */
        g_Task->mode = t;
    }
}
