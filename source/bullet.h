#if defined(_WIN32)||(_WIN64)

#include "SDL.h"
#include "SDL_image.h"



#endif
#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#endif


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;


class bullet
{

public:

	bool active;

	SDL_Texture *texture;
	SDL_Rect bulpos;
	float speed;
	float xdir, ydir;
	float xpos, ypos;

	bullet(SDL_Renderer *rend, string filepath, float x, float y);

	void update(float deltatime);

	void Draw(SDL_Renderer *rend);

	//~bullet();




};
