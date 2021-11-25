#pragma once
#include <iostream>
#include <string>
#include "delim.h"
#include "recfile.h"

#define MEM_LENBIR 10
#define MEM_LENCLASS 1
#define MEM_LENLEVEL 1
#define STDMAXBUF 256

using namespace std;

class Member {
private:
	string id;
	string password;
	string name;
	string email;
	string address;
	char birthday[MEM_LENBIR];
	char Class[MEM_LENCLASS];
	char level[MEM_LENLEVEL];
	string key;

public:
	Member();
	Member(const char * new_id);
	Member(const Member& m);
	Member & operator=(const Member &m);
	bool operator == (const Member &m);
	bool operator != (const Member &m);

	friend istream & operator >> (istream & is, Member &m);
	friend ostream & operator << (ostream & os, Member &m);
	
	void update_id(const string new_id);
	void update_password(const string new_password);
	void update_name(const string new_name);
	void update_email(const string new_email);
	void update_address(const string new_address);
	void update_birthday(const char *new_birthday);
	void update_Class(const char *new_Class);
	void update_level(const char* new_level);

	string get_id();
	string get_password();
	int get_level();
	int get_MemberLength();

	bool Pack(IOBuffer & Buffer) const;
	bool Unpack(IOBuffer & Buffer);

	char* Key();
};

istream & operator >> (istream & is, Member & m);
ostream & operator << (ostream & os, Member & m);