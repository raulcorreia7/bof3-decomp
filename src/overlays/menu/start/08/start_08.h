#ifndef OVERLAY_ETC_START_08_H
#define OVERLAY_ETC_START_08_H

#include "game/character.h"
#include "shared/etc.h"
#include <string.h>
#include <stdio.h>

/* The save-image buffer the card writer clears and then checksums. */
#define SAVE_IMAGE_ADDR 0x800C1A00u
#define g_SceneFlags    ((void*)g_SceneFlags)

/* Draw the scene timer sprite and count down; on zero advance the cue counter.
 * A bare statement macro: the member declares `timer` and `count`. Kept: tested
 * as an inline, the member's local frame disappears and the bytes move; the
 * do/while form moves bytes too. */
#define ETC_TICK_SCENE_TIMER()      \
    Menu_DrawClutStrip(D_80144953); \
    timer  = &D_80148654;           \
    count  = *timer - 1;            \
    *timer = count;                 \
    if (count == 0) {               \
        D_80148651 += 1;            \
    }

/* Step the master panel right and clamp it at the given x. Kept: as an inline
 * the limit is an argument used after the branch and the store moves (tested;
 * bytes differ in the member). */
#define MENU_CLAMP_PANEL(limit)                  \
    do {                                         \
        MenuPanelTask* panel;                    \
        u16            next;                     \
                                                 \
        panel    = g_MenuPanelTaskCurrent;       \
        next     = panel->x + MENU_PANEL_STEP_X; \
        panel->x = next;                         \
        if ((s16)next >= 17) {                   \
            panel->x     = (limit);              \
            panel->state = 0;                    \
        }                                        \
    } while (0)

/* The start menu's skill order screen, which runs in the battle selection
 * work area at 0x80148570: func_801D8908 moves the cursor and swaps two
 * skills, func_801D9350 packs the empty slots to the end. func_80166AE4
 * resolves the character's ability list by party slot and ability group. */
typedef struct SkillOrder {
    u8 pad_00[0x0A];
    u8 party_slot;    /* 0x0A; character whose ability list is shown */
    u8 ability_group; /* 0x0B; healing, assist, attack or skill list */
    u8 cursor;        /* 0x0C; index in the list */
    u8 swap_cursor;   /* 0x0D; first picked skill, 0xFF until picked */
    u8 pad_0E[0x46];
    u8 unk_54;
} SkillOrder;

ASSERT_SIZE(SkillOrder, 0x55);
ASSERT_OFFSET(SkillOrder, party_slot, 0x0A);
ASSERT_OFFSET(SkillOrder, ability_group, 0x0B);
ASSERT_OFFSET(SkillOrder, cursor, 0x0C);
ASSERT_OFFSET(SkillOrder, swap_cursor, 0x0D);
ASSERT_OFFSET(SkillOrder, unk_54, 0x54);

/* The start overlay's step counter at 0x80143B92. func_801E3EC4 takes its
 * address before the increment (lui/addiu of the base, then lhu/shu through
 * it), so that unit needs the one-element table view; every other reader
 * takes the scalar cell. */
typedef union CampMenuStepCounter {
    u16 value;
    u16 rows[1];
} CampMenuStepCounter;

ASSERT_SIZE(CampMenuStepCounter, 2);
ASSERT_OFFSET(CampMenuStepCounter, rows, 0);

/* D_80143F00 */
extern u16             g_GameAreaId;
extern u8              D_80144F57;
extern u16             D_80145594[];
extern s16             D_80145ABE;
extern u8              D_80145FCC[][BATTLE_PARTY_STRIDE];
extern u8              D_80148477;
extern u8              D_80148480;
extern s16             D_80148484;
extern u8              D_8014849B;
extern s16             D_801484A8;
extern s8              D_801484BD;
extern s8              D_801484BE;
extern s8              D_801484BF;
extern s16             D_801484C0;
extern s16             D_801484C2;
extern s16             D_801484CC;
extern s8              D_801484E1;
extern s8              D_801484E2;
extern s8              D_801484E3;
extern s16             D_801484E4;
extern s16             D_801484E6;
extern u8              D_801484EB;
/* The start-menu panel: slot 13 of g_MenuPanelTasks (0x80148504), the shared
 * choice-list view. The retail addresses the cells one by one, so they keep
 * their own symbols below; each is the cell the shared record names. */
