/* Sets the GTE rotation and translation to the effect actor's position and
 * half its height span, multiplied by the camera matrix. One definition shared
 * by the bmagic effect modules; every change here must verify every member. */
/* func_801F06E0 (magic006), func_801EF9F4 (magic039), func_801EF5C0 (magic041), func_801F0110 (magic053), func_801EF700
   (magic055), func_801EF410 (magic056), func_801EF69C (magic058), func_801EF414 (magic062), func_801EF784 (magic066),
   func_801EFBE8 (magic068), func_801F07C8 (magic078), func_801EF3A8 (magic079), func_801EF4BC (magic082), func_801EF794
   (magic083), func_801EF1C8 (magic086), func_801EF430 (magic088), func_801EF700 (magic091), func_801EF4D0 (magic092),
   func_801EF7AC (magic093), func_801EF14C (magic095), func_801EFA8C (magic096), func_801EEFCC (magic101), func_801EF128
   (magic103), func_801EF998 (magic110), func_801EF440 (magic113), func_801EF60C (magic118), func_801F0BF8 (magic120),
   func_801EF1A8 (magic125), func_801EF118 (magic126), func_801F0604 (magic131), func_801EF1E4 (magic144), func_801F01BC
   (magic151), func_801EF228 (magic167), func_801EF1A0 (magic218), func_801F0284 (magic220), func_801EF7CC (magic222),
   func_801F0724 (magic226), Effect_SetActorMatrix_801F0138 (magic110), Effect_SetActorMatrix_801F0D44 (magic131),
   Effect_SetActorMatrix_801F1DC0 (magic151), Effect_SetActorMatrix_801F0168 (magic222) */
MATCH void Effect_SetActorMatrix(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}
