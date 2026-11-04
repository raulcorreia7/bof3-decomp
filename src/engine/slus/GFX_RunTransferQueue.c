#include "engine/slus/slus.h"

/* walks the transfer queue: each entry names two packed RECT
 * halves and a record whose kind routes the upload through func_8014E7F8,
 * func_8014E8FC or LoadImage; the queue count is cleared afterwards.
 */
MATCH void GFX_RunTransferQueue(void) {
    RECT rect;
    u16* table1;
    u16* table2;
    u16* record;
    u8   index;
    s32  kind;
    s32  i;

    i = 0;
    if (D_80145A00 != 0) {
        table1 = D_80145A54;
        table2 = &D_80145A54[20];
        do {
            index  = (u8)i;
            rect.x = table1[index];
            rect.y = table2[index];
            record = (u16*)(&D_80145A04)[index];
            rect.w = *record++;
            rect.h = *record++;
            kind   = *(s32*)record;
            if (kind == 1) {
                GFX_ExpandRgb555((u32*)(record + 2), rect);
            } else if (kind == 2) {
                GFX_DecodeLzss((u32*)(record + 2), rect);
            } else {
                LoadImage(&rect, (u_long*)(record + 2));
            }
            i++;
        } while ((u8)i < D_80145A00);
    }
    D_80145A00 = 0;
}
