//
// Created by Тимур Ахметзянов on 20.09.2024.
//

#pragma once

#include <algorithm>
#include <random>
#include <chrono>

class Attacker {
 public:
    Attacker(int health, int attack) : health_(health), attack_(attack) {}

    [[nodiscard]]
    bool isAlive() const {
        return health_ != 0;
    }

    virtual void attack(Attacker* target) {
        target->health_ -= attack_;
        target->health_ = std::max(0, target->health_);
    }

    virtual bool isEnemy() = 0;

    void addAttack(int delta) {
        attack_ += delta;
    }

    [[nodiscard]]
    int getHealth() const {
        return health_;
    }

    [[nodiscard]]
    int getAttack() const {
        return attack_;
    }

    void heal(int delta) {
        health_ += delta;
    }

 private:
    int health_, attack_;
};
