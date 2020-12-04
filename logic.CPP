#include <iostream>
#define ARRMAX 40  //arrmax =maximum no of cubes
#define CUBEMAX 11 //cubemax = maximum no inputs and outputs
using namespace std;

//GLOBAL DECLARATIONS
int arrsize = ARRMAX, cubesize = CUBEMAX;
typedef int cube[CUBEMAX][2]; // using typedef to avoid bool and logic
struct larray
{
    int NoInputs;
    int NoOutputs;
    int NoCubes;
    int cubes[ARRMAX][CUBEMAX][2]; //we have use arrmax and cubemax bz we cant have varialble as dimensions
};
char smalldetails[3];

enum errtype
{
    INITTMV,
    COMBUNV,
    COMBAOV,
    CHNGCOR,
    DELCUNC,
    APCUAOV,
    SHRPUNV,
    INTXAOV,
    INTXUNV,
    CONSAOV
};

//prodecure error
void error(errtype e1)
{
    switch (e1)
    {
    case INITTMV:
        cout << "INITTMV:too many variable" << endl;
        break;
    case COMBUNV:
        cout << "COMBINE:unequal number of variables" << endl;
        break;
    case COMBAOV:
        cout << "COMBINE:array overflow" << endl;
        break;
    case CHNGCOR:
        cout << "CHANGECOLUMN:column out of range" << endl;
        break;
    case DELCUNC:
        cout << "DELETECUBE : nonexistent cube" << endl;
        break;
    case APCUAOV:
        cout << "APPENDCUUUBE:array overflow" << endl;
        break;
    case SHRPUNV:
        cout << " SHARPS: unequal number of variables" << endl;
        break;
    case INTXAOV:
        cout << "INTERSECTION :array overflow" << endl;
        break;
    case INTXUNV:
        cout << " INTERSECTION :unequal number of variables" << endl;
        break;
    case CONSAOV:
        cout << "CONSENSUS : array overflow" << endl;
        break;
    }
}

//prodecure initcube
void initcube(cube a)
{
    int i = cubesize;
    for (i = 1; i <= cubesize; i++)
    {
        a[i][0] = {0};
        a[i][1] = {1};
    }
}

//prodecure initarray
//we havent used arrsize and cudbesize here bz they r just int types
void initarray(larray a, int ncubes, int ninputs, int noutputs)
{
    int i = arrsize;
    if (ninputs + noutputs > CUBEMAX)
        error(INITTMV);
    a.NoInputs = ninputs;
    a.NoOutputs = noutputs;
    a.NoCubes = ncubes;
    for (int j = 0; j < ncubes; j++)
    {
        initcube(a.cubes[j]);
    }
}

//prodecure readarray
void readarray(larray a)
{
    int i; // arrsize is int type;
    int j; //cubesize is int type;
    char c;
    bool err;
    int ncubes;
    int ninputs, noutputs;

    cin >> ncubes;
    cin >> ninputs >> noutputs;
    initarray(a, ncubes, ninputs, noutputs);
    for (int i = 1; i <= ncubes; i++)
    {
        do
        {
            err = false;
            for (int j = 1; j < (ninputs + noutputs); j++)
            {
                if (!err)
                    cin >> c;
                while (c = ' ')
                {
                    cin >> c;
                }

                if (c != '0' || c != '1' || c != 'x' || c != 'X')
                {
                    cout << c << "is not valid character\n";
                    break;
                }
                else
                {
                    if (c = '0')
                    {
                        a.cubes[i][j][0] = {0};
                    }
                    else if (c = '1')
                        a.cubes[i][j][1] = {1};
                    //else is skiped temporaryly
                }
            }
            // if(!err)
            // not clear ask to sir

        } while (!err);
    }
}

//prodecure writecube
void writecube(cube c, int ni, int no)
{
    int n;
    n = ni + no;
    for (int j = 0; j <= n; j++)
    {
        if (j = ni + 1)
            cout << " ";
        if (c[j][0] == '0')
            cout << "0";
        else if (c[j][1] == '1')
            cout << "1";
        else if (j > ni)
            cout << "-";
        else
            cout << "x";
    }
}

//prodecure writearray
void writearray(larray a)
{
    int i;
    if (a.NoCubes == '0')
        cout << "PRINTING ARRAY: empty array\n";
    else
        for (i = 1; i <= a.NoCubes; i++)
        {
            writecube(a.cubes[i], a.NoInputs, a.NoOutputs);
            cout << endl;
        }
}

//judt prototypes
void combine(larray a, larray b);
void changecolumn(larray a, int b, char);
void deletecube(larray a, int b);
void cubecost();
bool cubex(cube a, cube b, cube c, int n);

//procedure movecube
void movecube(larray a, larray b, int cubeno)
{
    initarray(a, 1, b.NoInputs, b.NoOutputs);
    a.cubes[ARRMAX][CUBEMAX][1] = b.cubes[ARRMAX][CUBEMAX][cubeno]; //not Sure about this line
    deletecube(b, cubeno);
}

