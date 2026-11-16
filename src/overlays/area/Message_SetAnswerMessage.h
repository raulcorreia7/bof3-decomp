/* Stores the message id the menu choice g_MessageChoice selects in g_MessageRequest. */
MATCH void Message_SetAnswerMessage(void) {
    switch (g_MessageChoice) {
        case 0:
            g_MessageRequest = MSG_250;
            break;
        case 1:
            g_MessageRequest = MSG_251;
            break;
        case 2:
            g_MessageRequest = MSG_252;
            break;
        case 3:
            g_MessageRequest = MSG_253;
            break;
        case 4:
            g_MessageRequest = MSG_249;
            break;
    }
}
