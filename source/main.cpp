/*
 main.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: eugeneorr
 */
#if defined(_WIN32)||(_WIN64)

#include "SDL.h"

#endif

#if defined(__APPLE__)

#include "SDL2/SDL.h"

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"

#endif



#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {




#if defined(_WIN32)||(_WIN64)

cout<< "Running on windows  "<<endl;

#endif

#if defined(__APPLE__)

cout<<"running on mac"<<endl;

#endif

#if defined(__linux__)

cout<<"running on linux"<<endl;
cout<<"effectivly ran on linux"<<endl;

#endif


    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Get window surface
	screenSurface = SDL_GetWindowSurface( window );

	//set up game controller
	SDL_GameController* gGameController=NULL;

	//****** open game controller up
	gGameController=SDL_GameControllerOpen(0);
	//turn on game controller events
	SDL_GameControllerEventState(SDL_ENABLE);

	//SDL event to handle input

	SDL_Event event;
	//***set up variable for game states
	enum GameState{MENU,instruct,Playone,play2,win,lose};

	//set up initial state
	GameState gamestate=MENU;
	//bool values to controll movement through states
	bool menu,instruction,play1,players2,Win,Lose,quit;



	//Fill the surface white
	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 42, 254 ) );

	//Update the surface
	SDL_UpdateWindowSurface( window );

    // The window is open: could enter program loop here (see SDL_PollEvent())
	while(!quit)
	{
		switch(gamestate)
		{
		case MENU:

			menu=true;

			cout<<"the game state is menu"<<endl;
			cout<<"press A button for instructions"<<endl;
			cout<<" B for one player"<<endl;
			cout<<" x button for 2 player"<<endl;
			cout<<" y button for quit"<<endl;

			while (menu)
			{
				//cheack for input events
				if(SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed player hits x in window
					if(event.type==SDL_QUIT)
					{
						quit=true;
						menu=false;
						break;
					}
					switch(event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if(event.cdevice.which==0)
						{
							if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
							{
								menu=false;
								gamestate=instruct;
							}
							if(event.cbutton.button==SDL_CONTROLLER_BUTTON_B)
														{
															menu=false;
															gamestate=Playone;
														}
							if(event.cbutton.button==SDL_CONTROLLER_BUTTON_X)
														{
															menu=false;
															gamestate=play2;
														}
							if(event.cbutton.button==SDL_CONTROLLER_BUTTON_Y)
														{
															menu=false;
															quit=true;
														}
						}
						break;
					}
				}

			}
			break;

			//case two begins
		case instruct:

					instruction=true;

					cout<<"the game state is insrtructions"<<endl;
					cout<<"press A button for main menu"<<endl;
				cout<<endl;

					while (instruction)
					{
						//cheack for input events
						if(SDL_PollEvent(&event))
						{
							//check to see if the sdl window is closed player hits x in window
							if(event.type==SDL_QUIT)
							{
								quit=true;
								instruction=false;
								break;
							}
							switch(event.type)
							{

							case SDL_CONTROLLERBUTTONDOWN:

								if(event.cdevice.which==0)
								{
									if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
									{
										instruction=false;
										gamestate=MENU;
									}

								}
								break;
							}
						}

					}
					break;//end instructions case

		case Playone:

							play1=true;

							cout<<"the game state is play1"<<endl;
							cout<<"press A button for win"<<endl;
							cout<<"press B for lose"<<endl;
						cout<<endl;

							while (play1)
							{
								//cheack for input events
								if(SDL_PollEvent(&event))
								{
									//check to see if the sdl window is closed player hits x in window
									if(event.type==SDL_QUIT)
									{
										quit=true;
										play1=false;
										break;
									}
									switch(event.type)
									{

									case SDL_CONTROLLERBUTTONDOWN:

										if(event.cdevice.which==0)
										{
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
											{
												play1=false;
												gamestate=win;
											}
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_B)
																						{
																							play1=false;
																							gamestate=lose;
																						}

										}
										break;
									}
								}

							}
							break;//end play1


		case play2:

							players2=true;

							cout<<"the game state is play2"<<endl;
							cout<<"press A button for win"<<endl;
							cout<<"press B for lose"<<endl;
						cout<<endl;

							while (players2)
							{
								//cheack for input events
								if(SDL_PollEvent(&event))
								{
									//check to see if the sdl window is closed player hits x in window
									if(event.type==SDL_QUIT)
									{
										quit=true;
										players2=false;
										break;
									}
									switch(event.type)
									{

									case SDL_CONTROLLERBUTTONDOWN:

										if(event.cdevice.which==0)
										{
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
											{
												players2=false;
												gamestate=win;
											}
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_B)
																						{
																							players2=false;
																							gamestate=lose;
																						}

										}
										break;
									}
								}

							}
							break;//end play2




		case win:

							Win=true;

							cout<<"the game state is win"<<endl;
							cout<<"press A button for menu"<<endl;
							cout<<"press B for quit"<<endl;
						cout<<endl;

							while (Win)
							{
								//cheack for input events
								if(SDL_PollEvent(&event))
								{
									//check to see if the sdl window is closed player hits x in window
									if(event.type==SDL_QUIT)
									{
										quit=true;
										Win=false;
										break;
									}
									switch(event.type)
									{

									case SDL_CONTROLLERBUTTONDOWN:

										if(event.cdevice.which==0)
										{
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
											{
												Win=false;
												gamestate=MENU;
											}
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_B)
																						{
																							Win=false;
																							quit=true;
																						}

										}
										break;
									}
								}

							}
							break;//end play2



		case lose:

							Lose=true;

							cout<<"the game state is lose"<<endl;
							cout<<"press A button for menu"<<endl;
							cout<<"press B for quit"<<endl;
						cout<<endl;

							while (Lose)
							{
								//cheack for input events
								if(SDL_PollEvent(&event))
								{
									//check to see if the sdl window is closed player hits x in window
									if(event.type==SDL_QUIT)
									{
										quit=true;
										Lose=false;
										break;
									}
									switch(event.type)
									{

									case SDL_CONTROLLERBUTTONDOWN:

										if(event.cdevice.which==0)
										{
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
											{
												Lose=false;
												gamestate=MENU;
											}
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_B)
																						{
																							Lose=false;
																							quit=true;
																						}

										}
										break;
									}
								}

							}
							break;//end play2



		}
	}

  // SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}





