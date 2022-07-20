#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
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

	// todo: init에서 빼내기
	SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
	if (!pTempSurface)
	{
		// Return is NULL, an error occurred
		std::cout << "SDL_LoadBMP : return was NULL" << std::endl;
		return 0;
	}
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
	if (!m_pTexture)
	{
		// Return is NULL, an error occurred
		std::cout << "SDL_CreateTextureFromSurface : return was NULL" << std::endl;
		return 0;
	}
	SDL_FreeSurface(pTempSurface);

	// 원본상자
	SDL_QueryTexture(m_pTexture, NULL, NULL,
		&m_sourceRectangle.w, &m_sourceRectangle.h);

	// 대상상자
	m_destinationRectangle.w = m_sourceRectangle.w;
	m_destinationRectangle.h = m_sourceRectangle.h;

	// 배경
	pTempSurface = IMG_Load("assets/bakcground.png");
	if (!pTempSurface)
	{
		// Return is NULL, an error occurred
		std::cout << "SDL_LoadBMP : return was NULL" << std::endl;
		return 0;
	}
	m_pTextureBackground = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
	if (!m_pTextureBackground)
	{
		// Return is NULL, an error occurred
		std::cout << "SDL_CreateTextureFromSurface : return was NULL" << std::endl;
		return 0;
	}
	SDL_FreeSurface(pTempSurface);

	// 원본상자
	SDL_QueryTexture(m_pTextureBackground, NULL, NULL,
		&m_sourceRectangleBackground.w, &m_sourceRectangleBackground.h);

	// 대상상자
	m_destinationRectangleBackground.w = SCREEN_WIDTH;
	m_destinationRectangleBackground.h = SCREEN_HEIGHT;

	m_bRunning = true;
	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	SDL_RenderCopy(m_pRenderer, m_pTextureBackground, &m_sourceRectangleBackground, &m_destinationRectangleBackground);
	isMoveDirectionRight ?
		SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0.0, NULL, SDL_FLIP_HORIZONTAL)
		: SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
	if (isMoveDirectionRight)
	{
		if (m_destinationRectangle.x + m_sourceRectangle.w < SCREEN_WIDTH)
		{
			m_destinationRectangle.x++;
		}
		else
		{
			isMoveDirectionRight = !isMoveDirectionRight;
		}
	}
	else
	{
		if (m_destinationRectangle.x > 0)
		{
			m_destinationRectangle.x--;
		}
		else
		{
			isMoveDirectionRight = !isMoveDirectionRight;
		}
	}
	SDL_Delay(1);
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