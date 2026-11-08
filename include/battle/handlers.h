#ifndef BATTLE_HANDLERS_H
#define BATTLE_HANDLERS_H

#include "common/handler.h"

/* The moments of a boss encounter at which battle/battle/03 calls the boss overlay's g_Battle.boss_event_hook. */
typedef enum BossEvent {
    BOSS_EVENT_RESTART_BEGIN,  /* the battle restarts */
    BOSS_EVENT_ACTION_START,   /* a chosen action begins */
    BOSS_EVENT_TURN_END,       /* the turn's hand-off wait is over; the hook may keep it pending */
    BOSS_EVENT_TICK,           /* every frame of a running battle mode */
    BOSS_EVENT_EFFECTS_LOADED, /* the battle effect overlay finished loading */
    BOSS_EVENT_RESTART_END,    /* the restart message is up */
    BOSS_EVENT_BATTLE_RESET,   /* the battle state is reset */
    BOSS_EVENT_COUNT
} BossEvent;

/* The hook's reply to BOSS_EVENT_TURN_END while the boss still runs its own event. */
#define BOSS_EVENT_PENDING 0xFF

typedef u8 (*BossEventFunc)(u32 event);

void        func_800AC844(u8 entry_id);
void        func_800AC934(u8 entry_id);
s32         func_800ACFF4(void);
void        func_801DDED8(void);
void        func_801DDF00(void);
void        func_801DDF28(void);
void        Battle_ClearSlotPending(u32 slot);
void        func_801E2314(u32 script_index);
u8          func_801E30F8(void);
u8          func_801E3160(void);
/* func_801E54EC */
void        Battle_DefeatEnemy(void);
void        func_801E567C(void);
/* func_801E5704 */
void        Battle_TriggerCritical(void);
/* func_801EF318 */
extern void func_801EF318(void);
#endif
