#include <iostream>
#include <fstream>
using namespace std;

struct node{
    string task;
    int val;
    node *next;
};

class PrioQueue{
    private:
    node* front;
    node* end;
    public:
    PrioQueue(){
        front = end = nullptr;
    }

    bool isEmpty(){
        return (front == nullptr);
    }
    string getFront(){
        return front->task;
    }
    void enqueue(string t, int v){
        node *temp =new node;
        temp->task = t;
        temp->val =v;
        temp->next=nullptr;
        if(front == nullptr){
            front = end = temp;
        }else if( temp->val < front->val){
            temp->next = front;
            front = temp;
        }else {
            node *cu = front;
            while(cu-> next != nullptr && temp->val >= cu->next->val){
                cu=cu->next;
            }
            temp->next = cu->next;
            cu->next = temp;
        }
    }
    void dequeue(){
        node * temp= front;
        front = front->next;
        delete temp;
    }
    void print(/*ofstream& ofs*/){
        node *cu=front;
        while(cu!=nullptr){
            //ofs<<cu->task <<endl;
            cout<< cu->task<<endl;
            cu=cu->next;
        }
    }
};
