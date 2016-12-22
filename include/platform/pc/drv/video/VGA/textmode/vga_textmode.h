#ifndef _DRV_VIDEO_VGA_TEXTMODE_VGATEXTMODE_H_
#define _DRV_VIDEO_VGA_TEXTMODE_VGATEXTMODE_H_


typedef  struct
{
  int w;
  int h;
  void(*clear)(void);
  void(*putch)(char c);
  int(*update_cursor)(int row,int col,uint8_t crsr_start, uint8_t crsr_end);
  void(*scroll)(int offset);
  int(*init)(void);
  char* name;
}vga_textmode_t;


extern int init_vga_textmode();
extern vga_textmode_t __textmode;
extern vga_textmode_t *vga_textmodes_arr[];

#endif /*_DRV_VIDEO_VGA_TEXTMODE_VGATEXTMODE_H_*/



