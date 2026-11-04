#include "shop_00.h"

/* Handler table dispatched by the shop state counter. */

MATCH void Shop_DispatchStep(void) {
    SYS_DISPATCH_BYTE(D_801E5144, D_80148650);
}
