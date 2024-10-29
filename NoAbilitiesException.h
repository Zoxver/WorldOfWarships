#ifndef NO_ABILITIES_EXCEPTION_H
#define NO_ABILITIES_EXCEPTION_H

#include <exception>

class NoAbilitiesException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Ошибка: Нет доступных способностей.";
    }
};

#endif