#include "Classes.h"

extern bool start;
extern float speed;
extern float ds;

Entity::Entity(String file, int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2) {
	this->x = x1; this->y = y1;
	this->w = w1; this->h = h1;
	this->x1 = x1; this->y1 = y1;
	this->x2 = x2; this->y2 = y2;
	this->w1 = w1; this->h1 = h1;
	this->w2 = w2; this->h2 = h2;
	name = file;
	image.loadFromFile(name);
	image.createMaskFromColor(Color::White);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

float Entity::GetX() {
	return x;
}

float Entity::GetY() {
	return y;
}

float Entity::GetW() {
	return w;
}

float Entity::GetH() {
	return h;
}

Sprite& Entity::GetSprite() {
	return sprite;
}

Player::Player(String file, int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2) : Entity::Entity(file, x1, y1, x2, y2, w1, h1, w2, h2) {
	dy = 0;
	state = stay;
	x = x1; y = y1;
	w = w1; h = h1;
	CurrentFrame = 0;
	life = true; OnGround = true;
	sprite.setTextureRect(IntRect(1340, 6, w, h));
	sprite.setPosition(x, y);
}

void Player::update(float time) {
	control(time);
	if (life) {
		y += dy * time;
		check(time);
	}
	Animation(time);
	sprite.setPosition(x, y);
}

void Player::control(float time) {
	if (!life) {
		if (state == sit) {
			y -= 30;
		}
		state = dead;
		w = w1; h = h1;
		return;
	}
	if (!start) {
		state = jump;
		if ((Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Up))) {
			start = true;
			dy = -0.6;
			OnGround = false;
		}
		return;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Up)) && OnGround) {
		dy = -0.7;
		OnGround = false;
		state = jump;
		x = x1; y = y1;
		w = w1; h = h1;
		return;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Down))) {
		state = sit;
		w = w2; h = h2;
		if (OnGround) {
			x = x2;
			y = y2;
		}
		else {
			dy += 0.005 * time;
		}
		return;
	}
	w = w1; h = h1;
	if (OnGround) {
		state = stay;
		x = x1;
		y = y1;
	}
	else {
		state = jump;
	}

}

void Player::check(float time) {
	if (y + h > 700) {
		OnGround = true;
		y -= dy * time;
	}
	if (!OnGround) {
		dy += 0.0015 * time;
	}
}

void Player::Animation(float time) {
	switch (state) {
	case stay:
		CurrentFrame += 0.005 * time;
		if (CurrentFrame >= 2) CurrentFrame -= 2;
		sprite.setTextureRect(IntRect(1517 + ((int)CurrentFrame) * (w + 5), 6, w, h));
		break;
	case sit:
		CurrentFrame += 0.005 * time;
		if (CurrentFrame >= 2) CurrentFrame -= 2;
		sprite.setTextureRect(IntRect(1870 + (int)CurrentFrame * (w + 7.5), 39, w, h));
		break;
	case jump:
		sprite.setTextureRect(IntRect(1340, 6, w, h));
		break;
	case dead:
		sprite.setTextureRect(IntRect(1691, 6, w, h));
	}
}

bool Player::Get_life() {
	return life;
}

bool& Player::Set_Life() {
	return life;
}

Way::Way(String file, int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2) : Entity::Entity(file, x1, y1, x2, y2, w1, h1, w2, h2) {
	sprite.setTextureRect(IntRect(75, 79, w, h));
	sprite.setPosition(x, y);
}

void Way::update(float time) {
	if (start) {
		Animation(time);
		sprite.setPosition(x, y);
	}
}

void Way::Animation(float time) {
	x = x2; y = y2;
	w = w2; h = h2;
	sprite.setTextureRect(IntRect((1 + (int)speed) % 1104, 104, w, h));
}

Cloud::Cloud() : Entity::Entity("Image/dino.png", 1280, 90, 1280, 180, 95, 30, 95, 30) {
	check_new = true;
	sprite.setTextureRect(IntRect(165, 2, w, h));
}

void Cloud::update(float time) {
	if (check_new) Animation(time);
	x -= (0.1) * time;
	sprite.setPosition(x, y);
}

void Cloud::Animation(float time) {
	int i = rand() % 2;
	if (i) {
		x = x2;
		y = y2;
	}
	else {
		x = x1;
		y = y1;
	}
	check_new = false;
}

Pterodactyl::Pterodactyl() : Entity::Entity("Image/dino.png", 1280, 350, 1280, 480, 87, 72, 86, 53) {
	x3 = 1280; y3 = 570;
	CurrentFrame = 0;
	check_new = true;
	sprite.setTextureRect(IntRect(264, 6, w, h));
}

void Pterodactyl::update(float time) {
	Animation(time);
	x -= (ds + 0.1) * time;
	sprite.setPosition(x, y);
}

