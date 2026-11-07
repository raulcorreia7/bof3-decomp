#ifndef ETC_OVERLAY_H
#define ETC_OVERLAY_H

#include "sys/emi.h"
#include "types.h"

/* The ETC overlays load at 0x801D0C00 and share one payload prologue: a word
 * equal to the archive TOC's cached first word (@source: wiki:formats/emi). The
 * loader compares the two before it starts the payload.
 *
 * Each overlay then begins with a step entry: load the shared step byte, index
 * the overlay's handler table and tail-call the handler. commu01..05 dispatch
 * on the commu step byte D_801F294C that commu00 owns; shisu and bate dispatch
 * on the menu step byte D_80148650. The handler tables and step bytes stay in
 * each image's own header. */

typedef struct OverlayHeader {
    EMIModuleId id; /* 0x00 OverlayId, the TOC's cached first payload word */
} OverlayHeader;

ASSERT_SIZE(OverlayHeader, 0x4);

typedef enum OverlayId {
    ETC_OVERLAY_START   = 18, /* START.EMI#8, start menu */
    ETC_OVERLAY_SHOP    = 19, /* SHOP.EMI#0, shop program */
    ETC_OVERLAY_BATE    = 20, /* BATE.EMI#0, draws an ability list (screen unconfirmed) */
    ETC_OVERLAY_SHISU   = 21, /* SHISU.EMI#0, status menu */
    ETC_OVERLAY_COMMU00 = 24, /* COMMU00.EMI#0, fairy communication minigame */
    ETC_OVERLAY_COMMU01 = 25, /* COMMU01.EMI#7 */
    ETC_OVERLAY_COMMU02 = 26, /* COMMU02.EMI#8 */
    ETC_OVERLAY_COMMU03 = 27, /* COMMU03.EMI#6 */
    ETC_OVERLAY_COMMU04 = 28, /* COMMU04.EMI#6 */
    ETC_OVERLAY_COMMU05 = 29, /* COMMU05.EMI#7 */
    ETC_OVERLAY_GAME00  = 30, /* GAME.EMI#0, game frontend */
    ETC_OVERLAY_SISYOU  = 31, /* SISYOU.EMI#0, master and skill menu */
    ETC_OVERLAY_GAME01  = 32, /* GAME.EMI#1, title */
} OverlayId;

#endif
