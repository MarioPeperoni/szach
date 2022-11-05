#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>
#include <chrono>

using namespace std;

struct theme
{
    string bgColor[2];
    string p1Color;
    string p2Color;
};

//Player figure map
char p1Fig[8][8];
char p2Fig[8][8];

bool ghostPath[8][8];
int playerPointer[2];   //Point to selected fig
int currentPlayerID = 1;
int settingsThemeSetId = 0;
theme themeSet[5];

bool canMove = false;

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
            canMove = true;
            break;

        case 'R':
            for (int i = y; i > 0; i--)
            {
                ghostPath[i][x] = true;
            }
            canMove = true;
            break;
        
        case 'N':
            if (y - 2 >= 0 && x - 1 >= 0)
            {
                ghostPath[y-2][x-1] = true;
            }
            if (y - 2 >= 0 && x + 1 <= 7)
            {
                ghostPath[y-2][x+1] = true;
            }
            canMove = true;
            break;

        case 'B':
            break;

        case 'Q':
            break;
        
        case 'K':
            if (y - 1 >= 0) //In front
            {
                ghostPath[y - 1][x] = true;
            }
            if (y + 1 <= 7) //Back
            {
                ghostPath[y + 1][x] = true;
            }
            if (x - 1 >= 0) //Left
            {
                ghostPath[y][x - 1] = true;
            }
            if (x + 1 <= 7) //Right
            {
                ghostPath[y][x + 1] = true;
            }
            if (y - 1 >= 0 && x - 1 >= 0)   //Front Left
            {
                ghostPath[y - 1][x - 1] = true;
            }
            if (y + 1 <= 7 && x + 1 <= 8)   //Back Right
            {
                ghostPath[y + 1][x + 1] = true;
            }
            if (y - 1 >= 0 && x + 1 <= 8)   //Front Right
            {
                ghostPath[y - 1][x + 1] = true;
            }
            if (y + 1 <= 7 && x - 1 >= 0)    //Back Left
            {
                ghostPath[y - 1][x - 1] = true;
            }
            canMove = true;
            break;
        
        default:
            canMove = false;
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
            canMove = true;
            break;

        case 'R':
            for (int i = y; i < 8; i++)
            {
                ghostPath[i][x] = true;
            }
            canMove = true;
            break;
        
        case 'N':
            if (y + 2 <= 7 && x - 1 >= 0)
            {
                ghostPath[y+2][x-1] = true;
            }
            if (y + 2 <= 7 && x + 1 <= 7)
            {
                ghostPath[y+2][x+1] = true;
            }
            canMove = true;
            break;

        case 'B':
            break;

        case 'Q':
            break;
        
        case 'K':
            if (y - 1 >= 0) //In front
            {
                ghostPath[y - 1][x] = true;
            }
            if (y + 1 <= 7) //Back
            {
                ghostPath[y + 1][x] = true;
            }
            if (x - 1 >= 7) //Left
            {
                ghostPath[y][x - 1] = true;
            }
            if (x + 1 <= 7) //Right
            {
                ghostPath[y][x + 1] = true;
            }
            if (y - 1 >= 0 && x - 1 >= 0)   //Front Left
            {
                ghostPath[y - 1][x - 1] = true;
            }
            if (y + 1 <= 7 && x + 1 <= 7)   //Back Right
            {
                ghostPath[y + 1][x + 1] = true;
            }
            if (y - 1 >= 0 && x + 1 <= 8)   //Front Right
            {
                ghostPath[y - 1][x + 1] = true;
            }
            if (y + 1 <= 7 && x - 1 >= 0)    //Back Left
            {
                ghostPath[y - 1][x - 1] = true;
            }
            canMove = true;
            break;
        
        default:
            canMove = false;
            break;
        }
    }
}

