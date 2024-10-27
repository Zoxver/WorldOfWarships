#ifndef ABILITIES_H
#define ABILITIES_H

#include <iostream>
#include "IAbility.h"
#include "GameField.h"

class DoubleDamageAbility : public IAbility {
public:
    DoubleDamageAbility(GameField& field);
    void activate() override;
    void getParams() override;

private:
    GameField& field;
    int x, y;
};

class ScannerAbility : public IAbility {
public:
    ScannerAbility(GameField& field);
    void activate() override;
    void getParams() override;

private:
    GameField& field;
    int x, y;
};

class RandomFireAbility : public IAbility {
public:
    RandomFireAbility(GameField& field);
    void activate() override;
    void getParams() override;

private:
    GameField& field;
};

#endif