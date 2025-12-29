//
// PixArt - 10x10 display using NeoPixel LEDs
// Author: Dale Low <gumbypp@yahoo.com>
//

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// - The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel leds = Adafruit_NeoPixel(100, 2, NEO_GRB + NEO_KHZ800);

#define kGridColorBlue    1
#define kGridColorRed     2
#define kGridColorGreen   3

#define kCodeSmiley      128
#define kCodeTree        129

#define R_COLOUR(rgb) ((rgb >> 16) & 0xFF)
#define G_COLOUR(rgb) ((rgb >> 8) & 0xFF)
#define B_COLOUR(rgb) ((rgb >> 0) & 0xFF)

// display options:
#define OPTION_TREE
#define OPTION_FIREWORKS
#define OPTION_BALLOONS
#define OPTION_DOGGY

//credit: https://github.com/dhepper/font8x8
/** 
 * 8x8 monochrome bitmap fonts for rendering
 * Author: Daniel Hepper <daniel@hepper.net>
 * 
 * License: Public Domain
 * 
 * Based on:
 * // Summary: font8x8.h
 * // 8x8 monochrome bitmap fonts for rendering
 * //
 * // Author:
 * //     Marcel Sondaar
 * //     International Business Machines (public domain VGA fonts)
 * //
 * // License:
 * //     Public Domain
 * 
 * Fetched from: http://dimensionalrift.homelinux.net/combuster/mos3/?p=viewsource&file=/modules/gfx/font8_8.asm
 **/

