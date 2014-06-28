#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAX_N = 10000;
const double PI = 3.14159265359;
#define RAD2DEG(a)((a) * (180) / (PI))
int **gcdmemo;
double  **anglememo;
//-----------------------------------------------------------
//--------------composition class seisu-----------------------
//------------------------------------------------------------
void free_memo(){
        for(int i = 0; i < 1000; i++){
            free(gcdmemo[i]);
            free(anglememo[i]);
        }
        free(gcdmemo);
        free(anglememo);
}

class Seisu{
    public:
        Seisu();
        inline int gcd(int x, int y);
};

Seisu::Seisu(){

    gcdmemo = (int **)calloc(1000,sizeof(int*));
    anglememo = (double **)calloc(1000,sizeof(int*));

    for(long i = 0; i < 1000; i++){
        gcdmemo[i] = (int *)calloc(1000,sizeof(int));
        anglememo[i] = (double *)calloc(1000,sizeof(double));
    }

    try{
        if(gcdmemo == NULL){
            cout << "CAN'T_ACCESS_HEAP_AREA!" << endl;
            throw "CAN'T_ACCESS_HEAP_AREA!";
        }
        if(anglememo == NULL){
            cout << "CAN'T_ACCESS_HEAP_AREA!" << endl;
            throw "CAN'T_ACCESS_HEAP_AREA!";
        }
    }
    catch(char* err){
        free_memo();
        cout << err << endl;
    }
}

inline int Seisu::gcd(int x, int y){

 if(gcdmemo[x][y] > 0) return  gcdmemo[x][y];
 if(y == 0) return (gcdmemo[x][y]= x);
 else return (gcdmemo[x][y] = gcd(y, x % y));
}


//--------------------------------------------------------
//---------------abstruct class---------------------------
//--------------------------------------------------------
struct Option{
    int fo;
    int showv;
    int angtype;
};

class Triangle{
    protected:
        int a,b,c;
        long minilim;
        long limit;
        long long int num;
        double angle[3];
        double area;
        Option opt;
    public:
        Triangle();
        inline double getarea(int a, int b, int c);
        inline void getangle(int a, int b, int c, double area);
};

Triangle::Triangle(){

        for(int i = 0; i < 3; i++)
            angle[i] = 0;
        cout << "--------------SETTINGS-------------------" << endl;
        cout << "ENTER_MAXIMUM."<< endl;
        cin >> limit;
        try{
            if(limit > 1000){
                cout << "GREATER_THAN_1000!" << endl;
                cout << "ABORTING......" << endl;
                throw "GREATER_THAN_1000!";
            }
        }
        catch(char* err){
            free_memo();
            cout << err << endl;
        }
        cout << "ENTER_MINIMUM." << endl;
        cin >> minilim;
        try{
            if(minilim < 0 || minilim > 1000 || minilim >= limit){
                cout << "NUMBER_ERROR!" << endl;
                cout << "ABORTING......" <<endl;
                throw "NUMBER_ERROR!";
            }
        }
        catch(char* err){
            free_memo();
            cout << err << endl;
        }
        opt.fo = 0;
        cout << endl;
        cout << "----------------OPTIONS-------------------"<< endl;
        cout << endl;
        cout << "SHOW_SIDE_VALUE?"<<endl;
        cout << "1_TO_SHOW_,_2_TO_NOT_SHOW." << endl;
        cout << endl;
        cin >> opt.showv;
        try{
            if(opt.showv != 1 && opt.showv != 2){
                cout << "SIDE_VALUE_OUTPUT_IS_NOT_DEFINED!" << endl;
                throw "NUMBER_ERROR";
            }
        }
        catch(char* err){
            free_memo();
            cout << err << endl;
        }
        cout << "WRITE_FILE?_1_TO_WRITE,2_TO_NOT." << endl;
        cin >> opt.fo;
        try{
            if(opt.fo != 1 && opt.fo != 2){
                cout << "NUMBER_ERROR!" << endl;
                cout << "ABORTING......"<< endl;
                throw "NUMBER_ERROR!";
            }
        }
        catch(char* err){
            free_memo();
            cout << err << endl;
        }
        opt.angtype = 0;
        cout << endl;
        cout << "RAD_OR_DEG?" << endl;
        cout << "1_TO_DEG,_2_TO_RAD." << endl;
        cin  >> opt.angtype;
        try{
            if(opt.angtype != 1 && opt.angtype != 2){
                cout << "ANGLE_TYPE_NOT_DEFINED!" << endl;
                cout << "ABORTING......" << endl;
                throw "ANGLE_TYPE_NOT_DEFINED!";
            }
        }
        catch(char* err){
            free_memo();
            cout << err << endl;
        }
        cout << endl;
}

