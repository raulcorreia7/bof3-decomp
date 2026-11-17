#include "area077_14.h"

/* func_801F60C4 */
MATCH void func_801F60C4(void) {
    AreaLoad*    load;
    ScriptState* state;
    u8*          table;
    u8*          base;
    u8*          entry;
    u8           index;
    ScriptState* record;
    u16          value;
    s32          distance;

    state = g_ScriptState;
    load  = g_AreaLoads[g_GameAreaId];
    table = load->scripts;
    base  = *(u8**)(table + state->script_index * 4);
    entry = base + state->cursor;
    index = entry[2];
    if (func_801FD34C(state, D_801F6B60[index][0], D_801F6B60[index][1], 0x40, -0x400, 4, 0)) {
        record = g_ScriptState;
        value  = record->cursor - 2;
    } else {
        if (index == 4) {
            distance                 = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
            COORD_INT(g_Task->pos.z) = distance;
            Actor_SelectScript(0);
        }
        record = g_ScriptState;
        value  = record->cursor + 1;
    }
    record->cursor = value;
}