// Constant: font8x8_basic
// Contains an 8x8 font map for unicode points U+0000 - U+007F (basic latin)
static char font8x8_basic[][8] =
{
// comment out unused chars to save space:
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0000 (nul)
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0001
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0002
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0003
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0004
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0005
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0006
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0007
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0008
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0009
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000A
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000B
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000C
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000D
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000E
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000F
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0010
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0011
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0012
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0013
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0014
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0015
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0016
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0017
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0018
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0019
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001A
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001B
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001C
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001D
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001E
//    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001F
#define kFontBasicOffset 0x20
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0020 (space)
    { 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},   // U+0021 (!)
    { 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0022 (")
    { 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00},   // U+0023 (#)
    { 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00},   // U+0024 ($)
    { 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00},   // U+0025 (%)
    { 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00},   // U+0026 (&)
    { 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0027 (')
    { 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00},   // U+0028 (()
    { 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00},   // U+0029 ())
    { 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},   // U+002A (*)
    { 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00},   // U+002B (+)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06},   // U+002C (,)
    { 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00},   // U+002D (-)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00},   // U+002E (.)
    { 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00},   // U+002F (/)
    { 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},   // U+0030 (0)
    { 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00},   // U+0031 (1)
    { 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00},   // U+0032 (2)
    { 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00},   // U+0033 (3)
    { 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00},   // U+0034 (4)
    { 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00},   // U+0035 (5)
    { 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00},   // U+0036 (6)
    { 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00},   // U+0037 (7)
    { 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},   // U+0038 (8)
    { 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00},   // U+0039 (9)
    { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00},   // U+003A (:)
    { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06},   // U+003B (//)
    { 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00},   // U+003C (<)
    { 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00},   // U+003D (=)
    { 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00},   // U+003E (>)
    { 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00},   // U+003F (?)
    { 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00},   // U+0040 (@)
    { 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},   // U+0041 (A)
    { 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00},   // U+0042 (B)
    { 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00},   // U+0043 (C)
    { 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00},   // U+0044 (D)
    { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00},   // U+0045 (E)
    { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00},   // U+0046 (F)
    { 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00},   // U+0047 (G)
    { 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00},   // U+0048 (H)
    { 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0049 (I)
    { 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00},   // U+004A (J)
    { 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00},   // U+004B (K)
    { 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00},   // U+004C (L)
    { 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00},   // U+004D (M)
    { 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00},   // U+004E (N)
    { 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},   // U+004F (O)
    { 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00},   // U+0050 (P)
    { 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00},   // U+0051 (Q)
    { 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00},   // U+0052 (R)
    { 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00},   // U+0053 (S)
    { 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0054 (T)
    { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00},   // U+0055 (U)
    { 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},   // U+0056 (V)
    { 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00},   // U+0057 (W)
    { 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00},   // U+0058 (X)
    { 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00},   // U+0059 (Y)
    { 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00},   // U+005A (Z)
    { 0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00},   // U+005B ([)
    { 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00},   // U+005C (\)
    { 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00},   // U+005D (])
    { 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00},   // U+005E (^)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},   // U+005F (_)
    { 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0060 (`)
    { 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00},   // U+0061 (a)
    { 0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00},   // U+0062 (b)
    { 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00},   // U+0063 (c)
    { 0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00},   // U+0064 (d)
    { 0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00},   // U+0065 (e)
    { 0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00},   // U+0066 (f)
    { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F},   // U+0067 (g)
    { 0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00},   // U+0068 (h)
    { 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0069 (i)
    { 0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E},   // U+006A (j)
    { 0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00},   // U+006B (k)
    { 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+006C (l)
    { 0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00},   // U+006D (m)
    { 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00},   // U+006E (n)
    { 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00},   // U+006F (o)
    { 0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F},   // U+0070 (p)
    { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78},   // U+0071 (q)
    { 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00},   // U+0072 (r)
    { 0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00},   // U+0073 (s)
    { 0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00},   // U+0074 (t)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00},   // U+0075 (u)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},   // U+0076 (v)
    { 0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00},   // U+0077 (w)
    { 0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00},   // U+0078 (x)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F},   // U+0079 (y)
    { 0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00},   // U+007A (z)
    { 0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00},   // U+007B ({)
    { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},   // U+007C (|)
    { 0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00},   // U+007D (})
    { 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+007E (~)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+007F
    
    { 0x24, 0x24, 0x24, 0x00, 0x81, 0x42, 0x3c, 0x00},   // smiley face (128)
    { 0x10, 0x38, 0x7C, 0x7C, 0xFE, 0xFE, 0x18, 0x3C}    // tree (129)
};

void clearLEDs()
{
  for (int i=0; i<100; i++) { leds.setPixelColor(i, 0); }
  leds.show();
}

// 0,0 is lower-left corner
int getPosFromXY(int x, int y)
{
  if (x < 0 || x > 9 || y < 0 || y > 9) {
    return 0;
  }
  
  if ((y % 2) == 0) {
    // even row, x is 0..9 from left to right
    return y*10 + x;
  }
  
  // odd row, x is 9..0 from left to right
  return y*10 + (9 - x);
}

void turnOnLEDsForPixelRow(int y, int pixelRow, int xOffset, int r, int g, int b)
{
  int x;
  for (x=0; x<8; x++) {
    if (pixelRow & (1<<x)) {
      int xPos = x + xOffset;
      if (xPos >= 0 && xPos <= 9) {
        int pos = getPosFromXY(xPos, y + 1);  // +1 on y to center vertically
        leds.setPixelColor(pos, r, g, b);
      }
    }
  }
}

// Draw a letter at a given x offset without clearing or showing
// Used for drawing multiple letters in the same frame
void drawLetterAtOffset(char letter[], int xOffset, int r, int g, int b)
{
  for (int row=0; row<8; row++) {
    int pixelRow = letter[row];
    turnOnLEDsForPixelRow(7-row, pixelRow, xOffset, r, g, b);
  }
}

void showLetterWithRGB(char letter[], int r, int g, int b)
{
  clearLEDs();
  drawLetterAtOffset(letter, 1, r, g, b);  // +1 to center on 10x10 grid
  leds.show();
}

void showLetter(char letter[], int gc)
{
  int r, g, b;
  
  switch(gc) {
    case kGridColorBlue:   r=0; g=0, b=255; break;
    case kGridColorRed:    r=255; g=0, b=0; break;
    case kGridColorGreen:  r=0; g=255, b=0; break;
  };
  
  showLetterWithRGB(letter, r, g, b);
}

////////////////////////////////////////////////////////////////////////////////
// Xmas tree

#ifdef OPTION_TREE
void showTree()
{
  char *treeCodes = font8x8_basic[kCodeTree - kFontBasicOffset];

  showLetter(treeCodes, kGridColorGreen);

  int lights = 0;
  while (lights < 128) {
    int x = rand()%8;
    int y = rand()%8;

    // make sure x/y are in the tree
    bool inTree = false;
    for (int row=0; row<8; row++) {
      int pixelRow = treeCodes[row];
      //y=7-row
      if ((pixelRow & (1<<x)) && (y == (7-row))) {
        
        inTree = true;
        break;
      }
    }
  
    if (inTree) {
      int pos = getPosFromXY(x + 1, y + 1);  // +1 on x,y to center it on the 10x10 grid
      if ((rand()%2) == 0) {
        leds.setPixelColor(pos, 0, 255, 0);  // green - light off
      } else {
        leds.setPixelColor(pos, rand()%255, rand()%255, rand()%255);  // random - light on
      }
      leds.show();
      delay(20);
      lights++;
    }
  }
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Fireworks

#ifdef OPTION_FIREWORKS
typedef struct {
  int x;
  int y;
} FireworkDelta;

#define kPoints  6
#define kRays    8

FireworkDelta deltas_nw[kPoints] = {{-1,1}, {-1,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}};
FireworkDelta deltas_ne[kPoints] = {{1,1}, {1,1}, {1,1}, {1,0}, {1,-1}, {0,-1}};
FireworkDelta deltas_se[kPoints] = {{1,-1}, {1,-1}, {1,-1}, {0,-1}, {0,-1}, {0,-1}};
FireworkDelta deltas_sw[kPoints] = {{-1,-1}, {-1,-1}, {-1,-1}, {0,-1}, {0,-1}, {0,-1}};

FireworkDelta deltas_n[kPoints] = {{0,0}, {0,1}, {0,1}, {0,0}, {0,-1}, {0,-1}};
FireworkDelta deltas_e[kPoints] = {{0,0}, {1,0}, {1,0}, {1,0}, {1,-1}, {0,-1}};
FireworkDelta deltas_s[kPoints] = {{0,0}, {0,-1}, {0,-1}, {0,-1}, {0,-1}, {0,-1}};
FireworkDelta deltas_w[kPoints] = {{0,0}, {-1,0}, {-1,0}, {-1,0}, {-1,-1}, {0,-1}};

FireworkDelta *allDeltas[kRays] = { deltas_nw, deltas_ne, deltas_se, deltas_sw, deltas_n, deltas_e, deltas_s, deltas_w };
long fwColours[kRays] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0x00FFFF, 0xFF00FF, 0x006400, 0xFFA500 };

void limit(int *x)
{
  if (*x < 0) {
    *x = 0;    
  } else if (*x > 9) {
    *x = 9;
  }
}

void showFireworks(int startX, int startY)
{
  clearLEDs();

  int x[kRays];
  int y[kRays];
  
  for (int ray=0; ray<kRays; ray++) {
    x[ray] = startX;
    y[ray] = startY;
  }
  
  leds.setPixelColor(getPosFromXY(x[0], y[0]), 255, 255, 255);
  delay(200);
  for (int i=0; i<kPoints; i++) {
    for (int ray=0; ray<kRays; ray++) {
      FireworkDelta *fw = allDeltas[ray];
      
      x[ray] += fw[i].x;
      y[ray] += fw[i].y;
      
      limit(&x[ray]);
      limit(&y[ray]);
      
      leds.setPixelColor(getPosFromXY(x[ray], y[ray]), 
        R_COLOUR(fwColours[ray]), G_COLOUR(fwColours[ray]), B_COLOUR(fwColours[ray]));
    }
    leds.show();
    delay(200);
  }  
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Birthday balloons

#ifdef OPTION_BALLOONS
#define kBalloonColour  0x0000FF
#define kStringColour   0x00FF00
#define kBalloonRows    7
#define kBalloonCols    5

//-XXX-
//XXXXX
//XXXXX
//-XXX-
//--X--
//--X--
//--X--

long kBalloon[][kBalloonCols] = {
  {              0, kBalloonColour, kBalloonColour, kBalloonColour,              0 },
  { kBalloonColour, kBalloonColour, kBalloonColour, kBalloonColour, kBalloonColour },
  { kBalloonColour, kBalloonColour, kBalloonColour, kBalloonColour, kBalloonColour },
  {              0, kBalloonColour, kBalloonColour, kBalloonColour,              0 },
  {              0,              0, kStringColour,               0,              0 },
  {              0,              0, kStringColour,               0,              0 },
  {              0,              0, kStringColour,               0,              0 }
};  

int limit2(int x)
{
  if (x < 0) {
    return -1;
  } 
 
  if (x > 9) {
    return -1;
  }
  
  return x;
}

void showBalloons()
{
  for (int start_x=0; start_x<7; start_x+=2) {
    for (int start_y=-6; start_y<11; start_y++) { 
      clearLEDs();
     
      for (int y=0; y<kBalloonRows; y++) {
        for (int x=0; x<kBalloonCols; x++) {
          
          long colour = kBalloon[kBalloonRows - 1 - y][x];
          
          int x2 = limit2(start_x + x);
          int y2 = limit2(start_y + y);
          
          if ((x2 != -1) && (y2 != -1)) {
            leds.setPixelColor(getPosFromXY(x2, y2),
              R_COLOUR(colour), G_COLOUR(colour), B_COLOUR(colour));        
          }
        }
      }
    
      leds.show();  
      delay(75);  
    }
  }
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Dog image (read from PPM P3 format)

#ifdef OPTION_DOGGY
// Note: stored in PROGMEM to save memory (https://www.arduino.cc/reference/en/language/variables/utilities/progmem/)

// PPM P3 ASCII format (https://en.wikipedia.org/wiki/Netpbm_format)
// ImageMagick cmd: "convert <file>.png -compress none <file>.ppm"
//skipping:
//P3
//10 10
//255
const char string_0[] PROGMEM = "222 222 222 222 222 222 134 108 82 123 97 66 188 168 141 199 183 161 167 146 121 157 136 110 222 222 222 222 222 222";
const char string_1[] PROGMEM = "222 222 222 157 129 97 174 147 113 139 110 76 182 157 128 204 187 158 207 199 179 151 129 108 123 102 82 222 222 222";
const char string_2[] PROGMEM = "107 81 51 146 120 91 116 87 56 96 66 29 131 103 75 168 134 96 174 151 121 172 158 137 81 61 37 19 6 0";
const char string_3[] PROGMEM = "86 58 22 0 0 0 2 0 0 37 10 0 85 55 26 82 46 12 161 161 161 163 141 113 72 53 31 0 0 0";
const char string_4[] PROGMEM = "43 15 0 65 40 11 162 153 136 161 142 125 189 172 148 87 67 46 0 0 0 65 37 7 101 75 42 0 0 0";
const char string_5[] PROGMEM = "76 51 21 207 193 166 0 0 0 0 0 0 0 0 0 202 183 157 112 82 51 87 45 5 86 51 17 2 0 0";
const char string_6[] PROGMEM = "128 108 76 209 194 172 209 194 172 0 0 0 88 75 65 222 209 184 209 188 158 142 103 61 88 48 10 19 0 0";
const char string_7[] PROGMEM = "153 136 102 179 166 136 162 153 136 161 142 125 153 136 121 216 201 177 204 187 152 157 121 80 92 51 10 0 0 0";
const char string_8[] PROGMEM = "97 87 70 137 110 70 0 0 0 0 0 0 0 0 0 191 171 132 188 166 128 161 131 88 88 55 11 0 0 0";
const char string_9[] PROGMEM = "222 222 222 91 71 46 144 116 80 132 105 72 142 113 71 144 108 61 153 125 81 139 108 67 81 51 16 222 222 222";

const char string_0a[] PROGMEM = "0 0 0 0 0 0 213 187 152 239 208 164 244 211 164 235 201 154 231 197 153 219 190 150 0 0 0 0 0 0 ";
const char string_1a[] PROGMEM = "0 0 0 207 181 143 218 185 140 222 187 142 219 182 135 211 174 129 210 172 129 199 161 120 199 166 131 0 0 0 ";
const char string_2a[] PROGMEM = "196 174 141 197 163 122 201 167 123 190 155 113 178 140 99 178 139 99 188 147 107 182 140 100 182 144 106 181 149 117 ";
const char string_3a[] PROGMEM = "204 178 141 154 118 85 118 93 66 52 39 27 120 87 60 141 105 73 50 37 25 114 79 53 173 130 92 170 139 107 ";
const char string_4a[] PROGMEM = "199 171 130 158 125 90 135 107 75 99 75 53 133 103 74 125 93 65 86 59 41 120 80 55 158 116 84 165 133 103 ";
const char string_5a[] PROGMEM = "180 151 111 155 127 91 183 148 104 176 139 95 119 94 65 131 98 65 162 119 83 148 105 73 138 105 78 151 123 97 ";
const char string_6a[] PROGMEM = "181 150 108 0 0 0 196 162 117 154 123 84 47 37 23 95 70 46 169 127 89 149 112 80 0 0 0 124 106 88 ";
const char string_7a[] PROGMEM = "0 0 0 0 0 0 179 146 104 133 100 67 30 21 13 30 21 13 97 68 48 124 88 65 0 0 0 0 0 0 ";
const char string_8a[] PROGMEM = "0 0 0 0 0 0 137 109 77 117 84 56 79 55 37 59 40 27 104 64 45 68 45 34 0 0 0 0 0 0 ";
const char string_9a[] PROGMEM = "0 0 0 0 0 0 0 0 0 106 72 38 113 82 58 120 86 61 103 71 51 0 0 0 0 0 0 0 0 0 ";

const char* const kDoggyPPM[] PROGMEM = { string_0, string_1, string_2,  string_3, string_4, string_5, string_6, string_7, string_8, string_9 };
const char* const kDoggy2PPM[] PROGMEM = { string_0a, string_1a, string_2a,  string_3a, string_4a, string_5a, string_6a, string_7a, string_8a, string_9a };

void showDoggy()
{
  char ppmText[3*4*10+1];  // 4 chars/color x 3 colors x 10 pixels
  int rr[10], gg[10], bb[10];
  
  clearLEDs();

  for (int y=0; y<10; y++) {    
    strcpy_P(ppmText, (char*)pgm_read_word(&(kDoggyPPM[y])));
    int rc = sscanf(ppmText, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
      &rr[0], &gg[0], &bb[0],
      &rr[1], &gg[1], &bb[1],
      &rr[2], &gg[2], &bb[2],
      &rr[3], &gg[3], &bb[3],
      &rr[4], &gg[4], &bb[4],
      &rr[5], &gg[5], &bb[5],
      &rr[6], &gg[6], &bb[6],
      &rr[7], &gg[7], &bb[7],
      &rr[8], &gg[8], &bb[8],
      &rr[9], &gg[9], &bb[9]);

    for (int x=0; x<10; x++) {
      leds.setPixelColor(getPosFromXY(x, 9-y), rr[x], gg[x], bb[x]);
    }
  }

  leds.show();  
}

void showDoggy2()
{
  char ppmText[3*4*10+1];  // 4 chars/color x 3 colors x 10 pixels
  int rr[10], gg[10], bb[10];
  
  clearLEDs();

  for (int y=0; y<10; y++) {    
    strcpy_P(ppmText, (char*)pgm_read_word(&(kDoggy2PPM[y])));
    int rc = sscanf(ppmText, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
      &rr[0], &gg[0], &bb[0],
      &rr[1], &gg[1], &bb[1],
      &rr[2], &gg[2], &bb[2],
      &rr[3], &gg[3], &bb[3],
      &rr[4], &gg[4], &bb[4],
      &rr[5], &gg[5], &bb[5],
      &rr[6], &gg[6], &bb[6],
      &rr[7], &gg[7], &bb[7],
      &rr[8], &gg[8], &bb[8],
      &rr[9], &gg[9], &bb[9]);

    for (int x=0; x<10; x++) {
      leds.setPixelColor(getPosFromXY(x, 9-y), rr[x], gg[x], bb[x]);
    }
  }

  leds.show();  
}
#endif

////////////////////////////////////////////////////////////////////////////////

void setup()
{
  leds.begin();
}

void loop()
{
// demo: cycle through all letters  
//  char c;
//  for (c='A'; c<='Z'; c++) {
//    showLetter(font8x8_basic[c - kFontBasicOffset]);
//    delay(200);
//  }
//  delay(2000);

  char *msg = "HAPPY NEW YEAR 2026!!";
  int len = strlen(msg);
  int letterSpacing = 9;  // pixels between letter starts (8 for letter + 1 gap)

  // Total scroll distance: start with first letter off-screen right,
  // end with last letter off-screen left
  int totalScroll = 10 + (len * letterSpacing) + 8;

  for (int scroll=0; scroll<totalScroll; scroll++) {
    clearLEDs();

    // Draw each letter at its current position
    for (int i=0; i<len; i++) {
      int xOffset = 10 - scroll + (i * letterSpacing);

      // Only draw if letter is potentially visible (-7 to 10)
      if (xOffset >= -7 && xOffset <= 10) {
        srand(i + 1);  // Seed based on letter index for stable colors
        drawLetterAtOffset(font8x8_basic[msg[i] - kFontBasicOffset],
                          xOffset, rand()%256, rand()%256, rand()%256);
      }
    }

    leds.show();
    delay(60);
  }

  // happy face
//  showLetter(font8x8_basic[kCodeSmiley - kFontBasicOffset], kGridColorRed);
//  delay(500);

#ifdef OPTION_TREE
  // tree
  showTree();
  delay(1000);
#endif

#ifdef OPTION_FIREWORKS
  // fireworks
  showFireworks(3, 4);
  showFireworks(7, 7);
  showFireworks(5, 3);
  delay(1000);
#endif

#ifdef OPTION_BALLOONS
  // birthday balloons
  showBalloons();
#endif  

#ifdef OPTION_DOGGY
  showDoggy();
  delay(2000);  
  showDoggy2();
  delay(2000);  
#endif
}
