#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

void current_status_ATM(std::vector<int> &vec_ATM) {
    //Вывод информации о текущем состоянии банкомата
    int vecSize = 0, sum = 0;
    for (int i = 0; i < 6; i++) {
        vecSize += vec_ATM[i];
    }
    sum = vec_ATM[0] * 100 + vec_ATM[1] * 200 + vec_ATM[2] * 500 + vec_ATM[3] * 1000 + vec_ATM[4] * 2000 + vec_ATM[5] * 5000;

    std::cout << "There are " << vecSize << " banknotes in the ATM " << std::endl;
    std::cout << "The ATM has banknotes of the following denominations: " << std::endl;
    std::cout << "Banknotes of 100 RUB - " << vec_ATM[0] << std::endl;
    std::cout << "Banknotes of 200 RUB - " << vec_ATM[1] << std::endl;
    std::cout << "Banknotes of 500 RUB - " << vec_ATM[2] << std::endl;
    std::cout << "Banknotes of 1000 RUB - " << vec_ATM[3] << std::endl;
    std::cout << "Banknotes of 2000 RUB - " << vec_ATM[4] << std::endl;
    std::cout << "Banknotes of 5000 RUB - " << vec_ATM[5] << std::endl;
    std::cout << "Total - " << sum << " RUB" << std::endl << std::endl;
    std::cout << std::endl;
}

