//
//  main.cpp
//  Project2 for Data Structures C S 2413 at The University of Oklahoma
//
//  Jacob Courtney
//  OUID: 113389044
//

#include <iostream>
#include <vector>
using namespace std;

/*
 * C L A S S  D E C L A R A T I O N S ============================================================== C L A S S  D E C L A R A T I O N S
 */

/*
 *SparseRow Class. contains 4 integers: row, col, value and index (DEPRECATED), which stores the row, column, value and index of a SparseMatrix object
 *This class is meant to be used in an array, where multiple SparseRow objects can be stored to represent a full matrix without having to store common values
 */

template<class DT>
class SparseRow {
    template<class DS>
    friend ostream &operator << (ostream& output,SparseRow<DS>& M);// print Row#, Column#, value in the following format: "<r> <c> <v>"
protected:
    int row;//Row#
    int col;//Column#
    DT value;//We will assume that all our values will be integers
    int index;//The index at which this SparseRow is stored in the array. THIS IS DEPRECATED AND IS NO LONGER USEFUL
public:
    SparseRow (); //default constructor;row=-1;col=-1;value=0
    SparseRow(int i, int r, int c, DT v); //regular constructor: r = row, c = column, v = value
    int getRow(); //gets the row
    void setRow(int r); //sets the row
    int getCol(); //gets the column
    void setCol(int c); //sets the column
    DT getValue(); //gets the value of thsis SparseRow
    void setValue(DT v); //sets the value of this SparseRow
    int getIndex(); //gets the index of this SparseRow
    void setIndex(int i); //sets the index of this SparseRow
};

/*
 *SparseMatrix class. contains 4 integers, noRows, noCols, commonValue and nonNonSparseValues
 *SparseMatrix also holds an array of SparseRows called myMatrix, which contains all of the values in
 *this matrix that are not equal to the common value. A SparseMatrix object is a condensed way to store a full
 *matrix. It achieves this by not storing any common values
 */

template <class DT>
class SparseMatrix {
    template<class DS>
    friend ostream &operator << (ostream& output,SparseMatrix<DS>& M);//Display the sparse matrix
protected:
    int noRows; //Number of rows of the original matrix
    int noCols; //Number of columns of the original matrix
    DT commonValue; //common value of this SparseMatrix
    int noNonSparseValues; //number of non sparse values in this SparseMatrix object. DEPRECATED
    vector<SparseRow<DT>>* myMatrix; //Array of SparseRows that contains info about the points in the array that are not the common value
public:SparseMatrix();
    SparseMatrix (int n, int m, DT cv); //regular constructor. takes in the number of rows and columns, the commonValue and the number of nonSparseValues
    ~SparseMatrix(); //destructor that will deep delete the array
    SparseMatrix *operator! (); //Transposes the matrix
    SparseMatrix *operator* (SparseMatrix<DT>& M); //Multiplies two matrices together
    SparseMatrix *operator+ (SparseMatrix<DT>& M); //Adds two matrices together
    void displayMatrix (); //Display the matrix in its original format
    void setSparseRow(int index, int r, int c, DT v); //allows the user to change full rows at a time within the SparseMatrix
    SparseRow<DT> getSparseRow(int c); //returns the SparseRow stored at index c in myMatrix
    bool ifThereExistsANonSparseVariableAtRowCol(int r, int c);
    SparseRow<DT> getSparseRow(int r, int c); //method to get a SparseRow with the specified row and column
};

/*
 * C  O N S T R U C T O R S ======================================================================================================================= C O N S T R U C T O R S
 */

//SparseRow regular constructor, takes in r, c, v and i and sets them equal to the appropriate values
template<class DT>
SparseRow<DT>::SparseRow(int i, int r, int c, DT v) {
    this->setCol(c);
    this->setRow(r);
    this->setValue(v);
    this->setIndex(i);
};

//SparseRow default Constructor, defaults row and col to -1, defaults the value to 0 and index to NULL
//Generally, if a SparseRow object contains a value of 0 or an index of NULL, then there is a bug in the software
template <class DT>
SparseRow<DT>::SparseRow() {
    this->setCol(-1);
    this->setRow(-1);
    this->setValue(0);
    this->setIndex(NULL);
};

