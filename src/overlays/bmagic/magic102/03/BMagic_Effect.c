#include "magic102_03.h"

#include <inline_c.h>

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC14.h"

/* The effect's start: the caster's facing picks the target cell, every battler,
 * field actor and actor slot stores its height over the ground, the parts of the
 * cells around the target take the 0x28..0x2B commands this overlay draws, and the
 * effect clears its grid and queues the selection sound. */
MATCH void func_801EEC80(void) {
    ScenePart* part;
    ScenePart* end;
    u16*       run;
    s32        i;
    s32        j;
    u16        cell;
    s32        offset;

    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
            D_801F0CBC = g_BattleActiveActor->facing ^ 2;
        } else {
            D_801F0CBC = g_BattleActiveActor->facing;
        }
    } else {
        if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
            D_801F0CBC = g_BattleActiveActor->facing;
        } else {
            D_801F0CBC = g_BattleActiveActor->facing ^ 2;
        }
    }
    offset                          = D_801F0CBC * 2;
    D_801F0CC4                      = g_AreaTargetCellX + D_801F0C94[offset];
    D_801F0CC8                      = g_AreaTargetCellY + D_801F0C94[offset + 1];
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        if (g_Game.members[i].header.flags) {
            D_801F0ECC[i] = COORD_INT(g_Game.members[i].pos.z) - Area_HeightSample(g_BattleEffects[i].pos.x.fixed, g_BattleEffects[i].pos.y.fixed);
        }
    }
    for (i = 0; i < 8; i++) {
        if (!(Battle_SlotIsBlocked((u8)(i + 3)) & BYTE_MASK)) {
            D_801F0F40[i] = COORD_INT(g_BattleEnemyBattlers[i].pos.z) - Area_HeightSample(g_BattleEffects[i + 3].pos.x.fixed, g_BattleEffects[i + 3].pos.y.fixed);
            D_801F0F50[i] = COORD_INT(g_BattleEnemyBattlers[i].pos.z);
        }
    }
    for (i = 0; i < ACTOR_COUNT; i++) {
        if (g_Actors[i].header.flags) {
            D_801F0ED4[i] = COORD_INT(g_Actors[i].pos.z) - Area_HeightSample(g_Actors[i].pos.x.fixed, g_Actors[i].pos.y.fixed);
        }
    }
    for (i = 0; i < 4; i++) {
        if (g_PartyActors[i].header.flags) {
            D_801F0F10[i] = COORD_INT(g_PartyActors[i].pos.z) - Area_HeightSample(g_PartyActors[i].pos.x.fixed, g_PartyActors[i].pos.y.fixed);
        }
    }
    for (i = 0; i < ACTOR_SLOT_COUNT; i++) {
        if (g_SpawnedActors[i].header.flags && g_SpawnedActors[i].type == 0x17) {
            D_801F0F18[i] = COORD_INT(g_SpawnedActors[i].pos.z) - Area_HeightSample(g_SpawnedActors[i].pos.x.fixed, g_SpawnedActors[i].pos.y.fixed);
        }
    }
    for (i = 0; i < AREA_CELL_GRID_ROWS; i++) {
        for (j = 0; j < AREA_CELL_GRID_COLS; j++) {
            cell = g_AreaCellGrid[i][j];
            if (cell == 0) {
                continue;
            }
            part = (ScenePart*)((u8*)MAP_BUNDLE_BASE + g_AreaMapBundle.cell_record_offset * 4 + cell * 4);
            run  = (u16*)part - 1;
            end  = (ScenePart*)((u8*)part + (*run * 4 - 4));
            while (part != end) {
                if (PART_COMMAND(part->raw) == 0x00) {
                    part->raw = PART_COMMAND_SET(part->raw, 0x28);
                }
                if (PART_COMMAND(part->raw) == 0x21) {
                    part->raw = PART_COMMAND_SET(part->raw, 0x29);
                }
                if (PART_COMMAND(part->raw) == 0x22) {
                    part->raw = PART_COMMAND_SET(part->raw, 0x2A);
                }
                if (PART_COMMAND(part->raw) == 0x27) {
                    part->raw = PART_COMMAND_SET(part->raw, 0x2B);
                }
                part += part->head.count;
            }
        }
    }
    for (i = 0; i < 17; i++) {
        for (j = 14; j >= 0; j--) {
            D_801F0CCC[i][j] = 0;
        }
    }
    switch (g_Battle.encounter) {
        case 0x1C:
        case 0x23:
        case 0x2F:
        case 0x34:
            D_801F0CC0 = 1;
            break;
        default:
            D_801F0CC0 = 0;
            break;
    }
    SND_SEQueueSelection(0x100);
    SELF(PartyMember)->header.mode += 1;
}

