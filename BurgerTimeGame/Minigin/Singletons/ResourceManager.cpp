#include "MiniginPCH.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Graphics/Texture2D.h"
#include "Graphics/Font.h"
#include "Sound/SoundEffect.h"
#include "Sound/SoundStream.h"

void ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}

	// load support for audio

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		throw std::runtime_error(std::string("error when calling Mix_OpenAudio:") + Mix_GetError());
	}

}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + file, size);
}

std::shared_ptr<SoundEffect> ResourceManager::LoadSoundEffect(const std::string& file)
{
	return std::make_shared<SoundEffect>(m_DataPath + file);
}

std::shared_ptr<SoundStream> ResourceManager::LoadSoundStream(const std::string& file)
{
	return std::make_shared<SoundStream>(m_DataPath + file);
}
