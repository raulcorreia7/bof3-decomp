/* Starts one spark at a random point near the actor position, falling from rest. */
/* func_801F8B50 (scena08), func_801F83D0 (scena07) */
MATCH void Scene_InitSpark(FallingSpark* spark) {
    spark->header.active = 1;
    spark->header.life   = 8;
    spark->header.type   = 0;
    spark->header.shade  = 0;
    spark->speed         = 0;
    spark->life_reload   = 64;
    spark->pos.vx        = SELF(Actor)->pos.x.fixed + (RANDOM_MASK(BYTE_MASK) << 11) - TO_COORD(4);
    spark->pos.vy        = SELF(Actor)->pos.y.fixed + (RANDOM_MASK(BYTE_MASK) << 11) - TO_COORD(4);
    spark->pos.vz        = SELF(Actor)->pos.z.fixed;
}
