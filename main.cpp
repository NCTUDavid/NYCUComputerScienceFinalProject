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
void ResetGL (int ML, int& score, int& time, int& DoubleTime, int state);
void PointAdder (int state, int& DoubleTime, int ML, int&score, int& time);
void gamerule();

int main()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &CursorInfo); // hide mouse

    gamerule();

    char yes;
    cin >> yes ;

    while (yes != 'y'){
        cout << "enter y !!!!!" << endl;
        cin >> yes;
    }
    system("cls");
    srand(time(NULL)); // set random time
    int GSpeed = 500, Clock = 30, Score = 0, MouseLocation = 0, DST = 0; //GSpeed = GameSpeed, DST = Double Score Remain Time
    double Clk = 0.0;
    int PsState = 0;

    InitializeGame();//create the road for the game
    while (Clock >= 0){
        auto start = chrono::steady_clock::now(); //start timer
        SetGamScr (Clock, Score, PsState, DST);
        ResetGL(MouseLocation, Score, Clock, DST, PsState);
        if (kbhit()){//detect if any key is press
            char input = getch(); //get the pressed ked;
            int tmp = MouseLocation;
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
            ObjectArray[16][tmp] = ' ';
            ObjectArray[16][MouseLocation] = '@';
            PointAdder(PsState, DST, MouseLocation, Score, Clock);
            SetGamScr (Clock, Score, PsState, DST);
            /*
            if (PsState > 0){
                if (ObjectArray[16][MouseLocation] == '$')
                    Score += 2;
            }else{
                if (ObjectArray[16][MouseLocation] == '$')
                    Score ++;
            }
            if (time <= 3){
                if(ObjectArray[16][MouseLocation] == '_')
                    time = 0;
            }else{
                if(ObjectArray[16][MouseLocation] == '_')
                    time -= 3;
            }

            if(ObjectArray[16][MouseLocation] == '+')
                time++;
            if(ObjectArray[16][MouseLocation] == '*'){
                state += 5;
            }
        */
        //ResetGL(MouseLocation, Score, Clock, DST);//reset the screen;
        }
        if (DST > 0 ){
            PsState = 1;
        }else{
            PsState = 0;
        }
        Sleep(GSpeed);
        //Sleep(500);
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
    system("cls");
    cout << endl;
    cout << "END" << endl;
    cout << endl;
    cout << "Your score is :" << Score << endl;
    cout << endl;

    if(Score <= 20)
    {
        cout << "Please work harder." << endl;
    }
    else if (Score>20 && Score <=50)
    {
        cout << "acceptable" << endl;
    }
    else
    {
        cout << "good" << endl;
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
    //system("cls");
    for (int row = 0; row < 17; row++){
        for (int column = 0; column < 4; column++){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            cout.width(3);
            cout << "l";
            cout.width(3);
            switch(ObjectArray[row][column]){
            case '$':
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                    break;
                case '+':
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1);
                    break;
                case '_':
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
                    break;
                case '*':
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                    break;
            }
            cout << ObjectArray[row][column];
        }
        cout.width(3);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
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
                    cout <<setw(10) <<"Normal " << "  " <<endl;
                }else if (state == 1){
                    cout <<setw(10) <<"Double " <<dst <<endl;
                }else if (state == 2){
                    cout <<setw(14) <<"Slow Motion" <<endl;
                }
                break;
            default:
                cout << endl;
        }
    }

}

void ResetGL (int ML, int& score, int& time, int& DoubleTime, int state){
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
        }else if (ObjectGenerator >= 80 && ObjectGenerator < 90){
            ObjectArray[0][column] = '$';
        }else if (ObjectGenerator >= 90 && ObjectGenerator < 94){
            ObjectArray[0][column] = '+';
        }else if (ObjectGenerator >= 94 && ObjectGenerator < 97){
            ObjectArray[0][column] = '*';
        }else if(ObjectGenerator >= 97 && ObjectGenerator <= 100){
            ObjectArray[0][column] = '_';
        }
    }
    /*
    if (state > 0){
            if (ObjectArray[16][ML] == '$') score += 2;
    }else{
        if (ObjectArray[16][ML] == '$') score ++;
    }
        if (ObjectArray[16][ML] == '$') score += 2;
    }else{
        if (ObjectArray[16][ML] == '$') score ++;
    }
    if (time <= 3){
        if(ObjectArray[16][ML] == '_')
            time = 0;
    }else{
        if(ObjectArray[16][ML] == '_')
            time -= 3;
    }
}
    if(ObjectArray[16][ML] == '+') time++;
    if(ObjectArray[16][ML] == '*'){
        state += 5;
    }
    */
    PointAdder (state, DoubleTime, ML, score, time);
    ObjectArray[16][ML] = '@';
}

void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

void PointAdder (int state, int& DoubleTime, int ML, int&score, int& time){
    if (state > 0){
        if (ObjectArray[16][ML] == '$') score += 2;
    }else{
        if (ObjectArray[16][ML] == '$') score ++;
    }
    if (time <= 3){
        if(ObjectArray[16][ML] == '_')
            time = 0;
    }else{
        if(ObjectArray[16][ML] == '_')
            time -= 3;
    }
    if(ObjectArray[16][ML] == '+') time++;
    if(ObjectArray[16][ML] == '*'){
        DoubleTime += 5;
    }
}

void gamerule()
{
    int i;

    cout << " " << "遊戲規則說明:" << endl;
    cout << endl;

    cout << " " << "1.利用 A D 鍵操控你的角色 @ 左右移動" << endl;
    cout << " " << "2.$是金幣，用 @ 吃到一個就可以得一分" << endl;
    cout << " " << "3.遊戲時間30秒" << endl;
    cout << endl;

    cout << " " << "特殊道具介紹:" << endl;
    cout << endl;
    cout << " " << "+" << " " << ":" << " " << "遊戲時間增加一秒" << endl;
    cout << " " << "*" << " " << ":" << " " << "接下來五秒鐘一個 $ 可以得兩分" << endl;

    cout << endl;



    cout << "Press y and enter to start" << endl;

    for(i=1;i<=20;i++)
    {
    cout << "." << " ";
    }
}



