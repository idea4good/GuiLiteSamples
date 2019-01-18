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

#ifndef __LCD_DISCO_F429ZI_H
#define __LCD_DISCO_F429ZI_H

#ifdef TARGET_DISCO_F429ZI

#include "mbed.h"
#include "stm32f429i_discovery_lcd.h"

/*
  This class drives the LCD display (ILI9341 240x320) present on DISCO_F429ZI board.

  Usage:

  #include "mbed.h"
  #include "LCD_DISCO_F429ZI.h"

  LCD_DISCO_F429ZI lcd;

  int main()
  {
      lcd.Clear(LCD_COLOR_BLUE);
      lcd.SetBackColor(LCD_COLOR_BLUE);
      lcd.SetTextColor(LCD_COLOR_WHITE);
      lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"HELLO", CENTER_MODE);
      while(1)
      {
      }
  }
*/
class LCD_DISCO_F429ZI
{
  
public:
  //! Constructor
  LCD_DISCO_F429ZI();

  //! Destructor
  ~LCD_DISCO_F429ZI();

  /**
    * @brief  Initializes the LCD.
    * @param  None
    * @retval LCD state
    */
  uint8_t Init(void);

  /**
    * @brief  Gets the LCD X size.
    * @param  None    
    * @retval The used LCD X size
    */
  uint32_t GetXSize(void);

  /**
    * @brief  Gets the LCD Y size.
    * @param  None    
    * @retval The used LCD Y size
    */
  uint32_t GetYSize(void);

  /**
    * @brief  Initializes the LCD layers.
    * @param  LayerIndex: the layer foreground or background. 
    * @param  FB_Address: the layer frame buffer.
    * @retval None
    */
  void LayerDefaultInit(uint16_t LayerIndex, uint32_t FB_Address);

  /**
    * @brief  Selects the LCD Layer.
    * @param  LayerIndex: the Layer foreground or background.
    * @retval None
    */
  void SelectLayer(uint32_t LayerIndex);

  /**
    * @brief  Sets a LCD Layer visible.
    * @param  LayerIndex: the visible Layer.
    * @param  state: new state of the specified layer.
    *    This parameter can be: ENABLE or DISABLE.  
    * @retval None
    */
  void SetLayerVisible(uint32_t LayerIndex, FunctionalState state);

  /**
    * @brief  Configures the Transparency.
    * @param  LayerIndex: the Layer foreground or background.
    * @param  Transparency: the Transparency, 
    *    This parameter must range from 0x00 to 0xFF.
    * @retval None
    */
  void SetTransparency(uint32_t LayerIndex, uint8_t Transparency);

  /**
    * @brief  Sets a LCD layer frame buffer address.
    * @param  LayerIndex: specifies the Layer foreground or background
    * @param  Address: new LCD frame buffer value      
    * @retval None
    */
  void SetLayerAddress(uint32_t LayerIndex, uint32_t Address);

  /**
    * @brief  Sets the Display window.
    * @param  LayerIndex: layer index
    * @param  Xpos: LCD X position
    * @param  Ypos: LCD Y position
    * @param  Width: LCD window width
    * @param  Height: LCD window height  
    * @retval None
    */
  void SetLayerWindow(uint16_t LayerIndex, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);

  /**
    * @brief  Configures and sets the color Keying.
    * @param  LayerIndex: the Layer foreground or background
    * @param  RGBValue: the Color reference
    * @retval None
    */
  void SetColorKeying(uint32_t LayerIndex, uint32_t RGBValue);

  /**
    * @brief  Disables the color Keying.
    * @param  LayerIndex: the Layer foreground or background
    * @retval None
    */
  void ResetColorKeying(uint32_t LayerIndex);

  /**
    * @brief  Gets the LCD Text color.
    * @param  None 
    * @retval Text color
    */
  uint32_t GetTextColor(void);

  /**
    * @brief  Gets the LCD Background color.
    * @param  None  
    * @retval Background color  
    */
  uint32_t GetBackColor(void);

  /**
    * @brief  Sets the Text color.
    * @param  Color: the Text color code ARGB(8-8-8-8);
    * @retval None
    */
  void SetTextColor(uint32_t Color);

  /**
    * @brief  Sets the Background color.
    * @param  Color: the layer Background color code ARGB(8-8-8-8);
    * @retval None
    */
  void SetBackColor(uint32_t Color);

  /**
    * @brief  Sets the Text Font.
    * @param  pFonts: the layer font to be used
    * @retval None
    */
  void SetFont(sFONT *pFonts);

  /**
    * @brief  Gets the Text Font.
    * @param  None
    * @retval Layer font
    */
  sFONT *GetFont(void);

  /**
    * @brief  Reads Pixel.
    * @param  Xpos: the X position
    * @param  Ypos: the Y position 
    * @retval RGB pixel color
    */
  uint32_t ReadPixel(uint16_t Xpos, uint16_t Ypos);

  /**
    * @brief  Clears the hole LCD.
    * @param  Color: the color of the background
    * @retval None
    */
  void Clear(uint32_t Color);

  /**
    * @brief  Clears the selected line.
    * @param  Line: the line to be cleared
    * @retval None
    */
  void ClearStringLine(uint32_t Line);

