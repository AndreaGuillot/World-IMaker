#pragma  once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include <glimac/SDLWindowManager.hpp>
#include "Curseur.hpp"
#include "Map.hpp"

/********************************
 *     CREATE USER INTERFACE    *
 ********************************/

class Interface
{
	private:
		bool m_running = true;
	public:
		SDLWindowManager windowManager;

	public:
		// initialization
		Interface();
		~Interface();
		// display
		void startFrame() const;
		void editScene(Cubes &cube, Map &map) const;
		void editCube(Cubes &cube, Curseur &cursor, Map &map) const;
		void editMap(Cubes &cube, Map &map, glm::vec4 defaultColor) const;
		void endFrame() const;
		// loop
		inline bool isRunning() const { return m_running; }
		inline void exit() { m_running = false; }
		inline SDLWindowManager getWindowManager() const { return windowManager; }  // doesn't work (??)
};