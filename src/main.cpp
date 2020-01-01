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
#include "../include/Interface.hpp"
#include "../include/GameControls.hpp"

using namespace glimac;

int main(int argc, char** argv)
{
    // ----------- Initialize interface
    Interface interface;

    displayControls();

    /***************************
     * THE INITIALIZATION CODE *
     ***************************/

    Cubes cube;
    Curseur cursor;

    // ----------- Shaders
    FilePath applicationPath(argv[0]);
    ShaderProgram cubeProgram(applicationPath, "ColorCube.fs.glsl");
    ShaderProgram cursorProgram(applicationPath, "ColorCursor.fs.glsl");

    // ----------- Initialize scene
    cube.addCube(glm::vec3(0.0, -1.0, 0.0), glm::vec4(0.8, 0.2, 0.3, 1.));
    cube.addCube(glm::vec3(0.0, 0.0, 0.0),  glm::vec4(0.3, 0.8, 0.2, 1.));
    cube.addCube(glm::vec3(0.0, 1.0, 0.0),  glm::vec4(0.2, 0.3, 0.8, 1.));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ----------- Event camera
    TrackballCamera camera;
    
    /***************************
     *    APPLICATION LOOP     *
     ***************************/

    glm::vec2 MousePos;
    glm::vec2 MousePosPrec = MousePos;

    while(interface.isRunning()) {
        // Event loop:
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            float speed = 1.f;
            float speedRotation = 0.1f;

            switch(e.type)
            {
                // 1. Leave the loop after this iteration
                case(SDL_QUIT)  : interface.exit();
                // 2. Keyboard options
                case(SDL_KEYDOWN) : cursor.onKeyPressed(e);
                    switch(e.key.keysym.sym)
                    {
                        /*
                        //Up arrow key
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
                        break;
                        */
                        case SDLK_z : camera.moveFront(speed);
                        break;
                        case SDLK_s : camera.moveFront(-speed);
                        break;
                        case SDLK_SPACE : cube.addCube(cursor.getPosition(), cube.getLastColor());
                        break;
                        case SDLK_c : cube.addCube(cursor.getPosition(), glm::vec4(0.8, 0.2, 0.3, 1.0));
                        break;
                        case SDLK_v : cube.addCube(cursor.getPosition(), glm::vec4(0.3, 0.8, 0.2, 1.0));
                        break;
                        case SDLK_b : cube.addCube(cursor.getPosition(), glm::vec4(0.2, 0.3, 0.8, 1.0));
                        break;
                        case SDLK_DELETE : cube.removeCube(cursor.getPosition());
                        break;
                        case SDLK_e : cube.extrudeCube(cursor.getPosition(), cube.getLastColor());
                        break;
                        case SDLK_d : cube.digCube(cursor.getPosition());
                        break;
                        default : break;
                    }
                // 3. Mouse options
                case(SDL_MOUSEMOTION) : MousePos = interface.windowManager.getMousePosition();
                    if(e.button.button != 0.0)
                    {
                        camera.rotateUp((MousePosPrec.y - MousePos.y) * speedRotation);
                        camera.rotateLeft((MousePosPrec.x - MousePos.x) * speedRotation);
                    }
            }   
        }

        MousePosPrec = MousePos;

        /*glm::vec3 lightDir = glm::vec3(1.f, 1.f, 1.f);

        glUniform3fv(uLightDir, 1, glm::value_ptr(lightDir));*/

        /**********************
         * THE RENDERING CODE *
         **********************/

        // Calling new frame
        interface.startFrame();

        // Calling ImGui menu 
        interface.editCube(cube, cursor);

        // Draw cursor
        cursorProgram.useProgram();
        cursorProgram.createViewMatrix(camera);
        cursor.drawCurseur();

        // Draw cube
        cubeProgram.useProgram();
        cubeProgram.createViewMatrix(camera);
        cube.drawCube();

        // Update the display
        interface.endFrame();
    }

    return EXIT_SUCCESS;
}