#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "queue.h"
#include "BST.h"
//#include "PrioQueue.h"
#include "ArgumentManager.h"

using namespace std;
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
int main(int argc, char *argv[]){
ArgumentManager am (argc, argv);
string input = am.get("input");
string output = am.get("output");

ifstream ifs("input1.txt");
ofstream ofs("output1.txt");

//ifstream ifs(input);
//ofstream ofs(output);

string line;
string outputs;
PriorityQueue instr; 
Queue msgQ;
BSTNode *root = NULL;

while(getline(ifs,line)){
    
    string priority = line.substr(line.find('(')+1,(line.find(')')-line.find('('))-1);
        if (priority != " ")
        {
            instr.enqueue(line, atoi(priority.c_str()));
        }
    }   

//instr.print();
string message;
while (!instr.isEmpty()){
    string command = instr.dequeue();
    if(command.find("DECODE")==0){
        message =instr.getFront().substr(instr.getFront().find('[')+1,(instr.getFront().find(']')-instr.getFront().find('['))-1);
        cout << message <<endl;
        msgQ.enqueue(message);

}
else if (!msgQ.isEmpty()) {
    if(command.find("REPLACE")==0){
    string cmd;
    cmd +=instr.getFront().substr(instr.getFront().find('[')+1,(instr.getFront().find(']')-instr.getFront().find('['))-1);
    //cmd +=instr.getFront().substr(instr.getFront().find(',')+1,(instr.getFront().find(']')-instr.getFront().find(','))-1);
    cout << cmd <<endl;
    
message = replace(message, cmd);
cout << message <<endl;
msgQ.enqueue(message);

//instr.dequeue();
}else if(command.find("ADD")==0){
    string cmd;
    cmd +=instr.getFront().substr(instr.getFront().find('[')+1,(instr.getFront().find(']')-instr.getFront().find('['))-1);
    cout << cmd <<endl;
message = add(message, cmd);
cout << message <<endl;
msgQ.enqueue(message);


//instr.dequeue();
} else if(command.find("REMOVE")==0){
    string cmd;
    cmd +=instr.getFront().substr(instr.getFront().find('[')+1,(instr.getFront().find(']')-instr.getFront().find('['))-1);
    cout << cmd <<endl;
message = remove(message, cmd);
cout << message <<endl;
msgQ.enqueue(message);
//instr.dequeue();
} else if(command.find("SWAP")==0){
    string cmd;
    cmd +=instr.getFront().substr(instr.getFront().find('[')+1,(instr.getFront().find(']')-instr.getFront().find('['))-1);
    cout << cmd <<endl;
message = swap(message, cmd);
cout << message <<endl;
msgQ.enqueue(message);
//instr.dequeue();
} else if(command.find("BST")==0){
    string messagee = msgQ.dequeue();

                if (root == NULL)
                {
                    root = new BSTNode(messagee);
                }
                else
                {
                    root->insert(new BSTNode(messagee));
                }
            }
        }
    }
    if (root != NULL)
    {
        if (line == "Inorder")
        {
            root->inOrder(outputs);
        }
        else if (line == "Preorder")
        {

            root->preOrder(outputs);
        }
        else if (line == "Postorder")
        {
            root->postOrder(outputs);
        }
    }

    cout << outputs;

    ofstream outfile;
    outfile.open(output);
    if (outfile.is_open())
    {
        outfile << output;
    }
    outfile.close();
    delete root;
    
//cout << instr.getFront().find("DECODE");
}