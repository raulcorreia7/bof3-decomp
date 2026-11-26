#include "engine/game/00/game_00.h"

/* The high nibble of an actor script opcode selects its handler group. */
typedef enum ActorScriptGroup {
    ACTOR_SCRIPT_GROUP_FLOW       = 0x00, /* jumps, branches, calls: Script_OpsRunFlow */
    ACTOR_SCRIPT_GROUP_WALK       = 0x10, /* 0x10 to 0x4F: step toward a facing (bits 3-5) for a count (bits 0-2) */
    ACTOR_SCRIPT_GROUP_SET_UNK_01 = 0x50, /* store the low nibble in the interaction state byte 1 */
    ACTOR_SCRIPT_GROUP_FACE       = 0x60, /* Script_OpsRunFace */
    ACTOR_SCRIPT_GROUP_STAGE      = 0x80, /* Script_OpsRunStage */
    ACTOR_SCRIPT_GROUP_SPAWN      = 0x90, /* Script_OpsRunSpawn */
    ACTOR_SCRIPT_GROUP_STEP_BACK  = 0xA0, /* move the cursor back one record */
    ACTOR_SCRIPT_GROUP_APPEARANCE = 0xC0, /* Script_OpsRunAppearance */
    ACTOR_SCRIPT_GROUP_WAIT       = 0xD0, /* Script_OpsRunWait */
    ACTOR_SCRIPT_GROUP_CONTROL    = 0xE0, /* Script_OpsRunControl */
    ACTOR_SCRIPT_GROUP_MOTION     = 0xF0, /* Script_OpsRunMotion */
} ActorScriptGroup;

/* func_801A8D38 */
/* Runs the actor script at the cursor and returns the facing it selects. */
MATCH u8 Script_Run(void* sub, s32 target) {
    u8 script;
    u8 value;
    u8 sel;

    sel           = TASK(Actor)->direction;
    g_ScriptState = (void*)sub;
    sel           = Script_OpsRunFlow(sub, (u8*)target, sel);
    script        = ((u8*)target)[((ScriptState*)sub)->cursor];
    switch (script & 0xF0) {
        case ACTOR_SCRIPT_GROUP_WALK:
        case ACTOR_SCRIPT_GROUP_WALK + 0x10:
        case ACTOR_SCRIPT_GROUP_WALK + 0x20:
        case ACTOR_SCRIPT_GROUP_WALK + 0x30:
            value = ((u8*)target)[((ScriptState*)sub)->cursor];
            sel   = (u8)(value - 0x10) >> 3;
            value &= 7;
            ((ScriptState*)sub)->steps = value;
            if (value != 0) {
                if (Actor_GetOwner() != 2) {
                    Area_MoveActorRoute(sub, sel);
                } else {
                    Area_SetFacingOffsetX(sel);
                }
            }
            break;
        case ACTOR_SCRIPT_GROUP_SET_UNK_01:
            ((ScriptState*)sub)->unk_01 = script & 0xF;
            break;
        case ACTOR_SCRIPT_GROUP_FACE:
            sel = Script_OpsRunFace(sub, target, sel);
            break;
        case ACTOR_SCRIPT_GROUP_STAGE:
            sel = Script_OpsRunStage(sub, (const u8*)target, sel);
            break;
        case ACTOR_SCRIPT_GROUP_SPAWN:
            sel = Script_OpsRunSpawn(sub, (u8*)target, sel);
            break;
        case ACTOR_SCRIPT_GROUP_STEP_BACK:
            ((ScriptState*)sub)->cursor--;
            break;
        case ACTOR_SCRIPT_GROUP_APPEARANCE:
            sel = Script_OpsRunAppearance(sub, target, sel);
            break;
        case ACTOR_SCRIPT_GROUP_WAIT:
            sel = Script_OpsRunWait(sub, (u8*)target, sel);
            break;
        case ACTOR_SCRIPT_GROUP_CONTROL:
            sel = Script_OpsRunControl(sub, target, sel);
            break;
        case ACTOR_SCRIPT_GROUP_MOTION:
            sel = Script_OpsRunMotion(sub, (const u8*)target, sel);
            break;
    }
    ((ScriptState*)sub)->cursor++;
    return sel;
}
