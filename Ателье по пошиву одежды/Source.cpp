#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <Windows.h>
using namespace std;


struct
{
	char name[64];  // Название
	int price;  // Цена
	char recomendtkan[64];//Рекомендуемая ткань
	char description[1024];  // Описание модели
}model;

struct
{
	char name[64]; // Название
	int price;  // Цена
	char description[1024];  // Описание ткани
}tkan;


struct
{
	char name[64];  // Название
	char tkantype[64]; // Из какой ткани сделана
	int term;  // Срок изготовления(дней)
	int sum;  // Цена
}zakaz;

// Функция сравнения 2 строчек
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


// Функция добавляет объект
void add(FILE* out, char* choise)
{
	// В зависимости от аргумента choise
	// будут добавленны разные типы данных
	if (sameStr((char*)"модель", choise))
	{
		out = fopen("Katmodel.bin", "a");
		fseek(out, 0, SEEK_END);

		cout << "Введите название товара: ";
		cin.getline(model.name, 64);
		cout << "Введите цену единицы товара(в рублях): ";
		cin >> model.price;
		cin.ignore();
		cout << "Введите рекомендуемую ткань для товара: ";
		cin.getline(model.recomendtkan, 64);
		cout << "Введите краткое описание товара(до точки): ";
		cin.getline(model.description, 1024, '.');
		cin.ignore();
		fwrite(&model, sizeof(model), 1, out);
	}
	else if (sameStr((char*)"ткань", choise))
	{
		out = fopen("Kattkan.bin", "a");
		fseek(out, 0, SEEK_END);
		cout << "Введите название ткани: ";
		cin.getline(tkan.name, 64);
		cout << "Введите цену единицы товара(в рублях): ";
		cin >> tkan.price;
		cin.ignore();
		cout << "Введите краткое описание товара(до точки): ";
		cin.getline(tkan.description, 1024, '.');
		cin.ignore();
		fwrite(&tkan, sizeof(tkan), 1, out);
	}
	else if (sameStr((char*)"заказ", choise))
	{
		out = fopen("Zakazy.bin", "a");
		fseek(out, 0, SEEK_END);
		cout << "Введите название модели: ";
		cin.getline(zakaz.name, 64);
		cout << "Введите выбранную ткань: ";
		cin.getline(zakaz.tkantype, 64);
		cout << "Срок изготовления заказа(дней): ";
		cin >> zakaz.term;
		cin.ignore();
		cout << "Введите cумму заказа: ";
		cin >> zakaz.sum;
		cin.ignore();
		fwrite(&zakaz, sizeof(zakaz), 1, out);
	}
	else
	{
		cout << "Тип объекта не предусмотрен" << endl;
		system("pause");
		return;
	}
	fclose(out);
}


// Функция выводит каталог моделей
void allModels(FILE* out)
{
	out = fopen("Katmodel.bin", "r");
	if (out != NULL)
	{
		while (fread(&model, sizeof(model), 1, out) != 0)
		{
			cout << " Товар: " << model.name
				<< "\n Цена единицы товара: " << model.price
				<< endl << endl;
		}
		fclose(out);
	}
	else
	{
		cout << "Нет файла" << endl;
	}
	system("pause");
}


// Функция выводит каталог тканей
void allTkan(FILE* out)
{
	out = fopen("Kattkan.bin", "r");
	if (out != NULL)
	{
		while (fread(&tkan, sizeof(tkan), 1, out) != 0)
		{
			cout << " Товар: " << tkan.name
				<< "\n Цена: " << tkan.price
				<< endl << endl;
		}
		fclose(out);
	}
	else
	{
		cout << "Нет файла" << endl;
	}

	fclose(out);
	system("pause");
}

// Функция выводит список заказов
void allZakazy(FILE* out)
{
	out = fopen("Zakazy.bin", "r");
	if (out != NULL)
	{
		while (fread(&zakaz, sizeof(zakaz), 1, out) != 0)
		{
			cout << " Модель: " << zakaz.name
				<< "\n Выбранная ткань: " << zakaz.tkantype
				<< "\n Срок изготовления: " << zakaz.term
				<< "\n Сумма заказа: " << zakaz.sum 
				<< endl << endl;
		}
		fclose(out);
	}
	else
	{
		cout << "Нет файла" << endl;
	}

	fclose(out);
	system("pause");
}

// Функция выводит информацию о товаре или ткани
void info(FILE* out, char* choise)
{
	bool find = 0;

	// Выводим данные о товаре
	out = fopen("Katmodel.bin", "r");
	if (out != NULL)
	{
		while (fread(&model, sizeof(model), 1, out) != 0)
		{
			if (sameStr((char*)model.name, choise))
			{
				cout << " Товар: " << model.name
					<< "\n Цена единицы товара: " << model.price
					<< "\n Рекомендуемая ткань: " << model.recomendtkan
					<< "\n Описание: " << model.description << endl;
				find = 1;
			}
		}
		fclose(out);
	}

	// Выводим данные о ткани
	out = fopen("Kattkan.bin", "r");
	if (out != NULL)
	{
		while (fread(&tkan, sizeof(tkan), 1, out) != 0)
		{
			if (sameStr((char*)tkan.name, choise))
			{
				cout << " Наименование ткани: " << tkan.name
					<<"\n Стоимость ткани: "<< tkan.price
					<< "\n Описание ткани: " << tkan.description
					<< endl;
				find = 1;
			}
		}
		fclose(out);
	}

	// В случае если объект не найден
	if (!find)
	{
		cout << "Нет в базе данных" << endl;
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
		cout << "Информацию о чем вы бы хотели получить:\n" << endl <<
			"\"Каталог моделей\" для просмотра модельного ряда\n" <<
			"\"Каталог тканей\" для пошива одежды\n" <<
			"Также можно написать конкретное название модели или ткани,\n"<<
			"чтобы получить больше информации\n"<<
			"\"Заказы\" чтобы просмотреть список заказов\n"<<
			"\"Добавить ...\" (модель, ткань, заказ) (напишите нужное вместо троеточия)\n"<<
			"Для выхода нажмите q\n"<< endl << endl <<
			"Ввод: ";
		//Ввод запроса
		cin.getline(choise, 64);
		cout << endl;

		if (sameStr((char*)"Каталог моделей", choise))
		{
			allModels(out);
		}
		else if (sameStr(choise, (char*)"Добавить"))
		{
			//Определяем значение второго слова
			sscanf(choise, "%*s%s", ptr);
			add(out, ptr);
		}
		else if (sameStr((char*)"Каталог тканей", choise))
		{
			allTkan(out);
		}
		else if (sameStr((char*)"Заказы", choise))
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