#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include "../lib/glimac/include/glimac/common.hpp"
#include "../lib/glimac/include/glimac/glm.hpp"
#include "../include/cube.hpp"
#include "../lib/glimac/include/glimac/TrackballCamera.hpp"

using namespace glimac;

int main(int argc, char** argv)
{
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "World IMaker");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError)
    {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /***************************
     * THE INITIALIZATION CODE *
     ***************************/

    // ----------- Shaders
    FilePath applicationPath(argv[0]);
    Cube cube(applicationPath);
    Program program = loadProgram(applicationPath.dirPath() + "../shaders/3D.vs.glsl", applicationPath.dirPath() + "../shaders/text3D.fs.glsl");
    program.use();

    // ----------- Find uniform var
    GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");


    glEnable(GL_DEPTH_TEST);

    TrackballCamera camera;
    glm::vec2 MousePos;
    glm::vec2 MousePosPrec = MousePos;
    glm::mat4 ViewMatrix;

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            if(e.type == SDL_KEYDOWN){
                float speed = 1.f;
                switch(e.key.keysym.sym){
                    /*//Up arrow key
                    case SDLK_UP : camera.rotateUp(speed);
                    break;
                    //Down arrow key
                    case SDLK_DOWN: camera.rotateUp(-speed);
                    break;
                    //Left arrow key
                    case SDLK_LEFT: camera.rotateLeft(speed);
                    break;
                    //Right arrow key
                    case SDLK_RIGHT: camera.rotateLeft(-speed);
                    break;*/
                    //Z key to move forward
                    case SDLK_z: camera.moveFront(speed);
                    break;
                    //S key to move backward
                    case SDLK_s: camera.moveFront(-speed);
                    break;

                    default: break;
                }
            }

            if(e.type == SDL_MOUSEMOTION){
                MousePos = windowManager.getMousePosition();
                if(e.button.button != 0.0){
                    camera.rotateUp(MousePosPrec.y - MousePos.y);
                    camera.rotateLeft(MousePosPrec.x - MousePos.x);
                }
            }

        }

        ViewMatrix = camera.getViewMatrix();
        MousePosPrec = MousePos;

        /**********************
         * THE RENDERING CODE *
         **********************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ----------- Transformation matrix
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 4.f/3.f, 0.1f, 100.f);
        glm::mat4 MVMatrix = glm::translate(ViewMatrix, glm::vec3(0.f,0.f,0.f));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


        // ----------- Uniform 
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

        // Draw call
        cube.drawCube();

        // Update the display
        windowManager.swapBuffers();
    }

    // Free allocated memory
    cube.deleteData();

    return EXIT_SUCCESS;
}