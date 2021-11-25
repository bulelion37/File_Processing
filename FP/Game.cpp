#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include <sstream>

//생성자
Game::Game() {	}
Game::Game(const char * new_id) {
	update_id(new_id);
}

//복사 생성자
Game::Game(const Game &m) {
	update_id(m.id);
	update_title(m.title);
	update_releaseDate(m.release_date);
	update_developer(m.developer);
	update_platform(m.platform);
	update_score(m.score);
	update_price(m.price);
}

//객체 복사 생성자 (대입 연산자)
Game &Game::operator = (const Game & m) {
	update_id(m.id);
	update_title(m.title);
	update_releaseDate(m.release_date);
	update_developer(m.developer);
	update_platform(m.platform);
	update_score(m.score);
	update_price(m.price);
	return *this;
}

//연산자 오버로딩 : 같음 비교 연산자 , ID 기준
bool Game::operator == (const Game & m) {
	if (memcmp(this->id, m.id, GAME_LENID) != 0)
		return false;
	return true;
}

//연산자 오버로딩 : 다름 비교 연산자 , ID 기준
bool Game::operator != (const Game &m) {
	if (memcmp(this->id, m.id, GAME_LENID) == 0)
		return false;
	return true;
}

istream & operator >> (istream & is, Game & m) {
	string one_line;

	is.exceptions(istream::failbit | istream::badbit);

	try {
		getline(is, one_line);
	}
	catch (istream::failure e) {
		return is;
	}

	istringstream isstr(one_line);
	string part_data;

	getline(isstr, part_data, '|');
	m.update_id(part_data.data());

	getline(isstr, part_data, '|');
	m.update_title(part_data.data());

	getline(isstr, part_data, '|');
	m.update_releaseDate(part_data.data());

	getline(isstr, part_data, '|');
	m.update_developer(part_data.data());

	getline(isstr, part_data, '|');
	m.update_platform(part_data.data());

	getline(isstr, part_data, '|');
	m.update_score(part_data.data());

	getline(isstr, part_data, '|');
	m.update_price(part_data.data());

	return is;
}
ostream & operator << (ostream & os, Game & m) {
	string str_ID(m.id, GAME_LENID);
	string str_reldate(m.release_date, GAME_RELDATE);
	string str_score(m.score, GAME_SCORE);
	string str_price(m.price, GAME_PRICE);

	os << "ID : " << str_ID << "\n"
		<< "Title : " << m.title << "\n"
		<< "Release date : " << str_reldate << "\n"
		<< "Developer : " << m.developer << "\n"
		<< "Platform : " << m.platform << "\n"
		<< "Score : " << str_score << "\n"
		<< "Price : " << str_price << "\n";
	return os;
}

//멤버 변수 변경 : 각 필드 값을 갱신할 수 있는 함수
void Game::update_id(const char *new_id) {
	memcpy(this->id, new_id, GAME_LENID);
}
void Game::update_title(const string new_title) {
	this->title = new_title;
}
void Game::update_releaseDate(const char *new_releaseDate) {
	memcpy(this->release_date, new_releaseDate, GAME_RELDATE);
}
void Game::update_developer(const string new_developer) {
	this->developer = new_developer;
}
void Game::update_platform(const string update_platform) {
	this->platform = update_platform;
}
void Game::update_score(const char *new_score) {
	memcpy(this->score, new_score, GAME_SCORE);
}
void Game::update_price(const char *new_price) {
	memcpy(this->price, new_price, GAME_PRICE);
}

char * Game::get_id()
{
	return id;
}

int Game::get_GameLength()
{
	//header 표시하는 길이 3 추가, 7는 | 구분자 길이. 
	return ( 3+ GAME_LENID + title.length() + GAME_RELDATE + developer.length() + platform.length() + GAME_SCORE + GAME_PRICE + 7);
}

bool Game::Pack(IOBuffer & Buffer) const
{
	int numBytes;

	Buffer.Clear();

	string s_id(id, GAME_LENID);
	string s_release_date(release_date, GAME_RELDATE);
	string s_score(score, GAME_SCORE);
	string s_price(price, GAME_PRICE);

	numBytes = Buffer.Pack(s_id.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(title.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(s_release_date.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(developer.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(platform.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(s_score.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(s_price.c_str());
	if (numBytes == -1)	return false;

	return true;
}

bool Game::Unpack(IOBuffer & Buffer)
{
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(id, GAME_LENID);
	if (numBytes == -1)	return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1)	return false;
	title = buf;

	numBytes = Buffer.Unpack(release_date, GAME_RELDATE);
	if (numBytes == -1)	return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1)	return false;
	developer = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1)	return false;
	platform = buf;
	
	numBytes = Buffer.Unpack(score, GAME_SCORE);
	if (numBytes == -1)	return false;

	numBytes = Buffer.Unpack(price, GAME_PRICE);
	if (numBytes == -1)	return false;

	return true;
}

char* Game::Key()
{
	key.assign(id, GAME_LENID);
	return (char*)(key.c_str());
}

