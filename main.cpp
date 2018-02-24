/*===========================================================================================================
 * Author: Brian Hane
 * Date: 24/01/2018
 * Description: Prompts user for matrix input, gets
 * 	determinant,adjoint, and inverse of inputted matrix
 *===========================================================================================================
 */
#include<iostream>
#include<iomanip>
using namespace std;

//declare functions
float calcDeterminant (float **matrix,int n);
void cofactor (float **matrix,float **holder,int r, int c, int n);
void adjugate(float **matrix,float **adju,int n);
bool inverseMatrix(float **matrix, float **inverse,int n);

//function calculates the determinant
float calcDeterminant(float **matrix,int n){
    //declare and initalize variables
	int i=0,j=0,sign=1;
    float det=0;
	//for storing cofactors
    float **holder = new float*[n];
    //allocate memory for each row of 2d array
    for (i = 0; i <n; ++i){
    	holder[i] = new float[n];
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
           holder[i][j] = matrix[i][j];
        }
    }
	//matrix contains single element
	if (n==1){
		return matrix[0][0];
	}
	for (int x =0; x<n;x++){
		cofactor(matrix,holder,0,x,n);
		det += (sign* matrix[0][x] * calcDeterminant(holder,n-1));
		sign =(-sign);//alternate sign for next term
	}

	//free memory of array, then clear array to prevent memory errors
	for (int i = 0; i <n; i++){
	    	delete[] holder[i];
	   }
	delete [] holder;
	holder = NULL;

	return det;
}
//function gets the cofactor matrix
void cofactor (float **matrix, float **holder,int r, int c, int n){
    //declare and initalize variables
	int i=0,j=0;
	//loop through each index of matrix
	for(int row =0; row<n; row++){
		for (int col=0; col<n; col++){
			//copy into holder, elements that are not in given row/col
			if(row !=r && col!=c){
				holder[i][j++] = matrix[row][col];
				//row is filled so move to next row index and reset col index
				if (j== n -1){
					j=0;
					i++;
				}
			}
		}
	}
}//end cofactor

//function gets the adjoint matrix
void adjugate(float **matrix,float **adju,int n){
	//declare and initalize variables
	int x=0, i=0, sign = 1;

	if (n==1){
		adju[0][0] = 1;
	}
	//array used to store cofactors of matrix
	float **holder = new float*[n];
	//allocate memory for each row of 2d array
	for (i = 0; i <n; ++i){
		holder[i] = new float[n];
	}

	    for (i=0; i<n; i++){
	        for (x=0; x<n; x++){
	            //get cofactor
	            cofactor(matrix, holder, i, x, n);
	            // sign is positive if sum of row and column index equals even.
                if ((i+x)%2==0)
	            	sign=1;
	            else
	            	sign=-1;
	            //transposition of cofactor matrix
	            adju[x][i] = sign*calcDeterminant(holder, n-1);
	        }
	    }
	 //free memory of array, then clear array to prevent memory errors
	for (int i = 0; i <n; i++){
			delete[] holder[i];
	   }
	delete [] holder;
	holder = NULL;
}
//function gets the inverted matrix
bool inverseMatrix(float **matrix, float **inverse, int n){
    //declare and initalize variables
	int i=0,j=0;
	float det=0;

    float **adjoint = new float*[n];
    //allocate memory for each row of 2d array
    for (int i = 0; i <n; ++i){
    	adjoint[i] = new float[n];
    }
    //get determinant of matrix
	det = calcDeterminant (matrix,n);

	//singular matrix, has no inverse
	if (det==0){
		return false;
	}

	//get adjoint of matrix
	adjugate(matrix,adjoint,n);
	//get the inverse by dividing the matrix's adjoint and determinant
	for (i =0; i<n; i++){
		for(j=0; j<n; j++){
            //cast det to float because invert matrix is float
			inverse[i][j] = adjoint[i][j]/(det);
		}
	}
	//free memory of array, then clear array to prevent memory errors
	for (int i = 0; i <n; i++){
	    	delete[] adjoint[i];
	   }
	delete [] adjoint;
	adjoint = NULL;

	return true;
}
int main(){
	//declare and initialize variables
    int i=0, j=0,n=0;
    float determinant=0;
    //get matrix dimensions
    cout<<"Enter matrix dimension NxN:\n";
    cin>>n;

    // allocate memory for array of pointers
    float **matrix = new float*[n];
    float **adjoint = new float*[n];
    float **inverse = new float*[n];
    //allocate memory for each row of 2d array
    for (i = 0; i <n; ++i)
    	matrix[i] = new float[n];
    for (i = 0; i <n; ++i)
    	adjoint[i] = new float[n];
    for (i = 0; i <n; ++i)
    	inverse[i] = new float[n];

    //get array elements
    cout<<"Enter matrix elements row wise:\n";
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
           cin>>matrix[i][j];
        }
    }
    //print array obtained
    cout<<"\nInput matrix:";
    for(i = 0; i < n; i++){
        cout<<"\n";
        for(j = 0; j < n; j++)
            cout<<matrix[i][j]<<"\t";
    }
    //finding determinant
    determinant = calcDeterminant(matrix,n);
    cout<<"\n\nDeterminant: "<<determinant;

    //get adjoint of matrix
    adjugate(matrix,adjoint,n);
    //print resulting matrix
    cout<<"\n\nAdjoint matrix:";
    for(i = 0; i < n; i++){
        cout<<"\n";
        for(j = 0; j < n; j++)
            cout<<adjoint[i][j]<<"\t";
    }
    //check for singular matrix, print result inverse if not
    if(inverseMatrix(matrix,inverse,n)){
        cout<<"\n\nInverse matrix:";
        for(i = 0; i < n; i++){
            cout<<"\n";
            for(j = 0; j < n; j++){
                //round the output to 3 decimal points
                cout<<setprecision(3)<<fixed<<inverse[i][j]<<"\t";
            }
        }
    }else{
        cout<<"\nSingular matrix, does not have an inverse";
    }
    //free the memory that was allocated for each row
   for (i = 0; i <n; ++i){
    	delete [] matrix[i];
   }
   for (i = 0; i <n; ++i){
    	delete [] inverse[i];
   }
   for (i = 0; i <n; ++i){
    	delete [] adjoint[i];
   }
   //free memory of first row
   delete [] matrix;
   delete [] adjoint;
   delete [] inverse;

   //clear arrays to prevent memory reference errors
   matrix = NULL;
   adjoint = NULL;
   inverse = NULL;
   return 0;
}
