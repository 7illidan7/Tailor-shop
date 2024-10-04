#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <Windows.h>
using namespace std;


struct
{
	char name[64];  // ��������
	int price;  // ����
	char recomendtkan[64];//������������� �����
	char description[1024];  // �������� ������
}model;

struct
{
	char name[64]; // ��������
	int price;  // ����
	char description[1024];  // �������� �����
}tkan;


struct
{
	char name[64];  // ��������
	char tkantype[64]; // �� ����� ����� �������
	int term;  // ���� ������������(����)
	int sum;  // ����
}zakaz;

// ������� ��������� 2 �������
bool sameStr(char* str1, char* str2)
{
	while (*str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return 0;
		}
		str1++;
		str2++;
	}
	return 1;
}


// ������� ��������� ������
void add(FILE* out, char* choise)
{
	// � ����������� �� ��������� choise
	// ����� ���������� ������ ���� ������
	if (sameStr((char*)"������", choise))
	{
		out = fopen("Katmodel.bin", "a");
		fseek(out, 0, SEEK_END);

		cout << "������� �������� ������: ";
		cin.getline(model.name, 64);
		cout << "������� ���� ������� ������(� ������): ";
		cin >> model.price;
		cin.ignore();
		cout << "������� ������������� ����� ��� ������: ";
		cin.getline(model.recomendtkan, 64);
		cout << "������� ������� �������� ������(�� �����): ";
		cin.getline(model.description, 1024, '.');
		cin.ignore();
		fwrite(&model, sizeof(model), 1, out);
	}
	else if (sameStr((char*)"�����", choise))
	{
		out = fopen("Kattkan.bin", "a");
		fseek(out, 0, SEEK_END);
		cout << "������� �������� �����: ";
		cin.getline(tkan.name, 64);
		cout << "������� ���� ������� ������(� ������): ";
		cin >> tkan.price;
		cin.ignore();
		cout << "������� ������� �������� ������(�� �����): ";
		cin.getline(tkan.description, 1024, '.');
		cin.ignore();
		fwrite(&tkan, sizeof(tkan), 1, out);
	}
	else if (sameStr((char*)"�����", choise))
	{
		out = fopen("Zakazy.bin", "a");
		fseek(out, 0, SEEK_END);
		cout << "������� �������� ������: ";
		cin.getline(zakaz.name, 64);
		cout << "������� ��������� �����: ";
		cin.getline(zakaz.tkantype, 64);
		cout << "���� ������������ ������(����): ";
		cin >> zakaz.term;
		cin.ignore();
		cout << "������� c���� ������: ";
		cin >> zakaz.sum;
		cin.ignore();
		fwrite(&zakaz, sizeof(zakaz), 1, out);
	}
	else
	{
		cout << "��� ������� �� ������������" << endl;
		system("pause");
		return;
	}
	fclose(out);
}


// ������� ������� ������� �������
void allModels(FILE* out)
{
	out = fopen("Katmodel.bin", "r");
	if (out != NULL)
	{
		while (fread(&model, sizeof(model), 1, out) != 0)
		{
			cout << " �����: " << model.name
				<< "\n ���� ������� ������: " << model.price
				<< endl << endl;
		}
		fclose(out);
	}
	else
	{
		cout << "��� �����" << endl;
	}
	system("pause");
}


// ������� ������� ������� ������
void allTkan(FILE* out)
{
	out = fopen("Kattkan.bin", "r");
	if (out != NULL)
	{
		while (fread(&tkan, sizeof(tkan), 1, out) != 0)
		{
			cout << " �����: " << tkan.name
				<< "\n ����: " << tkan.price
				<< endl << endl;
		}
		fclose(out);
	}
	else
	{
		cout << "��� �����" << endl;
	}

	fclose(out);
	system("pause");
}

// ������� ������� ������ �������
void allZakazy(FILE* out)
{
	out = fopen("Zakazy.bin", "r");
	if (out != NULL)
	{
		while (fread(&zakaz, sizeof(zakaz), 1, out) != 0)
		{
			cout << " ������: " << zakaz.name
				<< "\n ��������� �����: " << zakaz.tkantype
				<< "\n ���� ������������: " << zakaz.term
				<< "\n ����� ������: " << zakaz.sum 
				<< endl << endl;
		}
		fclose(out);
	}
	else
	{
		cout << "��� �����" << endl;
	}

	fclose(out);
	system("pause");
}

// ������� ������� ���������� � ������ ��� �����
void info(FILE* out, char* choise)
{
	bool find = 0;

	// ������� ������ � ������
	out = fopen("Katmodel.bin", "r");
	if (out != NULL)
	{
		while (fread(&model, sizeof(model), 1, out) != 0)
		{
			if (sameStr((char*)model.name, choise))
			{
				cout << " �����: " << model.name
					<< "\n ���� ������� ������: " << model.price
					<< "\n ������������� �����: " << model.recomendtkan
					<< "\n ��������: " << model.description << endl;
				find = 1;
			}
		}
		fclose(out);
	}

	// ������� ������ � �����
	out = fopen("Kattkan.bin", "r");
	if (out != NULL)
	{
		while (fread(&tkan, sizeof(tkan), 1, out) != 0)
		{
			if (sameStr((char*)tkan.name, choise))
			{
				cout << " ������������ �����: " << tkan.name
					<<"\n ��������� �����: "<< tkan.price
					<< "\n �������� �����: " << tkan.description
					<< endl;
				find = 1;
			}
		}
		fclose(out);
	}

	// � ������ ���� ������ �� ������
	if (!find)
	{
		cout << "��� � ���� ������" << endl;
	}
	system("pause");
}

int main()
{
 
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* out = NULL;
	while (true)
	{
		setlocale(LC_ALL, "RUSSIAN");
		//FILE* out = NULL;
		char choise[64];
		char ptr[64];

		system("cls");
		cout << "���������� � ��� �� �� ������ ��������:\n" << endl <<
			"\"������� �������\" ��� ��������� ���������� ����\n" <<
			"\"������� ������\" ��� ������ ������\n" <<
			"����� ����� �������� ���������� �������� ������ ��� �����,\n"<<
			"����� �������� ������ ����������\n"<<
			"\"������\" ����� ����������� ������ �������\n"<<
			"\"�������� ...\" (������, �����, �����) (�������� ������ ������ ���������)\n"<<
			"��� ������ ������� q\n"<< endl << endl <<
			"����: ";
		//���� �������
		cin.getline(choise, 64);
		cout << endl;

		if (sameStr((char*)"������� �������", choise))
		{
			allModels(out);
		}
		else if (sameStr(choise, (char*)"��������"))
		{
			//���������� �������� ������� �����
			sscanf(choise, "%*s%s", ptr);
			add(out, ptr);
		}
		else if (sameStr((char*)"������� ������", choise))
		{
			allTkan(out);
		}
		else if (sameStr((char*)"������", choise))
		{
			allZakazy(out);
		}
		else if (sameStr((char*)"q", choise))
		{
			return 0;
		}
		else
		{
			info(out, choise);
		}
	}

	return 0;
}