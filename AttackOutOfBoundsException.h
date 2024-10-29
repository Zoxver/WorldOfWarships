#ifndef ATTACK_OUT_OF_BOUNDS_EXCEPTION_H
#define ATTACK_OUT_OF_BOUNDS_EXCEPTION_H

#include <exception>

class AttackOutOfBoundsException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Ошибка: Атака за границами поля.";
    }
};

#endif