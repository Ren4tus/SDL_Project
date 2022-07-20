#include "Game.h"
#include <cstdlib>
#include<ctime>
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) {
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else {
				return false; // 렌더러 생성 실패
			}
		}
		else {
			return false; // 윈도우 생설 실패 l
		}
	}
	else {
		return false; // SDL 초기화 실패
	}
	srand((unsigned int)time(NULL));
	m_bRunning = true;
	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
	SDL_SetRenderDrawColor(m_pRenderer, rand() % 256, rand() % 256, rand() % 256, 255);
	SDL_Delay(1000);
}
bool Game::running() const
{
	return m_bRunning;
}

void Game::handleEvents()
{
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type) {
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}