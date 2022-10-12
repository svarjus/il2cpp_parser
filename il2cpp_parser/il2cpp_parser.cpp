// il2cpp_parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

void read(il2cpp::il2cpp_value& val)
{
    std::cout << "get value for name: ";
    std::cin >> val.input_value.search_keyword;

    std::chrono::time_point<std::chrono::system_clock> old = std::chrono::system_clock::now();

    il2cpp::il_FindValue(&val);

    if (val.success) {
        printf("wow the word '%s' was found!!!\nline [%i, %i]\n", val.input_value.search_keyword.c_str(), fs::file.lines_read, fs::file.current_column - (int)val.output_value.string.size());
    }
    else
        printf("the word was not found! [%i]\n", (DWORD)val.output_value.value);

    std::cout << '\n';

    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

    std::chrono::duration<float> difference = now - old;

    printf("time taken: %.6f\n", difference.count());

    system("pause");

}

int main()
{
    il2cpp::il2cpp_value val;
    std::cout << "file path: ";
    std::cin >> val.input_value.file_path;

    while (true) {
        read(val);
        Sleep(300);
        system("cls");
    }

    std::cout << "Hello World!\n";
}