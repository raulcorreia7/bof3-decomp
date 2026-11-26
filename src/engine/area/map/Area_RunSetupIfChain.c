#include "engine/game/00/game_00.h"

/* func_801A4518 */
/* Runs the branch of the first holding test of a 0xF4 chain. */
MATCH u8* Area_RunSetupIfChain(u8* script) {
    ScriptOpCallback* handler;
    s8                flag;
    s32               lead;
    u8                op;

    flag    = 1;
    lead    = *script;
    handler = (ScriptOpCallback*)(&g_AreaScriptTests + ((lead << 24) >> 22));
    script += 1;
    for (;;) {
        op = *script;
        if (op == 0xF5) {
            /* stream terminator: return the cursor after it */
            goto done;
        }
        if (op == 0xF6) {
            script += 1;
            if (flag != 0) {
                if ((*handler)(&script) != 0) {
                    flag = 0;
                    script += 1;
                    script = Area_RunSetupChainBody(script);
                } else {
                    script += 1;
                    script = Area_SkipSetupChainBody(script);
                }
            } else {
                script += 1;
                script = Area_SkipSetupChainBody(script);
            }
        }
        if (*script != 0xF7) {
            continue;
        }
        script += 1;
        if (flag != 0) {
            flag   = 0;
            script = Area_RunSetupChainBody(script);
        } else {
            script = Area_SkipSetupChainBody(script);
        }
    }
done:
    script += 1;
    return script;
}
