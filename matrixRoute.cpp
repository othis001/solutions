/*******************************
 * subseqFlip.cpp by Oliver Thistlethwaite
 *
 * Purpose: This function takes as input a matrix where each entry is either
 *          0 or 1. We assume the top left and bottom right entries are 1 and
 *          then count how many paths of 1s are between them. While on a path
 *          we may only move right or down.
 ******************************/

#include <iostream>
#include <string>

using namespace std;

/* We will use this class to store our matrix. Note that this class
   envisions the matrix as being surrounded by a frame of 0s which we
   do to simplify the code below.
*/
class Matrix
{
    public:
        Matrix(int *thematrix, int theN, int theM)
        {
            N = theN;
            M = theM;
            matrix = thematrix;
        }
        int get(int n, int m)
        {
            if(n < 0 || m < 0 || n >= N || m >= M) return 0;
            else return matrix[N*n + m];
        }
        void set(int n, int m, int value)
        {
            matrix[N*n + m] = value;
        }
        int N, M;
    private:
        int *matrix;
};

/* This recursive function returns the number of paths from the
   coordinate (i,j) to the end point.
*/
int getPath(Matrix mat, int i, int j)
{
    if(mat.get(i,j) == 0) // The entry is 0 so just return 0.
    {
        return 0;
    }
    else if(i == mat.N-1 && j == mat.M-1) // The entry is the end point.
    {
        return 1;
    }
    else // We call the function recursively on the entries below and to the right.
    {
        return getPath(mat, i+1, j) + getPath(mat, i, j+1);
    }
}

/* This function returns the number of paths from (0,0) to (N-1,M-1).
*/
int numberOfPaths(Matrix mat)
{
    int i, j, N = mat.N, M = mat.M;
  
    /* First we do this step to eliminate dead ends.
    */
    for(i=N-1; i>=0; i--)
    {
        for(j=M-1; j>=0; j--)
        {
            if(i == N-1 && j == M-1) continue; // Don't eliminate the end point!

            if(mat.get(i,j) == 1 && mat.get(i+1,j) == 0 && mat.get(i,j+1) == 0)
            {
                mat.set(i,j, 0);
            }
        }
    }    

    /* Now call the recursive getPath function to find the number of paths.
    */
    return getPath(mat, 0, 0);
}


int main()
{
    int N, M, i, j;

    cout << "This function takes as input a matrix where each entry is either\n"
            "0 or 1. We assume the top left and bottom right entries are 1 and\n"
            "then count how many paths of 1s are between them. While on a path,\n"
            "we may only move right or down.\n" << endl;
                                        
    cout << "Enter the dimensions of the matrix: ";
    cin >> N; cin >> M;

    cout << "Enter the matrix." << endl;

    int *input = new int[N*M];
    for(i=0; i< N*M; i++)
    {
        cin >> input[i];
    }

    Matrix mat(input, N, M);  

    cout << "There are " << numberOfPaths(mat) << " paths." << endl;

    return 0;
}
