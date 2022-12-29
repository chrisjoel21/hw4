#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using namespace std;

struct qNode
{
  string data;
  int priority;
  qNode *next;
};

class Queue
{
protected:
  qNode *front;
  qNode *rear;

public:
  Queue();
  bool isEmpty();
  void enqueue(string);
  string dequeue();
};

Queue::Queue()
{
  front = nullptr;
  rear = nullptr;
}

bool Queue::isEmpty() { return (front == nullptr); }

void Queue::enqueue(string p)
{
  qNode *temp = new qNode();
  temp->data = p;
  temp->next = nullptr;
  if (isEmpty())
  {
    front = temp;
    rear = temp;
  }
  else
  {
    rear->next = temp;
    rear = temp;
  }
}

string Queue::dequeue()
{
  string temp = front->data;
  qNode *del = front;
  front = front->next;
  delete del;
  return temp;
}

class PriorityQueue : public Queue
{
  // low priority Queue
public:
  void enqueue(string p, int priority=0)
  {
    qNode *temp = new qNode();
    temp->data = p;
    temp->priority = priority;
    temp->next = nullptr;
    if (isEmpty())
    {
      front = temp;
      rear = temp;
    }
    else
    {
      qNode *current = front;
      if (current->priority > temp->priority)
      {
        temp->next = front;
        front = temp;
        current = NULL;
      }
        
      while (current != NULL)
      {
        if (current->priority <= temp->priority )
        {
          if(current->next!=NULL){
            
          if(current->next->priority > temp->priority){
          temp->next = current->next;
          current->next = temp;
          break;
          }
          }
          else{
          temp->next = NULL;
          current->next = temp;
          rear=temp;
          break;
          }
        }
        
        current = current->next;
      }
    }
  }
};

#endif