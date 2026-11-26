/* Runs one frame of the spawn work: advances the frame counter at g_Self +0x06 and claims a spawn slot every fourth frame, runs the per-image spawn step (AREA_SPAWN_TICK) and the slot pass, then decrements the timer at g_Self +0x09. When the timer reaches zero the pending spawn is installed: the work coordinates at +0x64/+0x68/+0x6C move to +0x18/+0x1C/gravity, the velocity cells +0x0C/+0x10 take -0x1000/-0x400, and the spawn index at +0x01 advances. The spawn step is a named setting in each member's image header. */
/* func_801F3AA8 (area098/13), func_801F3598 (area188/13) */
MATCH void Area_UpdateSpawn(void) {
    Actor* work;
    u8     timer;
    u8     frame;

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
        work          = SELF(Actor);
        work->vx      = -0x1000;
        work->vy      = -0x400;
        work->unk_18  = work->angle_x;
        work->unk_1C  = work->angle_y;
        work->gravity = work->angle_z;
        work->header.mode++;
    }
}
