#ifndef COLOR_PRESETS_H
#define COLOR_PRESETS_H

// i4
// A 0000 0000 0000 0000 0000 0000 0000 1111 >> 0x0  & 0xF  = 0-15 * (255/15 = 17)              = 0-255

// i8
// A 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0-255

// ia4
// I 0000 0000 0000 0000 0000 0000 0000 1110 >> 0x1  & 0x7  = 0-7 * (255/7 = 36.4285714286)     = 0-255
// A 0000 0000 0000 0000 0000 0000 0000 0001 >> 0x0  & 0x1  = 0-255

// ia8
// I 0000 0000 0000 0000 0000 0000 1111 0000 >> 0x4  & 0xF  = 0-15 * (255/15 = 17)              = 0-255
// A 0000 0000 0000 0000 0000 0000 0000 1111 >> 0x0  & 0xF  = 0-15 * (255/15 = 17)              = 0-255

// ia16
// I 0000 0000 0000 0000 1111 1111 0000 0000 >> 0x8  & 0xFF                                     = 0-255
// A 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0-255

// rgba16
//   0000 0000 0000 0000 0000 0000 0001 1111
// R 0000 0000 0000 0000 1111 1000 0000 0000 >> 0xB  & 0x1F = 0-31 * (255/31 = 8.22580645161)   = 0-255
// G 0000 0000 0000 0000 0000 0111 1100 0000 >> 0x6  & 0x1F = 0-31 * (255/31 = 8.22580645161)   = 0-255
// B 0000 0000 0000 0000 0000 0000 0011 1110 >> 0x1  & 0x1F = 0-31 * (255/31 = 8.22580645161)   = 0-255
// A 0000 0000 0000 0000 0000 0000 0000 0001 >> 0x0  & 0x1  = 0-1

// rgba32
// R 1111 1111 0000 0000 0000 0000 0000 0000 >> 0x20 & 0xFF                                     = 0-255
// G 0000 0000 1111 1111 0000 0000 0000 0000 >> 0x10 & 0xFF                                     = 0-255
// B 0000 0000 0000 0000 1111 1111 0000 0000 >> 0x8  & 0xFF                                     = 0-255
// A 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0-255

// ci4
// P 0000 0000 0000 0000 0000 0000 0000 1111 >> 0x0  & 0xF  = 0-15 * (255/15 = 17)              = 0-255
// RGBA16

// ci8
// P 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0-255
// RGBA16

// -- Presets --

#define COLOR_RGBA_WHITE            { 0xFF, 0xFF, 0xFF, 0xFF }
// Grayscale color presets
#define COLOR_RGB_WHITE             { 0xFF, 0xFF, 0xFF } // 255 255 255
#define COLOR_RGB_LIGHT             { 0xBF, 0xBF, 0xBF } // 191 191 191
#define COLOR_RGB_GRAY              { 0x7F, 0x7F, 0x7F } // 127 127 127
#define COLOR_RGB_DARK              { 0x3F, 0x3F, 0x3F } //  63  63  63
#define COLOR_RGB_BLACK             { 0x00, 0x00, 0x00 } //   0   0   0
// Primary/secondary/tertiary color presets
#define COLOR_RGB_RED               { 0xFF, 0x00, 0x00 } // 255   0   0
#define COLOR_RGB_ORANGE            { 0xFF, 0x7F, 0x00 } // 255 127   0
#define COLOR_RGB_YELLOW            { 0xFF, 0xFF, 0x00 } // 255 255   0
#define COLOR_RGB_LIME              { 0x7F, 0xFF, 0x00 } // 127 255   0
#define COLOR_RGB_GREEN             { 0x00, 0xFF, 0x00 } //   0 255   0
#define COLOR_RGB_SPRING            { 0x00, 0xFF, 0x7F } //   0 255 127
#define COLOR_RGB_CYAN              { 0x00, 0xFF, 0xFF } //   0 255 255
#define COLOR_RGB_SKY               { 0x00, 0x7F, 0xFF } //   0 127 255
#define COLOR_RGB_BLUE              { 0x00, 0x00, 0xFF } //   0   0 255
#define COLOR_RGB_PURPLE            { 0x7F, 0x00, 0xFF } // 127   0 255
#define COLOR_RGB_MAGENTA           { 0xFF, 0x00, 0xFF } // 255   0 255
#define COLOR_RGB_PINK              { 0xFF, 0x00, 0x7F } // 255   0 127
// Elemental color presets
#define COLOR_RGB_JRB_SKY           { 0x50, 0x64, 0x5A } //  80 100  90
#define COLOR_RGB_WATER             { 0x05, 0x50, 0x96 } //   5  80 150
#define COLOR_RGB_LAVA              { 0x8F, 0x06, 0x00 } // 143   6   0
#define COLOR_RGB_SAND              { 0xDC, 0xA9, 0x73 } // 220 169 115
#define COLOR_RGB_ELECTRIC          { 0xFF, 0xEE, 0x00 } // 255 238   0
// Goddard-specific
#define COLOR_RGBF_WHITE            { 1.0f, 1.0f, 1.0f }
#define COLOR_RGBF_RED              { 1.0f, 0.0f, 0.0f }
#define COLOR_RGBF_GREEN            { 0.0f, 1.0f, 0.0f }
#define COLOR_RGBF_BLUE             { 0.0f, 0.0f, 1.0f }
#define COLOR_RGBF_ERR_DARK_BLUE    { 0.0f, 0.0f, 6.0f }
#define COLOR_RGBF_PINK             { 1.0f, 0.0f, 1.0f }
#define COLOR_RGBF_BLACK            { 0.0f, 0.0f, 0.0f }
#define COLOR_RGBF_GREY             { 0.6f, 0.6f, 0.6f }
#define COLOR_RGBF_DARK_GREY        { 0.4f, 0.4f, 0.4f }
#define COLOR_RGBF_YELLOW           { 1.0f, 1.0f, 1.0f }

