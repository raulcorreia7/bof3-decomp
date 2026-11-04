#include "engine/slus/slus.h"

/* forwards the selector byte to func_8014D6DC with a zero extra
 * operand.
 */
MATCH void Actor_SelectScript(u8 selector) {
    Actor_BeginScript(selector, 0);
}
