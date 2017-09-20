#include "Grid.hpp"
#include "Cell.hpp"
#include "ShipLocation.hpp"

Grid::Grid(size_t width, size_t height) : _width(width), _height(height), _ships(createShipsList()), _placing(nullptr) {
    _cells = std::vector<std::vector<Cell>>(_width);
    for (size_t i = 0; i < _width; i++) {
        _cells[i].resize(_height);
        for (auto j = 0; j < _height; j++) {
            _cells[i][j] = {.ship = nullptr, .status = CellStatus::clean};
        }
    }
}

Grid::Grid(const Grid &other) : _width(other._width), _height(other._height), _placing(other._placing),
                                _shipLocations(other._shipLocations), _ships(other._ships), _cells(other._cells) {

}

size_t Grid::width() const {
    return _width;
}

size_t Grid::height() const {
    return _height;
}

Cell Grid::operator()(size_t y, size_t x) const {
    return _cells[x][y];
}

void Grid::shoot(size_t y, size_t x) {
    _cells[x][y].status = CellStatus::hit;
   std::shared_ptr<Ship> ship = _cells[x][y].ship;
    if(ship){
        ship->hit(getShipHitZone(y, x, _shipLocations.at(*ship)));
    }
}

void Grid::addShip(std::shared_ptr<Ship> ship) {
    ShipLocation location = {.x = 0, .y = 0, .orientation = Orientation::horizontal};
    _shipLocations[*ship] = location;
    _placing = ship;
}

bool Grid::moveShip(std::shared_ptr<Ship> ship, int y, int x) {
    if (y < 0 || x < 0 || y == height() || x == width()) return false;

    ShipLocation &location = _shipLocations[*ship];
    if (location.orientation == Orientation::horizontal && x + ship->length() > width()) return false;
    if (location.orientation == Orientation::vertical && y + ship->length() > height()) return false;

    location.x = x;
    location.y = y;

    return true;
}

ShipLocation& Grid::rotateShip(std::shared_ptr<Ship> ship) {
    ShipLocation &location = _shipLocations[*ship];

    if (location.orientation == Orientation::vertical) {
        location.orientation = Orientation::horizontal;
        if ((location.x + ship->length()) > width()) {
            location.x = width() - ship->length();
        }
    } else {
        location.orientation = Orientation::vertical;
        if ((location.y + ship->length()) > height()) {
            location.y = height() - ship->length();
        }
    }

    return location;
}

const std::map<Ship, ShipLocation> Grid::shipLocations() const {
    return _shipLocations;
}


const std::shared_ptr<Ship> Grid::placing() const {
    return _placing;
}

bool Grid::anchorShip(std::shared_ptr<Ship> ship, ShipLocation location) {
    size_t y = location.y;
    size_t x = location.x;
    // Check for collisions
    for (size_t i = 0; i < ship->length(); i++) {
        if( x >= width() || y >= height()) return false;
        if ((*this)(y, x).ship) return false;
        location.orientation == Orientation::horizontal ? x++ : y++;
    }

    y = location.y;
    x = location.x;

    // Actually place the ship
    for (size_t i = 0; i < ship->length(); i++) {
        _cells[x][y].ship = std::shared_ptr<Ship>(ship);
        location.orientation == Orientation::horizontal ? x++ : y++;
    }

    _shipLocations[*ship] = location;
    return true;
}

bool Grid::anchorShip() {
    std::shared_ptr<Ship> ship = _placing;
    ShipLocation &location = _shipLocations[*ship];

    if(anchorShip(ship, location)) {
        _placing = nullptr;
        return true;
    }
    return false;
}

const std::vector<std::shared_ptr<Ship>> Grid::fleet() const {
    return _ships;
}

const std::vector<std::shared_ptr<Ship>> Grid::createShipsList() {
    std::vector<std::shared_ptr<Ship>> ships;
    ships.push_back(std::shared_ptr<Ship>(new Ship(5)));
    ships.push_back(std::shared_ptr<Ship>(new Ship(4)));
    ships.push_back(std::shared_ptr<Ship>(new Ship(3)));
    ships.push_back(std::shared_ptr<Ship>(new Ship(3)));
    ships.push_back(std::shared_ptr<Ship>(new Ship(2)));

    return ships;
}

size_t Grid::getShipHitZone(size_t y, size_t x, ShipLocation &shipLocation) {
    if(shipLocation.orientation == Orientation::horizontal) {
        return x - shipLocation.x;
    }
    return y - shipLocation.y;
}