//regular constructor for SparseMatrix. takes in the number of rows and columns, the commonValue and the number of nonSparseValues, and initializes myMatrix
template <class DT>
SparseMatrix<DT>::SparseMatrix (int n, int m, DT cv) {
    noRows = n;
    noCols = m;
    commonValue = cv;
    myMatrix = new vector<SparseRow<DT>>();
    noNonSparseValues = NULL;
};

//default constructor for SparseMatrix. initializes noRows, noCols, commonValue and noNonSparseValues to 0, and leaves myMatrix pointing to the null pointer
template <class DT>
SparseMatrix<DT>::SparseMatrix () {
    noRows = 0;
    noCols = 0;
    commonValue = 0;
    noNonSparseValues = NULL;
};

/*
 * D E S T R U C T O R S ======================================================================================================================== D E S T R U C T O R S
 */



/*
 * G E T T E R S ======================================================================================================================================= G E T T E R S
 */

//simply returns the SparseRow object stored at index c in myMatrix
template <class DT>
SparseRow<DT> SparseMatrix<DT>::getSparseRow(int c) {
    return (*myMatrix)[c];
};

//returns a SparseRow with row r and column c, returns a default SparseRow if that does not exists. This should only be called when it has already been confirmed that one exists
template <class DT>
SparseRow<DT> SparseMatrix<DT>::getSparseRow(int r, int c) {
    for (int i = 0; i < (*myMatrix).size(); i++) {
        if ((*myMatrix)[i].getCol() == c && (*myMatrix)[i].getRow() == r) {
            return (*myMatrix)[i];
        }
    }
    cout << "No NSV with Row " << r << "and Column" << c << endl;
    return SparseRow<DT>();
};

//gets the row# from this SparseRow
template <class DT>
int SparseRow<DT>::getRow() {
    return row;
};

//gets the col# from this SparseRow
template <class DT>
int SparseRow<DT>::getCol() {
    return col;
};

//gets the value from this SparseRow
template <class DT>
DT SparseRow<DT>::getValue() {
    return value;
};

//gets the index# from this SparseRow
template <class DT>
int SparseRow<DT>::getIndex() {
    return index;
};


/*
 * S E T T E R S =============================================================================================================================== S E T T E R S
 */

/* allows the user to essentially just set a new row in myMatrix. becuase of the way that memory allocation works
 * with arrays and the new operator, it is possible to create new objects of the myMatrix array that are out of
 * bounds of what the user originally set as the size of myMatrix. nsv can basically be set to any number
 */
template <class DT>
void SparseMatrix<DT>::setSparseRow(int index, int r, int c, DT v) {
    (*myMatrix).push_back(SparseRow<DT>(index,r,c,v));
};

//sets the value of the SparseRow
template <class DT>
void SparseRow<DT>::setValue(DT v) {
    this->value = v;
};

//sets the row of the SparseRow
template <class DT>
void SparseRow<DT>::setRow(int r) {
    this->row = r;
};

//sets the column of the SparseRow
template <class DT>
void SparseRow<DT>::setCol(int c) {
    this->col = c;
};

//sets the index of the SparseRow
template <class DT>
void SparseRow<DT>::setIndex(int i) {
    this->index = i;
};

/*
 * H E L P E R  M E T H O D S ============================================================================================================ H E L P E R  M E T H O D S
 */

//boolean function that returns true if there is a non sparse value at row r and column c
template <class DT>
bool SparseMatrix<DT>::ifThereExistsANonSparseVariableAtRowCol(int r, int c) {
    for (int i = 0; i < (*myMatrix).size(); i++) {
        if (this->getSparseRow(i).getRow() == r && this->getSparseRow(i).getCol() == c) {
            return true;
        }
    }
    return false;
};

/*
 * E X C E P T I O N S ========================================================================================================================= E X C E P T I O N S
 */

class ExceptionAdd : public exception {
    
};

class ExceptionMultiply : public exception {
    
};

class ExceptionCV : public exception {
    
};

/*
 *  O T H E R =========================================================================================================================================== O T H E R
 */

