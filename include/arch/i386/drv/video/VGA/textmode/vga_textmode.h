#ifndef  _DRV_VIDEO_VGA_TEXTMODE_VGATEXTMODE_H_
#define _DRV_VIDEO_VGA_TEXTMODE_VGATEXTMODE_H_

#define eighty_twentyfive_TEXTMODE_INDEX 0

typedef 
struct
{
  int w;
  int h;
  void(*cls)(void);
  void(*putch)(char c);
  char* name;
}vga_textmode_t;

#define ACTIVE_RES_W 80
#define ACTIVE_RES_H 25

extern int init_vga_textmode();
extern vga_textmode_t *vga_textmodes_arr[];

#endif /*_DRV_VIDEO_VGA_TEXTMODE_VGATEXTMODE_H_*/