#define COLOR_I4_BLACK                 0x0 // 0000
#define COLOR_I4_WHITE                 0xF // 1111

#define COLOR_I8_BLACK                 0x0 // 0000 0000
#define COLOR_I8_WHITE                 0xF // 1111 1111

#define COLOR_IA4_BLACK                0x1 // 0001
#define COLOR_IA4_GRAY                 0x7 // 0111
#define COLOR_IA4_WHITE                0xF // 1111

#define COLOR_IA8_BLACK               0x0F // 0000 1111
#define COLOR_IA8_GRAY                0x7F // 0111 1111
#define COLOR_IA8_WHITE               0xFF // 1111 1111

#define COLOR_IA16_BLACK            0x00FF // 0000 0000 1111 1111
#define COLOR_IA16_GRAY             0x7FFF // 0111 1111 1111 1111
#define COLOR_IA16_WHITE            0xFFFF // 1111 1111 1111 1111

#define COLOR_RGBA16_BLACK          0x0001 // 0000 0000 0000 0000,  0  0  0 31
#define COLOR_RGBA16_DARK_GRAY      0x39CF // 0011 1001 1100 1111,  7  7  7 31
#define COLOR_RGBA16_GRAY           0x7BDF // 0111 1011 1101 1111, 15 15 15 31
#define COLOR_RGBA16_LIGHT_GRAY     0xBDEF // 1011 1101 1110 1111, 23 23 23 31
#define COLOR_RGBA16_WHITE          0xFFFF // 1111 1111 1111 1111, 31 31 31 31

#define COLOR_RGBA32_BLACK      0x000000FF //   0   0   0 255
#define COLOR_RGBA32_DARK_GRAY  0x3F3F3FFF //  63  63  63 255
#define COLOR_RGBA32_GRAY       0x7F7F7FFF // 127 127 127 255
#define COLOR_RGBA32_LIGHT_GRAY 0xBFBFBFFF // 191 191 191 255
#define COLOR_RGBA32_WHITE      0xFFFFFFFF // 255 255 255 255

#define COLOR_RGBA32_RED        0xFF0000FF // 255   0   0
#define COLOR_RGBA32_ORANGE     0xFF7F00FF // 255 127   0
#define COLOR_RGBA32_YELLOW     0xFFFF00FF // 255 255   0
#define COLOR_RGBA32_LIME       0x7FFF00FF // 127 255   0
#define COLOR_RGBA32_GREEN      0x00FF00FF //   0 255   0
#define COLOR_RGBA32_SPRING     0x00FF7FFF //   0 255 127
#define COLOR_RGBA32_CYAN       0x00FFFFFF //   0 255 255
#define COLOR_RGBA32_SKY        0x007FFFFF //   0 127 255
#define COLOR_RGBA32_BLUE       0x0000FFFF //   0   0 255
#define COLOR_RGBA32_PURPLE     0x7F00FFFF // 127   0 255
#define COLOR_RGBA32_MAGENTA    0xFF00FFFF // 255   0 255
#define COLOR_RGBA32_PINK       0xFF007FFF // 255   0 127

#define COLOR_RGBA32_JRB_SKY    0x50645AFF //  80 100  90
#define COLOR_RGBA32_WATER      0x055096FF //   5  80 150
#define COLOR_RGBA32_LAVA       0x8F0600FF // 143   6   0
#define COLOR_RGBA32_SAND       0xDCA973FF // 220 169 115
#define COLOR_RGBA32_ELECTRIC   0xFFEE00FF // 255 238   0

#define COLOR_RGBA32_AMP_LIGHT      COLOR_RGBA32_YELLOW //! COLOR_RGBA32_ELECTRIC doesn't work?
#define COLOR_RGBA32_STAR_LIGHT     COLOR_RGBA32_YELLOW //! 0xFFF000FF doesn't work?
#define COLOR_RGBA32_FLAME_LIGHT    COLOR_RGBA32_RED    //! COLOR_RGBA32_LAVA doesn't work?

#define COLOR_RGBA32_ACYAN          0x00FFFF00
#define COLOR_RGBA32_ABLUE          0x0000FF00

#define COLOR_RGBA32_DEBUG_DEFAULT  0x00FF0000
#define COLOR_RGBA32_DEBUG_ALPHA    0x0000007F
#define COLOR_RGBA32_DEBUG_HITBOX   0x800000FF
#define COLOR_RGBA32_DEBUG_HURTBOX  0x8FF00000
#define COLOR_RGBA32_DEBUG_POSITION 0x80FFFFFF

#endif // COLOR_PRESETS_H

