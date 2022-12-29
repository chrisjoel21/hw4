#include <iostream>
#include <fstream>
#include "Queue.h"
#include "BST.h"
#include "ArgumentManager.h"
using namespace std;
// get text between some text
string get_enclosed(string s, char start = '(', char end = ')')
{
    int index = s.length() - 1;
    while (s[index] != end)
    {
        if (index <= 1)
            return " ";
        index--;
    }
    string value;
    for (int i = index - 1; i >= 0; i--)
    {
        if (s[i] == start)
            break;
        value = s[i] + value;
    }
    return value;
}
// get substring of string
string sub_string(string s, int a = 0, int b = 0)
{
    string ss;
    for (int i = a; i < b; i++)
    {
        ss += s[i];
    }
    return ss;
}

// add
string add(string s, string cmd)
{
    string newstr;
    for (int i = 0; i < s.length(); i++)
    {
        newstr += s[i];
        if (s[i] == cmd[0])
        {
            newstr += cmd[2];
        }
    }
    return newstr;
}
// remove
string remove(string s, string cmd)
{
    string newstr;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != cmd[0])
        {
            newstr += s[i];
        }
    }
    return newstr;
}
// replace
string replace(string s, string cmd)
{
    string newstr;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != cmd[0])
        {
            newstr += s[i];
        }
        else
        {
            newstr += cmd[2];
        }
    }
    return newstr;
}
// swap
string swap(string s, string cmd)
{
    string newstr;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == cmd[0])
        {
            newstr += cmd[2];
        }
        else if (s[i] == cmd[2])
        {
            newstr += cmd[0];
        }
        else
        {
            newstr += s[i];
        }
    }
    return newstr;
}

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        std::cout << "Invalid parameters" << std::endl;
        return -1;
    }
    ArgumentManager am(argc, argv);
    string infilename = am.get("input"); // get the input filename
    string outfilename = am.get("output");
    ifstream infile;
    infile.open(infilename);
    Queue msgQ;
    PriorityQueue cmdQ;
    string line, output;
    BSTNode *root = NULL;
    // load commands from file
    while (getline(infile, line, '\n'))
    {
        string priority = get_enclosed(line);
                cout << priority << endl;

        if (priority != " ")
        {
            cmdQ.enqueue(line, atoi(priority.c_str()));
        }else{
            break;
        }
    }

    infile.clear();
    infile.close();

    // process command
    while (!cmdQ.isEmpty())
    {

        string command = cmdQ.dequeue();

        if (sub_string(command, 0, 6) == "DECODE")
        {
            msgQ.enqueue(get_enclosed(command, '[', ']'));
        }
        else if (!msgQ.isEmpty())
        {
            if (sub_string(command, 0, 7) == "REPLACE")
            {
                string cmd;
                cmd +=command.substr(command.find('[')+1,(command.find(']')-command.find('['))-1);
                string j = msgQ.dequeue(); 
                msgQ.enqueue(replace(j, cmd));
                //msgQ.enqueue(replace(msgQ.dequeue(), get_enclosed(command, '[', ']')));
            }
            else if (sub_string(command, 0, 3) == "ADD")
            {   
                string cmd;
                cmd +=command.substr(command.find('[')+1,(command.find(']')-command.find('['))-1);
                string j = msgQ.dequeue(); 
                msgQ.enqueue(add(j, cmd));
                //msgQ.enqueue(add(msgQ.dequeue(), get_enclosed(command, '[', ']')));
            }
            else if (sub_string(command, 0, 6) == "REMOVE")
            {
                string cmd;
                cmd +=command.substr(command.find('[')+1,(command.find(']')-command.find('['))-1);
                string j = msgQ.dequeue(); 
                msgQ.enqueue(remove(j, cmd));
                //msgQ.enqueue(remove(msgQ.dequeue(), get_enclosed(command, '[', ']')));
            }
            else if (sub_string(command, 0, 4) == "SWAP")
            {
                string cmd;
                cmd +=command.substr(command.find('[')+1,(command.find(']')-command.find('['))-1);
                string j = msgQ.dequeue(); 
                msgQ.enqueue(swap(j, cmd));
               // msgQ.enqueue(swap(msgQ.dequeue(), get_enclosed(command, '[', ']')));
            }
            else if (sub_string(command, 0, 3) == "BST")
            {
                string message = msgQ.dequeue();

                if (root == NULL)
                {
                    root = new BSTNode(message);
                }
                else
                {
                    root->insert(new BSTNode(message));
                }
            }
        }
    }
    if (root != NULL)
    {
        if (line == "Inorder")
        {
            root->inOrder(output);
        }
        else if (line == "Preorder")
        {

            root->preOrder(output);
        }
        else if (line == "Postorder")
        {
            root->postOrder(output);
        }
    }

    std::cout << output;

    ofstream outfile;
    outfile.open(outfilename);
    if (outfile.is_open())
    {
        outfile << output;
    }
    outfile.close();
    delete root;
    return 0;
}