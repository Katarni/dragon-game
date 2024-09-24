//
// Created by Тимур Ахметзянов on 20.09.2024.
//

#pragma once

#include "Attacker.h"


class Hero : public Attacker {
 public:
    Hero(const std::string& name, int health, int attack) : Attacker(health, attack, name) {}
    Hero(std::string&& name, int health, int attack) : Attacker(health, attack, std::move(name)) {}

    virtual bool isEnemy() final override {
        return false;
    }

    virtual void attack(Attacker* target) override {
        Attacker::attack(target);
        addAttack(2);
    }
};
