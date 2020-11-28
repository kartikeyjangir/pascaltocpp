#include <iostream>
#define ARRMAX 40  //arrmax =maximum no of cubes
#define CUBEMAX 11 //cubemax = maximum no inputs and outputs
using namespace std;

//GLOBAL DECLARATIONS
int arrsize = ARRMAX, cubesize = CUBEMAX;
typedef int cube[CUBEMAX][2]; // using typedef to avoid bool and logic
struct larray
{
    int NoInputs = cubesize;
    int NoOutputs = cubesize;
    int NoCubes = arrsize;
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
void writecube(cube c,int ni,int no){
    int n;
    n=ni+no;
    for (int j = 0; j <=n; j++)
    {
        if (j=ni+1)
        cout<<" ";
        if(c[j][0]=='0')
        cout<<"0";
        else if(c[j][1]=='1')
        cout<<"1";
        else if (j>ni)
        cout<<"-";
        else
        cout<<"x";

        
    }
    
}


//prodecure writearray
void writearray(larray a){
    int i;
    if(a.NoCubes=='0')
    cout<<"PRINTING ARRAY: empty array\n";
    else
    for ( i = 1; i <=a.NoCubes; i++)
    {
        writecube(a.cubes[i],a.NoInputs,a.NoOutputs);
        cout<<endl;

    }
    
}

int main()
{

    return 0;
}