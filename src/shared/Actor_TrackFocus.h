/* Builds a GTE vertex from the party focus position, projects it with RotTransPers into the ordering-table screen buffer, stores the depth result at the work offset 0x60 and the screen x and y at offsets 0x2E and 0x30, resets the timer at byte 0x09 and advances the handler index at byte 0x01. */
/* func_801F2C48 (area032), func_801F8640 (scena03) */
MATCH void Actor_TrackFocus(void) {
    SVECTOR* vertex;
    u16*     screen;
    long     depth;
    long     flag;
    long     result;
    u16      other;
    Actor*   work;
    Actor*   item;

    vertex                 = D_1F800014;
    screen                 = D_1F800034;
    vertex->vx             = (s16)((g_Game.members[0].pos.x.fixed >> 9) - 0x4000);
    SP_REF(s16, 0x16)      = (s16)((g_Game.members[0].pos.y.fixed >> 9) - 0x4000);
    SP_REF(s16, 0x18)      = (s16)((-COORD_INT(g_Game.members[0].pos.z)) / 2);
    result                 = RotTransPers(vertex, (long*)screen, &depth, &flag);
    work                   = g_Task;
    work->unk_60           = result;
    FIELD(u16, work, 0x2E) = screen[0];
    other                  = SP_REF(u16, 0x36);
    work->timer            = 0;
    item                   = g_Task;
    work->screen_y         = other;
    item->header.mode += 1;
}