extern u8*             D_80148500;
extern MenuChoicePanel D_80148504;
extern s8              D_80148505;
extern s8              D_80148506;
extern s8              D_80148507;
extern s16             D_80148508; /* signed scalar view of the panel's x */
extern s16             D_8014850A; /* signed scalar view of the panel's y */
extern u8              D_8014850E; /* the panel's group */
extern u8              D_8014850F; /* the panel's group first entry */
extern u8              D_80148510; /* the panel's group cursor */
extern s8              D_80148511; /* signed scalar view of the panel's drawn cursor */
extern s16             D_80148514;
extern s16             D_80148516;
extern u8*             D_80148524;
extern u8              D_80148528;
extern s8              D_80148529;
extern s8              D_8014852A;
extern s16             D_8014852C;
extern s16             D_8014852E;
extern u8              D_80148530;
extern u8              D_80148532;
extern s8              D_80148533;
extern u8              D_80148534;
extern u8              D_80148535;
extern s8              D_8014854D;
extern s8              D_8014854E;
extern s8              D_8014854F;
extern s16             D_80148550;
extern s16             D_80148552;
extern u8              D_80148556;
/* D_80148570: the battle choice panel record, also the skill-order work area. */
extern u8              g_BattleChoicePanel[];
extern s8              D_80148571;
extern u8              D_80148572;
extern s16             D_80148576;
extern u8              D_80148594;
extern u8              D_80148595;
extern u8              D_80148596;
extern u16             D_80148598;
extern u16             D_8014859A;
extern u16             D_801485BC;
extern u16             D_801485BE;
extern u8              D_801485DD;
extern u8              D_801485DE;
extern s16             D_80148628; /* the computed bar length; func_801D8188 stores it with sh at 0x801D81FC */
extern u16             D_8014862A; /* the second bar length; func_801D8188 stores it with sh at 0x801D8210 */
extern u8              D_80148653;
extern u8              D_80148654;
extern u8              D_8014865F;
extern u8              D_80148660;
extern s8              D_80148662;
extern u8              D_80148663;
extern s8              D_80148664;
extern u8              D_80148665;
extern s8              D_80148668;
extern s8              D_80148669;
extern s8              D_8014866A;
extern u8              D_80148694;
/* The save/card probe's result word; the start rows read its low byte with
 * LOBU, and etc/start/09 and etc/shop/00 test and store the whole word. */
extern u8              D_8018E990[];
extern u8*             D_801C893C[];
extern u8*             D_801C8950[];
/* D_801D0C4C */
extern char            g_MenuStatFormat[4];
/* D_801D0C70 */
extern char            g_MenuZennyFormat[4];
extern char            D_801D0C74[];
extern char            D_801D0DAC[];
extern char            D_801D0DB0[];
extern u8              D_801D0DBC[4];
extern u8              D_801D0DC0[4];
extern u8              D_801D0DC4[4];
/* D_801D0EB0 */
extern u8              s_RowCaptionTags[24];
extern char            g_SaveFileNameFormat[];
extern char            D_801D0F14[];
/* The party records the New Game screen starts from. */
extern Character       D_801EB514[7];
extern Character       D_801EB990;
extern u8              D_801EBA34[][2];
/* D_801EC354 */
extern u8              s_CampMenuPanelIds[8];
extern Callback        D_801EC35C[9];
extern Callback        D_801EC380[];
extern u8              D_801EC38C[];
extern Callback        D_801EC394[5];
extern Callback        D_801EC3A8[11];
extern Callback        D_801EC3D4[];
extern Callback        D_801EC400[7];
extern Callback        D_801EC41C[];
extern u16             D_801EC440[];
/* D_801EC458 */
extern u8              s_EquipSlotCategories[8];
extern Callback        D_801EC460[];
extern Callback        D_801EC498[];
extern Callback        D_801EC4B0[5];
extern Callback        D_801EC4C4[];
extern Callback        D_801EC518[6];
extern Callback        D_801EC530[3];
extern Callback        D_801EC53C[];
extern Callback        D_801EC578[];
extern Callback        D_801EC58C[];
/* Panel and caption resources. A glyph row is a run of 3-byte records
 * {s8 dx, s8 dy, u8 glyph} in 8-pixel units that UI_DrawSpriteRun draws until
 * glyph 0xFF; MENU_CAPTION_GLYPH_2 packs several such runs and the label
 * strings in one row. The icon and portrait rows are UI_DrawText glyph
 * strings and an atlas of s16 cells followed by label strings. Both stay byte
 * arrays: a row's size includes alignment padding past its payload (44 bytes
 * for a 42-byte run, 688 for a 687-byte bank), and a typed record array would
 * need the split data to own that padding. */
