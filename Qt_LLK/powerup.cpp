#include "powerup.h"


#include <QtWidgets>
#include <QObject>
#include <QPixmap>

powerup::powerup(QWidget* parent) : QWidget(parent) { }
powerup::~powerup() { }

TimePowerUp::TimePowerUp(QWidget* parent) : powerup(parent) { }

void TimePowerUp::applyPowerUp()
{
    //timeLeft += 10;
}

ShufflePowerUp::ShufflePowerUp(QWidget* parent) : powerup(parent) { }

void ShufflePowerUp::applyPowerUp()
{
    // Implement shuffle power-up logic (e.g., shuffle the board)
}

FlashPowerUp::FlashPowerUp(QWidget* parent) : powerup(parent) { }

void FlashPowerUp::applyPowerUp()
{
    // Implement flash power-up logic (e.g., teleport character)
}
