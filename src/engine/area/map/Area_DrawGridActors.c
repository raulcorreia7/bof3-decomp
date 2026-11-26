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
    u8   scene;
    u8   actor;
    u8   packet_index;
    s32  scan;
    s32  count;
    s32  sum_a;
    s32  sum_b;
    s32  merged;
    s32  limit;
    s32  panel;
    s32  key;
    u8*  a2;
    u8*  a3;
    u8*  obj;
    u32  word;
    s32  first;
    u32  packet;
    s8   rows;
    s8   row;
    s8   other;
    s8   last;
    s32  lowest;
    s32  tpage;
    u32* packet_slot;
    u32  actor_key;
    FAKE_STACK_PADS(u8, 16);

    count = g_AreaGridActorCount;
    scene = 0;
    if ((count - 1) > 0) {
        do {
            actor = count - 1;
            scan  = actor;
            first = scene + 1;
            if (scan >= first) {
                lowest = first;
                do {
                    a2 = OBJ(scan);
                    a3 = OBJ(scan - 1);
                    if ((*(u16*)(a2 + 0x32) < *(u16*)(a3 + 0x32)) ||
                        ((*(u16*)(a2 + 0x32) == *(u16*)(a3 + 0x32)) && ((sum_a = *(s32*)(a2 + 0x34) + *(s32*)(a2 + 0x38), sum_b = *(s32*)(a3 + 0x34) + *(s32*)(a3 + 0x38), (sum_a < sum_b)) ||
                                                                        ((sum_a == sum_b) && (*(s32*)(a2 + 0x3C) < *(s32*)(a3 + 0x3C)))))) {
                        Area_SwapGridActors(scan, (u8)(actor - 1));
                    }
                    actor -= 1;
                    scan = actor;
                } while (scan >= lowest);
            }
            scene += 1;
            count = g_AreaGridActorCount;
        } while (scene < (count - 1));
    }
    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_FIELD_SCENE, tpage);
    scene        = 0;
    actor        = 0;
    packet_index = 0;
    do {
        if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
            Area_CellDrawLayer(scene);
        }
        if (g_AreaDrawFlags & AREA_DRAW_APPEND_AREA_PRIMITIVES) {
            word = (u32)g_AreaCellPacketLists[scene][g_GfxBufferIndex + 4].head;
            if (word != 0) {
                u32** slot = &g_GfxOtHeads[g_AreaDrawMode];
                u32*  head = *slot;
                setaddr(head, word);
                *slot = (u32*)g_AreaCellPacketLists[scene][g_GfxBufferIndex + 4].tail;
            }
        }
        layer = scene;
        while ((((OBJ_KEY(actor) >> 8) == layer) && (actor < g_AreaGridActorCount)) || (((g_AreaCellPackets[packet_index] >> 0x18) == layer) && (packet_index < g_AreaCellPacketCount))) {
            word = g_AreaCellPackets[packet_index];
            if ((((word >> 0x18) == layer) && (packet_index < g_AreaCellPacketCount) && (OBJ_KEY(actor) >= (word >> 0x10))) || (actor == g_AreaGridActorCount)) {
                if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
                    packet = packet_index;
                    CatPrim(g_GfxOtHeads[g_AreaDrawMode], &g_AreaCellPrims[g_AreaCellPackets[packet] & 0xFFF][g_GfxBufferIndex]);
                    g_GfxOtHeads[g_AreaDrawMode] = (u32*)&g_AreaCellPrims[g_AreaCellPackets[packet] & 0xFFF][g_GfxBufferIndex];
                }
                packet_index += 1;
            }
            packet      = packet_index;
            packet_slot = &g_AreaCellPackets[packet];
            actor_key   = OBJ_KEY(actor);
            rows        = 0;
            merged      = actor_key < *(u16*)((u8*)packet_slot + 2);
            while (merged || (packet == g_AreaCellPacketCount)) {
                obj = OBJ(actor);
                key = *(u16*)(obj + 0x32);
                if ((((u32)(key << 0x10)) >> 0x18) != layer) {
                    break;
                }
                if (!(actor < g_AreaGridActorCount)) {
                    break;
                }
                if (g_AreaDrawMode != GFX_LAYER_FIELD_SCENE) {
                    if (g_AreaDrawMode != GFX_LAYER_BATTLE_SCENE) {
                        break;
                    }
                    if ((s16)actor_key != (s16)key) {
                        break;
                    }
                }
                SELF_SET(obj);
                if (obj[0x24] & 0x40) {
                    rows += func_8015AD00(&D_80147D08[rows]);
                } else {
                    panel = rows;
                    rows++;
                    D_80147D08[panel].primitive = obj;
                    D_80147D0C[panel].depth     = *(s32*)(obj + 0x60) | WORD_SIGN_BIT;
                }
                actor += 1;
                merged = OBJ_KEY(actor) < *(u16*)((u8*)packet_slot + 2);
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
                            SELF_SET(D_80147D08[row].primitive);
                            Area_DrawObjectSprite();
                        }
                    } else if (g_AreaDrawFlags & AREA_DRAW_APPEND_ACTOR_PRIMITIVES) {
                        SELF_SET(D_80147D08[row].work);
                        CatPrim(g_GfxOtHeads[SELF(Actor)->draw_layer], D_80147D08[row].primitive);
                        g_GfxOtHeads[SELF(Actor)->draw_layer] = (u32*)D_80147D08[row].primitive;
                    }
                    row++;
                } while (row < limit);
            }
        }
        if (g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) {
            Area_SceneAddPrim(scene);
        }
        scene += 1;
    } while (scene < 0x37U);
}
#else
INCLUDE_ASM(Area_DrawGridActors);
#endif
