#include "mbed.h"
#include "LCD_DISCO_F429ZI.h"

LCD_DISCO_F429ZI lcd;

DigitalOut led1(LED1);

struct EXTERNAL_GFX_OP
{
	void (*draw_pixel)(int x, int y, unsigned int rgb);
	void (*fill_rect)(int x0, int y0, int x1, int y1, unsigned int rgb);
} my_gfx_op;

void gfx_draw_pixel(int x, int y, unsigned int rgb)
{
	lcd.DrawPixel(x,y,rgb);
}

//Implement it, if you have more fast solution than drawing pixels one by one.
void gfx_fill_rect(int x0, int y0, int x1, int y1, unsigned int rgb)
{
    lcd.FillRect(x0, y0, x1, y1, rgb);
}

extern void startHelloMCU(int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op);

int main()
{      
    led1 = 1;
  
    BSP_LCD_SetFont(&Font20);
    lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"MBED EXAMPLE", CENTER_MODE);
    wait(1);
  
    //Link external graphic driver & start UI:
   
    my_gfx_op.draw_pixel = &gfx_draw_pixel;
    my_gfx_op.fill_rect = &gfx_fill_rect;//gfx_fill_rect;
    startHelloMCU(240, 320, 32, &my_gfx_op);
    while(1);
        
    while(1)
    {      
      lcd.Clear(LCD_COLOR_BLUE);
      lcd.SetBackColor(LCD_COLOR_BLUE);
      lcd.SetTextColor(LCD_COLOR_WHITE);
      wait(0.3);
      lcd.DisplayStringAt(0, LINE(4), (uint8_t *)"DISCOVERY", CENTER_MODE);
      lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"STM32F429ZI", CENTER_MODE);
      wait(1);

      lcd.Clear(LCD_COLOR_GREEN);
      
      lcd.SetTextColor(LCD_COLOR_BLUE);
      lcd.FillRect(10, 20, 50, 50);
      wait(0.1);
      lcd.SetTextColor(LCD_COLOR_BROWN);
      lcd.FillCircle(80, 80, 50);
      wait(0.1);
      lcd.SetTextColor(LCD_COLOR_YELLOW);
      lcd.FillEllipse(150, 150, 50, 100);
      wait(0.1);
      lcd.SetTextColor(LCD_COLOR_RED);
      lcd.FillCircle(200, 200, 40);
      wait(1);

      lcd.SetBackColor(LCD_COLOR_ORANGE);
      lcd.SetTextColor(LCD_COLOR_CYAN);
      BSP_LCD_SetFont(&Font24);
      lcd.DisplayStringAt(0, LINE(7), (uint8_t *)"HAVE FUN !!!", CENTER_MODE);
      wait(1);

      led1 = !led1;
      wait(0.5);
    }
}

