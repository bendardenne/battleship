//
// Created by bdardenn on 08/09/17.
//

#include <vector>
#include <queue>
#include "PlaceShipsController.hpp"
#include "DefaultController.hpp"
#include "../ai/RandomShipPlacer.hpp"

const std::string &PlaceShipsController::DEFAULT_MESSAGE = "← → ↓ ↑: Move ship\tr: Rotate\tq: Quit";

PlaceShipsController::PlaceShipsController(GameWindow &window, GridWindow *gridWindow) :
        AController(window), _shipsToPlace(createShipsList(gridWindow->grid().fleet())), _gridWindow(gridWindow) {}

bool PlaceShipsController::finished() const {
    return _shipsToPlace.empty();
}


void PlaceShipsController::handleKey(int key) {
    _gameWindow.status(DEFAULT_MESSAGE);

    Grid &grid = _gridWindow->grid();
    std::shared_ptr<Ship> shipToPlace = _shipsToPlace.front();
    ShipLocation newLoc;
    RandomShipPlacer placer;


    int x, y;
    _gridWindow->_getyx(y, x);

    switch (key) {
        case KEY_UP:
            if (grid.moveShip(shipToPlace, y - 1, x)) _gridWindow->move(y - 1, x);
            break;
        case KEY_DOWN:
            if (grid.moveShip(shipToPlace, y + 1, x)) _gridWindow->move(y + 1, x);
            break;
        case KEY_LEFT:
            if (grid.moveShip(shipToPlace, y, x - 1)) _gridWindow->move(y, x - 1);
            break;
        case KEY_RIGHT:
            if (grid.moveShip(shipToPlace, y, x + 1)) _gridWindow->move(y, x + 1);
            break;
        case 'r' :
            newLoc = grid.rotateShip(shipToPlace);
            _gridWindow->move(newLoc.y, newLoc.x);
            break;
        case 's' :
            placer.placeShips(_gridWindow->grid());
            _shipsToPlace = std::queue<std::shared_ptr<Ship>>();
            break;
        case '\n':
            if (!anchorShip()) _gameWindow.status("Cannot place " + shipToPlace->name() + " here", MessageType::error);
            break;
        default:
            if (_next)
                _next->handleKey(key);
    }

    _gridWindow->redraw();
}

void PlaceShipsController::enable() {
    _gridWindow->move(0, 0);
    _gridWindow->grid().addShip(_shipsToPlace.front());
    _gridWindow->redraw();
    _gameWindow.status(DEFAULT_MESSAGE);
}

bool PlaceShipsController::anchorShip() {
    Grid &grid = _gridWindow->grid();

    if (!grid.anchorShip()) {
        return false;
    }

    _shipsToPlace.pop();

    // Still more shipLocations to place
    if (_shipsToPlace.size() > 0) {
        grid.addShip(_shipsToPlace.front());
        _gridWindow->move(0, 0);
    }

    return true;
}

std::queue<std::shared_ptr<Ship>>
PlaceShipsController::createShipsList(const std::vector<std::shared_ptr<Ship>> vector) {
    std::queue<std::shared_ptr<Ship>> c;
    for (auto s : vector) {
        c.push(s);
    }
    return c;
}
