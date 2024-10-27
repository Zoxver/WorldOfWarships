#include "Ship.h"

Ship::Ship(int size, Orientation orientation) : orientation(orientation), size(static_cast<ShipSize>(size)), segments(size, SegmentHealth::intact)
{
    if (size < static_cast<int>(ShipSize::oneDeck) || size > static_cast<int>(ShipSize::fourDeck))
    {
        throw std::invalid_argument("Invalid size for ship");
    }
}

bool Ship::isSunk() const
{
    for (Ship::SegmentHealth seg : segments)
    {
        if (seg != Ship::SegmentHealth::destroyed)
        {
            return false;
        }
    }
    return true;
}

void Ship::checkSegmentIndex(int index) const
{
    if (index < 0 || index >= static_cast<int>(size))
    {
        throw std::out_of_range("Invalid segment index");
    }
}

void Ship::damageSegment(int index)
{
    checkSegmentIndex(index);
    if (segments[index] == SegmentHealth::destroyed)
    {
        return;
    }
    segments[index] = static_cast<SegmentHealth>(static_cast<int>(segments[index]) - 1);
}

Ship::ShipSize Ship::getSize() const
{
    return size;
}

Ship::Orientation Ship::getOrientation() const
{
    return orientation;
}

Ship::SegmentHealth Ship::getSegmentStatus(int index) const
{
    Ship::checkSegmentIndex(index);
    return segments[index];

}

const std::vector<Ship::SegmentHealth>& Ship::getSegments() const
{
    return segments;
}