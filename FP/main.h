 #pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Member.h"
#include "Game.h"
#include "Purchase.h"
#include "recfile.h"
#include "textind.h"
#include "indfile.h"
#include "buffile.h"
#include "tindbuff.h"
#include "btnode.h"
#include "btree.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

string UserID;
int GPSLevel;
bool IDXFlag = false;
int purchaseCnt = 100;

BTree <char> bt(4);

void ShowMenu();
int showMember();
int showGame();
int showPurchase();
int MemberTest();
int GameTest();
int PurchaseTest();
void GamePurchaseSystem();
int GPSystemLogin();
void AdminModeGPS();
void UserModeGPS();
void makeIndexFile();
void MemberGPS();
void GameGPS();
void PurchaseGPS();
int searchMember(string IDLine, int calledFlag);
void insertMember(string IDLine);
void deleteMember(string IDLine);
void modifyMember(string IDLine);
int searchGame(string IDLine, int calledFlag);
void insertGame(string IDLine);
void deleteGame(string IDLine);
void modifyGame(string IDLine);
string stringtoLenString(string IDLine, int length);
int searchPurchase(string IDLine, int calledFlag, int dataNum);
void insertPurchase(string IDLine, int dataNum);
void deletePurchase(string IDLine, int dataNum);
void modifyPurchase(string IDLine, int dataNum);

void ShowMenu()
{
	cout << "++++++++++++++++++++++++" << endl;
	cout << "1 : showMember   " << endl;
	cout << "2 : showGame   " << endl;
	cout << "3 : showPurchase   " << endl;
	cout << "4 : MemberTest   " << endl;
	cout << "5 : GameTest   " << endl;
	cout << "6 : PurchaseTest   " << endl;
	cout << "7 : GamePurchaseSystem   " << endl;
	cout << "8 : Exit   " << endl;
	cout << "++++++++++++++++++++++++" << endl;
}

int showMember(){
	cout << "\t< Test Program : ShowMember >" << endl;
	ifstream ifs("listOfMember.txt");
		if(ifs.fail()){
			cout << "\tFile Open error!" << endl;
			return -1;
		}

		int n;
		ifs >> n;
		ifs.ignore(numeric_limits<streamsize>::max(), '\n');

		vector<Member> m_list;

		cout << "\n\tReading listOfMember.txt" << endl;
		cout << "\t..." << endl;
		for (int i = 0; i < n; i++){
			Member m;
			ifs >> m;
			m_list.push_back(m);
		}
		cout << "\tSuccess Reading listOfMember.txt" << endl << endl;

		for (int i = 0; i < 10; i++)
		{
			cout << i+1 << "th Member" << endl;
			cout << m_list[i] << endl;
		}
		ifs.close();
		m_list.clear();
		return 0;
}

int showGame(){
	cout << "\t< Test Program : ShowGame >" << endl;
	ifstream ifs("listOfGame.txt");
	if (ifs.fail()) {
		cout << "\tFile Open error!" << endl;
		return -1;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<Game> m_list;

	cout << "\n\tReading listOfGame.txt" << endl;
	cout << "\t..." << endl;
	for (int i = 0; i < n; i++) {
		Game m;
		ifs >> m;
		m_list.push_back(m);
	}
	cout << "\tSuccess Reading listOfGame.txt" << endl << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << i+1 << "th Game" << endl;
		cout << m_list[i] << endl;
	}
	ifs.close();
	m_list.clear();
	return 0;
}

int showPurchase(){
	cout << "\t< Test Program : ShowPurchase >" << endl;
	ifstream ifs("listOfPurchase.txt");
	if (ifs.fail()) {
		cout << "\tFile Open error!" << endl;
		return -1;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<Purchase> m_list;

	cout << "\n\tReading listOfPurchase.txt" << endl;
	cout << "\t..." << endl;
	for (int i = 0; i < n; i++) {
		Purchase m;
		ifs >> m;
		m_list.push_back(m);
	}
	cout << "\tSuccess Reading listOfPurchase.txt" << endl << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << i + 1 << "th Purchase" << endl;
		cout << m_list[i] << endl;
	}
	ifs.close();
	m_list.clear();
	return 0;
}

int MemberTest(){

	cout << "\t< Test Program : MemberTest >" << endl;
	ifstream ifs("listOfMember.txt");
	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return -1;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	char fileName[20] = "fileOfMember.dat";

	//Write test
	cout << "\n\tWriting fileOfMember.dat" << endl;
	cout << "\t..." << endl;

	MemberFile.Create(fileName, ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Member m;
		ifs >> m;
		int recaddr;
		if ((recaddr = MemberFile.Write(m)) == -1)
			cout << "Write Error!" << endl;
		//else
			//cout << "Write at " << recaddr << endl;
	}
	MemberFile.Close();
	cout << "\tSuccess Writing fileOfMember.dat" << endl << endl;

	//Read test
	cout << "\n\tReading fileOfMember.dat" << endl;
	cout << "\t..." << endl;

	MemberFile.Open(fileName, ios::in);
	for (int i = 0; i < n; i++) {
		Member m;
		MemberFile.Read(m, -1);

		if (i < 10) {
			cout << i + 1 << "th Member" << endl;
			cout << m << endl;
		}
	}
	MemberFile.Close();
	ifs.close();
	cout << "\tSuccess Reading fileOfMember.dat" << endl << endl;
	return 0;
}

int GameTest(){
	cout << "\t< Test Program : GameTest >" << endl;
	ifstream ifs("listOfGame.txt");
	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return -1;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Game> GameFile(buffer);

	char fileName[20] = "fileOfGame.dat";

	//Write test
	cout << "\n\tWriting fileOfGame.dat" << endl;
	cout << "\t..." << endl;

	GameFile.Create(fileName, ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Game m;
		ifs >> m;
		int recaddr;
		if ((recaddr = GameFile.Write(m)) == -1)
			cout << "Write Error!" << endl;
		//else
			//cout << "Write at " << recaddr << endl;
	}
	GameFile.Close();
	cout << "\tSuccess Writing fileOfGame.dat" << endl << endl;

	//Read test
	cout << "\n\tReading fileOfGame.dat" << endl;
	cout << "\t..." << endl;

	GameFile.Open(fileName, ios::in);
	for (int i = 0; i < n; i++) {
		Game m;
		GameFile.Read(m,-1);

		if (i < 10) {
			cout << i + 1 << "th Game" << endl;
			cout << m << endl;
		}
	}
	GameFile.Close();
	ifs.close();
	cout << "\tSuccess Reading fileOfGame.dat" << endl << endl;
	return 0;
}

