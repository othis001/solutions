/*******************************
 * ksub.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a program that takes as input an array and a
 *          number K and determines how many subsequences have
 *          sums that are divisible by K.
 ******************************/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/* The way this algorithm works is as follows. First we store
   how many prefixes have sums that are N mod K for each 0<=N<K.
   Then we note a subsequence (i , i+1 , ... , j) will have a sum
   of 0 mod K if and only if the prefixes (0, ... , i-1) and
   (0 , ... , j) have sums that are equal mod K. So we can count
   the total number by counting how many ways there are to choose
   two prefixes that have sums of N mod K for each 0<=N<K.
*/
long kSub(int K, vector < int > nums) 
{
    int i, size = nums.size();


    /* This array will store the number of prefixes that have sum
       i mod K in the ith position.
    */
    int prefixesmod[K];
    prefixesmod[0] = 1; // We add a 1 for the empty prefix.
    for(i=1; i<K; i++) prefixesmod[i] = 0;
  
    /* Now we go through the prefixes and populate our array.
    */
    int sum = 0;
    for(i=0; i<size; i++)
    {
        sum = (sum + nums[i])%K;
        prefixesmod[ sum ]++;
    }

    /* Finally we calculate prefixesmod[i] choose 2 for each
       0<=i<K and sum the values up.
    */
    long seqnum = 0;
    for(i=0; i<K; i++)
    {
        seqnum = seqnum + ( prefixesmod[i] * (prefixesmod[i] - 1) ) / 2;
    }
  
    return seqnum;
}

int main() 
{
    int N, K;

    cout << "\nThis is a program that takes as input an array and a\n"
            "number K and determines how many subsequences have\n"
            "sums that are divisible by K.\n" << endl;

    cout << "Input the number of elements in the array: ";
    cin >> N;

    cout << "Input the array: ";

    vector<int> nums;
    int temp;
    for(int i = 0; i < N; i++)
    {
        cin >> temp;
        nums.push_back(temp);
    }
   
    cout << "Input a number K: ";
    cin >> K;

    cout << "There are " << kSub(K, nums) << " such subsequences." << endl;

    return 0;
}
