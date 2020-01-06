#include "../include/Cubes.hpp"

/********************************
 *        CREATE 3D CUBE        *
 ********************************/

Cubes::Cubes()
    : m_type(1)
{
    texture = addTexture();

    //    v4----- v7
    //   /|      /|
    //  v0------v3|
    //  | |     | |
    //  | |v5---|-|v6
    //  |/      |/
    //  v1------v2

    std::vector<glm::vec3> cube_vertex = {
        glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.5f,  0.5f,  0.5f),     // front face
        glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.5f,  0.5f, -0.5f),     // back face
        glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-0.5f, -0.5f, -0.5f),     // left face
        glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.5f, -0.5f, -0.5f),     // right face
        glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.5f,  0.5f, -0.5f),     // top face
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.5f, -0.5f, -0.5f)      // bot face
    };

    glm::vec2 cube_texCoords[] = {
        glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0),     // front face
        glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1), glm::vec2(0, 0),     // back face
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),     // left face
        glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1),     // right face
        glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0),     // top face
        glm::vec2(1, 1), glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1)      // bot face
    };

    glm::vec3 cube_normals[] = {
        glm::vec3( 0,  0,  1), glm::vec3( 0,  0,  1), glm::vec3( 0,  0,  1), glm::vec3( 0,  0,  1),    // front face
        glm::vec3( 0,  0, -1), glm::vec3( 0,  0, -1), glm::vec3( 0,  0, -1), glm::vec3( 0,  0, -1),    // back face
        glm::vec3(-1,  0,  0), glm::vec3(-1,  0,  0), glm::vec3(-1,  0,  0), glm::vec3(-1,  0,  0),    // left face
        glm::vec3( 1,  0,  0), glm::vec3( 1,  0,  0), glm::vec3( 1,  0,  0), glm::vec3( 1,  0,  0),    // right face
        glm::vec3( 0,  1,  0), glm::vec3( 0,  1,  0), glm::vec3( 0,  1,  0), glm::vec3( 0,  1,  0),    // top face
        glm::vec3( 0, -1,  0), glm::vec3( 0, -1,  0), glm::vec3( 0, -1,  0), glm::vec3( 0, -1,  0)     // bot face
    };
    
    for(size_t i = 0; i < 24; ++i)
    {
        ShapeVertex vertex;
        
        vertex.texCoords = cube_texCoords[i];

        vertex.normal = cube_normals[i];

        vertex.position = cube_vertex[i];
        
        m_vertex.push_back(vertex);
    }

    // --------------------------- //

    // ------ VERTEX BUFFER ------ //

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertex.size() * sizeof(ShapeVertex), m_vertex.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &vbPos);
    glBindBuffer(GL_ARRAY_BUFFER, vbPos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &vbCol);
    glBindBuffer(GL_ARRAY_BUFFER, vbCol);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // ------ INDEX BUFFER ------- //

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        // Index table
        std::vector<uint32_t> index = {
            0,   1,  2,     0,  2,  3,      // front
            4,   5,  6,     4,  6,  7,      // back
            8,   9,  10,    8,  10, 11,     // left
            12,  13, 14,    12, 14, 15,     // right
            16,  17, 18,    16, 18, 19,     // top
            20,  21, 22,    20, 22, 23      // bot
        };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(uint32_t), index.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // -- INDEX BUFFER WIREFRAME -- //

    glGenBuffers(1, &iboWireframe);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboWireframe);

        // Index table
        std::vector<uint32_t> index_w = {
            1, 0, 3, 2, 0, 3, 1, 2,         // front
            5, 4, 7, 6, 4, 7, 5, 6,         // back
            3, 7, 0, 4,                     // top
            2, 6, 1, 5                      // bottom
        };


    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (index_w.size()+1) * sizeof(uint32_t), index_w.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // ------ VERTEX ARRAY ------- //

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);

        // Activation - Specification
        const GLuint VERTEX_ATTR_POSITION   = 0;
        const GLuint VERTEX_ATTR_NORMAL     = 1;
        const GLuint VERTEX_ATTR_TEXCOORDS  = 2;
        const GLuint CUBES_ATTR_POSITION    = 3;
        const GLuint CUBES_ATTR_COLOR       = 4;

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position));

        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal));

        glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
        glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords));

        glBindBuffer(GL_ARRAY_BUFFER, this->vbPos);
        glEnableVertexAttribArray(CUBES_ATTR_POSITION);
        glVertexAttribPointer(CUBES_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), NULL);
        // advance in the buffer at each new cube drawing
        glVertexAttribDivisor(CUBES_ATTR_POSITION, 1);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbCol);
        glEnableVertexAttribArray(CUBES_ATTR_COLOR);
        glVertexAttribPointer(CUBES_ATTR_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), NULL);
        glVertexAttribDivisor(CUBES_ATTR_COLOR, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Cubes::~Cubes()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vbPos);
    glDeleteBuffers(1, &vbCol);
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &iboWireframe);
    glDeleteVertexArrays(1, &vao);
}

