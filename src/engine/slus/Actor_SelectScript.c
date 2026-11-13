#include "engine/slus/slus.h"

/* forwards the script_index byte to func_8014D6DC with a zero extra
 * operand.
 */
MATCH void Actor_SelectScript(u8 script_index) {
    Actor_BeginScript(script_index, 0);
}
