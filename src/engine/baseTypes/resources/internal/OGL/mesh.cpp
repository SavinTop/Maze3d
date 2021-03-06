#include "mesh.hpp"

namespace res::ogl{

Mesh::Mesh(){}

Mesh::Mesh(const Containers::Mesh& meshContainer) {
    setParams(meshContainer);
}

void Mesh::setParams(const Containers::Mesh& meshContainer) {
    mesh = meshContainer;
}

void Mesh::draw(oglw::Shader& program){
    unsigned int diffuseNr = 1;
    unsigned int heightNr = 1;
    unsigned int normalNr = 1;
    for(unsigned int i = 0; i < mesh.textures.size(); i++)
    {
        if(!mesh.textures[i].get()) continue;
        std::string number;
        std::string name;
        
        if(mesh.textures[i]->getType() == TextureType::Diffuse)
        {
            number = std::to_string(diffuseNr++);
            name = "texture_diffuse";
        }
        else if(mesh.textures[i]->getType() == TextureType::Height)
        {
            number = std::to_string(heightNr++);
            name = "texture_height";
        }
        else if(mesh.textures[i]->getType() == TextureType::Normal)
        {
            number = std::to_string(normalNr++);
            name = "texture_normal";
        }
        
        int id = program.getUniformLocation((name + number));
        if(id>0)
        {
            glUniform1i(id, i);
            mesh.textures[i]->bind(i);
        }
        
    }

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::drawWithoutTextures() 
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::InitializeSubResources(std::string groupName) 
{

}

void Mesh::load(){
    if(loaded) return;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Containers::Vertex), &mesh.vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), 
                 &mesh.indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Containers::Vertex), (void*)0);

    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Containers::Vertex), (void*)offsetof(Containers::Vertex, normal));
    
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Containers::Vertex), (void*)offsetof(Containers::Vertex, texCoords));

    glEnableVertexAttribArray(3);	
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Containers::Vertex), (void*)offsetof(Containers::Vertex, Tangent));
    
    glEnableVertexAttribArray(4);	
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Containers::Vertex), (void*)offsetof(Containers::Vertex, Bitangent));

    glBindVertexArray(0);
    
    loaded = true;
}

void Mesh::unload(){
    if(!loaded) return;
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    loaded = false;
}

}