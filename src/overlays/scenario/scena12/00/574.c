#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F71B8(void) {
    SYS_DISPATCH_TASK(D_801FD184, 2, g_Self);
}

MATCH void func_801F71FC(void) {
    Actor* actor;

    D_801FD288.half    = (RANDOM_MASK(1)) << 15;
    actor              = SELF(Actor);
    actor->header.step = actor->header.step + 1;
}

#define SCENA12_STEP_COUNTER()                                                                      \
    {                                                                                               \
        s32    bits;                                                                                \
        u16    value;                                                                               \
        u32    high;                                                                                \
        u32    count;                                                                               \
        Actor* actor;                                                                               \
                                                                                                    \
        if (*g_ScriptVars == 1) {                                                                   \
            Actor_Clear();                                                                          \
            return;                                                                                 \
        }                                                                                           \
        high = (u16)D_801FD288.half >> 0xF;                                                         \
        if ((u32)(D_801FD288.half & BYTE_MASK) >= 0xC8U) {                                          \
            actor = g_Self;                                                                         \
            actor->header.step += 1;                                                                \
            return;                                                                                 \
        }                                                                                           \
        count = ((u32)(D_801FD288.half & 0x7F00) >> 8) + 1;                                         \
        value = D_801FD288.half;                                                                    \
        if (((high & BYTE_MASK) == 0 && count >= 30) || ((high & BYTE_MASK) != 0 && count >= 40)) { \
            count = 0;                                                                              \
            value += 1;                                                                             \
            if (SYS_TestFlag(g_SceneFlags, 0x14) != 0) {                                            \
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 10));                                           \
            }                                                                                       \
        }                                                                                           \
        bits = high << 15;                                                                          \
        bits |= count << 8;                                                                         \
        D_801FD288.half = (value & BYTE_MASK) | bits;                                               \
    }

MATCH void func_801F7240(void) {
    SCENA12_STEP_COUNTER();
}

/* The statements of func_801F7348 and func_801F7518, byte-identical twins: unless a message is pending, the entry state is 4 or scene flag 0x2E is set, queue script step 5 with g_ScenarioState.step = 0x19, raise the script-active flag and clear the work. */
#define SCENA12_START_SCRIPT()                                                                                        \
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_GameEntryState != 4 && SYS_TestFlag(g_SceneFlags, 0x2E) == 0) { \
        g_ScenarioState.step     = 0x19;                                                                              \
        g_ScenarioState.state_04 = 5;                                                                                 \
        g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;                                                                       \
        Actor_Clear();                                                                                                \
    }

MATCH void func_801F7348(void) {
    SCENA12_START_SCRIPT();
}

MATCH void func_801F73CC(void) {
    SYS_DISPATCH_TASK(D_801FD190, 2, g_Self);
}

MATCH void func_801F7410(void) {
    SCENA12_STEP_COUNTER();
}

MATCH void func_801F7518(void) {
    SCENA12_START_SCRIPT();
}

MATCH void func_801F759C(void) {
    func_801F75EC();
    if ((g_GameStateIndex != GAME_REQUEST_MESSAGE) && (g_GameEntryState != 4)) {
        Actor_Clear();
    }
}

MATCH void func_801F75EC(void) {
    char* buffer;
    char* fmt;
    u8    value;

    buffer = (char*)g_UiTextFormatBuffer;
    Menu_DrawHeaderBar(138, 30, 45, 20, 1u);
    value = D_801FD288.bytes[0];
    fmt   = D_801F6C04;
    TEXT_Format(buffer, fmt, value);
    UI_TextDrawAscii(0x95, 0x22, 0, buffer);
}

#include "shared/Menu_DrawHeaderBar.h"

MATCH void func_801F7BA8(void) {
    SYS_DISPATCH_TASK(D_801FD198, 1, g_Self);
}

MATCH void func_801F7BEC(void) {
    Actor* actor;

    actor              = SELF(Actor);
    actor->screen_x    = 0;
    actor->header.mode = actor->header.mode + 1;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 21));
}

/* Places the task on an orbit round the focus point by its angle; at frame 330 it plays a sound and moves on. */
MATCH void func_801F7C24(void) {
    VECTOR from;
    VECTOR to;
    s32    cos;

    setVector(&from, -0x6000, -0x12000, 1 << 24);
    cos                      = rcos(SELF(Actor)->angle_z);
    to.vx                    = (from.vx * cos - from.vy * rsin(SELF(Actor)->angle_z)) >> 12;
    cos                      = rsin(SELF(Actor)->angle_z);
    to.vy                    = (from.vx * cos + from.vy * rcos(SELF(Actor)->angle_z)) >> 12;
    to.vz                    = from.vz;
    SELF(Actor)->pos.x.fixed = g_PartyActors[1].pos.x.fixed + to.vx;
    SELF(Actor)->pos.y.fixed = g_PartyActors[1].pos.y.fixed + to.vy;
    SELF(Actor)->pos.z.fixed = g_PartyActors[1].pos.z.fixed + to.vz;
    setVector(SELF(Actor), g_PartyActors[1].pos.x.fixed + to.vx - ((s16)SELF(Actor)->screen_x << 15), g_PartyActors[1].pos.y.fixed + to.vy, g_PartyActors[1].pos.z.fixed + to.vz);
    func_801F7E34(&SELF(Actor)->pos.x.fixed, &SELF(Actor)->vx, 0x40);
    SELF(Actor)->screen_x += 1;
    if ((s16)SELF(Actor)->screen_x == 330) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 22));
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801F7E14(void) {
    Actor_Clear();
}

MATCH void func_801F7E34(s32* pos_a, s32* pos_b, u8 shade) {
    LINE_F2* prim;
    DVECTOR  xy;
    MATRIX   matrix;

    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Camera_SetMatrix(&matrix);
    prim = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(prim);
    SetSemiTrans(prim, 1);
    Camera_ProjectPoint(pos_a, &xy);
    setXY0(prim, (u16)xy.vx, (u16)xy.vy);
    Camera_ProjectPoint(pos_b, &xy);
    prim->x1 = (u16)xy.vx;
    prim->y1 = (u16)xy.vy;
    setRGB0(prim, shade, shade, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F2));
}

MATCH void func_801F7F28(void) {
    SYS_DISPATCH_BYTE(D_801FD1B8, D_80146872);
}

MATCH void func_801F7F64(void) {
    D_80146872 = 1;
}
