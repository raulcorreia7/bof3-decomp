/* Runs one frame of the spawn work: advances the frame counter at g_Self +0x06 and claims a spawn slot every fourth frame, runs the per-image spawn step (AREA_SPAWN_TICK) and the slot pass, then decrements the timer at g_Self +0x09. When the timer reaches zero the pending spawn is installed: the work coordinates at +0x64/+0x68/+0x6C move to +0x18/+0x1C/gravity, the velocity cells +0x0C/+0x10 take -0x1000/-0x400, and the spawn index at +0x01 advances. The spawn step is a named setting in each member's image header. */
/* func_801F3AA8 (area098/13), func_801F3598 (area188/13) */
MATCH void Area_UpdateSpawn(void) {
    u8 timer;
    u8 frame;

    frame               = SELF(Actor)->unk_06;
    SELF(Actor)->unk_06 = frame + 1;
    if (!(frame & 3)) {
        Area_ClaimSpawnSlot();
    }
    AREA_SPAWN_TICK();
    Area_UpdateSpawnSlots();
    timer              = SELF(Actor)->timer - 1;
    SELF(Actor)->timer = timer;
    if (!(timer & 0xFF)) {
        s32 x;
        s32 y;
        s32 z;
        u8  t;

        x               = SELF(Actor)->angle_x;
        y               = SELF(Actor)->angle_y;
        SELF(Actor)->vx = -0x1000;
        SELF(Actor)->vy = -0x400;
        FAKE_ORDER_FENCE(); /* FAKE: the order fence keeps the unk_01/angle_z loads below the constant stores. */
        t                    = SELF(Actor)->header.mode;
        z                    = SELF(Actor)->angle_z;
        t                    = t + 1;
        SELF(Actor)->unk_18  = x;
        SELF(Actor)->unk_1C  = y;
        SELF(Actor)->gravity = z;
        FAKE_ORDER_FENCE(); /* FAKE: the order fence keeps the byte store last in retail's schedule. */
        SELF(Actor)->header.mode = t;
    }
}
