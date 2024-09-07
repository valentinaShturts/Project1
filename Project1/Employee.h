#pragma once

struct Employee
{
    char* name;
    char* surname;
    char* phone;
    double payment;
};

// Функции для работы с сотрудниками
void ClearFileContents(char filename[]);
void ShowMenu();
void WriteEmployeeToFile(const Employee* list, int& size);
void ViewEmployeeListFromFile();
Employee create();
void SearchBySurname(Employee* list, int length);
void SearchByPayment(Employee* list, int length);
void SortBySurname(Employee* list, int length, char filename[]);
void AddEmployee(Employee* list, int& size, char filename[]);
void DeleteEmployee(Employee* list, int& length, char filename[]);
void PerformAction(int option, Employee* list, int& size, char filename[]);