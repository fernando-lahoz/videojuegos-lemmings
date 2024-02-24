#include <iostream>
#include <iomanip>
#include <chrono>

#include <SDL2/SDL.h>


extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libavutil/avutil.h>
}

int main(int, char**)
{
    int init_flags = SDL_INIT_EVERYTHING;
    if (SDL_Init(init_flags) != 0) {
        std::cerr << "SDL failed to init: " << SDL_GetError() << '\n';
        return EXIT_FAILURE;
    }

    int window_flags = SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/;
    SDL_Window *window = SDL_CreateWindow("Hello World!",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            1280, 720, window_flags);
    if (window == nullptr) {
        std::cerr << "SDL failed to create window: " << SDL_GetError() << '\n';
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "SDL failed to create renderer: " << SDL_GetError() << '\n';
        return EXIT_FAILURE;
    }

    //==========================================================================

    AVFormatContext *pFormatCtx = nullptr;
    int             i, videoStream;
    AVCodecContext *pCodecCtx = nullptr;
    AVCodecParameters *pCodecPar = nullptr;
    const AVCodec    *pCodec = nullptr;
    AVFrame         *pFrame = nullptr; 
    AVPacket        packet;

    AVDictionary    *optionsDict = nullptr;

    // Open video file
    if (avformat_open_input(&pFormatCtx, "../assets/video/test.mp4", nullptr, nullptr) != 0) {
        std::cerr << "Failed to open video file\n";
        return EXIT_FAILURE;
    }

    // Retrieve stream information
    if(avformat_find_stream_info(pFormatCtx, nullptr) < 0) {
        std::cerr << "Couldn't find stream information\n";
        return EXIT_FAILURE;
    }

    // Dump information about file onto standard error
    //av_dump_format(pFormatCtx, 0, "../assets/video/test.mp4", 0);

    // Find the first video stream
    videoStream = -1;
    for (i = 0; i < (int)pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }
        
    if(videoStream == -1) {
        std::cerr << "Didn't find a video stream\n";
        return EXIT_FAILURE;
    }

    // Get a pointer to the codec context for the video stream
    pCodecPar = pFormatCtx->streams[videoStream]->codecpar;

    // Find the decoder for the video stream
    pCodec = avcodec_find_decoder(pCodecPar->codec_id);
    if (pCodec == nullptr) {
        std::cerr << "Unsupported codec!\n";
        return EXIT_FAILURE; // Codec not found
    }

    std::cout << "CODEC: " << pCodec->long_name << '\n';

    pCodecCtx = avcodec_alloc_context3(pCodec);

    if (avcodec_parameters_to_context(pCodecCtx, pCodecPar) < 0) {
        std::cerr << "Unable to change parameters to context\n";
        return EXIT_FAILURE;
    }

    // Open codec
    if (avcodec_open2(pCodecCtx, pCodec, &optionsDict) < 0) {
        std::cerr << "Unable to open codec\n";
        return EXIT_FAILURE; 
    }

    // Allocate video frame
    pFrame = av_frame_alloc();

   // SDL_SetWindowSize(window, pCodecCtx->width, pCodecCtx->height);

    std::cout << "w: " << pCodecCtx->width << ", h: " << pCodecCtx->height << '\n';


    SDL_Texture* texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_IYUV, //SDL_PIXELFORMAT_YV12
            SDL_TEXTUREACCESS_STREAMING,
            pCodecCtx->width, pCodecCtx->height
        );

    //=========================================================================

    std::cout << "Just before streaming!!! \n";

    double frame_delay = 1.0 / av_q2d(pCodecCtx->framerate);
    
    std::chrono::time_point start = std::chrono::steady_clock::now();
    std::chrono::time_point frame_time = start;

    auto process_events = [&]() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return false;
        }
        return true;
    };

    int drawed_frames = 0;
    // Read frames and save first five frames to disk
    while (process_events())
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        frame_time = std::chrono::steady_clock::now();
        double delay = std::chrono::duration<double>(frame_time - start).count();
        while (delay > drawed_frames * frame_delay) { // draw frame
            // Is this a packet from the video stream?
            bool any_video_found = false;
            while (av_read_frame(pFormatCtx, &packet) >= 0) {
                if (packet.stream_index == videoStream) {
                    any_video_found = true;
                    break;
                }  
            }
            if (any_video_found) {
                drawed_frames++;
                if (avcodec_send_packet(pCodecCtx, &packet) != 0)
                    std::cout << "Failed to send!!! \n";
                if (avcodec_receive_frame(pCodecCtx, pFrame) != 0)
                    std::cout << "Failed to receive!!! \n";

                SDL_UpdateYUVTexture(
                    texture, nullptr,
                    pFrame->data[0], pFrame->linesize[0], 
                    pFrame->data[1], pFrame->linesize[1],
                    pFrame->data[2], pFrame->linesize[2]
                );
            }
        }

        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        // Free the packet that was allocated by av_read_frame
        av_packet_unref(&packet);
    }

    // Free the YUV frame
    av_free(pFrame);
    
    // Close the codec
    avcodec_close(pCodecCtx);
    
    // Close the video file
    avformat_close_input(&pFormatCtx);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}