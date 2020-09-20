#ifndef RESSOURCES_LOADER_H
#define RESSOURCES_LOADER_H

#include <string>

class Ressources
{
public:
	enum class Type
	{
		TEXTURES,
		FONTS,
		SHADERS
	};

	static void setPrefix(Type type, std::string folder);

	static std::string loadTextures(std::string name);
	static std::string loadShaders(std::string name);
	static std::string loadFonts(std::string name);

	static std::string load(std::string name);

private:
	static std::string textures;
	static std::string fonts;
	static std::string shaders;
};

#endif // !RESSOURCES_LOADER_H
