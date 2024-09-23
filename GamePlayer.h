//
// Created by Тимур Ахметзянов on 23.09.2024.
//

#pragma once

#include <KatLib.h>
#include "units/Dragon.h"
#include "units/Hero.h"
#include "units/Elf.h"


class GamePlayer {
 public:
    GamePlayer(const std::string& hero_name, sf::RenderWindow* window) : window_(window) {
        hero_ = new Hero(hero_name, 100, 10);
        hero_->loadImages("../img/pikachu-back.png", "../img/pikachu-back.png");
        hero_->setRender(window_);
        hero_->scale(0.35);
        hero_->setX(250);
        hero_->setY(375);

        enemies_ = {
                new Dragon(Dragon::Color::Blue, 100, 15),
                new Dragon(Dragon::Color::Red, 100, 15),
                new Dragon(Dragon::Color::Violet, 100, 15),
                new Elf(250, 30)
        };

        for (int i = 0; i < 1; ++i) {
            enemies_[i]->setX(init_coor_[i].first);
            enemies_[i]->setY(init_coor_[i].second);

            enemies_[i]->scale(init_scales_[i]);

            enemies_[i]->setRender(window);
            enemies_[i]->loadImages("../img/dragon-" + std::to_string(i + 1) + "-base.png",
                                   "../img/dragon-" + std::to_string(i + 1) + "-low-hp.png");
        }
    }

    void play() {
        // transition to first level

        auto ans_input = kat::TextInput(625, 500, 200, 35, "../fonts/NovaMono.ttf", window_);
        ans_input.setBackgroundColor(sf::Color(194, 146, 110));
        ans_input.setBorderColor(sf::Color(77, 36, 5));
        ans_input.setBorderBold(3);
        ans_input.setBorderRadius(5);

        while (cur_state_ < 4) {
            auto background = kat::Image("../img/battle-back-" + std::to_string(cur_state_ + 1) + ".jpg", window_);
            background.resize(1000, 625);

            while (window_->isOpen()) {
                sf::Event event{};
                while (window_->pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window_->close();
                    }
                }

                window_->clear(sf::Color::White);
                background.render();

                enemies_[cur_state_]->render();
                hero_->render();
                ans_input.render();

                window_->display();
            }

            // transition

            ++cur_state_;
        }

        // ending
    }

 private:
    int cur_state_ = 0;

    sf::RenderWindow* window_;

    Hero* hero_;
    std::vector<Enemy*> enemies_;

    std::vector<std::pair<float, float>> init_coor_ = {
            {500, 50}
    };
    std::vector<float> init_scales_ = {
            0.75
    };

    void playLevel() {

    }
};
