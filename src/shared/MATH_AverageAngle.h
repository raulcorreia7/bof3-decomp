/* Average two 12-bit angles along the shorter arc: order the pair, then use the plain midpoint below half a turn and the wrapped midpoint at or above it. */
/* func_801F35B0 (area088), func_801F8F40 (scena07), func_801F9420 (scena08) */
MATCH u32 MATH_AverageAngle(u16 a, u16 b) {
    u16 t;

    a &= 0xFFF;
    b &= 0xFFF;
    if (b < a) {
        t = a;
        a = b;
        b = t;
    }
    if ((b - a) < ONE / 2) {
        return (u32)(b + a) >> 1;
    }
    return (u16)(((b + a) >> 1) + ONE / 2);
}
