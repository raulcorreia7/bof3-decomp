#ifndef OVERLAY_ETC_START_08_H
#define OVERLAY_ETC_START_08_H

#include "game/character.h"
#include "menu/party.h"
#include "shared/etc.h"
#include "menu/save_data.h"
#include <string.h>
#include <stdio.h>

/* The save-image buffer the card writer clears and then checksums. */
#define SAVE_IMAGE_ADDR               0x800C1A00u

/* Panel slots of the start menu, by the role the modes assigned to them give. */
#define MENU_START_PANEL_DESCRIPTION  11 /* header bar with the selected entry's description */
#define MENU_START_PANEL_COMMANDS     12 /* command row */
#define MENU_START_PANEL_ITEMS        13 /* item list */
#define MENU_START_PANEL_CURSOR_FRAME 19 /* frame drawn around the cursor */
#define MENU_START_PANEL_CURSOR       21 /* pointing-hand cursor */

/* Panel modes of the start menu: the index into g_MenuStartPanelModes. Modes
 * whose draw helper is not yet read keep their number. */
#define MENU_START_MODE_CHARACTER     0
#define MENU_START_MODE_ZENNY         1
#define MENU_START_MODE_PLAY_TIME     2
#define MENU_START_MODE_CAMP_ICONS    3
#define MENU_START_MODE_TITLE         4
#define MENU_START_MODE_STATS         5
#define MENU_START_MODE_EQUIPMENT     6
#define MENU_START_MODE_MESSAGE       9
#define MENU_START_MODE_CURSOR_FRAME  10
#define MENU_START_MODE_INVENTORY     12
#define MENU_START_MODE_COMMANDS      13
#define MENU_START_MODE_CURSOR        14
#define MENU_START_MODE_EQUIP_COMPARE 16
#define MENU_START_MODE_ABILITIES     17
#define g_SceneFlags                  ((void*)g_SceneFlags)

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
#define MENU_CLAMP_PANEL(limit)                          \
    do {                                                 \
        MenuPanelTask* panel;                            \
        u16            next;                             \
                                                         \
        panel        = g_MenuCurrentPanel;               \
        next         = panel->pos.x + MENU_PANEL_STEP_X; \
        panel->pos.x = next;                             \
        if ((s16)next >= 17) {                           \
            panel->pos.x = (limit);                      \
            panel->state = 0;                            \
        }                                                \
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

/* The save menu results g_SaveCardStatus holds beyond the CardEvent codes 0 to 4. */
enum {
    SAVE_STATUS_LOADED       = 5, /* the load verified; the slots show */
    SAVE_STATUS_NO_FILE      = 6, /* the card directory has no save file */
    SAVE_STATUS_BAD_CHECKSUM = 7, /* the loaded file failed its checksum */
    SAVE_STATUS_NO_CARD      = 8, /* neither port holds a usable card */
};

typedef struct {
    s32 unk_00;
    s32 unk_04;
    s8  unk_08;
    s8  unk_09;
} __attribute__((packed)) Record10;

typedef struct {
    s32 unk_00;
    s32 unk_04;
    s8  unk_08;
    s8  unk_09;
    s8  unk_0A;
} __attribute__((packed)) Record11;

typedef struct {
    s32 unk_00;
    s8  unk_04;
    s8  unk_05;
} __attribute__((packed)) Record6;

typedef struct {
    s32 unk_00;
    s32 unk_04;
} __attribute__((packed)) Record8;

extern Record10 D_801D0DE0;
extern Record11 D_801D0DEC;
extern Record11 D_801D0DF8;
extern Record6  D_801D0E04;
extern Record8  D_801D0E0C;
extern Record11 D_801D0E14;

typedef struct Start08Rotation {
    u16 unk_00;
    u16 unk_02;
    s32 unk_04;
} Start08Rotation;

extern Start08Rotation D_801EC4D0[];

/* One 8-byte label row: glyph count, signed x nudge (read through (s8)), then
 * the text. */
typedef struct StartLabel {
    u8 length;
    u8 offset_x;
    u8 text[6];
} StartLabel;

extern StartLabel D_801ECD24[];

/* The command cells of the name entry grid, beside the letter cells (0 is an empty cell). */
typedef enum NameEntryCommand {
    NAME_ENTRY_NEXT  = 1,
    NAME_ENTRY_BACK  = 2,
    NAME_ENTRY_QUIT  = 3,
    NAME_ENTRY_START = 4,
} NameEntryCommand;

/* The four command labels of the grid ("Next", "Back", "Quit", "Start"), five characters each. */
typedef struct NameEntryLabels {
    u8 next[5];
    u8 back[5];
    u8 quit[5];
    u8 start[5];
} NameEntryLabels;

extern NameEntryLabels D_801D0F00;
extern u8              D_801ECDBC[];

extern u8              D_80144F57;
extern u16             D_80145594[];
extern u8              D_80148480;
extern u8              D_8014849B;
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
extern s16             D_80148508; /* signed scalar view of the panel's x */
extern u8              D_8014850E; /* the panel's group */
extern u8              D_8014850F; /* the panel's group first entry */
extern u8              D_80148510; /* the panel's group cursor */
extern s8              D_80148511; /* signed scalar view of the panel's drawn cursor */
extern u8*             D_80148524;
extern s8              D_8014854C;
extern s8              D_8014854D;
extern s8              D_8014854E;
extern s8              D_8014854F;
extern s16             D_80148550;
extern s16             D_80148552;
extern u8              D_80148556;
/* D_80148570: the battle choice panel record, also the skill-order work area. */
extern u8              g_BattleChoicePanel[];
extern s8              D_80148571;
extern s8              D_80148572;
extern s16             D_80148576;
extern u8              D_80148594;
extern s8              D_80148595;
extern s8              D_80148596;
extern s16             D_80148598;
extern s16             D_8014859A;
extern u16             D_801485BC;
extern u16             D_801485BE;
extern u8              D_801485DD;
extern u8              D_801485DE;
extern s16             D_80148628; /* the computed bar length; func_801D8188 stores it with sh at 0x801D81FC */
extern u16             D_8014862A; /* the second bar length; func_801D8188 stores it with sh at 0x801D8210 */
extern u8              D_80148653;
extern u8              D_80148654;
/* D_80148656, the party cursor, has no declaration here: its readers split between lb and lbu, so each unit keeps its own view. */
extern s8              D_80148658[6];
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
/* D_8018E990 */
extern u8              g_SaveCardDirectory[];
extern u8*             D_801C893C[];
extern u8*             D_801C8950[];
extern char            g_MenuStatFormat[4];
extern char            g_MenuZennyFormat[4];
/* D_801D0C74 */
extern char            g_MenuNextExpBlank[];
extern char            g_SaveSlotLevelFormat[];
extern char            g_SaveSlotTimeFormat[];
extern char            g_SaveSlotTimeColon[4];
extern u8              D_801D0DC0[4];
extern u8              D_801D0DC4[4];
extern u8              s_RowCaptionTags[24];
extern char            g_SaveFileNameFormat[];
extern char            D_801D0F14[];

/* The party records the New Game screen starts from. */
typedef struct WillpowerCurve {
    u8 level_divisor;
    u8 base;
} WillpowerCurve;

extern Character      g_NewGameCharacters[CHARACTER_COUNT];
extern WillpowerCurve g_NewGameWillpowerCurves[CHARACTER_COUNT];
extern u8             s_CampMenuPanelIds[8];
/* Entries of the step handler tables. */
#define MENU_START_STEP_COUNT          9
#define MENU_START_STEP2_COUNT         11
#define MENU_START_STEP5_COUNT         6
#define MENU_START_STEP5_SUB2_COUNT    3
#define MENU_START_STEP6_COUNT         5

/* Entries of the panel handler tables. */
#define MENU_START_MODE_COUNT          21
#define MENU_START_PANEL0_STATE_COUNT  11
#define MENU_START_PANEL1_STATE_COUNT  3
#define MENU_START_PANEL2_STATE_COUNT  3
#define MENU_START_PANEL3_STATE_COUNT  3
#define MENU_START_PANEL4_STATE_COUNT  3
#define MENU_START_PANEL5_STATE_COUNT  7
#define MENU_START_PANEL6_STATE_COUNT  3
#define MENU_START_PANEL7_STATE_COUNT  3
#define MENU_START_PANEL8_STATE_COUNT  3
#define MENU_START_PANEL9_STATE_COUNT  3
#define MENU_START_PANEL11_STATE_COUNT 3
#define MENU_START_PANEL12_STATE_COUNT 5
#define MENU_START_PANEL13_STATE_COUNT 3
#define MENU_START_PANEL16_STATE_COUNT 5
#define MENU_START_PANEL17_STATE_COUNT 5
#define MENU_START_PANEL18_STATE_COUNT 5
#define MENU_START_PANEL19_STATE_COUNT 3
#define MENU_START_PANEL20_STATE_COUNT 3

/* D_801EC35C */
extern Callback g_MenuStartStates[MENU_START_STEP_COUNT];
extern Callback D_801EC380[];
extern u8       D_801EC38C[];
/* D_801EC394 */
extern Callback g_MenuStartStep6Funcs[MENU_START_STEP6_COUNT];
/* D_801EC3A8 */
extern Callback g_MenuStartStep2Funcs[MENU_START_STEP2_COUNT];
extern Callback D_801EC3D4[];
extern Callback D_801EC400[7];
extern Callback D_801EC41C[];
extern u16      D_801EC440[];
extern u8       s_EquipSlotCategories[8];
extern Callback D_801EC460[];
extern Callback D_801EC498[];
extern Callback D_801EC4B0[5];
extern Callback D_801EC4C4[];
/* D_801EC518 */
extern Callback g_MenuStartStep5Funcs[MENU_START_STEP5_COUNT];
/* D_801EC530 */
extern Callback g_MenuStartStep5Sub2Funcs[MENU_START_STEP5_SUB2_COUNT];
extern Callback D_801EC53C[];
extern Callback D_801EC578[];
extern Callback D_801EC58C[];
/* Panel and caption resources. A glyph row is a run of 3-byte records
 * {s8 dx, s8 dy, u8 glyph} in 8-pixel units that UI_DrawSpriteRun draws until
 * glyph 0xFF; g_MenuCaptionRight packs several such runs and the label
 * strings in one row. The icon and portrait rows are UI_DrawText glyph
 * strings and an atlas of s16 cells followed by label strings. Both stay byte
 * arrays: a row's size includes alignment padding past its payload (44 bytes
 * for a 42-byte run, 688 for a 687-byte bank), and a typed record array would
 * need the split data to own that padding. */
extern u8       g_MenuCaptionRight[688];
/* D_801EC754 */
extern u8       g_MenuListTab2OffSprites[];
/* D_801EC76C */
extern u8       g_MenuListTab2OnSprites[];
extern u8*      g_MenuInventoryTitles[5];
extern char     g_MenuInventoryCountFormat[];
extern u8       g_MenuInventoryTab1OffSprites[];
extern u8*      g_MenuEquipTitles[5];
extern u8       g_MenuEquipChoiceIds[];
extern u8       g_MenuEquipChoiceCounts[];
extern u8       g_MenuInventoryTab1OnSprites[];
/* D_801EC784 */
extern u8       g_MenuListTab1OffSprites[];
/* D_801EC790 */
extern u8       g_MenuListTab1OnSprites[];
extern u8       g_SaveSlotFrameSprites[];
extern u8       g_MenuLabelAgility[4];
extern u8       g_MenuEquipRowIcons[8]; /* equipment-row sprites. @source: read:Shop_DrawEquipment */
extern u8       g_MenuLabelEquip[8];    /* the equipment panel caption. @source: read:Shop_DrawEquipment */
extern u8       g_MenuPortraitAtlas[96];
extern u8       g_MenuCaptionIcon[792];
extern s32      D_801ECC98[];
extern Callback D_801ECCF8[];
extern Callback D_801ECD1C[];
extern u8       s_CampMenuState[8];
extern Callback D_801ED11C[7];
extern Callback D_801ED138[4];
extern Callback D_801ED148[17];
extern u8       D_801ED18C;
extern u8       s_PanelIconSelectors[24];
extern u8       s_PanelIconValues[228];
extern s32 (*D_801ED224[])(u8 caster_index, u8 target_index, u8 use_battle_record);
extern s32 (*D_801ED24C[])(u8 save_slot, u8 record_value);
extern u8       g_SaveRecordTypeCommands[92];
/* D_801ED330 */
extern Callback g_MenuStartPanelModes[MENU_START_MODE_COUNT];
/* D_801ED384 */
extern Callback g_MenuStartCharacterStates[MENU_START_PANEL0_STATE_COUNT];
/* D_801ED3B0 */
extern Callback g_MenuStartZennyStates[MENU_START_PANEL1_STATE_COUNT];
/* D_801ED3BC */
extern Callback g_MenuStartPlayTimeStates[MENU_START_PANEL2_STATE_COUNT];
/* D_801ED3C8 */
extern Callback g_MenuStartCampIconsStates[MENU_START_PANEL3_STATE_COUNT];
/* D_801ED3D4 */
extern Callback g_MenuStartTitleStates[MENU_START_PANEL4_STATE_COUNT];
/* D_801ED3E0 */
extern Callback g_MenuStartStatsStates[MENU_START_PANEL5_STATE_COUNT];
/* D_801ED3FC */
extern Callback g_MenuStartEquipmentStates[MENU_START_PANEL6_STATE_COUNT];
/* D_801ED408 */
extern Callback g_MenuStartPanel7StateFuncs[MENU_START_PANEL7_STATE_COUNT];
/* D_801ED414 */
extern Callback g_MenuStartPanel8StateFuncs[MENU_START_PANEL8_STATE_COUNT];
/* D_801ED420 */
extern Callback g_MenuStartMessageStates[MENU_START_PANEL9_STATE_COUNT];

typedef struct CursorFrameSize {
    u16 width;
    u16 height;
} CursorFrameSize;

ASSERT_SIZE(CursorFrameSize, 4);

extern CursorFrameSize g_MenuStartCursorFrames[4];
/* D_801ED43C */
extern Callback        g_MenuStartPanel11StateFuncs[MENU_START_PANEL11_STATE_COUNT];
/* D_801ED448 */
extern Callback        g_MenuStartInventoryStates[MENU_START_PANEL12_STATE_COUNT];
/* D_801ED45C */
extern Callback        g_MenuStartCommandsStates[MENU_START_PANEL13_STATE_COUNT];
extern u8              D_801ED468[];
extern u8              D_801ED48C[];
extern u8              D_801ED498[];
extern u32             D_801ED534[];
extern u8              D_801ED560[][6];
/* D_801ED58C */
extern Callback        g_MenuStartEquipCompareStates[MENU_START_PANEL16_STATE_COUNT];
/* D_801ED5A0 */
extern Callback        g_MenuStartAbilitiesStates[MENU_START_PANEL17_STATE_COUNT];
/* D_801ED5B4 */
extern Callback        g_MenuStartPanel18StateFuncs[MENU_START_PANEL18_STATE_COUNT];
/* D_801ED5C8 */
extern Callback        g_MenuStartPanel19StateFuncs[MENU_START_PANEL19_STATE_COUNT];
/* D_801ED5E4 */
extern Callback        g_MenuStartPanel20StateFuncs[MENU_START_PANEL20_STATE_COUNT];
extern u8              s_PartyCharacterIds[3];
extern u8              D_801ED613[];
extern s8              D_801ED618;
extern u8              D_801ED620;
/* D_801ED63C */
extern u8              g_EquipPreview[EQUIP_SLOT_COUNT];
extern s8              D_801ED648;
/* The start overlay's slot rows (three bytes per slot) and its byte table;
 * every reader indexes or walks them as bytes. */
extern u8              D_801ED680[];
extern u8              D_801ED68C;
extern u8              D_801ED690[];
extern u8              D_801ED694[][2];
extern u8              D_801ED695[][2];
extern u8              D_801ED6A0;
extern u8*             D_801ED7D8;
extern u8              D_801ED7DC;
extern s8              D_801ED7E0;
extern s8              D_801ED7E4;
extern u8              D_801ED7E8;
extern u8              D_801ED7EC;
/* D_801ED7F0 */
extern s8              g_MenuStartTimer;
extern u8              D_801ED7F4;
extern u8              D_801ED7F8;
/* D_801ED860 */
extern u8              g_MenuStartReturnStep;
extern u8              g_MenuStartStep;
extern u8              D_801ED864;
extern u8              D_801ED868;
extern u8              D_801ED86C;
extern u8              D_801ED870;
extern u8              D_801ED890;
extern u8              D_801ED891;
extern u8              s_ChoiceMenuValues[8];
extern u8              s_ChoiceMenuCursors[12];
extern u8              s_SkillOrderCursors[4][4];
extern u8              s_SkillOrderGroups[4][6];
extern u8              s_SkillOrderKinds[3][6];
extern Callback        g_MenuCampSubFuncs[5];
extern Callback        g_MenuCampSubstates[5];

/* The name entry command labels, the grid's dot string and the control window's sprite table. */
/* D_801ED1B8 */
extern u8* g_NameEntryCommandLabels[];
/* D_801ED1D4 */
extern u8* g_NameEntryGridDot;
/* D_801ED05C */
extern u8  g_NameEntryControlsFrame[];

/* Shared calls the start-screen units make: the main executable's window,
 * input, resource and sound helpers, and the game overlay's draw helpers. */
extern bool Item_Add(s32 category, u8 item, u8 amount, s32 unused);
extern s16  Char_AddStat(u16* value, s16 delta);
/* Draws one sprite at (x, y); defined in the game overlay (emi/etc/game/00). */
bool        func_801AF494(u8 test, u8 character_id, u8 category, u8 item_id);
s32         func_801B6470(u8 arg0);
/* func_801C1254 */
void        Party_LoadMemberSprite(s32 character_id, s32 save_slot);
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
bool        func_801D70EC(void);
void        func_801D7204(void);
void        func_801D8CC8(void);
void        func_801D8D64(void);
void        func_801D8DC8(void);
void        func_801D902C(void);
void        func_801D90A8(void);
void        func_801D9110(void);
extern void Menu_SwapBytes3(u8* first, u8* second);
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
void        Menu_SwapBytes4(u8* first, u8* second);
extern void func_801DB510(void);
void        func_801DB550(void);
void        func_801DB5AC(void);
/* func_801DBF04 */
extern void Shop_DrawEquipment(s16 x, s16 y, u8 record_index);
extern void func_801DC150(s16 x, s16 y, u8 character_index, s32 layout);
/* func_801DCDB8 */
void        Menu_DrawFormationPreview(u16 x, u16 y, u8 index, u8 blink, s32 angle);
extern void Menu_DrawCommandRow(s16 x, s16 y, u8 row, u8 selected, s32 unused);
void        Menu_DrawCharacterWindow(u16 x, u16 y, u8 character_index, u8 shaded, s32 unused);
void        Menu_DrawEquipStatWindow(u16 x, u16 y, u8 character_index, u8 item_kind, u8 item_id);
void        Menu_DrawWindowFrame(s16 x, s16 y, u8 width, u8 height);
/* func_801DFBF4 */
extern void Menu_DrawInventoryWindow(MenuPanelTask* task);
/* func_801E0354 */
extern void Menu_DrawAbilitiesPanel(MenuPanelTask* task);
/* func_801E0A70 */
extern void Menu_DrawEquipChoiceWindow(MenuPanelTask* task);
extern void func_801E14A8(s32 x, s32 y, u8 flags, u8 row, u8 active);
void        func_801E16BC(void);
void        SAVE_DrawSlot(u8 index, s32 left, s32 top, MenuListRow* row);
void        func_801E18D0(void);
void        func_801E1C20(void);
void        func_801E206C(void);
void        func_801E2408(void);
extern void func_801E2668(s32 icon_kind, s32 icon_x, s32 icon_y);
extern void func_801E26A8(s32 x, s32 y);
void        Menu_DrawOptionRow(s32 x, s32 y, s32 option_index, s32 select_step);
u8*         Menu_DrawGlyphAt(s16 x, s16 y, s32 color, u8* cursor, s32 glyph_left, s32 glyph_right);
void        func_801E3EC4(void);
void        func_801E4024(void);
void        func_801E4060(void);
void        func_801E40A0(void);
void        func_801E411C(void);
void        func_801E4288(void);
void        func_801E4318(void);
void        func_801E441C(void);
void        func_801E45CC(void);
/* func_801E462C */
void        Menu_UpdateCamp(void);
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
void        SAVE_RunLoadVerify(void);
void        func_801E5BCC(void);
void        func_801E5C68(void);
void        func_801E5E30(void);
void        func_801E5F34(void);
void        SAVE_RunLoadRestore(void);
void        Menu_ExitCamp(void);
extern void func_801E6388(s32 overlay_x, s32 overlay_y);
extern void Menu_DrawNameEntryGrid(u8 page, s32 grid_x, s32 grid_y);
/* func_801E6784 */
extern s32  Menu_DrawNameEntryControls(u8 page, s32 x, s32 y);
extern u8   func_801E715C(s32 range_low, s32 range_high, s32 draw_count);
extern void func_801E7210(u32 panel_index);
s32         func_801E7D20(s32 character_index, s32 target_index, s32 ability_id, s32 use_battle_record);
s32         func_801E8C9C(u8 save_slot, u8 item_id, u8 record_value);
void        func_801E8D58(void);
/* func_801E8D60 */
void        Menu_CharacterPanel(void);
/* func_801E8DB4 */
extern void Menu_DrawCharacterPanel(MenuPanelTask* task);
void        func_801E8EA8(void);
void        func_801E8EE8(void);
void        func_801E8F28(void);
void        func_801E8F68(void);
void        func_801E8FA8(void);
void        func_801E8FE8(void);
void        func_801E9040(void);
void        func_801E9080(void);
void        func_801E90C0(void);
void        func_801E9100(void);
/* func_801E9140 */
void        Menu_ZennyPanel(void);
void        func_801E91A4(void);
void        func_801E91E4(void);
/* func_801E9224 */
void        Menu_PlayTimePanel(void);
void        func_801E9284(void);
void        func_801E92C4(void);
/* func_801E9304 */
void        Menu_CampIconsPanel(void);
void        func_801E94D4(void);
void        func_801E9514(void);
/* func_801E9554 */
void        Menu_TitlePanel(void);
void        func_801E964C(void);
void        func_801E968C(void);
/* func_801E96CC */
void        Menu_StatsPanel(void);
void        func_801E9748(void);
void        func_801E9788(void);
void        func_801E97E0(void);
void        func_801E9820(void);
void        func_801E9878(void);
void        func_801E98B8(void);
/* func_801E98F8 */
void        Menu_EquipmentPanel(void);
void        func_801E9974(void);
void        func_801E99B4(void);
void        func_801E99F4(void);
void        func_801E9A70(void);
void        func_801E9AB0(void);
void        func_801E9AF0(void);
void        func_801E9B6C(void);
void        func_801E9BAC(void);
/* func_801E9BEC */
void        Menu_MessagePanel(void);
void        func_801E9D18(void);
void        func_801E9D58(void);
/* func_801E9D98 */
void        Menu_CursorFramePanel(void);
void        func_801E9DF4(void);
void        func_801E9EAC(void);
void        func_801E9F04(void);
/* func_801E9F5C */
void        Menu_InventoryPanel(void);
void        func_801E9FB0(void);
void        func_801E9FF0(void);
void        func_801EA030(void);
/* func_801EA0B0 */
void        Menu_CommandsPanel(void);
void        func_801EA118(void);
void        func_801EA158(void);
void        func_801EA1C8(void);
/* func_801EA50C */
void        Menu_EquipComparePanel(void);
void        func_801EA598(void);
void        func_801EA5D8(void);
void        func_801EA618(void);
void        func_801EA658(void);
/* func_801EA698 */
void        Menu_AbilitiesPanel(void);
void        func_801EA6EC(void);
void        func_801EA72C(void);
void        func_801EA76C(void);
void        func_801EA7AC(void);
/* func_801EA7EC */
void        Menu_EquipChoicePanel(void);
void        func_801EA840(void);
void        func_801EA880(void);
void        func_801EA8C0(void);
void        func_801EA900(void);
void        func_801EA940(void);
extern void func_801EAA14(MenuPanelTask* task);
void        func_801EA994(void);
void        func_801EA9D4(void);
void        func_801EAEC4(void);
extern void func_801EAF98(MenuPanelTask* task);
extern s8   SAVE_AccessFile(s32 port, s32 name, s32 mode, s32 size, s32 offset);
extern s32  func_801EFCA8(char* prefix, u8 length);

/* Slide the master panel in to x 320 and stop it there. */
static inline void Menu_SlidePanelIn(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x += MENU_PANEL_STEP_X;
    if ((s16)task->pos.x >= 321) {
        task->pos.x = 320;
        task->state = 0;
    }
}

/* Retreat the master panel left and clamp it. */
static inline void MenuRetreatPanelXToMinus200(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= MENU_PANEL_STEP_X;
    if ((s16)task->pos.x < -200) {
        LOH(task->pos.x) = -200;
        task->state      = 0;
    }
}

/* Step the master panel down and clamp it at the field limit. */
static inline void MenuAdvancePanelYField6(void) {
    MenuPanelTask* panel;
    u8*            bytes;
    u16            next;

    panel        = g_MenuCurrentPanel;
    bytes        = (u8*)panel;
    next         = panel->pos.y + MENU_PANEL_STEP_Y;
    panel->pos.y = next;
    if ((s16)next >= bytes[10] * 0x36 + 0x3E) {
        panel->pos.y = bytes[10] * 54 + 62;
        panel->state = 0;
    }
}

s32              Char_GetExpForLevel(s32 character, s32 level);
extern s8        D_8014850C;
extern u8        D_801485B9;
extern u8        D_801485BA;
extern s8        D_80148659;
extern u8        D_8014865A;
extern u8        D_80181B1A;
extern s32       Item_Count(u8 category, u8 item, u8 mode);
extern u8*       D_801C8940;
extern u8*       D_801C8944;
/* D_801D0C50 */
extern char      g_MenuCurrentValueFormat[8];
/* D_801D0C58 */
extern char      g_MenuMaxValueFormat[8];
extern char      g_MenuClockFormat[];
extern u8        D_801D0E20[];
extern s32       D_801D0E28;
extern s32       D_801D0EA8;
extern char      D_801D0F18[];
extern char      D_801D0F1C[];
extern char      D_801D0F24[];
void             Party_InitDefaults(void);
void             func_801D29A4(void);
extern void      func_801D2C7C(void);
void             func_801D2D74(void);
void             func_801D4884(void);
void             func_801D667C(void);
void             Menu_PreviewStrongestEquipment(u8 character);
void             func_801D71EC(void);
void             func_801D9664(void);
void             func_801D96D4(void);
void             Menu_DrawPlayTimeWindow(u16 panel_x, u16 panel_y);
void             func_801DAE14(u16 buttons);
void             Menu_DrawPanelIcon(u16 icon_x, u16 icon_y, s32 icon_u, s32 icon_v, u16 icon_clut, u8 icon_shade);
void             Menu_DrawEquipCompareWindow(u8 index, s32 x, s32 y, u8* patch, u8 hide_changes, MenuPanelTask* task);
extern void      func_801E30FC(u16 row_x, u16 row_y, s32 row_flags);
void             func_801E6D88(s32 prompt_x);
void             func_801E6E18(s16 x, s16 y, s32 row, s32 shade, u8 blend);
void             func_801E7000(void);
extern s32       func_801E7348(void);
extern void      func_801E77F0(void);
/* func_801E9350 */
void             Menu_DrawCampIcons(void);
void             func_801EAF18(void);
void             func_801EAF58(void);
extern u8        D_801EC3E0[]; /* 6-byte rows: entry count, then up to five entries */
extern s32       D_801EC488;
extern s32       D_801EC4A4;
extern s32       D_801EC548;
extern s32       D_801EC54A;
extern s32       D_801EC54C;
extern s32       D_801EC598;
extern u8        g_MenuClockCaption[];
extern u8        g_MenuCommandFrame[];
extern u8        g_MenuCommandFrameSelected[];
extern u8        g_MenuEquipStatSprites[];
extern u8        D_801EC938[];
extern u8        g_MenuClockColon[];
extern u8*       g_MenuCommandLabels[];  /* label id -> button text */
extern u8        g_MenuCommandRows[][5]; /* button count, then four label ids */
extern u8        g_MenuEquipStatLabels[];
extern u8        g_MenuEquipCompareLabels[];
extern u8        g_MenuEquipCompareSprites[];
extern u8        g_MenuEquipSlotIcons[];
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
extern u8        D_801ED7FC;
extern s8        D_801ED66C;
extern u8        D_801ED105;
extern u8        D_801485B8;
void             func_801EA1F0(MenuPanelTask* task);

/* Pick the party record the record index selects: record 0 is the saved
 * Character, any other is the Character copy inside the battle row. */
static inline Character* Start_PickPartyRecord(s32 character_index, s32 record_index) {
    if ((record_index & BYTE_MASK) == 0) {
        return &g_Characters[character_index & BYTE_MASK];
    } else {
        return &g_Game.members[character_index & BYTE_MASK].chr;
    }
}

void Menu_DrawCharacterPortrait(u16 sprite_x, u16 sprite_y, u8 atlas_index, u8 shade_mode);

void UI_DrawSpriteRun(s16 base_x, s16 base_y, const u8* record_table, u8 flags);

extern FormationLayout g_MenuFormations[FORMATION_COUNT];
extern FormationOrder  g_MenuFormationOrder;
extern s32             g_MenuFormationArrow[3][2];
extern s32             g_MenuFormationArrowTurned[3][2];
extern s32             g_MenuFormationSpots[PARTY_SLOT_COUNT][2];
extern u8              g_MenuFormationFrameLeft[];
extern u8              g_MenuFormationFrameMiddle[];
extern u8              g_MenuFormationFrameRight[];

void func_801AF930(s32 x, s32 y, u8 palette_index, u8 icon_index, u8* command_stream, u8 stat_value, u8 sprite_flag);
void func_801AF800(s16 record_x, s32 record_y, u8 text_shade, u8 category, s32 item_id, s32 quantity, s32 sprite_flag);

void func_801AFA1C(u8* arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);

void func_801E2C00(u16 x, s32 y, s32 group, s32 selected, s32 mode);

void func_801E2D84(s16 x, s32 y);

/* func_801E3E34 */
void Menu_SetGlyphPage(u16 line_index);
void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style);
void Menu_DrawIcon(u16 sprite_x, u16 sprite_y, u8 icon_column, u8 shade_mode);

s32  Char_GetAbilityCost(s32 character_index, s32 ability_kind, s32 mode);
void func_801D9304(s32 handler_index);
u8   func_801DB04C(void);

/* Step the master panel up 16 pixels and stop it at y 62. The member declares task. */
#define MENU_STEP_PANEL_UP()     \
    task = g_MenuCurrentPanel;   \
    task->pos.y -= 16;           \
    if ((s16)task->pos.y < 63) { \
        task->pos.y = 62;        \
        task->state = 0;         \
    }

/* Step the master panel right 32 pixels and stop it at x 45. The member declares task. */
#define MENU_STEP_PANEL_RIGHT()   \
    task = g_MenuCurrentPanel;    \
    task->pos.x += 32;            \
    if ((s16)task->pos.x >= 46) { \
        task->pos.x = 45;         \
        task->state = 0;          \
    }

#endif