int PurchaseTest(){
	cout << "\t< Test Program : PurchaseTest >" << endl;
	ifstream ifs("listOfPurchase.txt");
	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return -1;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);

	char fileName[22] = "fileOfPurchase.dat";

	//Write test
	cout << "\n\tWriting fileOfPurchase.dat" << endl;
	cout << "\t..." << endl;

	PurchaseFile.Create(fileName, ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Purchase m;
		ifs >> m;
		int recaddr;
		if ((recaddr = PurchaseFile.Write(m)) == -1)
			cout << "Write Error!" << endl;
		//else
			//cout << "Write at " << recaddr << endl;
	}
	PurchaseFile.Close();
	cout << "\tSuccess Writing fileOfPurchase.dat" << endl << endl;

	//Read test
	cout << "\n\tReading fileOfPurchase.dat" << endl;
	cout << "\t..." << endl;

	PurchaseFile.Open(fileName, ios::in);
	for (int i = 0; i < n; i++) {
		Purchase m;
		PurchaseFile.Read(m,-1);

		if (i < 10) {
			cout << i + 1 << "th Purchase" << endl;
			cout << m << endl;
		}
	}
	PurchaseFile.Close();
	ifs.close();
	cout << "\tSuccess Reading fileOfPurchase.dat" << endl << endl;
	return 0;
}

void GamePurchaseSystem() {
	if (!IDXFlag)
	{
		makeIndexFile();
		IDXFlag = true;
	}
	GPSLevel = GPSystemLogin();
	if (GPSLevel == 1)
		//관리자 모드
		AdminModeGPS();
	else
		//사용자 모드
		UserModeGPS();
}

int GPSystemLogin()
{
	int MemLV = 0;
	string InputID, InputPW;
	while (1) {
		cout << "Input ID : ";
		cin >> InputID;
		cout << "Input Password : ";
		cin >> InputPW;

		char MemName[20] = "fileOfMember";
		Member m;

		DelimFieldBuffer buf('|', STDMAXBUF);
		TextIndexedFile<Member>MemberIdxedFile(buf, 20, 1100);
		MemberIdxedFile.Open(MemName);

		int checked = MemberIdxedFile.Read((char*)(InputID.c_str()), m);
		MemberIdxedFile.Close();
		if (checked != -1)
		{
			if (InputPW.compare(m.get_password()) == 0)
			{
				if (InputID.compare("admin") == 0)
				{
					MemLV = 1;
					break;
				}
				else
				{
					MemLV = 9;
					UserID = InputID;
					break;
				}
			}
			else
				cout << "Wrong ID or Password!\n";
		}
		else
			cout << "Wrong ID or Password!\n";
	}
	return MemLV;
}

void AdminModeGPS()
{
	//관리자 모드
	cout << "\n  Admin Mode Menu" << endl;
	cout << "1 : Member   " << endl;
	cout << "2 : Game   " << endl;
	cout << "3 : Purchase   " << endl;
	cout << "4 : Exit GamePurchaseSystem" << endl;
	
	int GamePurchaseNum = 0;
	string GamePurchaseLine;
	while (1)
	{
		//Menu number 입력 받음.
		cout << "\ninput the number of GamePurchase System Menu >>> ";
		cin >> GamePurchaseLine;

		//Menu number int로 변환
		stringstream ssInt(GamePurchaseLine);
		ssInt >> GamePurchaseNum;

		//Quit
		if (GamePurchaseNum == 4)
			break;
		else
		{
			switch (GamePurchaseNum)
			{
			case 1:
				MemberGPS();
				break;
			case 2:
				GameGPS();
				break;
			case 3:
				PurchaseGPS();
				break;
			default:
				cout << "Input Correct Number!" << endl;
				break;
			}
		}
	}
}

void UserModeGPS()
{
	//사용자 모드
	cout << "\n  User Mode Menu" << endl;
	cout << "1 : Member   " << endl;
	cout << "2 : Game   " << endl;
	cout << "3 : Purchase   " << endl;
	cout << "4 : Exit GamePurchaseSystem" << endl;

	int GamePurchaseNum = 0;
	string GamePurchaseLine;
	while (1)
	{
		//Menu number 입력 받음.
		cout << "\ninput the number of GamePurchase System Menu >>> ";
		cin >> GamePurchaseLine;

		//Menu number int로 변환
		stringstream ssInt(GamePurchaseLine);
		ssInt >> GamePurchaseNum;

		//Quit
		if (GamePurchaseNum == 4)
			break;
		else
		{
			switch (GamePurchaseNum)
			{
			case 1:
				MemberGPS();
				break;
			case 2:
				GameGPS();
				break;
			case 3:
				PurchaseGPS();
				break;
			default:
				cout << "Input Correct Number!" << endl;
				break;
			}
		}
	}
}

void makeIndexFile()
{
	//Member Index File
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	TextIndex MemberIndex(1100);

	char fileName[20] = "fileOfMember.dat";
	char fileName2[20] = "fileOfMember.ind";
	MemberFile.Open(fileName, ios::in);
	while (1) {		// 학생 데이터를 읽어서 인덱스를 생성
		Member m;
		int recaddr = MemberFile.Read(m);
		if (recaddr == -1) 
			break;
		MemberIndex.Insert(m.Key(), recaddr);
		//cout << recaddr << '\n' << m;
	}
	MemberFile.Close();

	// 생성한 인덱스를 인덱스 파일로 저장
	TextIndexBuffer idxbuf(20, 1100);
	//ID의 길이만큼 10개를 가질 수 있는 버퍼. 
	BufferFile MemIdxFile(idxbuf);
	MemIdxFile.Create(fileName2, ios::out | ios::trunc);
	MemIdxFile.Rewind(); //헤더 다음의 첫번째 레코드 위치로 이동
	idxbuf.Pack(MemberIndex);
	int result = MemIdxFile.Write();
	MemIdxFile.Close();

	if(!IDXFlag)
		cout << "Member Index File has made \n";
	

	//Game Index File

	DelimFieldBuffer buffer2('|', STDMAXBUF);
	RecordFile <Game> GameFile(buffer2);

	TextIndex GameIndex(1100);

	char gameName[20] = "fileOfGame.dat";
	char gameName2[20] = "fileOfGame.ind";
	GameFile.Open(gameName, ios::in);
	while (1) {		// 학생 데이터를 읽어서 인덱스를 생성
		Game m;
		int recaddr = GameFile.Read(m);
		if (recaddr == -1) break;
		GameIndex.Insert(m.Key(), recaddr);
		//cout << recaddr << '\n' << m;
	}
	GameFile.Close();

	// 생성한 인덱스를 인덱스 파일로 저장
	TextIndexBuffer idxbuf2(GAME_LENID, 1100);
	//ID의 길이만큼 10개를 가질 수 있는 버퍼. 
	BufferFile GameIdxFile(idxbuf2);
	GameIdxFile.Create(gameName2, ios::out | ios::trunc);
	GameIdxFile.Rewind(); //헤더 다음의 첫번째 레코드 위치로 이동
	idxbuf2.Pack(GameIndex);
	int result2 = GameIdxFile.Write();
	GameIdxFile.Close();

	if (!IDXFlag)
		cout << "Game Index File has made \n";

	char purchaseName[20] = "fileOfPurchase.dat";
	char purchaseName2[20] = "fileOfPurchase.ind";

	bt.Create(purchaseName2, ios::in | ios::out | ios::trunc);

	// purchase 데이터를 읽어서 인덱스를 생성, B-Tree도 생성. 
	DelimFieldBuffer buffer3('|', 1000);
	RecordFile <Purchase> PurchaseFile(buffer3);

	PurchaseFile.Open(purchaseName, ios::in);
	while (1) {
		Purchase p;
		int temp_key = 0;
		int recaddr = PurchaseFile.Read(p);
		if (recaddr == -1) break;
		bt.Insert(p.get_Key(), recaddr); //인덱스를 추가함!
	}
	PurchaseFile.Close();

	if (!IDXFlag)
		cout << "Purchase Index File has made \n";

}

