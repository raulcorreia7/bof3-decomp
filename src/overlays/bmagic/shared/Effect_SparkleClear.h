/* Frees the current sparkle record by clearing its header, shade row and type. */
/* func_801F006C (magic070), func_801F006C (magic071), func_801F006C (magic072) */
MATCH void Effect_SparkleClear(void) {
    g_BMagicSparkle->header.flags = 0;
    g_BMagicSparkle->header.mode  = 0;
    g_BMagicSparkle->header.step  = 0;
    g_BMagicSparkle->unk_03       = 0;
    g_BMagicSparkle->unk_04       = 0;
}
