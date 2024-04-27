#include <iostream>

#include "Src/CorvusEditor.h"

int main() {

    std::cout << "Hello there" << std::endl;

    {
        CorvusEngine::CorvusEditor Editor;
        Editor.Run();
    }

    std::cin.get();

    return 0;
}
