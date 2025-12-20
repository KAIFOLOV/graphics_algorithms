#ifndef IVNA_H
#define IVNA_H

#include <QDebug>

class IVna
{
public:
    virtual ~IVna() = default;

    virtual bool connect() = 0;
    virtual bool setStartFrequency(double hz) = 0;
    virtual bool setStopFrequency(double hz) = 0;
    virtual bool setPoints(int pts) = 0;
    virtual int getNumber() = 0;
    virtual void printNumber(int number) = 0;
};

class FakeVna : public IVna
{
public:
    bool connect() override {
        qInfo() << "connect";
        return true;
    }
    bool setStartFrequency(double hz) override {
        qInfo() << "setStartFrequency" << hz;
        return true;
    }
    bool setStopFrequency(double hz) override {
        qInfo() << "setStopFrequency" << hz;
        return true;
    }
    bool setPoints(int pts) override {
        qInfo() << "setPoints" << pts;
        return true;
    }
    int getNumber() override {
        qInfo() << "getNumber";
        return 8;
    }
    void printNumber(int number) override {
        qInfo() << "printNumber" << number;
    }

};

#endif // IVNA_H
