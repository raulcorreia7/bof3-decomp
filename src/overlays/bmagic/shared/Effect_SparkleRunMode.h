/* Runs the handler that header.mode of the current sparkle selects from g_BMagicSparkleRecordModes. */
/* func_801EF33C (magic070), func_801EF33C (magic071), func_801EF33C (magic072) */
MATCH void Effect_SparkleRunMode(void) {
    BMagicEffect* work;

    work = g_BMagicSparkle;
    g_BMagicSparkleRecordModes[work->header.mode]();
}
