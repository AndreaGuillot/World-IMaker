#include "../include/Map.hpp"

int  Map::findControlPoint(float x, float z){
    for(int j = 0; j < m_nbPoints; ++j)
    {
        if((glm::length(x - m_ControlPoints(j,0)) < 0.1f) && (glm::length(z - m_ControlPoints(j,1)) < 0.1f))
        {
            // find
            return j;
        }
    }
    // not find
    return -1;
}

bool Map::isControlPointExist(float x, float z){
    int index = findControlPoint(x, z);
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

void Map::removeControlPoint(float x, float z){
    int index = findControlPoint(x, z);
    if(index != -1)
    {
        // put the item to delete at the end
        std::swap(m_ControlPoints(index,0), m_ControlPoints(m_nbPoints-1,0));
        std::swap(m_ControlPoints(index,1), m_ControlPoints(m_nbPoints-1,1));
        std::swap(m_values(index), m_values(m_nbPoints-1));

        --m_nbPoints;

        m_ControlPoints.conservativeResize(m_nbPoints, 2);
        m_values.conservativeResize(m_nbPoints);

    }

    displayControlPoints();
}

void Map::addControlPoint(int x, int z, int poids){
    if(isControlPointExist((float)x, (float)z))
    {
        std::cerr << "ERREUR : Point de controle préexistant." << std::endl;
    }
    else
    {
        ++m_nbPoints;
        m_ControlPoints.conservativeResize(m_nbPoints, 2);
        m_ControlPoints(m_nbPoints-1,0)=(float)x;
        m_ControlPoints(m_nbPoints-1,1)=(float)z;

        m_values.conservativeResize(m_nbPoints);
        m_values(m_nbPoints-1) = (float)poids;

        displayControlPoints();
        
    }

}

void Map::loadWorld(Cubes &cube, glm::vec4 defaultColor){

    int defaultType = 1;

    if(m_nbPoints != 0){
        clearWorld(cube);
        m_map = getMap(m_ControlPoints, m_values);

        for(int x=0; x<WORLD_TAILLE; x++){
            for(int z=0; z<WORLD_TAILLE; z++){
                for(int y=0; y <= m_map(x, z); y++){
                    if(m_map(x,z) != 0)
                        cube.addCube(glm::vec3 (x-WORLD_TAILLE/2, y, z-WORLD_TAILLE/2), defaultColor, defaultType);
                }
            }
        }
    }
      
}

void Map::clearWorld(Cubes &cube){

    if(m_nbPoints != 0){
        for(int x=0; x<WORLD_TAILLE; x++){
            for(int z=0; z<WORLD_TAILLE; z++){
                for(int y=0; y <= m_map(x, z); y++){
                    if(m_map(x,z) != 0)
                        cube.removeCube(glm::vec3 (x-WORLD_TAILLE/2, y, z-WORLD_TAILLE/2));
                }
            }
        }
    }
    
}

void Map::displayControlPoints(){
    std::cout<<"Vos points de controle : "<<std::endl;
        for (int i=0; i<m_nbPoints; ++i){
            for(int j=0; j<2; ++j){
                std::cout<<m_ControlPoints(i,j)<<" ";
            }
            std::cout<<m_values(i)<<std::endl;
        }
        std::cout<<std::endl;
}