#include <iostream>
#include <fstream>
#include <ctime>

int main()
{
    std::cout << "************** Drawing random pictures *************\n\n";

    srand(time(0));
    std::string file_path;
    std::cout << "Enter the path to the faile: ";
    std::cin >> file_path;
    std::cout << std::endl;

    std::ofstream binary_picture;
    binary_picture.open(file_path, std::ios::binary);

    if (!binary_picture.is_open()) {
        std::cerr << "The file in the specified path cannot be opened\n";
        return 0;
    }
    if (file_path.length() < 5 || (file_path.substr(file_path.length() - 3) != "txt")) {
        std::cerr << "The file is not 'txt'\n";
        return 0;
    }


    int height, width;
    std::cout << "\nInput height, width of picture by space: ";
    std::cin >> height >> width;

    if (height <= 0 || width <= 0) {
        std::cout << "\nWrong size of picture. Try again\n";
        return 0;
    }
    else {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int int_pixel = rand() % 2;
                char bin_pixel = (int_pixel == 0 ? '0' : '1');
                binary_picture.put(bin_pixel);
            }
            binary_picture.put('\n');
        }
    }
    binary_picture.close();
}
