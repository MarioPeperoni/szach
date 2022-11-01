#include <iostream>

char p1Fig[8][8];
char p2Fig[8][8];

using namespace std;


void renderFig(int playerID)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (p1Fig[i][j] == 'E' && p2Fig[i][j] == 'E')
            {
                cout << "▄";
            }
            if (p1Fig[i][j] == 'E' && p2Fig[i][j] != 'E')
            {
                cout << p2Fig[i][j];
            }
            if (p1Fig[i][j] != 'E' && p2Fig[i][j] == 'E')
            {
                cout << p1Fig[i][j];
            }
            cout << " ";
        }
        
        cout << endl;
        
    }
    
}

void initGame()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            p1Fig[i][j] = 'E';
            p2Fig[i][j] = 'E';
        }
        
    }

    //P1 init
    for (int i = 0; i < 8; i++)
    {
        p1Fig[6][i] = 'P';
    }
    p1Fig[7][0] = 'T';
    p1Fig[7][7] = 'T';


    //P2 init
    for (int i = 0; i < 8; i++)
    {
        p2Fig[1][i] = 'P';
    }
    
    
    
}

int main()
{
    initGame();
    renderFig(1);
    return 0;
}