void MemberGPS()
{
	int FunctionNum = 0;
	string IDLine, FuntionLine;
	int searchMemFlag = 0;

	//관리자 모드
	if (GPSLevel == 1)
	{
		cout << "1 : Search   " << endl;
		cout << "2 : Insert   " << endl;
		cout << "3 : Delete   " << endl;
		cout << "4 : Modify   " << endl;
		cout << "5 : Exit GamePurchaseSystem" << endl;

		cout << "\ninput the number of Function Menu >>> ";
		cin >> FuntionLine;
		FunctionNum = stoi(FuntionLine);

		//잘못된 Function Menu
		if (FunctionNum > 5)
		{
			while (1)
			{
				cout << "Wrong Function Number\n";
				cin >> FuntionLine;
				FunctionNum = stoi(FuntionLine);

				if (FunctionNum < 5 && FunctionNum > 0)
					break;
				else if (FunctionNum == 5)
					return;
			}
		}
		//Exit
		else if (FunctionNum == 5)
			return;
		else
		{
			cout << "\ninput Member ID >>> ";
			cin >> IDLine;

			//search
			if (FunctionNum == 1)
				searchMember(IDLine,1);
			
			//modify & delete & insert
			else {
				if (FunctionNum == 2)
					insertMember(IDLine);
				else if (FunctionNum == 3)
					deleteMember(IDLine);
				else
					modifyMember(IDLine);
			}
		}
	}
	//사용자 모드
	else
	{
		cout << "1 : Delete   " << endl;
		cout << "2 : Modify   " << endl;
		cout << "3 : Exit GamePurchaseSystem" << endl;

		cout << "\ninput the number of Function Menu >>> ";
		cin >> FuntionLine;
		FunctionNum = stoi(FuntionLine);

		//잘못된 Function Menu
		if (FunctionNum > 3)
		{
			while (1)
			{
				cout << "Wrong Function Number\n";
				cin >> FuntionLine;
				FunctionNum = stoi(FuntionLine);

				if (FunctionNum < 3 && FunctionNum > 0)
					break;
				else if (FunctionNum == 3)
					return;
			}
		}
		//Exit
		else if (FunctionNum == 3)
			return;
		else
		{
			if (FunctionNum == 1)
				deleteMember(UserID);
			else
				modifyMember(UserID);

		}
	}
}

void GameGPS()
{
	int FunctionNum = 0;
	string IDLine, FuntionLine;
	int searchMemFlag = 0;

	//관리자 모드
	if (GPSLevel == 1)
	{
		cout << "1 : Search   " << endl;
		cout << "2 : Insert   " << endl;
		cout << "3 : Delete   " << endl;
		cout << "4 : Modify   " << endl;
		cout << "5 : Exit GamePurchaseSystem" << endl;

		cout << "\ninput the number of Function Menu >>> ";
		cin >> FuntionLine;
		FunctionNum = stoi(FuntionLine);

		//잘못된 Function Menu
		if (FunctionNum > 5)
		{
			while (1)
			{
				cout << "Wrong Function Number\n";
				cin >> FuntionLine;
				FunctionNum = stoi(FuntionLine);

				if (FunctionNum < 5 && FunctionNum > 0)
					break;
				else if (FunctionNum == 5)
					return;
			}
		}
		//Exit
		else if (FunctionNum == 5)
			return;
		else
		{
			cout << "\ninput Game ID >>> ";
			cin >> IDLine;

			//search
			if (FunctionNum == 1)
				searchGame(IDLine, 1);

			//modify & delete & insert
			else {
				if (FunctionNum == 2)
					insertGame(IDLine);
				else if (FunctionNum == 3)
					deleteGame(IDLine);
				else
					modifyGame(IDLine);
			}
		}
	}
	//사용자 모드
	else
	{
		cout << "1 : Search   " << endl;
		cout << "2 : Exit GamePurchaseSystem" << endl;

		cout << "\ninput the number of Function Menu >>> ";
		cin >> FuntionLine;
		FunctionNum = stoi(FuntionLine);

		//잘못된 Function Menu
		if (FunctionNum > 2)
		{
			while (1)
			{
				cout << "Wrong Function Number\n";
				cin >> FuntionLine;
				FunctionNum = stoi(FuntionLine);

				if (FunctionNum < 2 && FunctionNum > 0)
					break;
				else if (FunctionNum == 2)
					return;
			}
		}
		//Exit
		else if (FunctionNum == 2)
			return;
		else
		{
			if (FunctionNum == 1)
			{
				cout << "\ninput Game ID >>> ";
				cin >> IDLine;
				searchGame(IDLine, 1);
			}
		}
	}
}

