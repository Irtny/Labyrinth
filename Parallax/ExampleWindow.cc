/*
 * ExampleWindow.cc
 *
 *  Created on: 31 ���. 2021 �.
 *      Author: fomin
 */

#include "ExampleWindow.h"
#include <stdexcept>
#include <SDL2/SDL_image.h>

ExampleWindow::ExampleWindow(int width, int height)
: Window(width, height), _bee_x(500), _bee_y(300), _bee_phase(0.)
{
	_bee = std::shared_ptr<SDL_Texture>(
			IMG_LoadTexture(_renderer.get(), "bee.png"),
			SDL_DestroyTexture);
	if (_bee == nullptr)
		throw std::runtime_error(
				std::string("�� ������� ��������� �����") +
				std::string(SDL_GetError()));
}

void ExampleWindow::render()
{
	SDL_SetRenderDrawColor(_renderer.get(), 32, 32, 96, 255);
	SDL_RenderClear(_renderer.get());

	SDL_Rect bee_rect { _bee_x, _bee_y, 256, 256 };
	// SDL_Rect r { 100, 100, 200, 150 };
	SDL_RenderCopy(_renderer.get(), _bee.get(), nullptr, &bee_rect);


}

void ExampleWindow::do_logic()
{
	_bee_x+= 4;
	if (_bee_x >= width())
		_bee_x = -256;
	_bee_y += 4 * sin(_bee_phase);
	_bee_phase +=0.1;
}

void ExampleWindow::handle_keys(const Uint8 *keys)
{
	if (keys[SDL_SCANCODE_DOWN])
		_bee_y += 2;
	if (keys[SDL_SCANCODE_UP])
		_bee_y -= 2;
}
