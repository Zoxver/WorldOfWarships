#include <stdlib.h>
#include <vector>
#include <iostream>
#include "Ship.cpp"



class ShipManager{
    private:
        int ships_amount;
        std::vector<Ship> ships;
    public:
        ShipManager(int ships_amount, std::initializer_list<int> ships_sizes) : ships_amount(ships_amount){
            if (ships_amount != ships_sizes.size()){
                throw std::invalid_argument("ships amount must be equal to lentgh of ships sizes");
            }

            for(int size : ships_sizes){
                ships.emplace_back(size);
            }
        }

        void attackShip(int shipIndex, int segmentIndex){
            if (shipIndex < 0 || shipIndex >= ships_amount){
                throw std::out_of_range("Invalid ship index");
            }
            ships[shipIndex].damageSegment(segmentIndex);
        }

        int getShipAmount() const{
            return ships_amount;
        }
};


int main(){





}