void PurchaseGPS()
{
	int FunctionNum = 0;
	string IDLine, FuntionLine;
	int searchMemFlag = 0;

	//관리자 모드
	if (GPSLevel == 1)
	{
		cout << "1 : Search   " << endl;
		cout << "2 : Insert   " << endl;
		cout << "3 : Delete   " << endl;
		cout << "4 : Modify   " << endl;
		cout << "5 : Exit GamePurchaseSystem" << endl;

		cout << "\ninput the number of Function Menu >>> ";
		cin >> FuntionLine;
		FunctionNum = stoi(FuntionLine);

		//잘못된 Function Menu
		if (FunctionNum > 5)
		{
			while (1)
			{
				cout << "Wrong Function Number\n";
				cin >> FuntionLine;
				FunctionNum = stoi(FuntionLine);

				if (FunctionNum < 5 && FunctionNum > 0)
					break;
				else if (FunctionNum == 5)
					return;
			}
		}
		//Exit
		else if (FunctionNum == 5)
			return;
		else
		{
			//search
			if (FunctionNum == 1)
			{
				cout << "\nSearch Menu" << endl;
				cout << "1 : Search by Member ID   " << endl;
				cout << "2 : Search by Game ID   " << endl;
				cout << "3 : Search by Purchase ID   " << endl;
				cout << "4 : Search by Key   " << endl;

				cout << "\ninput the number of Search Menu >>> ";
				cin >> FuntionLine;
				FunctionNum = stoi(FuntionLine);

				if (FunctionNum == 1)
				{
					cout << "\ninput Member ID >>> ";
					cin >> IDLine;
					searchMemFlag = searchPurchase(IDLine, 1, 1);
					if (searchMemFlag == -1)
						cout << "No such ID!\n";
				}
				else if (FunctionNum == 2)
				{
					cout << "\ninput Game ID >>> ";
					cin >> IDLine;
					searchMemFlag = searchPurchase(IDLine, 1, 2);
					if (searchMemFlag == -1)
						cout << "No such ID!\n";
				}
				else if (FunctionNum == 3)
				{
					cout << "\ninput Purchase ID >>> ";
					cin >> IDLine;
					searchMemFlag = searchPurchase(IDLine, 1, 3);
					if (searchMemFlag == -1)
						cout << "No such ID!\n";
				}
				else if (FunctionNum == 4)
				{
					cout << "\ninput key (0~127 ASCII NUMBER) >>> ";
					cin >> IDLine;
					searchMemFlag = searchPurchase(IDLine, 1, 4);
					if (searchMemFlag == -1)
						cout << "No such ID!\n";
				}
				else 
					cout << "Wrong Search Number\n";
			}

			//modify & delete & insert
			else {
				cout << "\ninput Purchase Key >>> ";
				cin >> IDLine;

				if (FunctionNum == 2)
					insertPurchase(IDLine, 2);
				else if (FunctionNum == 3)
					deletePurchase(IDLine,2);
				else
					modifyPurchase(IDLine, 2);
			}
		}
	}
	//사용자 모드
	else
	{
		cout << "1 : Search   " << endl;
		cout << "2 : Insert   " << endl;
		cout << "3 : Delete   " << endl;
		cout << "4 : Modify   " << endl;
		cout << "5 : Exit GamePurchaseSystem" << endl;

		cout << "\ninput the number of Function Menu >>> ";
		cin >> FuntionLine;
		FunctionNum = stoi(FuntionLine);

		//잘못된 Function Menu
		if (FunctionNum > 5)
		{
			while (1)
			{
				cout << "Wrong Function Number\n";
				cin >> FuntionLine;
				FunctionNum = stoi(FuntionLine);

				if (FunctionNum < 5 && FunctionNum > 0)
					break;
				else if (FunctionNum == 5)
					return;
			}
		}
		//Exit
		else if (FunctionNum == 5)
			return;
		else
		{
			//search
			if (FunctionNum == 1)
			{
				searchMemFlag = searchPurchase(UserID, 1, 1);
				if (searchMemFlag == -1)
					cout << "No such ID\n";
			}

			//modify & delete & insert
			else {
				if (FunctionNum == 2)
					insertPurchase(UserID,1);
				else if (FunctionNum == 3)
					deletePurchase(UserID, 1);
				else
				{
					searchPurchase(UserID, 1, 1);
					modifyPurchase(UserID,1);
				}
			}
		}
	}
}

int searchMember(string IDLine, int calledFlag)
{
	//calledFlag : 1 : search에서 호출, calledFlag : 2 그 이외에 호출
	char MemberFile[20] = "fileOfMember";
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<Member>MemberIdxedFile(buf, 20, 1100);
	MemberIdxedFile.Open(MemberFile);
	Member m;

	int checked = MemberIdxedFile.Read((char*)(IDLine.c_str()), m);
	MemberIdxedFile.Close();
	if (calledFlag == 1)
	{
		if (checked == -1)
			cout << "No such ID\n";
		else
			cout << m << endl;
	}
	return checked;
}

void insertMember(string IDLine)
{
	//새로운 데이터 입력. 
	Member insertMember;
	insertMember.update_id(IDLine);
	string line;
	cout << "Input New Password : ";
	cin >> line;
	insertMember.update_password(line);
	cout << "Input New Name : ";
	cin >> line;
	insertMember.update_name(line);
	cout << "Input New email : ";
	cin >> line;
	insertMember.update_email(line);
	cout << "Input New address : ";
	cin >> line;
	insertMember.update_address(line);

	string temp = "";
	cout << "Input New Birthday Year : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 4 && stoi(line) < 2100 & stoi(line) > 1900)
			break;
		else
			cout << "Input Correct Year : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Birthday Month : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) > 0 && stoi(line) < 13)
			break;
		else
			cout << "Input Correct Month : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Birthday Day : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) > 0 && stoi(line) < 31)
			break;
		else
			cout << "Input Correct Day : ";
	}
	temp += line;
	insertMember.update_birthday(temp.c_str());

	cout << "Input New Class : ";
	while (1)
	{
		cin >> temp;
		if (temp.compare("A") == 0 || temp.compare("B") == 0 || temp.compare("C") == 0 || temp.compare("S") == 0)
			break;
		else
			cout << "Input Correct Class : ";
	}
	insertMember.update_Class(temp.c_str());
	insertMember.update_level("9");

	char MemberFile[20] = "fileOfMember";
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<Member>MemberIdxedFile(buf, 20, 1100);
	MemberIdxedFile.Open(MemberFile);
	Member m;

	int checked = MemberIdxedFile.Read(insertMember.Key(), m);
	if (checked != -1)
		cout << "Same ID Alrleady Exists\n";
	else
	{
		MemberIdxedFile.Append(insertMember);
		cout << "Insertion Complete!\n";
	}
	MemberIdxedFile.Close();
}

void deleteMember(string IDLine)
{
	Member m;
	char MemberName[20] = "fileOfMember";
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<Member>MemberIdxedFile(buf, 20, 1100);
	MemberIdxedFile.Open(MemberName);
	bool deletedFlag = false;

	if (MemberIdxedFile.Read((char*)(IDLine.c_str()), m) != -1)
	{
		MemberIdxedFile.Delete((char*)(IDLine.c_str()), m);
		cout << "Successfully Deleted from '" << MemberName << ".dat" <<"'!\n" << endl;
		deletedFlag = true;
	}
	else 
		cout << "No Such ID." << endl << endl;
	MemberIdxedFile.Close();

	if (deletedFlag) {
		char TempfileName[20] = "temp.dat";
		char fileName[20] = "fileofPurchase.dat";

		rename(fileName, TempfileName);
		//temp.dat을 읽어서 fileOfMember.dat에 씀. 

		ifstream ifsTemp(TempfileName);
		if (ifsTemp.fail()) {
			cout << "File Open error! : " << fileName << endl;
			return;
		}
		ifsTemp.ignore(numeric_limits<streamsize>::max(), '\n');
		DelimFieldBuffer tempbuffer('|', STDMAXBUF);
		RecordFile <Purchase> TempPurchaseFile(tempbuffer);
		TempPurchaseFile.Open(TempfileName, ios::in);

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Purchase> PurchaseFile(buffer);
		PurchaseFile.Create(fileName, ios::out | ios::trunc);

		//seekg로 제일 끝으로 보낸 후, tellg로 현재 위치를 정수값으로 return
		//그렇게 하여 처음으로부터 파일 길이를 ifsLength에 저장.
		ifsTemp.seekg(0, ifsTemp.end);
		int ifsLength = ifsTemp.tellg();

		//시작 위치로 보냄. 
		ifsTemp.seekg(0, ifsTemp.beg);
		int ifsCur = ifsTemp.tellg();

		Purchase p;
		int recaddr = 0;
		int totalCnt = purchaseCnt;
		//for (ifsCur; ifsCur < ifsLength; ) {
		for(int i = 0 ; i< totalCnt ; i ++){
			int curAddr = TempPurchaseFile.Read(p, -1);

			if (p.get_member_id().compare(IDLine) == 0)
			{
				purchaseCnt--;
				continue;
			}
			else
				PurchaseFile.Write(p);

			ifsTemp.seekg(p.get_PurchaseLength(), ifsTemp.cur);
			ifsCur = ifsTemp.tellg();
		}
		TempPurchaseFile.Close();
		PurchaseFile.Close();
		ifsTemp.close();
		remove(TempfileName);
		cout << "Successfully Deleted from '" << fileName << "'!\n" << endl;
	}
}

