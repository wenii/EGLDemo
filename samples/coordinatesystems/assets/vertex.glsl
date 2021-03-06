layout(location = 0) attribute vec4 Position;
layout(location = 1) attribute vec2 texcoord;
varying vec2 otexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
   otexcoord = vec2(texcoord.x, 1.0 - texcoord.y);
   gl_Position = projection * view * model * Position;

}