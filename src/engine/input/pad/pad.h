#ifndef OVERLAY_INPUT_PAD_H
#define OVERLAY_INPUT_PAD_H

#include "types.h"

/* The repeatable buttons of a pad mask: INPUT_GetRepeatedButtons sees the held keys
 * filtered to the buttons that repeat. */
#define INPUT_DIRECTIONAL                (PADLup | PADLright | PADLdown | PADLleft)
#define INPUT_ACTION_BUTTONS             (PADRup | PADRdown | PADRleft | PADRright | PADL1 | PADL2 | PADR1 | PADR2 | PADstart | PADselect)
#define INPUT_REPEATED(pressed, buttons) (INPUT_GetRepeatedButtons((pressed) & (buttons)))

/* D_80145AA4 */
extern u16 g_InputHeld;

/* Pad masks, one slot per game action. The config screen remaps the six
 * labelled Speak, Move, Action, Menu, View and Change; Confirm and Cancel are
 * read by the menu-like states. Each game state names the slots it reads. */
typedef enum InputSlot {
    INPUT_SLOT_SPEAK,
    INPUT_SLOT_MOVE,
    INPUT_SLOT_MENU,
    INPUT_SLOT_VIEW,
    INPUT_SLOT_CHANGE,
    INPUT_SLOT_UNUSED, /* only the config screen touches it */
    INPUT_SLOT_ACTION,
    INPUT_SLOT_CONFIRM,
    INPUT_SLOT_CANCEL,
    INPUT_SLOT_COUNT
} InputSlot;

/* Field: X talks to people, examines objects and opens chests; the run button
 * walks or runs by the Auto Run option; the triangle starts the lead
 * character's personal action. */
#define FIELD_INPUT_INTERACT        INPUT_SLOT_SPEAK
#define FIELD_INPUT_RUN             INPUT_SLOT_MOVE
#define FIELD_INPUT_MENU            INPUT_SLOT_MENU
#define FIELD_INPUT_VIEW            INPUT_SLOT_VIEW
#define FIELD_INPUT_SWITCH_LEADER   INPUT_SLOT_CHANGE
#define FIELD_INPUT_PERSONAL_ACTION INPUT_SLOT_ACTION

/* World map: X enters the location under the party; the triangle shows a short
 * text guide to the current location; the areas that run the world map variant
 * read the run and view buttons too. */
#define WORLD_INPUT_ENTER           INPUT_SLOT_SPEAK
#define WORLD_INPUT_RUN             INPUT_SLOT_MOVE
#define WORLD_INPUT_VIEW            INPUT_SLOT_VIEW
#define WORLD_INPUT_LOCATION_GUIDE  INPUT_SLOT_ACTION

/* Message window: holding the talk button prints text at the fast step. */
#define MESSAGE_INPUT_SPEED_UP      INPUT_SLOT_SPEAK

#define MENU_INPUT_CONFIRM          INPUT_SLOT_CONFIRM
#define MENU_INPUT_CANCEL           INPUT_SLOT_CANCEL
#define BATTLE_INPUT_CONFIRM        INPUT_SLOT_CONFIRM
#define BATTLE_INPUT_CANCEL         INPUT_SLOT_CANCEL
#define FISHING_INPUT_CAST          INPUT_SLOT_CONFIRM
#define FISHING_INPUT_CANCEL        INPUT_SLOT_CANCEL
extern u16 g_InputMasks[INPUT_SLOT_COUNT];
/* func_8014E640 */
s32        INPUT_GetRepeatedButtons(s32 button_mask);
/* D_80145AA8 */
extern u16 g_InputPressed;
extern u16 g_InputRepeatDelay;
extern u16 g_InputRepeatButtons;

#endif
