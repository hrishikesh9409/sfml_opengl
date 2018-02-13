#version 410 core

in vec3 vertexColor;
out vec4 outColor;

void main(){
    outColor = vec4(vertexColor.x, vertexColor.y, vertexColor.z, 1.0);
}
