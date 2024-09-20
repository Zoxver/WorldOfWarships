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
            TREE_DECK = 3,
            FOUR_DECk = 4
        };

        enum class SegmentHealth {
            DESTROYED = 0,  
            DAMAGED = 1,
            INTACT = 2
        };
        ShipSize size;
        Orientation orientation;
        std::vector<SegmentHealth> segments;
        Ship(int size, Orientation Orientation) : size(ShipSize(size)), orientation(Orientation), segments(size, SegmentHealth::INTACT) {
        }

        void damageSegment(int index){
            if (index < 0 || index >= (int)this->size){
                return;
            }
            if (segments[index] == SegmentHealth::DESTROYED){
                return;
            }
            segments[index] = SegmentHealth((int)segments[index] - 1);
        }

        ShipSize getSize(){
            return this->size;
        }

        Orientation getOrientation(){
            return this->orientation;
        }

        std::vector<SegmentHealth>& getSegments(){
            return this->segments;
        }
        

    private:

       


};


int main(){
    Ship sh = Ship(4, Ship::Orientation::HORIZONTAL);
    for (auto i = 0; i<(int)sh.size; i++){
        std::cout << (int)sh.segments[i] << std::endl;
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
    for (auto i = 0; i<(int)sh.size; i++){
        std::cout << (int)sh.segments[i] << std::endl;
    }





}
