#include "function.h"

bool start = false;
float ds = 0.4;
float speed = 0;
float score = 0;
float record = 0;
int index = 1;

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(1280, 720), "Dino");
	RectangleShape rectangle(Vector2f(1280, 720));

	Player dino("Image/dino.png", 230, 613, 230, 646, 84, 87, 112, 54);
	Way way("Image/dino.png", 230, 690, 1, 680, 90, 18, 1280, 25);
	std::vector<Cloud> cloud;
	Cloud c;
	std::vector<Pterodactyl> pterodactyl;
	Pterodactyl p;
	std::vector<Cactus> cactus;
	Cactus ct;

	Game_Over end("Image/dino.png", 450, 300, 382, 77);

	NScore ns[11] = {
		NScore("Image/dino.png", 1000, 20, 19, 21),
		NScore("Image/dino.png", 1023, 20, 19, 21),
		NScore("Image/dino.png", 1046, 20, 19, 21),
		NScore("Image/dino.png", 1069, 20, 19, 21),
		NScore("Image/dino.png", 1092, 20, 19, 21),
		NScore("Image/dino.png", 812, 20, 39, 21),
		NScore("Image/dino.png", 865, 20, 19, 21),
		NScore("Image/dino.png", 888, 20, 19, 21),
		NScore("Image/dino.png", 911, 20, 19, 21),
		NScore("Image/dino.png", 934, 20, 19, 21),
		NScore("Image/dino.png", 957, 20, 19, 21)
	};

	Clock clock;

	float timeCloud = 0;
	int icloud = 0;

	float ptTime = 0;
	int ipt = 30;

	float timeCt = 0;
	int cti = 0;

	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;
		if (dino.Get_life() && start)score += 0.005;

		timeCloud += 0.005 * time;
		ptTime += 0.005 * time;
		timeCt += 0.005 * time;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		Time_st(dino.Get_life(), cloud, pterodactyl, cactus, time, timeCloud, ptTime, icloud, ipt, timeCt, cti, c, p, ct);

		update_st(cloud, pterodactyl, cactus, time, way, dino, ns, end);

		window.clear();

		windowdraw_st(window, rectangle, way, cloud, pterodactyl, cactus, dino, ns, end);

		restart_st(cloud, pterodactyl, cactus, timeCloud, icloud, ptTime, ipt, timeCt, cti, dino);

		window.display();
	}
	return 0;
}