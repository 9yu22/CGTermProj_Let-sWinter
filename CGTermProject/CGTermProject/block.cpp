
#include "block.h"

Block::Block()
{
    float vertexData[] = {
        // cube
        // front
        -1.f, 1.f, -1.f, 0.f, 0.f, -1.f,    1.0, 1.0,
        1.f, -1.f, -1.f, 0.f, 0.f, -1.f,    0.0, 0.0,
        -1.f, -1.f, -1.f, 0.f, 0.f, -1.f,   1.0, 0.0,

        -1.f, 1.f, -1.f, 0.f, 0.f, -1.f,    1.0, 1.0,
        1.f, 1.f, -1.f, 0.f, 0.f, -1.f,     0.0, 1.0,
        1.f, -1.f, -1.f, 0.f, 0.f, -1.f,    0.0, 0.0,

        // back
        1.f, 1.f, 1.f, 0.f, 0.f, 1.f,       1.0, 1.0,
        -1.f, -1.f, 1.f, 0.f, 0.f, 1.f,     0.0, 0.0,
        1.f, -1.f, 1.f, 0.f, 0.f, 1.f,      1.0, 0.0,

        1.f, 1.f, 1.f, 0.f, 0.f, 1.f,       1.0, 1.0,
        -1.f, 1.f, 1.f, 0.f, 0.f, 1.f,      0.0, 1.0,
        -1.f, -1.f, 1.f, 0.f, 0.f, 1.f,     0.0, 0.0,

        // left
        -1.f, 1.f, 1.f, -1.f, 0.f, 0.f,     1.0, 1.0,
        -1.f, -1.f, -1.f, -1.f, 0.f, 0.f,   0.0, 0.0,
        -1.f, -1.f, 1.f, -1.f, 0.f, 0.f,    1.0, 0.0,

        -1.f, 1.f, 1.f, -1.f, 0.f, 0.f,     1.0, 1.0,
        -1.f, 1.f, -1.f, -1.f, 0.f, 0.f,    0.0, 1.0,
        -1.f, -1.f, -1.f, -1.f, 0.f, 0.f,   0.0, 0.0,

        // right
        1.f, 1.f, -1.f, 1.f, 0.f, 0.f,      1.0, 1.0,
        1.f, -1.f, 1.f, 1.f, 0.f, 0.f,      0.0, 0.0,
        1.f, -1.f, -1.f, 1.f, 0.f, 0.f,     1.0, 0.0,

        1.f, 1.f, -1.f, 1.f, 0.f, 0.f,      1.0, 1.0,
        1.f, 1.f, 1.f, 1.f, 0.f, 0.f,       0.0, 1.0,
        1.f, -1.f, 1.f, 1.f, 0.f, 0.f,      0.0, 0.0,

        // top
        -1.f, 1.f, 1.f, 0.f, 1.f, 0.f,      1.0, 1.0,
        1.f, 1.f, -1.f, 0.f, 1.f, 0.f,      0.0, 0.0,
        -1.f, 1.f, -1.f, 0.f, 1.f, 0.f,     1.0, 0.0,

        -1.f, 1.f, 1.f, 0.f, 1.f, 0.f,      1.0, 1.0,
        1.f, 1.f, 1.f, 0.f, 1.f, 0.f,       0.0, 1.0,
        1.f, 1.f, -1.f, 0.f, 1.f, 0.f,      0.0, 0.0,

        // bottom
        -1.f, -1.f, -1.f, 0.f, -1.f, 0.f,   1.0, 1.0,
        1.f, -1.f, 1.f, 0.f, -1.f, 0.f,     0.0, 0.0,
        -1.f, -1.f, 1.f, 0.f, -1.f, 0.f,    1.0, 0.0,

        -1.f, -1.f, -1.f, 0.f, -1.f, 0.f,   1.0, 1.0,
        1.f, -1.f, -1.f, 0.f, -1.f, 0.f,    0.0, 1.0,
        1.f, -1.f, 1.f, 0.f, -1.f, 0.f,     0.0, 0.0, };

    vtSize = 36;

    for (int i = 0; i < vtSize; i++) {
        vertices.push_back(glm::vec3(vertexData[i * 8], vertexData[i * 8 + 1], vertexData[i * 8 + 2]));
        normals.push_back(glm::vec3(vertexData[i * 8 + 3], vertexData[i * 8 + 4], vertexData[i * 8 + 5]));
        uvs.push_back(glm::vec2(vertexData[i * 8 + 6], vertexData[i * 8 + 7]));
        colors.push_back(glm::vec3(0.f, 0.f, 0.f));
    }
    //std::cout << "v: " << vertices.size() << std::endl;

    pos = glm::vec3(0.f, -2.f, 0.f);
    scale = glm::vec3(1.f, 1.f, 1.f);
}

void Block::render(GLuint shaderProgramID)
{
    glUseProgram(shaderProgramID);

    model = glm::mat4(1.0);
    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rotate.y), glm::vec3(0, 1, 0));
    model = glm::scale(model, scale);
    //glm::vec3 bottomLeftOffset = glm::vec3(-11.0, -10.0, 17.0);
    //model = glm::translate(model, bottomLeftOffset);

    //model = glm::mat4(1.0);
    //model = glm::translate(model, glm::vec3(moveLeftRight, moveUpDown, moveBackForth));
    //model = glm::rotate(model, rotationAngle, glm::vec3(0, 1, 0));
    //glm::vec3 bottomLeftOffset = glm::vec3(-11.0, -10.0, 17.0);
    //model = glm::translate(model, bottomLeftOffset);
    //model = glm::scale(model, scale);


    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(vao);
    //glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, vtSize);
}

void Block::initBuffer()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    //glGenBuffers(1, &tbo);
    //glBindBuffer(GL_ARRAY_BUFFER, tbo);
    //glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(1);

    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
}

void Block::initTexture()
{
    //glGenTextures(1, &texture);
    //glBindTexture(GL_TEXTURE_2D, texture);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //int width, height, nrChannels;
    ////unsigned char* data = stbi_load("LEGO_Texture.jpg", &width, &height, &nrChannels, 0);
    //unsigned char* data = stbi_load("minifig.png", &width, &height, &nrChannels, 0);

    //// cout << "check image load" << endl;
    //// cout << width << " " << height << " " << nrChannels << endl;

    //if (data) {
    //    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //    // glGenerateMipmap(GL_TEXTURE_2D);
    //}
    //else {
    //    std::cout << "Failed to load texture" << std::endl;
    //}
    //stbi_image_free(data);
}
