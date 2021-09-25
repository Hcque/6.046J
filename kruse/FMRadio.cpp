#include <iostream>
using namespace std;

class FMRadio
{

public:
    FMRadio(double f, double v);
    double freq;
    double volume;
    double pset[6];
};


FMRadio::FMRadio( double f, double v ){
    f = 2;
    v = 2;
}

int main()
{
    FMRadio f(9,9) ;//= FMRadio();
    cout << f.freq << " " << f.volume  << " "
    << f.pset[2] << endl;

    return 0;
}
