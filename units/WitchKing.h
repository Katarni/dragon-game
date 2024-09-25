//
// Created by Тимур Ахметзянов on 20.09.2024.
//

#pragma once

#include "Enemy.h"


class WitchKing : public Enemy {
 public:
    WitchKing(int health, int attack, const std::string& name) : Enemy(health, attack, name) {}
    WitchKing(int health, int attack, std::string&& name) : Enemy(health, attack, std::move(name)) {}

    [[nodiscard]]
    virtual std::pair<std::string, std::string> ask() override {
        generateQuestion();
        std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        return {phrases_[rnd() % phrases_.size()], question_};
    }

    virtual bool checkAns(std::string ans) override {
        while (!ans.empty() && ans[0] == ' ') {
            ans.erase(ans.begin());
        }
        while (!ans.empty() && ans.back() == ' ') {
            ans.pop_back();
        }

        std::vector<int> nums;
        int cur = 0;
        for (char c : ans) {
            if (c == ',') continue;

            if (c == ' ') {
                if (cur > 1) {
                    nums.push_back(cur);
                }
                cur = 0;
                continue;
            }

            if ('0' <= c && c <= '9') {
                cur = cur * 10 + c - '0';
            }
        }
        if (cur > 1) {
            nums.push_back(cur);
        }
        std::sort(nums.begin(), nums.end());
        return nums == answer_;
    }

 protected:
    virtual void generateQuestion() override {
        std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

        answer_.clear();

        int number = rnd() % 150 + 2;
        question_ = "factorize the number: " + std::to_string(number);
        for (int i = 2; i <= sqrt(number); ++i) {
            while (number % i == 0) {
                answer_.push_back(i);
                number /= i;
            }
        }
        if (number != 1) {
            answer_.push_back(number);
        }
    }

 private:
    std::string question_;
    std::vector<int> answer_;
};
