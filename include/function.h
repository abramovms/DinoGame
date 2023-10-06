#include "Classes.h"

void Time_st(bool life, std::vector<Cloud>& cloud, std::vector<Pterodactyl>& pterodactyl, std::vector<Cactus>& cactus, float time, float &timeCloud, float &ptTime, int &icloud, int &ipt, float &timeCt, int &cti, Cloud &c, Pterodactyl &p, Cactus &ct);

void update_st(std::vector<Cloud>& cloud, std::vector<Pterodactyl>& pterodactyl, std::vector<Cactus>& cactus, float time, Way &way, Player& dino, NScore *ns, Game_Over &end);

void windowdraw_st(RenderWindow &window, RectangleShape& rectangle, Way& way, std::vector<Cloud>& cloud, std::vector<Pterodactyl>& pterodactyl, std::vector<Cactus>& cactus, Player& dino, NScore *ns, Game_Over &end);

void restart_st(std::vector<Cloud>& cloud, std::vector<Pterodactyl>& pterodactyl, std::vector<Cactus>& cactus, float& timeCloud, int& icloud, float& ptTime, int& ipt, float& timeCt, int& cti, Player& dino);