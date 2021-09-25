
struct Tveb{
    Tveb(int uniSize);
    ~Tveb();

    const int uni;
    const int uniSqrt;

    const int lowerUnisqrt;
    const int lowerUnisqrt;

    int min;
    int max;
    Tveb * summary;
    Tveb ** cluster;

};

int low( Tveb * tree, int val);
int high( Tveb * tree, int val);
int index(Tveb * tree, int high, int low );



bool vebFind(Tveb *tree, int val);



