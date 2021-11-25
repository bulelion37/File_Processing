#pragma once
#include <iostream>
#include <string>
#include "delim.h"
#include "recfile.h"

#define PURCHASE_ID 12
#define PURCHASE_GAME_ID 8
#define PURCHASE_DATE 10
#define STDMAXBUF 256

using namespace std;

class Purchase {
private:
	char id[PURCHASE_ID];
	char game_id[PURCHASE_GAME_ID];
	string member_id;
	char date[PURCHASE_DATE];
	char key[1];

public:
	Purchase();
	Purchase(const char * new_id);
	Purchase(const Purchase&m);
	Purchase & operator=(const Purchase &m);
	bool operator == (const Purchase &m);
	bool operator != (const Purchase &m);

	friend istream & operator >> (istream & is, Purchase &m);
	friend ostream & operator << (ostream & os, Purchase &m);

	void update_id(const char *new_id);
	void update_game_id(const char * new_game_id);
	void update_member_id(const string new_member_id);
	void update_date(const char *new_date);
	void update_key(const char new_key);

	string getStr_id();
	string getStr_game_id();
	string get_member_id();
	int get_PurchaseLength();
	char get_Key();

	bool Pack(IOBuffer & Buffer) const;
	bool Unpack(IOBuffer & Buffer);
};

istream & operator >> (istream & is, Purchase &m);
ostream & operator << (ostream & os, Purchase &m);