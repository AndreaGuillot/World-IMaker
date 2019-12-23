#include "../include/Cubes.hpp"

/********************************
 *       CREATE A 3D CUBE       *
 ********************************/

Cubes::Cubes()
{
    //    v4----- v7
    //   /|      /|
    //  v0------v3|
    //  | |     | |
    //  | |v5---|-|v6
    //  |/      |/
    //  v1------v2

    std::vector<glm::vec3> cube_vertex = {
        // front face
        glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f),
        // back face
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f),
        // left face
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, -0.5f),
        // right face
        glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f),
        // top face
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f),
        // bot face
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f)
    };

    glm::vec3 normals[] = {
    	// front face
    	glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), 
    	// back face
    	glm::vec3(0, 0, -1), glm::vec3(0, 0, -1), glm::vec3(0, 0, -1), glm::vec3(0, 0, -1), 
    	// left face
    	glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0),glm::vec3(-1, 0, 0),glm::vec3(-1, 0, 0),
    	// right face
    	glm::vec3(1, 0, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0),glm::vec3(1, 0, 0),
    	// top face
    	glm::vec3(0, 1, 0),glm::vec3(0, 1, 0),glm::vec3(0, 1, 0),glm::vec3(0, 1, 0),
    	// bot face
    	glm::vec3(0, -1, 0),glm::vec3(0, -1, 0),glm::vec3(0, -1, 0),glm::vec3(0, -1, 0)
    };
    
    for(size_t i = 0; i < 24; ++i)
    {
        ShapeVertex vertex;
        
        vertex.texCoords.x = 0;
        vertex.texCoords.y = 1;

        vertex.position = cube_vertex[i];
        vertex.normal = normals[i];
        
        this->m_vertex.push_back(vertex);
    }

    // --- VERTEX BUFFER
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER,this->vbo);
    glBufferData(GL_ARRAY_BUFFER, (this->m_vertex.size()+1) * sizeof(ShapeVertex), this->m_vertex.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glGenBuffers(1, &this->vbPos);
    glBindBuffer(GL_ARRAY_BUFFER,this->vbPos);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    // --- INDEX BUFFER
    glGenBuffers(1, &this->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);

        // Index table
        std::vector<uint32_t> index = {
            0, 1, 2,  0, 2, 3,    // front
            4, 5, 6,  4, 6, 7,    // back
            8, 9, 10,  8, 10, 11,    // back
            12, 13, 14,  12, 14, 15,    // back
            16, 17, 18,  16, 18, 19,    // back
            20, 21, 22,  20, 22, 23    // back
         };


    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (index.size()+1) * sizeof(uint32_t), index.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // --- INDEX BUFFER WIREFRAME
    glGenBuffers(1, &this->iboWireframe);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboWireframe);

        // Index table
        std::vector<uint32_t> index_w = {
            1, 0, 3, 2, 0, 3, 1, 2,    // front
            5, 4, 7, 6, 4, 7, 5, 6,    // back
            3, 7, 0, 4,                // top
            2, 6, 1, 5                 // bottom
        };


    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (index_w.size()+1) * sizeof(uint32_t), index_w.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // --- VERTEX ARRAY
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);

        // Activation - Specification
        {
            const GLuint VERTEX_ATTR_POSITION = 0;
            const GLuint VERTEX_ATTR_NORMAL = 2;
            const GLuint CUBE_ATTR_POSITION = 1;

            glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), NULL);

            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (void*)(3*sizeof(float)));
            
            glBindBuffer(GL_ARRAY_BUFFER, this->vbPos);
            glEnableVertexAttribArray(CUBE_ATTR_POSITION);
            glVertexAttribPointer(CUBE_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), NULL);
           
            // advance in the buffer at each new cube drawing
            glVertexAttribDivisor(1, 1);
        }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cubes::getLocation(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, GLint &uLightDir, ShaderProgram &shader)
{
    uMVPMatrix = glGetUniformLocation(shader.m_program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(shader.m_program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(shader.m_program.getGLId(), "uNormalMatrix");
    uLightDir = glGetUniformLocation(shader.m_program.getGLId(), "uLightDir"); 
}

void Cubes::transformMatrix(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, GLint &uLightDir, const TrackballCamera &camera) const
{   
    glm::mat4 ViewMatrix = camera.getViewMatrix();
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 4.f/3.f, 0.1f, 100.f);
    glm::mat4 MVMatrix = glm::translate(ViewMatrix, glm::vec3(0.f,0.f,0.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::vec3 lightDir = glm::vec3(1.f, 1.f, 1.f);
    
    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniform3fv(uLightDir, 1, glm::value_ptr(lightDir));
}

void Cubes::drawCube()
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, this->m_position.size());
    glBindVertexArray(0);
};

void Cubes::drawCubeWireframe()
{
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboWireframe);
    glDrawElementsInstanced(GL_LINES, 24, GL_UNSIGNED_INT, 0, this->m_position.size());
    glBindVertexArray(0);
};

void Cubes::updateGPU()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vbPos); 
    glBufferData(GL_ARRAY_BUFFER, (this->m_position.size()+1) * sizeof(glm::vec3), this->m_position.size() > 0 ? &this->m_position[0] : nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

int Cubes::findCube(glm::vec3 position)
{
    for(size_t j = 0; j < m_position.size(); j++)
    {
        if(glm::length(position - m_position[j]) < 0.1f)
        {
            // find
            return j;
        }
    }
    // not find
    return -1;
};

void Cubes::removeCube(glm::vec3 position)
{
    int index = findCube(position);
    if(index != -1)
    {
        // put the item to delete at the end
        int lastIndex = m_position.size() - 1;
        std::swap(m_position[index], m_position[lastIndex]);
        this->m_position.pop_back();

        updateGPU();
    }
};

void Cubes::addCube(glm::vec3 position)
{
    removeCube(position);
    this->m_position.push_back(position);
    updateGPU();
};

void Cubes::extrudeCube(glm::vec3 position){
    int index = 0;
    while(index != -1){
        index = findCube(position);
        position.y++;
    }
    position.y--;
    addCube(position);
}

void Cubes::digCube(glm::vec3 position){
    int index = 0;
    while(index != -1){
        index = findCube(position);
        position.y++;
    }
    position.y -= 2.f;
    removeCube(position);
}

Cubes::~Cubes()
{
    glDeleteBuffers(1, &this->vbo);
    glDeleteBuffers(1, &this->vbPos);
    glDeleteBuffers(1, &this->ibo);
    glDeleteBuffers(1, &this->iboWireframe);
    glDeleteVertexArrays(1, &this->vao);
}