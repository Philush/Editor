#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>

void videlenie(std::string stroka);														 //videlyaet  chislas skobkami
void openFile(std::string* stroka, int& strNum, int& strNumEnd, std::string& fileName); //Otkrivaet zaranee sozdanni file
void startMenu(std::string* stroka, int& strNum, int& strNumEnd, std::string& fileName); //startovoe menu
void createFile(std::string* stroka, int& strNum, int& strNumEnd, std::string& fileName); //sozdanie file
void printStr(std::string* stroka, int& strNum, int& strNumEnd, std::string& fileName);	//pechataet na ekran text
void selectMenu(std::string* stroka, int& strNum, int& strNumEnd, std::string& fileName); //menu vibora dejstvia
void textRedactor(std::string* stroka, int &strNum, int &strNumEnd, std::string& fileName); //redaktirovanie texta
void saveFile(std::string* stroka, int& strNum, int& strNumEnd, std::string fileName); //sohranenie file
void symbolRedactor(std::string* stroka, int& strNum, int& strNumEnd, std::string fileName); //vstavka, udalenie simvola
void addSym(std::string* stroka, int& strNum, int& strNumEnd, int pl);						//dobavlenie simvola v stroku
void delSym(std::string* stroka, int& strNum, int& strNumEnd, int pl);						//udalenie simvola iz stroki
void clearMas(std::string* stroka, int& strNumEnd);											//prosto chistka massiva strok
void findInfo(std::string* stroka, int& strNum, int& strNumEnd, std::string fileName);		//poisk informacii v tekste
void spravka();																				//spravka dlya raboti s redaktorom

int main()
{
	const int N = 500;
	int strNum = 0;
	int strNumEnd = strNum;
	std::string stroka[N];
	std::string fileName;;
		
	startMenu(stroka, strNum, strNumEnd, fileName);
	   
	return 0;
}

void printStr(std::string* stroka, int& strNum, int& strNumEnd, std::string& fileName)
{
	
	for (int i = 0; i <= strNumEnd; i++)
	{
		if (strNum == i)
		{
			std::cout << "\x1b[32m";
			videlenie(stroka[i]);
			std::cout << "\x1b[0m";
		}
		else
		{
			videlenie(stroka[i]);
		}
		
	}
	std::cout << "_";
}

void videlenie(std::string stroka)
{
	std::stringstream s(stroka);
	std::string word;
	while (s >> word)
	{
		try
		{
			int number = stoi(word);
			if (std::to_string(number) == word)
			{
				std::cout << "<_" << word << "_> ";
			}
			else
			{
				std::cout << word << " ";
			}
		}
		catch (std::invalid_argument e)
		{
			std::cout << word << " ";
		}
		
	}
	std::cout << std::endl;
}

void openFile(std::string* stroka, int& strNum, int& strNumEnd, std::string& fileName)
{
	tryAgainOpen:
	system("cls");

	std::ifstream fin;
	strNum = 0;
	std::cout << "Vvedite polnoe imya faila, kotorii hotite otkrit' (file.txt)\n";
	getline(std::cin, fileName); std::cout << std::endl;
	fin.open(fileName);

	if (!fin.is_open())
	{
		std::cout << "Error!!! File not found!\n" <<
			"Hotite poprobovat' snova?\n" <<
			"1. Yes\n" <<
			"2. No\n";
		tryAgainError:
		switch (_getch())
		{
		case 49: // key 1
		{
			goto tryAgainOpen;
			break;
		}
		case 50: // key 2
		{
			fin.close();
			startMenu(stroka, strNum, strNumEnd, fileName);
			break;
		}
		default:
		{
			goto tryAgainError;
		}
		}
	}
	else
	{
		while (!fin.eof())
		{
			getline(fin, stroka[strNum]);
			
			videlenie(stroka[strNum]);
			strNum++;
			
		}
		strNumEnd = strNum;
		fin.close();

		selectMenu(stroka, strNum, strNumEnd, fileName);
	}
	

}

