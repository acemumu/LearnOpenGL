#version 330 core
in vec3 vcolor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixPer;

out vec4 fragColor; 


void main() 
{ 
	fragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixPer);
    //fragColor = vec4(vcolor, 1.0f); 
}