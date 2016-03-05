/*******************************
 * connections.cpp by Oliver Thistlethwaite
 *
 * Purpose: This function takes as input an array of positive integers that
 *          represent positions of towns on a line and then an array of
 *          their populations. We calculate the total amount of wire needed
 *          to connect each person to each other person. 
 ******************************/

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

/* To increase readability of the code, we create a town class.
*/
class Town
{
  public:
      Town()
      {
      }
      int pop;
      int pos;    
};

/* We will want to order the towns by population so we create
   a < operator.
*/
bool operator < (Town const &a, Town const &b)
{
    if(a.pop == b.pop)
    {
        return a.pos < b.pos;
    }
    
    return a.pop < b.pop;
}

/* Now we create a binary search tree to store sums of positions and numbers
   of towns to the right of each town.
*/
class Node
{
    public:
        Node(int thepos)
        {
            pos = thepos;
            rsum = 0;
            rnum = 0;
            left = NULL;
            right = NULL;
        }
        int pos;    
        long long rsum;
        long long rnum;
        Node *left, *right;
};
class Tree
{  
    public:
        Tree()
        {
            root = NULL;            
        }
        void add(int pos) // This adds a town to our tree.
        {
            if(root == NULL) root = new Node(pos);
            else radd(pos, root);
        }

        /* This queries the tree to obtain the number of towns to the right of a
           position as well as the sum of their positions.
        */
        vector<long long> query(int pos)
        {
            long long sum = 0, num = 0;
            return rquery(pos, root, sum, num);
        }

    private:
        void radd(int pos, Node *node) // The recursive function.
        {
            /* The idea here is we want to store the number and the
               sum of positions of all the towns contained in the
               right subtree of each node. So when we are adding a new
               town and we move to a node's right child, we increment
               variables in that node that store this information.
            */
            if(pos > node->pos)
            {
                node->rsum += pos;
                node->rnum ++;

                if(node->right == NULL) node->right = new Node(pos);  
                else radd(pos, node->right);
            }
            else
            {
                if(node->left == NULL) node->left = new Node(pos);       
                else radd(pos, node->left);
            }
        }
        vector<long long> rquery(int pos, Node *node, long long sum, long long num)
        {            
            vector<long long> output;
             
            if(pos > node->pos)
            {
                return rquery(pos, node->right, sum, num);   
            }
            else if(pos < node->pos) // If we move to a left child, we increment
            {                        // our counters with the node and all its
                sum += node->pos;    // right descendants.
                num ++;
                
                sum += node->rsum;
                num += node->rnum;
                
                return rquery(pos, node->left, sum, num);                
            }
            else // We have found what we queried so finally add its right descendants
            {    // to our counters and return.
                sum += node->rsum;
                num += node->rnum;
                
                output.push_back(sum);
                output.push_back(num);
                return output;
            }                
        }
        Node *root;
};


unsigned long long lengthOfWire(Town towns[], int size)
{
    long long i, lsum, rsum, lnum, rnum, pos, pop, tsum = 0;
    unsigned long long wire = 0;
    
    /* We sort by population so as we move through our array of towns,
       we know exactly how many wires are needed to connect to each
       previous town.
    */
    sort(towns, towns+size);

    Tree thetree;
        
    for(i=0; i<size; i++)
    {
        pos = towns[i].pos;
        pop = towns[i].pop;
        
        thetree.add(pos); // Adds the town to the tree.
        
        /* Here we find the number and sum of positions of towns with 
           lower or equal population to the right of our current position.
        */
        vector<long long> output;
        output = thetree.query(pos);
        rsum = output[0];
        rnum = output[1];          
          
        /* This is how much wire we will need to connect to them.
        */
        wire += pop * (rsum - (rnum * pos) );
            
        /* We can save a lot of time by realizing the same information
           can be obtained for the left towns by simply subtracting the
           information for the right towns from the totals.
        */
        lsum = tsum - rsum;
        lnum = i - rnum;
        
        wire += pop * ((lnum * pos) - lsum);    
                    
        tsum += pos; // The current total sum of positions.
    }
    
    return wire;
}

int main() {
    int N, i, j;
       
    cout << "\nThis function takes as input an array of positive integers that\n"
            "represent positions of towns on a line and then an array of\n"
            "their populations. We calculate the total amount of wire needed\n"
            "to connect each person to each other person.\n"<< endl;

    cout << "Enter the number of towns: ";
    cin >> N;

    int C[N][2];

    cout << "Enter the positions of the towns: ";
    for(j=0; j<N; j++)
    {
        cin >> C[j][0];
    }

    cout << "Now enter their populations: ";
    for(j=0; j<N; j++)
    {
        cin >> C[j][1];
    } 
  
    Town towns[N];
    for(j=0; j<N; j++)
    {
        towns[j].pos = C[j][0];
        towns[j].pop = C[j][1];  
    } 

    cout << lengthOfWire(towns, N) << " units of wire is required." << endl;

    return 0;
}
