#ifndef FIELD_SIZE_EXCEPTION_H
#define FIELD_SIZE_EXCEPTION_H

#include <exception>

class FieldSizeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Ошибка: Некорректные размеры поля.";
    }
};

#endif