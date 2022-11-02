#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

char p1Fig[8][8];
char p2Fig[8][8];
bool ghostPath[8][8];
int playerPointer[2];
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

void clearGhostPath()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            ghostPath[i][j] = false;
        }
        
    }
    
}

void setGhostPath(int x , int y, int player)
{
    if (player == 1)    //Player 1 
    {
        switch (p1Fig[x][y])
        {
        case 'P':
            if (x - 1 >= 0)
            {
                ghostPath[x-1][y] = true;
            }
            if (x - 2 >= 0)
            {
                ghostPath[x-2][y] = true;
            }
            break;

        case 'R':
            
            break;
        
        case 'N':
            break;

        case 'B':
            break;

        case 'Q':
            break;
        
        case 'K':
            break;
        
        default:
            break;
        }
    }
    else                //Player 2
    {
        switch (p2Fig[x][y])
        {
        case 'P':
            if (x - 1 <= 7)
            {
                ghostPath[x+1][y] = true;
            }
            if (x - 2 <= 7)
            {
                ghostPath[x+2][y] = true;
            }
            break;

        case 'R':
            break;
        
        case 'N':
            break;

        case 'B':
            break;

        case 'Q':
            break;
        
        case 'K':
            break;
        
        default:
            break;
        }
    }
}

void renderBoard(int playerID, bool renderPath)    //Render board
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
                if (renderPath == true && ghostPath[i][j] == true)
                {
                    cout << "#";
                }
                else
                {
                    cout << " ";
                }
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
        cout << makeSpace(2) << uiText[i];
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
    clearGhostPath();   //Ghost path init
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

void getCOFromInput(int player)  //Get coordinates from keyboard input
{
    string selectedFigXY;
    cin >> selectedFigXY;
    playerPointer[0] = (int)selectedFigXY[0] - 49;
    playerPointer[1] = (int)selectedFigXY[1] - 49;
    setGhostPath((int)selectedFigXY[0] - 49, (int)selectedFigXY[1] - 49, player);
}

int main()
{
    initGame();
    getCOFromInput(1);
    while (true)
    {
        renderBoard(1 , true);
        sleep(1);
        renderBoard(1, false);
        sleep(1);
    }

    //renderBoard(1 , true);
    
    return 0;
}