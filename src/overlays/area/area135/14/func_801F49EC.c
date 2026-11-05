#include "area135_14.h"

/* m2c draft with the y offset hoisted into a local matches in multiset but not in schedule (8 differing): retail
 * materializes the 0xFFF38000 constant first and copies the sign-extended unk_07 into the fixup path
 * (addu v1,v0,zero in the bgez delay slot at 0x801F4A58), which every tried form folds away. Permuter candidate. */
INCLUDE_ASM(func_801F49EC);
