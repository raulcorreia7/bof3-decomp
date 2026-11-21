/* Advance the area origin one step and advance the work state once it passes image threshold. Each overlay's image header names its origin offset, step and threshold. */
/* func_801F2EF8 (area160), func_801F2EF8 (area163), func_801F2EF8 (area164), func_801F2EF8 (area165), func_801F2F0C
   (area169), func_801F2F2C (area157), func_801F2FE0 (area167), func_801F3420 (area152), func_801F3490 (area033),
   func_801F34CC (area151), func_801F355C (area016), func_801F355C (area045), func_801F3560 (area115), func_801F3574
   (area121), func_801F3590 (area087), func_801F3594 (area065), func_801F3620 (area104), func_801F3738 (area168),
   func_801F377C (area174), func_801F3F28 (area170), func_801F40C0 (area088), func_801F4458 (area173) */
MATCH void Actor_SlideScreenX(void) {
    u8* work;
    u16 origin;

    work                                 = TASK_BYTES;
    origin                               = FIELD(u16, work, AREA_ORIGIN_OFFSET) + ACTOR_SCREEN_X_STEP;
    FIELD(u16, work, AREA_ORIGIN_OFFSET) = origin;
    if ((s16)origin >= ACTOR_SCREEN_X_THRESHOLD) {
        work[0x02]++;
    }
    Area_Update();
}
