/*
Pixel_Buffer subroutine
*/
void buffer_swap_isr()
{
  volatile short *frontbuffer = (0xFF203020);
  *frontbuffer = *(0xFF203024);
  
}
