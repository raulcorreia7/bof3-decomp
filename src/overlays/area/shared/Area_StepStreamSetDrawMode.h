/* Run the work record's delay-counted stream step (Actor_StepAnimLoop), then stage the area draw mode. */
/* func_801F4740 (area016, area045, area115), func_801F4674 (area033), func_801F4778 (area065), func_801F4770 (area087),
   func_801F52A0 (area088), func_801F4754 (area121), func_801F46AC (area151), func_801F4600 (area152) */
MATCH void Area_StepStreamSetDrawMode(void) {
    Actor_StepAnimLoop();
    Area_SetDrawMode();
}
