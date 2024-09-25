//
// Created by Тимур Ахметзянов on 23.09.2024.
//

#pragma once

#include <KatLib.h>
#include "units/Dragon.h"
#include "units/Hero.h"
#include "units/WitchKing.h"


class GamePlayer {
 public:
    GamePlayer(const std::string& hero_name, sf::RenderWindow* window) : window_(window) {
        hero_ = new Hero(hero_name, 100, 10);
        hero_->loadImages("../img/pikachu-offside-back.png", "../img/pikachu-offside-back.png");
        hero_->setRender(window_);
        hero_->scale(0.35);
        hero_->setX(250);
        hero_->setY(375);

        enemies_ = {
                new Dragon(Dragon::Color::Blue, 100, 15, "Charizard"),
                new Dragon(Dragon::Color::Red, 100, 15, "Gyarados"),
                new Dragon(Dragon::Color::Violet, 100, 15, "Venusaur"),
                new WitchKing(250, 30, "Witch-king")
        };

        for (int i = 0; i < 4; ++i) {
            enemies_[i]->setX(init_coor_[i].first);
            enemies_[i]->setY(init_coor_[i].second);

            enemies_[i]->scale(init_scales_[i]);

            enemies_[i]->setRender(window);
            enemies_[i]->loadImages("../img/dragons/dragon-" + std::to_string(i + 1) + "-base.png",
                                   "../img/dragons/dragon-" + std::to_string(i + 1) + "-low-hp.png");
        }

        ans_input_ = kat::TextInput(625, 500, 200, 35, "../fonts/NovaMono.ttf", window_);
        ans_input_.setBackgroundColor(sf::Color(194, 146, 110));
        ans_input_.setBorderColor(sf::Color(77, 36, 5));
        ans_input_.setBorderBold(3);
        ans_input_.setBorderRadius(5);
        ans_input_.setFontSize(20);

        words_lbl_ = kat::Label(250, 140, 250, 55, "", "../fonts/NovaMono.ttf", window_);
        words_lbl_.setBackgroundColor(sf::Color(194, 146, 110));
        words_lbl_.setBorderColor(sf::Color(77, 36, 5));
        words_lbl_.setBorderBold(3);
        words_lbl_.setFontSize(15);
        words_lbl_.setBorderRadius(5);
        words_lbl_.setPaddings({5, 5, 5, 5});

        question_lbl_ = kat::Label(250, 215, 250, 35, "", "../fonts/NovaMono.ttf", window_);
        question_lbl_.setBackgroundColor(sf::Color(194, 146, 110));
        question_lbl_.setBorderColor(sf::Color(77, 36, 5));
        question_lbl_.setBorderBold(3);
        question_lbl_.setFontSize(15);
        question_lbl_.setBorderRadius(5);
        question_lbl_.setPaddings({5, 5, 5, 5});

        player_name_ = kat::Label(50, 10, 150, 35, hero_name, "../fonts/NovaMono.ttf", window_);
        player_name_.setBackgroundColor(sf::Color::Transparent);
        player_name_.setFontSize(25);
        player_name_.setColor(sf::Color::White);

        enemy_name_ = kat::Label(800, 10, 150, 35, "", "../fonts/NovaMono.ttf", window_);
        enemy_name_.setBackgroundColor(sf::Color::Transparent);
        enemy_name_.setFontSize(25);
        enemy_name_.setColor(sf::Color::White);

        player_health_ = kat::ProgressBar(50, 55, 150, 20, window_);
        player_health_.setBackgroundColor(sf::Color(194, 146, 110));
        player_health_.setBorderColor(sf::Color(77, 36, 5));
        player_health_.setBorderBold(3);
        player_health_.setBorderRadius(5);
        player_health_.setProgressColor(sf::Color::Red);

        enemy_health_ = kat::ProgressBar(800, 55, 150, 20, window_);
        enemy_health_.setBackgroundColor(sf::Color(194, 146, 110));
        enemy_health_.setBorderColor(sf::Color(77, 36, 5));
        enemy_health_.setBorderBold(3);
        enemy_health_.setBorderRadius(5);
        enemy_health_.setProgressColor(sf::Color::Red);
    }

