#include <iostream>
#include <SDL.h>

using namespace std;

void renderGame(SDL_Renderer* renderer,const string& guessedWord, const string& badGuesses);
void displayFinalResult(SDL_Renderer* renderer,bool won, const string& word);
void setRenderColor(SDL_Renderer* renderer,SDL_Color cl);
bool trangChu(SDL_Renderer* renderer,bool choiLai);