inline double Triangle::getarea(int a, int b, int c){
    double s = (a + b + c) * 0.5;
    double area = sqrt( s * ( s - a ) * ( s - b ) * ( s - c ) );
    return area;
}

inline void Triangle::getangle(int a, int b, int c, double area){
    double h;
    h = 2 * area / c;
    angle[0] = asin(h/b);
    angle[1] = asin(h/a);
    angle[2] = M_PI - angle[0] - angle[1];
    if(opt.angtype == 1){
        for(int i = 0; i < 3; i++){
            angle[i] = RAD2DEG(angle[i]);
        }
    }
}

//-----------------------------------------------
//--------------tagainiso_inheritance_class------
//-----------------------------------------------

class Sotriangle: public Triangle{
    private:
        Seisu gcd;
    public:
        void sotri();
        void sotri2();
        void sotri3();
        void sotri4();
        void sotri5();
};

 void Sotriangle::sotri(){
    num = 0;
    ofstream fout("sotriangle_1.txt");
    cout << endl;
    cout << "----------------RESULT---------------------" << endl;
    cout << endl;
    for(int i = minilim; limit - 2 > i; i++){
        for(int j = i + 1; limit - 1 > j; j++){
            if(gcd.gcd(i,j) != 1) continue;
            for(int k = j + 1; limit > k; k++){
                if(k >= i + j) break;
                else if((gcd.gcd(i,k) == 1) && (gcd.gcd(j,k) == 1)){
                        if(opt.showv == 1){
                                cout << i << " " << j << " " << k  << endl;
                        }
                        if(opt.fo == 1) {
                            try{
                                if(fout.fail()){
                                    cout << "CAN'T_WRITE_FILE!" << endl;
                                    cout << "ABORTING......" << endl;
                                    throw "CAN'T_WRITE_FILE!";
                                }
                            }
                            catch(char* err){
                                free_memo();
                                cout << err << endl;
                            }
                            area = getarea(i,j,k);
                            getangle(i,j,k,area);
                            fout << "SIDE: " << i << " " << j << " " << k << " \n";
                            fout << "ANGLE: " <<angle[0] << " " << angle[1] << " " << angle[2] << "\n";
                            fout << "AREA: " << area << endl;
                        }
                        num++;
                }
            }
        }
    }
    cout << endl;
    cout << "THE_NUMBER_OF_TRIANGLE_IS_" << num << "." << endl;
    free_memo();
    fout.close();
}

