#ifndef SLUS_FUNCTIONS_H
#define SLUS_FUNCTIONS_H

#include "types.h"
#include "audio/bgm.h"
#include "audio/cue.h"
#include "sys/cd_format.h"
#include "psx/psyq.h"
#include "game/character.h"
#include "game/item.h"
#include "common/handler.h"
#include "gfx/palette.h"
#include "gfx/prim.h"
#include "slus/part.h"
#include "slus/actor.h"
#include "slus/area.h"
#include "slus/party.h"
#include "slus/sound.h"
#include "slus/system.h"
#include "slus/ui.h"

volatile u8* func_800AC754(u8 entry_id);
void         func_8014BA04(void);
/* func_8014FC00 */
void         func_8014FC00(s32 mode);
void         func_80154438(void);
void         func_8015B410(void* matrix);
void         func_8015B4B0(void* matrix);
/* func_8015A944 */
void         func_8015A944(void);
/* func_8015C058 */
void         Game_ClearScriptActive(void);
/* func_8015C088; int with no value returned (see its definition) */
extern s32   Game_SetScriptActive(void);
void         func_8015C214(s32 slot, u8 value);
s32          func_8015CC00(u8 id, s32 step, s32 selection, s32 x, s32 y, s32 z);
void         func_8015D104(s32 slot, s32 amount);
/* formats a game-text buffer; PsyQ declares sprintf on char, the game keeps its text as u8 */
#define TEXT_Format(dst, fmt, args...) sprintf((char*)(dst), (char*)(fmt), ##args)
#define TEXT_FormatLiteral(dst, fmt)   sprintf((char*)(dst), (char*)(fmt))
/* 0x40-byte palette staging entries; GFX_LoadPalette copies them out, the second copy lands 0x4000 above. */
#define GAME_PALETTE_STAGE             MEM_PTR(u8, 0x80035600u)
#define GAME_PALETTE_MIRROR            MEM_PTR(u8, 0x80039600u)
#define GAME_PALETTE_MIRROR_U16        ((u16*)GAME_PALETTE_MIRROR)

#endif