void startMenu(std::string* stroka, int& strNum, int& strNumEnd, std::string& fileName)
{
	system("cls");
	std::cout << "Viberete, chto vi hotite i nazhmite na nuzhnuu cifru\n" <<
		"1. Sozdat' novii file\n" <<
		"2. Otkrit' suschestvuuschii file\n" <<
		"3. Vijti iz programmi";
	tryAgainStartMenu:
 	switch (_getch())
	{
	case 49: // klavisha 1
	{
		createFile(stroka, strNum, strNumEnd, fileName);
		break;
	}
	case 50: //klavisha 2
	{
		openFile(stroka, strNum, strNumEnd, fileName);
		break;
	}
	case 51: //klavisha 3
	{
		break;
	}
	default:
		goto tryAgainStartMenu;
		break;
	}
}

void createFile(std::string* stroka, int& strNum, int& strNumEnd, std::string& fileName)
{
	system("cls");
	strNum = 0;
	strNumEnd = 0;
	textRedactor(stroka, strNum, strNumEnd, fileName);

	std::ofstream fout;
	std::cout << "\nVvedite polnoe imya, sozdavaemogo faila (file.txt)\n";
	getline(std::cin, fileName); std::cout << std::endl;
	saveFile(stroka, strNum, strNumEnd, fileName);
	
	strNumEnd = 0;
	strNum = 0;
	startMenu(stroka, strNum, strNumEnd, fileName);
}

void selectMenu(std::string* stroka, int& strNum, int& strNumEnd, std::string& fileName)
{
	std::cout << "\n\nChto bi vi hoteli sdelat'? Viberite nuzhnij variant i nazhmite na sootvetstvuuschuu cifru\n";
	std::cout << "1. Redaktirovat' tekst\n" <<
		"2. Redaktirovat' stroku\n" <<
		"3. Poisk informacii\n" <<
		"4. Sohranit' i Vernutsa v menu vibora\n" <<
		"5. Vernutsa v menu bez sohranenia";
	tryAgainSelectMenu:
	switch (_getch())
	{
	case 49: // key 1
	{
		textRedactor(stroka, strNum, strNumEnd, fileName);
		system("cls");
		strNum = -1;
		printStr(stroka, strNum, strNumEnd, fileName);
		selectMenu(stroka, strNum, strNumEnd, fileName);
		break;
	}
	case 50: // key 2
	{
		symbolRedactor(stroka, strNum, strNumEnd, fileName);
		system("cls");
		strNum = -1;
		printStr(stroka, strNum, strNumEnd, fileName);
		selectMenu(stroka, strNum, strNumEnd, fileName);
		break;
	}
	case 51: //key 3
	{
		findInfo(stroka, strNum, strNumEnd, fileName);

		std::cout << "\n\n\n";
		system("pause");

		system("cls");
		strNum = -1;
		printStr(stroka, strNum, strNumEnd, fileName);
		selectMenu(stroka, strNum, strNumEnd, fileName);
		break;
	}
	case 52: //key 4
	{
		saveFile(stroka, strNum, strNumEnd, fileName);
		startMenu(stroka, strNum, strNumEnd, fileName);
		strNumEnd = 0;
		break;
	}
	case 53: //key 5
	{
		clearMas(stroka, strNumEnd);
		startMenu(stroka, strNum, strNumEnd, fileName);
		strNumEnd = 0;
		break;
	}
	default:
	{
		goto tryAgainSelectMenu;
		break;
	}
	}
}