void Sotriangle::sotri2(){
    num = 0;
    ofstream fout("sotriangle_2.txt");
    cout << endl;
    cout << "----------------RESULT---------------------" << endl;
    cout << endl;
    for(int i = minilim; limit - 3 > i; i++){
        if(gcd.gcd(i,i + 1) != 1) continue;
        for(int j = i + 3; limit > j; j++){
            if(j >= 2 * i + 1 || j <= i + 1) break;
            else if((gcd.gcd(i,j) == 1) && (gcd.gcd(i+1,j) == 1)){
                if(opt.showv == 1){
                    cout << i << " " << i+1 << " " << j  << endl;
                }
                if(opt.fo == 1) {
                    try{
                        if(fout.fail()){
                            cout << "CAN'T_WRITE_FILE!" << endl;
                            cout << "ABORTING......" << endl;
                            throw "CAN'T_WRITE_FILE!";
                        }
                    }
                    catch(char* err){
                        free_memo();
                        cout << err << endl;
                    }
                    area = getarea(i,i+1,j);
                    getangle(i,i + 1,j,area);
                    fout << "SIDE: " << i << " " << i+i << " " << j << " \n";
                    fout << "ANGLE: " <<angle[0] << " " << angle[1] << " " << angle[2] << "\n";
                    fout << "AREA: " << area << endl;
                }
                num++;
            }
        }
    }
    for(int i = minilim; limit - 3 > i; i++){
        for(int j = i + 3; limit > j; j++){
            if(gcd.gcd(j-1,j) != 1) continue;
            if(1 >= i || j   <= i - 2) break;
            else if((gcd.gcd(i,j) == 1) && (gcd.gcd(j - 1, j) == 1)){
                if(opt.showv == 1){
                    cout << i << " " << j-1 << " " << j  << endl;
                }
                if(opt.fo == 1) {
                    try{
                        if(fout.fail()){
                            cout << "CAN'T_WRITE_FILE!" << endl;
                            cout << "ABORTING......" << endl;
                            throw "CAN'T_WRITE_FILE!";
                        }
                    }
                    catch(char* err){
                        free_memo();
                        cout << err << endl;
                    }
                    area = getarea(i,j-1,j);
                    getangle(i,j-1,j,area);
                    fout << "SIDE: " << i << " " << j-1 << " " << j << " \n";
                    fout << "ANGLE: " <<angle[0] << " " << angle[1] << " " << angle[2] << "\n";
                    fout << "AREA: " << area << endl;
                }
                num++;
            }
        }
    }
    cout << endl;
    cout << "THE_NUMBER_OF_TRIANGLE_IS_" << num << "." << endl;
    free_memo();
    fout.close();
}

void Sotriangle::sotri3(){
    num = 0;
    ofstream fout("sotriangle_3.txt");
    cout << endl;
    cout << "----------------RESULT---------------------" << endl;
    cout << endl;
    for(int i = minilim; limit - 2 > i; i++){
            if( 1 >=  i ) continue;
            if(gcd.gcd(i,i + 1) != 1) continue;
            else if((gcd.gcd(i,i + 2) == 1) && (gcd.gcd(i + 1, i + 2) == 1)){
                        if(opt.showv == 1){
                                cout << i << " " << i + 1 << " " << i + 2  << endl;
                        }
                        if(opt.fo == 1) {
                            try{
                                if(fout.fail()){
                                    cout << "CAN'T_WRITE_FILE!" << endl;
                                    cout << "ABORTING......" << endl;
                                    throw "CAN'T_WRITE_FILE!";
                                }
                            }
                            catch(char* err){
                                free_memo();
                                cout << err << endl;
                            }
                            area = getarea(i,i + 1, i + 2);
                            getangle(i, i + 1, i + 2,area);
                            fout << "SIDE: " << i << " " << i + 1 << " " << i + 2 << " \n";
                            fout << "ANGLE: " <<angle[0] << " " << angle[1] << " " << angle[2] << "\n";
                            fout << "AREA: " << area << endl;
                        }
                        num++;
                }
    }
    cout << endl;
    cout << "THE_NUMBER_OF_TRIANGLE_IS_" << num << "." << endl;
    free_memo();
    fout.close();
}

void Sotriangle::sotri4(){
    num = 0;
    ofstream fout("sotriangle_4.txt");
    cout << endl;
    cout << "----------------RESULT---------------------" << endl;
    cout << endl;
    for(int i = minilim; limit - 2 > i; i++){
        for(int j = i + 1; limit - 1 > j; j++){
            if(gcd.gcd(i,j) != 1) continue;
            for(int k = j + 1; limit > k; k++){
                if(k >= i + j) break;
                else if((gcd.gcd(i,k) == 1) && (gcd.gcd(j,k) == 1)){
                        area = getarea(i,j,k);
                        if(ceil(area) != floor(area)) continue;
                        if(opt.showv == 1){
                                cout << i << " " << j << " " << k  << endl;
                        }
                        if(opt.fo == 1) {
                            try{
                                if(fout.fail()){
                                    cout << "CAN'T_WRITE_FILE!" << endl;
                                    cout << "ABORTING......" << endl;
                                    throw "CAN'T_WRITE_FILE!";
                                }
                            }
                            catch(char* err){
                                free_memo();
                                cout << err << endl;
                            }
                            getangle(i,j,k,area);
                            fout << "SIDE: " << i << " " << j << " " << k << " \n";
                            fout << "ANGLE: " <<angle[0] << " " << angle[1] << " " << angle[2] << "\n";
                            fout << "AREA: " << area << endl;
                        }
                        num++;
                }
            }
        }
    }
    cout << endl;
    cout << "THE_NUMBER_OF_TRIANGLE_IS_" << num << "." << endl;
    free_memo();
    fout.close();
}

