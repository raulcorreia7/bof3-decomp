/* Stores the message id the menu choice g_UiMessageChoice selects in g_UiMessageRequest. */
MATCH void UI_MessageAnswerSet(void) {
    switch (g_UiMessageChoice) {
        case 0:
            g_UiMessageRequest = MSG_AREA175_HELP_WHICH_JOBS;
            break;
        case 1:
            g_UiMessageRequest = MSG_AREA175_HELP_ASSIGN_JOBS;
            break;
        case 2:
            g_UiMessageRequest = MSG_AREA175_HELP_ABILITIES;
            break;
        case 3:
            g_UiMessageRequest = MSG_AREA175_HELP_HOUSING;
            break;
        case 4:
            g_UiMessageRequest = MSG_AREA175_HELP_UP_TO_YOU;
            break;
    }
}
