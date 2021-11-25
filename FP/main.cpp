#include "main.h"

using namespace std;

int main()
{
	int MenuNum = 0;
	string inputLine;
	ShowMenu();
	while (1)
	{
		//Menu number 입력 받음. 
		cout << "input the number of menu >>> ";
		cin >> inputLine;
		
		//Menu number int로 변환
		stringstream ssInt(inputLine);
		ssInt >> MenuNum;
		
		//Quit
		if (MenuNum == 8)
			break;
		else
		{
			switch (MenuNum)
			{
			case 1:
				showMember();
				break;
			case 2:
				showGame();
				break;
			case 3:
				showPurchase();
				break;
			case 4:
				MemberTest();
				break;
			case 5:
				GameTest();
				break;
			case 6:
				PurchaseTest();
				break;
			case 7:
				GamePurchaseSystem();
				break;
			default:
				cout << "Input Correct Number!" << endl;
				break;
			}
		}

	}


	return 0;
}