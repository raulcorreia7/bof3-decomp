#include "engine/slus/slus.h"

/* Runs the scrolling choice step that g_UIMessageStep selects from g_UIMessageScrollStateSteps. */
MATCH void UI_MessageRunScrollChoice(void) {
    MessageChoiceSteps handlers;

    handlers = g_UIMessageScrollStateSteps;
    handlers.steps[g_UIMessageStep]();
}
