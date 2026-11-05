#include "batl_end_00.h"

/* The retail copy takes six Callback slots (three-word batches) out of
 * D_801EEC28; the shared handler-table types cover three and five slots. */
typedef struct BattleHandlerTable6 {
    Callback handlers[6];
} BattleHandlerTable6;

extern BattleHandlerTable6 D_801EEC28;

MATCH void func_801EFD98(void) {
    BattleHandlerTable6 handlers = D_801EEC28;

    handlers.handlers[((u8*)g_MenuCurrentPanel)[2]]();
}
