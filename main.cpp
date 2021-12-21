#include <iostream>
#include<iomanip>
#include<windows.h>
#include<conio.h>
#include <chrono>

using namespace std;

int MAX = 100;
const int ObjectNumber = 5;


char ObjectArray [18][ObjectNumber];

//void ResetGL (int, int&);
void InitializeGame();
void gotoxy(int xpos, int ypos);
void SetGamScr (int clk, int score, int state, int dst);
void ResetGL (int ML, int& score, int& time, int& state);

int main()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &CursorInfo); // hide mouse

    srand(time(NULL)); // set random time
    int GSpeed = 500, Clock = 30, Score = 0, MouseLocation = 0, DST = 0; //GSpeed = GameSpeed, DST = Double Score Remain Time
    double Clk = 0.0;
    int PsState = 0;

    InitializeGame();//create the road for the game
    while (Clock >= 0){
        auto start = chrono::steady_clock::now(); //start timer
        SetGamScr (Clock, Score, PsState, DST);
        ResetGL(MouseLocation, Score, Clock, DST);
        if (kbhit()){//detect if any key is press
            char input = getch(); //get the pressed ked;
            switch (input){
                case 'a':
                    if(MouseLocation - 1 >= 0){
                        MouseLocation -= 1;
                    }
                    break;
                case 'd':
                    if(MouseLocation + 1 <= 3){
                        MouseLocation += 1;
                    }
                    break;
            }
            ResetGL(MouseLocation, Score, Clock, DST);
            SetGamScr (Clock, Score, PsState, DST);
        }
        //ResetGL(MouseLocation, Score, Clock, DST);//reset the screen;
        if (DST > 0 ){
            PsState = 1;
        }else{
            PsState = 0;
        }
        Sleep(GSpeed);
        GSpeed *= 0.98;//increase game speed
        auto end = chrono::steady_clock::now();//end timer

        Clk += chrono::duration_cast<chrono::milliseconds>(end - start).count(); // get timer's time
        if (Clk >= 1000 ){
            Clock--;
            Clk = 0;
            if (DST >= 1){
                DST--;
            }
        }
    }
    return 0;
}

void InitializeGame(){
    for (int row = 0; row < 16; row++){
        for (int column = 0; column < 4; column++){
            int ObjectGenerator = (rand() % 100);
            if (ObjectGenerator < 80){
                ObjectArray[row][column] = ' ';
            }else if (ObjectGenerator >= 80 && ObjectGenerator < 94){
                ObjectArray[row][column] = '$';
            }else if (ObjectGenerator >= 94 && ObjectGenerator < 97){
                ObjectArray[row][column] = '+';
            }else if (ObjectGenerator >= 97 && ObjectGenerator <= 100){
                ObjectArray[row][column] = '*';
            }
        }
    }
    for (int column = 0; column < 4; column++){
    ObjectArray[16][column] = ' ';
    }
    ObjectArray[16][0] = '@';
}

void SetGamScr (int clk, int score, int state, int dst){
    gotoxy(0, 0);
    for (int row = 0; row < 17; row++){
        for (int column = 0; column < 4; column++){
            cout.width(3);
            cout << "l";
            cout.width(3);
            cout << ObjectArray[row][column];
        }
        cout.width(3);
        cout << "l";
        switch (row){
            case 2:
                cout <<setw(9) <<"Time: "<<endl;
                break;
            case 3:
                cout <<setw(7) <<clk<<endl;
                break;
            case 5:
                cout <<setw(10) <<"Score: "<<endl;
                break;
            case 6:
                cout <<setw(8) <<score <<endl;
                break;
            case 8:
                cout <<setw(9) <<"State:"<<endl;
                break;
            case 9:
                if (state == 0 ){
                    cout <<setw(9) <<"Normal" <<endl;
                }else if (state == 1){
                    cout <<setw(16) <<"Double Score " <<dst<<endl;
                }else if (state == 2){
                    cout <<setw(14) <<"Slow Motion" <<endl;
                }
                break;
            default:
                cout << endl;
        }
    }

}

void ResetGL (int ML, int& score, int& time, int& state){
    for (int column = 0; column < 4; column++){
        ObjectArray[18][column] = ObjectArray[16][column];
    }
    for (int row = 16; row > 0; row--){
        for (int column = 0; column < 4; column++){
            ObjectArray[row][column] = ObjectArray[row - 1][column];
        }
    }
    for (int column = 0; column < 4; column++){
        ObjectArray[0][column] = ObjectArray[18][column];
    }
    for (int column = 0; column < 4; column++){
        int ObjectGenerator = (rand() % MAX );//generate a random number from 0 to 100
        if (ObjectGenerator < 80){
            ObjectArray[0][column] = ' ';
        }else if (ObjectGenerator >= 80 && ObjectGenerator < 94){
            ObjectArray[0][column] = '$';
        }else if (ObjectGenerator >= 94 && ObjectGenerator < 97){
            ObjectArray[0][column] = '+';
        }else if (ObjectGenerator >= 97 && ObjectGenerator <= 100){
            ObjectArray[0][column] = '*';
        }
    }
    if (state > 0){
        if (ObjectArray[16][ML] == '$') score += 2;
    }else{
        if (ObjectArray[16][ML] == '$') score ++;
    }

    if(ObjectArray[16][ML] == '+') time++;
    if(ObjectArray[16][ML] == '*'){
        state += 5;
    }
    ObjectArray[16][ML] = '@';
}

void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}
