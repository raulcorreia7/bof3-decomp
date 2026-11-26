#ifndef OVERLAY_PARTY_PARTY_H
#define OVERLAY_PARTY_PARTY_H

#include "types.h"

/* func_801BDB7C */
u8          Party_CountOrder(u8 order);
u8          Party_CountOrder(u8 mode);
/* The executable's character, item and party functions, in address order. */
/* func_8015C100 */
extern void Party_BattlersHide(void);
/* func_801664A0 */
u8          Party_CountAbilities(u8 character_index, u8 ability_type, u8 mode);
/* func_8016663C */
bool        Party_SpendZenny(u32 amount, s32 unused);
/* func_8016666C */
s32         Party_AddZenny(s32 amount, s32 skip_earned);
/* func_801C1254 */
void        Party_MemberLoadSprite(s32 character_id, s32 party_slot);
/* func_801C1400 */
void        Party_BattlersBuild(u32 order);
/* Party_LoadPalettes */
/* func_801C1630 */
void        Party_LoadPalettes(void);
/* func_801C187C */
s32         Party_MemberJoin(s32 char_id);
/* Party_MemberRemove */
/* func_801C1ABC */
void        Party_MemberRemove(s32 character_id);
/* Party_TickConfusion */
/* func_801C3598 */
void        Party_TickConfusion(void);
/* func_80166AE4: type table for (source slot, group, table type) */
u8*         Party_GetAbilities(u32 formation_index, u32 ability_type, u32 mode);
/* func_80166CEC */
void        Party_BattlersClearState(s32 character_index);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_PARTY_PARTY_H_LOCAL)
#define OVERLAY_PARTY_PARTY_H_LOCAL

void Party_BattlersShow(void);
void Party_BattlersReset(void);
void Party_BattlersClearActive(void);
/* func_801B55C0 */
bool Party_CanSwitchLeader(void);
void Party_MemberSwap(u32 slot_a, u32 slot_b, u32 skip_state);
void Party_BattlersSwapRows(s32 slot_a, s32 slot_b, s32 skip_state);
/* func_801B00F8 */
void Party_RunLeader(void);
/* func_801BBE48 */
void Party_RunFollower(void);
/* func_801C308C */
void Party_FlashDamage(s32 color_index);

#endif
