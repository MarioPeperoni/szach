#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

char p1Fig[8][8];
char p2Fig[8][8];
bool ghostPath[8][8];
int playerPointer[2];
string boardNum[8] = {"8", "7", "6", "5", "4", "3", "2", "1"};

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
        switch (p1Fig[y][x])
        {
        case 'P':
            if (y - 1 >= 0)
            {
                ghostPath[y-1][x] = true;
            }
            if (y - 2 >= 0)
            {
                ghostPath[y-2][x] = true;
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
        switch (p2Fig[y][x])
        {
        case 'P':
            if (y + 1 <= 7)
            {
                ghostPath[y+1][x] = true;
            }
            if (y + 2 <= 7)
            {
                ghostPath[y+2][x] = true;
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
            if (p1Fig[i][j] == 'E' && p2Fig[i][j] == 'E')   //If box is empty
            {
                if (renderPath == true && ghostPath[i][j] == true)  //Renders path of figure
                {
                    cout << "#";
                }
                else
                {
                    cout << " ";
                }
            }
            if (p1Fig[i][j] == 'E' && p2Fig[i][j] != 'E')   //If player 2 have a figure in box 
            {
                cout << p2Fig[i][j];
            }
            if (p1Fig[i][j] != 'E' && p2Fig[i][j] == 'E') //If player 1 have a figure in box 
            {
                cout << p1Fig[i][j];
            }
            cout << " ║";
        }
        cout << makeSpace(1) << boardNum[i];    //Draw board numbers
        cout << endl;
        for (int j = 0; j < 8; j++)
        {
            cout << "╚═══╝";    //Draw lower frame
        }

        cout << endl;
    }
    cout << "  A    B    C    D    E    F    G    H  " << endl; //Draw board letters
    
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

int inputTranslator(char input, bool letters)
{
    if (letters)
    {
        switch (input)
        {
        case 'a':
            return 0;
            break;
        case 'b':
            return 1;
            break;
        case 'c':
            return 2;
            break;
        case 'd':
            return 3;
            break;
        case 'e':
            return 4;
            break;
        case 'f':
            return 5;
            break;
        case 'g':
            return 6;
            break;
        case 'h':
            return 7;
            break;
        } 
    }
    else
    {
        switch (input)
        {
        case '1':
            return 7;
            break;
        case '2':
            return 6;
            break;
        case '3':
            return 5;
            break;
        case '4':
            return 4;
            break;
        case '5':
            return 3;
            break;
        case '6':
            return 2;
            break;
        case '7':
            return 1;
            break;
        case '8':
            return 0;
            break;
        }
    }
    return 0;
}

void getCOFromInput(int player)  //Get coordinates from keyboard input
{
    string selectedFigXY;
    //cin >> selectedFigXY;
    selectedFigXY = "d7";

    setGhostPath(inputTranslator(selectedFigXY[0],true), inputTranslator(selectedFigXY[1], false), 2);
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