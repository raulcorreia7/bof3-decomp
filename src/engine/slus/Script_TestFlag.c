#include "engine/slus/slus.h"

/* reports bit **cursor of the D_80145548 flag byte.
 */
/* func_8015B83C */
MATCH s32 Script_TestFlag(u8** cursor) {
    return SYS_TestFlag((u8*)&D_80145548, **cursor) & BYTE_MASK;
}
