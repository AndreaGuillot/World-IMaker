#include "../include/cube.hpp"

using namespace glimac;

Cube::Cube(FilePath applicationPath)
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

    // --- INDEX BUFFER
    glGenBuffers(1, &this->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);

        // Index table
        std::vector<uint32_t> index = {
            0, 1, 2,    2, 3, 0,    // front
            4, 5, 6,    6, 7, 4,    // back
            0, 4, 3,    3, 7, 4,    // top
            1, 2, 5,    2, 6, 5,    // bottom
            0, 1, 5,    5, 4, 0,    // left
            3, 2, 6,    6, 7, 3     // right
        };


    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (index.size()+1) * sizeof(uint32_t), index.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // --- VERTEX ARRAY
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);

        // Activation - Specification
        {
            const GLuint VERTEX_ATTR_POSITION = 0;
            const GLuint VERTEX_ATTR_NORMAL = 1;
            const GLuint VERTEX_ATTR_TEXCOORDS = 2;

            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
            glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
            glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
        }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cube::drawCube()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
};

void Cube::deleteData()
{
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}

Cube::~Cube()
{
    delete this;
};