void textRedactor(std::string* stroka, int& strNum, int& strNumEnd, std::string& fileName)
{
	system("cls");
	spravka();
	bool tr = true;
	int letter;
	strNum = 0;
	printStr(stroka, strNum, strNumEnd, fileName);
	while (tr == true)
	{
		switch (letter = _getch())
		{
		case 32: //probel
		{
			stroka[strNum] += " ";
			system("cls");
			spravka();

			printStr(stroka, strNum, strNumEnd, fileName);
			break;
		}
		case 8: //backspace
		{
			if (stroka[strNum].size() == 0 && strNum > 0)
			{
				strNum--;
			}
			else
			{
				stroka[strNum] = stroka[strNum].substr(0, stroka[strNum].size() - 1);
			}
			system("cls");
			spravka();
			printStr(stroka, strNum, strNumEnd, fileName);
			break;
		}
		case 9: //tab
		{
			tr = false;
			break;
		}
		case 13: //Enter
		{
			strNum += 1;
			strNumEnd = strNum > strNumEnd ? strNum : strNumEnd; //upravlenie posledney strokoj
			system("cls");
			spravka();
			printStr(stroka, strNum, strNumEnd, fileName);
			break;
		}
		case 27: //Esc
		{
			strNum = strNum > 0 ? (strNum - 1) : strNum;
			system("cls");
			spravka();
			printStr(stroka, strNum, strNumEnd, fileName);
			break;
		}

		case 96: // key ` (na klaviature pered 1)
		{
			strNumEnd += 1;
			std::string temp;
			for (int i = strNumEnd; i > strNum + 1; i--)
			{
				temp = stroka[i];
				stroka[i] = stroka[i - 1];
				stroka[i - 1] = temp;
			}
			system("cls");
			spravka();
			printStr(stroka, strNum, strNumEnd, fileName);
			break;
		}
		case 126: // key ~ (shift + `)
		{
			
			for (int i = strNum; i < strNumEnd; i++)
			{
				stroka[i] = stroka[i + 1];
			}
			stroka[strNumEnd] = "";

			strNumEnd = strNumEnd > 0 ? (strNumEnd - 1) : strNumEnd;
			strNum = strNum > strNumEnd ? strNumEnd : strNum;
			system("cls");
			spravka();
			printStr(stroka, strNum, strNumEnd, fileName);
			break;
		}
		default:
		{
			stroka[strNum] += (char)letter;
			system("cls");
			spravka();
			printStr(stroka, strNum, strNumEnd, fileName);
			break;
		}
		}
	}
}

void saveFile(std::string* stroka, int& strNum, int& strNumEnd, std::string fileName)
{
	std::ofstream fout;

	fout.open(fileName, std::ios::out | std::ios::trunc);

	if (!fout.is_open())
	{
		std::cout << "Error!!! File didn't open";
	}
	else
	{
		for (int i = 0; i <= strNumEnd; i++)
		{
			if (stroka[i] != "")
			{
				fout << stroka[i] << std::endl;
			}
			
		}
	}
	fout.close();
	clearMas(stroka, strNumEnd);
}

void symbolRedactor(std::string* stroka, int& strNum, int& strNumEnd, std::string fileName)
{
	system("cls");
	printStr(stroka, strNum, strNumEnd, fileName);
	
	std::cout << std::endl << std::endl <<
		"Chto bi vi hoteli sdelat'? Viberite nuzhnij variant i nazhmite na sootvetstvuuschuu cifru\n" <<
		"1. Dobavit' simvol v nachalo\n" <<
		"2. Dobavit' simvol v konec\n" <<
		"3. Dobavit' simvol v seredinu\n" <<
		"4. Udalit' simvol v nachale\n" <<
		"5. Udalit' simvol v konce\n" <<
		"6. Udalit' simvol v seredine\n" <<
		"7. Back\n\n";

tryAgainSymbol:
	switch (_getch())
	{
	case 49: //key 1
	{
		addSym(stroka, strNum, strNumEnd, 1);
		break;
	}
	case 50: //key 2
	{
		addSym(stroka, strNum, strNumEnd, 2);
		break;
	}
	case 51: //key 3
	{
		addSym(stroka, strNum, strNumEnd, 3);
		break;
	}
	case 52: //key 4
	{
		delSym(stroka, strNum, strNumEnd, 1);
		break;
	}
	case 53: //key 5
	{
		delSym(stroka, strNum, strNumEnd, 2);
		break;
	}
	case 54: //key 6
	{
		delSym(stroka, strNum, strNumEnd, 3);
		break;
	}
	case 55: //key 7
	{
		break;
	}
	default:
	{
		goto tryAgainSymbol;
		break;
	}
	}

}

