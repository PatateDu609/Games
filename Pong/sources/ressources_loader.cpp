#include "../headers/ressources_loader.h"
#include <algorithm>
#include <filesystem>

std::string Ressources::fonts = ".";
std::string Ressources::textures = ".";
std::string Ressources::shaders = ".";

std::string Ressources::loadTextures(std::string name)
{
	return textures + "/" + name;
}

std::string Ressources::loadShaders(std::string name)
{
	return shaders + "/" + name;
}

std::string Ressources::loadFonts(std::string name)
{
	return fonts + "/" + name;
}

std::string Ressources::load(std::string name)
{
	std::string extension = std::filesystem::path(name).extension().string();

	if (extension == ".vert" || extension == ".frag")
		return loadShaders(name);
	else if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
		return loadTextures(name);
	else if (extension == ".ttf")
		return loadFonts(name);
	return name;
}

void Ressources::setPrefix(Type type, std::string folder)
{
	std::replace(folder.begin(), folder.end(), '\\', '/');
	switch (type)
	{
	case Type::SHADERS: shaders = folder; break;
	case Type::FONTS: fonts = folder; break;
	case Type::TEXTURES: textures = folder; break;
	}
}