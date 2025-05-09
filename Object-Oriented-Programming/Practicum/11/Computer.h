#pragma once

class Computer
{
public:
    Computer() = default;

    Computer(const Computer &other);
    Computer &operator=(const Computer &other);

    Computer(Computer &&other) noexcept;
    Computer &operator=(Computer &&other) noexcept;

    void setPower(int newPower);
    void setRamCapacity(int newRamCapacity);
    void setProcessorPower(double newProcessorPower);
    void setGraphicCardName(const char *newGraphicCardName);

    int getPower() const;
    int getRamCapacity() const;
    double getProcessorPower() const;
    char *getGraphicCardName() const;

    virtual void printDeviceType() const = 0;
    virtual void printAccessories() const = 0;

    virtual ~Computer();

private:
    int power = 0;
    int ramCapacity = 0;

    char *graphicCardName = nullptr;

    double processorPower = 0.0;

    void copyFrom(const Computer &other);
    void moveFrom(Computer &&other);

    void free();
};