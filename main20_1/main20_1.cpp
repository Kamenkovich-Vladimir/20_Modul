#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::cout << "************** Filling out the statement *************\n\n";

    std::string file_path;
    std::cout << "Enter the path to the faile: ";
    std::cin >> file_path;
    std::cout << std::endl;

    std::ofstream statement_strim;
    statement_strim.open(file_path, std::ios::app);

    if (!statement_strim.is_open()) {
        std::cerr << "The file in the specified path is missing or cannot be opened\n";
        return 0;
    }

    std::string name, surname, date, ins = "y";
    double payment;

    while (ins == "y") {
        std::cout << "Input name: ";
        std::cin >> name;

        if (name[0] > 96 && name[0] < 123)
            name[0] = name[0] - 32;

        std::cout << "Input surname: ";
        std::cin >> surname;

        if (surname[0] > 96 && surname[0] < 123)
            surname[0] = surname[0] - 32;

        //Ввод и валидация формата даты 'dd.mm.yyyy'
        bool valid_date = false;
        while (!valid_date) {

            std::cout << "Input date of payment: ";
            std::cin >> date;

            if (date.length() != 10)
                std::cout << "Invalid format of date 'dd.mm.yyyy'\n";
            else if (date[2] != '.' || date[5] != '.')
                std::cout << "The day, month and year should be separated by dots\n";
            else if (std::stoi(date.substr(0, 2)) <= 0 || std::stoi(date.substr(0, 2)) > 31)
                std::cout << "The wrong value of the day\n";
            //Проверку количества дней в месяце делать поленился, но это механика
            else if (std::stoi(date.substr(3, 2)) <= 0 || std::stoi(date.substr(3, 2)) > 12)
                std::cout << "The wrong value of the month\n";
            //Должна быть, конечно, проверка на превышение текущей даты
            else if ((std::stoi(date.substr(6)) <= 2000) || (std::stoi(date.substr(6)) > 2024))
                std::cout << "The wrong value of the year\n";
            else {
                valid_date = true;
            }
        }
        payment = 0;
        while (payment <= 0) {
            std::cout << "Input payment: ";
            std::cin >> payment;

            if (payment <= 0)
                std::cout << "The payout should be higher\n";

        }
        //Записываем в файл "валидированные" данные
        statement_strim.setf(std::ios::fixed);
        statement_strim.precision(2);
        statement_strim << name << " " << surname << " " << date << " " << payment << std::endl;

        std::cout << std::endl;

        std::cout << "Add an entry? (y/n)";
        std::cin >> ins;
    }
    statement_strim.close();
}
