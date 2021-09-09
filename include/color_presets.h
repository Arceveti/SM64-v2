#ifndef COLOR_PRESETS_H
#define COLOR_PRESETS_H

// Texture formats:
// NOTE: IA4 and RGBA16 formats are tricky, because while their
// composite values are 4bit aligned, their components are not.

// i4
// A 0000 0000 0000 0000 0000 0000 0000 1111 >> 0x0  & 0xF  = 0-15 * (255/15 = 17)              = 0..255

// i8
// A 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0..255

// ia4
// I 0000 0000 0000 0000 0000 0000 0000 1110 >> 0x1  & 0x7  = 0-7 * (255/7 = 36.4285714286)     = 0..255
// A 0000 0000 0000 0000 0000 0000 0000 0001 >> 0x0  & 0x1  = 0-255

// ia8
// I 0000 0000 0000 0000 0000 0000 1111 0000 >> 0x4  & 0xF  = 0-15 * (255/15 = 17)              = 0..255
// A 0000 0000 0000 0000 0000 0000 0000 1111 >> 0x0  & 0xF  = 0-15 * (255/15 = 17)              = 0..255

// ia16
// I 0000 0000 0000 0000 1111 1111 0000 0000 >> 0x8  & 0xFF                                     = 0..255
// A 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0..255

// rgba16
//   0000 0000 0000 0000 0000 0000 0001 1111
// R 0000 0000 0000 0000 1111 1000 0000 0000 >> 0xB  & 0x1F = 0-31 * (255/31 = 8.22580645161)   = 0..255
// G 0000 0000 0000 0000 0000 0111 1100 0000 >> 0x6  & 0x1F = 0-31 * (255/31 = 8.22580645161)   = 0..255
// B 0000 0000 0000 0000 0000 0000 0011 1110 >> 0x1  & 0x1F = 0-31 * (255/31 = 8.22580645161)   = 0..255
// A 0000 0000 0000 0000 0000 0000 0000 0001 >> 0x0  & 0x1  = 0-1

// rgba32
// R 1111 1111 0000 0000 0000 0000 0000 0000 >> 0x20 & 0xFF                                     = 0..255
// G 0000 0000 1111 1111 0000 0000 0000 0000 >> 0x10 & 0xFF                                     = 0..255
// B 0000 0000 0000 0000 1111 1111 0000 0000 >> 0x8  & 0xFF                                     = 0..255
// A 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0..255

// ci4
// P 0000 0000 0000 0000 0000 0000 0000 1111 >> 0x0  & 0xF  = 0-15 * (255/15 = 17)              = 0..255
// RGBA16

// ci8
// P 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0-255
// RGBA16



// -- Presets --


// I4 (I[0..15])
#define COLOR_I4_BLACK                             0x0 // 0000 |  0
#define COLOR_I4_GRAY                              0x7 // 0111 |  7
#define COLOR_I4_WHITE                             0xF // 1111 | 15


// I8 (I[0..255])
#define COLOR_I8_BLACK                            0x00 // 0000 0000 |   0
#define COLOR_I8_GRAY                             0x7F // 0111 1111 | 127
#define COLOR_I8_WHITE                            0xFF // 1111 1111 | 255


// IA4 (I[0..7], A[0..1])
#define COLOR_IA4_BLACK                            0x1 // 0001 | 000 1 | 0 1
#define COLOR_IA4_GRAY                             0x7 // 0111 | 011 1 | 3 1
#define COLOR_IA4_WHITE                            0xF // 1111 | 111 1 | 7 1


// IA8 (I[0..15], A[0..15])
#define COLOR_IA8_BLACK                           0x0F // 0000 1111 |  0 15
#define COLOR_IA8_GRAY                            0x7F // 0111 1111 |  7 15
#define COLOR_IA8_WHITE                           0xFF // 1111 1111 | 15 15


// IA16 (I[0..255], A[0..255])
#define COLOR_IA16_BLACK                        0x00FF // 0000 0000 1111 1111 |   0 255
#define COLOR_IA16_GRAY                         0x7FFF // 0111 1111 1111 1111 | 127 255
#define COLOR_IA16_WHITE                        0xFFFF // 1111 1111 1111 1111 | 255 255


// RGBA16 (RGB[0..31], A[0..1])

// Grayscale
#define COLOR_RGBA16_BLACK                      0x0001 // 0000 0000 0000 0001 | 00000 00000 00000 1 |  0  0  0  1
#define COLOR_RGBA16_DARK_GRAY                  0x39CF // 0011 1001 1100 1111 | 00111 00111 00111 1 |  7  7  7  1
#define COLOR_RGBA16_GRAY                       0x7BDF // 0111 1011 1101 1111 | 01111 01111 01111 1 | 15 15 15  1
#define COLOR_RGBA16_LIGHT_GRAY                 0xBDEF // 1011 1101 1110 1111 | 10111 10111 10111 1 | 23 23 23  1
#define COLOR_RGBA16_WHITE                      0xFFFF // 1111 1111 1111 1111 | 11111 11111 11111 1 | 31 31 31  1