void Sotriangle::sotri5(){
    num = 0;
    ofstream fout("sotriangle_5.txt");
    cout << endl;
    cout << "----------------RESULT---------------------" << endl;
    cout << endl;
    for(int i = minilim; limit - 2 > i; i++){
        for(int j = i + 1; limit - 1 > j; j++){
            if(gcd.gcd(i,j) != 1) continue;
            for(int k = j + 1; limit > k; k++){
                if(k >= i + j) break;
                else if((gcd.gcd(i,k) == 1) && (gcd.gcd(j,k) == 1)){
                    area = getarea(i,j,k);
                    getangle(i,j,k,area);
                    if((ceil(angle[0]) == floor(angle[0])) || (ceil(angle[1]) == floor(angle[1])) || (ceil(angle[2]) == floor(angle[2]))){
                        if(opt.showv == 1){
                                cout << i << " " << j << " " << k  << endl;
                        }
                        if(opt.fo == 1) {
                            try{
                                if(fout.fail()){
                                    cout << "CAN'T_WRITE_FILE!" << endl;
                                    cout << "ABORTING......" << endl;
                                    throw "CAN'T_WRITE_FILE!";
                                }
                            }
                            catch(char* err){
                                free_memo();
                                cout << err << endl;
                            }
                            fout << "SIDE: " << i << " " << j << " " << k << " \n";
                            fout << "ANGLE: " <<angle[0] << " " << angle[1] << " " << angle[2] << "\n";
                            fout << "AREA: " << area << endl;
                        }
                        num++;
                    }
                }
            }
        }
    }
    cout << endl;
    cout << "THE_NUMBER_OF_TRIANGLE_IS_" << num << "." << endl;
    free_memo();
    fout.close();
}
//----------------------------------
//------------main_class-------------
//-----------------------------------
class Kensei{
    private:
        int state;
    public:
        Kensei();
        void main_prog();
        ~Kensei();
};

Kensei::Kensei(){
    cout << endl;
    cout<<"WELCOME_TO_KENSEI_DEMURA'S_TRIANGLE_CALCLATING_SYSTEM!"<<endl;
    cout << endl;
    cout<<"---------------PROGRAM_START---------------------------"<<endl;
    cout << endl;
    state = 0;
    cout << "COPRIME_TRIANGLE,TWO_CONTINUOUS_TRIANGLE,_THREE_CONTINUOUS_TRIANGLE,"<< endl;
    cout << "_OR_INTEGRAL_SURFACE?"<<endl;
    cout << "IF_COPRIME,_ENTER_1."<<endl;
    cout << "IF_TWO,_ENTER_2."<<endl;
    cout << "IF_THREE,_ENTER_3."<< endl;
    cout << "IF_INTEGRAL_SURFACE,_ENTER_4." << endl;
    cout << "IF_INTEGRAL_INTERNAL_ANGLE,_ENTER_5." << endl;
    cin >> state;
    try{
        if(state < 1 || state > 5 ){
                cout << "NUMBER_IS_NOT_1~5!" << endl;
                cout << "ABORTING......" << endl;
                throw "NUMBER_IS_NOT_1~5!";
        }
    }
    catch(char* err){
        free_memo();
        cout << err << endl;
    }
}

void Kensei::main_prog(){
    Sotriangle so;
    switch(state){
        case 1:
            so.sotri();
            break;
        case 2:
            so.sotri2();
            break;
        case 3:
            so.sotri3();
            break;
        case 4:
            so.sotri4();
            break;
        case 5:
            so.sotri5();
            break;
        default:
            break;
    }
}

Kensei::~Kensei(){
    char n;
    cout << endl;
    cout << "QUIT_PROGRAM?" << endl;
    cout << "ENTER_ANY_KEY_TO_QUIT." << endl;
    while(!(cin >> n)){}
}
//-----------------------------------------------------
int main()
{
    Kensei kensei;
    kensei.main_prog();
    return 0;
}
