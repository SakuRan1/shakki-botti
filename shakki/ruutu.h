#pragma once

class Ruutu {
public:
    Ruutu(int rivi, int sarake);
    Ruutu() {}
    int getRivi();
    int getSarake();
    void setRivi(int);
    void setSarake(int);
private:
    int _sarake;
    int _rivi;
};