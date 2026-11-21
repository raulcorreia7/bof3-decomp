/* Starts one spark at a random point near the actor position, falling from rest. */
/* func_801F8B50 (scena08), func_801F83D0 (scena07) */
MATCH void Scene_InitSpark(FallingSpark* spark) {
    spark->active      = 1;
    spark->life        = 8;
    spark->kind        = 0;
    spark->fade        = 0;
    spark->speed       = 0;
    spark->life_reload = 64;
    spark->x           = g_Task->pos.x.fixed + (RANDOM_MASK(BYTE_MASK) << 11) - TO_COORD(4);
    spark->y           = g_Task->pos.y.fixed + (RANDOM_MASK(BYTE_MASK) << 11) - TO_COORD(4);
    spark->z           = g_Task->pos.z.fixed;
}
