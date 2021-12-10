#include <iostream>
#include <fstream>
#include <string>
#include<iomanip>
#include<cstdlib>
#include<windows.h>



using namespace std;

string GLine[18];
const int NumGLine = 17;


void ResetGL (int GSpeed);
void SetGamScr (int clk, int& score, int state);
void ReadMap(ifstream& inStream);

int main()
{
    ifstream Map;
    Map.open("GameMap.txt");
    if ( Map.fail( ) ){
        cout << "Input file opening failed.\n";
        exit(1);
    }
    int GSpeed = 1000, Clock = 60, Score = 0;
    enum State {Normal, X2, Slow} ;
    State PsState = Normal;
    ReadMap(Map);
    Map.close();

    for (double Clk = 60; Clk >= 0; Clk--){
        Clock = Clk;
        SetGamScr (Clock, Score, PsState);
        GSpeed -= (10 * (60 - Clock));
        ResetGL(GSpeed);
        Sleep(1000);

    }


}


void ReadMap(ifstream& inStream){
    for (int i = 0; i  < NumGLine; i++ ){
        getline(inStream, GLine[i]);
    }
    inStream.close();
}


void SetGamScr (int clk, int& score, int state){
    system("cls");
    for (int i = 0; i  < NumGLine; i++ ){
        cout <<GLine[i];
        switch (i){
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
                    cout <<setw(15) <<"Double Score" <<endl;
                }else if (state == 2){
                    cout <<setw(14) <<"Slow Motion" <<endl;
                }
                break;
            default:
                cout << endl;
        }
    }
}

void ResetGL (int Speed){
    GLine[17] = GLine[16];
    for(int i = 16; i > 0 ; i--){
        GLine[i] = GLine[i-1];
    }
    GLine[0] = GLine[17];
}





