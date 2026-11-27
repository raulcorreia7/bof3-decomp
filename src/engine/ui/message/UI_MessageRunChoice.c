#include "engine/slus/slus.h"

/* Runs the choice step that g_UIMessageStep selects from g_UIMessageChoiceStateSteps. */
MATCH void UI_MessageRunChoice(void) {
    MessageStateSteps handlers;

    handlers = g_UIMessageChoiceStateSteps;
    handlers.steps[g_UIMessageStep]();
}
