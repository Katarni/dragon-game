//
// Created by Тимур Ахметзянов on 20.09.2024.
//

#pragma once

#include <algorithm>
#include <random>
#include <chrono>
#include "KatLib.h"

class Attacker {
 public:
    Attacker(int health, int attack,
             const std::string& name) : health_(health), attack_(attack),
                                        full_health_(health), x_(0), y_(0),
                                        name_(name) {}
    Attacker(int health, int attack,
             std::string&& name) : health_(health), attack_(attack),
                                        full_health_(health), x_(0), y_(0),
                                        name_(std::move(name)) {}

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
        health_ = std::min(full_health_, health_);
    }

    [[nodiscard]]
    int getFullHealth() const {
        return full_health_;
    }

    const std::string &getName() const {
        return name_;
    }

    void loadImages(const std::string& base, const std::string& low_hp) {
        base_image_.loadFromFile(base);
        low_hp_image_.loadFromFile(low_hp);
        calcCoordinates();
    }

    void loadBaseImage(const std::string& file) {
        base_image_.loadFromFile(file);
        calcCoordinates();
    }

    void loadLowHpImage(const std::string& file) {
        base_image_.loadFromFile(file);
        calcCoordinates();
    }

    virtual void render() {
        if (getHealth() < 0.3 * getFullHealth()) {
            low_hp_image_.render();
        } else {
            base_image_.render();
        }
    }

    void setX(float x) {
        x_ = x;
        calcCoordinates();
    }

    void setY(float y) {
        y_ = y;
        calcCoordinates();
    }

    void setRender(sf::RenderWindow* render) {
        low_hp_image_.setParent(render);
        base_image_.setParent(render);
    }

    void scale(float scale) {
        base_image_.scale(scale);
        low_hp_image_.scale(scale);
    }

 protected:
    kat::Image base_image_, low_hp_image_;

 private:
    int health_, attack_, full_health_;
    float x_, y_;

    std::string name_;

    void calcCoordinates() {
        float max_w = std::max(base_image_.getWidth(), low_hp_image_.getWidth());
        float max_h = std::max(base_image_.getHeight(), low_hp_image_.getHeight());

        base_image_.setX(x_ + (max_w - base_image_.getWidth()) / 2);
        low_hp_image_.setX(x_ + (max_w - low_hp_image_.getWidth()) / 2);

        base_image_.setY(y_ + max_h - base_image_.getHeight());
        low_hp_image_.setY(y_ + max_h - low_hp_image_.getHeight());
    }
};