void modifyMember(string IDLine)
{
	//새로운 데이터 입력. 
	Member insertMember;
	insertMember.update_id(IDLine);
	string line;
	cout << "Input New Password : ";
	cin >> line;
	insertMember.update_password(line);
	cout << "Input New Name : ";
	cin >> line;
	insertMember.update_name(line);
	cout << "Input New email : ";
	cin >> line;
	insertMember.update_email(line);
	cout << "Input New address : ";
	cin >> line;
	insertMember.update_address(line);

	string temp = "";
	cout << "Input New Birthday Year : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 4 && stoi(line) < 2100 & stoi(line) > 1900)
			break;
		else
			cout << "Input Correct Year : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Birthday Month : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) > 0 && stoi(line) < 13)
			break;
		else
			cout << "Input Correct Month : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Birthday Day : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) > 0 && stoi(line) < 31)
			break;
		else
			cout << "Input Correct Day : ";
	}
	temp += line;
	insertMember.update_birthday(temp.c_str());

	cout << "Input New Class : ";
	while (1)
	{
		cin >> temp;
		if (temp.compare("A") == 0 || temp.compare("B") == 0 || temp.compare("C") == 0 || temp.compare("S") == 0)
			break;
		else
			cout << "Input Correct Class : ";
	}
	insertMember.update_Class(temp.c_str());
	insertMember.update_level("9");

	char MemberFile[20] = "fileOfMember";
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<Member>MemberIdxedFile(buf, 20, 1100);
	MemberIdxedFile.Open(MemberFile);
	Member m;

	int checked = MemberIdxedFile.Read(insertMember.Key(), m);
	if (checked == -1)
		cout << "No Such ID\n";
	else
	{
		MemberIdxedFile.Update((char*)(IDLine.c_str()), insertMember);
		cout << "Modification Complete!\n";
	}
	MemberIdxedFile.Close();
}

string stringtoLenString(string IDLine, int length)
{
	int size = IDLine.size();
	string result;
	for (int i = 0; i < length - size; i++)
		result += "0";
	result +=  IDLine;
	return result;
	/*int num = stoi(IDLine);
	string result;
	long divider = pow(10,length-1);
	while (1)
	{
		switch (num / divider)
		{
		case 0:
			result += "0";
			break;
		case 1:
			result += "1";
			break;
		case 2:
			result += "2";
			break;
		case 3:
			result += "3";
			break;
		case 4:
			result += "4";
			break;
		case 5:
			result += "5";
			break;
		case 6:
			result += "6";
			break;
		case 7:
			result += "7";
			break;
		case 8:
			result += "8";
			break;
		case 9:
			result += "9";
			break;
		}
		if (result.length() == length)
			break;
		num %= divider;
		divider /= 10;
	}
	return result;*/
}

int searchGame(string IDLine, int calledFlag)
{
	//calledFlag : 1 : search에서 호출, calledFlag : 2 그 이외에 호출
	char GameFile[20] = "fileOfGame";
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<Game>GameIdxedFile(buf, GAME_LENID*sizeof(char), 1100);
	GameIdxedFile.Open(GameFile);
	Game m;

	string eightID = stringtoLenString(IDLine, 8);

	int checked = GameIdxedFile.Read((char*)(eightID.c_str()), m);
	GameIdxedFile.Close();
	if (calledFlag == 1)
	{
		if (checked == -1)
			cout << "No such ID\n";
		else
			cout << m << endl;
	}
	return checked;
}

void insertGame(string IDLine)
{
	//새로운 데이터 입력. 
	Game insertGame;
	string eigthID = stringtoLenString(IDLine, 8);
	insertGame.update_id(eigthID.c_str());
	string line;
	cout << "Input New Title : ";
	cin >> line;
	insertGame.update_title(line);

	string temp = "";
	cout << "Input New Release Year : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 4 && stoi(line) > 1900 && stoi(line) < 2100)
			break;
		else
			cout << "Input Correct Year : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Release Month : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) > 0 && stoi(line) < 13)
			break;
		else
			cout << "Input Correct Month : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Release Day : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) > 0 && stoi(line) < 31)
			break;
		else
			cout << "Input Correct Day : ";
	}
	temp += line;
	insertGame.update_releaseDate(temp.c_str());

	cout << "Input New Developer : ";
	cin >> line;
	insertGame.update_developer(line);
	cout << "Input New Platform : ";
	cin >> line;
	insertGame.update_platform(line);

	cout << "Input New Score : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) > 9)
			break;
		else
			cout << "Input 2 Words Score : ";
	}
	insertGame.update_score(line.c_str());

	cout << "Input New Price : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 3 && stoi(line) > 99)
			break;
		else
			cout << "Input 3 Words Price : ";
	}
	insertGame.update_price(line.c_str());

	char GameFile[20] = "fileOfGame";
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<Game>GameIdxedFile(buf, GAME_LENID, 1100);
	GameIdxedFile.Open(GameFile);
	Game m;

	int checked = GameIdxedFile.Read(insertGame.Key(), m);
	if (checked != -1)
		cout << "Same ID Alrleady Exists\n";
	else
	{
		GameIdxedFile.Append(insertGame);
		cout << "Insertion Complete!\n";
	}
	GameIdxedFile.Close();
}