//method to display the matrix in its original format
template <class DT>
void SparseMatrix<DT>::displayMatrix() {
    
    //the current row and column we are on
    int currentRow = 0;
    int currentCol = 0;
    
    //the main for loops. it goes through this noRows*noCols times
    for (int i = 0; i < ((noRows)*(noCols)); i++) {
        
        //if there is a non sparse variable at currentRow, currentCol
        if (ifThereExistsANonSparseVariableAtRowCol(currentRow, currentCol)) {
            
            //then print out the value of it
            cout << getSparseRow(currentRow,currentCol).getValue();
        }
        
        //otherwise, print the common value
        else {
            cout << commonValue;
        }
        
        //end of row/col checks
        if (currentCol < noCols) {
            cout << " ";
            currentCol++;
        }
        if (currentCol >= noCols) {
            cout << endl;
            currentCol = 0;
            currentRow++;
        }
    }
};

/*
 * O P E R A T O R S ========================================================================================================================================  O P E R A T O R S
 */

//displays the single SparseRow in the following format: "<row> <col> <value>" and an endline
template <class DS>
ostream &operator << (ostream &output, SparseRow<DS> &M) {
    output << M.getRow() << " " << M.getCol() << " " << M.getValue() << endl;
    return output;
};

//transposes the matrix
template <class DT>
SparseMatrix<DT>* SparseMatrix<DT>::operator!() {
    
    //stores the temporary row, column and value inside of each iteration of the for loop below
    int r, c;
    DT v;
    
    //temp SparseMatrix object for return
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValue);
    
    /*
    //this for loop initializes each SparseRow in myMatrix before use to make sure there is room for them
    for (int j = 0; j < this->myMatrix.size(); j++) {
        copy->myMatrix.push_back(SparseRow());
    }
     */
    
    //main for loop of this function. loops through all of the values in myMatrix and switches the row and column value
    for (int i = 0; i < (*myMatrix).size(); i++) {
        r = (*myMatrix)[i].getRow();
        c = (*myMatrix)[i].getCol();
        v = (*myMatrix)[i].getValue();
        copy->setSparseRow(i, c, r, v);
    }
    //returning the copy that has the switched row and column values
    return copy;
};

//multiplies two matrices together
template <class DT>
SparseMatrix<DT>* SparseMatrix<DT>::operator*(SparseMatrix<DT> &M) {
    
    //checking that the number of columns in the first matrix matches the number of rows in the second matrix
    if (this->noCols != M.noRows) {
        throw ExceptionMultiply();
    }
    if (this->commonValue != M.commonValue) {
        throw ExceptionCV();
    }
    
    //the SparseMatrix to be returned
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValue);
    
    //instantiating some variables
    int firstOneRow, firstOneCol, secondOneRow, secondOneCol, index;
    DT current, firstOneValue,secondOneValue;
    
    //stores the current row and column values that will be incremented appropriately
    firstOneRow = 0;
    firstOneCol = 0;
    secondOneRow = 0;
    secondOneCol = 0;
    
    //the sum of the current rows we are multiplying together
    current = 0;
    
    //the index of the sum we will be inserting into the copy
    index = 0;
    
    //main for loop goes through this process noRows*noCols times
    for (int i = 0; i < ((noRows)*(noCols)); i++) {
        
        //checking to see if i is 0 and if the matrix's side is 2 or less. required step in order to run properly on small matrices
        if (((noRows > 2) || (noCols > 2)) && (i == 0)) {
            i++;
        }
        
        //loops through the current rows
        while (firstOneCol < noCols && secondOneRow < noRows) {
            
            //if theres a non sparse variable at both current row and column values
            if (this->ifThereExistsANonSparseVariableAtRowCol(firstOneRow, firstOneCol)
                && M.ifThereExistsANonSparseVariableAtRowCol(secondOneRow, secondOneCol)) {
                
                //then sum them up!
                firstOneValue = this->getSparseRow(firstOneRow,firstOneCol).getValue();
                secondOneValue = M.getSparseRow(secondOneRow,secondOneCol).getValue();
                current += (firstOneValue * secondOneValue);
            }
            
            //incrementing the rows and columns appropriately
            firstOneCol++;
            secondOneRow++;
        }
        
        //checking to see if anything was added up and adding it to copy if so
        if (current != 0) {
            copy->myMatrix->push_back(SparseRow<DT>(i, firstOneRow, secondOneCol, current));
            
            //also incrementing the index and resetting current
            index++;
            current = 0;
        }
        
        //checks for end of row/end of column
        if (secondOneCol < M.noCols) {
            firstOneCol = 0;
            secondOneRow = 0;
            secondOneCol++;
            if (secondOneCol >= M.noCols) {
                firstOneRow++;
                secondOneCol = 0;
            }
        }
    }
    
    //returning
    return copy;
};

