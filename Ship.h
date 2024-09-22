#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <stdexcept>

class Ship
{
public:
    enum class Orientation { HORIZONTAL, VERTICAL };
    enum class ShipSize { ONE_DECK = 1, TWO_DECK, THREE_DECK, FOUR_DECK };
    enum class SegmentHealth { DESTROYED = 0, DAMAGED, INTACT };

private:
    ShipSize size;
    Orientation orientation;
    std::vector<SegmentHealth> segments;

public:
    Ship(int size, Orientation orientation = Orientation::HORIZONTAL);

    void damageSegment(int index);
    void setOrientation(Orientation orientation);
    ShipSize getSize() const;
    Orientation getOrientation() const;
    const std::vector<SegmentHealth>& getSegments() const;
};

#endif