#include <cstdio>
#include <fat12.h>
#include <directory_entry.h>
#include <iostream>

int main(int argv, char *argc[]) {
    fat12 fs("../images/floppy.img");
    
    auto root = directory(fs, fs.root());

    for (auto& e : root) {
        std::cout << e.file_name << std::endl;
    }

    return 0;
}

