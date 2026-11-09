#include "sys/gameui.h"
#include "scenario/runtime.h"
#include "common/util.h"

/* One source for the answer-message bodies every world area overlay carries. Kept as statement macros: as inlines these five diverge in 15 members across 6 images (area051, area056, area111, area112, area143, area148 of world01-03): the message id is used after the branch, so it moves to $a0/$v1 and the body grows from 0x28 to 0x38 bytes. */

/* Store the message id the menu selection picks, else the idle id. */
#define WORLD_SELECT_ANSWER_MESSAGE(selected, idle) \
    do {                                            \
        if (MENU_SELECTION_ARMED()) {               \
            g_MessageRequest = (selected);          \
        } else {                                    \
            g_MessageRequest = (idle);              \
        }                                           \
    } while (0)

/* Store the message id when the menu selection equals the selector, else the
 * reset sentinel. */
#define WORLD_SELECT_ANSWER_MESSAGE_ON_VALUE(selection, value) \
    do {                                                       \
        if (g_MessageChoice == (selection)) {                  \
            g_MessageRequest = (value);                        \
        } else {                                               \
            MESSAGE_REQUEST_CLEAR();                           \
        }                                                      \
    } while (0)

/* Arm the message request and the master panel step: the message id and step 6
 * when the menu selection is set, the reset sentinel otherwise. */
#define WORLD_ARM_ANSWER_MESSAGE(request) \
    do {                                  \
        if (MENU_SELECTION_ARMED()) {     \
            g_MessageRequest = (request); \
            g_MenuMasterStep = 6;         \
        } else {                          \
            MESSAGE_REQUEST_CLEAR();      \
        }                                 \
    } while (0)

/* Arm the message request: the idle id when the menu selection is clear, else
 * the selected id and master panel step 6. */
#define WORLD_ARM_ANSWER_MESSAGE_IDLE(idle, selected) \
    do {                                              \
        if (MENU_SELECTION_IDLE()) {                  \
            g_MessageRequest = (idle);                \
        } else {                                      \
            g_MessageRequest = (selected);            \
            g_MenuMasterStep = 6;                     \
        }                                             \
    } while (0)

/* Clear the message request and set the master panel sub-step when the menu
 * selection arms it. */
#define WORLD_FINISH_ANSWER_MESSAGE(substep) \
    do {                                     \
        if (MENU_SELECTION_ARMED()) {        \
            g_MenuMasterSubStep = (substep); \
        }                                    \
        MESSAGE_REQUEST_CLEAR();             \
    } while (0)

/* The master panel step and sub-step the answer messages arm; the sisyou
 * image owns the bytes. */
/* D_801D4286 */
extern u8 g_MenuMasterSubStep;
