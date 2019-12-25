#include "../include/Interface.hpp"

/********************************
 *        IMGUI INTERFACE       *
 ********************************/

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

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
	ImGui::Begin("Options : Cube");

	glm::vec4 defaultColor = glm::vec4(1.0, 1.0, 1.0, 1.0);

	// Basic options
	if (ImGui::Button("Créer cube")) 
	{
		cube.addCube(cursor.getPosition(), defaultColor);
	}

	ImGui::SameLine();

	if (ImGui::Button("Supprimer cube"))
	{
		cube.removeCube(cursor.getPosition());
	}
	
	// Other options
	if (ImGui::Button("Extruder colonne")) {
		glm::vec4 localizedColor = defaultColor;
		if (cube.findCube(cursor.getPosition()) != -1) {
			localizedColor = cube.getColor()[cube.findCube(cursor.getPosition())];
		}
		cube.extrudeCube(cursor.getPosition(), localizedColor);
	}

	ImGui::SameLine();

	if (ImGui::Button("Creuser colonne")) {
		if (cube.findCube(cursor.getPosition()) != -1) {
			cube.digCube(cursor.getPosition());
		}
	}

	ImGui::ColorEdit4("Couleur", (float*)&defaultColor);

	if (ImGui::Button("Modifier la couleur")) {
		cube.editColor(cursor.getPosition(), defaultColor);
	}

	ImGui::SameLine();

	ImGui::End();
}

void Interface::endFrame() const
{
	SDL_GL_SwapWindow(windowManager.window);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

Interface::~Interface()
{
    SDL_GL_DeleteContext(windowManager.openglContext);
    SDL_DestroyWindow(windowManager.window);
    SDL_Quit();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}