void deleteGame(string IDLine)
{
	Game m;
	char GameName[20] = "fileOfGame";
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<Game>GameIdxedFile(buf, GAME_LENID, 1100);
	GameIdxedFile.Open(GameName);
	bool deletedFlag = false;

	string eightID = stringtoLenString(IDLine, 8);

	if (GameIdxedFile.Read((char*)(eightID.c_str()), m) != -1)
	{
		GameIdxedFile.Delete((char*)(eightID.c_str()), m);
		cout << "Successfully Deleted from '" << GameName << ".dat" << "'!\n" << endl;
		deletedFlag = true;
	}
	else
		cout << "No Such ID." << endl << endl;
	GameIdxedFile.Close();

	if (deletedFlag) {
		char TempfileName[20] = "temp.dat";
		char fileName[20] = "fileofPurchase.dat";

		rename(fileName, TempfileName);
		//temp.dat을 읽어서 fileOfGame.dat에 씀. 

		ifstream ifsTemp(TempfileName);
		if (ifsTemp.fail()) {
			cout << "File Open error! : " << fileName << endl;
			return;
		}
		ifsTemp.ignore(numeric_limits<streamsize>::max(), '\n');
		DelimFieldBuffer tempbuffer('|', STDMAXBUF);
		RecordFile <Purchase> TempPurchaseFile(tempbuffer);
		TempPurchaseFile.Open(TempfileName, ios::in);

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Purchase> PurchaseFile(buffer);
		PurchaseFile.Create(fileName, ios::out | ios::trunc);

		//seekg로 제일 끝으로 보낸 후, tellg로 현재 위치를 정수값으로 return
		//그렇게 하여 처음으로부터 파일 길이를 ifsLength에 저장.
		ifsTemp.seekg(0, ifsTemp.end);
		int ifsLength = ifsTemp.tellg();

		//시작 위치로 보냄. 
		ifsTemp.seekg(0, ifsTemp.beg);
		int ifsCur = ifsTemp.tellg();

		Purchase p;
		int recaddr = 0;

		int totalCnt = purchaseCnt;
		//for (ifsCur; ifsCur < ifsLength; ) {
		for (int i = 0; i < totalCnt; i++) {
			int curAddr = TempPurchaseFile.Read(p, -1);

			if (p.getStr_game_id().compare(stringtoLenString(IDLine, 8)) == 0)
			{
				purchaseCnt--;
				continue;
			}
			else
				PurchaseFile.Write(p);

			ifsTemp.seekg(p.get_PurchaseLength(), ifsTemp.cur);
			ifsCur = ifsTemp.tellg();
		}
		TempPurchaseFile.Close();
		PurchaseFile.Close();
		ifsTemp.close();
		remove(TempfileName);
		cout << "Successfully Deleted from '" << fileName << "'!\n" << endl;
	}
}

void modifyGame(string IDLine)
{
	//새로운 데이터 입력. 
	Game modifyingGame;
	string eightID = stringtoLenString(IDLine, 8);
	modifyingGame.update_id(eightID.c_str());
	string line;
	cout << "Input New Title : ";
	cin >> line;
	modifyingGame.update_title(line);

	string temp = "";
	cout << "Input New Release Year : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 4 && stoi(line) > 1900 && stoi(line) < 2100)
			break;
		else
			cout << "Input Correct Year : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Release Month : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) > 0 && stoi(line) < 13)
			break;
		else
			cout << "Input Correct Month : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Release Day : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) > 0 && stoi(line) < 31)
			break;
		else
			cout << "Input Correct Day : ";
	}
	temp += line;
	modifyingGame.update_releaseDate(temp.c_str());

	cout << "Input New Developer : ";
	cin >> line;
	modifyingGame.update_developer(line);
	cout << "Input New Platform : ";
	cin >> line;
	modifyingGame.update_platform(line);

	cout << "Input New Score : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) > 9)
			break;
		else
			cout << "Input 2 Words Score : ";
	}
	modifyingGame.update_score(line.c_str());

	cout << "Input New Price : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 3 && stoi(line) > 99)
			break;
		else
			cout << "Input 3 Words Price : ";
	}
	modifyingGame.update_price(line.c_str());

	char GameFile[20] = "fileOfGame";
	DelimFieldBuffer buf('|', STDMAXBUF);
	TextIndexedFile<Game>GameIdxedFile(buf, GAME_LENID, 1100);
	GameIdxedFile.Open(GameFile);
	Game m;

	int checked = GameIdxedFile.Read((char*)(eightID.c_str()), m);
	if (checked == -1)
		cout << "No Such ID\n";
	else
	{
		GameIdxedFile.Update((char*)(eightID.c_str()), modifyingGame);
		cout << "Modification Complete!\n";
	}
	GameIdxedFile.Close();
}

