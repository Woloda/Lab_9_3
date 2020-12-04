#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum measurement { МГ, Г, ЦН, КГ, ТТ };

string t_measurement[] = { "Мг ",
					       "Гр",
					       "Цн",
					       "Кг",
					       "Тн" };

struct towar
{
	string n_towar;
	int vartіst;
	int kilkist;
	measurement units;
	int masa;
};

void Create_towar(towar* s, const int kil_towar, int i);
void Print_towar(towar* s, const int kil_towar, int i);
towar* vulychenya(towar* s, int& kil_towar, int pozution);
void Sort(towar* s, const int kil_towar, const int zmina);
int BinSearch_towar(towar* s, const int kil_towar, const string nazwa_towar);
void BinSearch_vartist(towar* s, const int kil_towar, const int vartisr1, const int vartisr2, int& l1, int& l2);
void SaveToFile(towar* s, const int kil_towar, const char* filename);
void LoadFromFile(towar*& s, int& kil_towar, const char* filename);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int kil_towar;
	cout << "Введіть початкову кількість товарів: "; cin >> kil_towar;
	cout << endl;
	int soxr_towar = kil_towar;
	towar* s = new towar[kil_towar + 1000];

	int i, g, pos, zmina, found, index;
	int l1 = 0, l2 = 0;
	int vartisr1, vartisr2;
	string nazwa_towar;
	char filename[100];

	int menutowar;
	do {
		cout << "Виберіть дію:" << endl << endl;

		cout << " [1] - створення списку товарів" << endl;
		cout << " [2] - вивід інформації про товар" << endl;
		cout << " [3] - добавлення товару" << endl;
		cout << " [4] - вулучення товару" << endl;
		cout << " [5] - редагування інформації про товар" << endl;
		cout << " [6] - сортування товару" << endl;
		cout << " [7] - пошук товару за назвою і вивід інформації про товар" << endl;
		cout << " [8] - вивід інформації про товари із заданого діапазону вартості" << endl;
		cout << " [9] - запис даних у файл" << endl;
		cout << " [10] - зчитування даних із файлу" << endl << endl;

		cout << " [0] - вихід та завершення роботи програми" << endl << endl;

		cout << "Введіть пункт меню: "; cin >> menutowar;
		switch (menutowar)
		{
		case 1:
			kil_towar = soxr_towar;
			Create_towar(s, kil_towar, 0);
			break;
		case 2:
			cout << endl;
			Print_towar(s, kil_towar, 0);
			break;
		case 3:
			cout << endl;
			cout << "Введіть певну кількість товарів які ви хочете добавити до списку: "; cin >> g;
			cout << endl;
			kil_towar += g;
			i = kil_towar - g;
			Create_towar(s, kil_towar, i);
			break;
		case 4:
			cout << endl;
			cout << "Введіть певну позицію товару для вилучення його зі списку: "; cin >> pos;
			cout << endl;
			s = vulychenya(s, kil_towar, pos);
			break;
		case 5:
			cout << endl;
			cout << "Введіть певну позицію товару для редагування його інформації в списку: "; cin >> pos;
			cout << endl;
			i = pos;
			Create_towar(s, i, i - 1);
			break;
		case 6:
			cout << endl;
			cout << "Сортування по назві товару(спосіб 1) або за загальною вартістю(спосіб 0): " << endl;
			cout << "Виберіть певний спосіб(1 або 0): ";cin >> zmina;
			cout << endl;
			Sort(s, kil_towar, zmina);
			break;
		case 7:
			cout << endl;
			cin.get();
			cin.sync();
			cout << "Введіть назву товару: ";getline(cin, nazwa_towar);
			cout << endl;
			found = BinSearch_towar(s, kil_towar, nazwa_towar);
			if (found != -1)
			{
				cout << "Інформація про товар: " << endl << endl;
				Print_towar(s, found + 1, found);
			}
			else
				cout << "Введеного вами товару в списку не знайшлося: " << endl << endl;
			break;
		case 8:
			cout << "Діапазон вартості: " << endl << endl;
			cout << "Введіть мінімальну вартість: ";
			cin >> vartisr1;
			cout << "Введіть максимальну вартість: ";
			cin >> vartisr2;
			l1 = -1;
			l2 = -2;
			BinSearch_vartist(s, kil_towar, vartisr1, vartisr2, l1, l2);
			Print_towar(s, l2 + 1, l1);
			break;
		case 9:
			cin.get();
			cin.sync();
			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			SaveToFile(s, kil_towar, filename);
			break;
		case 10:
			cin.get();
			cin.sync();
			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			LoadFromFile(s, kil_towar, filename);
			break;
		case 0:
			cout << "завершення роботи програми" << endl << endl;
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
		cout << endl;
	} while (menutowar != 0);
	delete[] s;
}

