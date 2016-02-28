/*******************************
 * selfSimilarity.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a program that takes as input a string and determines its self-similarity
 *          or the total number of places in all the beginnings of its substrings that match
 *          the whole string.
 ******************************/

#include<string>
#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

long long calculate_count(string s)
{
    int length = s.length(), left, right, i, counter;

    /* The count vector stores the number of place that are the same as the beginning of the string
       starting at (and including) the ith position for each i.
    */
    vector<long long> count(length, 0);     // Adds the suffix consisting of the whole set.
                                            // We skip the first element in our algorithm
    count[0] = length;                      // due to the slowness of the first iteration.
 

    left = 0; // These store a subsequence that is the same as the beginning of s.
    right = 0;
    
    for(i=1;i<length;i++)
    {
        if(i<=right) // The i position is contained in the current similar subsequence.
        {
            /* Here we set count[i] = the smaller of the number of elements in our subsequence after
               (and including) i AND how many places are good after (and including) the element at
               the beginning of the string that corresponds to i in the substring.
            */
            if(right - i + 1 < count[ i - left ]) count[i] = right - i + 1; 
            else count[i] = count[ i - left ];                             
        }  
                                                           
        while(i + count[i] < length && s[ count[i] ] == s[i + count[i] ]) // Try to extend it from starting point i.
        {
            if(i + count[i] > right) // We suceeded so make a new subsequence starting at i to that point. 
            {
                left = i;
                right = i + count[i];  
            }
            count[i]++; // Implement count and try again.
        }
    }

    /* Finally add them all up and return. */
    counter = 0; 
    for(int i=0;i<count.size();i++)
    {
        counter = counter + count[i];
    }

    return counter;
}

int main()
{
    string input;

    cout << "\nThis is a program that takes as input a string and determines its\n"
            "self-similarity or the total number of places in all the beginnings\n"
            "of its substrings that match the whole string.\n" << endl;
 
    cout << "Enter the string: ";  
    cin >> input;     
    cout << "The string's self-similarity is " << calculate_count(input) << "." << endl;

    return 0;
}
