class Enemy
{
private:
	int moveY = 0;
	SDL_Renderer* renderer;
	int prevPosY = 0;
	int prevPosX = 0;
	double angle = 0;
	int orbitX = 0;
	int orbitY = 0;
	int creatureType;
	bool moveVector2 = true;
public:
	int  velocityX = 3;
	int	velocityY = 1;
	bool moveVector = true;
	bool active = true;
	SDL_Texture* enemyImg;
	SDL_Rect position;

	Enemy(SDL_Renderer* r, const char* imgSrc, int x, int y, int creature, int xspeed, int yspeed, bool moveVector);
	void move();
	void deactive();
	void shoot();
	~Enemy();
};

#endif //SPACE_S