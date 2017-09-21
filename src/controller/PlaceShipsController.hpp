//
// Created by bdardenn on 08/09/17.
//
#pragma once

#include <queue>

#include "AController.hpp"
#include "../model/Ship.hpp"
#include "../ui/VisibleGridWindow.hpp"

class PlaceShipsController : public AController {
public:
    PlaceShipsController(GameWindow& window, GridWindow& gridWindow);
    void handleKey(int key) override ;
    bool enabled() const override;
    void enable() override;

protected:
    std::queue<std::shared_ptr<Ship>> _shipsToPlace;
    bool anchorShip();

private:
    static const std::string &DEFAULT_MESSAGE;
    GridWindow& _gridWindow;

    std::queue<std::shared_ptr<Ship>> createShipsList(std::vector<std::shared_ptr<Ship>> vector);
};