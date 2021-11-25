#pragma once
#include <iostream>
#include <string>
#include "delim.h"
#include "recfile.h"

#define GAME_LENID 8
#define GAME_RELDATE 10
#define GAME_SCORE 2
#define GAME_PRICE 3
#define STDMAXBUF 256

using namespace std;

class Game {
private:
	char id[GAME_LENID];
	string title;
	char release_date[GAME_RELDATE];
	string developer;
	string platform;
	char score[GAME_SCORE];
	char price[GAME_PRICE];

	string key;

public:
	Game();
	Game(const char * new_id);
	Game(const Game& m);
	Game & operator=(const Game &m);
	bool operator == (const Game &m);
	bool operator != (const Game &m);

	friend istream & operator >> (istream & is, Game &m);
	friend ostream & operator << (ostream & os, Game &m);

	void update_id(const char *new_id);
	void update_title(const string new_title);
	void update_releaseDate(const char *new_releaseDate);
	void update_developer(const string new_developer);
	void update_platform(const string new_platform);
	void update_score(const char *new_score);
	void update_price(const char *new_price);

	char* get_id();
	int get_GameLength();

	bool Pack(IOBuffer & Buffer) const;
	bool Unpack(IOBuffer & Buffer);

	char* Key();
};

istream & operator >> (istream & is, Game & m);
ostream & operator << (ostream & os, Game & m);