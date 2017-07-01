#pragma once
// Tell SDL not to mess with main()

#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define SDL_MAIN_HANDLED

//#include <SDL2\SDL.h>
#include "VulkanStuff.h"

SDL_Window* window;

bool SDLInit();

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

int main()
{
	if (SDLInit()) {
		std::unique_ptr<VulkanStuff> vulkan(new VulkanStuff(window));
		vulkan->initVulkan();
		vulkan->mainLoop();
	}
	system("pause");
	return 0;
}

bool SDLInit() {
	try {
		// Create an SDL window that supports Vulkan and OpenGL rendering.
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			throw std::runtime_error("Could not initialize SDL. Line: " + __LINE__ + static_cast<std::string>(" File: ") + __FILE__);
		}
		window = SDL_CreateWindow("Vulkan Window", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (window == NULL) {
			throw std::runtime_error("Could not create SDL window. Line: " + __LINE__ + static_cast<std::string>(" File: ") + __FILE__);
		}
	}
	catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

