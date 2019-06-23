#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixPer;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//float y = TexCoord.y;
	//vec2 face_coord = vec2(TexCoord.x, y);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixPer);
}