void addSym(std::string* stroka, int& strNum, int& strNumEnd, int pl)
{

	std::cout << std::endl;
	for (int i = 0; i < strNumEnd; i++)
	{
		std::cout << i + 1 << ". " << stroka[i] << std::endl;
	}
	std::cout << "\nVvedite nomer stroki i nazhmite Enter \n";
	int strN;
	std::cin >> strN; 

	system("cls");

	std::cout << stroka[strN - 1] << std::endl << "\nVvedite simvol dlya vstavki\n";

	std::string symb = "";
	symb = (char)_getch();

	switch (pl)
	{
	case 1: //nachalo
	{
		stroka[strN - 1] = symb + stroka[strN - 1];
		break;
	}
	case 2: //konec
	{
		stroka[strN - 1] += symb;
		break;
	}
	case 3: //seredina
	{
		std::cout << "\nVvedite index vstavki i nazhmite Enter (otschet nachinayatsya s 0): ";
		int index;
		std::cin >> index;
		stroka[strN - 1].insert(index, symb);
		break;
	}
	}


}

void delSym(std::string* stroka, int& strNum, int& strNumEnd, int pl)
{
	std::cout << std::endl;
	for (int i = 0; i < strNumEnd; i++)
	{
		std::cout << i + 1 << ". " << stroka[i] << std::endl;
	}
	std::cout << "\nVvedite nomer stroki i nazhmite Enter \n";
	int strN;
	std::cin >> strN;

	system("cls");

	std::cout << stroka[strN - 1] << std::endl;

	switch (pl)
	{
	case 1: //nachalo
	{
		stroka[strN - 1].erase(0, 1);
		break;
	}
	case 2: //konec
	{
		stroka[strN - 1].erase(stroka[strN - 1].size() - 1, 1);
		break;
	}
	case 3: //seredina
	{
		std::cout << "\nVvedite index udalenia i nazhmite Enter (otschet nachinayatsya s 0): ";
		int index;
		std::cin >> index;
		stroka[strN - 1].erase(index, 1);
		break;
	}
	}

}

void clearMas(std::string* stroka, int& strNumEnd)
{
	for (int i = 0; i <= strNumEnd; i++)
	{
		stroka[i] = "";
	}
}

void findInfo(std::string* stroka, int& strNum, int& strNumEnd, std::string fileName)
{
	system("cls");
	strNum = -1;
	printStr(stroka, strNum, strNumEnd, fileName);

	std::cout << std::endl << std::endl <<
		"Vvedite to, chto vi hoteli bi najti v tekste:    ";
	std::string finder;

	getline(std::cin, finder);

	for (int i = 0; i < strNumEnd; i++)
	{
		for (int j = 0; j < stroka[i].size(); j++)
		{
			if (stroka[i].substr(j, finder.size()) == finder)
			{
				std::cout << "\x1b[32m" << finder << "\x1b[0m";
				j = j + finder.size() - 1;
			}
			else
			{
				std::cout << stroka[i][j];
			}
		}
		std::cout << std::endl;
	}
}

void spravka()
{
	std::cout << "Pishite suda text, Enter - sleduuschaya stroka; Esc - prediduschaya stroka; BackSpace - steret' simvol; \n" <<
		"` - sozdat' novuu strochku posle aktivnoj (pered klavishey 1); shift + ` -- udalit' aktivnuu strochku\n" <<
		"Tab - zakonchit' zapis' v file;\n\n";
}