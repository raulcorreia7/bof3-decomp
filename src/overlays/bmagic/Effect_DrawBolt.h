/* Draws the lightning bolt of the effect as LINE_G2 segments: each segment swings by the effect ticker, its length and brightness flicker at random, and it goes into the depth cell of the effect's position. each image header defines BOLT_RADIUS, BOLT_FLICKER_MASK and BOLT_FLICKER_BASE and reads the scratch words as s32 (GAME_SCRATCH_BASE_WORD). */
/* func_801F043C (magic099), func_801EF9A4 (magic143) */
MATCH void Effect_DrawBolt(void) {
    LINE_G2* primitive;
    s32*     d;
    s32*     cell;
    s16*     vec;
    s16*     point;
    long     p;
    long     flag;
    s32      x;
    s32      y;
    s32      page;
    s32      i;

    d          = &D_1F800000;
    vec        = D_1F800014_HALF;
    d[0]       = BOLT_RADIUS;
    D_1F800004 = ((g_Task->param.unk_0B + 2) & 0xF) << 8;
    D_1F80000C = g_Task->timer;
    i          = 1;
    D_1F800008 = RANDOM_MASK(0x3F);
    vec[0]     = 0;
    D_1F800016 = FIXED_MUL(rsin(D_1F800004), d[0]);
    D_1F800018 = 0;
    if (i < D_1F80000C) {
        point = vec;
        cell  = d + 1;
        do {
            x = (point[0] >> 3) + g_Task->pos.x.fixed;
            y = (point[1] >> 3) + g_Task->pos.y.fixed;
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(1, 1, 320, 256), 0);
            Area_AddCellPrim(x, y, 2, sizeof(DR_MODE));
            primitive = (LINE_G2*)g_GfxPrimCursor;
            SetLineG2(primitive);
            SetSemiTrans(primitive, 1);
            RotTransPers(D_1F800014, (long*)&primitive->x0, &p, &flag);
            if RANDOM_MASK (1) {
                D_1F800000 = RANDOM_MASK(BOLT_FLICKER_MASK) + BOLT_FLICKER_BASE;
            } else {
                D_1F800000 = BOLT_FLICKER_BASE - RANDOM_MASK(BOLT_FLICKER_MASK);
            }
            page     = ((g_Task->param.unk_0B + i + 2) & 0xF) << 8;
            point[0] = 0;
            cell[0]  = page;
            point[1] = FIXED_MUL(rsin(page), cell[-1]);
            point[2] = -(i << 6);
            RotTransPers((SVECTOR*)point, (long*)&primitive->x1, &p, &flag);
            setRGB0(primitive, cell[1], cell[1], 32);
            cell[1] = (rand() + 0x40) & 0x3F;
            setRGB1(primitive, cell[1], cell[1], 32);
            Area_AddCellPrim(x, y, 2, sizeof(LINE_G2));
            i++;
        } while (i < cell[2]);
    }
}
