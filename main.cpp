#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <random>
using namespace std;
using namespace chrono;


class sparseMat{
private:
    vector<int> rowS;
    vector<int> colS;
    vector<int> valS;
public:
    void setRowS(int r){
        rowS.push_back(r);
    }
    void setColS(int c){
        colS.push_back(c);
    }
    void setValS(int v){
        valS.push_back(v);
    }


    void transposeMatrix(){
        int temp{0};
        for (int i = 0; i < rowS.size(); ++i){
            temp = rowS[i];
            rowS[i] = colS[i];
            colS[i] = temp;
        }
        for (int i = 1; i < rowS.size(); ++i){
            int tempRow = rowS[i] , tempCol = colS[i] , tempVal = valS[i] , j ;

            for (j = i - 1; j >= 0 && tempRow < rowS[j]; --j){
                rowS[j + 1] = rowS[j];
                colS[j + 1] = colS[j];
                valS[j + 1] = valS[j];

            }
            rowS[j + 1] = tempRow;
            colS[j + 1] = tempCol;
            valS[j + 1] = tempVal;
        }
    }
    friend ostream& operator<<(ostream &out , sparseMat &value){

        out << "Sparse Matrix:" << endl;
        out << "Row:    ";
        for (int i = 0; i < value.rowS.size(); ++i){
            out << value.rowS[i] + 1 << " ";
        }
        out << endl;

        out << "Column: ";
        for (int i = 0; i < value.colS.size(); ++i){
            out << value.colS[i] + 1 << " ";
        }
        out << endl;

        out << "Value:  ";
        for (int i = 0; i < value.valS.size(); ++i){
            out << value.valS[i] << " ";
        }
        out << endl;

        return out;
    }
};




class randomMat{
private:
    int row;
    int col;
    sparseMat temp;
public:
    randomMat(){
        row = 0;
        col = 0;
    }
    void Mat(int r , int c){
        int arr[r][c];
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                arr[i][j] = rand() % 50;
                if (arr[i][j] >= 10)
                {
                    arr[i][j] = 0;
                }
                else if (arr[i][j] > 0 && arr[i][j] < 10)
                {
                    temp.setRowS(i);
                    temp.setColS(j);
                    temp.setValS(arr[i][j]);
                }
            }
        }
        cout << "Random generated matrix ( " << row << "x" << col << " ):" << endl;
        for (int i = 0; i < row; ++i){
            for (int j = 0; j < col;++j){
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }


    void setRow(int r){
        row = r;
    }
    void setCol(int c){
        col = c;
    }
    int getRow() { return row; }
    int getCol() { return col; }
    void displaySparseMatrix(){
        cout << temp;
    }
    void transposeMatrix(){
        temp.transposeMatrix();
    }
};

int main(){


    randomMat myMatrix;
    srand(time(NULL));
    int row = (rand()%10) + 1;
    myMatrix.setRow(row);
    int col = (rand()%10) + 1;
    myMatrix.setCol(col);
    myMatrix.Mat(row,col);
    cout << endl;
    myMatrix.displaySparseMatrix();
    cout << endl;

    auto start = high_resolution_clock::now();
    myMatrix.transposeMatrix();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Sparse Matrix Transpose took " << duration.count() << " microseconds." << endl;
    cout<< endl;
    myMatrix.displaySparseMatrix();
    cout  << endl;







    return 0;
}