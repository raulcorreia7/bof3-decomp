#include "engine/slus/slus.h"

/* Runs the scrolling choice step that g_UiMessageStep selects from g_UiMessageScrollStateSteps. */
MATCH void UI_MessageRunScrollChoice(void) {
    MessageChoiceSteps handlers;

    handlers = g_UiMessageScrollStateSteps;
    handlers.steps[g_UiMessageStep]();
}
