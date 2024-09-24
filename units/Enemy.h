//
// Created by Тимур Ахметзянов on 20.09.2024.
//

#pragma once

#include "Attacker.h"


class Enemy : public Attacker {
 public:
    Enemy(int health, int attack, const std::string& name) : Attacker(health, attack, name) {}
    Enemy(int health, int attack, std::string&& name) : Attacker(health, attack, std::move(name)) {}

    virtual bool isEnemy() final override {
        return true;
    }

    virtual std::pair<std::string, std::string> ask() = 0;
    virtual bool checkAns(std::string ans) = 0;

  protected:
    virtual void generateQuestion() = 0;

    std::vector<std::string> phrases_ = {
            "Try to answer this question!",
            "Ooh, it's my favorite\nquestion)",
            "No one has answered\nthis question yet...",
            "This one is like a riddle\nfrom the sphinx",
            "I came up with this question\nwhile under the influence",
            "Even my king has\nno right answer"
    };
};
