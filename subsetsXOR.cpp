/*******************************
 * subsetsXOR.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a program that takes an input an array of nonnegative integers.
 *          It will then compute the sum of the XORs of all the subsets.
 ******************************/

#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

long long XORsubsets(vector<int> input)
{
     int k, i, size = input.size();
     long long total = 0;

    /* First we count the number of entries that have the kth bit set for each
       0<=k<30 and store that information in kbitset.
    */
    int kbitset[31];
    for(k=0; k<31; k++)
    {
        kbitset[k] = 0;
        for(i=0; i<size; i++)
        {
            if( (input[i] & (1 << k)) != 0) kbitset[k]++;
        }
    }
 
    total = 0;
    for(k=0; k<31; k++)
    {
        /* Now we traverse each bit position. Any choice of subset with an odd number
           of 1s in the kth positions will contribute a 2^k to the total sum. The number
           of subsets that will contribute a 2^k will be the number of ways to chose
           a subset where each element has a 0 in the kth position times the number
           of ways to choose a subset of odd size where each element has a 1 in the kth
           position. If you do the math, you will find this number is always 2^(size-1)
           provided at least one entry has a 1 in its kth bit position. So if we multiply
           this number by 2^k, we obtain the total contribution.
        */
        if(kbitset[k] != 0)
        {
            total += pow(2, k + size - 1);
        }
    }
    
    return total;
}

int main() {
    int i,j,K, N, a;    

    cout << "\nThis is a program that takes an input an array of nonnegative integers.\n"
                "It will then compute the sum of the XORs of all the subsets.\n" << endl;


    cout << "Enter the size of the array: ";
    cin >> N;
        
    cout << "Enter the array: ";
    vector<int> input;      
    for(j=0; j<N; j++)
    {
        cin >> a;  
        input.push_back(a);
    }

    cout << "The sum of the XORs of all the subsets is " << XORsubsets(input) << "." << endl;

    return 0;
}
