layout(location = 0) attribute vec4 Position;
layout(location = 1) attribute vec3 aNormal;

varying vec3 outNormal;
varying vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
   gl_Position = projection * view * model * Position;
   outNormal = aNormal;
   fragPos = vec3(model * Position);

}