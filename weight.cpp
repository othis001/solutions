/*******************************
 * weight.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a program that takes as input an array and then
 *          an array of weights where each weight corresponds to the
 *          corresponding entry in the first array. We then return
 *          the maximum weight formed by an INCREASING subsequence. 
 ******************************/
#include <iostream>
#include <map>

using namespace std;

long long maxw(int A[][2], int size)
{
    int i; long long max, total_max = 0;

    /* This map best stores a list of values together with the highest
       weight that corresponds to a subsequence starting at each value.
       We create this so that for each element we encounter as we move
       right to left, we immediately know what subsequence to append to
       it to obtain a maximally weighted subsequence.
    */
    map<int , long long> best;
    map<int , long long>::iterator itr;
    
    for(i=size-1; i>=0; i--)
    {
        max = A[i][1]; // max will be the highest weight of a subsequence
                       // starting at A[i].
        
        /* Since we only care about increasing subsequences, the next
           highest value in our map will be the best choice to form
           a subsequence.
        */      
        itr = best.upper_bound( A[i][0] );
        if(itr != best.end() ) max += itr->second;
        
        /* If there is already an entry in best with the same value and
           a higher weight, we don't touch it.
        */
        if(best[ A[i][0] ] < max)         
        {                        
            best[ A[i][0] ] = max; // Add A[i] to best.
            if(max > total_max) total_max = max; // This is the highest subsequence.

            /* We do this last step to remove all entries with lower values
               and lower weights than what we just put in, since these entries
               will never be chosen. Also it makes the upper_bound above become
               the best choice.
            */
            itr = best.begin();
            while(itr->first < A[i][0])
            {
                if(itr->second < max) best.erase(itr++);
                else itr++;
            }
        }       
    }    
    return total_max;
}

int main() 
{
    int N, i;
       
    cout << "\nThis is a program that takes as input an array and then\n"
            "an array of weights where each weight corresponds to the\n"
            "corresponding entry in the first array. We then return\n"
            "the maximum weight formed by an INCREASING subsequence.\n" << endl;

    cout << "Enter the size of the array: ";
    cin >> N;
        
    int A[N][2]; // This 2D array stores the weighted array.
     
    cout << "Enter the array: ";   
    for(i=0; i<N; i++)
    {
        cin >> A[i][0];    
    }

    cout << "Enter the weights: ";
    for(i=0; i<N; i++)
    {
        cin >> A[i][1];
    }
       
    cout << "The maximum weight obtained by an INCREASING subsequence is " << maxw(A, N) << "." << endl;   

    return 0;
}
