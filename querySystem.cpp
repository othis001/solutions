/*******************************
 * querySystem.cpp by Oliver Thistlethwaite
 *
 * Purpose: This is a program that implements a simple query system.
 ******************************/

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <limits>

using namespace std;

// This program will probably only make sense after you run it!

/* We use a tree to store our data. Here is its node.
*/
class Node
{
    public:
        Node(string thename)
        {
            name = thename;
        }
        string name;
        list <Node *> children;
        list <string> questions;   
};

/* The tree our data is stored in.
*/
class Tree
{
    public:
        Tree() // The constuctor
        {
            string word;

            cin >> word;

            root = new Node(word);
            address[word] = root;

            cin >> word; // Skips the first (
            add(root);
        }

        /* This function reads from stdin and decodes the flat tree format.
        */
        void add(Node *node)
        {
            Node *temp;
            string word;

            cin >> word;
            while(word != ")")
            {
                if(word == "(")
                {
                    add(temp);
                    cin >> word;
                    continue;
                }
                temp = new Node(word);
                address[word] = temp;
                node->children.push_back(temp);
      
                cin >> word;  
           }    
           return;
       }
       /* This function adds a question to a thing.
       */
       bool addQuestion(string thing, string question)
       {
           if(address.find(thing) == address.end() )
           {
               return false;
           }

           ( address[thing] )-> questions.push_back(question);

           return true;
       }

       /* This function counts how many times a query occurs.
       */       
       int count(string thing, string question)
       {
           if(address.find(thing) == address.end() )
           {
               return -1;
           }

           return countit( address[thing] , question);
       }

   private:
       /* This is a recursive function that goes through the tree seeing if any children
          have a corresponding question.
       */
       int countit(Node *node, string question)
       {
           int count = 0;

           list<string>::iterator i;
           for(i = ( node->questions ).begin(); i != ( node->questions ).end(); i++)
           {
               if(question == ( *i ).substr(0, question.length() ) ) count++;
           }

           list<Node *>::iterator j;
           for(j = ( node->children ).begin(); j != ( node->children ).end(); j++)
           {
               count = count + countit( *j, question);
           }

           return count;
       }

       Node *root; // The root of the tree.
       map <string, Node *> address; // A map to store where topics nodes are located.
};

int main() 
{
    int i, pos, K, M, count;
    string line, word, thing, question;

    cout << "This program implements a simple query system.\n" << endl;

    cout << "Enter the topics in a flat tree format.\n"
            "For example: Pet ( Cat Dog ( Akita Retriever ) )" << endl;

    Tree data;
   
    cout << "Enter the number of questions you wish add: ";
    cin >> M;

    cout << "Enter each question in the form \"Pet: Should I get one?\"" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for(i=0; i<M; i++)
    {
        getline(cin, line);
        pos = line.find(":");
        thing = line.substr(0, pos);
        question = line.substr(pos+2);
   
        if( ! data.addQuestion(thing, question) )
        {
            cout << "Topic not found!" << endl;
        }
    }

    cout << "Enter the number of queries to make: ";

    cin >> K;

    cout << "Enter each query in the form \"Pet: Should I\"" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for(i=0; i<K; i++)
    {
        getline(cin, line);
        pos = line.find(":");
        thing = line.substr(0, pos);
        question = line.substr(pos+2);

        count = data.count(thing, question);
        if(count == -1)
        {
            cout << "Topic not found!" << endl;
        }
        else
        {
            cout << "This question occurred " << count << " times." << endl;
        }    
    }
    return 0;
}