int searchPurchase(string IDLine, int calledFlag, int dataNum)
{
	//dataNum : 1 : Member , 2 : Game, 3 : Purchase
	//calledFlag : 1 : Admin 모드, 

	char fileName[20] = "fileofPurchase.dat";

	ifstream ifsTemp(fileName);
	if (ifsTemp.fail()) {
		cout << "File Open error! : " << fileName << endl;
		return -2;
	}
	ifsTemp.ignore(numeric_limits<streamsize>::max(), '\n');
	DelimFieldBuffer tempbuffer('|', STDMAXBUF);
	RecordFile <Purchase> TempPurchaseFile(tempbuffer);
	TempPurchaseFile.Open(fileName, ios::in);

	//seekg로 제일 끝으로 보낸 후, tellg로 현재 위치를 정수값으로 return
	//그렇게 하여 처음으로부터 파일 길이를 ifsLength에 저장.
	ifsTemp.clear();
	ifsTemp.seekg(0, ifsTemp.end);
	int ifsLength = ifsTemp.tellg();

	//시작 위치로 보냄. 
	ifsTemp.seekg(0, ifsTemp.beg);
	int ifsCur = ifsTemp.tellg();

	Purchase p;
	vector<Purchase> foundP;
	int recaddr = 0;
	string charstring;
	char charKey;
	int inputNum = 0;

	if (dataNum == 2)
		charstring = stringtoLenString(IDLine, 8);
	else if(dataNum == 3)
		charstring = stringtoLenString(IDLine, 12);
	else if (dataNum == 4)
	{
		stringstream ssInt(IDLine);
		ssInt >> inputNum;
		charKey = (char)inputNum;
	}

	if (dataNum == 4)
	{
		//key 값을 이용하여 b-tree에서 검색
		int check = bt.Search(charKey);
		//b-tree에 key 값이 존재하지 않는 경우
		if (check == -1)
			cout << "Cannot find such key" << endl;
		//if found print
		else
		{
			DelimFieldBuffer buffer('|', 1000);
			RecordFile <Purchase> RegisterFile(buffer);
			RegisterFile.Open(fileName, ios::in);
			RegisterFile.Read(p, check);
			RegisterFile.Close();
			cout << p;
			//foundP.push_back(p);
		}
	}
	else {
		//for (ifsCur; ifsCur < ifsLength; ) {
		for (int i = 0; i < purchaseCnt; i++) {
			int curAddr = TempPurchaseFile.Read(p, -1);

			//Search By Member
			if (dataNum == 1)
			{
				if (p.get_member_id().compare(IDLine) == 0)
					foundP.push_back(p);
			}
			//Search By Game
			else if (dataNum == 2)
			{
				if (p.getStr_game_id().compare(charstring) == 0)
					foundP.push_back(p);
			}
			//Search By Purchase
			else
			{
				if (p.getStr_id().compare(charstring) == 0)
					foundP.push_back(p);
			}

			ifsTemp.seekg(p.get_PurchaseLength(), ifsTemp.cur);
			ifsCur = ifsTemp.tellg();
		}
		TempPurchaseFile.Close();
		ifsTemp.close();

		if (foundP.empty())
			return -1;
		if (calledFlag == 1) {
			int size = foundP.size();
			for (int i = 0; i < size; i++)
				cout << foundP[i] << endl;
		}
		foundP.clear();
	}
	return 0;
}
void insertPurchase(string IDLine, int dataNum)
{
	//새로운 데이터 입력. 
	Purchase insertPurchase;
	string line;
	string charstring;
	int inputNum;
	char charKey;
	//Admin에서 purchase insert : 
	if (dataNum == 2)
	{
		stringstream ssInt(IDLine);
		ssInt >> inputNum;
		charKey = (char)inputNum;
		//if (searchPurchase(IDLine, 2, 3) != -1)
		if(bt.Search(charKey) != -1)
		{
			cout << "Already Exists Same Key!\n";
			return;
		}
		insertPurchase.update_key(charKey);
		//charstring = stringtoLenString(IDLine, 12);
		//insertPurchase.update_id(charstring.c_str());
	}
	else
	{
		while (1) {
		cout << "Input New Purchase ID : ";
			cin >> line;
			if (line.size() != 12)
				cout << "Input 12 lengths Purchase ID : ";
			else if (searchPurchase(line, 3, 3) == -1)
				break;
			else
				cout << "Already Exists Same ID!\n";
		}
		charstring = stringtoLenString(line, 12);
		insertPurchase.update_id(charstring.c_str());
	}
	cout << "Input New Game ID : ";
	while (1) {
		cin >> line;
		if (line.size() != 8)
			cout << "Input 8 lengths Game ID : ";
		else if (searchGame(line, 2) != -1)
			break;
		else
			cout << "Input Correct Game ID : ";
	}
	insertPurchase.update_game_id(line.c_str());

	//User에서 purchase insert
	if (dataNum == 1)
		insertPurchase.update_member_id(IDLine.c_str());
	//admin에서 purchase insert
	else {
		cout << "Input New Member ID : ";
		while (1) {
			cin >> line;
			if (searchMember(line, 2) != -1)
				break;
			else
				cout << "Input Correct Member ID : ";
		}
		insertPurchase.update_member_id(line.c_str());
	}

	string temp = "";
	cout << "Input New Year : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 4)
			break;
		else
			cout << "Input Correct Year : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Month : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) < 13)
			break;
		else
			cout << "Input Correct Month : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Day : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) < 31)
			break;
		else
			cout << "Input Correct Day : ";
	}
	temp += line;
	insertPurchase.update_date(temp.c_str());

	purchaseCnt++;
	string purchaseID = to_string(purchaseCnt);
	insertPurchase.update_id( stringtoLenString(purchaseID, 12).c_str() );

	char TempfileName[20] = "temp.dat";
	char fileName[20] = "fileofPurchase.dat";
	int recaddr;

	//dat 파일의 마지막에 레코드 삽입하고 주소 값 recaddr에 갖고옴.
	DelimFieldBuffer buffer('|', 1000);
	RecordFile<Purchase>PurchaseFile(buffer);
	PurchaseFile.Open(fileName, ios::out);
	recaddr = PurchaseFile.Append(insertPurchase);
	PurchaseFile.Close();

	//dat 파일의 주소 & key  b-tree에 저장
	bt.Insert(charKey, recaddr);
	//bt.Insert(insertPurchase.get_Key(), recaddr); //index 추가
	/*rename(fileName, TempfileName);
	//temp.dat을 읽어서 fileOfMember.dat에 씀. 

	ifstream ifsTemp(TempfileName);
	if (ifsTemp.fail()) {
		cout << "File Open error! : " << fileName << endl;
		return;
	}
	ifsTemp.ignore(numeric_limits<streamsize>::max(), '\n');
	DelimFieldBuffer tempbuffer('|', STDMAXBUF);
	RecordFile <Purchase> TempPurchaseFile(tempbuffer);
	TempPurchaseFile.Open(TempfileName, ios::in);

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Create(fileName, ios::out | ios::trunc);

	//seekg로 제일 끝으로 보낸 후, tellg로 현재 위치를 정수값으로 return
	//그렇게 하여 처음으로부터 파일 길이를 ifsLength에 저장.
	ifsTemp.seekg(0, ifsTemp.end);
	int ifsLength = ifsTemp.tellg();

	//시작 위치로 보냄. 
	ifsTemp.seekg(0, ifsTemp.beg);
	int ifsCur = ifsTemp.tellg();

	Purchase p;
	int recaddr = 0;
	
	if (dataNum == 2)
		charstring = stringtoLenString(IDLine, 12);

	//for (ifsCur; ifsCur < ifsLength; ) {
	for(int i = 0 ; i < purchaseCnt; i++){
		int curAddr = TempPurchaseFile.Read(p, -1);
		PurchaseFile.Write(p);
		ifsTemp.seekg(p.get_PurchaseLength(), ifsTemp.cur);
		ifsCur = ifsTemp.tellg();
	}
	PurchaseFile.Write(insertPurchase);
	TempPurchaseFile.Close();
	PurchaseFile.Close();
	ifsTemp.close();
	remove(TempfileName);*/

	cout << "Successfully Inserted to '" << fileName << "'!\n" << endl;
	purchaseCnt++;
}

