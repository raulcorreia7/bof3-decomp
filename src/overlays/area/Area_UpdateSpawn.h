/* Runs one frame of the spawn work. */
/* func_801F3AA8 (area098/13), func_801F3598 (area188/13) */
MATCH void Area_UpdateSpawn(void) {
    u8 timer;
    u8 frame;

    frame          = g_Task->unk_06;
    g_Task->unk_06 = frame + 1;
    if (!(frame & 3)) {
        Area_ClaimSpawnSlot();
    }
    AREA_SPAWN_TICK();
    Area_UpdateSpawnSlots();
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (!(timer & 0xFF)) {
        s32 x;
        s32 y;
        s32 z;
        u8  t;

        x          = g_Task->unk_64;
        y          = g_Task->unk_68;
        g_Task->vx = -0x1000;
        g_Task->vy = -0x400;
        FAKE_ORDER_FENCE(); /* FAKE: the order fence keeps the unk_01/unk_6C loads below the constant stores. */
        t               = g_Task->header.mode;
        z               = g_Task->unk_6C;
        t               = t + 1;
        g_Task->unk_18  = x;
        g_Task->unk_1C  = y;
        g_Task->gravity = z;
        FAKE_ORDER_FENCE(); /* FAKE: the order fence keeps the byte store last in retail's schedule. */
        g_Task->header.mode = t;
    }
}
