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
        // front
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        // back
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f)
    };
    
    for(size_t i = 0; i < 8; ++i)
    {
        ShapeVertex vertex;
        
        vertex.texCoords.x = 0;
        vertex.texCoords.y = 1;

        vertex.normal.x = cube_vertex[i].x;
        vertex.normal.y = cube_vertex[i].y;
        vertex.normal.z = cube_vertex[i].z;
        
        vertex.position = vertex.normal;
        
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
            1, 0, 3,    1, 2, 3,    // front
            5, 4, 7,    5, 6, 7,    // back
            3, 0, 4,    3, 7, 4,    // top
            2, 1, 5,    2, 6, 5,    // bottom
            5, 1, 0,    5, 4, 0,    // left
            6, 2, 3,    6, 7, 3     // right
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
            const GLuint CUBE_ATTR_POSITION = 1;

            glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), NULL);
            
            glBindBuffer(GL_ARRAY_BUFFER, this->vbPos);
            glEnableVertexAttribArray(CUBE_ATTR_POSITION);
            glVertexAttribPointer(CUBE_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), NULL);
           
            // advance in the buffer at each new cube drawing
            glVertexAttribDivisor(1, 1);
        }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cubes::drawCube()
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, this->posCubes.size());
    glBindVertexArray(0);
};

void Cubes::drawCubeWireframe()
{
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboWireframe);
    glDrawElementsInstanced(GL_LINES, 24, GL_UNSIGNED_INT, 0, this->posCubes.size());
    glBindVertexArray(0);
};

void Cubes::updateGPU()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vbPos); 
    glBufferData(GL_ARRAY_BUFFER, (this->posCubes.size()+1) * sizeof(glm::vec3), this->posCubes.size() > 0 ? &this->posCubes[0] : nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

int Cubes::findCube(glm::vec3 position)
{
    for(size_t j = 0; j < posCubes.size(); j++)
    {
        if(glm::length(position - posCubes[j]) < 0.1f)
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
        int lastIndex = posCubes.size() - 1;
        std::swap(posCubes[index], posCubes[lastIndex]);
        this->posCubes.pop_back();

        updateGPU();
    }
};

void Cubes::addCube(glm::vec3 position)
{
    removeCube(position);
    this->posCubes.push_back(position);
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

void Cubes::deleteData()
{
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}

Cubes::~Cubes()
{
    delete this;
};