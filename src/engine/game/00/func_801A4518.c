#include "game_00.h"

MATCH u8* func_801A4518(u8* script) {
    ScriptFunc* handler;
    s8          flag;
    s32         lead;
    u8          op;

    flag    = 1;
    lead    = *script;
    handler = (ScriptFunc*)(&g_AreaScriptTests + ((lead << 24) >> 22));
    script += 1;
    for (;;) {
        op = *script;
        if (op == 0xF5) {
            /* stream terminator: return the cursor after it. */
            goto done;
        }
        if (op == 0xF6) {
            script += 1;
            if (flag != 0) {
                if ((*handler)(&script) != 0) {
                    flag = 0;
                    script += 1;
                    script = func_801A4640(script);
                } else {
                    script += 1;
                    script = func_801A46E8(script);
                }
            } else {
                script += 1;
                script = func_801A46E8(script);
            }
        }
        if (*script != 0xF7) {
            continue;
        }
        script += 1;
        if (flag != 0) {
            flag   = 0;
            script = func_801A4640(script);
        } else {
            script = func_801A46E8(script);
        }
    }
done:
    script += 1;
    return script;
}
