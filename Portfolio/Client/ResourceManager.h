#pragma once

class ResourceBase;
class Texture;
class Sprite;
class Flipbook;
class Tilemap;

class ResourceManager
{
public:
	DECLARE_SINGLE(ResourceManager)

	~ResourceManager();

public:
	void Init(fs::path resourcePath);
	void Clear();

	const fs::path& GetResourcePath() { return _resourcePath; }

	Texture* GetTexture(const wstring& key) { return _textures[key]; }
	Texture* LoadTexture(const wstring& key, const wstring& path, uint32 transparent = RGB(255, 0, 255));

	Sprite* GetSprite(const wstring& key) { return _sprites[key]; }
	Sprite* CreateSprite(const wstring& key, Texture* texture, Vec2Int pos, Vec2Int size);
	Sprite* CreateSprite(const wstring& key, Texture* texture, Vec2Int pos, Vec2Int size, Vec2Int pivot);

	Flipbook* GetFlipbook(const wstring& key) { return _flipbooks[key]; }
	Flipbook* CreateFlipbook(const wstring& key, Texture* texture, Vec2Int size, int32 start, int32 end, int32 line, float duration, bool loop);
	Flipbook* CreateFlipbook(const wstring& key, Texture* texture, Vec2Int size, Vec2Int pivot, int32 start, int32 end, int32 line, float duration, bool loop);

private:
	fs::path _resourcePath;

	unordered_map<wstring, Texture*> _textures;
	unordered_map<wstring, Sprite*> _sprites;
	unordered_map<wstring, Flipbook*> _flipbooks;
};