/* D_801EC690 */
extern u8              MENU_CAPTION_GLYPH_2[688];
extern u8              D_801EC754[];
extern u8              D_801EC76C[];
extern u8              D_801EC784[];
extern u8              D_801EC790[];
extern u8              D_801EC854[];
/* D_801EC94C */
extern u8              g_MenuLabelAgility[4];
extern u8              g_MenuEquipRowIcons[8]; /* equipment-row sprites. @source: read:func_801DBF04 */
extern u8              g_MenuLabelEquip[8];    /* the equipment panel caption. @source: read:func_801DBF04 */
/* D_801EC96C */
extern u8              g_MenuPortraitAtlas[96];
/* D_801EC9CC */
extern u8              MENU_CAPTION_ICON[792];
extern s32             D_801ECC98[];
extern Callback        D_801ECCF8[];
extern Callback        D_801ECD1C[];
/* D_801ED100 */
extern u8              s_CampMenuState[8];
extern Callback        D_801ED11C[7];
extern Callback        D_801ED138[4];
extern Callback        D_801ED148[17];
extern u8              D_801ED18C;
/* D_801ED1D8 */
extern u8              s_PanelIconSelectors[24];
/* D_801ED1F0 */
extern u8              s_PanelIconValues[228];
extern s32 (*D_801ED224[])(u8 caster_index, u8 target_index, u8 use_battle_record);
extern s32 (*D_801ED24C[])(u8 slot_index, u8 record_value);
/* D_801ED2D4 */
extern u8       g_SaveRecordTypeCommands[92];
extern Callback D_801ED330[21];
extern Callback D_801ED384[11];
extern Callback D_801ED3B0[3];
extern Callback D_801ED3BC[3];
extern Callback D_801ED3C8[6];
extern void (*D_801ED3D4[])(void);
extern Callback D_801ED3E0[7];
extern Callback D_801ED3FC[3];
extern Callback D_801ED408[3];
extern Callback D_801ED414[3];
extern Callback D_801ED420[3];
extern u16      D_801ED42C[1];
extern u16      D_801ED42E[];
extern Callback D_801ED43C[3];
extern Callback D_801ED448[5];
extern Callback D_801ED45C[];
extern u8       D_801ED468[];
extern u8       D_801ED48C[];
extern u8       D_801ED498[];
extern u32      D_801ED534[];
extern u8       D_801ED560[][6];
extern Callback D_801ED58C[5];
extern Callback D_801ED5A0[5];
extern Callback D_801ED5B4[5];
extern Callback D_801ED5C8[];
extern Callback D_801ED5E4[];
/* D_801ED610 */
extern u8       s_PartyCharacterIds[3];
extern u8       D_801ED613[];
extern s8       D_801ED618;
extern u8       D_801ED620;
extern u8       D_801ED63C;
extern u8       D_801ED63D;
extern u8       D_801ED63E;
extern u8       D_801ED63F;
extern u8       D_801ED640;
extern u8       D_801ED641;
extern s8       D_801ED648;
/* The start overlay's slot rows (three bytes per slot) and its byte table;
 * every reader indexes or walks them as bytes. */
