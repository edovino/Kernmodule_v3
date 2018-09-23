#include "Block.h"
#include <glm\glm.hpp>

glm::vec2 typeToTex(side s, blockType t) {

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

	if (t == blockType::Log) {
		if (s == side::Left || s == side::Right || s == side::Front || s == side::Back) {
			return glm::vec2(4, 1);
		}
		if (s == side::Top || s == side::Bottom) {
			return glm::vec2(5, 1);
		}
	}

	if (t == blockType::Leaf) {

			return glm::vec2(5,3);
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

	return glm::vec2(8, 0);

}

Block::Block(int x, int y, int z, blockType type) : x(x), y(y), z(z)
{
	for (int i = 0; i < 6; i++) {
		glm::vec2 t = typeToTex((side)i, type);
		BlockPlane p((side)i, t.x, t.y);
		Planes.insert(std::pair<side, BlockPlane>((side)i, p));
	}
}


