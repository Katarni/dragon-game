//
// Created by Тимур Ахметзянов on 20.09.2024.
//

#pragma once

#include "Enemy.h"


class Elf : public Enemy {
 public:
    Elf(int health, int attack) : Enemy(health, attack) {}

    [[nodiscard]]
    virtual std::string ask() override {
        generateQuestion();
        return question_;
    }

    virtual bool checkAns(const std::string& ans) override {
        return ans == answer_;
    }

 protected:
    virtual void generateQuestion() override {
        std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

        answer_ = "";

        int number = rnd() % 150 + 2;
        question_ = "factorize the number: " + std::to_string(number) + " and sort answer in ascending order";
        for (int i = 2; i <= sqrt(number); ++i) {
            while (number % i == 0) {
                answer_ += std::to_string(i) + ", ";
                number /= i;
            }
        }
        if (number != 1) {
            answer_ += std::to_string(number) + ", ";
        }

        question_ = phrases_[rnd() % (phrases_.size() - 1)] + "\n" + question_;

        answer_.pop_back(); answer_.pop_back();
    }

 private:
    std::string question_, answer_;
};
