/* Finds the first empty row in the sprite work table at AREA_WORK, or NULL. */
/* func_801F2D7C (area143), func_801D171C (sce15ef3) */
MATCH SpriteSpark* Area_FindFreeSpriteRow(void) {
    SpriteSpark* spark;
    u16          i;

    spark = MEM_PTR(SpriteSpark, AREA_WORK);
    for (i = 0; i < SPRITE_SPARK_COUNT; i++) {
        if (spark->active == 0) {
            return spark;
        }
        spark++;
    }
    return NULL;
}
