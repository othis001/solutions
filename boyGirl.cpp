/*******************************
 * boygirl.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a program that takes as input a string of the form
 *          GGBGBB which represents a seating arrangment of boys and 
 *          girls in row. The program will then calculate the minimum
 *          numbers of swaps necessary to ensure K girls will be seated
 *          together. Note we may only swap adjacent seats.
 ******************************/

#include<string>
#include<iostream>
#include<vector>
#include<cmath>
#include<limits>

using namespace std;


int minimumSwapsRequired(int m, string s)
{
    int length = s.size(), i, j, k;
    
    int bcount, gcount, pos[m], boycount[m], boysinbetween, left, right, min = length;

    bcount = 0, gcount = 0 , j=0;
    left = -1, right = -1; // If these are unchanged, we know there are not enough girls.

    /* During this for loop, we find m girls that have the
       smallest number of boys between them.
    */
    for(i=0; i<length; i++)
    {     
        if(s[i] == 'G')
        {
            gcount++; // This counts the number of girls.                      
            pos[ gcount % m ] = i; // This array stores the positions of the last m girls.
            boycount[ gcount % m] = bcount; // We also store the number of boys before each
                                            // girl's position.
            if(gcount >= m) // If we have read in at least m girls.
            {
                /* This calculates the number of boys between the last m girls.
                   If that number is a minimum, we store the positions of the
                   first and last girl.
                */                               
                boysinbetween = boycount[ gcount % m ] - boycount[ (gcount + 1) % m ];
                if(boysinbetween < min)
                {
                    left = pos[ (gcount + 1) % m];
                    right =  pos[ gcount % m];
                    min = boysinbetween;
                } 
            }     
        } 
        else if(s[i] == 'B')
        {
            bcount++;  
        }      
    }

    if(left == -1) return -1; // Not enough girls so we return -1 to specify an error.
        
    int swaps = 0;
    char temp;

    /* After the first for loop, we now have a substring of the form GBBGBBBG.
       The idea is, we want to calculate the minimum number of swaps necessary
       to move all the boys in the middle to the edges so all the girls can sit
       together.
    */
    for(i=left; i<right;i++)
    {
        if(s[i] == 'B') // We have encountered a boy.
        {
            if(i-left < right-i) // The boy is closer to the left.
            {          
                for(k=left; k<i; k++) // Repeatedly swap to move them to the left.
                {
                    temp = s[k];
                    s[k] = s[k+1];
                    s[k+1] = temp;

                    swaps++;
                }
                left++; // Shrinks the substring since the left position is now
            }           // occupied by a boy.
            else  // The boy is midway or closer to the right.
            {     
                for(k=right; k>i; k--) // Repeatedly swap and move them to the right.
                {
                    temp = s[k];
                    s[k] = s[k-1];
                    s[k-1] = temp;

                    swaps++;
                }
                right--; // Shrinks the substring since the right position is now
            }            // occupied by a boy.
        }
    } 
    return swaps;
}

int main()
{
    int swaps;
    int m;
    string seats;

    cout << "\nThis is a program that takes as input a string of the form \n"
            "GGBGBB which represents a seating arrangment of boys and \n" 
            "girls in row. The program will then calculate the minimum \n"
            "numbers of swaps necessary to ensure M girls will be seated \n"
            "together. Note we may only swap adjacent seats. \n" << endl;

    cout << "Enter the number of girls desired to be seated together: ";
    cin >> m;

    cin.ignore (numeric_limits<streamsize>::max(), '\n'); // Flushes the input buffer.
    
    cout << "Enter the seating arrangment: ";    
    getline(cin, seats);
    
    swaps = minimumSwapsRequired(m, seats);

    if(swaps == -1) cout << "There are not enough girls!" << endl;
    else            cout << swaps << " swaps are required." << endl;
    
    return 0;
}


