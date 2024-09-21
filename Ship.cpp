#include <stdlib.h>
#include <vector>
#include <iostream>



class Ship{
    public:
        enum class Orientation {
            HORIZONTAL,
            VERTICAL
        };

        enum class ShipSize {
            ONE_DECK = 1,
            TWO_DECK = 2,
            THREE_DECK = 3,
            FOUR_DECK = 4
        };

        enum class SegmentHealth {
            DESTROYED = 0,  
            DAMAGED = 1,
            INTACT = 2
        };
    private:
        ShipSize size;
        Orientation orientation;
        std::vector<SegmentHealth> segments;
    public:
        Ship(int size, Orientation orientation = Orientation::HORIZONTAL) : orientation(orientation) {
            if (size < static_cast<int>(ShipSize::ONE_DECK) || size > static_cast<int>(ShipSize::FOUR_DECK)) {
                throw std::invalid_argument("Invalid size for ship");
            }
            this->size = static_cast<ShipSize>(size);
            segments = std::vector<SegmentHealth>(size, SegmentHealth::INTACT);
        }

        void damageSegment(int index){
            if (index < 0 || index >= static_cast<int>(size)){
                throw std::out_of_range("Invalid segment index");
            }
            if (segments[index] == SegmentHealth::DESTROYED){
                return;
            }
            segments[index] = static_cast<SegmentHealth>(static_cast<int>(segments[index]) - 1);
        }

        void setOrientation(Orientation orientation){
            this->orientation = orientation;
        }

        ShipSize getSize() const {
            return size;
        }

        Orientation getOrientation() const {
            return orientation;
        }

        const std::vector<SegmentHealth>& getSegments() const {
            return segments;
        }
};


int main(){
    Ship sh = Ship(4, Ship::Orientation::HORIZONTAL);
    for (auto i = 0; i<(int)sh.getSize(); i++){
        std::cout << (int)sh.getSegments()[i] << std::endl;
    }
    // sh.damageSegment(0);
    // sh.damageSegment(0);
    // sh.damageSegment(0);
    // sh.damageSegment(1);
    // sh.damageSegment(1);
    // sh.damageSegment(1);
    // sh.damageSegment(2);
    // sh.damageSegment(2);
    // sh.damageSegment(2);
    // sh.damageSegment(3);
    // sh.damageSegment(3);
    // sh.damageSegment(3);
    // sh.damageSegment(4);
    // sh.damageSegment(4);
    // sh.damageSegment(4);
    for (auto i = 0; i<(int)sh.getSize(); i++){
        std::cout << (int)sh.getSegments()[i] << std::endl;
    }





}