extern u8       D_801ED680[];
extern u8       D_801ED68C;
extern u8       D_801ED690[];
extern u8       D_801ED694[][2];
extern u8       D_801ED695[][2];
extern u8       D_801ED6A0;
extern u8*      D_801ED7D8;
extern u8       D_801ED7DC;
extern s8       D_801ED7E0;
extern s8       D_801ED7E4;
extern u8       D_801ED7E8;
extern u8       D_801ED7EC;
extern s8       D_801ED7F0;
extern u8       D_801ED7F4;
extern u8       D_801ED7F8;
extern u8       D_801ED860;
extern u8       D_801ED864;
extern u8       D_801ED868;
extern u8       D_801ED86C;
extern u8       D_801ED870;
extern u8       D_801ED890;
extern u8       D_801ED891;
/* D_801ED894 */
extern u8       s_ChoiceMenuValues[8];
/* D_801ED89C */
extern u8       s_ChoiceMenuCursors[12];
/* D_801ED8A8 */
extern u8       s_SkillOrderCursors[4][4];
/* D_801ED8B8 */
extern u8       s_SkillOrderGroups[4][6];
/* D_801ED8D0 */
extern u8       s_SkillOrderKinds[3][6];
extern Callback g_MenuCampSubFuncs[5];
extern Callback g_MenuCampFuncs[5];

/* Shared calls the start-screen units make: the main executable's window,
 * input, resource and sound helpers, and the game overlay's draw helpers. */
