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
#include "engine/sys/boot/boot.h"
#include "engine/state/mode/mode.h"
#include "engine/actor/task/task.h"
#include "engine/ui/text/text.h"
#include "engine/area/map/map.h"
#include "engine/camera/camera.h"

volatile u8* func_800AC754(u8 entry_id);
void         func_8015C214(s32 slot, u8 value);
/* formats a game-text buffer; PsyQ declares sprintf on char, the game keeps its text as u8 */
#define TEXT_Format(dst, fmt, args...) sprintf((char*)(dst), (char*)(fmt), ##args)
#define TEXT_FormatLiteral(dst, fmt)   sprintf((char*)(dst), (char*)(fmt))
/* 0x40-byte palette staging entries; GFX_LoadPalette copies them out, the second copy lands 0x4000 above. */
#define GAME_PALETTE_STAGE             MEM_PTR(u8, 0x80035600u)
#define GAME_PALETTE_MIRROR            MEM_PTR(u8, 0x80039600u)
#define GAME_PALETTE_MIRROR_U16        ((u16*)GAME_PALETTE_MIRROR)

#endif
