#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
#include <fstream>

using namespace std;

enum Special { ʲ, ��, ��, ��, �� };

string s_special[] = { "���������� �������� ",
					   "ʳ����������",
					   "��������� �����",
					   "��������� �����",
					   "������ ���������� " };

struct student
{
	string prizv;
	int kurs;
	Special specialization;
	int phisuka;
	int matematic;
	union
	{
		int programing;
		int chuslo_metod;
		int pedahohica;
	};
};

void Create(student& s, const int kilkist, const char* fname, ofstream& file_s);
void Print(student& s, const int kilkist, const char* fname, ifstream& file_l);
double find_prozent(student& s, const int kilkist, ifstream& file_l);
int find_studend(student& s, const int kilkist, ifstream& file_l);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int kil_student;
	cout << "������ ������� ��������: "; cin >> kil_student;
	cout << endl;
	student s;

	char fname[101];
	cout << "������ ����� ��������� �����: "; cin >> fname;

	ofstream file_s(fname, ios::binary);
	Create(s, kil_student, fname, file_s);
	cout << endl;
	file_s.close();

	ifstream file_l(fname, ios::binary);
	Print(s, kil_student, fname, file_l);
	cout << endl;
	file_l.close();

	ifstream file_ll(fname, ios::binary);
	cout << "������� ��������, �� ������� ��� ����� (�� ������� � ������): " << setprecision(2) << find_prozent(s, kil_student, file_ll) << "%" << endl << endl;
	file_ll.close();

	ifstream file_lll(fname, ios::binary);
	cout << "������� ��������, �� �������� � ������ ������ '5' ��� '4': " << endl;
	if (find_studend(s, kil_student, file_lll));
	else
		cout << "������� ��������, �� �������� � ������ ������ '5' ��� '4' �� ���������: " << endl << endl;

	return 0;
}

void Create(student& s, const int kilkist, const char* fname, ofstream& file_s)
{
	int special;
	for (int i = 0; i < kilkist; i++)
	{
		cout << endl;
		cout << "������� � " << i + 1 << endl;

		cin.get();
		cin.sync();

		cout << "  �������: "; getline(cin, s.prizv);
		cout << "  ����: "; cin >> s.kurs;
		cout << "  ������������ (0 - ���������� ��������, 1 - ʳ����������, 2 - ��������� �����, 3 - ��������� �����, 4 - ������ ���������� ): "; cin >> special;
		s.specialization = (Special)special;
		cout << "  ������ � ������: "; cin >> s.phisuka;
		cout << "  ������ � ����������: "; cin >> s.matematic;
		switch (special)
		{
		case 0:
			cout << "  ������ � �������������: "; cin >> s.programing;
			break;
		case 1:
			cout << "  ������ � ��������� ������: "; cin >> s.chuslo_metod;
			break;
		case 2:
		case 3:
		case 4:
			cout << "  ������ � ���������: "; cin >> s.pedahohica;
			break;
		default:
			cout << "�� ����� ��������� ��������! " << endl;
		}
		cout << endl;

		if (!file_s.write((char*)&s, sizeof(student)))
		{
			cerr << "Error writing file." << endl;
		}
	}
}

void Print(student& s, const int kilkist, const char* fname, ifstream& file_l)
{
	cout << "============================================================================================================================"
		<< endl;
	cout << "| �  | �������     | ���� | ������������           | Գ���� | ����������  | ������������� | ������� ������ | ��������� |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;

	int i = 0;
	while (i < kilkist)
	{
		file_l.read((char*)&s, sizeof(student));
		cout << "| " << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << s.prizv;
		cout << "| " << setw(3) << right << s.kurs << "  ";
		cout << "| " << setw(23) << left << s_special[s.specialization] << " ";
		cout << "| " << setw(4) << right << s.phisuka << "   ";
		cout << "| " << setw(6) << right << s.matematic << "      ";
		switch (s.specialization)
		{
		case 0:
			cout << "| " << setw(7) << right << s.programing << "       |" << setw(18) << "|" << setw(13) << "|" << endl;
			break;
		case 1:
			cout << "| " << setw(15) << "|" << setw(10) << right << s.chuslo_metod << "       |" << setw(13) << "|" << endl;
			break;
		case 2:
		case 3:
		case 4:
			cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << s.pedahohica << "     |" << endl;
			break;
		}
		i++;
	}
	cout << "============================================================================================================================" << endl;
}

double find_prozent(student& s, const int kilkist, ifstream& file_l)
{
	int k = 0;
	for (int i = 0; i < kilkist; i++)
	{
		file_l.read((char*)&s, sizeof(student));
		if (s.phisuka > 3 && s.matematic > 3 && s.programing > 3 && s.chuslo_metod > 3 && s.pedahohica > 3)
			k++;
	}
	return 100.0 * k / kilkist;
}

int find_studend(student& s, const int kilkist, ifstream& file_l)
{
	int l = 0;
	for (int i = 0; i < kilkist; i++)
	{
		file_l.read((char*)&s, sizeof(student));
		if (s.phisuka > 3)
		{
			cout << "� " << i + 1 << " " << s.prizv << " --- � ������ " << s.phisuka << endl;
			l = 1;
		}
	}
	return l;
}