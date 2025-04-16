#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include "C:\C++\GAME\GAME\src\include\SDL2\SDL.h"
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL_image.h"
#include "defs.h"
#include "C:\C++\GAME\GAME\src\include\SDL2\SDL_mixer.h"
#include <vector>

struct ScrollingBackground
{
    SDL_Texture *texture;    // Chứa ảnh nền
    int scrollingOffset = 0; // Vị trí ảnh nền
    int width, height;       // Kích thước ảnh nền lấy từ Query
    // Gán texture cho nền cuộn và lấy kích thước của texture
    void setTexture(SDL_Texture *_texture)
    {
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }
    // Dịch chuyển nền theo hướng ngang
    void scroll(int distance)
    {
        scrollingOffset -= distance; // Tạo hiệu ứng di chuyển từ phải sang trái
        if (scrollingOffset < 0)
        {
            scrollingOffset = width;
        }
        // Đặt lại nó về width, giúp nền lặp lại vô hạn
    }
};

struct Graphics
{
    SDL_Renderer *renderer;
    SDL_Window *window;

    void logErrorAndExit(const char *msg, const char *error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }
    // Log lỗi của SDL -> Thoát chương trình
    void init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        // full screen
        // window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (window == nullptr)
            logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit("SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        // Accelerated là dùng GPU tăng hiệu suất, PRESENTVSYNC đồng bộ tốc độ khung hình
        //  Khi chạy trong máy ảo
        //  renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr)
            logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        // Thiết lập chất lượng đồ hoạ
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        // Đặt kích thước logic của render
        SDL_ShowCursor(0);
        // Ẩn con trỏ chuột
    }
    // Hiển thị ảnh nền
    void prepareImg(SDL_Texture *background)
    {
        /* SDL_RenderClear(renderer);
        // Xoá màn hình */
        SDL_RenderCopy(renderer, background, NULL, NULL);
        // Sao chép texture lên renderer
    }

    // Chuẩn bị cảnh vẽ
    void prepareScene(SDL_Texture *background = nullptr)
    {
        /*  SDL_RenderClear(renderer);
         // Xoá màn hình */
        if (background != nullptr)
            SDL_RenderCopy(renderer, background, NULL, NULL);
        // Nếu có ảnh nền -> sao chép lên renderer
    }
    // Hiển thị nội dung renderer lên màn hình
    void presentScene()
    {
        SDL_RenderPresent(renderer);
        // Cấp nhật màn hình
    }
    // Tải ảnh từ tệp và chuyển thành SDL_Texture
    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        // Tải ảnh
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
        // trả về texture đã tải
    }
    // Vẽ texture lên màn hình tại vị trí x,y
    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;
        // Tạo vị trí và kích thước
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        // Lấy kích thước của texture

        SDL_RenderCopy(renderer, texture, NULL, &dest);
        // Vẽ texture lên renderer
    }
    // Cắt 1 phần src và vẽ lên x,y
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;
        // Tạo dest với vị trí x,y và kích thước src
        SDL_RenderCopy(renderer, texture, src, &dest);
        // Sao chép 1 phần texture src lên renderer tại dest
    }
    // Giải phóng
    void quit()
    {
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    // Hiển thị ảnh nền cuộn
    void render(const ScrollingBackground &background)
    {
        renderTexture(background.texture, background.scrollingOffset, 0);
        // Vẽ ảnh nền tại vị trí scrollingOffset
        renderTexture(background.texture, background.scrollingOffset - background.width, 0);
        // Vẽ lại 1 lần nữa ngay phía sau để tạo hiệu ứng lặp
    }
    Mix_Music *loadMusic(const char *path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                           "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }

    void play(Mix_Music *gMusic)
    {
        if (gMusic == nullptr)
            return;

        if (Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(gMusic, -1);
        }
        else if (Mix_PausedMusic() == 1)
        {
            Mix_ResumeMusic();
        }
    }

    Mix_Chunk *loadSound(const char *path)
    {
        Mix_Chunk *gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                           "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
    }
    void play(Mix_Chunk *gChunk)
    {
        if (gChunk != nullptr)
        {
            Mix_PlayChannel(-1, gChunk, 0);
        }
    }
};

#endif // _GRAPHICS__H