/* Counts this effect's steps; at the tick limit it re-arms the counter, steps
 * the magic, and flips the area camera's vertical offset with the frame parity. */
MATCH void func_801EF218(void) {
    PartyMember* work;
    u8           tick;

    work         = SELF(PartyMember);
    tick         = work->unk_09 + EFFECT_TICK_INCREMENT;
    work->unk_09 = tick;
    if (tick >= EFFECT_TICK_LIMIT) {
        SELF(PartyMember)->unk_09 = 0;
        SELF(PartyMember)->header.mode += 1;
    }
    g_AreaCameraOffsetY      = (((g_FrameCount & 0x1) * 2) - 1) * (SELF(PartyMember)->unk_09 >> 1);
    g_AreaCameraRefreshCount = 2;
}

/* Rolls a sine wave over the ground: per step of unk_09, the rise of 16 bands is added to the corner heights of the
 * map cells in front of the caster from the target cell (scaled down by D_801F0C9C) and to D_801F0CCC, then every
 * party member or enemy, field actor and type-0x17 actor slot is set back on the ground at its stored height.
 * Shakes the camera, and advances header.mode once D_801F0CCC is all zero and unk_09 has reached 0x5B. */
MATCH void func_801EF2B8(void) {
    s32 i;
    s32 j;
    s32 rise;
    s32 fall;

    for (i = 0; i < 16; i++) {
        rise = (rsin(((SELF(PartyMember)->unk_09 << 7) + (i << 8)) & ANGLE_MASK) >> 8) - (rsin((((SELF(PartyMember)->unk_09 - 1) << 7) + (i << 8)) & ANGLE_MASK) >> 8);
        fall = (rsin(((SELF(PartyMember)->unk_09 << 7) + ((i + 1) << 8)) & ANGLE_MASK) >> 8) - (rsin((((SELF(PartyMember)->unk_09 - 1) << 7) + ((i + 1) << 8)) & ANGLE_MASK) >> 8);
        if (i == 0) {
            rise = 0;
        }
        if (i == 15) {
            fall = 0;
        }
        for (j = 0; j < 14; j++) {
            if (D_801F0CBC & 1) {
                if (D_801F0CC8 + j < 0 || D_801F0CC8 + j >= g_AreaMapBundle.height || D_801F0CC4 + i < 0 || D_801F0CC4 + i >= AREA_MAP_BUNDLE->width) {
                    continue;
                }
                MAP_CELL_CORNER(D_801F0CC8 + j, D_801F0CC4 + i, 0) += rise / D_801F0C9C[D_801F0CBC >> 1][j];
                MAP_CELL_CORNER(D_801F0CC8 + j, D_801F0CC4 + i, 2) += rise / D_801F0C9C[D_801F0CBC >> 1][j + 1];
                MAP_CELL_CORNER(D_801F0CC8 + j, D_801F0CC4 + i, 1) += fall / D_801F0C9C[D_801F0CBC >> 1][j];
                MAP_CELL_CORNER(D_801F0CC8 + j, D_801F0CC4 + i, 3) += fall / D_801F0C9C[D_801F0CBC >> 1][j + 1];
            } else {
                if (D_801F0CC8 + i < 0 || D_801F0CC8 + i >= g_AreaMapBundle.height || D_801F0CC4 + j < 0 || D_801F0CC4 + j >= AREA_MAP_BUNDLE->width) {
                    continue;
                }
                MAP_CELL_CORNER(D_801F0CC8 + i, D_801F0CC4 + j, 0) += rise / D_801F0C9C[D_801F0CBC >> 1][j];
                MAP_CELL_CORNER(D_801F0CC8 + i, D_801F0CC4 + j, 1) += rise / D_801F0C9C[D_801F0CBC >> 1][j + 1];
                MAP_CELL_CORNER(D_801F0CC8 + i, D_801F0CC4 + j, 2) += fall / D_801F0C9C[D_801F0CBC >> 1][j];
                MAP_CELL_CORNER(D_801F0CC8 + i, D_801F0CC4 + j, 3) += fall / D_801F0C9C[D_801F0CBC >> 1][j + 1];
            }
            D_801F0DCC[i][j] = D_801F0CCC[i][j];
            D_801F0CCC[i][j] += rise / D_801F0C9C[D_801F0CBC >> 1][j];
        }
    }
    if (g_Battle.target_selector & BATTLE_TARGET_PARTY_SIDE) {
        for (i = 0; i < 3; i++) {
            if (g_Game.members[i].header.flags) {
                COORD_INT(g_Game.members[i].pos.z) = D_801F0ECC[i] + Area_HeightSample(g_BattleEffects[i].pos.x.fixed, g_BattleEffects[i].pos.y.fixed);
            }
        }
    } else {
        for (i = 0; i < 8; i++) {
            if (!(Battle_SlotIsBlocked((u8)(i + 3)) & BYTE_MASK)) {
                if (D_801F0CC0 && D_801F0F50[i] > Area_HeightSample(g_BattleEffects[i + 3].pos.x.fixed, g_BattleEffects[i + 3].pos.y.fixed)) {
                    COORD_INT(g_BattleEnemyBattlers[i].pos.z) = D_801F0F50[i];
                } else {
                    COORD_INT(g_BattleEnemyBattlers[i].pos.z) = D_801F0F40[i] + Area_HeightSample(g_BattleEffects[i + 3].pos.x.fixed, g_BattleEffects[i + 3].pos.y.fixed);
                }
            }
        }
    }
    for (i = 0; i < 30; i++) {
        if (g_Actors[i].header.flags) {
            COORD_INT(g_Actors[i].pos.z) = D_801F0ED4[i] + Area_HeightSample(g_Actors[i].pos.x.fixed, g_Actors[i].pos.y.fixed);
        }
    }
    for (i = 0; i < 4; i++) {
        if (g_PartyActors[i].header.flags) {
            COORD_INT(g_PartyActors[i].pos.z) = D_801F0F10[i] + Area_HeightSample(g_PartyActors[i].pos.x.fixed, g_PartyActors[i].pos.y.fixed);
        }
    }
    for (i = 0; i < 20; i++) {
        if (g_SpawnedActors[i].header.flags && g_SpawnedActors[i].type == 0x17) {
            COORD_INT(g_SpawnedActors[i].pos.z) = D_801F0F18[i] + Area_HeightSample(g_SpawnedActors[i].pos.x.fixed, g_SpawnedActors[i].pos.y.fixed);
        }
    }
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = (((g_FrameCount & 1) * 2) - 1) * 8;
    SELF(PartyMember)->unk_09++;
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 14; j++) {
            if (D_801F0CCC[i][j] != 0) {
                return;
            }
        }
    }
    if (SELF(PartyMember)->unk_09 >= 0x5B) {
        SELF(PartyMember)->header.mode++;
    }
}

