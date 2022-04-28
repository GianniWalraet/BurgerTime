#pragma once
#include "Base/Singleton.h"


class Texture2D;
class Font;
class SoundEffect;
class SoundStream;
class ResourceManager final : public Singleton<ResourceManager>
{
public:
	void Init(const std::string& data);
	std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
	std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
	std::shared_ptr<SoundEffect> LoadSoundEffect(const std::string& file);
	std::shared_ptr<SoundStream> LoadSoundStream(const std::string& file);
private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;
	std::string m_DataPath;
};

