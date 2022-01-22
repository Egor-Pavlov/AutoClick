#include <iostream>
#include <vector>
#include "windows.h"
#include <fstream>

using namespace std;
vector<POINT> points;
POINT cursor_position;
double delay;
ostream& operator << (ostream& out, vector<POINT>& points)
{
	out <<" points: [ "<< points.size()<< " ";
	for (int i = 0; i < points.size(); i++)
	{
		out << points[i].x << " ; " << points[i].y <<" ";
	}
	out << " ]\n";
	return out;
}
istream& operator >> (istream& in, vector<POINT>& points)
{
	string hps_data;
	int size = 0;
	POINT point;

	in >> hps_data;
	if (hps_data != "points:")
		return in;

	points.clear();
	
	in >> hps_data;
	if (hps_data == "[")
	{
		in >> size;
	}

	for (int i = 0; i < size; i++)
	{
		in >> point.x;
		in >> hps_data;
		if (hps_data == ";")
			in >> point.y;
		
		points.push_back(point);
	}
	return in;
}
void init()
{
	string enter;

	while (true)
	{
		cout << "�������� ������ �� �������, ������� ������ ��������� � ������� 1." << endl << "������� 0 ���� ������ ������� � ������" << endl << endl;
		cin >> enter;
		if (enter == "0")
			break;

		else if (enter == "1")
		{
			GetCursorPos(&cursor_position);
			points.push_back(cursor_position);
			cout << "������� ������� ������� ��������." << endl << endl;
			continue;
		}
		else
			cout << "������� ������������ ��������. ��������� ����." << endl;
	}
	system("cls");
}

void save_coords()
{
	string name;
	cout << "������� ��� �����: ";
	cin >> name;

	ofstream o(name);
	o << points;
}

void work()
{
	system("cls");
	cout << "�������� �������� ��������, �������� 0.1. B������ ����� �����!" << endl;
	cin >> delay;

	int count_of_clics;
	int a;
	system("cls");
	cout << "���������� � ������!" << endl << endl;

	count_of_clics = points.size();

	cout << "��� ������������ ����� �o ����������� �������� ����������� ��� ����" <<
		endl << "�������� ����� ��� ������������� � ������� ALT+TAB � ������� ����� ������. ��� ����������� � ������� ���� ������� 0" << endl;
	cin >> a;

	while (true)
	{
		system("cls");
		cout << "��� ������������ ����� �o ����������� �������� ����������� ��� ����" <<
			endl << "�������� ����� ��� ������������� � ������� ALT+TAB � ������� ����� ������. ��� ����������� � ������� ���� ������� 0" << endl;
		for (int i = 0; i < count_of_clics; i++)
		{
			SetCursorPos(points[i].x, points[i].y);
			Sleep(1000 * delay);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		cin >> a;
		if (a == 0)
			break;
	}
}

void deserealize()
{
	string name;
	cout << "������� ��� ����� � ������������:\n";
	cin >> name;
	ifstream i(name);
	i >> points;

	system("cls");
}

void main()
{
	//system("chcp 1251");
	setlocale(LC_ALL, "ru");
	while (true)
	{
		system("cls");

		string input;
		while (true)
		{
			cout <<"0. �����."<< "\n1.������� ��������� �����." << endl << "2.H�������� �����." << endl
				<< "������� �����, ����� ������� �����: ";
			cin >> input;
			if (input == "0")
				exit(0);
			else if (input == "1")
			{
				deserealize();
				break;
			}
			else if (input == "2")
			{
				init();
				cout << "������ �������� ��� ���������� ��� ����������� �������������?" << endl << "0. ���" << endl << "1. ��" << endl;
				cin >> input;

				if (input == "1")
				{
					save_coords();
					break;
				}

				else if (input == "0")
					break;

				else
					cout << "������� ������������ ��������.������� 1 ��� 0.";
				system("cls");
			}
			else
			{
				cout << "������� ������������ ��������. ������� 1 ��� 0.";
			}
		}
		work();
	}
}
