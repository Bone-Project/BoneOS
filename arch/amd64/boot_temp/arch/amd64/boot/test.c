void write_string()
{
  volatile char* video_mem = (volatile char*) 0xB8000;
  *video_mem++ = 'C';
  *video_mem++ = 10;
  while (1);
}
