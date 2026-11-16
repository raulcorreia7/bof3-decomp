#include "engine/slus/slus.h"

/* The object list entry at index i: D_8014828C holds the object pointers. */
#define OBJ(i)     ((u8*)D_8014828C[i])
#define OBJ_KEY(i) (*(u16*)(OBJ(i) + 0x32))

/* draws every queued object per scene layer: sorts the object list by layer key and depth, then for each of the
 * 0x37 scenes merges the object list with the packet list D_80143740 by key and links each object (sorted by depth
 * through the panel sort rows) or packet into the ordering table.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_8014BC70(void) {
    s32  layer;
    u8   var_s7;
    u8   var_s4;
    u8   var_fp;
    s32  var_t0_34;
    s32  count;
    s32  sum_a;
    s32  sum_b;
    s32  tmp;
    s32  merged;
    s32  limit;
    s32  i;
    s32  j;
    s32  key;
    u8*  a2;
    u8*  a3;
    u8*  obj;
    u32  word;
    s8   var_s0;
    s32  first;
    u32  packet;
    s8   rows;
    s8   row;
    s8   other;
    s8   last;
    s32  lowest;
    s32  tpage;
    s8   var_s6;
    u32* var_s3;
    u32  var_s2;
    s32  var_s1;
    s32  unlinked;
    u32  var_a0_187;
    u32  var_v1_169;
    u8*  entry;

    count  = D_8014832D;
    var_s7 = 0;
    if ((count - 1) > 0) {
        do {
            var_s4    = count - 1;
            var_t0_34 = var_s4;
            first     = var_s7 + 1;
            if (var_t0_34 >= first) {
                lowest = first;
                do {
                    a2 = OBJ(var_t0_34);
                    a3 = OBJ(var_t0_34 - 1);
                    if ((*(u16*)(a2 + 0x32) < *(u16*)(a3 + 0x32)) ||
                        ((*(u16*)(a2 + 0x32) == *(u16*)(a3 + 0x32)) && ((sum_a = *(s32*)(a2 + 0x34) + *(s32*)(a2 + 0x38), sum_b = *(s32*)(a3 + 0x34) + *(s32*)(a3 + 0x38), (sum_a < sum_b)) ||
                                                                        ((sum_a == sum_b) && (*(s32*)(a2 + 0x3C) < *(s32*)(a3 + 0x3C)))))) {
                        Area_SwapObjects(var_t0_34, (u8)(var_s4 - 1));
                    }
                    var_s4 -= 1;
                    var_t0_34 = var_s4;
                } while (var_t0_34 >= lowest);
            }
            var_s7 += 1;
            count = D_8014832D;
        } while (var_s7 < (count - 1));
    }
    tpage  = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    var_s7 = 0;
    var_s4 = 0;
    var_fp = 0;
    GFX_ADD_LAYER_DRAW_MODE(6U, tpage);
    do {
        if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
            Area_DrawCellLayer(var_s7);
        }
        if (g_AreaDrawFlags & AREA_DRAW_APPEND_AREA_PRIMITIVES) {
            word = (u32)g_AreaCellPacketLists[var_s7][g_FrameBufferIndex + 4].head;
            if (word != 0) {
                u32** slot = &D_801459D0[g_AreaDrawMode];
                u32*  head = *slot;
                setaddr(head, word);
                *slot = (u32*)g_AreaCellPacketLists[var_s7][g_FrameBufferIndex + 4].tail;
            }
        }
        layer = var_s7;
        while ((((OBJ_KEY(var_s4) >> 8) == layer) && (var_s4 < D_8014832D)) || (((D_80143740[var_fp] >> 0x18) == layer) && (var_fp < D_8014933D))) {
            word = D_80143740[var_fp];
            if ((((word >> 0x18) == layer) && (var_fp < D_8014933D) && (OBJ_KEY(var_s4) >= (word >> 0x10))) || (var_s4 == D_8014832D)) {
                if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
                    packet = var_fp;
                    CatPrim(D_801459D0[g_AreaDrawMode], &g_AreaCellPrims[D_80143740[packet] & 0xFFF][g_FrameBufferIndex]);
                    D_801459D0[g_AreaDrawMode] = (u32*)&g_AreaCellPrims[D_80143740[packet] & 0xFFF][g_FrameBufferIndex];
                }
                var_fp += 1;
            }
            packet = var_fp;
            var_s3 = &D_80143740[packet];
            var_s2 = OBJ_KEY(var_s4);
            rows   = 0;
            merged = var_s2 < *(u16*)((u8*)var_s3 + 2);
            while (merged || (packet == D_8014933D)) {
                obj = OBJ(var_s4);
                key = *(u16*)(obj + 0x32);
                if ((((u32)(key << 0x10)) >> 0x18) != layer) {
                    break;
                }
                if (!(var_s4 < D_8014832D)) {
                    break;
                }
                if (g_AreaDrawMode != 6) {
                    if (g_AreaDrawMode != 4) {
                        break;
                    }
                    if ((s16)var_s2 != (s16)key) {
                        break;
                    }
                }
                TASK_SET(obj);
                if (obj[0x24] & 0x40) {
                    rows += func_8015AD00(&D_80147D08[rows]);
                } else {
                    i = rows;
                    rows++;
                    D_80147D08[i].primitive = obj;
                    D_80147D0C[i].depth     = *(s32*)(obj + 0x60) | WORD_SIGN_BIT;
                }
                var_s4 += 1;
                merged = OBJ_KEY(var_s4) < *(u16*)((u8*)var_s3 + 2);
            }
            row = 0;
            if ((rows - 1) > 0) {
                last = rows - 1;
                do {
                    for (other = last; other >= (row + 1); other--) {
                        if ((s16)D_80147D08[other - 1].z < (s16)D_80147D08[other].z) {
                            MATH_SwapVectors((struct Vec3W*)&D_80147D08[other], (struct Vec3W*)&D_80147CFC[other]);
                        }
                    }
                    row++;
                } while (row < (rows - 1));
            }
            row = 0;
            if (rows > 0) {
                limit = rows;
                do {
                    if (D_80147D0C[row].depth < 0) {
                        if (g_AreaDrawFlags & AREA_DRAW_NEGATIVE_DEPTH) {
                            TASK_SET(D_80147D08[row].primitive);
                            Area_DrawObjectSprite();
                        }
                    } else if (g_AreaDrawFlags & AREA_DRAW_APPEND_ACTOR_PRIMITIVES) {
                        TASK_SET(D_80147D08[row].work);
                        CatPrim(D_801459D0[g_Task->draw_layer], D_80147D08[row].primitive);
                        D_801459D0[g_Task->draw_layer] = (u32*)D_80147D08[row].primitive;
                    }
                    row++;
                } while (row < limit);
            }
        }
        if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
            Area_AddScenePrim(var_s7);
        }
        var_s7 += 1;
    } while (var_s7 < 0x37U);
}
#else
INCLUDE_ASM(func_8014BC70);
#endif
