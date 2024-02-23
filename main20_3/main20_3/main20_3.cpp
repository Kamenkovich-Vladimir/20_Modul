#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::cout << "************** Fishing *************\n\n";
    
    std::ifstream fish_strim;
    fish_strim.open("river.txt");
    if (!fish_strim.is_open()) {
        std::cerr << "The file in the specified path cannot be opened\n";
        return 0;
    }

    std::ofstream basket_strim;
    basket_strim.open("basket.txt", std::ios::app);
    if (!basket_strim.is_open()) {
        std::cerr << "The file in the specified path cannot be opened\n";
        return 0;
    }

    std::string fish;
    std::vector<std::string> vec_river;
    bool luck = false;
    
    while (!fish_strim.eof()) { //Проведем инвентаризацию рыбы в реке
        fish_strim >> fish;
        if (fish != "")
            vec_river.push_back(fish);  //Запишем имеющуюся рыбу в вектор
        fish = "";                      //Обнулим переменную, чтобы не дублировать последнюю рыбу на пустой строке
    }
    fish_strim.close();

    std::ifstream river_strim;
    river_strim.open("river.txt");
    if (!river_strim.is_open()) {
        std::cerr << "The file in the specified path cannot be opened\n";
        return 0;
    }

    std::cout << "Enter tipe of fish: ";
    std::cin >> fish;

    auto iter = vec_river.cbegin();
    int i = 0;
    
    while (!river_strim.eof()) {
        std::string attempt;
        river_strim >> attempt;
        if (attempt == fish) {
            basket_strim << fish << std::endl;
            std::cout << fish << " is caught and in the basket! \n";
            vec_river.erase(iter + i);  //Удалим пойманную рыбу из инвентаризационной ведомости
            luck = true;
            break;
        }
        i++;
    }
    if(!luck)
        std::cout << fish << " won't bite! \n"; //не клюёт
    river_strim.close();
    basket_strim.close();

    //Обновим данные по рыбе в реке согласно инвентаризационной описи
    std::ofstream river;
    river.open("river.txt");
    if (!river.is_open()) {
        std::cerr << "The file in the specified path cannot be opened\n";
        return 0;
    }

    for (int i = 0; i < vec_river.size(); i++) {
        river << vec_river[i] << std::endl;
    }
    river.close();
}