void Cubes::drawCube()
{
    texture->bindTexture();
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, m_position.size());
    glBindVertexArray(0);
    texture->unbindTexture();
};

void Cubes::drawCubeWireframe()
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboWireframe);
    glDrawElementsInstanced(GL_LINES, 24, GL_UNSIGNED_INT, 0, m_position.size());
    glBindVertexArray(0);
};

void Cubes::updateGPU()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbPos); 
    glBufferData(GL_ARRAY_BUFFER, m_position.size() * sizeof(glm::vec3), m_position.size() > 0 ? &m_position[0] : nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbCol); 
    glBufferData(GL_ARRAY_BUFFER, m_color.size() * sizeof(glm::vec4), m_color.size() > 0 ? &m_color[0] : nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void Cubes::editColor(glm::vec3 position, glm::vec4 color)
{
    int index = findCube(position);
    if(index != -1)
    {
        m_color[index] = color;
    }
    updateGPU();
}  

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

bool Cubes::isCubeExist(glm::vec3 position)
{
    int index = findCube(position);
    if(index == -1)
    {
        // not find
        return false;
    } 
    else 
    {
        // find
        return true;
    }
}

void Cubes::removeCube(glm::vec3 position)
{
    int index = findCube(position);
    if(index != -1)
    {
        // put the item to delete at the end
        int lastIndexP = m_position.size() - 1;
        std::swap(m_position[index], m_position[lastIndexP]);
        m_position.pop_back();

        // put the item to delete at the end
        int lastIndexC = m_color.size() - 1;
        std::swap(m_color[index], m_color[lastIndexC]);
        m_color.pop_back();

        updateGPU();
    }
};

void Cubes::addCube(glm::vec3 position, glm::vec4 color, int type)
{
    if(isCubeExist(position))
    {
        std::cerr << "ERREUR : Impossible de créer un nouveau cube sur un cube préexistant." << std::endl;
    }
    else
    {
        m_position.push_back(position);
        m_color.push_back(color);
        m_texture.push_back(type);
        updateGPU();
    }
};

void Cubes::extrudeCube(glm::vec3 position, glm::vec4 color, int type)
{
    type = m_type;
    if (findCube(position) != -1) {
        color = getColors()[findCube(position)];
    }

    int index = 0;
    while(index != -1)
    {
        index = findCube(position);
        position.y++;
    }
    position.y--;
    addCube(position, color, type);
}

void Cubes::digCube(glm::vec3 position){
    int index = 0;
    while(index != -1)
    {
        index = findCube(position);
        position.y++;
    }
    position.y -= 2.f;
    removeCube(position);
}

void Cubes::editTexture(glm::vec3 position, int type)
{
    m_type = type;
    int index = findCube(position);
    if(index != -1)
    {   
        m_texture[index] = type;
    }
    updateGPU();
}

Texture* Cubes::addTexture()
{
    if(m_type == 1)      return new Texture("grass");
    else if(m_type == 2) return new Texture("ice");
    else if(m_type == 3) return new Texture("sand");
    else                 return new Texture("default");
}

void Cubes::saveScene(const std::string &filePath, const std::string &filename)
{
    std::ofstream file(filePath + filename);

    if(file)
    {
        file << m_position.size() << std::endl;
        for(size_t i = 0; i < m_position.size(); ++i)
        {
            file << m_position[i].x << " ";
            file << m_position[i].y << " ";
            file << m_position[i].z << " ";
            file << m_color[i].r    << " ";
            file << m_color[i].g    << " ";
            file << m_color[i].b    << " ";
            file << m_color[i].a    << std::endl;
        }
        std::cout << "Scène auvegardée !" << std::endl; 
        file.close();
    }
    else
    {
        std::cerr << "ERREUR : Impossible de créer le fichier " << filename << "." << std::endl;
    }
}

void Cubes::loadScene(const std::string &filePath, const std::string &filename)
{
    std::ifstream file(filePath + filename);

    if(file)
    {
        size_t nbCubes;
        file >> nbCubes;
        std::vector<glm::vec3> position(nbCubes);
        std::vector<glm::vec4> color(nbCubes);
        for(size_t i = 0; i < nbCubes; ++i)
        { 
            file >> position[i].x;
            file >> position[i].y;
            file >> position[i].z;
            file >> color[i].r;
            file >> color[i].g;
            file >> color[i].b;
            file >> color[i].a;
        }
        std::cout << "Scène chargée !" << std::endl; 
        file.close();
        m_position = position;
        m_color = color;
        updateGPU();
    }
    else
    {
        std::cerr << "ERREUR : Impossible d'ouvrir le fichier " << filename << "." << std::endl;
    }
}