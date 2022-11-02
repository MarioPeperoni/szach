#include <iostream>
#include <string>

using namespace std;

char p1Fig[8][8];
char p2Fig[8][8];
string uiText[8] = {"test1", "test2", "test3", "test4", "test5", "test6", "test7", "test8"};

string makeSpace(int size)
{
    string res = "";
    for (int i = 0; i < size; i++)
    {
        res+=" ";
    }
    return res;
}

void renderFig(int playerID)    //Render board
{
    system("clear");
    for (int i = 0; i < 8; i++)
    {      
        for (int j = 0; j < 8; j++)
        {
            cout << "╔═══╗";
        }
        cout << endl;
        for (int j = 0; j < 8; j++) //Render figures
        {
            cout << "║ ";
            if (p1Fig[i][j] == 'E' && p2Fig[i][j] == 'E')
            {
                cout << " ";
            }
            if (p1Fig[i][j] == 'E' && p2Fig[i][j] != 'E')
            {
                cout << p2Fig[i][j];
            }
            if (p1Fig[i][j] != 'E' && p2Fig[i][j] == 'E')
            {
                cout << p1Fig[i][j];
            }
            cout << " ║";
        }
        cout << makeSpace(10) << uiText[i];
        cout << endl;
        for (int j = 0; j < 8; j++)
        {
            cout << "╚═══╝";
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
    p1Fig[7][0] = 'R';
    p1Fig[7][7] = 'R';
    p1Fig[7][1] = 'N';
    p1Fig[7][6] = 'N';
    p1Fig[7][2] = 'B';
    p1Fig[7][5] = 'B';
    p1Fig[7][3] = 'Q';
    p1Fig[7][4] = 'K';


    //P2 init
    for (int i = 0; i < 8; i++)
    {
        p2Fig[1][i] = 'P';
    }
    p2Fig[0][0] = 'R';
    p2Fig[0][7] = 'R';
    p2Fig[0][1] = 'N';
    p2Fig[0][6] = 'N';
    p1Fig[0][2] = 'B';
    p1Fig[0][5] = 'B';
    p1Fig[0][3] = 'Q';
    p1Fig[0][4] = 'K';
}

int main()
{
    initGame();
    renderFig(1);
    
    return 0;
}