/* func_8014FF0C */
void        UI_DrawAsciiString(s16 left, s16 top, s32 flags, u8* text);
/* func_801650B4 */
extern bool Party_AddItem(s32 category, u8 item, u8 amount, s32 unused);
extern bool Char_RestoreHp(s32 character_index, s32 amount, s32 use_battle_copy);
extern s32  Char_RestoreAp(s32 character_index, s32 amount, s32 use_battle_copy);
/* func_8016546C */
extern s32  Char_AddCappedStat(u16* value, s32 delta);
extern s16  Char_AddStat(u16* value, s16 delta);
extern u32  Char_ClearStatus(u8 index, u16 mask, u8 mode);
/* Draws one sprite at (x, y); defined in the game overlay (emi/etc/game/00). */
void        UI_DrawSprite(s16 x, s16 y, u8 sprite_id, u8 flags);
bool        func_801AF494(u8 predicate_kind, u8 record_bit, u8 record_kind, u8 record_index);
s32         func_801B6470(u8 arg0);
/* func_801BDB7C */
extern u8   Party_CountOrder(u8 mode);
void        func_801C1254(s32 ability_id, s32 slot_index);
/* The start overlay's handler tables call these functions. */
void        func_801D177C(void);
void        func_801D1B24(void);
extern void func_801D1FDC(void);
s32         func_801D2190(void);
void        func_801D21F4(void);
void        func_801D2410(void);
void        func_801D244C(void);
void        func_801D24AC(void);
void        func_801D2564(void);
void        func_801D27CC(void);
void        func_801D28C8(void);
extern void func_801D2AC8(void);
void        func_801D2DAC(void);
void        func_801D2DE8(void);
void        func_801D2E48(void);
void        func_801D2EAC(void);
void        func_801D3174(void);
void        func_801D3768(void);
void        func_801D3848(void);
void        func_801D40D8(void);
void        func_801D42F0(void);
void        func_801D455C(void);
void        func_801D4564(void);
void        func_801D485C(void);
/* func_801D4A30 */
extern void Menu_SwapBytes(u8* first, u8* second);
void        func_801D4A44(void);
void        func_801D4B44(void);
void        func_801D4C68(void);
void        func_801D4D8C(void);
void        func_801D4EA4(void);
void        func_801D4FCC(void);
void        func_801D5114(void);
extern void func_801D528C(void);
void        func_801D52AC(void);
void        func_801D6E6C(void);
s32         func_801D70EC(void);
void        func_801D7204(void);
void        func_801D8CC8(void);
void        func_801D8D64(void);
void        func_801D8DC8(void);
void        func_801D902C(void);
void        func_801D90A8(void);
void        func_801D9110(void);
/* func_801D933C */
extern void Menu_SwapBytes_801D933C(u8* first, u8* second);
extern void func_801D9350(void);
void        func_801D970C(void);
void        func_801D9748(void);
void        func_801D98BC(void);
void        func_801D9AF0(void);
void        func_801D9B2C(void);
void        func_801D9BDC(void);
void        func_801DA27C(void);
void        func_801DA320(void);
void        func_801DA984(void);
void        func_801DAA68(void);
/* func_801DAC08 */
void        Menu_SwapBytes_801DAC08(u8* first, u8* second);
extern void func_801DB510(void);
void        func_801DB550(void);
void        func_801DB5AC(void);
extern void func_801DBF04(s16 x, s16 y, u8 record_index);
extern void func_801DC150(s16 x, s16 y, u8 character_index, s32 layout);
extern s32  func_801DCDB8(u16, u16, u8, u8, s32);
extern void Menu_DrawCommandRow(s16 x, s16 y, u8 row, u8 selected, s32 unused);
/* func_801DB764 */
void        Menu_DrawCharacterWindow(u16 x, u16 y, u8 character_slot, u8 shaded, s32 unused);
/* func_801DEEE8 */
void        Menu_DrawEquipStatWindow(s16 x, s16 y, s32 character_slot, s32 equip_slot, u8 item_id);
/* func_801DF6EC */
void        Menu_DrawWindowFrame(s16 x, s16 y, s32 width, s32 height);
/* func_801E2898 */
void        Menu_DrawOptionRow(s32 x, s32 y, s32 option_index, s32 select_step);
/* func_801E33E8 */
u8*         Menu_DrawGlyphAt(s16 x, s16 y, s32 color, u8* cursor, s32 glyph_left, s32 glyph_right);
extern void func_801DFBF4(MenuPanelTask* task);
extern void func_801E0354(MenuPanelTask* task);
extern void func_801E0A70(MenuPanelTask* task);
/* func_801E11A8 */
void        SAVE_DrawSlot(u8 index, s32 left, s32 top, u8* entry);
extern void func_801E14A8(s32 x, s32 y, u8 flags, u8 row, u8 active);
void        func_801E16BC(void);
void        func_801E18D0(void);
void        func_801E1C20(void);
void        func_801E206C(void);
void        func_801E2408(void);
extern void func_801E2668(s32 icon_kind, s32 icon_x, s32 icon_y);
extern void func_801E26A8(s32 x, s32 y);
void        func_801E3EC4(void);
void        func_801E4024(void);
void        func_801E4060(void);
void        func_801E40A0(void);
void        func_801E411C(void);
void        func_801E4288(void);
void        func_801E4318(void);
void        func_801E441C(void);
void        func_801E45CC(void);
void        func_801E462C(void);
void        func_801E4670(void);
void        func_801E46F8(void);
void        func_801E4744(void);
void        func_801E4E8C(void);
void        func_801E4ED4(void);
void        func_801E4F10(void);
void        func_801E4F50(void);
void        func_801E4FFC(void);
void        func_801E5078(void);
void        func_801E524C(void);
void        func_801E5320(void);
void        func_801E54A4(void);
void        func_801E55B8(void);
void        func_801E5674(void);
void        func_801E5738(void);
/* func_801E5A00 */
void        SAVE_RunLoadVerify(void);
void        func_801E5BCC(void);
void        func_801E5C68(void);
void        func_801E5E30(void);
void        func_801E5F34(void);
/* func_801E5FD4 */
void        SAVE_RunLoadRestore(void);
/* func_801E62A8 */
void        Camp_EnterMainLoop(void);
extern void func_801E6388(s32 overlay_x, s32 overlay_y);
extern void Start_DrawNameEntryGrid(u8 page, s32 grid_x, s32 grid_y);
extern s32  func_801E6784(u8 page, s32 x, s32 y);
extern u8   func_801E715C(s32 range_low, s32 range_high, s32 draw_count);
extern void func_801E7210(u32 slot_index);
s32         func_801E7D20(s32 character_index, s32 target_index, s32 ability_id, s32 use_battle_record);
s32         func_801E8C9C(u8 slot_index, u8 record_kind, u8 record_value);
void        func_801E8D58(void);
void        func_801E8D60(void);
extern void func_801E8DB4(MenuPanelTask* task);
void        func_801E8EA8(void);
void        func_801E8EE8(void);
void        func_801E8F28(void);
void        func_801E8F68(void);
void        func_801E8FE8(void);
void        func_801E9040(void);
void        func_801E9080(void);
void        func_801E90C0(void);
void        func_801E9100(void);
void        func_801E9140(void);
void        func_801E91A4(void);
void        func_801E91E4(void);
void        func_801E9224(void);
void        func_801E9284(void);
void        func_801E92C4(void);
void        func_801E9304(void);
void        func_801E94D4(void);
void        func_801E9514(void);
void        func_801E9554(void);
void        func_801E964C(void);
void        func_801E968C(void);
void        func_801E96CC(void);
void        func_801E9748(void);
void        func_801E9788(void);
void        func_801E97E0(void);
void        func_801E9820(void);
void        func_801E9878(void);
void        func_801E98B8(void);
void        func_801E98F8(void);
void        func_801E9974(void);
void        func_801E99B4(void);
void        func_801E99F4(void);
void        func_801E9A70(void);
void        func_801E9AB0(void);
void        func_801E9AF0(void);
void        func_801E9B6C(void);
void        func_801E9BAC(void);
void        func_801E9BEC(void);
void        func_801E9D18(void);
void        func_801E9D58(void);
void        func_801E9D98(void);
void        func_801E9DF4(void);
void        func_801E9EAC(void);
void        func_801E9F04(void);
void        func_801E9F5C(void);
void        func_801E9FB0(void);
void        func_801E9FF0(void);
void        func_801EA030(void);
void        func_801EA0B0(void);
void        func_801EA1C8(void);
void        func_801EA50C(void);
void        func_801EA598(void);
void        func_801EA5D8(void);
void        func_801EA618(void);
void        func_801EA658(void);
void        func_801EA698(void);
void        func_801EA6EC(void);
void        func_801EA72C(void);
void        func_801EA76C(void);
void        func_801EA7AC(void);
void        func_801EA7EC(void);
void        func_801EA840(void);
void        func_801EA880(void);
void        func_801EA8C0(void);
void        func_801EA900(void);
void        func_801EA940(void);
extern void func_801EAA14(MenuPanelTask* task);
void        func_801EAEC4(void);
extern void func_801EAF98(MenuPanelTask* task);
extern s8   CardAccessFile(s32 port, s32 name, s32 mode, s32 size, s32 offset);
extern s32  func_801EFCA8(char* prefix, u8 length);

