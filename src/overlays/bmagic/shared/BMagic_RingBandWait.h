/* Ring band mode 0: counts the start delay (byte 0x09) down; at zero copies the position of the task, sets the radius step to BMAGIC_RING_BAND_RADIUS, clears the wave height and phase and advances header.mode. */
/* func_801EEFFC (magic055), func_801EEFFC (magic091) */
MATCH void BMagic_RingBandWait(void) {
    u8           delay;
    PartyMember* src;
    PartyMember* work;

    delay                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = delay;
    if (delay == 0) {
        src                             = BATTLE_ACTIVE_WORK;
        work                            = TASK(PartyMember);
        work->pos.x                     = src->pos.x;
        work->pos.y                     = src->pos.y;
        work->pos.z                     = src->pos.z;
        work->unk_09                    = BMAGIC_RING_BAND_RADIUS;
        TASK(PartyMember)->timer        = 0;
        TASK(PartyMember)->param.unk_0B = 0;
        TASK(PartyMember)->header.mode  = TASK(PartyMember)->header.mode + 1;
    }
}
