#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <stdexcept>

class Ship
{
public:
    enum class Orientation { horizontal, vertical };
    enum class ShipSize { oneDeck = 1, twoDeck, threeDeck, fourDeck };
    enum class SegmentHealth { destroyed = 0, damaged, intact };

private:
    ShipSize size;
    Orientation orientation;
    std::vector<SegmentHealth> segments;

public:
    Ship(int size, Orientation orientation = Orientation::horizontal);

    void checkSegmentIndex(int index) const;
    void damageSegment(int index);
    SegmentHealth getSegmentStatus(int index) const;
    ShipSize getSize() const;
    Orientation getOrientation() const;
    const std::vector<SegmentHealth>& getSegments() const;
};

#endif