#pragma once

#include <iostream>
#include <map>
#include "Ship.hpp"
#include "Cell.hpp"

class Grid {

public:
    Grid(size_t width, size_t height);
    Grid(const Grid &other);

    size_t width() const;
    size_t height() const;
    Cell operator()(size_t y, size_t x) const; // [] operator ????

    const std::map<Ship, ShipLocation> shipLocations() const;
    const std::vector<std::shared_ptr<Ship>> fleet() const;

    void addShip(std::shared_ptr<Ship> ship);
    bool moveShip(std::shared_ptr<Ship> ship, int y, int x);
    ShipLocation &rotateShip(std::shared_ptr<Ship> ship);
    bool anchorShip();
    bool anchorShip(std::shared_ptr<Ship> ship, ShipLocation location);
    const std::shared_ptr<Ship> placing() const;
    void shoot(size_t y, size_t x);
protected:
private:
    size_t _width;
    size_t _height;
    std::shared_ptr<Ship> _placing;
    std::map<Ship, ShipLocation> _shipLocations;
    const std::vector<std::shared_ptr<Ship>> _ships;
    std::vector<std::vector<Cell>> _cells;

    const std::vector<std::shared_ptr<Ship>> createShipsList();
    size_t getShipHitZone(size_t y, size_t x, ShipLocation &shipLocation);
};
