/* Copyright (c) 2010-2011 mbed.org, MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "LCD_DISCO_F429ZI.h"

#define LCD_FRAME_BUFFER_LAYER0                  (LCD_FRAME_BUFFER+0x130000)
#define LCD_FRAME_BUFFER_LAYER1                  LCD_FRAME_BUFFER
#define CONVERTED_FRAME_BUFFER                   (LCD_FRAME_BUFFER+0x260000)

// Constructor
LCD_DISCO_F429ZI::LCD_DISCO_F429ZI()
{
  BSP_LCD_Init();  
  BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER_LAYER1);
  BSP_LCD_SelectLayer(1);
  BSP_LCD_Clear(LCD_COLOR_WHITE);  
  BSP_LCD_SetColorKeying(1, LCD_COLOR_WHITE);
  BSP_LCD_SetLayerVisible(1, DISABLE);
  BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER_LAYER0);
  BSP_LCD_SelectLayer(0);
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_DisplayOn();
  BSP_LCD_Clear(LCD_COLOR_WHITE);  
}

// Destructor
LCD_DISCO_F429ZI::~LCD_DISCO_F429ZI()
{

}

//=================================================================================================================
// Public methods
//=================================================================================================================

uint8_t LCD_DISCO_F429ZI::Init(void)
{
  return BSP_LCD_Init();
}

uint32_t LCD_DISCO_F429ZI::GetXSize(void)
{
  return BSP_LCD_GetXSize();
}

uint32_t LCD_DISCO_F429ZI::GetYSize(void)
{
  return BSP_LCD_GetYSize();
}

void LCD_DISCO_F429ZI::LayerDefaultInit(uint16_t LayerIndex, uint32_t FB_Address)
{
  BSP_LCD_LayerDefaultInit(LayerIndex, FB_Address);
}

void LCD_DISCO_F429ZI::SelectLayer(uint32_t LayerIndex)
{
  BSP_LCD_SelectLayer(LayerIndex);
}

void LCD_DISCO_F429ZI::SetLayerVisible(uint32_t LayerIndex, FunctionalState state)
{
  BSP_LCD_SetLayerVisible(LayerIndex, state);
}

void LCD_DISCO_F429ZI::SetTransparency(uint32_t LayerIndex, uint8_t Transparency)
{
  BSP_LCD_SetTransparency(LayerIndex, Transparency);
}

void LCD_DISCO_F429ZI::SetLayerAddress(uint32_t LayerIndex, uint32_t Address)
{
  BSP_LCD_SetLayerAddress(LayerIndex, Address);
}

void LCD_DISCO_F429ZI::SetLayerWindow(uint16_t LayerIndex, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  BSP_LCD_SetLayerWindow(LayerIndex, Xpos, Ypos, Width, Height);
}

void LCD_DISCO_F429ZI::SetColorKeying(uint32_t LayerIndex, uint32_t RGBValue)
{
  BSP_LCD_SetColorKeying(LayerIndex, RGBValue);
}

void LCD_DISCO_F429ZI::ResetColorKeying(uint32_t LayerIndex)
{
  BSP_LCD_ResetColorKeying(LayerIndex);
}

uint32_t LCD_DISCO_F429ZI::GetTextColor(void)
{
  return BSP_LCD_GetTextColor();
}

uint32_t LCD_DISCO_F429ZI::GetBackColor(void)
{
  return BSP_LCD_GetBackColor();
}

void LCD_DISCO_F429ZI::SetTextColor(uint32_t Color)
{
  BSP_LCD_SetTextColor(Color);
}

void LCD_DISCO_F429ZI::SetBackColor(uint32_t Color)
{
  BSP_LCD_SetBackColor(Color);
}

void LCD_DISCO_F429ZI::SetFont(sFONT *pFonts)
{
  BSP_LCD_SetFont(pFonts);
}

sFONT *LCD_DISCO_F429ZI::GetFont(void)
{
  return BSP_LCD_GetFont();
}

uint32_t LCD_DISCO_F429ZI::ReadPixel(uint16_t Xpos, uint16_t Ypos)
{
  return BSP_LCD_ReadPixel(Xpos, Ypos);
}

void LCD_DISCO_F429ZI::Clear(uint32_t Color)
{
  BSP_LCD_Clear(Color);
}

void LCD_DISCO_F429ZI::ClearStringLine(uint32_t Line)
{
  BSP_LCD_ClearStringLine(Line);
}

void LCD_DISCO_F429ZI::DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii)
{
  BSP_LCD_DisplayChar(Xpos, Ypos, Ascii);
}

void LCD_DISCO_F429ZI::DisplayStringAt(uint16_t X, uint16_t Y, uint8_t *pText, Text_AlignModeTypdef mode)
{
  BSP_LCD_DisplayStringAt(X, Y, pText, mode);
}

void LCD_DISCO_F429ZI::DisplayStringAtLine(uint16_t Line, uint8_t *ptr)
{
  BSP_LCD_DisplayStringAtLine(Line, ptr);
}

void LCD_DISCO_F429ZI::DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  BSP_LCD_DrawHLine(Xpos, Ypos, Length);
}

void LCD_DISCO_F429ZI::DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  BSP_LCD_DrawVLine(Xpos, Ypos, Length);
}

void LCD_DISCO_F429ZI::DrawLine(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
  BSP_LCD_DrawLine(X1, Y1, X2, Y2);
}

void LCD_DISCO_F429ZI::DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  BSP_LCD_DrawRect(Xpos, Ypos, Width, Height);
}

void LCD_DISCO_F429ZI::DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  BSP_LCD_DrawCircle(Xpos, Ypos, Radius);
}

void LCD_DISCO_F429ZI::DrawPolygon(pPoint Points, uint16_t PointCount)
{
  BSP_LCD_DrawPolygon(Points, PointCount);
}

void LCD_DISCO_F429ZI::DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  BSP_LCD_DrawEllipse(Xpos, Ypos, XRadius, YRadius);
}

void LCD_DISCO_F429ZI::DrawBitmap(uint32_t X, uint32_t Y, uint8_t *pBmp)
{
  BSP_LCD_DrawBitmap(X, Y, pBmp);
}

void LCD_DISCO_F429ZI::FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  BSP_LCD_FillRect(Xpos, Ypos, Width, Height);
}

void LCD_DISCO_F429ZI::FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  BSP_LCD_FillCircle(Xpos, Ypos, Radius);
}

void LCD_DISCO_F429ZI::FillTriangle(uint16_t X1, uint16_t X2, uint16_t X3, uint16_t Y1, uint16_t Y2, uint16_t Y3)
{
  BSP_LCD_FillTriangle(X1, X2, X3, Y1, Y2, Y3);
}

void LCD_DISCO_F429ZI::FillPolygon(pPoint Points, uint16_t PointCount)
{
  BSP_LCD_FillPolygon(Points, PointCount);
}

void LCD_DISCO_F429ZI::FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  BSP_LCD_FillEllipse(Xpos, Ypos, XRadius, YRadius);
}

void LCD_DISCO_F429ZI::DisplayOn(void)
{
  BSP_LCD_DisplayOn();
}

void LCD_DISCO_F429ZI::DisplayOff(void)
{
  BSP_LCD_DisplayOff();
}

void LCD_DISCO_F429ZI::DrawPixel(uint32_t Xpos, uint32_t Ypos, uint32_t RGB_Code)
{
  BSP_LCD_DrawPixel(Xpos, Ypos, RGB_Code);
}

void LCD_DISCO_F429ZI::FillRect(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t RGB_Code)
{
    uint16_t Width,Height,x,y;
    
    BSP_LCD_SetTextColor(RGB_Code);
    
    if(x0 > x1)
    {
        x = x1;
        Width = x0-x1;
    }
    else
    {
        x = x0;
        Width = x1-x0;
    }
    if(y0 > y1)
    {
        y = y1;
        Height = y0-y1;
    }
    else
    {
        y = y0;
        Height = y1 - y0;
    }
    
    BSP_LCD_FillRect(x, y, Width+1, Height+1);
}
//=================================================================================================================
// Private methods
//=================================================================================================================