void renderBoard(bool renderPath, int themeID)    //Render board
{
    string boardNum[8] = {"8", "7", "6", "5", "4", "3", "2", "1"};
    int themeBGIndex = 0;
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
            if (themeBGIndex == 0)  //Create checkerboard pattern
            {
                themeBGIndex++;
            }
            else
            {
                themeBGIndex--;
            }
            cout << "║" << "\x1b[" << themeSet[themeID].bgColor[themeBGIndex] << "m \x1b[0m"; //Draw BG theme
            if (p1Fig[i][j] == 'E' && p2Fig[i][j] == 'E')   //If box is empty
            {
                cout << "\e[1m\x1b[" << themeSet[themeID].bgColor[themeBGIndex] << "m";
                if (renderPath == true && ghostPath[i][j] == true)  //Renders path of figure
                {
                    cout << "#";
                }
                else
                {
                    cout << " ";
                }
                cout << "\e[0m\x1b[0m";
            }
            if (p1Fig[i][j] == 'E' && p2Fig[i][j] != 'E')   //If player 2 have a figure in box 
            {
                cout << "\e[1m\x1b[" << themeSet[themeID].p2Color << ";" << themeSet[themeID].bgColor[themeBGIndex] << "m" << p2Fig[i][j] << "\e[0m\x1b[0m";   //Draw p2 figure
            }
            if (p1Fig[i][j] != 'E' && p2Fig[i][j] == 'E') //If player 1 have a figure in box 
            {
                cout << "\e[1m\x1b[" << themeSet[themeID].p1Color << ";" << themeSet[themeID].bgColor[themeBGIndex] << "m" << p1Fig[i][j] << "\e[0m\x1b[0m";   //Draw p1 figure
            }
            cout << "\x1b["<< themeSet[themeID].bgColor[themeBGIndex] << "m \x1b[0m║";
        }
        cout << makeSpace(1) << boardNum[i];    //Draw board numbers
        if (i == 4)
        {
            cout << makeSpace(6) << "Current player: " << currentPlayerID;
        }
        cout << endl;
        for (int j = 0; j < 8; j++)
        {
            cout << "╚═══╝";    //Draw lower frame
        }
        cout << endl;
        if (themeBGIndex == 0)  //Create offset for checkerboard pattern
        {
            themeBGIndex++;
        }
        else
        {
            themeBGIndex--;
        }
    }
    cout << "  A    B    C    D    E    F    G    H  " << endl; //Draw board letters
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

void movePiece(int x, int y, int player)
{
    char charBuff;
    if (ghostPath[y][x])    //If path is valid
    {
        switch (player)
        {
        case 1:
            charBuff = p1Fig[playerPointer[1]][playerPointer[0]];
            p1Fig[playerPointer[1]][playerPointer[0]] = 'E';
            p1Fig[y][x] = charBuff;
            canMove = false;
            break;
        
        case 2:
            charBuff = p2Fig[playerPointer[1]][playerPointer[0]];
            p2Fig[playerPointer[1]][playerPointer[0]] = 'E';
            p2Fig[y][x] = charBuff;
            canMove = false;
            break;
        }
    }
}

void getCOFromInput(int player, bool playerMove)  //Get coordinates from keyboard input
{
    string selectedFigXY;
    cin >> selectedFigXY;
    if (playerMove && canMove)
    {
        //selectedFigXY = "e2";
        movePiece(inputTranslator(selectedFigXY[0], true), inputTranslator(selectedFigXY[1], false), player);
    }
    else
    {
        //selectedFigXY = "e1";
        playerPointer[0] = inputTranslator(selectedFigXY[0], true);
        playerPointer[1] = inputTranslator(selectedFigXY[1], false);
        setGhostPath(inputTranslator(selectedFigXY[0], true), inputTranslator(selectedFigXY[1], false), player);
    }
}

void graphicRunnerloop()
{
    while(true)
    {
        renderBoard(true, settingsThemeSetId);
        sleep(1);
        renderBoard(false, settingsThemeSetId);
        sleep(1);
    }
}

void playerInputLoop()
{
    while (true)
    {
        while (canMove == false)
        {
            getCOFromInput(currentPlayerID, false);
        }
        getCOFromInput(currentPlayerID, true);
        cin.get();
        clearGhostPath();
        if (currentPlayerID == 2)
        {
            currentPlayerID = 1;
        }
        else
        {
            currentPlayerID = 2;
        }
    }
}

void initGame()
{
    themeSet[0] = (theme){.bgColor[0] = "42", .bgColor[1] = "43", .p1Color = "40", .p2Color = "30"};    //Green yellow
    themeSet[1] = (theme){.bgColor[0] = "44", .bgColor[1] = "46", .p1Color = "40", .p2Color = "30"};    //Blue cyan
    themeSet[2] = (theme){.bgColor[0] = "43", .bgColor[1] = "45", .p1Color = "40", .p2Color = "30"};    //Yellow magenta
    themeSet[3] = (theme){.bgColor[0] = "40", .bgColor[1] = "47", .p1Color = "40", .p2Color = "30"};    //White Black
    themeSet[4] = (theme){.bgColor[0] = "41", .bgColor[1] = "43", .p1Color = "40", .p2Color = "30"};    //Red Gold

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
    p2Fig[0][2] = 'B';
    p2Fig[0][5] = 'B';
    p2Fig[0][3] = 'Q';
    p2Fig[0][4] = 'K';
}

int main()
{
    initGame();
    renderBoard(true, settingsThemeSetId);
    thread graphicRunnerThread(graphicRunnerloop);
    thread playerInputThread(playerInputLoop);
    graphicRunnerThread.join();
    playerInputThread.join();
    return 0;
}