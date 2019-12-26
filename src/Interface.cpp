#include "../include/Interface.hpp"

/********************************
 *        IMGUI INTERFACE       *
 ********************************/

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

Interface::Interface() : windowManager(SDLWindowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "World IMaker"))
{
	// Initialize Glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError)
    {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        std::exit(0);
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(windowManager.window, windowManager.openglContext);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();

}

void Interface::startFrame() const
{
	glClearColor(0.0, 0.0, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(windowManager.window);
    ImGui::NewFrame();
}

void Interface::editCube(Cubes &cube, Curseur &cursor) const
{
	ImGui::SetNextWindowPos(ImVec2(10, 10));
    
	glm::vec4 defaultColor = glm::vec4(1.0, 1.0, 1.0, 1.0);

	ImGui::Begin("Options : Cube / Colonne");
	{
		ImGui::Text("Action pour un cube :");
		{
			if (ImGui::Button("  Créer cube   "))
			{
				cube.addCube(cursor.getPosition(), defaultColor);
			}

			ImGui::SameLine();

			if (ImGui::Button(" Supprimer cube "))
			{
				cube.removeCube(cursor.getPosition());
			}
		}
		
		ImGui::Text("Action sur une colonne :");
		{
			if (ImGui::Button("Extrude colonne")) {
				glm::vec4 localizedColor = defaultColor;
				if (cube.findCube(cursor.getPosition()) != -1) {
					localizedColor = cube.getColor()[cube.findCube(cursor.getPosition())];
				}
				cube.extrudeCube(cursor.getPosition(), localizedColor);
			}

			ImGui::SameLine();

			{
				if (ImGui::Button("  Dig  colonne  ")) {
					if (cube.findCube(cursor.getPosition()) != -1) {
						cube.digCube(cursor.getPosition());
					}
				}
			}
		}
		
		ImGui::Text("Choisir la couleur du cube :");
		{
			if (ImGui::Button("Modifier couleur")) {
				cube.editColor(cursor.getPosition(), defaultColor);
			}
		}
	}
	ImGui::End();
}

void Interface::endFrame() const
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(windowManager.window);
}

Interface::~Interface()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(windowManager.openglContext);
    SDL_DestroyWindow(windowManager.window);
    SDL_Quit();
}