/* Reset the message request, then store the value the menu selection picks in g_ScriptVars. One source for the world area overlays; each member passes its reset sentinel and two state values. */
static inline void WorldMap_SelectAnswerValue(u16 reset, u8 state0, u8 state1) {
    u8 value;

    g_MessageRequest = reset;
    switch (g_MessageChoice) {
        case 0:
            value = state0;
            break;
        case 1:
            value = state1;
            break;
        default:
            return;
    }
    g_ScriptVars[0] = value;
}