  /**
    * @brief  Displays one character.
    * @param  Xpos: start column address
    * @param  Ypos: the Line where to display the character shape
    * @param  Ascii: character ascii code, must be between 0x20 and 0x7E
    * @retval None
    */
  void DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);

  /**
    * @brief  Displays a maximum of 60 char on the LCD.
    * @param  X: pointer to x position (in pixel);
    * @param  Y: pointer to y position (in pixel);    
    * @param  pText: pointer to string to display on LCD
    * @param  mode: The display mode
    *    This parameter can be one of the following values:
    *                @arg CENTER_MODE 
    *                @arg RIGHT_MODE
    *                @arg LEFT_MODE   
    * @retval None
    */
  void DisplayStringAt(uint16_t X, uint16_t Y, uint8_t *pText, Text_AlignModeTypdef mode);

  /**
    * @brief  Displays a maximum of 20 char on the LCD.
    * @param  Line: the Line where to display the character shape
    * @param  ptr: pointer to string to display on LCD
    * @retval None
    */
  void DisplayStringAtLine(uint16_t Line, uint8_t *ptr);

  /**
    * @brief  Displays an horizontal line.
    * @param  Xpos: the X position
    * @param  Ypos: the Y position
    * @param  Length: line length
    * @retval None
    */
  void DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);

  /**
    * @brief  Displays a vertical line.
    * @param  Xpos: the X position
    * @param  Ypos: the Y position
    * @param  Length: line length
    * @retval None
    */
  void DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);

  /**
    * @brief  Displays an uni-line (between two points);.
    * @param  X1: the point 1 X position
    * @param  Y1: the point 1 Y position
    * @param  X2: the point 2 X position
    * @param  Y2: the point 2 Y position
    * @retval None
    */
  void DrawLine(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);

  /**
    * @brief  Displays a rectangle.
    * @param  Xpos: the X position
    * @param  Ypos: the Y position
    * @param  Height: display rectangle height
    * @param  Width: display rectangle width
    * @retval None
    */
  void DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);

  /**
    * @brief  Displays a circle.
    * @param  Xpos: the X position
    * @param  Ypos: the Y position
    * @param  Radius: the circle radius
    * @retval None
    */
  void DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);

  /**
    * @brief  Displays an poly-line (between many points);.
    * @param  Points: pointer to the points array
    * @param  PointCount: Number of points
    * @retval None
    */
  void DrawPolygon(pPoint Points, uint16_t PointCount);

  /**
    * @brief  Displays an Ellipse.
    * @param  Xpos: the X position
    * @param  Ypos: the Y position
    * @param  XRadius: the X radius of ellipse
    * @param  YRadius: the Y radius of ellipse
    * @retval None
    */
  void DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius);

  /**
    * @brief  Displays a bitmap picture loaded in the internal Flash (32 bpp);.
    * @param  X: the bmp x position in the LCD
    * @param  Y: the bmp Y position in the LCD
    * @param  pBmp: Bmp picture address in the internal Flash
    * @retval None
    */
  void DrawBitmap(uint32_t X, uint32_t Y, uint8_t *pBmp);

  /**
    * @brief  Displays a full rectangle.
    * @param  Xpos: the X position
    * @param  Ypos: the Y position
    * @param  Height: rectangle height
    * @param  Width: rectangle width
    * @retval None
    */
  void FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);

  /**
    * @brief  Displays a full circle.
    * @param  Xpos: the X position
    * @param  Ypos: the Y position
    * @param  Radius: the circle radius
    * @retval None
    */
  void FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);

  /**
    * @brief  Fill triangle.
    * @param  X1: the point 1 x position
    * @param  Y1: the point 1 y position
    * @param  X2: the point 2 x position
    * @param  Y2: the point 2 y position
    * @param  X3: the point 3 x position
    * @param  Y3: the point 3 y position
    * @retval None
    */
  void FillTriangle(uint16_t X1, uint16_t X2, uint16_t X3, uint16_t Y1, uint16_t Y2, uint16_t Y3);

  /**
    * @brief  Displays a full poly-line (between many points);.
    * @param  Points: pointer to the points array
    * @param  PointCount: Number of points
    * @retval None
    */
  void FillPolygon(pPoint Points, uint16_t PointCount);

  /**
    * @brief  Draw a full ellipse.
    * @param  Xpos: the X position
    * @param  Ypos: the Y position
    * @param  XRadius: X radius of ellipse
    * @param  YRadius: Y radius of ellipse. 
    * @retval None
    */
  void FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius);

  /**
    * @brief  Enables the Display.
    * @param  None
    * @retval None
    */
  void DisplayOn(void);

  /**
    * @brief  Disables the Display.
    * @param  None
    * @retval None
    */
  void DisplayOff(void);

  /**
    * @brief  Writes Pixel.
    * @param  Xpos: the X position
    * @param  Ypos: the Y position
    * @param  RGB_Code: the pixel color in ARGB mode (8-8-8-8);  
    * @retval None
    */
  void DrawPixel(uint32_t Xpos, uint32_t Ypos, uint32_t RGB_Code);

  void FillRect(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t RGB_Code);
private:

};

#else
#error "This class must be used with DISCO_F429ZI board only."
#endif // TARGET_DISCO_F429ZI

#endif