void deletePurchase(string IDLine, int dataNum)
{
	int inputNum;
	char charKey;
	stringstream ssInt(IDLine);
	ssInt >> inputNum;
	charKey = (char)inputNum;
	//if (searchPurchase(IDLine, 2, 3) != -1)
	if (bt.Search(charKey) == -1)
	{
		cout << "No Such Key!" << endl;
		return;
	}

	char TempfileName[20] = "temp.dat";
	char fileName[20] = "fileofPurchase.dat";

	rename(fileName, TempfileName);
	//temp.dat을 읽어서 fileOfMember.dat에 씀. 

	Purchase p;
	DelimFieldBuffer buffer('|', 1000);
	RecordFile<Purchase>tempFile(buffer);
	RecordFile<Purchase>PurchaseFile(buffer);
	tempFile.Open(TempfileName, ios::in);
	PurchaseFile.Create(fileName, ios::out | ios::trunc);
	int recaddr = 0;
	//삭제하려는 것 제외 전부 쓰기. 
	while (1)
	{
		if (tempFile.Read(p) == -1)
			break;
		if (p.get_Key() == charKey)
		{
			bt.Remove(charKey);
			continue;
		}
		recaddr = PurchaseFile.Write(p);
		bt.Remove(p.get_Key());
		bt.Insert(p.get_Key(), recaddr);
	}
	tempFile.Close();
	PurchaseFile.Close();
	//bt.Remove(charKey);

	/*ifstream ifsTemp(TempfileName);
	if (ifsTemp.fail()) {
		cout << "File Open error! : " << fileName << endl;
		return;
	}
	ifsTemp.ignore(numeric_limits<streamsize>::max(), '\n');
	DelimFieldBuffer tempbuffer('|', STDMAXBUF);
	RecordFile <Purchase> TempPurchaseFile(tempbuffer);
	TempPurchaseFile.Open(TempfileName, ios::in);

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Create(fileName, ios::out | ios::trunc);

	//seekg로 제일 끝으로 보낸 후, tellg로 현재 위치를 정수값으로 return
	//그렇게 하여 처음으로부터 파일 길이를 ifsLength에 저장.
	ifsTemp.seekg(0, ifsTemp.end);
	int ifsLength = ifsTemp.tellg();

	//시작 위치로 보냄. 
	ifsTemp.seekg(0, ifsTemp.beg);
	int ifsCur = ifsTemp.tellg();

	Purchase p;
	int recaddr = 0;

	string charstring;
	if (dataNum == 2)
		charstring = stringtoLenString(IDLine, 12);

	//for (ifsCur; ifsCur < ifsLength; ) {
	int totalCnt = purchaseCnt;
	for (int i = 0; i < totalCnt; i++) {
		int curAddr = TempPurchaseFile.Read(p, -1);

		//delete By UserID
		if (dataNum == 1) {
			if (p.get_member_id().compare(IDLine) == 0)
			{
				purchaseCnt--;
				continue;
			}
			else
				PurchaseFile.Write(p);
		}
		//delete by purchase ID
		else if (dataNum == 2)
		{
			if (p.getStr_id().compare(charstring) == 0)
			{
				purchaseCnt--;
				continue;
			}
			else
				PurchaseFile.Write(p);
		}

		ifsTemp.seekg(p.get_PurchaseLength(), ifsTemp.cur);
		ifsCur = ifsTemp.tellg();
	}
	TempPurchaseFile.Close();
	PurchaseFile.Close();
	ifsTemp.close();*/
	remove(TempfileName);
	cout << "Successfully Deleted from '" << fileName << "'!\n" << endl;
}
void modifyPurchase(string IDLine, int dataNum)
{
	char fileName[20] = "fileofPurchase.dat";
	//새로운 데이터 입력. 
	Purchase modifyingPurchase;
	string line;

	int inputNum;
	char charKey;
	stringstream ssInt(IDLine);
	ssInt >> inputNum;
	charKey = (char)inputNum;
	//if (searchPurchase(IDLine, 2, 3) != -1)
	int check = bt.Search(charKey);
	if (check == -1)
	{
		cout << "No Such Key!\n";
		return;
	}
	//if found print
	else
	{
		DelimFieldBuffer buffer('|', 1000);
		RecordFile <Purchase> RegisterFile(buffer);
		RegisterFile.Open(fileName, ios::in);
		RegisterFile.Read(modifyingPurchase, check);
		RegisterFile.Close();
	}

	cout << "Look at the above records and enter the purchase ID of the record you want to change >> ";

	cout << "Input New Game ID : ";
	while (1) {
		cin >> line;
		if (line.size() != 8)
			cout << "Input 8 lengths Game ID : ";
		else if (searchGame(line, 2) != -1)
			break;
		else
			cout << "Input Correct Game ID : ";
	}
	modifyingPurchase.update_game_id(line.c_str());

	//User에서 purchase modify
	if (dataNum == 1)
		modifyingPurchase.update_member_id(IDLine.c_str());
	//admin에서 purchase modify
	else {
		cout << "Input New Member ID : ";
		while (1) {
			cin >> line;
			if (searchMember(line, 2) != -1)
				break;
			else
				cout << "Input Correct Member ID : ";
		}
		modifyingPurchase.update_member_id(line.c_str());
	}

	string temp = "";
	cout << "Input New Year : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 4)
			break;
		else
			cout << "Input Correct Year : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Month : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) < 13)
			break;
		else
			cout << "Input Correct Month : ";
	}
	temp += line;
	temp += "/";

	cout << "Input New Day : ";
	while (1)
	{
		cin >> line;
		if (line.size() == 2 && stoi(line) < 31)
			break;
		else
			cout << "Input Correct Day : ";
	}
	temp += line;
	modifyingPurchase.update_date(temp.c_str());
	bt.Remove(charKey);

	char TempfileName[20] = "temp.dat";

	rename(fileName, TempfileName);
	//temp.dat을 읽어서 fileOfMember.dat에 씀. 

	Purchase p;
	DelimFieldBuffer buffer('|', 1000);
	RecordFile<Purchase>tempFile(buffer);
	RecordFile<Purchase>PurchaseFile(buffer);
	tempFile.Open(TempfileName, ios::in);
	PurchaseFile.Create(fileName, ios::out | ios::trunc);

	//삭제하려는 것 제외 전부 쓰기. 
	int recaddr = 0;
	while (1)
	{
		if (tempFile.Read(p) == -1)
			break;
		if (p.get_Key() == charKey)
		{
			bt.Remove(charKey);
			continue;
		}
		recaddr = PurchaseFile.Write(p);
		bt.Remove(p.get_Key());
		bt.Insert(p.get_Key(), recaddr);
	}
	recaddr = PurchaseFile.Append(modifyingPurchase);
	tempFile.Close();
	PurchaseFile.Close();

	/*ifstream ifsTemp(TempfileName);
	if (ifsTemp.fail()) {
		cout << "File Open error! : " << fileName << endl;
		return;
	}
	ifsTemp.ignore(numeric_limits<streamsize>::max(), '\n');
	DelimFieldBuffer tempbuffer('|', STDMAXBUF);
	RecordFile <Purchase> TempPurchaseFile(tempbuffer);
	TempPurchaseFile.Open(TempfileName, ios::in);

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Create(fileName, ios::out | ios::trunc);

	//seekg로 제일 끝으로 보낸 후, tellg로 현재 위치를 정수값으로 return
	//그렇게 하여 처음으로부터 파일 길이를 ifsLength에 저장.
	ifsTemp.seekg(0, ifsTemp.end);
	int ifsLength = ifsTemp.tellg();

	//시작 위치로 보냄. 
	ifsTemp.seekg(0, ifsTemp.beg);
	int ifsCur = ifsTemp.tellg();

	Purchase p;
	int recaddr = 0;

	string charstring;
	
	//admin에서 modify 할 때는 IDLine이 purchase ID 갖고 있음
	if (dataNum == 2)
		charstring = stringtoLenString(IDLine, 12);
	else
		charstring = stringtoLenString(modifyingPurchase.getStr_id(), 12);

	//for (ifsCur; ifsCur < ifsLength; ) {
	for(int i = 0 ; i < purchaseCnt ; i ++){
		int curAddr = TempPurchaseFile.Read(p, -1);

		if (p.getStr_id().compare(charstring) == 0)
			PurchaseFile.Write(modifyingPurchase);
		else
			PurchaseFile.Write(p);

		ifsTemp.seekg(p.get_PurchaseLength(), ifsTemp.cur);
		ifsCur = ifsTemp.tellg();
	}
	//PurchaseFile.Append(modifyingPurchase);

	TempPurchaseFile.Close();
	PurchaseFile.Close();
	ifsTemp.close();*/
	remove(TempfileName);
	bt.Insert(charKey, recaddr);

	cout << "Successfully Modified from '" << fileName << "'!\n" << endl;
}
