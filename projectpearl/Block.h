#pragma once

enum BLOCK_TYPE {
	AIR,
	DIRT,
	GRASS,
	COBBLESTONE,
	GLASS,
	PLANKS
};

class Block {
public:
	int id;
	char type;
	int texture;
	bool solid;
	bool visible;
	Block(int id, int texture, char type, bool solid, bool visible) {
		this->id = id;
		this->texture = texture;
		this->type = type;
		this->solid = solid;
		this->visible = visible;
	};
	Block() {
		this->id = 0;
		this->texture = 0;
		this->type = AIR;
		this->solid = false;
		this->visible = false;
	};
};