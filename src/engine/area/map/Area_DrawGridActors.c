#include "engine/slus/slus.h"

/* The queue entry at index: g_AreaGridActors holds the actor pointers. */
#define OBJ(i)     ((u8*)g_AreaGridActors[i])
#define OBJ_KEY(i) (*(u16*)(OBJ(i) + 0x32))

/* draws every queued grid actor per scene layer: sorts the actor queue by layer key and depth, then for each of the
 * 0x37 scenes merges the actor queue with the packet list g_AreaCellPackets by key and links each actor (sorted by depth
 * through the panel sort rows) or packet into the ordering table.
 */
/* FAKE: retail reserves four stack words no local explains; the pad restores its 0x58 frame. */
/* func_8014BC70 */
#ifdef NON_MATCHING
NON_MATCHING void Area_DrawGridActors(void) {
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
    FAKE_STACK_PADS(u8, 16);

    count  = g_AreaGridActorCount;
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
                        Area_SwapGridActors(var_t0_34, (u8)(var_s4 - 1));
                    }
                    var_s4 -= 1;
                    var_t0_34 = var_s4;
                } while (var_t0_34 >= lowest);
            }
            var_s7 += 1;
            count = g_AreaGridActorCount;
        } while (var_s7 < (count - 1));
    }
    tpage  = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    var_s7 = 0;
    var_s4 = 0;
    var_fp = 0;
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_FIELD_SCENE, tpage);
    do {
        if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
            Area_CellDrawLayer(var_s7);
        }
        if (g_AreaDrawFlags & AREA_DRAW_APPEND_AREA_PRIMITIVES) {
            word = (u32)g_AreaCellPacketLists[var_s7][g_GfxBufferIndex + 4].head;
            if (word != 0) {
                u32** slot = &g_GfxOtHeads[g_AreaDrawMode];
                u32*  head = *slot;
                setaddr(head, word);
                *slot = (u32*)g_AreaCellPacketLists[var_s7][g_GfxBufferIndex + 4].tail;
            }
        }
        layer = var_s7;
        while ((((OBJ_KEY(var_s4) >> 8) == layer) && (var_s4 < g_AreaGridActorCount)) || (((g_AreaCellPackets[var_fp] >> 0x18) == layer) && (var_fp < g_AreaCellPacketCount))) {
            word = g_AreaCellPackets[var_fp];
            if ((((word >> 0x18) == layer) && (var_fp < g_AreaCellPacketCount) && (OBJ_KEY(var_s4) >= (word >> 0x10))) || (var_s4 == g_AreaGridActorCount)) {
                if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
                    packet = var_fp;
                    CatPrim(g_GfxOtHeads[g_AreaDrawMode], &g_AreaCellPrims[g_AreaCellPackets[packet] & 0xFFF][g_GfxBufferIndex]);
                    g_GfxOtHeads[g_AreaDrawMode] = (u32*)&g_AreaCellPrims[g_AreaCellPackets[packet] & 0xFFF][g_GfxBufferIndex];
                }
                var_fp += 1;
            }
            packet = var_fp;
            var_s3 = &g_AreaCellPackets[packet];
            var_s2 = OBJ_KEY(var_s4);
            rows   = 0;
            merged = var_s2 < *(u16*)((u8*)var_s3 + 2);
            while (merged || (packet == g_AreaCellPacketCount)) {
                obj = OBJ(var_s4);
                key = *(u16*)(obj + 0x32);
                if ((((u32)(key << 0x10)) >> 0x18) != layer) {
                    break;
                }
                if (!(var_s4 < g_AreaGridActorCount)) {
                    break;
                }
                if (g_AreaDrawMode != GFX_LAYER_FIELD_SCENE) {
                    if (g_AreaDrawMode != GFX_LAYER_BATTLE_SCENE) {
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
                            MATH_SwapVectors((Pos3*)&D_80147D08[other], (Pos3*)&D_80147CFC[other]);
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
                        CatPrim(g_GfxOtHeads[TASK(Actor)->draw_layer], D_80147D08[row].primitive);
                        g_GfxOtHeads[TASK(Actor)->draw_layer] = (u32*)D_80147D08[row].primitive;
                    }
                    row++;
                } while (row < limit);
            }
        }
        if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
            Area_SceneAddPrim(var_s7);
        }
        var_s7 += 1;
    } while (var_s7 < 0x37U);
}
#else
INCLUDE_ASM(Area_DrawGridActors);
#endif
