#include "engine/slus/slus.h"

/* returns the string a resource id selects: the id's group picks one of four
 * base words of the loader-written table at 0x8001A000, and the index is a
 * u16 offset into that group.
 */
/* func_801502D0 */
MATCH u8* Message_GetText(u32 resource_id) { /* func_801502D0 */
    u8*           base;
    volatile u32* entry;
    u8*           ptr;
    u16           offset;

    base   = (u8*)RESOURCE_TABLE_BASE;
    entry  = (volatile u32*)(base + (RESOURCE_ID_GROUP_WORD(resource_id)));
    ptr    = base + *entry;
    offset = *(u16*)(ptr + (RESOURCE_ID_INDEX(resource_id) * 2));
    return ptr + offset;
}
