//
//  main.cpp
//  Project2 for Data Structures C S 2413 at The University of Oklahoma
//
//  Jacob Courtney
//  OUID: 113389044
//
#include <iostream>
using namespace std;

/*
 *SparseRow Class. contains 4 integers: row, col, value and index (DEPRECATED), which stores the row, column, value and index of a SparseMatrix object
 *This class is meant to be used in an array, where multiple SparseRow objects can be stored to represent a full matrix without having to store common values
 */
class SparseRow {
protected:
    int row;//Row#
    int col;//Column#
    int value;//We will assume that all our values will be integers
    int index;//The index at which this SparseRow is stored in the array. THIS IS DEPRECATED AND IS NO LONGER USEFUL
public:
    SparseRow (); //default constructor;row=-1;col=-1;value=0
    SparseRow(int i, int r, int c, int v); //regular constructor: r = row, c = column, v = value
    void display();// print Row#, Column#, value in the following format: "<r> <c> <v>"
    
    //simply returns a row
    int getRow() {
        return row;
    };
    //sets the row
    void setRow(int r);
    //gets the column
    int getCol() {
        return col;
    };
    //sets the column
    void setCol(int c);
    //gets the value of this SparseRow
    int getValue() {
        return value;
    };
    //sets the value of this SparseRow
    void setValue(int v);
    // gets the index of this SparseRow
    int getIndex() {
        return index;
    };
    //sets the index of this SparseRow
    void setIndex(int i);
};

//SparseRow regular constructor, takes in r, c, v and i and sets them equal to the appropriate values
SparseRow::SparseRow(int i, int r, int c, int v) {
    this->setCol(r);
    this->setRow(c);
    this->setValue(v);
    this->setIndex(i);
}

//Default Constructor, defaults row and col to -1, defaults the value to 0 and index to NULL
//Generally, if a SparseRow object contains a value of 0 or an index of NULL, then there is a bug in the software
SparseRow::SparseRow() {
    this->setCol(-1);
    this->setRow(-1);
    this->setValue(0);
    this->setIndex(NULL);
}

/*
 *SparseMatrix class. contains 4 integers, noRows, noCols, commonValue and nonNonSparseValues
 *SparseMatrix also holds an array of SparseRows called myMatrix, which contains all of the values in
 *this matrix that are not equal to the common value. A SparseMatrix object is a condensed way to store a full
 *matrix. It achieves this by not storing any common values
 */
class SparseMatrix {
    
protected:
    int noRows; //Number of rows of the original matrix
    int noCols; //Number of columns of the original matrix
    int commonValue; //common value of this SparseMatrix
    int noNonSparseValues; //number of non sparse values in this SparseMatrix object
    SparseRow* myMatrix; //Array of SparseRows that contains info about the points in the array that are not the common value
    
public:SparseMatrix();
    SparseMatrix (int n, int m, int cv, int noNSV); //regular constructor. takes in the number of rows and columns, the commonValue and the number of nonSparseValues
    ~SparseMatrix(); //destructor that will deep delete the array
    SparseMatrix*Transpose (); //Transposes the matrix
    SparseMatrix*Multiply (SparseMatrix& M); //Multiplies two matrices together
    SparseMatrix*Add (SparseMatrix& M); //Adds two matrices together
    void display();//Display the sparse matrix
    void displayMatrix (); //Display the matrix in its original format
    void setSparseRow(int index, int r, int c,int v); //allows the user to change full rows at a time within the SparseMatrix
    SparseRow getSparseRow(int c); //returns the SparseRow stored at index c in myMatrix
    bool ifThereExistsANonSparseVariableAtRowCol(int r, int c);
    SparseRow getSparseRow(int r, int c); //method to get a SparseRow with the specified row and column
};

//destructor. deep deletes myMatrix
SparseMatrix::~SparseMatrix() {
    delete myMatrix;
};

//simply returns the SparseRow object stored at index c in myMatrix
SparseRow SparseMatrix::getSparseRow(int c) {
    return this->myMatrix[c];
};

//returns a SparseRow with row r and column c, returns a default SparseRow if that does not exists. This should only be called when it has already been confirmed that one exists
SparseRow SparseMatrix::getSparseRow(int r, int c) {
    for (int i = 0; i < noNonSparseValues; i++) {
        if (myMatrix[i].getCol() == c && myMatrix[i].getRow() == r) {
            return myMatrix[i];
        }
    }
    cout << "No NSV with Row " << r << "and Column" << c << endl;
    return SparseRow();
}