// Crash screen
#define COLOR_RGBA16_CRASH_ERROR                0x6253 // 0110 0010 0101 0011 | 01100 01001 01001 1 | 12  9  9  1
#define COLOR_RGBA16_CRASH_ASSERT               0x5263 // 0101 0010 0110 0011 | 01010 01001 10001 1 | 10  9 21  1
#define COLOR_RGBA16_CRASH_BLACK                COLOR_RGBA16_BLACK
#define COLOR_RGBA16_CRASH_WHITE                COLOR_RGBA16_WHITE


// RGBA32 (RGB[0..255], A[0..255])

// Grayscale
#define COLOR_RGBA32_BLACK                  0x000000FF //   0   0   0 255
#define COLOR_RGBA32_DARK_GRAY              0x3F3F3FFF //  63  63  63 255
#define COLOR_RGBA32_GRAY                   0x7F7F7FFF // 127 127 127 255
#define COLOR_RGBA32_LIGHT_GRAY             0xBFBFBFFF // 191 191 191 255
#define COLOR_RGBA32_WHITE                  0xFFFFFFFF // 255 255 255 255

// Primary/secondary/tertiary
#define COLOR_RGBA32_RED                    0xFF0000FF // 255   0   0 255
#define COLOR_RGBA32_ORANGE                 0xFF7F00FF // 255 127   0 255
#define COLOR_RGBA32_YELLOW                 0xFFFF00FF // 255 255   0 255
#define COLOR_RGBA32_LIME                   0x7FFF00FF // 127 255   0 255
#define COLOR_RGBA32_GREEN                  0x00FF00FF //   0 255   0 255
#define COLOR_RGBA32_SPRING                 0x00FF7FFF //   0 255 127 255
#define COLOR_RGBA32_CYAN                   0x00FFFFFF //   0 255 255 255
#define COLOR_RGBA32_SKY                    0x007FFFFF //   0 127 255 255
#define COLOR_RGBA32_BLUE                   0x0000FFFF //   0   0 255 255
#define COLOR_RGBA32_PURPLE                 0x7F00FFFF // 127   0 255 255
#define COLOR_RGBA32_MAGENTA                0xFF00FFFF // 255   0 255 255
#define COLOR_RGBA32_PINK                   0xFF007FFF // 255   0 127 255

#define COLOR_RGBA32_ACYAN                  0x00FFFF00 //   0 255 255   0
#define COLOR_RGBA32_ABLUE                  0x0000FF00 //   0   0 255   0

// Elemental
#define COLOR_RGBA32_JRB_SKY                0x50645AFF //  80 100  90 255
#define COLOR_RGBA32_WATER                  0x055096FF //   5  80 150 255
#define COLOR_RGBA32_LAVA                   0x8F0600FF // 143   6   0 255
#define COLOR_RGBA32_SAND                   0xDCA973FF // 220 169 115 255
#define COLOR_RGBA32_ELECTRIC               0xFFEE00FF // 255 238   0 255

// Lights
#define COLOR_RGBA32_AMP_LIGHT              COLOR_RGBA32_ELECTRIC
#define COLOR_RGBA32_STAR_LIGHT             0xFFF000FF
#define COLOR_RGBA32_FLAME_LIGHT            COLOR_RGBA32_LAVA

// Mario body lights - these should match the light groups in actors/mario/model.inc.c
#define COLOR_RGBA32_MARIO_LIGHTS_BLUE      0x0000FF00 //   0   0 255   0
#define COLOR_RGBA32_MARIO_LIGHTS_RED       0xFF000000 // 255   0   0   0
#define COLOR_RGBA32_MARIO_LIGHTS_WHITE     0xFFFFFF00 // 255 255 255   0
#define COLOR_RGBA32_MARIO_LIGHTS_BROWN1    0x721C0E00 // 114  28  14   0
#define COLOR_RGBA32_MARIO_LIGHTS_BEIGE     0xFEC17900 // 254 193 121   0
#define COLOR_RGBA32_MARIO_LIGHTS_BROWN2    0x73060000 // 115   6   0   0

// Debug box
#define COLOR_RGBA32_DEBUG_DEFAULT          0x00FF0000 //   0 255   0   0
#define COLOR_RGBA32_DEBUG_ALPHA            0x0000007F //   0   0   0 127
#define COLOR_RGBA32_DEBUG_POSITION         0x80FFFFFF // 128 255 255 255
#define COLOR_RGBA32_DEBUG_HITBOX           0x800000FF // 128   0   0 255
#define COLOR_RGBA32_DEBUG_HURTBOX          0x8FF00000 // 143 240   0   0


// Color RGB(A) Arrays:

