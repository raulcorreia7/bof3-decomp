/* Reset the message request, then set the scene event step the menu selection picks. One source for the world area overlays. */
static inline void WorldMap_SelectEventStep(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_MessageChoice == 0) {
        g_SceneEventStep = 2;
    } else if (g_MessageChoice == 1) {
        g_SceneEventStep = 0xA;
    } else {
        g_SceneEventStep = 0x14;
    }
}
