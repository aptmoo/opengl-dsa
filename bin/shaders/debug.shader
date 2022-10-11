// debug.shader: debug and testing shader

#shader vertex
#version 330 core

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 uvcoord;

uniform mat4 u_ViewProj;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main()
{
    v_TexCoord = uvcoord;
    gl_Position = u_ViewProj * u_Transform * vec4(vertexPosition, 1.0, 1.0);
}

#shader fragment
#version 330 core

in vec2 v_TexCoord;

out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texcolor = texture(u_Texture, v_TexCoord) * u_Color;
    color = texcolor;
}