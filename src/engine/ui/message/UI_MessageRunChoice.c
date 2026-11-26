#include "engine/slus/slus.h"

/* Runs the choice step that g_UiMessageStep selects from g_UiMessageChoiceStateSteps. */
MATCH void UI_MessageRunChoice(void) {
    MessageStateSteps handlers;

    handlers = g_UiMessageChoiceStateSteps;
    handlers.steps[g_UiMessageStep]();
}
