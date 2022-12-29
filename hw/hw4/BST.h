#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;


class BSTNode {
private:
  BSTNode * left;
  BSTNode * right;
  string data;
public:
  BSTNode(string data){
    left=NULL;
    right=NULL;
    this->data=data;
  }
  void insert(BSTNode * node){
    if(node->data.length()>data.length()){
      //right
      if(right==NULL){
        right=node;
      }else{
        right->insert(node);
      }
      
    }else if(node->data.length()<data.length()){
      //left
      if(left==NULL){
        left=node;
      }else{
        left->insert(node);
      }
    }else{
      this->data=node->data;
      delete node;
    }
  } 
~BSTNode(){
  delete left;
  delete right;
}
void preOrder(string & output){
  //traversal- root left right
  output+=(output==""?"":"\n")+data;
  if(left!=NULL){
    left->preOrder(output);
  }
  if(right!=NULL){

    right->preOrder(output);
  }



}
void inOrder(string & output){
//traversal- left root right
 if(left!=NULL){
    left->inOrder(output);
  }
  output+=(output==""?"":"\n")+data;
  if(right!=NULL){

    right->inOrder(output);
  }

}

void postOrder(string & output){
//traversal- left right root
  if(left!=NULL){
    left->postOrder(output);
  }
  if(right!=NULL){

    right->postOrder(output);
  }
   output+=(output==""?"":"\n")+data;
}


    
};


#endif