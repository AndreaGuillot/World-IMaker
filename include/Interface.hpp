#pragma  once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <stdio.h>
#include <glimac/SDLWindowManager.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include "Curseur.hpp"

using namespace glimac;

class Interface
{
	private:
		bool m_running = true;
	public:
		SDLWindowManager windowManager;

	public:
		// constructor
		Interface();
		// display
		void startFrame() const;
		void editCube(Cubes &cube, Curseur &cursor) const;
		void endFrame() const;
		// destructor
		~Interface();

		inline bool isRunning() const { return m_running; }
		inline void exit() { m_running = false; }
		//inline SDLWindowManager getWindowManager() const { return windowManager; }
};