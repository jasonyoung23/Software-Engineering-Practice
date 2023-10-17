#ifndef POWERUP_H
#define POWERUP_H

#include <QtWidgets>
#include <QObject>

class powerup : public QWidget{

    Q_OBJECT

public:
    powerup(QWidget *parent = nullptr);
    ~powerup();

    virtual void applyPowerUp() = 0;

private:
};

class TimePowerUp : public powerup{

    Q_OBJECT

public:
    TimePowerUp(QWidget* parent = nullptr);
    void applyPowerUp() override;
};

class ShufflePowerUp : public powerup{

    Q_OBJECT

public:
    ShufflePowerUp(QWidget* parent = nullptr);
    void applyPowerUp() override;
};

class FlashPowerUp : public powerup{

    Q_OBJECT

public:
    FlashPowerUp(QWidget* parent = nullptr);
    void applyPowerUp() override;
};

#endif // POWERUP_H