    bool play() {
        transition();

        bool is_shift = false;

        player_health_.setProgress(1);

        while (cur_state_ < 4 && hero_->isAlive()) {
            auto background = kat::Image("../img/backs/battle-back-" + std::to_string(cur_state_ + 1) + ".png",
                                         window_);
            background.resize(1000, 625);

            bool question_asked = true;

            player_health_.setY(55);
            enemy_health_.setY(55);

            hero_->setX(init_hero_coor_[cur_state_].first);
            hero_->setY(init_hero_coor_[cur_state_].second);

            auto question = enemies_[cur_state_]->ask();
            words_lbl_.setData(question.first);
            question_lbl_.setData(question.second);

            enemy_name_.setData(enemies_[cur_state_]->getName());

            enemy_health_.setProgress(1);

            while (window_->isOpen() && hero_->isAlive() && enemies_[cur_state_]->isAlive()) {
                sf::Event event{};
                while (window_->pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window_->close();
                    }

                    if (event.type == sf::Event::MouseButtonReleased) {
                        ans_input_.isPressed(static_cast<float>(event.mouseButton.x),
                                             static_cast<float>(event.mouseButton.y));
                    }

                    if (event.type == sf::Event::KeyReleased) {
                        if (event.key.code == sf::Keyboard::LShift ||
                            event.key.code == sf::Keyboard::RShift) {
                            is_shift = false;
                        }

                        if (event.key.code == sf::Keyboard::Space &&
                            !question_asked) {
                            question_asked = true;

                            question = enemies_[cur_state_]->ask();
                            words_lbl_.setData(question.first);
                            question_lbl_.setData(question.second);
                            continue;
                        }

                        if (!question_asked) continue;

                        char symbol = getCharFromEvent(event, is_shift);
                        if ('a' <= symbol && symbol <= 'z' || 'A' <= symbol && symbol <= 'Z' ||
                            symbol == ',' || symbol == '.' || '0' <= symbol && symbol <= '9' ||
                            symbol == '-' || symbol == ' ') {
                            ans_input_.addCharacter(symbol);
                        }
                    }

                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::LShift ||
                            event.key.code == sf::Keyboard::RShift) {
                            is_shift = true;
                        }

                        if (event.key.code == sf::Keyboard::Left &&
                            ans_input_.isSelected() && question_asked) {
                            ans_input_.moveCursorLeft();
                        }

                        if (event.key.code == sf::Keyboard::Right &&
                            ans_input_.isSelected() && question_asked) {
                            ans_input_.moveCursorRight();
                        }

                        if (event.key.code == sf::Keyboard::BackSpace &&
                            ans_input_.isSelected() && question_asked) {
                            ans_input_.delCharacter();
                        }

                        if (event.key.code == sf::Keyboard::Enter &&
                            !ans_input_.getData().empty() &&
                            question_asked) {
                            question_asked = false;
                            if (enemies_[cur_state_]->checkAns(ans_input_.getData())) {
                                words_lbl_.setData("You are goddamn right");
                                hero_->attack(enemies_[cur_state_]);
                            } else {
                                words_lbl_.setData("Hahaha, looser");
                                enemies_[cur_state_]->attack(hero_);
                            }
                            enemy_health_.setProgress(static_cast<double>(enemies_[cur_state_]->getHealth()) /
                                                        static_cast<double>(enemies_[cur_state_]->getFullHealth()));
                            player_health_.setProgress(static_cast<double>(hero_->getHealth()) /
                                                      static_cast<double>(hero_->getFullHealth()));
                            ans_input_.clear();
                        }
                    }
                }

                window_->clear(sf::Color::White);
                background.render();

                enemies_[cur_state_]->render();
                hero_->render();

                ans_input_.render();
                words_lbl_.render();
                if (question_asked) {
                    question_lbl_.render();
                }

                player_name_.render();
                enemy_name_.render();

                player_health_.render();
                enemy_health_.render();

