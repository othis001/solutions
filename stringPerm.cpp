/*******************************
 * stringPerm.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a program that takes as input a string and then a list of positions
 *          we are allowed to swap. It will then return the string with the highest
 *          lexicographical order, we can obtain. 
 ******************************/

#include <iostream>
#include <string>
#include <list>
#include <map>

using namespace std;

/* We solve this problem using a graph. This is its node.
*/
class Node
{
  public:
    Node(int thename)
    {
        name = thename;
        visited = false;
    }
    int name;
    list <Node *> neighbors;
    bool visited;
};

class Graph
{
    public:
        Graph(string theword) // The constructor.
        {
            word = theword;
        }

        /* This adds an edge between a and b.
        */
        int add(int a, int b)
        {
            /* We use a map to store the addresses
               of each letter. If they aren't in
               the graph, we add them.
            */
             if(address.find(a) == address.end() )
            {
                address[a] = new Node(a);
            }
            if(address.find(b) == address.end() )
            {
                address[b] = new Node(b);
            }

            Node *a_node = address[a];
            Node *b_node = address[b];

            // Here we add the edge.
            a_node->neighbors.push_back( b_node );
            b_node->neighbors.push_back( a_node );
        }

        /* This calculates the max string.
        */
        string getmaxstring()
        {
            map<int, Node*>::iterator itr;
            list<int>::iterator jtr;
            list<char>::iterator ktr;

            // This iterates through the connected components of the graph.
            for(itr=address.begin(); itr != address.end(); itr++)
            {
                if(itr->second->visited == false)
                {
                    /* Here we get the positions in our component. They are
                       stored in the int list "component" in our class.
                    */
                    getcomponent(itr->second);
                    component.sort(); // Sorts the list.
          
                    /* Now get the corresponding letters.
                    */
                    list<char> charlist;
                    for(jtr=component.begin(); jtr != component.end(); jtr++)
                    {
                        charlist.push_back( word[ *jtr ] );
                    }
                    charlist.sort(); // Alphabetizes the letters.
                    charlist.reverse(); // We reverse the list since we want higher letters first.

                    /* Finally put them back into the word.
                    */
                    for(jtr=component.begin(), ktr=charlist.begin(); jtr != component.end(); jtr++, ktr++)
                    {
                        word[ *jtr ] = *ktr;
                    }
                }
                component.clear();  
            }
            return word;
        }

    private:
        /* This recursive function will get all the positions in the same component as node.
        */
        void getcomponent(Node *node)
        {
            if(node->visited) return;

            node->visited = true;

            component.push_back(node->name);
      
            list<Node *>::iterator i;

            for(i=node->neighbors.begin(); i != node->neighbors.end(); i++)
            {
                getcomponent(*i);
            }
        }

        list<int> component; // Stores a list of positions.
        string word;
        map <int, Node *> address; // Stores the address corresponding to each position.
};

int main() {

    int N, i, a, b;
    string input;

    cout << "\nThis is a program that takes as input a string and then a list of positions\n"
            "we are allowed to swap. It will then return the string with the highest\n"
            "lexicographical order, we can obtain.\n" << endl;

    cout << "Enter a string: ";
    cin >> input;

    Graph thegraph(input); 

    cout << "Enter how many positions you wish to exchange: ";
    cin >> N;

    cout << "Enter these positions. Ie 0 1 to allow the first and second letters to switched."
         << endl;

    for(i=0; i<N; i++)
    {
        cin >> a;
        cin >> b;

        thegraph.add(a,b);
    }
    
    cout << "The highest string we can obtain is: " << thegraph.getmaxstring() << endl;

    return 0;
}
