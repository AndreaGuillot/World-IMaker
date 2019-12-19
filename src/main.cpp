#include <GL/glew.h>
#include <iostream>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include "../include/TrackballCamera.hpp"
#include "../include/Cubes.hpp"
#include "../include/Curseur.hpp"
#include "../include/ShaderProgram.hpp"

using namespace glimac;

int main(int argc, char** argv)
{
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "World IMaker");

    // Initialize Imgui interface

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

    // ----------- Objects
    Cubes cube;
    Curseur cursor;

    // ----------- Shaders
    FilePath applicationPath(argv[0]);
    ShaderProgram shaderCube(applicationPath,"ColorCube.fs.glsl");
    ShaderProgram shaderCursor(applicationPath,"ColorCursor.fs.glsl");

    GLint uMVPMatrix, uMVMatrix, uNormalMatrix;
    cube.linkShader(uMVPMatrix, uMVMatrix, uNormalMatrix, shaderCube);
    cursor.linkShader(uMVPMatrix, uMVMatrix, uNormalMatrix, shaderCursor);

    // ----------- Initial scene
    cube.addCube(glm::vec3(0.0, -1.0, 0.0));
    cube.addCube(glm::vec3(0.0, 0.0, 0.0));
    cube.addCube(glm::vec3(0.0, 1.0, 0.0));

    glEnable(GL_DEPTH_TEST);

    // ----------- Event camera
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

            float speed = 1.f;
            float speedRotation = 0.1f;

            if(e.type == SDL_KEYDOWN){

                cursor.onKeyPressed(e);

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

                    case SDLK_SPACE : cube.addCube(cursor.getPosition());
                    break;

                    case SDLK_DELETE : cube.removeCube(cursor.getPosition());
                    break;

                    case SDLK_e : cube.extrudeCube(cursor.getPosition());
                    break;

                    case SDLK_d : cube.digCube(cursor.getPosition());
                    break;

                    default: break;
                }
            }

            if(e.type == SDL_MOUSEMOTION){
                MousePos = windowManager.getMousePosition();
                if(e.button.button != 0.0){
                    camera.rotateUp((MousePosPrec.y - MousePos.y)*speedRotation);
                    camera.rotateLeft((MousePosPrec.x - MousePos.x)*speedRotation);
                }
            }

        }

        MousePosPrec = MousePos;

        /**********************
         * THE RENDERING CODE *
         **********************/

        glClearColor(0.0, 0.0, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw cursor
        shaderCursor.m_program.use();
        cursor.transformMatrix(uMVPMatrix, uMVMatrix, uNormalMatrix, camera);
        cursor.drawCurseur();

        // Draw cube
        shaderCube.m_program.use();
        cube.transformMatrix(uMVPMatrix, uMVMatrix, uNormalMatrix, camera);
        cube.drawCube();

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}