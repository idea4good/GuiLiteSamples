#ifndef _ffmpeg_h
#define _ffmpeg_h

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class c_player {
public:
    c_player(int width, int height, int color_bytes)
    {
        this->width = width;
        this->height = height;
        this->color_bytes = color_bytes;
        sws_ctx = 0;
    }

    bool ffmpeg_open(const char* filename)
    {
        av_register_all();

        av_format_ctx = avformat_alloc_context();
        if (!av_format_ctx) {
            printf("Couldn't created AVFormatContext\n");
            return false;
        }

        if (avformat_open_input(&av_format_ctx, filename, NULL, NULL) != 0) {
            printf("Couldn't open video file\n");
            return false;
        }

        // Find the first valid video stream inside the file
        video_stream_index = -1;
        AVCodecParameters* av_codec_params = 0;
        AVCodec* av_codec = 0;
        for (int i = 0; i < av_format_ctx->nb_streams; ++i) {
            av_codec_params = av_format_ctx->streams[i]->codecpar;
            av_codec = avcodec_find_decoder(av_codec_params->codec_id);
            if (!av_codec) {
                continue;
            }
            if (av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO) {
                video_stream_index = i;
                time_base = av_format_ctx->streams[i]->time_base;
                break;
            }
        }
        if (video_stream_index == -1) {
            printf("Couldn't find valid video stream inside file\n");
            return false;
        }

        // Set up a codec context for the decoder
        av_codec_ctx = avcodec_alloc_context3(av_codec);
        if (!av_codec_ctx) {
            printf("Couldn't create AVCodecContext\n");
            return false;
        }
        if (avcodec_parameters_to_context(av_codec_ctx, av_codec_params) < 0) {
            printf("Couldn't initialize AVCodecContext\n");
            return false;
        }
        if (avcodec_open2(av_codec_ctx, av_codec, NULL) < 0) {
            printf("Couldn't open codec\n");
            return false;
        }

        av_frame = av_frame_alloc();
        if (!av_frame) {
            printf("Couldn't allocate AVFrame\n");
            return false;
        }
        av_packet = av_packet_alloc();
        if (!av_packet) {
            printf("Couldn't allocate AVPacket\n");
            return false;
        }
        return true;
    }

    bool ffmpeg_read_frame(void* phy_fb = 0, AVPixelFormat pixel_format = AV_PIX_FMT_RGB565LE)
    {
        // Decode one frame
        int response;
        while (av_read_frame(av_format_ctx, av_packet) >= 0) {
            if (av_packet->stream_index != video_stream_index) {
                av_packet_unref(av_packet);
                continue;
            }

            response = avcodec_send_packet(av_codec_ctx, av_packet);
            if (response < 0) {
                printf("Failed to decode packet\n");
                return false;
            }

            response = avcodec_receive_frame(av_codec_ctx, av_frame);
            if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
                av_packet_unref(av_packet);
                continue;
            } else if (response < 0) {
                printf("Failed to decode packet\n");
                return false;
            }
            av_packet_unref(av_packet);
            break;
        }

        //scale frame & rendering on physical frame buffer
        if(!phy_fb)
        {
            return true;
        }
        if(!sws_ctx)
        {
            sws_ctx = sws_getContext(av_codec_ctx->width, av_codec_ctx->height, av_codec_ctx->pix_fmt, width, height, pixel_format, SWS_BILINEAR, NULL, NULL, NULL);
        }
        
        uint8_t *frame_buffer[4] = { (uint8_t*)phy_fb, 0, 0, 0};
        int stride[4] = {color_bytes * width, 0, 0, 0};
        sws_scale(sws_ctx, av_frame->data, av_frame->linesize, 0, av_frame->height, frame_buffer, stride);
        return true;
    }

    bool ffmpeg_seek_frame(int64_t ts)
    {
        av_seek_frame(av_format_ctx, video_stream_index, ts, AVSEEK_FLAG_BACKWARD);

        int response;
        while (av_read_frame(av_format_ctx, av_packet) >= 0) {
            if (av_packet->stream_index != video_stream_index) {
                av_packet_unref(av_packet);
                continue;
            }

            response = avcodec_send_packet(av_codec_ctx, av_packet);
            if (response < 0) {
                printf("Failed to decode packet");
                return false;
            }

            response = avcodec_receive_frame(av_codec_ctx, av_frame);
            if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
                av_packet_unref(av_packet);
                continue;
            } else if (response < 0) {
                printf("Failed to decode packet\n");
                return false;
            }

            av_packet_unref(av_packet);
            break;
        }
        return true;
    }

    void ffmpeg_close()
    {
        avformat_close_input(&av_format_ctx);
        avformat_free_context(av_format_ctx);
        av_frame_free(&av_frame);
        av_packet_free(&av_packet);
        avcodec_free_context(&av_codec_ctx);
    }

    AVFormatContext* av_format_ctx;
    AVCodecContext* av_codec_ctx;
    SwsContext *sws_ctx;
    AVFrame* av_frame;
    AVPacket* av_packet;
    int width, height, video_stream_index, color_bytes;
    AVRational time_base; 
};

#endif
