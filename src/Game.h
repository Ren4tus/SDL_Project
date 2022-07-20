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
    // �ؽ��ĸ� ������ ����
    SDL_Texture* m_pTexture;
    // ���� �簢�� - �̹����� ��� �߶� �������
    SDL_Rect m_sourceRectangle;
    // ��� �簢�� - �̹����� ȭ���� � ��ġ�� ��µ���
    SDL_Rect m_destinationRectangle;

    // ���
    SDL_Texture* m_pTextureBackground;
    SDL_Rect m_sourceRectangleBackground;
    SDL_Rect m_destinationRectangleBackground;

    const unsigned int SCREEN_WIDTH = 640;
    const unsigned int SCREEN_HEIGHT = 480;

    // ĳ���� �¿� �̵��� ���� ����
    bool isMoveDirectionRight;

    // �ؽ�Ʈ ������
    TTF_Font* font;
    SDL_Texture* textTexture;
    SDL_Rect textDestination;

    // 07. ������ �������� ���� �ǽ� �ӽú���
    SDL_Rect tempRect;
    bool m_bRunning;
    SDL_Event e;
};