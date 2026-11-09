/* While the actor's slide counter (0x0A) runs, moves it along the diagonal by the current entry of the offset table and lowers the field scroll by 2; at zero it clears the slide flag (0x04). */
/* AREA_SLIDE_ACTOR_STEP (area068 0x801F3B9C, area068 0x801F3CB0, area069 0x801F2C88) */
#define AREA_SLIDE_ACTOR_STEP(OFFSETS)                                       \
    Actor* work;                                                             \
    work = g_Task;                                                           \
    if (work->unk_0A != 0) {                                                 \
        work->pos.x.fixed += ((s8*)(OFFSETS + 8))[work->unk_0A & 0xF] << 11; \
        work->pos.y.fixed -= ((s8*)(OFFSETS + 8))[work->unk_0A & 0xF] << 11; \
        work->unk_0A -= 1;                                                   \
        g_GameState->u.field.unk_122 -= 2;                                   \
    } else {                                                                 \
        work->unk_04 = 0;                                                    \
    }
