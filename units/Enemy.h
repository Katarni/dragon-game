//
// Created by Тимур Ахметзянов on 20.09.2024.
//

#pragma once

#include "Attacker.h"


class Enemy : public Attacker {
 public:
    Enemy(int health, int attack) : Attacker(health, attack) {}

    virtual bool isEnemy() final override {
        return true;
    }

    virtual std::string ask() = 0;
    virtual bool checkAns(const std::string& ans) = 0;

  protected:
    virtual void generateQuestion() = 0;

    std::vector<std::string> phrases_ = {
            "Try to answer this question!",
            "Ooh, it's my favorite question)",
            "No one has answered this question yet...",
            "This one is like a riddle from the sphinx",
            "I came up with this question while under the influence",
            "Even my king has no right answer"
    };
};
