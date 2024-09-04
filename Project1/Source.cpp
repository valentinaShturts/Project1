#include <iostream>
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

	} while (true);
	
	

	return 0;
}