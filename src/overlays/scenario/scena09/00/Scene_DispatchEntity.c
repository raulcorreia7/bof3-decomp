#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F73A0(void) {
    Scene_ClearWorkRows();
    func_801F76D0();
    g_Task->timer = 0xFF;
    g_Task->header.mode++;
}

MATCH void func_801F73F0(void) {
    if (!(func_801F75BC() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F7424(Actor* actor) {
    POLY_F3* poly;
    FAKE_STACK_PADS(u8, 48); /* FAKE: retail frame reserves 48 bytes no statement uses. */

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK, 0);
    Area_AddCellPrim(actor->unk_18, actor->unk_1C, 0, sizeof(DR_MODE));
    poly = (POLY_F3*)g_GfxPrimCursor;
    SetPolyF3(poly);
    SetSemiTrans(poly, 1);
    Camera_ProjectPoint(&actor->unk_18, POLY_XY(poly, 0));
    poly->x1 = poly->x0 + D_801FE38C[actor->unk_04].dx1;
    poly->y1 = poly->y0 + D_801FE38C[actor->unk_04].dy1;
    poly->x2 = poly->x0 + D_801FE38C[actor->unk_04].dx2;
    poly->y2 = poly->y0 + D_801FE38C[actor->unk_04].dy2;
    setRGB0(poly, 0, actor->unk_03, actor->unk_03);
    Area_AddCellPrim(actor->unk_18, actor->unk_1C, -2, sizeof(POLY_F3));
}

/* func_801F7574 */
MATCH void Scene_ClearWorkRows(void) {
    SparkParticle* row;
    u8             i;

    row = (SparkParticle*)(MEM_PTR(u8, AREA_WORK + 0x800) + g_Task->unk_06 * 0x500);
    for (i = 0; i < SCENE_SPARK_COUNT; i++, row++) {
        row->header.active = 0;
    }
}

MATCH s32 func_801F75BC(void) {
    MATRIX         camera;
    SparkParticle* row;
    u8             i;
    u8             life;
    s32            alive;

    Camera_SetMatrix(&camera);
    alive = 0;
    row   = (SparkParticle*)(MEM_PTR(u8, AREA_WORK + 0x800) + g_Task->unk_06 * 0x500);
    for (i = 0; i < SCENE_SPARK_COUNT; row++, i++) {
        if (row->header.active == 0) {
            continue;
        }
        row->pos.vx += row->velocity.vx;
        row->pos.vy += row->velocity.vy;
        row->pos.vz += row->velocity.vz;
        row->velocity.vz -= 0x40000;
        row->header.shade -= 4;
        row->frame       = rand() & 7;
        life             = row->header.life - 1;
        row->header.life = life;
        if (life == 0) {
            row->header.active = 0;
        }
        func_801F7424(row);
        alive = 1;
    }
    return alive;
}

MATCH void func_801F76D0(void) {
    SparkParticle* spark;
    u8             mode;
    u8             i;

    FAKE_STACK_PADS(u8, 0x20); /* FAKE: retail reserves 32 unused stack bytes. */
    mode  = g_Task->unk_06;
    spark = MEM_PTR(SparkParticle, AREA_WORK + 0x800 + mode * 0x500);
    i     = 0;
    do {
        if (g_Task->unk_06 == 0) {
            spark->pos.vx = ((rand() & 0x1FF) << 8) + 0x120000;
            spark->pos.vy = ((rand() & 0x1FF) << 8) + 0x2E8000;
            spark->pos.vz = TO_COORD(2112) - ((spark->pos.vx - 0x120000) << 7);
            setVector(&spark->velocity, (spark->pos.vx - 0x130000) >> 4, (spark->pos.vy - 0x2F8000) >> 4, (-(rand() & 0xFF)) << 5);
            spark->velocity.vx -= 0x800;
        } else {
            spark->pos.vx = ((rand() & 0x1FF) << 8) + 0x78000;
            spark->pos.vy = ((rand() & 0x1FF) << 8) + 0x318000;
            spark->pos.vz = TO_COORD(2112) - ((spark->pos.vy - 0x318000) << 7);
            setVector(&spark->velocity, (spark->pos.vx - 0x88000) >> 4, (spark->pos.vy - 0x328000) >> 4, (-(rand() & 0xFF)) << 5);
            spark->velocity.vy = -0x800;
        }
        spark->header.active = 1;
        spark->header.life   = 0x18;
        spark->header.type   = 0;
        spark->header.shade  = 0x60;
        spark->frame         = rand() & 7;
        spark++;
        i++;
    } while (i < 32);
}

MATCH void func_801F78D0(void) {
    SYS_DISPATCH_BYTE(D_801FE3E0, D_80146872);
}

MATCH void func_801F790C(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7920);

MATCH void func_801F83D8(void) {
    SYS_DISPATCH_BYTE(D_801FE3EC, g_ScenarioState.state_04);
}

MATCH void func_801F8414(void) {
}

MATCH void func_801F841C(void) {
    u8* step = &g_ScenarioState.step_05;

    switch (*step) {
        case 0:
            *step = 1;
            SYS_SetFlag(g_SceneFlags, 0);
            Game_RequestAreaChange(AREA_ID_EYGNOCK_ROAD, TO_COORD_HALF(31), TO_COORD(76), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
            break;
        case 1:
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            *step           = 2;
            break;
        case 2:
            if (*g_ScriptVars == 0x11) {
                SYS_SetFlag(g_SceneFlags, 1);
                Game_ClearScriptActive();
                *step                    = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}
