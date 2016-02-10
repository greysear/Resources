#include "bullet.h";



bullet::bullet(SDL_Renderer *rend, string filepath, float x, float y)
{




	active = false;
	speed = 800;
	SDL_Surface *surface = IMG_Load(filepath.c_str());






	if (surface == NULL)
	{
		// In the case that the window could not be made...
		printf("Could not create surface: %s\n", SDL_GetError());

	}



	texture = SDL_CreateTextureFromSurface(rend, surface);

	if (texture == NULL) {
		// In the case that the window could not be made...
		printf("Could not create texture: %s\n", SDL_GetError());
	}

	SDL_FreeSurface(surface);

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	bulpos.w = w;
	bulpos.h = h;
	bulpos.x = x - (bulpos.w / 2);
	bulpos.y = y;

	xpos = x;
	ypos = y;
	xdir = 0;
	ydir = -1;


	//cout << bulpos.x << " X " << bulpos.y << " Y" <<bulpos.w<<" w "<< endl;

}

void bullet::update(float deltatime)
{

	if (active)
	{

		ypos += (speed*ydir)*deltatime;

		bulpos.y = (int)(ypos + 0.5f);

		if (bulpos.y < (0 - bulpos.h))
		{

			bulpos.x = -100;
			xpos = bulpos.x;
			active = false;

		}


		
	}
}




void bullet::Draw(SDL_Renderer *rend)
{
	
	SDL_RenderCopy(rend, texture, NULL, &bulpos);
}

//bullet::~bullet()
//{
//	SDL_DestroyTexture(texture);
//}
