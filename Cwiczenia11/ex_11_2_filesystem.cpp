//Pawel Jandula
#include <iostream>
#include <filesystem>
#include <regex>
#include <string_view>

namespace fs = std::filesystem;

void printDirectory(std::string_view path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        char type = ' ';
        if (entry.is_directory()) type = 'D';
        else if (entry.is_regular_file()) type = 'F';
        else if (entry.is_symlink()) type = 'L';

        std::cout << "[" << type << "] " << entry.path().filename().string();

        // Rozmiar pliku można bezpiecznie odczytać tylko dla zwykłych plików
        if (entry.is_regular_file()) {
            std::cout << " " << entry.file_size();
        }
        std::cout << '\n';
    }
}

void changeExtension(fs::path path, std::string fileNames, std::string_view newExtension) {
    std::regex re(fileNames);

    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();

            if (std::regex_match(filename, re)) {
                fs::path newPath = entry.path();
                newPath.replace_extension(newExtension);

                fs::copy_file(entry.path(), newPath, fs::copy_options::overwrite_existing);
            }
        }
    }
}
int main() {
    std::cout << "Zawartość obecnego katalogu:\n";
    printDirectory(".");

     std::cout << "\nZmieniam rozszerzenia z .txt na .md...\n";
     changeExtension(".", ".*\\.txt", ".md");

    return 0;
}
//g++ -std=c++17 ex_11_2_filesystem.cpp -o ex2