/* The effect's end: the cells around the target get back the commands the start replaced with 0x28..0x2B. */
MATCH void func_801EFD7C(void) {
    ScenePart* part;
    ScenePart* end;
    u16*       run;
    s32        i;
    s32        j;
    u16        cell;

    for (i = 0; i < AREA_CELL_GRID_ROWS; i++) {
        for (j = 0; j < AREA_CELL_GRID_COLS; j++) {
            cell = g_AreaCellGrid[i][j];
            if (cell == 0) {
                continue;
            }
            part = (ScenePart*)((u8*)MAP_BUNDLE_BASE + g_AreaMapBundle.cell_record_offset * 4 + cell * 4);
            run  = (u16*)part - 1;
            end  = (ScenePart*)((u8*)part + (*run * 4 - 4));
            while (part != end) {
                if (PART_COMMAND(part->raw) == 0x28) {
                    part->raw = PART_COMMAND_SET(part->raw, 0x00);
                }
                if (PART_COMMAND(part->raw) == 0x29) {
                    part->raw = PART_COMMAND_SET(part->raw, 0x21);
                }
                if (PART_COMMAND(part->raw) == 0x2A) {
                    part->raw = PART_COMMAND_SET(part->raw, 0x22);
                }
                if (PART_COMMAND(part->raw) == 0x2B) {
                    part->raw = PART_COMMAND_SET(part->raw, 0x27);
                }

                part += part->head.count;
            }
        }
    }
    g_AreaCameraOffsetY = 0;
    Battle_MarkDamaged(g_Battle.target_selector);
    g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
    Effect_Reset();
    g_AreaCameraRefreshCount = 2;
}

