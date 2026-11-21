/* Runs the handler that header.mode (byte 0x01) selects from the module head's seven-handler table. */
/* func_801EEC20 (magic088), func_801EEC20 (magic150) */
MATCH void func_801EEC20(void) {
    Callback handlers[7];

    memcpy(handlers, D_801EEC04, sizeof(handlers));
    SYS_DISPATCH_BYTE(handlers, g_Task->header.mode);
}
