/* Runs the handler that header.mode selects from the effect handlers at the head of the module. One definition
 * shared by the bmagic effect modules; every change here must verify every member. */
/* func_801EED70 (magic143), func_801EED98 (magic079), func_801EEDA4 (magic042), func_801EEDE4 (magic159),
   func_801EEDF0 (magic173), func_801EEE00 (magic044), func_801EEE04 (magic006), func_801EEE18 (magic218),
   func_801EEE2C (magic145), func_801EEE38 (magic172), func_801EEE58 (magic100), func_801EEE5C (magic122),
   func_801EEE68 (magic121), func_801EEE70 (magic048), func_801EEE90 (magic069), func_801EEE9C (magic144),
   func_801EEEA0 (magic096), func_801EEEA4 (magic045), func_801EEEBC (magic066), func_801EEEC0 (magic125),
   func_801EEEC8 (magic103), func_801EEED0 (magic126), func_801EEED4 (magic130), func_801EEEE0 (magic222),
   func_801EEEE4 (magic078), func_801EEEF0 (magic158), func_801EEEF0 (magic166), func_801EEF08 (magic050),
   func_801EEF30 (magic058), func_801EEF30 (magic063), func_801EEF48 (magic040), func_801EEF60 (magic138),
   func_801EEF64 (magic039), func_801EEF70 (magic046), func_801EEF78 (magic105), func_801EEF78 (magic220),
   func_801EEF80 (magic129), func_801EEF84 (magic097), func_801EEF84 (magic098), func_801EEF9C (magic074),
   func_801EEFB0 (magic073), func_801EEFC0 (magic213), func_801EEFD0 (magic013), func_801EEFD4 (magic137),
   func_801EEFD8 (magic001), func_801EEFDC (magic021), func_801EEFF4 (magic075), func_801EEFF8 (magic012),
   func_801EEFF8 (magic111), func_801EF000 (magic092), func_801EF004 (magic226), func_801EF00C (magic223),
   func_801EF010 (magic120), func_801EF014 (magic017), func_801EF014 (magic081), func_801EF024 (magic219),
   func_801EF04C (magic146), func_801EF054 (magic115), func_801EF064 (magic053), func_801EF080 (magic093),
   func_801EF09C (magic104), func_801EF0A8 (magic087), func_801EF0C0 (magic154), func_801EF0C4 (magic123),
   func_801EF0D0 (magic038), func_801EF0DC (magic009), func_801EF108 (magic083), func_801EF114 (magic132),
   func_801EF158 (magic054), func_801EF16C (magic099), func_801EF190 (magic041), func_801EF1B0 (magic056),
   func_801EF1E0 (magic059), func_801EF20C (magic065), func_801EF210 (magic169), func_801EF270 (magic124),
   func_801EF278 (magic086), func_801EF2D0 (magic067), func_801EF2D8 (magic167), func_801EF2D8 (magic225),
   func_801EF310 (magic101), func_801EF330 (magic076), func_801EF360 (magic043), func_801EF398 (magic020),
   func_801EF3F8 (magic110), func_801EF4C4 (magic062), func_801EF4E0 (magic088), func_801EF56C (magic082),
   func_801EF668 (magic131), func_801EF73C (magic068), func_801EF75C (magic113), func_801EF774 (magic114),
   func_801EF8CC (magic004), func_801EF9E4 (magic015), func_801EF9F0 (magic151), func_801EFA9C (magic003),
   func_801EFF44 (magic060), func_801F0250 (magic008) */
MATCH void BMagic_DispatchEffectMode(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}
