/* Stores the message id the menu choice g_MessageChoice selects in g_MessageRequest. */
MATCH void Message_SetAnswerMessage(void) {
    switch (g_MessageChoice) {
        case 0:
            g_MessageRequest = FAIRY_MESSAGE_HELP_JOBS;
            break;
        case 1:
            g_MessageRequest = FAIRY_MESSAGE_HELP_ASSIGNING;
            break;
        case 2:
            g_MessageRequest = FAIRY_MESSAGE_HELP_ABILITIES;
            break;
        case 3:
            g_MessageRequest = FAIRY_MESSAGE_HELP_HOUSING;
            break;
        case 4:
            g_MessageRequest = FAIRY_MESSAGE_HELP_UP_TO_YOU;
            break;
    }
}