// RGBA [0..255]
#define COLOR_RGBA_BLACK            0x00, 0x00, 0x00, 0xFF //   0   0   0 255
#define COLOR_RGBA_DARK             0x3F, 0x3F, 0x3F, 0xFF //  63  63  63 255
#define COLOR_RGBA_GRAY             0x7F, 0x7F, 0x7F, 0xFF // 127 127 127 255
#define COLOR_RGBA_LIGHT            0xBF, 0xBF, 0xBF, 0xFF // 191 191 191 255
#define COLOR_RGBA_WHITE            0xFF, 0xFF, 0xFF, 0xFF // 255 255 255 255

// RGB [0..255]

// Grayscale
#define COLOR_RGB_BLACK             0x00, 0x00, 0x00 //   0   0   0
#define COLOR_RGB_DARK              0x3F, 0x3F, 0x3F //  63  63  63
#define COLOR_RGB_GRAY              0x7F, 0x7F, 0x7F // 127 127 127
#define COLOR_RGB_LIGHT             0xBF, 0xBF, 0xBF // 191 191 191
#define COLOR_RGB_WHITE             0xFF, 0xFF, 0xFF // 255 255 255

// Primary/secondary/tertiary
#define COLOR_RGB_RED               0xFF, 0x00, 0x00 // 255   0   0
#define COLOR_RGB_ORANGE            0xFF, 0x7F, 0x00 // 255 127   0
#define COLOR_RGB_YELLOW            0xFF, 0xFF, 0x00 // 255 255   0
#define COLOR_RGB_LIME              0x7F, 0xFF, 0x00 // 127 255   0
#define COLOR_RGB_GREEN             0x00, 0xFF, 0x00 //   0 255   0
#define COLOR_RGB_SPRING            0x00, 0xFF, 0x7F //   0 255 127
#define COLOR_RGB_CYAN              0x00, 0xFF, 0xFF //   0 255 255
#define COLOR_RGB_SKY               0x00, 0x7F, 0xFF //   0 127 255
#define COLOR_RGB_BLUE              0x00, 0x00, 0xFF //   0   0 255
#define COLOR_RGB_PURPLE            0x7F, 0x00, 0xFF // 127   0 255
#define COLOR_RGB_MAGENTA           0xFF, 0x00, 0xFF // 255   0 255
#define COLOR_RGB_PINK              0xFF, 0x00, 0x7F // 255   0 127

// Elemental
#define COLOR_RGB_JRB_SKY           0x50, 0x64, 0x5A //  80 100  90
#define COLOR_RGB_WATER             0x05, 0x50, 0x96 //   5  80 150
#define COLOR_RGB_LAVA              0x8F, 0x06, 0x00 // 143   6   0
#define COLOR_RGB_SAND              0xDC, 0xA9, 0x73 // 220 169 115
#define COLOR_RGB_ELECTRIC          0xFF, 0xEE, 0x00 // 255 238   0

#define COLOR_RGB_COIN_YELLOW       COLOR_RGB_YELLOW
#define COLOR_RGB_COIN_BLUE         0x80, 0x80, 0xFF // 128 128 255
#define COLOR_RGB_COIN_RED          COLOR_RGB_RED

// Lights
#define DEFAULT_LIGHT_AMB   0x7F
#define DEFAULT_LIGHT_COL   0xFE
#define DEFAULT_LIGHT_DIR   0x28

// RGBF [0..1]
#define COLOR_RGBF_WHITE            1.0f, 1.0f, 1.0f // 0xFF 0xFF 0xFF | 255 255 255
#define COLOR_RGBF_RED              1.0f, 0.0f, 0.0f // 0xFF 0x00 0x00 | 255   0   0
#define COLOR_RGBF_GREEN            0.0f, 1.0f, 0.0f // 0x00 0xFF 0x00 |   0 255   0
#define COLOR_RGBF_BLUE             0.0f, 0.0f, 1.0f // 0x00 0x00 0xFF |   0   0 255
#define COLOR_RGBF_ERR_DARK_BLUE    0.0f, 0.0f, 6.0f // 0x00 0x00 0x5FF? |   0   0 1535?
#define COLOR_RGBF_PINK             1.0f, 0.0f, 1.0f // 0xFF 0x00 0xFF | 255   0 255
#define COLOR_RGBF_BLACK            0.0f, 0.0f, 0.0f // 0x00 0x00 0x00 |   0   0   0
#define COLOR_RGBF_GREY             0.6f, 0.6f, 0.6f // 0x99 0x99 0x99 | 153 153 153
#define COLOR_RGBF_DARK_GREY        0.4f, 0.4f, 0.4f // 0x66 0x66 0x66 | 102 102 102
#define COLOR_RGBF_YELLOW           1.0f, 1.0f, 1.0f // 0xFF 0xFF 0xFF | 255 255 255

#define ARR(a) { a }

#endif // COLOR_PRESETS_H