//adds two matrices together
template <class DT>
SparseMatrix<DT>* SparseMatrix<DT>::operator+(SparseMatrix<DT> &M) {
    
    //checking that the number of rows and columns match before we start adding
    if ((this->noRows != M.noRows) || (this->noCols != M.noCols)) {
        throw ExceptionAdd();
    }
    if (this->commonValue != M.commonValue) {
        throw ExceptionCV();
    }
    
    //creating a copy of the array
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValue);
    
    //the current row and col
    int currentRow = 0;
    int currentCol = 0;
    int index = 0;
    
    for (int i = 0; i < noCols*noRows; i++) {
        DT sum = 0;
        if (this->ifThereExistsANonSparseVariableAtRowCol(currentRow, currentCol)) {
            sum += this->getSparseRow(currentRow, currentCol).getValue();
        }
        if (M.ifThereExistsANonSparseVariableAtRowCol(currentRow, currentCol)) {
            sum += M.getSparseRow(currentRow, currentCol).getValue();
        }
        if (sum != commonValue) {
            copy->myMatrix->push_back(SparseRow<DT>(index,currentRow,currentCol,sum));
            index++;
        }
        
        //end of row/col checks
        if (currentCol < noCols) {
            currentCol++;
        }
        if (currentCol >= noCols) {
            currentCol = 0;
            currentRow++;
        }
    }
    
    
    //returning the copy
    return copy;
};

//display method in SparseMatrix format. simply loops through myMatrix and calls display on each entry
template <class DS>
ostream& operator << (ostream& output, SparseMatrix<DS> &M) {
    
    for (int i = 0; i < M.myMatrix->size(); i++) {
        output << M.myMatrix->at(i);
    }
    return output;
};

/*
 * M A I N  F U N C T I O N ================================================================================================================  M A I N  F U N C T I O N
 *
 * The code to insert values into the matrices is here, as well as the calls to all of the methods above
 *
 */
int main () {
    
    //initializing some variables before we use them
    int n, m, cv, index, value;
    SparseMatrix<int>* temp;
    
    //reset index to 0
    index = 0;
    
    //prompts the user for input. the program needs the number of rows and columns, the common value and the number of non sparse values
    cin >> n >> m >> cv;
    //initializing the first SparseMatrix with the values entered by the user
    SparseMatrix<int>* firstOne = new SparseMatrix<int>(n, m, cv);
    
    //this nested loop takes the input from the user and automatically assigns the row and column value of each
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            
            //taking input from the user
            cin >> value;
            
            //check to see if the input value is a common value or not
            if (value != cv) {
                
                //and if not then we add it to myMatrix and incremement which index that SparseRow is at
                (*firstOne).setSparseRow(index,i,j,value);
                index++;
            }
        }
    }    //this process is exactly the same as the first one. please refer to the comments above
    cin >> n >> m >> cv;
    index = 0;
    
    SparseMatrix<int>* secondOne = new SparseMatrix<int>(n, m, cv);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> value;
            if (value != cv) {
                (*secondOne).setSparseRow(index,i,j,value);
                index++;
            }
        }
    }
    
    //Statements to manipulate and print matrices
    cout << "First one in sparse matrix format" << endl;
    cout << (*firstOne);
    cout << "First one in normal matrix format" << endl;
    (*firstOne).displayMatrix();
    cout << "Second one in sparse matrix format" << endl;
    cout << (*secondOne);
    cout << "Second one in normal matrix format" << endl;
    (*secondOne).displayMatrix();
    cout << "After Transpose first one in normal format" << endl;
    temp = !*firstOne;
    (*temp).displayMatrix();
    cout << "After Transpose second one in normal format" << endl;
    temp = !*secondOne;
    (*temp).displayMatrix();
    cout << "Multiplication of matrices in sparse matrix form:" << endl;
    temp = *secondOne * *firstOne;
    cout << (*temp);
    cout << "Addition of matrices in sparse matrix form:" << endl;
    temp = *secondOne + *firstOne;
    cout << (*temp);
    
    //main function returns 0 if process is completed
    return 0;
}
