#include "area143_13.h"

MATCH void func_801F2FE0(void) {
    u16        i;
    AreaSpark* spark;
    /* FAKE: the retail frame holds 0x10 bytes no statement explains. */
    FAKE_STACK_PADS(u8, 0x10);

    spark = AREA_SPARKS;
    for (i = 0; i < 0x10; i++) {
        spark->live   = 1;
        spark->unk_01 = 0;
        spark->unk_02 = rand() | 0xF0;
        spark->unk_03 = RANDOM_MASK(0x1F);
        spark->x      = D_801F42E8[i][0] << 16;
        spark->y      = D_801F42E8[i][1] << 16;
        spark->z      = Area_SampleHeight(spark->x, spark->y) << 16;
        spark++;
    }
}