/*allows the user to essentially just set a new row in myMatrix. becuase of the way that memory allocation works
 *with arrays and the new operator, it is possible to create new objects of the myMatrix array that are out of
 *bounds of what the user originally set as the size of myMatrix. nsv can basically be set to any number
 */
void SparseMatrix::setSparseRow(int index, int r, int c, int v) {
    this->myMatrix[index].setRow(r);
    this->myMatrix[index].setCol(c);
    this->myMatrix[index].setValue(v);
    this->myMatrix[index].setIndex(index);
};

//sets the value of the SparseRow
void SparseRow::setValue(int v) {
    this->value = v;
};

//sets the row of the SparseRow
void SparseRow::setRow(int r) {
    this->row = r;
};

//sets the column of the SparseRow
void SparseRow::setCol(int c) {
    this->col = c;
};

//sets the index of the SparseRow
void SparseRow::setIndex(int i) {
    this->index = i;
}
//default constructor for SparseMatrix. takes in the number of rows and columns, the commonValue and the number of nonSparseValues, and initializes myMatrix
SparseMatrix::SparseMatrix (int n, int m, int cv, int noNSV) {
    noRows = n;
    noCols = m;
    commonValue = cv;
    noNonSparseValues = noNSV;
    myMatrix = new SparseRow[noNSV];
};

//default constructor for myMatrix. initializes noRows, noCols, commonValue and noNonSparseValues to 0, and leaves myMatrix pointing to the null pointer
SparseMatrix::SparseMatrix () {
    noRows = 0;
    noCols = 0;
    commonValue = 0;
    noNonSparseValues = 0;
    myMatrix = nullptr;
};

//boolean function that returns true if there is a non sparse value at row r and column c
bool SparseMatrix::ifThereExistsANonSparseVariableAtRowCol(int r, int c) {
    for (int i = 0; i < noNonSparseValues; i++) {
        if (this->getSparseRow(i).getRow() == r && this->getSparseRow(i).getCol() == c) {
            return true;
        }
    }
    return false;
};

//displays the single SparseRow in the following format: "<row> <col> <value>" and and endline
void SparseRow::display() {
    cout << this->getRow() << " " << this->getCol() << " " << this->getValue() << endl;
};

//transposes the matrix
SparseMatrix* SparseMatrix::Transpose() {
    
    //stores the temporary row, column and value inside of each iteration of the for loop below
    int r, c, v;
    
    //temp SparseMatrix object for return
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValue,noNonSparseValues);
    
    //this for loop initializes each SparseRow in myMatrix before use to make sure there is room for them
    for (int j = 0; j < noNonSparseValues; j++) {
        copy->getSparseRow(j) = getSparseRow(j);
    }
    
    //main for loop of this function. loops through all of the values in myMatrix and switches the row and column value
    for (int i = 0; i < noNonSparseValues; i++) {
        r = this->getSparseRow(i).getRow();
        c = this->getSparseRow(i).getCol();
        v = this->getSparseRow(i).getValue();
        copy->setSparseRow(i, c, r, v);
    }
    //returning the copy that has the switched row and column values
    return copy;
};