int main()
{
    std::cout << "************** Simulation of ATM operation *************\n\n";

    srand(time(0)); //Внесём элемент непредсказуемости

    std::vector<int> vec_ATM;   //Содержимое банкомата
    int getCash, cash100, cash200, cash500, cash1000, cash2000, cash5000;
    int vecSize, sum;

    //Проверка наличия файла atm.bin
    if (std::ifstream("atm.bin")) {
        //Вывод информации о текущем состоянии банкомата из файла
        std::ifstream iatm_file;
        iatm_file.open("atm.bin", std::ios::binary);
        int buffer;

        iatm_file.seekg(0, std::ios::end);
        int size = iatm_file.tellg();
        iatm_file.seekg(0, std::ios::beg);

        if (size == 24) {       //Проверяем размер файла, он должен быть равен 6 * 4 байта
            vec_ATM.resize(6);
            for (int i = 0; i < 6; i++) {
                iatm_file.read((char*)&vec_ATM[i], sizeof(vec_ATM[i]));
            }

            //Вывод информации о текущем состоянии банкомата
            current_status_ATM(vec_ATM);
        }
        else {
            std::cout << "The ATM broke down!\n" << std::endl; //Файл поврежден
            return 0;
        }
        iatm_file.close();
    }
    else {
        //Банкомат пустой (файл отсутствует)
        std::cout << "The ATM is empty!\n" << std::endl;
        std::ofstream atm_file("atm.bin");
        if (!atm_file) {     //Если невозможно создать файл, значит банкомат сломался
            std::cout << "The ATM broke down!\n" << std::endl;
            return 0;
        }
       
    }
    //Запуск работы банкомата
    char operation;
    
    while (true) {
        std::cout << "Enter the desired operation.\n";
        std::cout << "'+' - fill the ATM,\n'-' - get cash,\n'0' - exiting the program\n";
        std::cin >> operation;
        switch (operation) {

        case '+':   //Инкассаторы заполняют банкомат купюрами
            vecSize = 0;
            sum = 0;
            if (vec_ATM.size() == 0)    //Если файла ранее не существовало
                vec_ATM.resize(6);
            for (int i = 0; i < vec_ATM.size(); i++) {
                vecSize += vec_ATM[i];
            }

            int rand_denomination;
            for (int i = 0; i < (1000 - vecSize); i++) {
                rand_denomination = rand() % 6 + 1;
                switch (rand_denomination) {
                case 1:
                    vec_ATM[0]++;
                    break;
                case 2:
                    vec_ATM[1]++;
                    break;
                case 3:
                    vec_ATM[2]++;
                    break;
                case 4:;
                    vec_ATM[3]++;
                    break;
                case 5:
                    vec_ATM[4]++;
                    break;
                case 6:
                    vec_ATM[5]++;
                    break;
                default:
                    break;
                }
            }

            //Вывод информации о текущем состоянии банкомата
            current_status_ATM(vec_ATM);
            
            break;

        case '-':   //Снятие налички
            cash100 = 0; cash200 = 0; cash500 = 0; cash1000 = 0; cash2000 = 0; cash5000 = 0;
            std::cout << "Specify the amount you want to withdraw: ";
            std::cin >> getCash;

            sum = vec_ATM[0] * 100 + vec_ATM[1] * 200 + vec_ATM[2] * 500 + vec_ATM[3] * 1000 + vec_ATM[4] * 2000 + vec_ATM[5] * 5000;

            if (getCash > sum)
                std::cout << getCash << " There are not enough funds to issue.\n\n";
            else if (getCash % 100 != 0)
                std::cout << getCash << "!!! The requested amount must be a multiple of 100 rubles.\n\n";
            else {

                if (getCash >= 5000 && vec_ATM[5] > 0) {
                    cash5000 = getCash / 5000;
                    if (cash5000 <= vec_ATM[5]) {
                        getCash = getCash % 5000;
                        vec_ATM[5] -= cash5000;
                    }
                    else if (vec_ATM[5] > 0) {
                        cash5000 = vec_ATM[5];
                        getCash -= (vec_ATM[5] * 5000);
                        vec_ATM[5] = 0;
                    }
                }
                if (getCash >= 2000 && vec_ATM[4] > 0) {
                    cash2000 = getCash / 2000;
                    if (cash2000 <= vec_ATM[4]) {
                        getCash = getCash % 2000;
                        vec_ATM[4] -= cash2000;
                    }
                    else if (vec_ATM[4] > 0) {
                        cash2000 = vec_ATM[4];
                        getCash -= (vec_ATM[4] * 2000);
                        vec_ATM[4] = 0;
                    }
                }
                if (getCash >= 1000 && vec_ATM[3] > 0) {
                    cash1000 = getCash / 1000;
                    if (cash1000 <= vec_ATM[3]) {
                        getCash = getCash % 1000;
                        vec_ATM[3] -= cash1000;
                    }
                    else if (vec_ATM[3] > 0) {
                        cash1000 = vec_ATM[3];
                        getCash -= (vec_ATM[3] * 1000);
                        vec_ATM[3] = 0;
                    }
                }
                if (getCash >= 500 && vec_ATM[2] > 0) {
                    cash500 = getCash / 500;
                    if (cash500 <= vec_ATM[2]) {
                        getCash = getCash % 500;
                        vec_ATM[2] -= cash500;
                    }
                    else if (vec_ATM[2] > 0) {
                        cash500 = vec_ATM[2];
                        getCash -= (vec_ATM[2] * 500);
                        vec_ATM[2] = 0;
                    }
                }
                if (getCash >= 200 && vec_ATM[1] > 0) {
                    cash200 = getCash / 200;
                    if (cash200 <= vec_ATM[1]) {
                        getCash = getCash % 200;
                        vec_ATM[1] -= cash200;
                    }
                    else if (vec_ATM[1] > 0) {
                        cash200 = vec_ATM[1];
                        getCash -= (vec_ATM[1] * 200);
                        vec_ATM[1] = 0;
                    }
                }
                if (getCash >= 100 && vec_ATM[0] > 0) {
                    cash100 = getCash / 100;
                    if (cash100 <= vec_ATM[0]) {
                        getCash = getCash % 100;
                        vec_ATM[0] -= cash100;
                    }
                    else if (vec_ATM[0] > 0) {
                        cash100 = vec_ATM[0];
                        getCash -= (vec_ATM[0] * 100);
                        vec_ATM[0] = 0;
                    }
                }
                if (getCash > 0)
                    std::cout << "The requested amount cannot be issued.\n";
                else {
                    std::cout << "The following banknotes were issued:\n";
                    if (cash5000 > 0)
                        std::cout << cash5000 << " banknotes of 5000 rubles each.\n";
                    if (cash2000 > 0)
                        std::cout << cash2000 << " banknotes of 2000 rubles each.\n";
                    if (cash1000 > 0)
                        std::cout << cash1000 << " banknotes of 1000 rubles each.\n";
                    if (cash500 > 0)
                        std::cout << cash500 << " banknotes of 500 rubles each.\n";
                    if (cash200 > 0)
                        std::cout << cash200 << " banknotes of 200 rubles each.\n";
                    if (cash100 > 0)
                        std::cout << cash100 << " banknotes of 100 rubles each.\n";
                }
                std::cout << std::endl;

                //Вывод информации о текущем состоянии банкомата
                current_status_ATM(vec_ATM);

                break;

            case '0':
                //Выход из программы, при этом сохранение состояния банкомата в файл
                
                std::ofstream atm_file;
                atm_file.open("atm.bin", std::ios::binary);
                if (!atm_file) {     //Если доступ к файлу закрыт, значит банкомат сломался
                    std::cout << "The ATM broke down!\n" << std::endl;
                    return 0;
                }
                for (int i = 0; i < 6; i++) {
                    atm_file.write((char*)&vec_ATM[i], sizeof(vec_ATM[i]));
                }
                atm_file.close();
                return 0;
            }
        }
    }   
}