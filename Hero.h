//
// Created by Тимур Ахметзянов on 20.09.2024.
//

#pragma once

#include "Attacker.h"


class Hero : public Attacker {
 public:
    Hero(const std::string& name, int health, int attack) : name_(name), Attacker(health, attack) {}
    Hero(std::string&& name, int health, int attack) : name_(std::move(name)), Attacker(health, attack) {}

    virtual bool isEnemy() final override {
        return false;
    }

    virtual void attack(Attacker* target) override {
        Attacker::attack(target);
        addAttack(2);
    }

 private:
    std::string name_;
};
