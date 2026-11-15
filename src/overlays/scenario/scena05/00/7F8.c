#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801F743C(void) {
    Actor* actor;

    actor              = g_Task;
    actor->vx          = 0;
    actor->header.mode = actor->header.mode + 1;
}

/* Hint: a3 is lhu of the low half of vx (0x0C), while 0x0C is also read as a word; the same field needs two widths. */
MATCH void func_801F745C(void) {
    Actor* work;

    work = g_Task;
    func_801F7660(work->pos.x.fixed, work->pos.y.fixed, work->pos.z.fixed, work->vx);
    g_Task->vx += 16;
    if (g_Task->vx > 1280) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F74CC(void) {
    Actor_Clear();
}

MATCH void func_801F74EC(void) {
    SYS_DISPATCH_TASK(D_801FD5B4, 1, g_Task);
}

MATCH void func_801F7530(void) {
    Actor* actor;

    actor              = g_Task;
    actor->vx          = 4096;
    actor->header.mode = actor->header.mode + 1;
}

MATCH void func_801F7554(void) {
    SpawnedActor* spawned;
    Actor*        actor;
    u8            slot;

    if ((SP_REF(Actor*, 0x44)->vx & 0xF) == 0) {
        slot = Actor_FindFreeSpawned();
        if (slot != GAME_NONE) {
            spawned               = &g_SpawnedActors[slot];
            spawned->header.flags = 1;
            spawned->type         = 0x26;
            actor                 = g_Task;
            spawned->pos.x.fixed  = actor->pos.x.fixed;
            spawned->pos.y.fixed  = actor->pos.y.fixed;
            spawned->pos.z.fixed  = Area_SampleHeight(actor->pos.x.fixed, actor->pos.y.fixed) << 16;
        }
    }
    actor = g_Task;
    actor->vx -= 1;
    if (actor->vx == 0) {
        actor->header.mode += 1;
    }
}

MATCH void func_801F7640(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F7660);

MATCH void func_801F7A78(void) {
    SYS_DISPATCH_BYTE(D_801FD5DC, D_80146872);
}

MATCH void func_801F7AB4(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7AC8);

MATCH void func_801F83EC(void) {
    SYS_DISPATCH_BYTE(D_801FD5E8, g_SceneState.state_04);
}

MATCH void func_801F8428(void) {
}

MATCH void func_801F8430(void) {
    u8* step;

    step = &D_80146875;
    switch (*step) {
        case 0:
            Message_StartAreaMessage(5);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *step            = 1;
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                D_80146866 = 1;
                *step      = 2;
                SYS_SetFlag(g_SceneFlags, 0);
                func_8019FA28(0x44, 0x1D0000, 0x1E0000, 0x80);
            }
            break;
        case 2:
            if (*g_ScriptVars == 0x2D) {
                SYS_SetFlag(g_SceneFlags, 1);
                Game_ClearScriptActive();
                D_80146865 = 0;
                D_80146866 = 0;
                D_80146867 = 0;
                *step      = 0;
                D_80146874 = 0;
            }
            break;
    }
}

MATCH void func_801F8554(void) {
}

MATCH void func_801F855C(void) {
}
