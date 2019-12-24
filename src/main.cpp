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

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char** argv)
{
    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "World IMaker");

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

    Cubes cube;
    Curseur cursor;

    // ----------- Shaders
    FilePath applicationPath(argv[0]);
    ShaderProgram cubeProgram(applicationPath, "ColorCube.fs.glsl");
    ShaderProgram cursorProgram(applicationPath, "ColorCursor.fs.glsl");

    // ----------- Uniform locations
    GLint uMVPMatrix, uMVMatrix, uNormalMatrix;
    GLint uLightDir;
    cube.getLocation(uMVPMatrix, uMVMatrix, uNormalMatrix, cubeProgram);
    cursor.getLocation(uMVPMatrix, uMVMatrix, uNormalMatrix, cursorProgram);

    // ----------- Initialize scene
    cube.addCube(glm::vec3(0.0, -1.0, 0.0), glm::vec4(0.8, 0.2, 0.3, 1.));
    cube.addCube(glm::vec3(0.0, 0.0, 0.0), glm::vec4(0.3, 0.8, 0.2, 1.));
    cube.addCube(glm::vec3(0.0, 1.0, 0.0), glm::vec4(0.2, 0.3, 0.8, 1.));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ----------- Event camera
    TrackballCamera camera;
    
    glm::vec2 MousePos;
    glm::vec2 MousePosPrec = MousePos;
    glm::mat4 ViewMatrix;

    glm::vec4 defaultColor = glm::vec4(1.0, 1.0, 1.0, 1.0);

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

                    case SDLK_SPACE : cube.addCube(cursor.getPosition(), defaultColor);
                    break;

                    case SDLK_DELETE : cube.removeCube(cursor.getPosition());
                    break;

                    case SDLK_e : cube.extrudeCube(cursor.getPosition(), defaultColor);
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

        /*glm::vec3 lightDir = glm::vec3(1.f, 1.f, 1.f);

        glUniform3fv(uLightDir, 1, glm::value_ptr(lightDir));*/

        /**********************
         * THE RENDERING CODE *
         **********************/

        glClearColor(0.0, 0.0, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw cursor
        cursorProgram.m_program.use();
        cursor.transformMatrix(uMVPMatrix, uMVMatrix, uNormalMatrix, uLightDir, camera);
        cursor.drawCurseur();

        // Draw cube
        cubeProgram.m_program.use();
        //glUniform1i(cubeProgram.uColor, 1);
        cube.transformMatrix(uMVPMatrix, uMVMatrix, uNormalMatrix, uLightDir, camera);
        cube.drawCube();

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}