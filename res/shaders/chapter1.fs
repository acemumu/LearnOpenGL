#version 330 core
in vec3 vcolor;
out vec4 fragColor; 
void main() 
{ 
	fragColor = vec4(vcolor, 1.0f); 

}