#include "engine/slus/slus.h"

/* maps the record's value byte (Item_GetKind, kind kind_id, index index) to a role 0..4 for values 1..5, else
 * 0; when bit bit of the flag byte (Item_GetEquipability) is set it returns 1 if role equals the role (roles 0..3) or is
 * 4/5 (role 4), else 0.
 */
MATCH s32 Char_TestAbilityRole(s32 bit, s32 role, s32 kind_id, s32 index) {
    s32 kind;

    switch (Item_GetKind(kind_id & 0xFF, index & 0xFF) & 0xFF) {
        case 1:
            kind = 0;
            break;
        case 2:
            kind = 1;
            break;
        case 3:
            kind = 2;
            break;
        case 4:
            kind = 3;
            break;
        case 5:
            kind = 4;
            break;
        default:
            return 0;
    }
    if ((((Item_GetEquipability(kind_id & 0xFF, index & 0xFF) & 0xFF) >> bit) & 1) != 0) {
        if ((kind & 0xFF) < 4u && (kind & 0xFF) == (role & 0xFF)) {
            return 1;
        }
        if ((kind & 0xFF) == 4 && ((role & 0xFF) == (kind & 0xFF) || (role & 0xFF) == 5)) {
            return 1;
        }
    }
    return 0;
}
