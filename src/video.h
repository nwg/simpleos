#ifndef __VIDEO_H__
#define __VIDEO_H__

#define VIDEO_START_PHYS 0xb8000
#define USER_VIDEO 0x3fe000
#define VIDEO_SIZE (80*25*2)

#define COLOR_BLUE (0x01 << 8)
#define COLOR_GREEN (0x02 << 8)
#define COLOR_RED (0x04 << 8)

void printc(int row, int col, int color, char c);
void print(int row, int col, int color, const char *s);
void video_clear();

#endif
