#ifndef GAME_TEXT_H
#define GAME_TEXT_H

/* The string piece that writes each control code into a text record. */
#define T_END                  "\x00"
#define T_NEWLINE              "\x01"
#define T_PAGE                 "\x02"
#define T_GOTO                 "\x03"
#define T_INSERT               "\x04"
#define T_COLOR                "\x05"
#define T_NOCOLOR              "\x06"
#define T_VAR                  "\x07"
#define T_LINK                 "\x08"
#define T_NOP                  "\x09"
#define T_SE                   "\x0A"
#define T_GAP                  "\x0B"
#define T_BOX                  "\x0C"
#define T_OFFSET               "\x0D"
#define T_CURSOR               "\x0E"
#define T_STYLE                "\x0F"
#define T_STYLE_ALT            "\x10"
#define T_WAIT                 "\x11"
#define T_SKIP                 "\x12"
#define T_SKIP_ALT             "\x13"
#define T_CHOICE               "\x14"
#define T_NUM                  "\x15"
#define T_BOXEND               "\x16"
#define T_BACKSPACE            "\x90"

/* The operand a STRING_COLOR code loads. */
#define STRING_COLOR_RED       0x02
#define T_RED                  "\x02"
#define STRING_COLOR_BLUE      0x03
#define T_BLUE                 "\x03"

/* Glyph bytes outside the ASCII letters and digits, and the string form that
 * concatenates them. STRING_SPACE is the message font's space glyph; the plain
 * ASCII space belongs to the interface font. The two fullwidth slots draw the
 * same shapes as their plain counterparts, one glyph apart. */
#define STRING_COLON           0x3A
#define T_COLON                "\x3A"
#define STRING_SEMICOLON       0x3B
#define T_SEMI                 "\x3B"
#define STRING_COMMA           0x3C
#define T_COMMA                "\x3C"
#define STRING_HYPHEN          0x3D
#define T_DASH                 "\x3D"
#define STRING_PERIOD          0x3E
#define T_DOT                  "\x3E"
#define STRING_QUESTION        0x5C
#define T_QUESTION             "\x5C"
#define STRING_EXCLAMATION     0x5D
#define T_BANG                 "\x5D"
#define STRING_PLUS            0x8B
#define T_PLUS                 "\x8B"
#define STRING_FULLWIDTH_COMMA 0x8D
#define T_WIDE_COMMA           "\x8D"
#define STRING_APOSTROPHE      0x8E
#define T_APOS                 "\x8E"
#define STRING_FULLWIDTH_COLON 0x8F
#define T_WIDE_COLON           "\x8F"
#define STRING_SPACE           0xFF
#define T_SP                   "\xFF"

/* The game's text encoding. Letters and digits are ASCII; space and the
 * punctuation below have bytes of their own. Every byte has a value form
 * (STRING_SPACE, for code) and a short string piece (T_SP, for data), so game
 * text is plain C string joining:
 *
 *     "Green" T_SP "Apple"
 *     "Gaea" T_APOS "s" T_SP "Breath"
 *     "Hi" T_NEWLINE "there" T_DOT
 *
 * A fixed-size name field needs no trailing T_END fill; C zero-fills it.
 * The menu, window and scenario code encode and decode through this table
 * (@source: wiki:data/text).
 */

/* Control codes. Each name follows the case body that proves it; the codes
 * with no proven effect keep the plainest honest name. */
typedef enum TextCommand {
    STRING_END       = 0x00,
    STRING_NEWLINE   = 0x01,
    STRING_PAGE      = 0x02,
    STRING_GOTO      = 0x03,
    STRING_INSERT    = 0x04,
    STRING_COLOR     = 0x05,
    STRING_NOCOLOR   = 0x06,
    STRING_VAR       = 0x07,
    STRING_LINK      = 0x08,
    STRING_NOP       = 0x09,
    STRING_SE        = 0x0A,
    STRING_GAP       = 0x0B,
    STRING_BOX       = 0x0C,
    STRING_OFFSET    = 0x0D,
    STRING_CURSOR    = 0x0E,
    STRING_STYLE     = 0x0F,
    STRING_STYLE_ALT = 0x10,
    STRING_WAIT      = 0x11,
    STRING_SKIP      = 0x12,
    STRING_SKIP_ALT  = 0x13,
    STRING_CHOICE    = 0x14,
    STRING_NUM       = 0x15,
    STRING_BOXEND    = 0x16,
    STRING_BACKSPACE = 0x90,
} TextCommand;

enum {
    BATTLE_TEXT_INITIATIVE_PARTY    = 22,
    BATTLE_TEXT_INITIATIVE_OPPONENT = 23,
    BATTLE_TEXT_CANT_LEARN          = 35,
    BATTLE_TEXT_LEARNED             = 36,
    GAME_TEXT_SEARCH_FOUND          = 2,
    GAME_TEXT_SEARCH_NO_ROOM        = 3,
    GAME_TEXT_SAVE_COMPLETE         = 143,
    GAME_TEXT_INIT_COMPLETE         = 149,
    GAME_TEXT_NO_SAVE_FILE          = 151,
};

#endif
