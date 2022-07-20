#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
class Game {
public:
    Game() {
        isMoveDirectionRight = true;
    }
    ~Game() {}

    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    void render();
    void update();
    bool running() const;
    void handleEvents();
    void clean();

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    // 텍스쳐를 저장할 변수
    SDL_Texture* m_pTexture;
    // 원본 사각형 - 이미지를 어떻게 잘라서 출력할지
    SDL_Rect m_sourceRectangle;
    // 대상 사각형 - 이미지가 화면의 어떤 위치에 출력될지
    SDL_Rect m_destinationRectangle;

    // 배경
    SDL_Texture* m_pTextureBackground;
    SDL_Rect m_sourceRectangleBackground;
    SDL_Rect m_destinationRectangleBackground;

    const unsigned int SCREEN_WIDTH = 640;
    const unsigned int SCREEN_HEIGHT = 480;

    // 캐릭터 좌우 이동을 위한 변수
    bool isMoveDirectionRight;

    // 텍스트 변수들
    TTF_Font* font;
    SDL_Texture* textTexture;
    SDL_Rect textDestination;

    // 07. 대상상자 원본상자 응용 실습 임시변수
    SDL_Rect tempRect;
    bool m_bRunning;
    SDL_Event e;
};