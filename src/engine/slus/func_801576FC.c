#include "engine/slus/slus.h"

/* One word of a cell patch list: the list header, a patch head (row, column, selector bits and the patch type
 * in the top byte) or a patch value. */
typedef union AreaPatchWord {
    u32 word;

    struct {
        s16 request;
        u16 count;
    } header;

    struct {
        u8 row;
        u8 column;
        u8 pad_02;
        u8 type;
    } head;
} AreaPatchWord;

/* Applies a cell patch list: each patch stores a record word, a cell word or a cell code for (column, row), picked
 * by the list's condition, and the first two types upload the record to the cell's primitive. */
MATCH void func_801576FC(u8* record) {
    AreaPatchWord* list = (AreaPatchWord*)record;
    AreaPatchWord* entry;
    POLY_FT4*      prim;
    u32*           dst;
    u32*           slot;
    u32*           cells;
    u32            word;
    s32            i;
    s32            cond;
    s32            count;
    s32            row;
    s32            column;
    s32            type;
    s32            id;
    /* FAKE: unused frame, 16 bytes. */
    FAKE_STACK_PADS(u8, 16);

    i     = 0;
    cond  = Area_TestCondition(list->header.request);
    count = list->header.count;
    list++;
    if (count == 0) {
        return;
    }
    do {
        entry  = &list[i];
        word   = entry->word;
        column = entry->head.column;
        row    = word & 0xFF;
        switch (word >> 24) {
            case 0:
                dst   = &AREA_MAP_TILES[*(AREA_MAP_GRID + column + row * AREA_MAP_BUNDLE->width)];
                slot  = dst + ((word >> 16) & 0xF);
                *slot = entry[cond + 1].word;
                i++;
            case 1:
                type = (entry->word >> 20) & 0xF;
                id   = Area_CellGetId(column, row);
                if (id != 0) {
                    switch (type) {
                        case 0:
                            prim = &g_AreaCellPrims[id][g_GfxBufferIndex];
                            break;
                        case 1:
                            prim = &g_AreaCellPrims[g_AreaCellPrims[id][1].pad2][g_GfxBufferIndex];
                            break;
                        default:
                            prim = &g_AreaCellPrims[g_AreaCellPrims[id][1].pad1][g_GfxBufferIndex];
                            break;
                    }
                    Area_ApplyTileToQuad(entry[cond + 1].word, prim, 1);
                }
                i += 2;
                break;
            case 2:
                cells                    = (u32*)(MAP_BUNDLE_BASE + 0x30) + row * g_AreaMapBundle.width;
                slot                     = (u32*)(column * 4 + (u32)cells);
                *slot                    = entry[cond + 1].word;
                g_AreaCameraRefreshCount = 2;
                i += 3;
                break;
            default:
                *(g_AreaCellCodes + column + row * g_AreaMapBundle.width) = entry[1].word >> (cond * 16);
                i += 2;
                break;
        }
    } while (i < count);
}
