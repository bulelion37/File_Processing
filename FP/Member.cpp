#define _CRT_SECURE_NO_WARNINGS
#include "Member.h"
#include <sstream>

//������
Member::Member() {	}
Member::Member(const char * new_id) {
	update_id(new_id);
}

//���� ������
Member::Member(const Member &m){
	update_id(m.id);
	update_password(m.password);
	update_name(m.name);
	update_email(m.email);
	update_address(m.address);
	update_birthday(m.birthday);
	update_Class(m.Class);
	update_level(m.level);
}

//��ü ���� ������ (���� ������)
Member &Member::operator = (const Member & m){
	update_id(m.id);
	update_password(m.password);
	update_name(m.name);
	update_email(m.email);
	update_address(m.address);
	update_birthday(m.birthday);
	update_Class(m.Class);
	update_level(m.level);
	return *this;
}

//������ �����ε� : ���� �� ������ , ID ����
bool Member::operator == (const Member & m){
	if (this->id == m.id)
		return true;
	return false;
}

//������ �����ε� : �ٸ� �� ������ , ID ����
bool Member::operator != (const Member &m){
	if (this->id == m.id)
		return false;
	return true;
}

istream & operator >> (istream & is, Member & m){
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
	m.update_password(part_data.data());

	getline(isstr, part_data, '|');
	m.update_name(part_data.data());

	getline(isstr, part_data, '|');
	m.update_email(part_data.data());

	getline(isstr, part_data, '|');
	m.update_address(part_data.data());

	getline(isstr, part_data, '|');
	m.update_birthday(part_data.data());

	getline(isstr, part_data, '|');
	m.update_Class(part_data.data());

	getline(isstr, part_data, '|');
	m.update_level(part_data.data());

	return is;
}
ostream & operator << (ostream & os, Member & m){
	string str_birthday(m.birthday, MEM_LENBIR);
	string str_Class(m.Class, MEM_LENCLASS);

	os << "ID : " << m.id << "\n"
		<< "Password : " << m.password << "\n"
		<< "NAME : " << m.name << "\n"
		<< "E-mail : " << m.email << "\n"
		<< "Address : " << m.address << "\n"
		<< "BIRTHDAY : " << str_birthday << "\n"
		<< "Class : " << str_Class << "\n";
	return os;
}

//��� ���� ���� : �� �ʵ� ���� ������ �� �ִ� �Լ�
void Member::update_id(const string new_id){
	this->id = new_id;
}
void Member::update_password(const string new_password){
	this->password = new_password;
}
void Member::update_name(const string new_name) {
	this->name = new_name;
}
void Member::update_email(const string new_email){
	this->email = new_email;
}
void Member::update_address(const string new_address) {
	this->address = new_address;
}
void Member::update_birthday(const char *new_birthday){
	memcpy(this->birthday, new_birthday, MEM_LENBIR);
}
void Member::update_Class(const char *new_Class){
	memcpy(this->Class, new_Class, MEM_LENCLASS);
}

void Member::update_level(const char* new_level)
{
	memcpy(this->level, new_level, MEM_LENLEVEL);
}

string Member::get_id()
{
	return id;
}

string Member::get_password()
{
	return password;
}

int Member::get_level()
{
	return atoi(level);
}

int Member::get_MemberLength()
{
	//deleted flag 1 + header ǥ���ϴ� ���� 2 �߰�, 8�� | ������ ����. 
	return ( 1+ 2+ id.length() + password.length() + name.length() + email.length() + address.length() + MEM_LENBIR + MEM_LENCLASS +MEM_LENLEVEL+ 8);
}


bool Member::Pack(IOBuffer & Buffer) const
{
	int numBytes;

	Buffer.Clear();

	string s_birthday(birthday, MEM_LENBIR);
	string s_Class(Class, MEM_LENCLASS);
	string s_Level(level, MEM_LENLEVEL);

	numBytes = Buffer.Pack(id.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(password.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(name.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(email.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(address.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(s_birthday.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(s_Class.c_str());
	if (numBytes == -1)	return false;

	numBytes = Buffer.Pack(s_Level.c_str());
	if (numBytes == -1)	return false;

	return true;
}

bool Member::Unpack(IOBuffer & Buffer)
{
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1)	return false;
	id = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1)	return false;
	password = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1)	return false;
	name = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1)	return false;
	email = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1)	return false;
	address = buf;

	numBytes = Buffer.Unpack(birthday, MEM_LENBIR);
	if (numBytes == -1)	return false;

	numBytes = Buffer.Unpack(Class, MEM_LENCLASS);
	if (numBytes == -1)	return false;

	numBytes = Buffer.Unpack(level, MEM_LENCLASS);
	if (numBytes == -1)	return false;

	return true;
}

char* Member::Key()
{
	key = id;
	return (char*)(key.c_str());
}
