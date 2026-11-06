#include "start_08.h"

extern volatile u8 g_SndMono;

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 65.62%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_801E26A8(s32 x, s32 y) {
    u8  pairs[6][2] = {{0, D_80144950}, {1, D_80144952}, {2, D_80144953}, {3, g_SndMono}, {4, D_80144956}, {5, 0}};
    s16 i;
    u8  marker;

    Menu_DrawWindowFrame((s16)x, (s16)y, 0x21, 0xD);
    x = (x + 5) & HALF_MASK;
    y += 9;
    for (i = 0; i < 6; i++, y += 0xF) {
        marker = 0;
        if ((s8)D_80148655 - 2 == i) {
            marker = D_80148654;
        }
        Menu_DrawOptionRow(x, y & HALF_MASK, i & BYTE_MASK, marker);
        marker = 0;
        if ((s8)D_80148655 - 2 == i) {
            marker = D_80148654;
        }
        func_801E2C00(x, y & HALF_MASK, pairs[i][0], pairs[i][1], marker);
    }
}
#else
INCLUDE_ASM(func_801E26A8);
#endif
