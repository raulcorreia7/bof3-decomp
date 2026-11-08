#include "area128_13.h"

/* tried: if(choice) direct stores, ternary/temp tail-merge, if(choice==0) direct
 * stores, pre-set temp; needs bnez-to-else with li $v0,0xB in delay slot,
 * 0-path jumps to common with li $v0,3 in delay, else li $v0,8 falls to common
 * store of D_80146875 (leaf, tail-merged, $v0 carries all values) */
INCLUDE_ASM(func_801F2F84);
