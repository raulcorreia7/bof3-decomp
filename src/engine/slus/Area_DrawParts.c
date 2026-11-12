#include "engine/slus/slus.h"

/* draws the textured quads in part_list: builds the local position
 * and rotation vectors, then per 0x18-byte part pushes the GTE
 * matrix, rotates the part, emits a POLY_FT4 with four packed texture
 * coordinates and appends it with the part's draw mode.
 */
MATCH void Area_DrawParts(u8* part_list, s32 x, s32 y) {
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
    s32       draw_mode;

    if ((Area_TestCondition(((ScenePart*)part_list)[0].head.id) << 24) == 0) {
        return;
    }
    pos.vx = ((x - 0x80) << 0x7) + FIELD(s8, part_list, 7) * 2;
    pos.vy = ((y - 0x80) << 7) + FIELD(s8, part_list, 0x6) * 2;
    pos.vz = ((ScenePart*)part_list)[1].raw;
    scale  = (g_FrameCount & 0xFFF) * 4;
    rot.vx = (((ScenePart*)part_list)[2].raw >> 0x14 & 0x3FF) * scale;
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
        draw_mode = 6;
        if ((((ScenePart*)part_list)[part_word_offset + 5].raw & 0x40000000) == 0) {
            draw_mode = g_AreaDrawMode;
        }
        GFX_AddPrim(draw_mode, sizeof(*prim));
        PopMatrix();
    }
}
