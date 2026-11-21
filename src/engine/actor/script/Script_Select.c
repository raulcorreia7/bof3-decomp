#include "engine/slus/slus.h"

/* forwards the script_index byte to func_8014D6DC with a zero extra
 * operand.
 */
MATCH void Script_Select(u8 script_index) {
    Script_Begin(script_index, 0);
}
