#include "battle_03.h"

MATCH u8 func_801DDE7C(u32 counter_index, u32 packed_value) {
    u32   table_index;
    char* counter_table;
    char* value_table;
    char* ptr;
    char  counter;

    table_index   = (packed_value >> 6) & 0x3FCu;
    counter_table = *(char**)((char*)D_801C8950 + table_index);
    ptr           = counter_table + (counter_index & 0xFF);
    counter       = *ptr;
    if (counter == 'c') {
        return 1u;
    }
    *ptr                              = counter + 1;
    value_table                       = *(char**)((char*)D_801C893C + table_index);
    value_table[counter_index & 0xFF] = packed_value;
    return 0u;
}
