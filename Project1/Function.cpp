#include <iostream>
#include <windows.h>
#include "employee.h"
#pragma warning(disable : 4996)
using namespace std;

//ф-ия очищения текстового файла путем открытия и закрытия его
void ClearFileContents(char filename[])
{
	FILE* file = fopen("employee_list.txt", "w");
	if (file != nullptr)
	{
		fclose(file);
	}
	else
	{
		cout << "Error: Unable to open file." << endl;
	}
}

//ф-ия что выводит меню на экран
void ShowMenu()
{
	cout << " 1. Show all employees " << endl << " 2. Search by surname " << endl << " 3. Search by payment " << endl << " 4. Sort by surnames " << endl << " 5. Add new employee " << endl << " 6. Delete employee " << endl << " 0. Exit " << endl;
}

//ф-ия что записывает массив сотрудников в файл
void WriteEmployeeToFile(const Employee* list, int& size)
{
	FILE* file = fopen("employee_list.txt", "a");
	if (file != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			fprintf(file, "%s ", list[i].name);
			fprintf(file, " %s ", list[i].surname);
			fprintf(file, " %s ", list[i].phone);
			fprintf(file, " %f ", list[i].payment);
			fputc('\n\n', file);
		}
		fclose(file);
	}
	else {
		cout << "Error: Unable to open file for writing." << endl;
	}
}

//ф-ия что считывает с файла данные и выводит на экран
void ViewEmployeeListFromFile()
{
	FILE* file = fopen("employee_list.txt", "r");
	if (file != nullptr)
	{
		char name[50], surname[50], phone[50], payment[50];
		while (fscanf(file, "%49s %49s %49s %49s", name, surname, phone, payment) == 4)
		{
			cout << "Employee " << name << " " << surname << endl << "Phone: " << phone << endl << "Payment: " << payment << endl << endl;
		}
		fclose(file);
	}
	else
	{
		cout << "Error: Unable to open file for reading." << endl;
	}
}

//ф-ия создания обьекта структуры Сотрудник
Employee create()
{
	Employee employee;

	char* name = new char[20];
	cout << "Enter name : ";
	cin >> name;
	int size = strlen(name);
	employee.name = new char[size + 1];
	strcpy_s(employee.name, size + 1, name);

	char* surname = new char[20];
	cout << "Enter surname : ";
	cin >> surname;
	size = strlen(surname);
	employee.surname = new char[size + 1];
	strcpy_s(employee.surname, size + 1, surname);

	char* phone = new char[20];
	do
	{
		cout << "Enter phone (10): ";
		cin >> phone;
		size = strlen(phone);
		employee.phone = new char[size + 1];
		strcpy_s(employee.phone, size + 1, phone);
	} while (strlen(phone) != 10); //проверка коректности номера телефона

	cout << "Enter payment: ";
	cin >> employee.payment;

	delete[] name, surname, phone;
	return employee;
}

//ф-ия поиска сотрудника по фамилии
void SearchBySurname(Employee* list, int length)
{
	char* surname = new char[20];
	cout << "Enter surname : ";
	cin >> surname;
	int size = strlen(surname);
	char* Surname = new char[size + 1];
	strcpy_s(Surname, size + 1, surname);

	delete[] surname;

	for (int i = 0; i < length; i++)
	{
		if (strcmp(list[i].surname, Surname) == 0)
		{
			cout << "Employee " << list[i].name << " " << list[i].surname << endl << "Phone: " << list[i].phone << endl << "Payment: " << list[i].payment << endl << endl;
		}
	}

	delete[] Surname;
}

//ф-ия поиска сотрудников по заработной плате
void SearchByPayment(Employee* list, int length)
{
	double min = 0;
	double max = 0;
	cout << "Enter minimum limit of payment: ";
	cin >> min;
	cout << "Enter maximum limit of payment: ";
	cin >> max;
	if (max < min)
	{
		int temp = max;
		max = min;
		min = temp;
	}

	for (int i = 0; i < length; i++)
	{
		if (list[i].payment > min && list[i].payment < max)
		{
			cout << "Employee " << list[i].name << " " << list[i].surname << endl << "Phone: " << list[i].phone << endl << "Payment: " << list[i].payment << endl << endl;
		}
	}
}

//ф-ия сортировки сотрудников в списке по фамилии с помощью bubble sort
void SortBySurname(Employee* list, int length, char filename[])
{
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			if (strcmp(list[j].surname, list[j + 1].surname) > 0)
			{
				Employee temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
	ClearFileContents(filename);
	WriteEmployeeToFile(list, length);
}

//добавление сотрудника
void AddEmployee(Employee* list, int& size, char filename[])
{
	size += 1;
	list[size - 1] = create();
	ClearFileContents(filename);
	WriteEmployeeToFile(list, size);
}

//удаление сотрудника
void DeleteEmployee(Employee* list, int& length, char filename[])
{
	int temp = -1;

	char* name = new char[20];
	cout << "Enter name : ";
	cin >> name;
	int size = strlen(name);
	char* Name = new char[size + 1];
	strcpy_s(Name, size + 1, name);

	char* surname = new char[20];
	cout << "Enter surname : ";
	cin >> surname;
	size = strlen(surname);
	char* Surname = new char[size + 1];
	strcpy_s(Surname, size + 1, surname);

	delete[] name;
	delete[] surname;

	for (int i = 0; i < length; i++)
	{
		if (strcmp(list[i].name, Name) == 0 && strcmp(list[i].surname, Surname) == 0)
		{
			temp = i;
			break; 
		}
	}

	delete[] Name;
	delete[] Surname;

	//вопрос на удаление
	bool t;
	cout << "Are you sure you want to delete " << list[temp].name << " " << list[temp].surname << " from this list? (0 - no, 1 - yes) ";
	cin >> t;
	if (t == 0) return;

	if (temp != -1)
	{
		for (int i = temp; i < length - 1; i++)
		{
			strcpy(list[i].name, list[i + 1].name);
			strcpy(list[i].surname, list[i + 1].surname);
			strcpy(list[i].phone, list[i + 1].phone);
			list[i].payment = list[i + 1].payment;
		}
		length--; 
	}
	else
	{
		cout << "Employee not found." << endl;
	}

	ClearFileContents(filename);
	WriteEmployeeToFile(list, length);
}

//ф-ия которая вызывает другие ф-ии согласно выбору в меню пользователя
void PerformAction(int option, Employee* list, int& size, char filename[])
{
	if (option == 1) ViewEmployeeListFromFile();
	else if (option == 2) SearchBySurname(list, size);
	else if (option == 3) SearchByPayment(list, size);
	else if (option == 4) SortBySurname(list, size, filename);
	else if (option == 5) AddEmployee(list, size, filename);
	else if (option == 6) DeleteEmployee(list, size, filename);
	else if (option == 0) exit(0);

	char temp;
	cout << endl << "Enter smth to continue...";
	cin >> temp;
}