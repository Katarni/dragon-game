#include "GamePlayer.h"

int main() {
    std::string name = "chipi-chipi";
    auto window = new sf::RenderWindow(sf::VideoMode(1000, 625), "Dragons Game");

    auto back = kat::Image("../img/start-back.jpeg", window);
    back.resizeByWidth(1000);

    auto header = kat::Label(295, 100, 300, 70, "Dragons game", "../fonts/NovaMono.ttf", window);
    header.setBackgroundColor(sf::Color::Transparent);
    header.setFontSize(60);
    header.setColor(sf::Color(77, 36, 5));

    auto name_input = kat::TextInput(350, 250, 300, 40, "../fonts/NovaMono.ttf", window);
    name_input.setBackgroundColor(sf::Color(194, 146, 110));
    name_input.setBorderColor(sf::Color(77, 36, 5));
    name_input.setBorderBold(3);
    name_input.setBorderRadius(5);

    bool is_shift = false;

    // temp here
//    goto get_name;

    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                name_input.isPressed(static_cast<float>(event.mouseButton.x),
                                     static_cast<float>(event.mouseButton.y));
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::LShift ||
                        event.key.code == sf::Keyboard::RShift) {
                    is_shift = false;
                }

                if (name_input.getData().size() >= 12) continue;

                char symbol = getCharFromEvent(event, is_shift);
                if ('a' <= symbol && symbol <= 'z' || 'A' <= symbol && symbol <= 'Z') {
                    name_input.addCharacter(symbol);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::LShift ||
                    event.key.code == sf::Keyboard::RShift) {
                    is_shift = true;
                }

                if (event.key.code == sf::Keyboard::Left &&
                    name_input.isSelected()) {
                    name_input.moveCursorLeft();
                }

                if (event.key.code == sf::Keyboard::Right &&
                    name_input.isSelected()) {
                    name_input.moveCursorRight();
                }

                if (event.key.code == sf::Keyboard::BackSpace &&
                    name_input.isSelected()) {
                    name_input.delCharacter();
                }

                if (event.key.code == sf::Keyboard::Enter &&
                    !name_input.getData().empty()) {
                    window->clear(sf::Color::White);
                    goto get_name;
                }
            }
        }

        window->clear();
        back.render();
        header.render();
        name_input.render();
        window->display();
    }

    get_name:

    GamePlayer player(name_input.getData(), window);
    player.play();
}
