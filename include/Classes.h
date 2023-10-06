#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <iostream>
#include <cmath>
#define max(a, b) a > b ? a : b

using namespace sf;

class Entity {
public:
	Entity(String file, int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2);

	virtual void update(float time) = 0;

	virtual void Animation(float time) = 0;

	float GetX();

	float GetY();

	float GetW();

	float GetH();

	Sprite& GetSprite();
protected:
	float x, y, x1, y1, x2, y2, w, h, w1, h1, w2, h2;
	String name;
	Image image;
	Texture texture;
	Sprite sprite;
};

class Player : public Entity {
	float dy;
	float CurrentFrame;
	bool OnGround, life;
	enum {stay, jump, sit, dead} state;
public:
	Player(String file, int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2);

	void update(float time) override;

	void control(float time);

	void check(float time);

	void Animation(float time) override;

	bool Get_life();

	bool& Set_Life();
};

class Way : public Entity {
public:
	Way(String file, int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2);

	void update(float time) override;
	
	void Animation(float time) override;
};

class Cloud : public Entity {
	bool check_new;
public:
	Cloud();

	void update(float time) override;

	void Animation(float time) override;
};

class Pterodactyl : public Entity {
	float x3, y3;
	float CurrentFrame;
	bool check_new;
public:
	Pterodactyl();

	void update(float time) override;

	void Animation(float time) override;

	bool CheckCollision(float X, float Y, float W, float H);
};

class Cactus : public Entity {
	float w3, h3, w4, h4, w5, h5, w6, h6;
	bool check_new;
public:
	Cactus();

	void update(float time) override;

	void Animation(float time) override;

	bool CheckCollision(float X, float Y, float W, float H);
};

class NScore {
protected:
	int x, y;
	float w, h;
	String name;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	NScore(String file, int x, int y, float w, float h);

	void update(int index);

	Sprite Get_Sprite() {
		return sprite;
	}
};

class Game_Over : public NScore {
public:
	Game_Over(String file, int x, int y, float w, float h);

	void update();
};