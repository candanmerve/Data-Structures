#include <iostream>	
#include <cstring>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctype.h>
#include <bits/stdc++.h> 
#define N 100 // max array size

#define strnicmp strncasecmp 
using namespace std;

struct Node
{
    char *name;        //  name for BS or MH
    int num1;         //  value to be found or BS value
    int num2;        //  connected value
    Node *child[N]; //  an array of pointers for N children 
    Node *next;    //  to create  linked lists for mobile host
    Node *parent; // to find obtain path from Central Controller to the target MH. 
};

struct Message
{
    char *mes;
    int search;
};

struct Tree
{
    Node *root;
    void create();                                  //  create a root(top of the tree)
    void add_mh(Node *Task4);                      //  connecting MH to BS
    void add_bs(Node *Task3);                     //  creating base stations
    Node *traverse(Node *temp,int num);          //  location to create base stations
    int search(Node *task,int num);             //  to print travesing base station
    int search1(Node *task,int num);           //  to print path mh_[mh]
};

typedef struct Tree tree;
typedef Tree Datastructure; 

Datastructure WorkPlan;

void tree::create()
{
    root=new Node();                //    to create space to root
    root->num1=0;                  //    CC's value always be 0
    root->next=NULL;              //    only for MH
    root->parent=NULL;           //    only for path mh_[MH]
    for(int i=0;i<N;i++)        //    to null child values
    {
        root->child[i]=NULL;
    }
}

