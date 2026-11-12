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
    s32  var_s7;
    s32  var_s4;
    s32  var_fp;
    s32  var_t0_34;
    s32  count;
    s32  sum_a;
    s32  sum_b;
    s32  draw_mode;
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
            var_t0_34 = var_s4 & BYTE_MASK;
            tmp       = (s8)((var_s7 & BYTE_MASK) + 1);
            if (var_t0_34 >= tmp) {
                var_s0 = tmp;
                do {
                    a2 = OBJ(var_t0_34);
                    a3 = OBJ(var_t0_34 - 1);
                    if ((*(u16*)(a2 + 0x32) < *(u16*)(a3 + 0x32)) ||
                        ((*(u16*)(a2 + 0x32) == *(u16*)(a3 + 0x32)) && ((sum_a = *(s32*)(a2 + 0x34) + *(s32*)(a2 + 0x38), sum_b = *(s32*)(a3 + 0x34) + *(s32*)(a3 + 0x38), (sum_a < sum_b)) ||
                                                                        ((sum_a == sum_b) && (*(s32*)(a2 + 0x3C) < *(s32*)(a3 + 0x3C)))))) {
                        Area_SwapObjects(var_t0_34, (var_s4 - 1) & BYTE_MASK);
                    }
                    var_s4 -= 1;
                    var_t0_34 = var_s4 & BYTE_MASK;
                } while (var_t0_34 >= var_s0);
            }
            var_s7 += 1;
        } while ((var_s7 & BYTE_MASK) < (D_8014832D - 1));
    }
    draw_mode = 0x225;
    if (GetGraphType() != 1) {
        draw_mode = 0x95;
        if (GetGraphType() == 2) {
            draw_mode = 0x225;
        }
    }
    var_s7 = 0;
    var_s4 = 0;
    var_fp = 0;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, draw_mode, NULL);
    GFX_AddPrim(6U, sizeof(DR_MODE));
    do {
        if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
            Area_DrawCellLayer(var_s7 & BYTE_MASK);
        }
        if (g_AreaDrawFlags & AREA_DRAW_APPEND_AREA_PRIMITIVES) {
            tmp  = ((g_FrameBufferIndex + 4) * 8) + ((var_s7 & BYTE_MASK) * 0x30);
            word = *(u32*)(D_80142CC0 + tmp);
            if (word != 0) {
                u32** slot = &D_801459D0[g_AreaDrawMode];
                u32*  head = *slot;
                setaddr(head, word);
                *slot = *(u32**)(D_80142CC4 + tmp);
            }
        }
        layer = var_s7 & BYTE_MASK;
    loop_22:
        var_v1_169 = var_s4 & BYTE_MASK;
    loop_23:
        if ((OBJ_KEY(var_v1_169) >> 8) == layer) {
            var_a0_187 = var_fp & BYTE_MASK;
            if (var_v1_169 < D_8014832D) {
            block_27:
                word = D_80143740[var_a0_187];
                if ((((word >> 0x18) == layer) && (var_a0_187 < D_8014933D) && (OBJ_KEY(var_s4 & BYTE_MASK) >= (word >> 0x10))) || ((var_s4 & BYTE_MASK) == D_8014832D)) {
                    var_s0 = var_fp & BYTE_MASK;
                    if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
                        u32* pk  = &D_80143740[var_s0];
                        u8*  pkt = (u8*)g_AreaCellPrims + g_FrameBufferIndex * 0x28 + (*pk & 0xFFF) * 0x50;
                        CatPrim(D_801459D0[g_AreaDrawMode], pkt);
                        D_801459D0[g_AreaDrawMode] = (u32*)pkt;
                    }
                    var_fp += 1;
                }
                var_s0 = var_fp & BYTE_MASK;
                var_s3 = &D_80143740[var_s0];
                var_s2 = OBJ_KEY(var_s4 & BYTE_MASK);
                var_s1 = 0;
                merged = var_s2 < *(u16*)((u8*)var_s3 + 2);
            loop_45:
                tmp = var_s4 & BYTE_MASK;
                if (merged == 0) {
                    if (var_s0 != D_8014933D) {
                        goto block_47;
                    }
                    goto block_36;
                }
            block_36:
                obj      = OBJ(tmp);
                key      = *(u16*)(obj + 0x32);
                unlinked = var_s1 << 0x18;
                if ((((u32)(key << 0x10)) >> 0x18) == layer) {
                    if (tmp < D_8014832D) {
                        if (g_AreaDrawMode != 6) {
                            if (g_AreaDrawMode == 4) {
                                unlinked = var_s1 << 0x18;
                                if ((s16)var_s2 == (s16)key) {
                                    goto block_41;
                                }
                            } else {
                                goto block_47;
                            }
                        } else {
                        block_41:
                            TASK_SET(obj);
                            if (obj[0x24] & 0x40) {
                                var_s1 += func_8015AD00(&D_80147D08[(s8)var_s1]);
                            } else {
                                i = (s8)var_s1;
                                var_s1 += 1;
                                D_80147D08[i].primitive = obj;
                                D_80147D0C[i].depth     = *(s32*)(obj + 0x60) | WORD_SIGN_BIT;
                            }
                            var_s4 += 1;
                            merged = OBJ_KEY(var_s4 & BYTE_MASK) < *(u16*)((u8*)var_s3 + 2);
                            goto loop_45;
                        }
                    } else {
                    block_47:
                        unlinked = var_s1 << 0x18;
                    }
                }
                var_s2 = 0;
                if (((unlinked >> 0x18) - 1) > 0) {
                    var_s6 = var_s1 - 1;
                    i      = 0;
                    do {
                        var_s0 = var_s6;
                        tmp    = i + 1;
                        if (var_s6 >= tmp) {
                            j = (s8)var_s0;
                            do {
                                var_s0 = j - 1;
                                if (D_80147D0C[j - 1].depth < D_80147D0C[j].depth) {
                                    func_8014C47C(&D_80147D08[j], &D_80147CFC[j]);
                                }
                                j = (s8)var_s0;
                            } while (j >= tmp);
                        }
                        i = (s8)(i + 1);
                    } while (i < ((s8)var_s1 - 1));
                }
                var_s2 = 0;
                if ((s8)var_s1 > 0) {
                    limit = (s8)var_s1;
                    i     = 0;
                    do {
                        if (D_80147D0C[i].depth < 0) {
                            if (g_AreaDrawFlags & AREA_DRAW_NEGATIVE_DEPTH) {
                                TASK_SET(D_80147D08[i].primitive);
                                Area_DrawObjectSprite();
                            }
                        } else {
                            if (g_AreaDrawFlags & AREA_DRAW_APPEND_ACTOR_PRIMITIVES) {
                                entry = (u8*)D_80147D08[i].work;
                                TASK_SET(entry);
                                CatPrim(D_801459D0[entry[0x29]], D_80147D08[i].primitive);
                                D_801459D0[TASK_BYTES[0x29]] = (u32*)D_80147D08[i].primitive;
                            }
                        }
                        i = (s8)(i + 1);
                    } while (i < limit);
                    var_v1_169 = var_s4 & BYTE_MASK;
                } else {
                    goto loop_22;
                }
                goto loop_23;
            }
        }
        var_a0_187 = var_fp & BYTE_MASK;
        if ((D_80143740[var_a0_187] >> 0x18) == layer) {
            if (var_a0_187 < D_8014933D) {
                goto block_27;
            }
        }
        if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
            Area_AddScenePrim(var_s7 & BYTE_MASK);
        }
        var_s7 += 1;
    } while ((var_s7 & BYTE_MASK) < 0x37U);
}
#else
INCLUDE_ASM(func_8014BC70);
#endif