void Pterodactyl::Animation(float time) {
	if (check_new) {
		int i = 1 + rand() % 3;
		switch (i) {
		case 1:
			x = x1;
			y = y1;
			break;
		case 2:
			x = x2;
			y = y2;
			break;
		case 3:
			x = x3;
			y = y3;
		}
		check_new = false;
	}
	else {
		CurrentFrame += 0.005 * time;
		if (CurrentFrame > 2) CurrentFrame -= 2;
		if (CurrentFrame >= 1) {
			w = w2;
			h = h2;
		}
		else {
			w = w1;
			h = h1;
		}
		sprite.setTextureRect(IntRect(264 + (int)CurrentFrame * (w + 2.5), 6, w, h));
	}
}

bool Pterodactyl::CheckCollision(float X, float Y, float W, float H) {
	for (int i = X + 20; i < X + W - 10; i++) {
		if (i >= x && i <= x + w - 10 && Y + 15 <= y + h && Y + 15 >= y) {
			return false;
		}
		if (i >= x && i <= x + w - 10 && Y + H - 5 <= y + h && Y + H - 5 >= y + 10) {
			return false;
		}
	}
	for (int i = Y; i < Y + H; i++) {
		if (i - Y <= 32) {
			if (X + W - 10 >= x + 10 && X + W - 10 <= x + w && i <= y + h && i >= y) {
				return false;
			}
		}
		else if (X + W - 40 >= x + 20 && X + W - 10 <= x + w - 10 && i <= y + h && i >= y) {
			return false;
		}
	}
	return true;
}

Cactus::Cactus() : Entity::Entity("Image/dino.png", 1280, 610, 1280, 639, 46, 98, 95, 98) {
	w3 = 98, h3 = 98;
	w4 = 32, h4 = 68;
	w5 = 66, h5 = 68;
	w6 = 100, h6 = 68;
	check_new = true;
	sprite.setTextureRect(IntRect(654, 3, w, h));
}

void Cactus::update(float time) {
	if (check_new) Animation(time);
	x -= ds * time;
	sprite.setPosition(x, y);
}

void Cactus::Animation(float time) {
	int i = 1 + rand() % 6;
	switch (i) {
	case 1:
		w = w1; h = h1;
		x = x1; y = y1;
		sprite.setTextureRect(IntRect(654, 3, w, h));
		break;
	case 2:
		w = w2; h = h2;
		x = x1; y = y1;
		sprite.setTextureRect(IntRect(654, 3, w, h));
		break;
	case 3:
		w = w3; h = h3;
		x = x1; y = y1;
		sprite.setTextureRect(IntRect(852, 3, w, h));
		break;
	case 4:
		w = w4; h = h4;
		x = x2; y = y2;
		sprite.setTextureRect(IntRect(447, 4, w, h));
		break;
	case 5:
		w = w5; h = h5;
		x = x2; y = y2;
		sprite.setTextureRect(IntRect(447, 4, w, h));
		break;
	case 6:
		w = w6; h = h6;
		x = x2; y = y2;
		sprite.setTextureRect(IntRect(550, 4, w, h));
	}
	check_new = false;
}

bool Cactus::CheckCollision(float X, float Y, float W, float H) {
	for (int i = Y; i < Y + H - 15; i++) {
		if (i - Y <= 32) {
			if (X + W - 10 >= x && X + W - 10 <= x + w && i <= y + h && i >= y) {
				return false;
			}
		}
		else if (X + W - 40 >= x + 20 && X + W - 10 <= x + w - 10 && i <= y + h && i >= y) {
			return false;
		}
	}
	
	for (int i = X + 20; i < X + W - 30; i++) {
		if (i >= x && i <= x + w && Y + H - 5 <= y + h && Y + H - 5 >= y) {
			return false;
		}
	}

	return true;
}

NScore::NScore(String file, int x, int y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	name = file;
	image.loadFromFile(name);
	image.createMaskFromColor(Color::White);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

void NScore::update(int index) {
	switch (index) {
	case 0:
		sprite.setTextureRect(IntRect(953, 2, w, h));
		break;
	case 1:
		sprite.setTextureRect(IntRect(974, 2, w, h));
		break;
	case 2:
		sprite.setTextureRect(IntRect(993, 2, w, h));
		break;
	case 3:
		sprite.setTextureRect(IntRect(1014, 2, w, h));
		break;
	case 4:
		sprite.setTextureRect(IntRect(1034, 2, w, h));
		break;
	case 5:
		sprite.setTextureRect(IntRect(1053, 2, w, h));
		break;
	case 6:
		sprite.setTextureRect(IntRect(1074, 2, w, h));
		break;
	case 7:
		sprite.setTextureRect(IntRect(1093, 2, w, h));
		break;
	case 8:
		sprite.setTextureRect(IntRect(1113, 2, w, h));
		break;
	case 9:
		sprite.setTextureRect(IntRect(1133, 2, w, h));
		break;
	case -1:
		sprite.setTextureRect(IntRect(1153, 2, w, h));
	}
	sprite.setPosition(x, y);
}

Game_Over::Game_Over(String file, int x, int y, float w, float h) : NScore::NScore(file, x, y, w, h) {
	sprite.setTextureRect(IntRect(954, 27, w, h));
}

void Game_Over::update() {
	sprite.setPosition(x, y);
}