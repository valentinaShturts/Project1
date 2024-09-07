#include <iostream>
#include "Employee.h"

using namespace std;
int main()
{
	int option = 0; //переменная выбора пользователя
	int size = 0;
	Employee* employee_list = new Employee[size]; //массив сотрудников, размер которого будет менятся в ходе програмы
	char list[] = "employee_list.txt"; //название текстового документа в который будут записываться изменения массива
	ClearFileContents(list); //очищение файла после предыдущей работы программы
	//цикл основной работы программы
	do
	{
		system("cls");
		ShowMenu();
		cout << " Enter your option: ";
		cin >> option;
		PerformAction(option, employee_list, size, list); 
	} while (option!=0);
	
	//удаление динамических полей структруры и массива
	for (int i = 0; i < size; i++) 
	{
		delete[] employee_list[i].name;    
		delete[] employee_list[i].surname;
		delete[] employee_list[i].phone;
	}
	delete[]employee_list;

	return 0;
}