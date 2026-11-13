#ifndef MENU_SAVE_DATA_H
#define MENU_SAVE_DATA_H

#include "types.h"
#include "area/fishing.h"
#include "game/character.h"
#include "game/fairy.h"
#include "menu/clock.h"
#include "menu/inventory.h"
#include "menu/party.h"
#include "scenario/state.h"

/* The persistent block: 4,272 bytes. */
#define SAVE_BLOCK_SIZE 0x10B0u

/* The scene event the overlays step through: mode selects the g_SceneEvents handler, step advances inside it and
 * selection is the entry it works on (a fairy job, a master, a menu cursor). */
typedef struct SceneEventState {
    s8 mode;
    s8 step;
    u8 selection;
} SceneEventState;

ASSERT_SIZE(SceneEventState, 3);

/* The persistent game state: SYS_StartFrontend clears it, SAVE_BuildSlotImage copies it to the memory card file
 * payload (file offset 0x200, so the frame-relative offsets of menu/save.h are these plus 0x200) and
 * SAVE_RunLoadRestore copies it back. */
typedef struct SaveData {
    /* 0x000 */ SceneState      scene_state; /* a snapshot of g_SceneState */
    /* 0x010 */ u8              unk_10[3];
    /* 0x013 */ SceneEventState scene_event;
    /* 0x016 */ u16             scene_event_timer; /* the scene event countdown, in thirtieths of a second */
    /* 0x018 */ u8              unk_18[8];
    /* 0x020 */ u8              script_vars[4]; /* a copy of g_ScriptVars[0..3] */
    /* 0x024 */ u16             area_id;        /* the area the save resumes in */
    /* 0x026 */ u8              unk_26;
    /* 0x027 */ u8              entry_facing;
    /* 0x028 */ u32             entry_x; /* the party position in the area, 16.16 */
    /* 0x02C */ u32             entry_y;
    /* 0x030 */ u8              unk_30[0x40];
    /* 0x070 */ u16             checksum;     /* zeroed while the payload is summed, then holds the sum */
    /* 0x072 */ u8              unk_72[8];    /* holds g_SndMono at 0x79, read through volatile views */
    /* 0x07A */ u8              window_style; /* the last argument of UI_DrawWindow */
    /* 0x07B */ u8              unk_7B[0x15];
    /* 0x090 */ Character       characters[CHARACTER_COUNT];
    /* 0x5B0 */ u8              scene_flag_words[160]; /* eight bytes per scenario */
    /* 0x650 */ u8              scene_event_flags[40];
    /* 0x678 */ u32             zenny;
    /* 0x67C */ u8              unk_67C[4];
    /* 0x680 */ u8              party_formation;
    /* 0x681 */ u8              unk_681;
    /* 0x682 */ u8              field_order[PARTY_SLOT_COUNT];  /* character ids */
    /* 0x685 */ u8              battle_order[PARTY_SLOT_COUNT]; /* character ids */
    /* 0x688 */ u8              unk_688[0x60];
    /* 0x6E8 */ GameClock       play_clock;
    /* 0x6EC */ u8              unk_6EC[0x20];
    /* 0x70C */ u8              fish_best_catch[FISHING_RECORD_COUNT];
    /* 0x72C */ u8              unk_72C[0x20];
    /* 0x74C */ u8              emi_loaded_character_index;
    /* 0x74D */ u8              unk_74D[4];
    /* 0x751 */ u8              snd_bgm_id;
    /* 0x752 */ u8              unk_752[2];
    /* 0x754 */ u32             battle_count;
    /* 0x758 */ u8              unk_758[0x1C];
    /* 0x774 */ u8              inventory_ids[4][INV_SLOTS_PER_CATEGORY];
    /* 0x974 */ u8              inventory_counts[4][INV_SLOTS_PER_CATEGORY];
    /* 0xB74 */ u8              vital_item_ids[INV_VITAL_ITEM_SLOTS];
    /* 0xB94 */ u8              unk_B94[0xE8];
    /* 0xC7C */ GameClock       celerity_timer;
    /* 0xC80 */ GameClock       bonebreak_timer;
    /* 0xC84 */ u8              unk_C84[0x6C];
    /* 0xCF0 */ FairyJob        fairy_jobs[FAIRY_JOB_COUNT];
    /* 0xED0 */ u8              unk_ED0[0x1E0];
} SaveData;

ASSERT_SIZE(SaveData, SAVE_BLOCK_SIZE);
ASSERT_OFFSET(SaveData, scene_event, 0x013);
ASSERT_OFFSET(SaveData, scene_event_timer, 0x016);
ASSERT_OFFSET(SaveData, script_vars, 0x020);
ASSERT_OFFSET(SaveData, area_id, 0x024);
ASSERT_OFFSET(SaveData, entry_facing, 0x027);
ASSERT_OFFSET(SaveData, entry_x, 0x028);
ASSERT_OFFSET(SaveData, entry_y, 0x02C);
ASSERT_OFFSET(SaveData, checksum, 0x070);
ASSERT_OFFSET(SaveData, window_style, 0x07A);
ASSERT_OFFSET(SaveData, characters, 0x090);
ASSERT_OFFSET(SaveData, scene_flag_words, 0x5B0);
ASSERT_OFFSET(SaveData, scene_event_flags, 0x650);
ASSERT_OFFSET(SaveData, zenny, 0x678);
ASSERT_OFFSET(SaveData, party_formation, 0x680);
ASSERT_OFFSET(SaveData, field_order, 0x682);
ASSERT_OFFSET(SaveData, battle_order, 0x685);
ASSERT_OFFSET(SaveData, play_clock, 0x6E8);
ASSERT_OFFSET(SaveData, fish_best_catch, 0x70C);
ASSERT_OFFSET(SaveData, emi_loaded_character_index, 0x74C);
ASSERT_OFFSET(SaveData, snd_bgm_id, 0x751);
ASSERT_OFFSET(SaveData, battle_count, 0x754);
ASSERT_OFFSET(SaveData, inventory_ids, 0x774);
ASSERT_OFFSET(SaveData, inventory_counts, 0x974);
ASSERT_OFFSET(SaveData, vital_item_ids, 0xB74);
ASSERT_OFFSET(SaveData, celerity_timer, 0xC7C);
ASSERT_OFFSET(SaveData, bonebreak_timer, 0xC80);
ASSERT_OFFSET(SaveData, fairy_jobs, 0xCF0);

/* D_801448D8 */
extern SaveData g_SaveData;

#endif
