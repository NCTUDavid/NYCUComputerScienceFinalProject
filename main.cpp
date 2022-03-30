#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

typedef double *doublePtr;

class matrix {
    public:
        matrix();
        void initializeMatrix(int m , int n);
        ~matrix();
        void printMatrix();
        void initializeMatrix();
        void setElement(int i, int j, double value);
        const int getn();
        const int getm();
        const double getElement (int m, int n);

    private:
        int numRow, numColumn;
        doublePtr *matrixPtr;
};

matrix::matrix(){}

void matrix::initializeMatrix(int m , int n){
        numRow = m;
        numColumn = n;
        matrixPtr = new doublePtr[m];
        for(int i = 0; i < numRow; i++){
            matrixPtr[i] = new double[n];
        }
}

matrix::~matrix(){
    for(int m = 0; m < numRow; m++){
        delete [ ] matrixPtr[m];
    }
    delete [ ] matrixPtr;
    matrixPtr = NULL;
    cout << "MatrixPtr deleted ";
}

void matrix::printMatrix(){
    cout << endl;
    for(int m = 0; m < numRow; m++){
        for(int n = 0; n < numColumn; n++){
            cout <<setw(5) << matrixPtr[m][n];
        }
        cout << endl;
    }
    cout <<endl;
}

void matrix::initializeMatrix(){
    int m, n;
    char matrixCheck;
    cout << "Please enter the size of your matrix (m and n.)" << endl;
    cin >> m >> n;
    if(m >= 0 && n >= 0){
        numRow = m;
        numColumn = n;
        matrixPtr = new doublePtr[m];
        for(int i = 0; i < numRow; i++){
            matrixPtr[i] = new double[n];
        }
    }else{
        cout << "Invalid dimension.";
        exit(1);
    }

    do{
        for(int m = 0; m < numRow; m++){
            cout << "Please enter " << m + 1 << " row of your matrix. (Use space to seperate number)" <<endl;
            for(int n = 0; n < numColumn; n++){
                cin >> matrixPtr[m][n];
            }
        }
        cout << "Is your matrix as follow:" <<endl ;
        printMatrix();
        cout << "Please enter y for yes, n for no ";
        cin >> matrixCheck;
    }while(matrixCheck != 'y');
}

void matrix::setElement(int i, int j, double value){
    matrixPtr[i][j] = value;
}

const int matrix::getn(){
    return(numColumn);
}

const int matrix::getm(){
    return(numRow);
}

const double matrix::getElement (int m, int n){
    return(matrixPtr[m][n]);
}

class Matrices : public matrix {
public:
    Matrices();
    Matrices(int);
    ~Matrices();
    void viewAll();
    void add();
    void subt();
    void scalMulti(int index, double scalar);
    /*

    void subt(matrix a, matrix b);
    void scalMulti(double c, matrix a)
    */
private:
    matrix* matrices;
    int numMatrix;
};
Matrices::Matrices(int numM){
    numMatrix = numM;
    matrices = new matrix [numMatrix + 1];
    for(int i = 1; i <= numMatrix; i++){
        cout <<endl << "For " << i << " matrix." <<endl;
        matrices[i].initializeMatrix();
    }
}

Matrices::Matrices (){
    cout << "How many matrix would you like to create? ";
    cin >> numMatrix;
    matrices = new matrix [numMatrix + 1];
    for(int i = 1; i <= numMatrix; i++){
        cout <<endl << "For " << i << " matrix." <<endl;
        matrices[i].initializeMatrix();
    }
}

Matrices::~Matrices(){
    delete [] matrices;
    cout <<"matrices deleted ";
    matrices = NULL;
}

void Matrices::viewAll() {
    for(int i = 0; i < numMatrix; i++){
        cout <<endl << "This is matrix "<< i +1 << endl <<endl;
        matrices[i +1].printMatrix();
    }
}


void Matrices::add(){
    if(matrices[1].getm() != matrices[2].getm() || matrices[1].getn() != matrices[2].getn()){
        cout <<"Error. Cannot add a " << matrices[1].getm() << " * " << matrices[1].getn() <<" matrix with a "<<matrices[2].getm() << " * " << matrices[2].getn() <<" matrix.";
        return;
    }
    matrices[0].initializeMatrix(matrices[1].getm(), matrices[1].getn());
    for(int i = 0; i < matrices[0].getm(); i++) {
        for(int j = 0; j < matrices[0].getn(); j++){
            matrices[0].setElement(i, j, matrices[1].getElement(i, j) + matrices[2].getElement(i, j));
        }
    }
    cout << "matrix 1 + matrix 2 = " << endl;
    matrices[0].printMatrix();
}

void Matrices::subt(int i1, int i2){
    if(i1 < 0 || i1 > numMatrix || i2 < 0 || i2 > numMatrix ){
        cout << "Invalid index.";
    }

    if(matrices[1].getm() != matrices[2].getm() || matrices[1].getn() != matrices[2].getn()){
        cout <<"Error. Cannot add a " << matrices[1].getm() << " * " << matrices[1].getn() <<" matrix with a "<<matrices[2].getm() << " * " << matrices[2].getn() <<" matrix.";
        return;
    }
    matrices[0].initializeMatrix(matrices[1].getm(), matrices[1].getn());
    for(int i = 0; i < matrices[0].getm(); i++) {
        for(int j = 0; j < matrices[0].getn(); j++){
            matrices[0].setElement(i, j, matrices[1].getElement(i, j) - matrices[2].getElement(i, j));
        }
    }
    cout << "matrix 1 + matrix 2 = " << endl;
    matrices[0].printMatrix();
}

void Matrices::scalMulti(int index, double scalar){ //scalar multiple
    if(index > numMatrix || index < 0){
        cout <<"matrix " <<index <<" does not exit.";
        return;
    }
    for(int i = 0; i < matrices[0].getm(); i++) {
        for(int j = 0; j < matrices[0].getn(); j++){
            matrices[index].setElement(i, j, scalar * matrices[index].getElement(i, j));
        }
    }
    cout << "matrix " << index <<" becomes: " <<endl;
    matrices[index].printMatrix();
}

int main()
{
    int numM, index1, index2;
    double scalar;
    string command, cases;
    do{
        cin >> command;
        if(cases == "new"){
            cin >> numM;
                Matrices s1(numM);
                s1.viewAll();
        }else if(cases == "add"){
            cin >> index1 >>index2;
            s1.add();
        }else if(cases == "sub"){
            cin >> index1 >>index2;
            s1.subt();
        }else if(cases == "scaMul"){
            cin >> scalar;
            s1.scalMulti(scalar);
        }
    }while(command != "stop");
    return 0;
}