/* Draws the textured quads of the five-record parts at parts like the resident Area_DrawPartQuads, but each vertex
 * depth adds func_801F0ADC of its x and y. */
MATCH void func_801EFEFC(ScenePart* parts, s32 shift_x, s32 shift_y) {
    SVECTOR    verts[4];
    ScenePart* p;
    POLY_FT4*  prim;
    s32        i;
    s32        n;
    u32        mask;
    u8         ot;

    if ((Area_TestCondition(parts->head.id) << 24) == 0) {
        return;
    }
    shift_x = (shift_x - 0x80) << 7;
    shift_y = (shift_y - 0x80) << 7;
    func_801F0ADC(shift_x - 0x80, shift_y);
    for (n = 1; n != parts->head.count; n += 5) {
        setVector(&verts[0], shift_x + parts[n].vertex.x * 2, shift_y + parts[n].vertex.y * 2, func_801F0ADC(verts[0].vx, verts[0].vy) + parts[n].raw);
        gte_ldv0(&verts[0]);
        gte_rtps();
        p    = &parts[n];
        prim = (POLY_FT4*)g_GfxPrimCursor;
        gte_stsxy2(&prim->x0);
        if ((u16)(prim->x0 + 0x63) < 0x207U && (u16)(prim->y0 + 0x95) < 0x1C1U) {
            SetPolyFT4(prim);
            SetShadeTex(prim, 0);
            for (i = 1; i < 4; i++) {
                verts[i].vx = shift_x + p[i].vertex.x * 2;
                verts[i].vy = shift_y + p[i].vertex.y * 2;
                verts[i].vz = func_801F0ADC(verts[i].vx, verts[i].vy) + p[i].raw;
            }
            gte_ldv3c(&verts[1]);
            Area_ApplyTileToQuad(parts[n + 4].raw, prim, 1);
            gte_rtpt();
            if (parts[n + 4].raw & 0x4000) {
                /* Per-arm: keeps the constant's load inside the loop. */
                mask = 1 << 30;
                ot   = 4;
                if (parts[n + 4].raw & mask) {
                    ot = 7;
                }
            } else {
                mask = 1 << 30;
                ot   = 6;
                if (!(parts[n + 4].raw & mask)) {
                    ot = g_AreaDrawMode;
                }
            }
            GFX_AddPrim(ot, sizeof(POLY_FT4));
            gte_stsxy3(&prim->x1, &prim->x2, &prim->x3);
        }
    }
}

/* Draws one Gouraud-shaded quadrangle per eight-word part in the list at parts, like the resident
 * Area_DrawGouraudQuads, but each vertex's depth adds func_801F0ADC of its x and y. */
