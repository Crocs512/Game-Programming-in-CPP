#include "TileMapComponent.h"
#include "Actor.h"
#include <fstream>
#include <string>

TileMapComponent::TileMapComponent(Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder),
	unit_(1.0f)
{
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	int width = GetTexWidth();
	int height = GetTexHeight();

	// 纹理根据unit_块大小进行分割
	int cols = width / unit_;
	int rows = height / unit_;

	// 选取的unit_块实际放置的位置
	int dstX = 0;
	int dstY = 0;

	for (const auto& r : mapData_)
	{
		dstX = 0;

		for (auto c : r)
		{
			SDL_Rect srcrect, dstrect;

			int srcX = c % cols;
			int srcY = c / cols;

			srcrect.x = srcX * unit_;
			srcrect.y = srcY * unit_;
			srcrect.w = unit_;
			srcrect.h = unit_;

			dstrect.x = dstX * unit_;
			dstrect.y = dstY * unit_;
			dstrect.w = unit_;
			dstrect.h = unit_;

			++dstX;

			SDL_RenderCopyEx(renderer, mTexture, &srcrect, &dstrect, 0.0f, nullptr, SDL_FLIP_NONE);
		}

		++dstY;
	}
}

void TileMapComponent::readMapData(const std::string& filename)
{
	std::ifstream fin(filename);

	if (fin.fail())
		return;

	while (true)
	{
		std::string line;
		std::getline(fin, line);

		if (fin.eof())
			break;

		size_t start = 0;
		size_t end = 0;

		std::vector<int> row;
		bool done = false;

		while (!done)
		{
			end = line.find(',', start);

			if (end != std::string::npos)
			{
				row.push_back(std::stoi(line.substr(start, end - start)));
				start = end + 1;
			}
			else
			{
				row.push_back(std::stoi(line.substr(start)));
				mapData_.emplace_back(row);
				done = true;
			}
		}
	}

	fin.close();
}

void TileMapComponent::setUnit(int unit)
{
	unit_ = unit;
}

int TileMapComponent::getUnit() const
{
	return unit_;
}