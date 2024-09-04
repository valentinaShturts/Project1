#include <iostream>
#include <windows.h>
#pragma warning(disable : 4996)
using namespace std;

struct Employee
{
	char* name;
	char* surname;
	char* phone;
	double payment;
};

void ShowMenu()
{
	cout << " 1. Show all employees " << endl << " 2. Search by surname " << endl << " 3. Search by payment " << endl << " 4. Sort by surnames " << endl << " 5. Add new employee " << endl << " 6. Delete employee " << endl << " 0. Exit " << endl;
}

void WriteEmployeeToFile(const Employee& employee)
{
	FILE* file = fopen("employee_list.txt", "a"); // Открытие файла для записи (добавление в конец файла)
	if (file != nullptr)
	{
		fprintf(file, "%s ", employee.name);
		fprintf(file, " %s ", employee.surname);
		fprintf(file, " %s ", employee.phone);
		fprintf(file, " %f ", employee.payment);
		fputc('\n', file);
		fclose(file);
	}
	else {
		cout << "Error: Unable to open file for writing." << endl;
	}
}

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
	cout << "Enter phone : ";
	cin >> phone;
	size = strlen(phone);
	employee.phone = new char[size + 1];
	strcpy_s(employee.phone, size + 1, phone);

	cout << "Enter payment: ";
	cin >> employee.payment;

	delete[] name, surname, phone;
	WriteEmployeeToFile(employee);
	return employee;
}

int main()
{
	int option = 0;
	do
	{
		system("cls");
		ShowMenu();
		cout << " Enter your option: ";
		cin >> option;
		create();
		
	} while (true);
	
	

	return 0;
}