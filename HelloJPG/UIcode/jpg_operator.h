#include <stdlib.h>
#include <stdio.h>
#include "GuiLite.h"
#include "turbojpeg.h"
#include <cstdio>

class c_jpg_operator : public c_image_operator
{
public:
    virtual void draw_image(c_surface* surface, int z_order, const void* imagePath, int x, int y, unsigned int mask_rgb = DEFAULT_MASK_COLOR)
    {
        int width, height;
        unsigned int* rgb = (unsigned int*)getRgbData((const char*)imagePath, width, height);
        if (!rgb)
        {
            return;
        }

        for (int y_ = y; y_ < y + height; y_++)
		{
			for (int x_ = x; x_ < x + width; x_++)
			{
				surface->draw_pixel(x_, y_, (*rgb++), z_order);
			}
		}
    }

    virtual void draw_image(c_surface* surface, int z_order, const void* image_info, int x, int y, int src_x, int src_y, int width, int height, unsigned int mask_rgb = DEFAULT_MASK_COLOR){ /*TBD*/ }
    
private:
    void *readJpegFile(const char *path, int &fsize)
    {
        struct stat st;
        if (stat(path, &st) < 0)
        {
            perror("stat failed");
            return 0;
        }

        fsize = st.st_size;
        void *content = (void *)malloc(fsize);
        FILE* fp = std::fopen(path, "rb");
        std::fread(content, 1, fsize, fp);
        std::fclose(fp);
        return content;
    }

    unsigned char* getRgbData(const char* path, int& width, int& height)
    {
        tjhandle jpegHnd = tjInitDecompress();
        int fsize, subSamp;

        unsigned char *fileBuf = (unsigned char *)readJpegFile(path, fsize);
        if (tjDecompressHeader2(jpegHnd, fileBuf, fsize, &width, &height, &subSamp) != 0)
        {
            perror("tjDecompressHeader2 failed");
            return 0;
        }
        //printf("Success tjDecompressHeader2() : %d x %d, subSamp = %d\n", width, height, subSamp);

        if (subSamp != TJSAMP_420)
        {
            perror("unsupported subSamp");
            return 0;
        }

        unsigned char *yuvBuf = (unsigned char *)malloc(tjBufSizeYUV2(width, 1, height, subSamp));
        if (tjDecompressToYUV2(jpegHnd, fileBuf, fsize, yuvBuf, width, 1, height, 0) != 0)
        {
            perror("tjDecompressToYUV2 failed");
            return 0;
        }

        unsigned char* rgbBuf = (unsigned char*)malloc(width * height * tjPixelSize[TJPF_BGRX]);
        if (tjDecodeYUV (jpegHnd, yuvBuf, 1, subSamp, rgbBuf, width, 0, height, TJPF_BGRX, 0) != 0 ) {
            perror("tjDecodeYUV failed");
            return 0;
        }
        
        free(fileBuf);
        free(yuvBuf);
        return rgbBuf;
    }
};
