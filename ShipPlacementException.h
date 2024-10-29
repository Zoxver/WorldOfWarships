#ifndef SHIP_PLACEMENT_EXCEPTION_H
#define SHIP_PLACEMENT_EXCEPTION_H

#include <exception>

class ShipPlacementException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Ошибка: Корабль не может быть размещен по этим координатам";
    }
};

#endif