void Create_towar(towar* s, const int kil_towar, int i)
{
	int towar;
	for (; i < kil_towar; i++)
	{
		cout << endl;
		cout << "товар № " << i + 1 << endl;

		cin.get();
		cin.sync();

		cout << "  назва: "; getline(cin, s[i].n_towar);
		cout << "  вартість(в грн.): "; cin >> s[i].vartіst;
		cout << "  кількість: "; cin >> s[i].kilkist;
		cout << "  одиниці вимірювання(0 - Міліграм, 1 - Грам, 2 - Центнер, 3 - Кілограм, 4 - Тонна): "; cin >> towar;
		s[i].units = (measurement)towar;
		cout << "  упаковка по: "; cin >> s[i].masa; cout << "  " << t_measurement[towar] << endl;
	}
}

void Print_towar(towar* s, const int kil_towar, int i)
{
	cout << "====================================================================="
		<< endl;
	cout << "| №  | Назва        | Вартість(в грн.) | Кількість | упаковка по    |"
		<< endl;
	cout << "---------------------------------------------------------------------" << endl;

	for (; i < kil_towar; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s[i].n_towar
			<< "| " << setw(16) << left << s[i].vartіst << " "
			<< "| " << setw(5) << left << s[i].kilkist << "     "
			<< "| " << setw(2) << left << s[i].masa << setw(1) << left << " " << setw(11) << left << t_measurement[s[i].units] <<  " |" << endl;
	}
	cout << "=====================================================================" << endl;
}

towar* vulychenya(towar* s, int& kil_towar, int pozution)
{
	towar* l = new towar[kil_towar + 1000];
	int j = 0;

	for (int i = 0; i < kil_towar; i++)
	{
		if (i + 1 != pozution)
		{
			l[j++] = s[i];
		}
		else;
	}

	kil_towar = kil_towar - 1;
	return l;
}

void Sort(towar* s, const int kil_towar, const int zmina)
{
	towar tmp;
	for (int i0 = 0; i0 < kil_towar - 1; i0++)
		for (int i1 = 0; i1 < kil_towar - i0 - 1; i1++)
		{
			if (zmina)
				if (s[i1].n_towar > s[i1 + 1].n_towar)
				{
					tmp = s[i1];
					s[i1] = s[i1 + 1];
					s[i1 + 1] = tmp;
				}
				else;
			else
				if (s[i1].vartіst > s[i1 + 1].vartіst)
				{
					tmp = s[i1];
					s[i1] = s[i1 + 1];
					s[i1 + 1] = tmp;
				}
		}
}

int BinSearch_towar(towar* s, const int kil_towar, const string nazwa_towar)
{
	int L = 0, R = kil_towar - 1, m;
	do {
		m = (L + R) / 2;
		if (s[m].n_towar == nazwa_towar)
			return m;
		if (s[m].n_towar > nazwa_towar)
		{
			R = m - 1;
		}
		else
		{
			L = m + 1;
		}
	} while (L <= R);
	return -1;
}

void BinSearch_vartist(towar* s, const int kil_towar, const int vartisr1, const int vartisr2, int& l1, int& l2)
{
	int g = 0;
	for (int i = 0; i < kil_towar; i++)
	{
		if (s[i].vartіst >= vartisr1 && s[i].vartіst <= vartisr2)
		{
			l2 = i;
			g++;
		}
		if (g == 1)
			l1 = l2;
	}
}

void SaveToFile(towar* s, const int kil_towar, const char* filename)

{
	ofstream fout(filename, ios::binary);              // відкрили бінарний файл запису
	fout.write((char*)&kil_towar, sizeof(kil_towar));                  // записали кількість елементів
	for (int i = 0; i < kil_towar; i++)
		fout.write((char*)&s[i], sizeof(towar));       // записали елементи масиву
	fout.close();                                      // закрили файл
}
void LoadFromFile(towar*& s, int& kil_towar, const char* filename)
{
	delete[] s;                                         // знищили попередні дані
	ifstream fin(filename, ios::binary);                // відкрили бінарний файл зчитування
	fin.read((char*)&kil_towar, sizeof(kil_towar));                     // прочитали кількість елементів
	s = new towar[kil_towar];                                   // створили динамічний масив
	for (int i = 0; i < kil_towar; i++)
		fin.read((char*)&s[i], sizeof(towar));          // прочитали елементи масиву
	fin.close();                                        // закрили файл
}