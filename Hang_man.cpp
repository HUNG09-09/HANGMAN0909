#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <fstream>
#include <algorithm>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"

using namespace std;

const int MAX_BAD_GUESSES = 7;
const char DATA_FILE[] = "data/Ogden_Picturable_200.txt";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const string WINDOW_TITLE = "HANG MAN";
const string BGM = "bgm1.mp3";

string chooseWord(const char* fileName);
string getLowerCaseString(const string& s);
string getHigherCaseString(const string& s);
char readAGuess();
bool contains(const string& word, char guess);
void updateGuessedWord(string& guessedWord, const string& word, char guess);

void logSDLError(std::ostream& os,const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void waitUntilKeyPressed();

int main(int agrc,char* agrv[])
{
	srand(time(0));

	SDL_Renderer* renderer;
	SDL_Window* window;
    SDL_Event e;

    bool thua = false;
    bool win = false;
    bool clai = false;

	initSDL(window,renderer);
    TTF_Init();
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);

    Mix_Music* mus = Mix_LoadMUS(BGM.c_str());

    Mix_PlayMusic(mus,-1);

    while(trangChu(renderer,clai)){
        thua = false;
        win = false;
        clai = true;
        string word = chooseWord(DATA_FILE);
        if (word.length() < 1) {
            cout << "Error reading vocabulary file " << DATA_FILE;
            return -1;
        }

        string guessedWord = string(word.length(), '-');
        string badGuesses = "";

        renderGame(renderer,guessedWord, badGuesses);

        while(!thua) {
            char guess = '!';

            while(SDL_PollEvent(&e)){
                switch(e.type){
                case SDL_QUIT:
                    thua = true;
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                    case SDLK_ESCAPE:
                        thua = true;
                        break;
                    default:
                        guess = (char)e.key.keysym.sym;
                        //cout<<guess;
                        if((guess >= 'a' && guess <= 'z') || (guess >= 'A' && guess <= 'Z')){
                            guess = ::tolower(guess);
                        }else{
                            guess = '!';
                        }
                        break;
                    }
                    break;
                }

            }

            if(guess != '!'){
                if (contains(word, guess))
                    updateGuessedWord(guessedWord, word, guess);
                else {
                    badGuesses += guess;
                }
                //cout<<getHigherCaseString(badGuesses)<<endl;
                renderGame(renderer,guessedWord, badGuesses);
            }
            if (badGuesses.size() >= MAX_BAD_GUESSES || word == guessedWord){
                thua = true;
                win = true;
            }
        }
        SDL_Delay(1000);
        displayFinalResult(renderer,(win && (badGuesses.length() < MAX_BAD_GUESSES)), word);
        waitUntilKeyPressed();
    }

    Mix_PausedMusic();


    Mix_FreeMusic(mus);

    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

    SDL_Quit();
    TTF_Quit();

	return 0;
}

string getLowerCaseString(const string& s)
{
    string res = s;
    transform(s.begin(), s.end(), res.begin(), ::tolower);
    return res;
}

string getHigherCaseString(const string& s)
{
    string res = s;
    transform(s.begin(), s.end(), res.begin(), ::toupper);
    return res;
}

string chooseWord(const char* fileName)
{
    //return "book";
	vector<string> wordList;
	ifstream file(fileName);
  	if (file.is_open()) {
	    string word;
		while (file >> word) {
            wordList.push_back(word);
        }
    	file.close();
  	}
  	if (wordList.size() > 0) {
  		int randomIndex = rand() % wordList.size();
    	return getLowerCaseString(wordList[randomIndex]);
	} else return "";
}

char readAGuess()
{
	SDL_Event e;
    while(1){
        if ( SDL_WaitEvent(&e) != 0 && e.type == SDL_KEYDOWN){
          return (char)e.key.keysym.sym;
        }
    }
}

bool contains(const string& word, char c)
{
	return (word.find_first_of(c) != string::npos);
}

void updateGuessedWord(string& guessedWord, const string& word, char guess)
{
	for (int i = word.length() - 1; i >= 0; i--) {
        if (word[i] == guess) {
            guessedWord[i] = guess;
        }
    }
}



void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    logSDLError(std::cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void logSDLError(std::ostream& os,const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}


void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        //SDL_Delay(100);
    }
}
