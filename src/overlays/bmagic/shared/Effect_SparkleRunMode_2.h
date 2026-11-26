/* Runs the handler that header.mode of the current sparkle selects from g_BMagicSparkleRecordModes. */
/* func_801EF338 (magic162), func_801EF338 (magic168) */
MATCH void Effect_SparkleRunMode(void) {
    BMagicEffect* work;

    work = g_BMagicSparkle;
    g_BMagicSparkleRecordModes[work->header.mode]();
}