//procedure appendcube COMPLETE
void appendcube(larray a, int b)
{
    if (a.NoCubes + 1 < ARRMAX)
    {
        a.NoCubes += 1;
        a.cubes[ARRMAX][CUBEMAX][a.NoCubes] = b;
    }
    else
    {
        error(APCUAOV);
    }
}

//procedure subsome COMPLETE
bool subsume(cube a, cube b, int n)
{
    int i = 1;
    bool flag = false;
    while ((!flag) && i <= n)
    {
        if (a[CUBEMAX][i] - b[CUBEMAX][i] != NULL) 
        {
            flag = true;
        }
        else
        {
            ++i;
        }
    }
    return flag;
}

// procedure absorb
void absorb(larray a)
{
    int i, j, nvars;
    if (a.NoCubes > 0)
    {
        i = 1;
        nvars = a.NoInputs + a.NoOutputs;
        while (i <= a.NoCubes - 1)
        {
            j = i + 1;
            while (j <= a.NoCubes)
            {
                if (subsume(a.cubes[ARRMAX][CUBEMAX][i], a.cubes[ARRMAX][CUBEMAX][i], nvars))
                {
                    deletecube(a, i);
                    continue;
                }
                else if (a.cubes[CUBEMAX][i], a.cubes[CUBEMAX][i], nvars)
                    {
                        deletecube(a, i);
                    }
                else
                {
                    ++j;
                }
            }
            ++i;
        }
    }
}

//procedure shrap
void sharp(larray a, larray b, larray c)
{
    int nvars, j, k;
    larray t;
    //procedure cube sharp
    void sharp(larray x, cube a, cube b, int n)
    {
        int i;
        bool y;
        cube c;
        if (!cubex(c, b, a, n))
        {
            x.NoCubes = 1;
            x.Cubes[ARRMAX][CUBEMAX][1] = a;
        }
        else
        {
            x.NoCubes = 0;
            for (i = 1; i < N; I++)
            {
                //DONT KNOW
            }
        }
    }
}

//procedure spilt
void spiltarray(larray a, larray b, cube mask)
{
    int j, nvars;
    initarray(b, 0, a.NoInputs, a.NoOutputs);
    nvars = a.NoOutputs + a.NoInputs;
    if (a.NoCubes > 0)
        j = 1;
    while (j <= a.NoCubes && a.NoCubes > 0)
    {
        if (subsume(a.cubes[j], mask, nvars))
        {
            appendcube(b, a.cubes[j]);
            deletecube(a, j);
        }
        else
        {
            ++j;
        }
    }
}

//procedure intersection
void intersection(larray a, larray b, larray c)
{
    int i, j, nv;
    initarray(a, 0, b.NoInputs, b.NoOutputs);
    if (b.NoInputs + b.NoOutputs == c.NoOutputs + c.NoInputs)
    {
        nv = b.NoInputs + b.NoOutputs;
        for (i = 1; i <= b.NoCubes; i++)
        {
            for (j = 1; j <= c.NoCubes; j++)
            {
                if (a.NoCubes + 1 > ARRMAX)
                    error(INTXAOV);
                else if (cubex(a.cubes(a.NoCubes + 1), b.cubes[i], c.cubes[j], nv))
                {
                    ++a.NoCubes;
                    if (a.NoCubes + 1 > ARRMAX / 2)
                        absorb(a);
                }
            }
            absorb(a);
        }
        error(INTXUNV);
    }
}

//procedure coknsensus 
void consensus(larray a)
{
    int i, j, nv;
    larray b, c, d;
    cube mask, all0mask;
    nv = a.NoInputs + a.NoOutputs;
    for (j = a.NoInputs + 1; j <= nv; j++)
    {
        //  clearchangecolumn(a,j,)   this is commented bz its not
    }
    initcube(mask);
    if (a.NoOutputs > 0)
        initcube(all0mask);
    for (j = a.NoInputs + 1; j <= nv; j++)
    {
        all0mask[j][0] = 0;
        all0mask[j][1] = 0;
    }
    for (i = 1; i <= a.NoInputs; i++)
    {
        mask[i][0] = 1;
        mask[i][1] = 1;
        spiltarray(b, a, mask);
        mask[i][0] = 0;
        mask[i][1] = 0;
        spiltarray(c, a, mask);
        combine(a, b);
        combine(a, c);
        if (b.NoCubes > 0 && c.NoCubes > 0)
        {
            changecolumn(b, i, 'xxx');
            changecolumn(c, i, 'xxx');
            intersection(d, b, c);
            initcube(mask);
            if (a.NoInputs > 0 && d.NoCubes > 0)
            {
                spiltarray(b, d, all0mask);
            }
            absorb(a);
            if (a.NoCubes + d.NoCubes > ARRMAX)
            {
                error(CONSAOV);
            }
            combine(a, d);
            absorb(a);
        }
        mask[i][0] = 0;
        mask[i][1] = 1;
    }
}
int main()
{
    // khyati u have to do this o;ne  domain;
    return 0;
}