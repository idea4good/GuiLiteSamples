#include "GuiLite.h"
#include "ft2build.h"
#include FT_FREETYPE_H

class c_freetype_font_op : public c_font_operator
{
public:
    c_freetype_font_op()
    {
        FT_Init_FreeType(&library);
    }

    FT_Face set_font(const char* filepathname, int width_px, int height_px)
    {
        FT_Face face;
        ASSERT(0 == FT_New_Face(library, filepathname, 0, &face));
        ASSERT(0 == FT_Set_Pixel_Sizes(face, width_px, height_px));
        return face;
    }

    virtual void draw_string(c_surface* surface, int z_order, const void* string, int x, int y, const void* font, unsigned int font_color, unsigned int bg_color)//type of string should be: wchar_t
    {
        const wchar_t* s = (const wchar_t*)string;
        FT_Face face = (FT_Face)font;
        int font_height = (face->size->metrics.height / 64);
        if (0 == s)
        {
            return;
        }
        int x_ = x;
        y += font_height;
        while (*s)
        {
            if (*s == L'\n')
            {
                y += font_height;
                x_ = x;
                s++;
                continue;
            }
            x_ += draw_single_char(surface, z_order, *s++, x_, y, face, font_color, bg_color);
        }
    }

    virtual void draw_string_in_rect(c_surface* surface, int z_order, const void* string, c_rect rect, const void* font, unsigned int font_color, unsigned int bg_color, unsigned int align_type = ALIGN_LEFT)
    {
        const wchar_t* s = (const wchar_t*)string;
        if (0 == s)
        {
            return;
        }
        int x, y;
        get_string_pos(s, (const LATTICE_FONT_INFO*)font, rect, align_type, x, y);
        draw_string(surface, z_order, string, rect.m_left + x, rect.m_top + y, font, font_color, bg_color);
    }

    virtual int get_str_size(const void* string, const void* font, int& width, int& height)
    {
        const wchar_t* s = (const wchar_t*)string;
        FT_Face face = (FT_Face)font;
        if (0 == s)
        {
            return -1;
        }
        
        width = 0;
        height = (face->size->metrics.height / 64);
        while (*s)
        {
            width += draw_single_char(0, 0, *s++, 0, 0, face, 0, 0);
        }
        return 0;
    }

    virtual void draw_value(c_surface* surface, int z_order, int value, int dot_position, int x, int y, const void* font, unsigned int font_color, unsigned int bg_color) {/*TBD*/ }
    virtual void draw_value_in_rect(c_surface* surface, int z_order, int value, int dot_position, c_rect rect, const void* font, unsigned int font_color, unsigned int bg_color, unsigned int align_type = ALIGN_LEFT) {/*TBD*/ }

private:
    int draw_single_char(c_surface* surface, int z_order, wchar_t code, int x, int y, FT_Face face, unsigned int font_color, unsigned int bg_color)
    {
        ASSERT(0 == FT_Load_Char(face, code, FT_LOAD_RENDER));
        if (code == L' ')
        {
            return (face->glyph->advance.x / 64);
        }
        if (!surface)
        {
            return face->glyph->bitmap.width;
        }
        return draw_lattice(surface, z_order, &(face->glyph->bitmap), x, (y - face->glyph->bitmap_top), font_color, bg_color);
    }

    int draw_lattice(c_surface* surface, int z_order, FT_Bitmap* bitmap, int x, int y, unsigned int font_color, unsigned int bg_color)
    {
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
