#include "area030_04.h"

/* Runs the panel helper, then issues the 0x1D text-row draw for the
 * table entry selected by the scratch record byte at +0x4B. */
MATCH void func_801D3898(void) {
    FishingState* record;
    s32           index;

    Fishing_PromptSlideOut();
    record = SELF(FishingState);
    index  = (record->row_4B * 3) << 2;
    UI_TextDraw(29, (record->origin_y + 2), 0, D_801E1E78[index], (u8*)(*(u32*)((u8*)D_801E1E7C + index)));
}
