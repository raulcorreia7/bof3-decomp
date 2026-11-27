/* Stores the message id the menu choice g_UIMessageChoice selects in g_UIMessageRequest. */
MATCH void UI_MessageAnswerSet(void) {
    switch (g_UIMessageChoice) {
        case 0:
            g_UIMessageRequest = MSG_AREA175_HELP_WHICH_JOBS;
            break;
        case 1:
            g_UIMessageRequest = MSG_AREA175_HELP_ASSIGN_JOBS;
            break;
        case 2:
            g_UIMessageRequest = MSG_AREA175_HELP_ABILITIES;
            break;
        case 3:
            g_UIMessageRequest = MSG_AREA175_HELP_HOUSING;
            break;
        case 4:
            g_UIMessageRequest = MSG_AREA175_HELP_UP_TO_YOU;
            break;
    }
}
