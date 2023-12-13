#include "stdafx.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "character.h"

character::character()
{
    vtSize = objReader.loadObj("minifigure.obj");
    vertices.resize(objReader.out_vertices.size());
    normals.resize(objReader.out_normals.size());
    uvs.resize(objReader.out_uvs.size());
    for (int i = 0; i < objReader.out_vertices.size(); i++)
    {
        vertices[i] = objReader.out_vertices[i];
        normals[i] = objReader.out_normals[i];
        uvs[i] = objReader.out_uvs[i];
    }

    scale = glm::vec3(0.3, 0.3, 0.3);
}

void character::render(GLuint ID)
{
    glUseProgram(ID);

    model = glm::mat4(1.0);
    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rotate.y), glm::vec3(0, 1, 0));
    model = glm::scale(model, scale);
    glm::vec3 bottomLeftOffset = glm::vec3(-11.0, -10.0, 17.0); 
    model = glm::translate(model, bottomLeftOffset);

    //model = glm::mat4(1.0);
    //model = glm::translate(model, glm::vec3(moveLeftRight, moveUpDown, moveBackForth));
    //model = glm::rotate(model, rotationAngle, glm::vec3(0, 1, 0));
    //glm::vec3 bottomLeftOffset = glm::vec3(-11.0, -10.0, 17.0);
    //model = glm::translate(model, bottomLeftOffset);
    //model = glm::scale(model, scale);


    glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, vtSize);
}

void character::initBuffer()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
}

void character::initTexture()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    //unsigned char* data = stbi_load("LEGO_Texture.jpg", &width, &height, &nrChannels, 0);
    unsigned char* data = stbi_load("minifig.png", &width, &height, &nrChannels, 0);

    // cout << "check image load" << endl;
    // cout << width << " " << height << " " << nrChannels << endl;

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}