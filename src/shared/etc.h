#ifndef ETC_FAMILY_H
#define ETC_FAMILY_H

#include "game.h"
#include "sys/cd.h"
#include "sys/exe.h"
#include "sys/scene.h"
#include "area/map.h"
#include "sys/actor.h"
#include "etc/overlay.h"
#include "menu/clock.h"
#include "menu/draw.h"
#include "menu/inventory.h"
#include "menu/item.h"
#include "menu/panel.h"
#include "menu/save.h"
#include "menu/shop.h"
#include "scenario/effect.h"
#include "scenario/runtime.h"
#include "slus/facing.h"
#include <strings.h>

extern s8          D_801448EA[1];
/* D_801448FC */
/* D_801448FF */
/* D_80144900 */
/* D_80144904 */
/* The game state the overlay tests. */
extern u32         D_80145034; /* 0x80145034 */
extern u32         D_80145038;
extern u8          D_8014504A;
extern u8          D_8014554C[]; /* 0x8014554C */
extern u8          D_8014554F[];
extern u8          D_801455C3;
extern u8          D_801455C4;
extern u8          D_801455C5;
/* The fairy village rooms, eight bytes each. */
extern const u8    g_FairyRooms[];
extern s32         D_80145EC4; /* 0x80145EC4 */
extern u8          D_8014842D;
extern u8          D_8014842E;
extern u8          D_8014842F;
extern u16         D_80148430;
extern s16         D_80148432;
extern s8          D_80148451;
extern s8          D_80148452;
extern u8          D_80148453;
extern s16         D_80148454;
extern s16         D_80148456;
extern s8          D_80148475;
extern s8          D_80148476;
extern s16         D_80148478;
extern s16         D_8014847A;
extern s8          D_8014847E;
extern s8          D_8014847F;
extern s8          D_80148499;
extern s8          D_8014849A;
extern s16         D_8014849C;
extern s16         D_8014849E;
extern s8          D_80148600;
extern u16         D_80148604;
extern u16         D_80148606;
extern u8          D_8014860A;
extern u8          D_8014860B;
extern u8          D_80148655;
extern s8          D_8014865B;
extern u8          D_8014865D;
extern u8          D_80148661;
extern u8          D_80148698;
extern u8          D_8014869C;
extern u8          D_8014869D;
extern AbilityCost D_801CA71A[];
/* D_801EC628 */
extern u8          g_MenuStatFrameLeft[44];
/* D_801EC654 */
extern u8          g_MenuStatFrameMiddle[12];
/* D_801EC660 */
extern u8          g_MenuStatFrameRight[24];
/* D_801EC678 */
extern u8          g_MenuCaptionLeft[12];
/* D_801EC684 */
extern u8          g_MenuCaptionMiddle[12];
/* D_801EC940 */
extern u8          g_MenuLabelPower[4];
/* D_801EC944 */
extern u8          g_MenuLabelDefense[4];
/* D_801EC948 */
extern u8          g_MenuLabelIntellect[4];

/* D_801E5A24 (shop), D_801ECB40 (start) */
extern UvRect      g_MenuClutStripCells[];
/* D_801E5AD0 (shop), D_801ECBEC (start) */
extern u8          g_MenuClutStripEntries[];
/* D_801E5B1C (shop), D_801ECC38 (start) */
extern u8          g_MenuClutStripPalettes[];
/* D_801E6074 (shop), D_801ED804 (start) */
extern u8          g_SaveSlotFirst;
/* D_801E6078 (shop), D_801ED808 (start) */
extern u8          g_SaveSlotCount;
/* D_801E6098 (shop), D_801ED80C (start) */
extern MenuListRow g_SaveSlots[];
/* The fairy roster: nine bytes a fairy, the five-byte name first. */
extern u8          g_Fairies[][9];
/* The active village UI record the fairy scenes hand to one another. */
extern u8*         D_801F2948;
extern u8          D_801F294C;
extern u8          D_801F294D;
extern u8          D_801F294E;
/* Bate and Shisu read scenario_id from the resident scenario record. */
struct SceneState;

void        func_801D0C04(void);
void        func_801D0C10(void);
void        func_801D0C2C(void);
void        func_801D0C44(void);
void        func_801D0C50(void);
void        func_801D0D80(void);
void        func_801D0D9C(void);
/* func_801DA1D8 */
void        Menu_DrawExperienceLine(u16 x, u16 y, u8 char_id, u8 level, u32 exp);
void        func_801D12FC(void);
void        func_801D2B64(void);
/* func_801D4754 */
extern void Menu_DrawItemRow(s32 x0, s32 y0, s32 item, s32 selection);
/* func_801D95F4 */
void        Menu_DrawEquipment(s32 origin_x, s32 origin_y, s32 index, s32 selection);
/* func_801DA2F4 */
void        Menu_DrawZennyWindow(s32 panel_x, s32 panel_y, s32 panel_kind, s32 caption_value);
/* func_801DA678 */
u8          Menu_ToggleOption(void);
/* func_801D504C */
u32         Char_GetExpProgress(u32 character, u32 level, u32 exp);
/* func_801D6470 (bate), func_801DBF18 (shop) */
void        Menu_DrawFilledPanel(s16 x, s16 y, s16 width, s32 height);
/* func_801D1CC0 (sisyou), func_801D3384 (bate), func_801D432C (shisu), func_801D8E2C (shop), func_801DC324 (start) */
void        Menu_DrawCursorFrame(u16 x, u16 y, s32 width, s32 height, u8 color, s32 mask);
/* func_801D67B0 */
void        SAVE_DrawSlots(s16 panel_x, s16 panel_y, u8 row_cursor);
/* func_801D78A8 (bate), func_801D8850 (shisu), func_801DD350 (shop) */
void        Menu_DrawPanelFrame(s16 x, s16 y, s32 width, s32 height);
/* func_801DBD24 */
void        Menu_DrawClutStrip(u8 clut_index);
void        func_801D3310(void);
void        func_801E1680(void);
s32         SAVE_ScanDirectory(char* prefix, u8 length);
void        func_801F03D0(void);
void        func_801F16BC(void);
void        func_801F18BC(void);
void        func_801F1B8C(void);
void        func_801F1E74(void);
void        func_801F1F9C(void);
void        func_801F2020(void);
void        func_801F228C(void);
int         abs(int); /* SDK libc, no staged abs.h */

extern s32 D_801457AC;

/* function-local data for func_801729D0 */
extern u8 D_8018E9A1;

extern s32 D_8018E9A4;

void func_801F23A4(void);

#endif
