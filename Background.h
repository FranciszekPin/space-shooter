#pragma once

class Background {
private:
	static int scrollingOffset;
public:
	Background();
	Background(int x);
	void render();
	void render2();
};