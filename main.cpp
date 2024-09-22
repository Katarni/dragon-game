#include <iostream>
#include "termcolor/termcolor.h"
#include "Dragon.h"
#include "Hero.h"
#include "Elf.h"
#include <SFML/Graphics.hpp>

int main() {
    std::cout << "Whats your name?" << std::endl;
    std::string name_;
    std::cin >> name_;
    std::cout << "Hi, " << name_ << ", now you will " << termcolor::red;
    std::cout << "die" << termcolor::white << "?" << std::endl << std::endl;

    Hero* hero = new Hero(name_, 50, 10);
    std::vector<Enemy*> enemies = {
            new Dragon(Dragon::Color::Blue, 40, 10),
            new Dragon(Dragon::Color::Red, 40, 10),
            new Dragon(Dragon::Color::Violet, 40, 10),
            new Elf(100, 20)
    };


}
