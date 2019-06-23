#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "mygl.h"

unsigned int CreateTexture(const char *image_path, int *width, int *height, unsigned int format)
{
	unsigned int texture=0;
	glGenTextures(1, &texture); // object
	glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);
	int nrChannels;
	unsigned char *data = stbi_load(image_path, width, height, &nrChannels, 0);
	if (data) 
	{
		// 第一个GL_RGB是生成纹理的格式，第二个format是资源像素点的格式；
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *width, *height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D); // mipmap
		std::cout << "image '" << image_path << "' " << " w:" << *width << " h:" << *height << std::endl;
	}
	else {
		std::cout << "Failed to load image " << image_path << std::endl;
	}	
	stbi_image_free(data);
	return texture;
}