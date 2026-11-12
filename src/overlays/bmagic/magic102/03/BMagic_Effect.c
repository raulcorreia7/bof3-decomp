#include "magic102_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

INCLUDE_ASM(func_801EEC80);

/* Counts this effect's steps; at the tick limit it re-arms the counter, steps
 * the magic, and flips the area camera's vertical offset with the frame parity. */
MATCH void func_801EF218(void) {
    PartyMember* work;
    u8           tick;

    work         = g_Task;
    tick         = work->unk_09 + EFFECT_TICK_INCREMENT;
    work->unk_09 = tick;
    if (tick >= EFFECT_TICK_LIMIT) {
        g_Task->unk_09 = 0;
        g_Task->header.mode += 1;
    }
    g_AreaCameraOffsetY      = (((g_FrameCount & 0x1) * 2) - 1) * (g_Task->unk_09 >> 1);
    g_AreaCameraRefreshCount = 2;
}

INCLUDE_ASM(func_801EF2B8);

INCLUDE_ASM(func_801EFD7C);

INCLUDE_ASM(func_801EFEFC);

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
            mode = getTPage(1, rec[4].color.tpage, 320, 256);
            /* Written out: GFX_AddDitheredDrawMode moves the g_AreaDrawMode load. */
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, mode, NULL);
            GFX_AddPrim(g_AreaDrawMode, sizeof(DR_MODE));
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
    mode = getTPage(1, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, mode, NULL);
    GFX_AddPrim(g_AreaDrawMode, sizeof(DR_MODE));
}

/* Draws the textured quads in part_list like the resident Area_DrawParts, but the origin depth adds func_801F0ADC of
 * the origin x and y, and every part draws in the area draw mode. */
MATCH void func_801F0488(u8* part_list, s32 x, s32 y) {
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

    if ((Area_TestCondition(((ScenePart*)part_list)[0].head.id) << 24) == 0) {
        return;
    }
    pos.vx = ((x - 0x80) << 0x7) + FIELD(s8, part_list, 7) * 2;
    pos.vy = ((y - 0x80) << 7) + FIELD(s8, part_list, 0x6) * 2;
    pos.vz = func_801F0ADC(pos.vx, pos.vy) + ((ScenePart*)part_list)[1].raw;
    rot.vx = (((ScenePart*)part_list)[2].raw >> 0x14 & 0x3FF) * (scale = (g_FrameCount & 0xFFF) * 4);
    rot.vy = (((ScenePart*)part_list)[2].raw >> 0xA & 0x3FF) * scale;
    rot.vz = (((ScenePart*)part_list)[2].raw & 0x3FF) * scale;
    for (part_word_offset = 3; part_word_offset != (FIELD(u8, part_list, 0x2u)); part_word_offset += 6) {
        PushMatrix();
        part_rotation.vx = (rot.vx + (((((ScenePart*)part_list)[part_word_offset].raw) >> 0x12) & 0xFFC)) & ANGLE_MASK;
        part_rotation.vy = (rot.vy + (((((ScenePart*)part_list)[part_word_offset].raw) >> 8) & 0xFFC)) & ANGLE_MASK;
        part_rotation.vz = (rot.vz + (((((ScenePart*)part_list)[part_word_offset].raw) & 0x3FF) * 4)) & ANGLE_MASK;
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
        func_80155560(((ScenePart*)part_list)[part_word_offset + 5].raw, prim, 1);
        GFX_AddPrim(g_AreaDrawMode, sizeof(*prim));
        PopMatrix();
    }
}

/* Draws one sprite of a scene record as an FT4 primitive, like the resident Area_DrawSceneSprite, but the sprite stands
 * on the ground: its depth is half the ground height under its origin. */
MATCH void Area_DrawGroundSceneSprite(u8* record, s32 origin_x, s32 origin_y) {
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
    D_1F800014->vx = ((origin_x - 0x80) << 0x7) + FIELD(s8, record, 7) * 2;
    D_1F800014->vy = ((origin_y - 0x80) << 7) + FIELD(s8, record, 0x6) * 2;
    D_1F800014->vz = -Area_SampleHeight((D_1F800014->vx + 0x4000) << 9, (D_1F800014->vy + 0x4000) << 9) / 2;
    z              = RotTransPers(D_1F800014, (long*)D_1F800034_U16, &depth, &flag);
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
    func_80155560(FIELD(u32, frame, 0xC), prim, 1);
    GFX_AddPrim(g_AreaDrawMode, sizeof(POLY_FT4));
}

INCLUDE_ASM(func_801F0ADC);