                window_->display();
            }

            if (!window_->isOpen()) {
                exit(0);
            }

            auto win_lbl = kat::Label(350, -160, 100, 50, "", "../fonts/KodeMono-bold.ttf", window_);
            win_lbl.setData("YOU " + std::string(hero_->isAlive() ? "WIN" : "LOST"));
            win_lbl.setBackgroundColor(sf::Color::Transparent);
            win_lbl.setFontSize(66);
            win_lbl.setColor(sf::Color::White);

            auto continue_lbl = kat::Label(295, -66, 100, 35, "", "../fonts/KodeMono-bold.ttf", window_);
            continue_lbl.setData("press any key to " + std::string(hero_->isAlive() ? "continue" : "restart"));
            continue_lbl.setBackgroundColor(sf::Color::Transparent);
            continue_lbl.setFontSize(30);
            continue_lbl.setColor(sf::Color::White);

            if (hero_->isAlive()) {
                continue_lbl.moveX(-30);
            }

            int64_t iteration = 0;
            while (player_health_.getY() + player_health_.getHeight() >= -10 ||
                    win_lbl.getY() < 100 || continue_lbl.getY() < 200) {
                if (iteration % 1048576 == 0) {
                    if (player_health_.getY() + player_health_.getHeight() >= -10) {
                        player_health_.moveY(-1);
                        enemy_health_.moveY(-1);
                    }
                    if (win_lbl.getY() < 100) {
                        win_lbl.moveY(1);
                    }
                    if (continue_lbl.getY() < 200) {
                        continue_lbl.moveY(1);
                    }
                    iteration = 0;

                    window_->clear(sf::Color::White);
                    background.render();

                    enemies_[cur_state_]->render();
                    hero_->render();

                    player_health_.render();
                    enemy_health_.render();

                    win_lbl.render();
                    continue_lbl.render();

                    window_->display();
                }
                ++iteration;
            }

            iteration = 0;
            auto dead_animation = kat::Animation("../img/explosion/", 10, "sprite_", ".png", window_);
            dead_animation.scale(2.5);

            std::pair<float, float> center_coor;
            if (!enemies_[cur_state_]->isAlive()) {
                center_coor = enemies_[cur_state_]->getCenterCoor();
            } else {
                center_coor = hero_->getCenterCoor();
            }

            dead_animation.setX(center_coor.first - dead_animation.getScaledWidth() / 2);
            dead_animation.setY(center_coor.second - dead_animation.getScaledHeight() / 2);

            while (true) {
                if (iteration % 67108864 == 0) {
                    iteration = 0;

                    window_->clear(sf::Color::White);
                    background.render();

                    if (enemies_[cur_state_]->isAlive()) {
                        enemies_[cur_state_]->render();
                    } else {
                        hero_->render();
                    }

                    dead_animation.render();

                    win_lbl.render();
                    continue_lbl.render();

                    window_->display();

                    if (dead_animation.nextFrame()) {
                        break;
                    }
                }
                ++iteration;
            }

            while (window_->isOpen()) {
                sf::Event event{};
                while (window_->pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window_->close();
                        exit(0);
                    }

                    if (event.type == sf::Event::KeyPressed) {
                        if (!hero_->isAlive()) {
                            return true;
                        }

                        goto transition;
                    }
                }

                window_->clear(sf::Color::White);
                background.render();

                if (enemies_[cur_state_]->isAlive()) {
                    enemies_[cur_state_]->render();
                } else {
                    hero_->render();
                }

                win_lbl.render();
                continue_lbl.render();

                window_->display();
            }

            transition:

            ++cur_state_;
            if (cur_state_< 4) {
                transition();
            }
        }

        ending();

        return false;
    }

 private:
    int cur_state_ = 0;

    sf::RenderWindow* window_;

    Hero* hero_;
    std::vector<Enemy*> enemies_;
    
    kat::Label words_lbl_, question_lbl_, player_name_, enemy_name_;
    kat::TextInput ans_input_;
    kat::ProgressBar player_health_, enemy_health_;

    std::vector<std::pair<float, float>> init_hero_coor_ = {
            {250, 375},
            {250, 350},
            {200, 400},
            {400, 450}
    };

    std::vector<std::pair<float, float>> init_coor_ = {
            {500, 50},
            {530, 70},
            {540, 120},
            {570, 180}
    };
    std::vector<float> init_scales_ = {
            0.75,
            0.75,
            0.9,
            0.4
    };

    void transition() {
        auto running_pikachu = kat::Animation("../img/pikachu-run/", 4, "sprite_", ".png", window_);
        running_pikachu.setY(410);
        running_pikachu.scale(0.45);
        running_pikachu.setDuration(9500);
        auto background = kat::Image("../img/transitions/transition-" +
                                     std::to_string(cur_state_ % 2 + 1) + ".png",
                                     window_);
        background.resize(1000, 625);
        int iteration = 0;
        while (running_pikachu.getX() + running_pikachu.getScaledWidth() <
                static_cast<float>(window_->getSize().x)) {
            if (iteration % 500 == 0) {
                iteration = 0;

                window_->clear(sf::Color::White);
                background.render();

                running_pikachu.render();

                window_->display();

                running_pikachu.moveX(1);
            }
            if (running_pikachu.tick()) {
                window_->clear(sf::Color::White);
                background.render();

                running_pikachu.render();

                window_->display();
            }

            ++iteration;
        }
    }

    void ending() {
        auto background = kat::Image("../img/backs/finish-back.png", window_);
        background.resize(1000, 625);

        auto pikachu = kat::Image("../img/pikachu-front.png", window_);
        pikachu.setX(410);
        pikachu.setY(510);
        pikachu.scale(0.2);

        while (window_->isOpen()) {
            sf::Event event{};
            while (window_->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window_->close();
                }

                if (event.type == sf::Event::KeyPressed) {
                    window_->close();
                }
            }

            window_->clear(sf::Color::White);
            background.render();

            pikachu.render();

            window_->display();
        }
    }
};
