#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
#include <stdio.h>
#include "ffmpeg.h"

#define UI_WIDTH 640
#define UI_HEIGHT 360

static c_display* s_display;
static c_surface* s_surface;

void render_frame_from_rawdata(c_player* player)
{
    unsigned char* luma = player->av_frame->data[0];
    unsigned char* u = player->av_frame->data[1];
    unsigned char* v = player->av_frame->data[2];

    int width = player->av_frame->linesize[0];
    int height = player->av_frame->height;

    for(int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned char r = *luma++;
            s_surface->draw_pixel(x, y, GL_RGB(r, r, r), Z_ORDER_LEVEL_0);
        }
    }
}

int play_video(const char* file_name)
{
    c_player player(UI_WIDTH, UI_HEIGHT);
    if (!player.ffmpeg_open(file_name))
    {
        return printf("ffmpeg_open failed\n");
    }
    
    if (!player.ffmpeg_read_frame())
    {
        return printf("Couldn't load video frame\n");
    }
    printf("video info: width=%d, height=%d, line size: %d, %d, %d\n", player.av_frame->width, player.av_frame->height, player.av_frame->linesize[0], player.av_frame->linesize[1], player.av_frame->linesize[2]);

    void* phy_fb = s_display->get_updated_fb(0, 0, true);
    double last_seconds = 0;
    while (true)
    {
        if (!player.ffmpeg_read_frame(phy_fb))
        {
            return printf("Couldn't load video frame\n");
        }
        //player.ffmpeg_read_frame();
        //render_frame_from_rawdata(&player);

        double cur_seconds = player.av_frame->pts * (double)player.time_base.num / (double)player.time_base.den;
        if(cur_seconds <= last_seconds)
        {
            break;
        }
        thread_sleep((cur_seconds - last_seconds) * 1000);
        last_seconds = cur_seconds;
    }
    player.ffmpeg_close();
    return 0;
}

void startHelloFFmpeg(const char* file_name, void* phy_fb, int width, int height, int color_bytes)
{
	s_surface = new c_surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_0);
	s_display = new c_display(phy_fb, width, height, s_surface);

    s_surface->fill_rect(0, 0, UI_WIDTH - 1, UI_HEIGHT - 1, 0, Z_ORDER_LEVEL_0);

	play_video(file_name);
}

void captureUiOfHelloFFmpeg()
{
    s_display->snap_shot("snap_short.bmp");
}