/* Slide the master panel in to x 320 and stop it there. */
static inline void Menu_SlidePanelIn(void) {
    MenuPanelTask* task;

    task = g_MenuPanelTaskCurrent;
    task->x += MENU_PANEL_STEP_X;
    if ((s16)task->x >= 321) {
        task->x     = 320;
        task->state = 0;
    }
}

/* Retreat the master panel left and clamp it. */
static inline void MenuRetreatPanelXToMinus200(void) {
    MenuPanelTask* task;

    task = g_MenuPanelTaskCurrent;
    task->x -= MENU_PANEL_STEP_X;
    if ((s16)task->x < -200) {
        LOH(task->x) = -200;
        task->state  = 0;
    }
}

/* Step the master panel down and clamp it at the field limit. */
static inline void MenuAdvancePanelYField6(void) {
    MenuPanelTask* panel;
    u8*            bytes;
    u16            next;

    panel    = g_MenuPanelTaskCurrent;
    bytes    = (u8*)panel;
    next     = panel->y + MENU_PANEL_STEP_Y;
    panel->y = next;
    if ((s16)next >= bytes[10] * 0x36 + 0x3E) {
        panel->y     = bytes[10] * 54 + 62;
        panel->state = 0;
    }
}

/* func_801DDF70 */
s32              Char_GetExpForLevel(s32 character, s32 level);
extern s8        D_8014850C;
extern s8        D_8014850D;
extern u8        D_801485B9;
extern u8        D_801485BA;
extern s8        D_80148659;
extern u8        D_8014865A;
extern u8        D_80181B1A;
extern void      func_801AE214(s32 line_x, s32 line_y, s32 line_length, s32 line_mode);
extern u8*       D_801C8940;
extern u8*       D_801C8944;
extern char      D_801D0C50[8];
extern char      D_801D0C58[8];
extern char      g_MenuClockFormat[];
extern u8        D_801D0E20[];
extern s32       D_801D0E28;
extern s32       D_801D0EA8;
extern s8        D_801D0F18;
extern s8        D_801D0F1C;
extern s8        D_801D0F24;
/* func_801D15C0 */
void             Party_InitDefaults(void);
void             func_801D29A4(void);
extern void      func_801D2C7C(void);
void             func_801D2D74(void);
void             func_801D4884(void);
void             func_801D667C(void);
void             func_801D71EC(void);
void             func_801D9664(void);
void             func_801D96D4(void);
s32              func_801DAE14(u16);
void             Menu_DrawPlayTimeWindow(u16 panel_x, u16 panel_y);
void             func_801DE5D4(u8, u16, u16, s32, s32, MenuPanelTask*);
extern void      func_801E30FC(u16 row_x, u16 row_y, s32 row_flags);
void             func_801E6D88(s32 prompt_x);
void             func_801E6E18(s16 x, s16 y, s32 row, s32 shade, u8 blend);
void             func_801E7000(void);
extern s32       func_801E7348(void);
extern void      func_801E77F0(void);
void             func_801E9350(void);
void             func_801EA1F0(MenuPanelTask* task);
extern u8        D_801EC3E0[]; /* 6-byte rows: entry count, then up to five entries */
extern s32       D_801EC488;
extern s32       D_801EC4A4;
extern s32       D_801EC548;
extern s32       D_801EC54A;
extern s32       D_801EC54C;
extern s32       D_801EC598;
extern u8        MENU_CLOCK_CAPTION[];
extern u8        MENU_COMMAND_FRAME[];
extern u8        MENU_COMMAND_FRAME_SELECTED[];
extern u8        D_801EC7F8[];
extern u8        D_801EC938[];
extern u8        MENU_CLOCK_COLON[];
extern u8*       g_MenuCommandLabels[];  /* label id -> button text */
extern u8        g_MenuCommandRows[][5]; /* button count, then four label ids */
extern u8        D_801ECB2C[];
extern u8        D_801ECD0C[];
extern u8        D_801ECD14[];
extern u8        D_801ECDAC[];
extern u8        D_801ECDB4[];
extern s32       D_801ECFB8;
extern const u16 D_801ED1FC[];
extern const u16 D_801ED1FE[];
extern const u16 D_801ED200[];
extern const u16 D_801ED202[];
extern const u16 D_801ED204[];
extern u8        D_801ED5DC[];
extern s32       D_801ED5F0;
extern s32       D_801ED5FC;
extern s32       D_801ED608;
extern s8        D_801ED654;
extern u8        D_801ED660;
extern u8        D_801ED664;
extern s8        D_801ED668;
extern s8        D_801ED670;
extern s8        D_801ED674;
extern s8        D_801ED678;
extern s8        D_801ED67C;
extern u8        D_801ED69C;
extern s32       D_801ED878;
extern s32       Party_CountItem(u8 category, u8 item, u8 mode);