/* func_801F016C */
MATCH void Effect_DrawShadedQuads(ScenePart* parts, s32 shift_x, s32 shift_y) {
    SVECTOR    verts[4];
    long       flag;
    long       p;
    ScenePart* rec;
    POLY_G4*   prim;
    s32        n;
    s32        i;
    s32        mode;

    if ((Area_TestCondition(parts->head.id) << 24) == 0) {
        return;
    }
    shift_x = (shift_x - 0x80) << 7;
    shift_y = (shift_y - 0x80) << 7;
    func_801F0ADC(shift_x - 0x80, shift_y);
    n = 1;
    if (parts->head.count != 1) {
        rec = &parts[1];
        do {
            mode = getTPage(TPAGE_DEPTH_8BIT, rec[4].color.tpage, 320, 256);
            /* Written out: GFX_AddDitheredDrawMode moves the g_AreaDrawMode load. */
            GFX_ADD_DITHERED_DRAW_MODE(g_AreaDrawMode, mode);
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            for (i = 0; i < 4; i++, rec++, n++) {
                verts[i].vx = shift_x + parts[n].vertex.x * 2;
                verts[i].vy = shift_y + parts[n].vertex.y * 2;
                verts[i].vz = func_801F0ADC(verts[i].vx, verts[i].vy) + parts[n].raw;
            }
            RotTransPers4(&verts[1], &verts[2], &verts[3], &verts[0], (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, (long*)&prim->x0, &p, &flag);
            SetSemiTrans(prim, (rec[0].raw >> 31));
            setRGB0(prim, (rec[0].raw >> 16), (rec[0].raw >> 8), rec[0].raw);
            rec++;
            setRGB1(prim, (rec[0].raw >> 16), (rec[0].raw >> 8), rec[0].raw);
            rec++;
            setRGB2(prim, (rec[0].raw >> 16), (rec[0].raw >> 8), rec[0].raw);
            rec++;
            setRGB3(prim, (rec[0].raw >> 16), (rec[0].raw >> 8), rec[0].raw);
            rec++;
            n += 4;
            GFX_AddPrim(g_AreaDrawMode, sizeof(POLY_G4));
        } while (n != parts->head.count);
    }
    mode = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(g_AreaDrawMode, mode);
}

/* Draws the textured quads in part_list like the resident Area_DrawParts, but the origin depth adds func_801F0ADC of
 * the origin x and y, and every part draws in the area draw mode. */
MATCH void func_801F0488(ScenePart* part_list, s32 x, s32 y) {
    SVECTOR   pos;
    SVECTOR   rot;
    SVECTOR   part_rotation;
    SVECTOR   uv[4];
    MATRIX    matrix;
    long      flag;
    long      p;
    POLY_FT4* prim;
    s32       scale;
    s32       part_word_offset;
    s32       vertex_index;
    u32       packed_uv;
    u32       shifted_uv;
    u32*      part_words;
    SVECTOR*  vertex;
    s32       coordinate;
    s32       signed_coordinate;

    if ((Area_TestCondition(part_list[0].head.id) << 24) == 0) {
        return;
    }
    setVector(&pos, ((x - 0x80) << 0x7) + part_list[1].vertex.x * 2, ((y - 0x80) << 7) + part_list[1].vertex.y * 2, func_801F0ADC(pos.vx, pos.vy) + part_list[1].raw);
    setVector(&rot, (part_list[2].raw >> 0x14 & 0x3FF) * (scale = (g_FrameCount & 0xFFF) * 4), (part_list[2].raw >> 0xA & 0x3FF) * scale, (part_list[2].raw & 0x3FF) * scale);
    for (part_word_offset = 3; part_word_offset != (part_list[0].head.count); part_word_offset += 6) {
        PushMatrix();
        setVector(&part_rotation, (rot.vx + (((part_list[part_word_offset].raw) >> 0x12) & 0xFFC)) & ANGLE_MASK, (rot.vy + (((part_list[part_word_offset].raw) >> 8) & 0xFFC)) & ANGLE_MASK,
                  (rot.vz + (((part_list[part_word_offset].raw) & 0x3FF) * 4)) & ANGLE_MASK);
        RotTransMatrix(&pos, matrix, &flag);
        Camera_SetModelMatrix(&part_rotation, &matrix);
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        part_words = ((u32*)part_list) + part_word_offset;
        for (vertex_index = 0; vertex_index < 4; vertex_index++) {
            vertex     = &uv[vertex_index];
            packed_uv  = part_words[1 + vertex_index];
            coordinate = (packed_uv >> 0x14);
            vertex->vx = coordinate;
            if (coordinate & 0x200) {
                signed_coordinate = coordinate | (~0x3FF);
                vertex->vx        = signed_coordinate;
            }
            packed_uv  = part_words[1 + vertex_index];
            shifted_uv = packed_uv >> 0xA;
            coordinate = (shifted_uv & 0x3FF);
            vertex->vy = coordinate;
            if (shifted_uv & 0x200) {
                signed_coordinate = coordinate | (~0x3FF);
                vertex->vy        = signed_coordinate;
            }
            packed_uv  = part_words[1 + vertex_index];
            coordinate = (packed_uv & 0x3FF);
            vertex->vz = coordinate;
            if (packed_uv & 0x200) {
                signed_coordinate = coordinate | (~0x3FF);
                vertex->vz        = signed_coordinate;
            }
        }

        RotTransPers4(&uv[1], &uv[2], &uv[3], &uv[0], (long*)(&prim->x1), (long*)(&prim->x2), (long*)(&prim->x3), (long*)(&prim->x0), &p, &flag);
        Area_ApplyTileToQuad(part_list[part_word_offset + 5].raw, prim, 1);
        GFX_AddPrim(g_AreaDrawMode, sizeof(*prim));
        PopMatrix();
    }
}

/* Draws one sprite of a scene record as an FT4 primitive, like the resident Area_SceneDrawSprite, but the sprite stands
 * on the ground: its depth is half the ground height under its origin. */
MATCH void Area_SceneDrawGroundSprite(u8* record, s32 origin_x, s32 origin_y) {
    POLY_FT4* prim;
    u8*       frame;
    s32       z;
    s32       i;
    s32       n;
    s32       x;
    s32       y;
    long      depth;
    long      flag;

    if ((Area_TestCondition(FIELD(s16, record, 0x0)) << 24) == 0) {
        return;
    }
    setVector(g_ScratchPadVectors, ((origin_x - 0x80) << 0x7) + FIELD(s8, record, 7) * 2, ((origin_y - 0x80) << 7) + FIELD(s8, record, 0x6) * 2,
              -Area_HeightSample((g_ScratchPadVectors->vx + AREA_CELL_ORIGIN) << 9, (g_ScratchPadVectors->vy + AREA_CELL_ORIGIN) << 9) / 2);
    z = RotTransPers(g_ScratchPadVectors, (long*)D_1F800034_U16, &depth, &flag);
    if (((u32)(D_1F800034_U16[0] + 0x3C) & HALF_MASK) >= 0x1B9) {
        return;
    }
    if (((u32)(D_1F800034_U16[1] + 0x96) & HALF_MASK) >= 0x1C3) {
        return;
    }
    i = 0;
    if (z == 0) {
        return;
    }
    n = g_FrameCount % record[8];
    while (1) {
        if (n < record[0xA + i]) {
            break;
        }
        i++;
    }
    prim = (POLY_FT4*)g_GfxPrimCursor;
    n    = (u32)(record[9] + 5) >> 2;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    /* FAKE: integer address arithmetic keeps the retail add order and reuses the index register. */
    frame    = (u8*)((i << 3) + ((n << 2) + (s32)record));
    x        = D_1F800034_U16[0] - FIELD(s8, frame, 0x8) * 1125 / z;
    prim->x0 = prim->x2 = x;
    x += (s8)(FIELD(u32, frame, 0x8) >> 8) * 1125 / z;
    prim->x1 = prim->x3 = x;
    y                   = D_1F800034_U16[1] - FIELD(s8, frame, 0xA) * 1125 / z;
    prim->y0 = prim->y1 = y;
    y += FIELD(s8, frame, 0xB) * 1125 / z;
    prim->y2 = prim->y3 = y;
    Area_ApplyTileToQuad(FIELD(u32, frame, 0xC), prim, 1);
    GFX_AddPrim(g_AreaDrawMode, sizeof(POLY_FT4));
}

/* The ground height under world point (x, y), read from the D_801F0DCC height grid. */
MATCH s32 func_801F0ADC(s32 x, s32 y) {
    s32 col;
    s32 row;
    /* FAKE: retail reserves 8 unused frame bytes. */
    FAKE_STACK_PADS(u8, 8);

    if (D_801F0CBC & 1) {
        col = ((y + 0x4000) >> 6) - D_801F0CC8 * 2;
        row = ((x + 0x4000) >> 6) - D_801F0CC4 * 2;
    } else {
        col = ((x + 0x4000) >> 6) - D_801F0CC4 * 2;
        row = ((y + 0x4000) >> 6) - D_801F0CC8 * 2;
    }
    if (((u32)col >= 0x1C) | ((u32)row >= 0x20)) {
        return 0;
    }
    if (((col | row) & 1) == 0) {
        return -((D_801F0DCC[(row >> 1) + 1][col >> 1] + D_801F0DCC[row >> 1][(col >> 1) + 1]) << 19) >> 16;
    } else if ((col & 1) && !(row & 1)) {
        return -((D_801F0DCC[(row >> 1) + 1][(col >> 1) + 1] + D_801F0DCC[row >> 1][(col >> 1) + 1]) << 19) >> 16;
    } else if (!(col & 1) && (row & 1)) {
        return -((D_801F0DCC[(row >> 1) + 1][(col >> 1) + 1] + D_801F0DCC[(row >> 1) + 1][col >> 1]) << 19) >> 16;
    } else {
        return -(D_801F0DCC[(row >> 1) + 1][(col >> 1) + 1] << 20) >> 16;
    }
}
