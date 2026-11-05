/* Builds a GTE vertex from the party focus position, projects it with
 * RotTransPers into the ordering-table screen buffer, stores the depth result
 * at the work offset 0x60 and the screen x and y at offsets 0x2E and 0x30,
 * resets the timer at byte 0x09 and advances the handler index at byte 0x01.
 * One definition shared by the area and scenario overlays; every change here
 * must verify every member.
 */
/* func_801F2C48 (area032), func_801F8640 (scena03) */
MATCH void Actor_ProjectFocusAndStep(void) {
    SVECTOR* vertex;
    u16*     screen;
    long     depth;
    long     flag;
    long     result;
    u16      other;
    u8**     slots;
    u8*      work;
    u8*      item;

    vertex                 = D_1F800014;
    screen                 = D_1F800034;
    vertex->vx             = (s16)((D_80145EC4 >> 9) - 0x4000);
    SP_REF(s16, 0x16)      = (s16)((D_80145EC8 >> 9) - 0x4000);
    SP_REF(s16, 0x18)      = (s16)((-D_80145ECE) / 2);
    result                 = RotTransPers(vertex, (long*)screen, &depth, &flag);
    slots                  = SP_PTR(u8*, 0u);
    work                   = slots[0x11];
    FIELD(s32, work, 0x60) = result;
    FIELD(u16, work, 0x2E) = screen[0];
    other                  = SP_REF(u16, 0x36);
    work[9]                = 0;
    slots                  = SP_PTR(u8*, 0u);
    item                   = slots[0x11];
    FIELD(u16, work, 0x30) = other;
    item[1] += 1;
}
