#include "function.h"

extern bool start;
extern float ds;
extern float speed;
extern float score;
extern float record;
extern int index;

void Time_st(bool life, std::vector<Cloud>& cloud, std::vector<Pterodactyl>& pterodactyl, std::vector<Cactus>& cactus, float time, float& timeCloud, float& ptTime, int& icloud, int& ipt, float &timeCt, int &cti, Cloud &c, Pterodactyl &p, Cactus &ct) {

	if (start && life) {
		speed += ds * time;
		if (!cloud.empty()) {
			if (cloud[cloud.size() - 1].GetX() + cloud[cloud.size() - 1].GetW() <= 0) cloud.pop_back();
		}
		if (!pterodactyl.empty()) {
			if (pterodactyl[pterodactyl.size() - 1].GetX() + pterodactyl[pterodactyl.size() - 1].GetW() <= 0) pterodactyl.pop_back();
		}
		if (!cactus.empty()) {
			if (cactus[cactus.size() - 1].GetX() + cactus[cactus.size() - 1].GetW() <= 0) cactus.pop_back();
		}
	}

	if (start && timeCloud > icloud && life) {
		icloud = 20 + rand() % 6;
		timeCloud = 0;
		if (cloud.empty())
		{
			cloud.push_back(c);
		}
		else {
			cloud.emplace(cloud.begin(), c);
		}
	}

	if (start && ptTime > ipt && life && score >= 100) {
		if (timeCt + 5 >= cti) timeCt -= 7;
		ipt = 20 - 5 * ds + rand() % 6 + index;
		ptTime = 0;
		if (pterodactyl.empty()) {
			pterodactyl.push_back(p);
		}
		else {
			pterodactyl.emplace(pterodactyl.begin(), p);
		}
	}

	if (start && timeCt > cti && life) {
		if (ptTime + 9 >= ipt) ptTime -= 9;
		cti = 12 - 10 * ds + rand() % 6 + (index - 2 * ds);
		timeCt = 0;
		if (cactus.empty()) {
			cactus.push_back(ct);
		}
		else {
			cactus.emplace(cactus.begin(), ct);
		}
	}

}

void update_st(std::vector<Cloud>& cloud, std::vector<Pterodactyl>& pterodactyl, std::vector<Cactus>& cactus, float time, Way &way, Player& dino, NScore * ns, Game_Over &end) {
	if (dino.Get_life()) {
		for (int j = 0; j < cloud.size(); j++) {
			cloud[j].update(time);
		}
		for (int j = 0; j < pterodactyl.size(); j++) {
			pterodactyl[j].update(time);
			dino.Set_Life() = pterodactyl[j].CheckCollision(dino.GetX(), dino.GetY(), dino.GetW(), dino.GetH());
		}
		for (int j = 0; j < cactus.size(); j++) {
			cactus[j].update(time);
			if (dino.Get_life()) dino.Set_Life() = cactus[j].CheckCollision(dino.GetX(), dino.GetY(), dino.GetW(), dino.GetH());
		}
		way.update(time);
	}
	else end.update();
	for (int i = 0; i < 5; i++) {
		int number = score / pow(10, 4 - i);
		number %= 10;
		ns[i].update(number);
	}
	if (record > 0) {
		ns[5].update(-1);
		for (int i = 6; i < 11; i++) {
			int number = record / pow(10, 4 - (i - 6));
			number %= 10;
			ns[i].update(number);
		}
	}
	dino.update(time);

	if (score >= 100 * index) {
		index++;
		ds += 0.1;
	}
}

void windowdraw_st(RenderWindow &window, RectangleShape& rectangle, Way& way, std::vector<Cloud> &cloud, std::vector<Pterodactyl>& pterodactyl, std::vector<Cactus>& cactus, Player& dino, NScore *ns, Game_Over &end) {
	window.draw(rectangle);

	for (int j = 0; j < cloud.size(); j++) {
		window.draw(cloud[j].GetSprite());
	}

	for (int j = 0; j < pterodactyl.size(); j++) {
		window.draw(pterodactyl[j].GetSprite());
	}

	window.draw(way.GetSprite());

	for (int j = 0; j < cactus.size(); j++) {
		window.draw(cactus[j].GetSprite());
	}

	for (int i = 0; i < 5; i++) {
		window.draw(ns[i].Get_Sprite());
	}
	if (record > 0) {
		for (int i = 5; i < 11; i++) {
			window.draw(ns[i].Get_Sprite());
		}
	}
	if (!dino.Get_life()) window.draw(end.Get_Sprite());
	window.draw(dino.GetSprite());
}

void restart_st(std::vector<Cloud>& cloud, std::vector<Pterodactyl>& pterodactyl, std::vector<Cactus>& cactus, float& timeCloud, int& icloud, float& ptTime, int& ipt, float& timeCt, int& cti, Player& dino) {
	if (Keyboard::isKeyPressed(Keyboard::Space) && !dino.Get_life()) {
		dino.Set_Life() = true;
		speed = 0;
		ds = 0.4;
		cloud.clear();
		pterodactyl.clear();
		cactus.clear();
		index = 1;
		record = max(score, record);
		score = 0;
		timeCloud = icloud = ptTime = timeCt = cti = 0;
		ipt = 30;
	}
}
