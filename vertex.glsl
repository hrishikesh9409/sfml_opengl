#version 410 core
 
//  vec3[3] vertices = vec3[3](
//      vec3(-0.5,-0.5,0.0),
//      vec3(0.0,0.5,0.0),
//      vec3(0.5,-0.5,0.0)
//  );

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

out vec3 vertexColor;

 void main(){
     //vec3 pos = vertices[gl_VertexID];
     vertexColor = col;
     gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
 }