#version 330 core

in vec3 fPos;
in vec2 fTexture;

uniform sampler2D tex;
out vec4 fragColor;


void main()
{    
    fragColor = texture(tex , fTexture);
    //fragColor = vec4(1.0, 1.0, 1.0, 1);
}