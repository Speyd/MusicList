#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std;
typedef struct {
	string text_song;
	string name_song;
	string autor_song;
	string age_song;
	int index;//Для mass_find, индекс в главном массиве(mass)
}Songs;
vector<Songs> mass;
#pragma region SpecialFunctions
void ClearScrean() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
void Enter(int choice) {
	string enter;
	if (choice != 3 && choice != 4 && choice != 5)cin.ignore();
	do {
		cout << "Нажмите enter что-бы продолжить: "; getline(cin, enter);
	} while (enter.empty() == false);
}
#pragma endregion
#pragma region File
void AmountSongs(int& amount_songs) {
	ifstream file("songs.txt");
	string text;
	while (!file.eof()) {
		getline(file, text);
		if (text.find("Number_song") == 0)amount_songs++;
	}
	file.close();
}
void InputInfoFile(vector<Songs>& mass, int choice_file) {
	int amount_songs = 0;
	if (choice_file == 1) {
		ofstream file("songs.txt");
		file.close();
	}
	else AmountSongs(amount_songs);
	fstream file("songs.txt", ios::app);
	for (int i = 0; i != mass.size(); i++) {
		file << "Number_song: " << amount_songs + i + 1 << endl;
		file << "Text_song: " << mass[i].text_song << endl;
		file << "Name_song: " << mass[i].name_song << endl;
		file << "Autor_song: " << mass[i].autor_song << endl;
		file << "Age_song: " << mass[i].age_song << endl;
		file << "=====================================" << endl;
	}
	file.close();
	/*}
	else {
		fstream file("songs.txt",ios::app);
		for (int i = 0; i != mass.size(); i++) {
			file << "Number_song: " << i + 1 << endl;
			file << "Text_song: " << mass[i].text_song << endl;
			file << "Name_song: " << mass[i].name_song << endl;

			file << "Autor_song: " << mass[i].autor_song << endl;
			file << "Age_song: " << mass[i].age_song << endl;
			file << "=====================================" << endl;
		}
		file.close();
	}*/
}
void OutInfoFile(const char* info, vector<Songs>& mass) {
	ifstream file(info);
	string text, temp_text = "";
	while (!file.eof()) {
		getline(file, text);
		if (text.find(' ') + 1 != text.size()) {
			for (int i = text.find(' ') + 1; i != text.size(); i++)temp_text += text[i];
			if (text.find("Number_song") == 0)mass.resize(mass.size() + 1);
			else if (text.find("Text_song") == 0)mass[mass.size() - 1].text_song = temp_text;
			else if (text.find("Name_song") == 0)mass[mass.size() - 1].name_song = temp_text;
			else if (text.find("Autor_song") == 0)mass[mass.size() - 1].autor_song = temp_text;
			else if (text.find("Age_song") == 0)mass[mass.size() - 1].age_song = temp_text;
			temp_text = "";
		}
	}
	file.close();
}
int CheckEmptyFile(const char* info) {
	fstream file(info);
	int sizefile = 1;
	if (file.tellg())int sizefile = 0;
	file.close();
	return sizefile;
}
void SaveInformation(vector<Songs>& mass, bool& save) {
	int choice_file = 1;
	do {
		ClearScrean();
		cout << "\t\tСохранение данных\nВыберете способ сохранения\n[1] - Сохранить с удалением всей информаци в файле\n[2] - Сохранить с сохранением всей информации в файле\n[0] - Выйти в меню\n";
		if (choice_file >= 0 && choice_file <= 2)cout << "Ваш выбор: ";
		else cout << "Нету такого выбора!\nВведите ваш выбор снова: ";
		cin >> choice_file;
	} while (choice_file < 0 || choice_file>2);
	if (choice_file == 0) {
		save = false; return;
	}
	InputInfoFile(mass, choice_file);
}
int AdditionalSave() {
	int choice = 1;
	do {
		cout << "\t\tСохранение\nЕсли вы выйдете, то данные которые были вписаные ранее пропадут\nБудем сохранять прогрес?\n[1] - Да\n[2] - Нет\n";
		if (choice >= 1 && choice <= 2)cout << "Ваш выбор: ";
		else cout << "Нету такого выбора!\nВведит ваш выбор снова: ";
		cin >> choice;
	} while (choice < 1 || choice>2);
	return choice;
}
#pragma endregion
#pragma region InputOutInfo
void InputInfoSongs(vector<Songs>& mass) {
	mass.resize(mass.size() + 1);
	cin.ignore();
	cout << "\t\tВвод новой песни" << endl;
	cout << "Введите текст песни(нажмите enter если не знаете текст): "; getline(cin, mass[mass.size() - 1].text_song);
	cout << "Введите название песни(нажмите enter если не знаете название песни): "; getline(cin, mass[mass.size() - 1].name_song);
	cout << "Введите имя автора песни(нажмите enter если не знаете имя автора): "; getline(cin, mass[mass.size() - 1].autor_song);
	cout << "Введите год написания песни(нажмите enter если не знаете год написания песни): "; getline(cin, mass[mass.size() - 1].age_song);
}
void OutInfoSongs(vector<Songs>& mass, int choice) {
	int page = 1, page_input = 1;
	for (int i = 0; i != mass.size(); i++) {
		do {
			ClearScrean();
			cout << "\t\tВыввод информаци" << endl;
			if (mass[i].text_song.empty())cout << "Текст песни: Данные отсутствуют" << endl << endl;
			else {
				cout << "Текст песни:" << endl;
				for (int l = 0; l != mass[i].text_song.size(); l++) {
					if (mass[i].text_song[l] == '\\' && l < mass[i].text_song.size() - 1 && mass[i].text_song[l + 1] == 'n')cout << endl;
					else if (l > 0 && mass[i].text_song[l - 1] == '\\' && mass[i].text_song[l] == 'n')continue;
					else cout << mass[i].text_song[l];
				}
				cout << endl << endl;
			}
			if (mass[i].name_song.empty())cout << "Имя песни: Данные отсутствуют" << endl << endl;
			else cout << "Имя песни: " << mass[i].name_song << endl << endl;
			if (mass[i].autor_song.empty())cout << "Автор песни песни: Данные отсутствуют" << endl << endl;
			else cout << "Автор песни: " << mass[i].autor_song << endl << endl;
			if (mass[i].age_song.empty())cout << "Год написания песни: Данные отсутствуют" << endl << endl;
			else cout << "Год написания песни: " << mass[i].age_song << endl << endl;
			cout << page << " песня из " << mass.size() << endl;
			if (page == 1 && mass.size() > 1)cout << "[1] - К следуйщей песни\n[0] - Выйти в меню";
			else if (page == mass.size() && mass.size() > 1)cout << "[1] - К предыдущей песни\n[0] - Выйти в меню";
			else if (page > 1 && page < mass.size() && mass.size() > 3)cout << "[1] - К следуйщей песни	    |	  [2] - К предыдущей песни\n[0] - Выйти в меню";
			else {
				Enter(choice);
				return;
			}
			if (page == 1 && mass.size() > 1 && page_input == 1)cout << "\nВаш выбор: ";
			else if (page == mass.size() && mass.size() > 1 && page_input == 1)cout << "\nВаш выбор: ";
			else if (page > 1 && page < mass.size() && page_input == 1 || page > 1 && page < mass.size() && page_input == 2)cout << "Ваш выбор: ";
			else  cout << "\nНету такого выбора!\nВведите ваш выбор снова: ";
			cin >> page_input;
			if (page_input == 0)return;
			else if (page == 1 && mass.size() > 1 && page_input == 1)continue;
			else if (page == mass.size() && mass.size() > 1 && page_input == 1)continue;
			else if (page > 1 && page < mass.size() && page_input == 1 || page > 1 && page < mass.size() && page_input == 2)continue;
			else  page_input = 3;
			//} while (page_input == 3);
		} while (page_input == 3);
		if (page == 1 && page_input == 1 || page > 1 && page < mass.size() && page_input == 1)page++;
		else if (page == mass.size() || page > 1 && page < mass.size() && page_input == 2) { page--; i -= 2; }
	}
}
#pragma endregion
#pragma region ChangeInfoMass
void  ChangeDeleteInfoSongs(vector<Songs>& mass, int index_find, int choice) {
	int choice_change = 0;
	vector<int> mass_change;
	do {
		do {
			ClearScrean();
			if (choice == 3)cout << "\tИзменение информаци\nИзменять будем...\n";
			else cout << "\tУдаление информаци\nУдалять будем...\n";
			cout << "[1] - Название песни\n[2] - Автора песни\n[3] - Текст песни\n[4] - Год написания песни\n[5] - Всю информацию\n";
			if (choice == 3)cout << "[6] - Перейти к изменениям\n[0] - Выход в меню\n";
			else if (choice == 4)cout << "[6] - Перейти к удалениям\n[0] - Выход в меню\n";
			if (choice_change >= 0 && choice_change <= 6)cout << "Ваш выбор: ";
			else cout << "Нету такого выбора!\nВведите ваш выбор снова: ";
			cin >> choice_change;
		} while (choice_change < 0 || choice_change>6);
		if (choice_change == 0)return;
		else if (choice_change == 6 && mass_change.size() == 0) {
			if (choice == 3)cout << "Что-бы перейти к изменению, нужно выбрать что изменять!" << endl;
			else cout << "Что-бы перейти к удалению, нужно выбрать что удалять!" << endl;
			choice_change = 1;
			Enter(1);
		}
		else if (choice_change == 5) {
			mass_change.resize(1);
			mass_change[0] = 5;
		}
		else if (choice_change >= 1 && choice_change <= 4) {
			for (int i = 0; i != mass_change.size(); i++) {
				if (choice_change == mass_change[i]) {
					cout << "Этот выбор вы уже ввели!" << endl;
					Enter(1);
					choice_change = 0;
					break;
				}
			}
			if (choice_change != 0) {
				mass_change.resize(mass_change.size() + 1);
				mass_change[mass_change.size() - 1] = choice_change;
			}
		}
	} while (choice_change != 5 && choice_change != 6);
	ClearScrean();
	if (choice == 3) {
		cout << "\tИзменение информаци\n";
		cin.ignore();
		for (int i = 0; i != mass_change.size(); i++) {
			if (mass_change[i] == 1 || mass_change[i] == 5) {
				cout << "Введите новое название песни: ";
				getline(cin, mass[index_find].name_song);
			}
			if (mass_change[i] == 2 || mass_change[i] == 5) {
				cout << "Введите новое имя автора: ";
				getline(cin, mass[index_find].autor_song);
			}
			if (mass_change[i] == 3 || mass_change[i] == 5) {
				cout << "Введите новый текст песни: ";
				getline(cin, mass[index_find].text_song);
			}
			if (mass_change[i] == 4 || mass_change[i] == 5) {
				cout << "Введите новый год написание песни: ";
				getline(cin, mass[index_find].age_song);
			}
		}
		cout << "Инфрмация успешно изменена!" << endl;
		Enter(choice);
	}
	else {
		cout << "\tУдаление информаци\n";
		for (int i = 0; i != mass_change.size(); i++) {
			if (mass_change[i] == 1)mass[index_find].name_song = "";
			else if (mass_change[i] == 2)mass[index_find].autor_song = "";
			else if (mass_change[i] == 3)mass[index_find].text_song = "";
			else if (mass_change[i] == 4)mass[index_find].age_song = "";
			else if (mass_change[i] == 5) {
				swap(mass[index_find], mass[mass.size() - 1]);
				mass.resize(mass.size() - 1);

			}
		}
		cout << "Инфрмация успешно удалена!" << endl;
		Enter(1);
	}
}
void FindSongsInMass(vector<Songs>& mass, int choice) {
	vector<Songs> mass_find;
	int choice_find = 0, check = 0, index_find = 0;
	bool checktrue_index = false;
	string name_song, autor_song;
	do {
		ClearScrean();
		if (choice == 3)cout << "\tИзменение информаци\n";
		else if (choice == 4)cout << "\tУдаление ифнормации\n";
		else cout << "\tПоиск информации\n";
		cout << "Ищем песню по...\n[1] - Названии песни\n[2] - Имя автора\n[3] - Названии песни и имя автора\n[0] - Выход в меню\n";
		if (choice_find >= 0 && choice_find <= 3)cout << "Ваш выбор: ";
		else cout << "Нету такого выбора!\nВведите ваш выбор внова: ";
		cin >> choice_find;
	} while (choice_find < 0 || choice_find > 3);
	if (choice_find == 0)return;
	cin.ignore();
	if (choice_find == 1 || choice_find == 3) { cout << "Введите название песни для поиска: "; getline(cin, name_song); }
	if (choice_find == 2 || choice_find == 3) { cout << "Введите имя автора для поиска: "; getline(cin, autor_song); }
	for (int i = 0; i != mass.size(); i++) {
		if (choice_find == 1 && mass[i].name_song == name_song)check = 1;
		else if (choice_find == 2 && mass[i].autor_song == autor_song)check = 1;
		else if (choice_find == 3 && mass[i].name_song == name_song && mass[i].autor_song == autor_song)check = 1;
		if (check == 1) {
			mass_find.resize(mass_find.size() + 1);
			if (choice_find == 1 || choice_find == 3) {
				mass_find[mass_find.size() - 1].name_song = name_song;
				mass_find[mass_find.size() - 1].autor_song = mass[i].autor_song;
			}
			if (choice_find == 2 || choice_find == 3) {
				mass_find[mass_find.size() - 1].autor_song = autor_song;
				mass_find[mass_find.size() - 1].name_song = mass[i].autor_song;
			}
			mass_find[mass_find.size() - 1].text_song = mass[i].text_song;
			mass_find[mass_find.size() - 1].age_song = mass[i].age_song;
			mass_find[mass_find.size() - 1].index = i;
			check = 0;
		}
	}
	if (mass_find.size() == 0 || mass_find.size() == 1) {
		if (mass_find.size() == 0)cout << "В списке нету такой песни с ";
		else {
			index_find = mass_find[0].index;
			cout << "Песня с ";
		}
		if (choice_find == 1 || choice_find == 3) {
			if (!name_song.empty())cout << "названием(" << name_song << ")";
			else cout << "названием(Данные отсутствуют)";
		}
		if (choice_find == 2) {
			if (!autor_song.empty())cout << " именнем автора(" << autor_song << ")";
			else cout << " именем автора(Данные отсутствуют)";
		}
		if (choice_find == 3) {
			if (!autor_song.empty())cout << " и с именнем автора(" << autor_song << ")";
			else cout << " и с именем автора(Данные отсутствуют)";
		}
		if (mass_find.size() == 0)cout << endl;
		else cout << ", находить на " << mass_find[0].index + 1 << "-ым местом в списке песен" << endl;
		Enter(choice);
		if (mass_find.size() == 0)return;
	}
	else if (mass_find.size() > 1) {
		do {
			ClearScrean();
			if (choice == 3)cout << "\tИзменение информаци\n";
			else if (choice == 4) cout << "\tУдаление ифнормации\n";
			else cout << "\tПоиск информации\n";
			if (choice_find == 1 || choice_find == 3) {
				cout << "Все песни в списке с названием(";
				if (!name_song.empty())cout << name_song << ")";
				else cout << "Данные отсутсвують)";
			}
			if (choice_find == 2) {
				cout << "Все песни в списке с именем автора(";
				if (!autor_song.empty())cout << autor_song << ")";
				else cout << "Данные отсутсвуют)";
			}
			if (choice_find == 3) {
				cout << ") и с именнем автора(";
				if (!autor_song.empty())cout << autor_song << ")";
				else cout << "Данные отсутсвуют";
			}
			cout << endl << endl;
			for (int i = 0; i != mass_find.size(); i++) {
				cout << mass_find[i].index + 1 << "-ая песня в спике\nНазвание песни: ";
				if (!name_song.empty())cout << name_song;
				else cout << "Данные отсутсвують";
				cout << "\nАвтор песни : ";
				if (!autor_song.empty())cout << autor_song;
				else cout << "Данные отсутсвуют";
				cout << "\nТекст песни:\n";
				if (!mass[mass_find[i].index].text_song.empty())cout << mass[mass_find[i].index].text_song;
				else cout << "Данные отсутсвують";
				cout << "\nГод выпуска песни: ";
				if (!mass[mass_find[i].index].age_song.empty())cout << mass[mass_find[i].index].age_song;
				else cout << "Данные отсутсвуют";
				cout << endl << endl;
			}
			for (int i = 0; i != mass_find.size(); i++) {
				if (index_find == mass_find[i].index)break;
				else if (i == mass_find.size() - 1) index_find = 0;
			}
			if (index_find == 0) {
				if (checktrue_index == false)cout << "Ваш выбор: ";
				else cout << "Нету такого выбора!\nВведите ваш выбор снова: ";
				cin >> index_find;
				checktrue_index = true;
			}
			else break;
		} while (true);
		Enter(choice);
	}
	if (choice != 5)ChangeDeleteInfoSongs(mass, index_find, choice);
}
#pragma endregion
int main() {
	setlocale(0, "Rus");
	int choice = 1;
	bool save = false;
	do {
		cout << "\t\tГлавное меню\n[1] - Взять всю информацию об песни(-ен) из файла\n[2] - Добавить всю информацию об песни(-ен) самому\n[0] - Выйти\n";
		if (choice >= 0 && choice <= 2)cout << "Ваш выбор: ";
		else cout << "Нету такого выбора!\nВведит ваш выбор снова: ";
		cin >> choice;
	} while (choice < 0 || choice>2);
	if (choice == 1) {
		if (CheckEmptyFile("songs.txt") != 0) {
			OutInfoFile("songs.txt", mass);
			cout << "Информация с файле успешно считана!" << endl;
		}
		else cout << "С файл не возможно считать информацию, он пуст!" << endl;;
		Enter(choice);
	}
	ClearScrean();
	do {
		do {
			ClearScrean();
			cout << "\tКаталог песен\n[1] - Вывод информаци\n[2] - Добавить новую песню\n[3] - Изменение информации\n[4] - Удаление информации\n[5] - Поиск песни\n[6] - Записать инофрмацию в файл\n[0] - Выйти\n";
			if (choice >= 0 && choice <= 5)cout << "Вваш выбор: ";
			else cout << "Нету такого выбора!\nВведит ваш выбор снова: ";
			cin >> choice;
		} while (choice < 0 || choice>5);
		ClearScrean();
		switch (choice) {
		case 0:
			if (save == false && AdditionalSave() == 1)SaveInformation(mass, save);
			break;
		case 1:save = false; OutInfoSongs(mass, choice); break;
		case 2:save = false; InputInfoSongs(mass); break;
		case 3:FindSongsInMass(mass, choice); break;
		case 4:FindSongsInMass(mass, choice); break;
		case 5:FindSongsInMass(mass, choice); break;
		case 6:save = true; SaveInformation(mass, save); break;
		}
	} while (choice != 0);
	return 0;
}