//multiplies two matrices together
SparseMatrix* SparseMatrix::Multiply(SparseMatrix &M) {
    
    //the SparseMatrix to be returned
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValue,0);
    
    //instantiating some variables
    int firstOneRow, firstOneCol, secondOneRow, secondOneCol, current, firstOneValue, secondOneValue, index;
    
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
            if (this->ifThereExistsANonSparseVariableAtRowCol(firstOneRow, firstOneCol) && M.ifThereExistsANonSparseVariableAtRowCol(secondOneRow, secondOneCol)) {
                
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
            (*copy).myMatrix[index].setCol(secondOneCol);
            (*copy).myMatrix[index].setRow(firstOneRow);
            (*copy).myMatrix[index].setValue(current);
            (*copy).noNonSparseValues++;
            
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
SparseMatrix* SparseMatrix::Add(SparseMatrix &M) {
    //creating a copy of the array
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValue,0);
    
    //starting values for the while loop and the value to be added once it is found
    int i = 0, j, valueToAdd;
    
    //whether the value has been found or not
    bool found;
    
    //boolean array so we dont have to instantiate a new bool every time
    bool* mArray = new bool[M.noNonSparseValues];
    
    //initializing all values in mArray
    for (int k=0; k < M.noNonSparseValues; k++) {
        mArray[k] = false;
    }
    
    //main while loop. loops through all non sparse values
    while (i < noNonSparseValues) {
        
        //reset j to 0 and found to false each iteration
        j = 0;
        found = false;
        
        //sets the row and column of the new one before its found
        (*copy).myMatrix[(*copy).noNonSparseValues].setRow(myMatrix[i].getRow());
        (*copy).myMatrix[(*copy).noNonSparseValues].setCol(myMatrix[i].getCol());
        
        //resetting valueToAdd
        valueToAdd = 0;
        
        //iterates through until either the value is found or we have gone through every entry in myMatrix
        while ((j < M.noNonSparseValues) && (!found)) {
            
            //checking the rows and columns of both matrices to see if they match,
            if ((myMatrix[i].getRow() == M.myMatrix[j].getRow()) &&
                (myMatrix[i].getCol() == M.myMatrix[j].getCol()) ) {
                
                //and if they do, then we set found to true, the value to valueToAdd, and also switch mArray[j] to true
                found = true;
                valueToAdd = M.myMatrix[j].getValue();
                mArray[j] = true;
                
            }
            //otherwise just keep going
            else j++;
        }
        
        //check to make sure that the two values dont equal the commonValue, otherwise we'll skip it
        if (myMatrix[i].getValue() + valueToAdd != commonValue) {
            (*copy).myMatrix[(*copy).noNonSparseValues++].setValue(myMatrix[i].getValue() + valueToAdd);
        }
        
        //increment i
        i++;
    }
    
    //adds the values to the copy's myMatrix
    for (int k=0; k < M.noNonSparseValues; k++) {
        if (!mArray[k]) {
            (*copy).myMatrix[(*copy).noNonSparseValues].setRow(myMatrix[k].getRow());
            (*copy).myMatrix[(*copy).noNonSparseValues].setCol(myMatrix[k].getCol());
            (*copy).myMatrix[(*copy).noNonSparseValues++].setValue(myMatrix[k].getValue());
        }
    }
    
    //returning the copy
    return copy;
};

//display method in SparseMatrix format. simply loops through myMatrix and calls display on each entry
void SparseMatrix::display() {
    for (int i = 0; i < this->noNonSparseValues; i++) {
        this->getSparseRow(i).display();
    }
};

//method to display the matrix in its original format
void SparseMatrix::displayMatrix() {
    
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

//main method. the code to insert values into the matrices is here, as well as the calls to all of the methods above
int main () {
    
    //initializing some variables before we use them
    int n, m, cv, noNSV, index, value;
    SparseMatrix* temp;
    
    //reset index to 0
    index = 0;
    
    //prompts the user for input. the program needs the number of rows and columns, the common value and the number of non sparse values
    cin >> n >> m >> cv >> noNSV;
    
    //initializing the first SparseMatrix with the values entered by the user
    SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);
    
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
    }
    
    //this process is exactly the same as the first one. please refer to the comments above
    cin >> n >> m >> cv >> noNSV;
    index = 0;
    
    SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);
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
    (*firstOne).display();
    cout << "First one in normal matrix format" << endl;
    (*firstOne).displayMatrix();
    cout << "Second one in sparse matrix format" << endl;
    (*secondOne).display();
    cout << "Second one in normal matrix format" << endl;
    (*secondOne).displayMatrix();
    cout << "After Transpose first one in normal format" << endl;
    temp = (*firstOne).Transpose();
    (*temp).displayMatrix();
    cout << "After Transpose second one in normal format" << endl;
    temp = (*secondOne).Transpose();
    (*temp).displayMatrix();
    cout << "Multiplication of matrices in sparse matrix form:" << endl;
    temp = (*secondOne).Multiply(*firstOne);
    (*temp).display();
    cout << "Addition of matrices in sparse matrix form:" << endl;
    temp = (*secondOne).Add(*firstOne);
    (*temp).display();
    
    return 0;
    
}