Node *tree::traverse(Node *temp,int num)// A utlity function to traverse the constructed N-ary tree 
{
   if(temp->num1==num)
   {
       return temp;
   }
   else
   {
       for(int i=0;i<N;i++) // for 1st generation child
       {
           if(temp->child[i])
           {
               if(temp->child[i]->num1==num)
               {
                   return temp->child[i];
               }
               for(int k=0;k<N;k++) // for 2st generation child
               {
                   if(temp->child[i]->child[k])
                   {
                        if(temp->child[i]->child[k]->num1==num)
                        {
                            return temp->child[i]->child[k];
                        }
                        for(int j=0;j<N;j++) // for 3st generation child
                        {
                            if(temp->child[i]->child[k]->child[j])
                            {
                                if(temp->child[i]->child[k]->child[j]->num1==num)
                                {
                                    return temp->child[i]->child[k]->child[j];
                                }
                                for(int l=0;l<N;l++) // for 4st generation child
                                {
                                    if(temp->child[i]->child[k]->child[j]->child[l])
                                    {
                                        if(temp->child[i]->child[k]->child[j]->child[l]->num1==num)
                                        {
                                            return temp->child[i]->child[k]->child[j]->child[l];
                                        }
                                        for(int y=0;y<N;y++) // for 5st generation child
                                        {
                                            if(temp->child[i]->child[k]->child[j]->child[l]->child[y])
                                            {
                                                if(temp->child[i]->child[k]->child[j]->child[l]->child[y]->num1==num)
                                                {
                                                    return temp->child[i]->child[k]->child[j]->child[l]->child[y];
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                   }
               }
           }
       }
   }
   return temp;
}

void tree::add_bs(Node *Task3) // A utility function to create a new N-ary tree node 
{
    // to retrieve the details of the new point
    Node *node=new Node();
    node->name = new char[strlen(Task3->name)]; 
	strcpy(node->name, Task3->name);           
    node->num1=Task3->num1;
    node->num2=Task3->num2;
    node->next=NULL;
    node->parent=NULL;
    for(int i=0;i<N;i++)
    {
        node->child[i]=NULL;
    }
    Node *cur=new Node();
    cur=traverse(root,node->num2);
    for(int i=0;i<N;i++)
    {
        if(cur->child[i]==NULL)
        {
            cur->child[i]=node;    // to connect base stations
            node->parent=cur;     // only for path mh_[MH]
            return;
        }
    }
}

void tree::add_mh(Node *Task4)
{
    // to retrieve the details of the new point
    Node *node=new Node();
    node->name = new char[strlen(Task4->name)];
	strcpy(node->name, Task4->name);
    node->num1=Task4->num1;
    node->num2=Task4->num2;
    node->next=NULL;
    node->parent=NULL;
    Node *cur=new Node();
    cur=traverse(root,node->num2); // to find the right place
    while(cur->next)
    {
        cur=cur->next; // Progress to null
    }
    cur->next=node; // add to linked list
}

int tree::search(Node *temp,int num)
{
   int go;
   if(temp==NULL)
   {
       return 0;
   }
   else
   {
       cout<<temp->num1<<" "; // to write bs while traversing
       Node *cur=temp;
       while(temp->next)
       {
           if(temp->next->num1==num)
           {
               return 1; // close to recursive
           }
           else
           {
               temp=temp->next;
           }
       }
       for(int i=0;i<N;i++)
       {
           go=search(cur->child[i],num);
           if(go)
           {
               return true; // return function
           }
       }
       if(go!=1)
       {
           return 0; // dont return from the function
       }
   }
   return 0;
}


int tree::search1(Node *temp,int num)
{
   int go;
   if(temp==NULL)
   {
       return 0;
   }
   else
   {
       Node *cur=temp;
       while(temp->next)
       {
           if(temp->next->num1==num)
           {
               int counter=0;
               Node *hold=cur;
               Node *print=new Node;
               print->child[0]=root; // for writing path(mh_)
               while(hold!=root)
               {
                   counter++;
                   hold=hold->parent;
               }
               for(int j=counter;j>0;j--)
               {
                   print->child[j]=cur;
                   cur=cur->parent;
               }
               for(int k=0;k<=counter;k++)
               {
                   cout<<print->child[k]->num1<<" ";// writing element of array for path
               }
               return 1;
           }
           else
           {
               temp=temp->next;
           }
       }
       for(int i=0;i<N;i++)
       {
           go=search1(cur->child[i],num); // to go  recursive 
           if(go)
           {
               return true;
           }
       }
       if(go!=1)
       {
           return 0;
       }
   }
   return 0;
}


int main(int argc, char **argv)
{
    int n=0;
    Node Task;
    Message Task1;
    WorkPlan.create();
    ifstream network(argv[1]);
    ifstream Messages(argv[2]);
    while(network.peek() != EOF)
    {
		string letter,newline;
		getline(network,letter,' '); // bs or mh 
        network >> Task.num1; // firs number
        network >> Task.num2; // second number
		getline(network,newline,'\n'); // for newline 
		char cstr[letter.size() + 1];
		letter.copy(cstr, letter.size() + 1);
		cstr[letter.size()] = '\0';
		for (int i = 0; i < n; i++){
        		cout << cstr[i]; 
        }
        Task.name = cstr;
        if(Task.name[0] == 'M')
        {
            WorkPlan.add_mh(&Task); // if first element of name is M, work on add_mh function
        }
        else
        {
            WorkPlan.add_bs(&Task); // if first element of name is B, work on add_bs function
        }
	}

    while(Messages.peek() != EOF )
    {
		string message,number;
		getline(Messages,message,'>'); // get to message
        Messages >> Task1.search;   // get to number for searching
		getline(Messages,number,'\n');
		char cstr[message.size() + 1];
		message.copy(cstr, message.size() + 1);
		cstr[message.size()] = '\0';
		for (int i = 0; i < n; i++){
        		cout << cstr[i]; 
        }
        Task1.mes = cstr;
        cout<<"Traversing:";
        int ctrl=WorkPlan.search(WorkPlan.root,Task1.search);
        cout<<endl;
        if(ctrl)
        {
            cout<<"Message:"<<Task1.mes<<" To:";
            int ctrl2=WorkPlan.search1(WorkPlan.root,Task1.search);
            if(!ctrl2)
            {
                cout<<"error";
            }
            cout<<"mh_"<<Task1.search;
        }
        else
        {
            cout<<"Can not be reached the mobile host ";
             cout<<"mh_"<<Task1.search<<" at the moment";
        }
        cout<<endl;
	}
	Messages.close(); // close file
	network.close(); // close file
	return 0;
}