/* Pick the party record the record index selects: record 0 is the saved
 * Character, any other is the Character copy inside the battle row. */
static inline Character* Start_PickPartyRecord(s32 character_index, s32 record_index) {
    if ((record_index & BYTE_MASK) == 0) {
        return &g_Characters[character_index & BYTE_MASK];
    } else {
        return &g_BattlePartyBattlers[character_index & BYTE_MASK].stats;
    }
}

/* func_801AED54 */
void UI_DrawWindowOutline(s16 x, s16 y, s16 width, s32 height, s32 flags);

void func_801AF930(s32 x, s32 y, u8 palette_index, u8 icon_index, u8* command_stream, u8 stat_value, u8 sprite_flag);

/* func_801DC604 */
void Menu_DrawCharacterPortrait(u16 sprite_x, u16 sprite_y, u8 atlas_index, u8 shade_mode);

void func_80164D2C(u8 idx, u8 sel, u8 val, u8* flags, u16* dst);

void func_801AFA1C(u8* arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);

s32 func_801AFD10(u8* column_counter, u8* row_offset, u8* row_flag, u8* position);

void func_801E2C00(u16 x, s32 y, s32 group, s32 selected, s32 mode);

void func_801E2D84(s16 x, s32 y);

void func_801E3E34(u16 line_index);

void UI_DrawSpriteRun(s16 base_x, s16 base_y, const u8* record_table, u8 flags);
void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style);

#endif
