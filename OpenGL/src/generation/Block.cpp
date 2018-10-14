#include "Block.h"
#include <glm\glm.hpp>

glm::vec2 typeToTex(side s, blockType t) {

#pragma region Generic Blocks
	if (t == blockType::Grass) {
		if (s == side::Left || s == side::Right || s == side::Front || s == side::Back) {
			return glm::vec2(3, 0);
		}
		if (s == side::Top) {
			return glm::vec2(0, 0);
		}
		if (s == side::Bottom) {
			return glm::vec2(2, 0);
		}
	}
	if (t == blockType::Snow) {
		if (s == side::Left || s == side::Right || s == side::Front || s == side::Back) {
			return glm::vec2(4, 4);
		}
		if (s == side::Top) {
			return glm::vec2(8, 2);
		}
		if (s == side::Bottom) {
			return glm::vec2(2, 0);
		}
	}

	if (t == blockType::Sand) {
		return glm::vec2(2, 1);
	}

	if (t == blockType::Dirt) {
		return glm::vec2(2, 0);
	}

	if (t == blockType::Stone) {
		return glm::vec2(1, 0);
	}
#pragma endregion

#pragma region Trees
	if (t == blockType::OakLog) {
		if (s == side::Left || s == side::Right || s == side::Front || s == side::Back) {
			return glm::vec2(4, 1);
		}
		if (s == side::Top || s == side::Bottom) {
			return glm::vec2(5, 1);
		}
	}

	if (t == blockType::OakLeaf) {
		return glm::vec2(5, 3);
	}

	if (t == blockType::SpruceLog) {
		if (s == side::Left || s == side::Right || s == side::Front || s == side::Back) {
			return glm::vec2(4, 7);
		}
		if (s == side::Top || s == side::Bottom) {
			return glm::vec2(5, 1);
		}
	}

	if (t == blockType::SpruceLeaf) {
		return glm::vec2(5, 8);
	}

	if (t == blockType::BirchLog) {
		if (s == side::Left || s == side::Right || s == side::Front || s == side::Back) {
			return glm::vec2(5, 7);
		}
		if (s == side::Top || s == side::Bottom) {
			return glm::vec2(5, 1);
		}
	}

	if (t == blockType::BirchLeaf) {
		return glm::vec2(5, 3);
	}

#pragma endregion

#pragma region Plants
	if (t == blockType::Cactus) {
		if (s == side::Left || s == side::Right || s == side::Front || s == side::Back) {
			return glm::vec2(6, 4);
		}
		if (s == side::Top) {
			return glm::vec2(5, 4);
		}
		if (s == side::Bottom) {
			return glm::vec2(7, 4);
		}
	}
#pragma endregion

	return glm::vec2(8, 0);
}

Block::Block(int x, int y, int z, blockType type) : x(x), y(y), z(z), type(type) {
	for (int i = 0; i < 6; i++) {
		glm::vec2 t = typeToTex((side)i, type);
		BlockPlane p((side)i, t.x, t.y);
		Planes.insert(std::pair<side, BlockPlane>((side)i, p));
	}
}



