#define _CRT_SECURE_NO_WARNINGS
#include "Purchase.h"
#include <sstream>

//생성자
Purchase::Purchase() {	}
Purchase::Purchase(const char * new_id) {
	update_id(new_id);
}

//복사 생성자
Purchase::Purchase(const Purchase &m) {
	update_id(m.id);
	update_game_id(m.game_id);
	update_member_id(m.member_id);
	update_date(m.date);
	update_key(m.key[0]);
}

//객체 복사 생성자 (대입 연산자)
Purchase &Purchase::operator = (const Purchase & m) {
	update_id(m.id);
	update_game_id(m.game_id);
	update_member_id(m.member_id);
	update_date(m.date);
	update_key(m.key[0]);
	return *this;
}

//연산자 오버로딩 : 같음 비교 연산자 , ID 기준
bool Purchase::operator == (const Purchase & m) {
	if (memcmp(this->id, m.id, PURCHASE_ID) != 0)
		return false;
	return true;
}

//연산자 오버로딩 : 다름 비교 연산자 , ID 기준
bool Purchase::operator != (const Purchase &m) {
	if (memcmp(this->id, m.id, PURCHASE_ID) == 0)
		return false;
	return true;
}

istream & operator >> (istream & is, Purchase & m) {
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
	m.update_game_id(part_data.data());

	getline(isstr, part_data, '|');
	m.update_member_id(part_data.data());

	getline(isstr, part_data, '|');
	m.update_date(part_data.data());

	getline(isstr, part_data, '|');
	m.update_key(part_data.data()[0]);

	return is;
}
ostream & operator << (ostream & os, Purchase & m) {
	string str_ID(m.id, PURCHASE_ID);
	string str_game_id(m.game_id, PURCHASE_GAME_ID);
	string str_date(m.date, PURCHASE_DATE);

	os << "Purchase ID : " << str_ID << "\n"
		<< "Game ID : " << str_game_id << "\n"
		<< "Member ID : " << m.member_id << "\n"
		<< "Purchase date : " << str_date << "\n"
		<< "Key : " << m.key[0] << "  ASCII CODE NUMBER :  " << (unsigned int)m.key[0] << endl;
	return os;
}

//멤버 변수 변경 : 각 필드 값을 갱신할 수 있는 함수
void Purchase::update_id(const char *new_id) {
	memcpy(this->id, new_id, PURCHASE_ID);
}
void Purchase::update_game_id(const char *new_game_id) {
	memcpy(this->game_id, new_game_id, PURCHASE_GAME_ID);
}
void Purchase::update_member_id(const string new_member_id) {
	this->member_id = new_member_id;
}
void Purchase::update_date(const char *new_date) {
	memcpy(this->date, new_date, PURCHASE_DATE);
}

void Purchase::update_key(const char new_key)
{
	this->key[0] = new_key;
}

string Purchase::getStr_id()
{
	string temp = "";
	for (int i = 0; i < PURCHASE_ID; i++)
		temp += id[i];
	return temp;
}

string Purchase::getStr_game_id()
{
	string temp = "";
	for (int i = 0; i < PURCHASE_GAME_ID; i++)
		temp += game_id[i];
	return temp;
}

string Purchase::get_member_id()
{
	return member_id;
}

int Purchase::get_PurchaseLength()
{
	//header 표시하는 길이 2 추가, 4는 | 구분자 길이. 
	return (3+PURCHASE_ID + PURCHASE_GAME_ID + member_id.length() + PURCHASE_DATE + 5 + 1);
}

bool Purchase::Pack(IOBuffer & Buffer) const
{
	int numBytes;

	Buffer.Clear();

	string s_id(id, PURCHASE_ID);
	string s_game_id(game_id, PURCHASE_GAME_ID);
	string s_date(date, PURCHASE_DATE);
	string s_key(key, 1);

	numBytes = Buffer.Pack(s_id.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(s_game_id.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(member_id.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(s_date.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(s_key.c_str());
	if (numBytes == -1)	return false;

	return true;
}

bool Purchase::Unpack(IOBuffer & Buffer)
{
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(id, PURCHASE_ID);
	if (numBytes == -1)	return false;
	
	numBytes = Buffer.Unpack(game_id, PURCHASE_GAME_ID);
	if (numBytes == -1)	return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1)	return false;
	member_id = buf;

	numBytes = Buffer.Unpack(date, PURCHASE_DATE);
	if (numBytes == -1)	return false;
	
	numBytes = Buffer.Unpack(key, 1);
	if (numBytes == -1) return false;

	return true;
}

char Purchase::get_Key()
{
	return key[0];
}
