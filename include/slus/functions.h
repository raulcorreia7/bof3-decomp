#ifndef SLUS_FUNCTIONS_H
#define SLUS_FUNCTIONS_H

#include "types.h"
#include "audio/bgm.h"
#include "audio/se.h"
#include "sys/cd_format.h"
#include "psx/psyq.h"
#include "game/character.h"
#include "game/item.h"
#include "common/callback.h"
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
/* func_8014BA04 */
void         SYS_ClearCurrentThread(void);
/* func_8014FC00 */
void         UI_AddTextDrawMode(s32 mode);
/* func_80154438 */
void         Area_ApplyMapBundleObjects(void);
/* func_8015A944 */
void         Actor_ProjectForDraw(void);
/* func_8015B410 */
void         Actor_BuildTransformMatrix(void* matrix);
/* func_8015B4B0 */
void         Area_ApplyCameraMatrix(void* matrix);
/* func_8015C058 */
void         Game_ClearScriptActive(void);
/* func_8015C088; int with no value returned (see its definition) */
extern s32   Game_SetScriptActive(void);
void         func_8015C214(s32 slot, u8 value);
/* func_8015CC00 */
s32          Actor_SpawnHelper(u8 id, s32 step, s32 selection, s32 x, s32 y, s32 z);
/* func_8015D104 */
void         SND_DecreaseVoiceTargetVolume(s32 slot, s32 amount);
/* formats a game-text buffer; PsyQ declares sprintf on char, the game keeps its text as u8 */
#define TEXT_Format(dst, fmt, args...) sprintf((char*)(dst), (char*)(fmt), ##args)
#define TEXT_FormatLiteral(dst, fmt)   sprintf((char*)(dst), (char*)(fmt))
/* 0x40-byte palette staging entries; GFX_LoadPalette copies them out, the second copy lands 0x4000 above. */
#define GAME_PALETTE_STAGE             MEM_PTR(u8, 0x80035600u)
#define GAME_PALETTE_MIRROR            MEM_PTR(u8, 0x80039600u)
#define GAME_PALETTE_MIRROR_U16        ((u16*)GAME_PALETTE_MIRROR)

#endif
