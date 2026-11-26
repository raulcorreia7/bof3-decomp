#include "engine/slus/slus.h"

/* Reports bit **cursor of the found-genes mask. */
MATCH s32 func_8015B83C(u8** cursor) {
    return SYS_TestFlag((u8*)&g_SaveData.found_genes, **cursor) & BYTE_MASK;
}
