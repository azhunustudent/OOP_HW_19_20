#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <time.h>
#include <fstream>
using namespace std;
#define RAND(Min, Max) (rand() % ((Max) - (Min) + 1) + (Min))
struct LC { LC() { system("chcp 1251 > nul"); srand(time(0)); } ~LC() { cin.get(); cin.get(); } } _;


// Создайте класс Date, который будет содержать информацию о дате(день, месяц, год).
// С помощью механизма перегрузки операторов, определите операцию разности двух дат
// (результат в виде количества дней между датами), 
// а также операцию увеличения даты на определенное количество дней.
// Для класса перегрузите операторы ввода - вывода: << , >>
// Используйте обычную и дружественную перегрузку.
class Date
{
private:
    int Day, Month, Year;
public:
    Date() : Day(1), Month(1), Year(1970) {}
    Date(int day, int month, int year) : Day(day), Month(month), Year(year) {}

    // геттеры-сеттеры
    bool SetDay(int day)
    {
        if (day > 0 && day <= numOfDaysInMonth(Month, Year))
        {
            Day = day;
            return true;
        }
        else
        {
            cout << "Ошибка: Некорректный ввод дня! ";
            return false;
        }
    }
    bool SetMonth(int month)
    {
        if (month > 0 && month <= 12)
        {
            Month = month;
            return true;
        }
        else
        {
            cout << "Ошибка: Некорректный ввод месяца! ";
            return false;
        }
    }
    bool SetYear(int year)
    {
        if (year > 0)
        {
            Year = year;
            return true;
        }
        else
        {
            cout << "Ошибка: Некорректный ввод года! ";
            return false;
        }
    }

    int GetDay() const { return Day; }
    int GetMonth() const { return Month; }
    int GetYear() const { return Year; }

private:
    // метод для оперделения високосного года
    bool isLeapYear(int year) const
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            return true;
        }
        else { return false; }
    }

    // метод для вычисления кол-во дней в месяце
    int numOfDaysInMonth(int month, int year) const
    {
        if (month == 2)
        {
            return isLeapYear(year) ? 29 : 28;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            return 30;
        }
        else { return 31; }
    }

    // метод для вычисления кол-во дней в году (учитывая високосный год)
    int numOfDaysInYear() const
    {
        int countDays = 0;

        for (int i = 1970; i < Year; i++)
        {
            countDays += isLeapYear(i) ? 366 : 365;
        }

        for (int i = 1; i < Month; i++)
        {
            countDays += numOfDaysInMonth(i, Year);
        }

        countDays += Day;
        return countDays;
    }

public:
    // перегрузка операторов
    // операция разность двух дат (результат в виде количества дней между датами)
    int operator- (const Date& right) const
    {
        if (numOfDaysInYear() > right.numOfDaysInYear())
        {
            return numOfDaysInYear() - right.numOfDaysInYear();
        }
        else
        {
            return right.numOfDaysInYear() - numOfDaysInYear();
        }
    }

    // операция увеличения даты на определенное количество дней
    Date& operator+= (int days)
    {
        this->Day += days;

        while (this->Day > numOfDaysInMonth(Month, Year))
        {
            this->Day -= numOfDaysInMonth(Month, Year);
            Month++;

            if (Month > 12)
            {
                Month = 1;
                Year++;
            }
        }

        return *this;
    }

    // операторы ввода - вывода: << , >>
    friend ostream& operator<< (ostream& os, const Date& obj)
    {
        os << obj.GetDay() << "." << obj.GetMonth() << "." << obj.GetYear() << endl;
        return os;
    }

    friend istream& operator>> (istream& is, Date& obj)
    {
        int t1;

        while (true)
        {
            cout << "Год: ";
            (is >> t1).ignore();

            if (obj.SetYear(t1) == true) { break; }
            cout << "Попробуйте еще раз!" << endl;
        }
        while (true)
        {
            cout << "Месяц: ";
            (is >> t1).ignore();

            if (obj.SetMonth(t1) == true) { break; }
            cout << "Попробуйте еще раз!" << endl;
        }
        while (true)
        {
            cout << "День: ";
            (is >> t1).ignore();

            if (obj.SetDay(t1) == true) { break; }
            cout << "Попробуйте еще раз!" << endl;
        }

        return is;
    }
};


int main() 
{
    Date A, B;
    cout << "Введите первую дату: " << endl;
    cin >> A;
    cout << "Введите вторую дату: " << endl;
    cin >> B;
    cout << endl;

    cout << "Первая дата: " << A;
    cout << "Вторая дата: " << B;
    cout << "Разность дат: Дата 1 - Дата 2 = " << (A - B) << endl;

    A += 5;
    cout << "Увеличение даты: Первая дата (+= 5): " << A;
    cout << "Увеличение даты: Вторая дата (+= 10): " << (B += 10);
    cout << "Дата 1 - Дата 2 = " << (A - B) << endl;
}