#include "shop_00.h"

/* A shop action's name, its horizontal tile offset and six signed corner
 * offsets; func_801D98C0 copies the ten rows to the stack at a 0x14 stride. */
typedef struct ShopActionLayout {
    char name[7];
    u8   unk_07;
    s16  unk_08[6];
} ShopActionLayout;
ASSERT_SIZE(ShopActionLayout, 0x14);
ASSERT_OFFSET(ShopActionLayout, name, 0x00);
ASSERT_OFFSET(ShopActionLayout, unk_07, 0x07);
ASSERT_OFFSET(ShopActionLayout, unk_08, 0x08);

char D_801D0C94[4] = "*";

char D_801D0C98[0x44] = {
    0x82, 0x61, 0x82, 0x92, 0x82, 0x85, 0x82, 0x81, 0x82, 0x94, 0x82, 0x88, 0x81, 0x40, 0x82, 0x8F,
    0x82, 0x86, 0x81, 0x40, 0x82, 0x65, 0x82, 0x89, 0x82, 0x92, 0x82, 0x85, 0x81, 0x40, 0x82, 0x52,
    0x81, 0x69, 0x25, 0x73, 0x81, 0x6A, 0x81, 0x40, 0x25, 0x73, 0x25, 0x73, 0x82, 0x88, 0x25, 0x73,
    0x25, 0x73, 0x82, 0x8D, 0x81, 0x40, 0x82, 0x6B, 0x82, 0x96, 0x81, 0x44, 0x25, 0x73, 0x25, 0x73,
    0x00, 0x65, 0x70, 0x74,
};

char D_801D0CDC[4] = "%3dZ";
u8   D_801D0CE0[4] = {0x00, 0x94, 0x08, 0x00};
char g_MenuStatFormat[4] = "%3d";
char D_801D0CE8[8] = "%3d/   ";
char D_801D0CF0[8] = "   /%3d";
char D_801D0CF8[4] = "%8d";
char D_801D0CFC[12] = "--------";
char g_MenuZennyFormat[4] = "%7d";
char D_801D0D0C[8] = "-------";

ShopActionLayout D_801D0D14[10] = {
    {{'N', 'o', 'r', 'm', 'a', 'l', '\0'}, 6, {0, 0, 0, 0, 0, 0}},
    {{'N', 'o', 'r', 'm', 'a', 'l', '\0'}, 6, {-8, -8, 8, -8, 0, 0}},
    {{'A', 't', 't', 'a', 'c', 'k', '\0'}, 6, {0, -8, 0, 8, 0, 0}},
    {{'D', 'e', 'f', 'e', 'n', 's', 'e'}, 7, {-4, 0, 4, 0, 0, 0}},
    {{'N', 'o', 'r', 'm', 'a', 'l', '\0'}, 6, {-8, -8, 8, -8, 0, 8}},
    {{'A', 't', 't', 'a', 'c', 'k', '\0'}, 6, {0, -8, -8, 8, 8, 8}},
    {{'D', 'e', 'f', 'e', 'n', 's', 'e'}, 7, {0, 0, -8, 0, 8, 0}},
    {{'C', 'h', 'a', 'i', 'n', '\0', '\0'}, 5, {-4, -12, 0, 0, 4, 12}},
    {{'M', 'a', 'g', 'i', 'c', '\0', '\0'}, 5, {-12, -4, 12, -4, 0, 4}},
    {{'R', 'e', 'f', 'u', 'g', 'e', '\0'}, 6, {0, -12, -8, 0, 8, 12}},
};

u8 D_801D0DDC[4] = {0x00, 0x01, 0x02, 0x00};

char g_MenuClockFormat[12] = "%02d";
