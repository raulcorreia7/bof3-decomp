#include "game_00.h"

struct GameSelState {
    u8           pad[0x3B90];
    volatile u16 state;
    volatile u16 substate;
};

#define GAME_SEL_STATE ((volatile struct GameSelState*)&D_80140000)

MATCH void Game_RunMainLoop(void) {
    const Callback* callbacks;

    GAME_SEL_STATE->state    = 0u;
    GAME_SEL_STATE->substate = 0u;
    func_8014BA04();
    Menu_ResetPanelTasks();

    while (1) {
        callbacks = g_GameStates;
        callbacks[GAME_SEL_STATE->state]();
        func_80198CAC();
        CallbackWait(1u);
    }
}
