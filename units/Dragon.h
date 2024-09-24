//
// Created by Тимур Ахметзянов on 20.09.2024.
//

#pragma once

#include "Enemy.h"


class Dragon : public Enemy {
 public:
    enum class Color {
        Red, Blue, Violet
    };

    Dragon(Color color, int health, int attack,
           const std::string& name) : color_(color), Enemy(health, attack, name) {}
    Dragon(Color color, int health, int attack,
           std::string&& name) : color_(color), Enemy(health, attack, std::move(name)) {}

    [[nodiscard]]
    virtual std::pair<std::string, std::string> ask() override {
        generateQuestion();
        std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        return {phrases_[rnd() % phrases_.size()], question_};
    }

    virtual bool checkAns(std::string ans) override {
        while (ans.size() > 0 && ans[0] == ' ') {
            ans.erase(ans.begin());
        }
        while (ans.size() > 0 && ans.back() == ' ') {
            ans.pop_back();
        }
        return ans == answer_;
    }

    [[nodiscard]]
    Color getColor() const {
        return color_;
    }

    virtual void render() override {
        if (getHealth() >= 0.4 * getFullHealth()) {
            base_image_.render();
        } else {
            low_hp_image_.render();
        }
    }

 protected:
    virtual void generateQuestion() override {
        std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        int lhs = static_cast<int>(rnd()) % 30, rhs = static_cast<int>(rnd()) % 30;
        switch (color_) {
            case Color::Red:
                question_ = std::to_string(lhs) + " - " + std::to_string(rhs);
                answer_ = std::to_string(lhs - rhs);
                break;
            case Color::Blue:
                question_ = std::to_string(lhs) + " + " + std::to_string(rhs);
                answer_ = std::to_string(lhs + rhs);
                break;
            default:
                question_ = std::to_string(lhs) + " * " + std::to_string(rhs);
                answer_ = std::to_string(lhs * rhs);
        }
    }

 private:
    Color color_;
    std::string question_, answer_;
};
