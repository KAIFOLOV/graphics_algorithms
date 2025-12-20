#ifndef IVNA_H
#define IVNA_H

#include <QDebug>

class IVna
{
public:
    virtual ~IVna() = default;

    virtual bool connect() = 0;
    virtual void setStartFrequency(double hz) = 0;
    virtual void setStopFrequency(double hz) = 0;
    virtual void setPoints(int pts) = 0;
    virtual int getNumber() = 0;
    virtual bool isPower() = 0;
    virtual void printNumber(int number) = 0;
};

class FakeVna : public IVna
{
public:
    bool connect() override {
        qInfo() << "connect";
        return true;
    }
    void setStartFrequency(double hz) override {
        qInfo() << "setStartFrequency" << hz;
    }
    void setStopFrequency(double hz) override {
        qInfo() << "setStopFrequency" << hz;
    }
    void setPoints(int pts) override {
        qInfo() << "setPoints" << pts;
    }
    int getNumber() override {
        qInfo() << "getNumber";
        return 8;
    }
    bool isPower() override {
        qInfo() << "isPower";
        return true;
    }
    void printNumber(int number) override {
        qInfo() << "printNumber" << number;
    }
};

#endif // IVNA_H
