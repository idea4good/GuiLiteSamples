#include "GuiLite.h"
#include "ft2build.h"
#include FT_FREETYPE_H

class c_freetype
{
public:
    c_freetype()
    {
        FT_Init_FreeType(&library);
    }

    FT_Face set_font(const char *filepathname, int width_px, int height_px)
    {
        FT_Face face;
        ASSERT(0 == FT_New_Face(library, filepathname, 0, &face));
        ASSERT(0 == FT_Set_Pixel_Sizes(face, width_px, height_px));
        return face;
    }

    int draw_single_char(c_surface *surface, int z_order, wchar_t code, int x, int y, FT_Face face,unsigned int font_color, unsigned int bg_color)
    {
        ASSERT(0 == FT_Load_Char(face, code, FT_LOAD_RENDER));
        if(code == L' ')
        {
            return (face->glyph->advance.x / 64);
        }
        return draw_lattice(surface, z_order, &(face->glyph->bitmap), x, (y - face->glyph->bitmap_top), font_color, bg_color);
    }

    void draw_string(c_surface* surface, int z_order, const wchar_t *s, int x, int y, FT_Face face, unsigned int font_color, unsigned int bg_color)
    {
        if (0 == s)
		{
			return;
		}
        int x_ = x;
        int y_ = y;
		while (*s)
		{
            if(*s == L'\n')
            {
                y += (face->size->metrics.height / 64);
                x_ = x;
                s++;
                continue;
            }
			x_ += draw_single_char(surface, z_order, *s++, x_, y, face, font_color, bg_color);
		}
    }
private:
    int draw_lattice(c_surface *surface, int z_order, FT_Bitmap *bitmap, int x, int y, unsigned int font_color, unsigned int bg_color)
    {
        ASSERT(bitmap);
        ASSERT(surface);
        ASSERT(bitmap->pixel_mode == FT_PIXEL_MODE_GRAY);

        FT_Int width = bitmap->width;
        FT_Int height = bitmap->rows;

        //printf("%lc: left:%d, top: %d\n", code, face->glyph->bitmap_left, face->glyph->bitmap_top);
        //printf("width:%d, height: %d, mode = %d\n", bitmap->width, bitmap->rows, bitmap->pixel_mode);
        int i = 0;
        for (int y_ = 0; y_ < height; y_++)
        {
            for (int x_ = 0; x_ < width; x_++)
            {
                unsigned char grey_value = bitmap->buffer[i++];
                //printf("%03d,", grey_value);
                if (0x00 == grey_value)
				{
					if (GL_ARGB_A(bg_color))
					{
						surface->draw_pixel(x + x_, y + y_, bg_color, z_order);
					}
                    continue;
				}
                unsigned int b = (GL_RGB_B(font_color) * grey_value + GL_RGB_B(bg_color) * (255 - grey_value)) >> 8;
                unsigned int g = (GL_RGB_G(font_color) * grey_value + GL_RGB_G(bg_color) * (255 - grey_value)) >> 8;
                unsigned int r = (GL_RGB_R(font_color) * grey_value + GL_RGB_R(bg_color) * (255 - grey_value)) >> 8;
                surface->draw_pixel(x + x_, y + y_, GL_RGB(r, g, b), z_order);
            }
            //printf("\n");
        }
        return width;
    }

    FT_Library library;
};
