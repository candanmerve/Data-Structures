/* @Author
 Student Name: <Merve_Candan>
 Student ID: <150160041>
 Date: <16.10.2019> */

#include <iostream>
#include <fstream>

using namespace std;

struct node{
    int size;
    int quant;
    node *next;
};
struct stock{
    node *head;
    void create();
    void add_stock(int);
    void sell(int);
    void current_stock();
    void clear();
};

void stock::create()
{
    head = NULL;
}
void stock::add_stock(int x)
{
    node *temp = head;			// Create temp pointer and assigned it to head for initial node.
    node *temp2 = new node;		// Create new node which temp2 pointer is point that node.
    temp2->size = x;
    temp2->quant = 0;			// First node's quant is 0. Because there is no shoe for now.
    temp2->next = NULL;			// First and only node, thus temp2's next is NULL. 
    
    if(head == NULL)
	{
        temp2->quant+=1;		// If head equals NULL, that means there is no node, then temp2 comes and it's quant iis increased by 1.
        head = temp2;				// There is only one node and it's size is x (defined above), thus head pointer equals temp2 pointer
    }
    else
    {
		while(temp)
        {
            if(temp2->size == temp->size)		// The coming shoe number is already in the stock at least one,
            {										//just increment the quantity.
                temp->quant += 1;
                break;
            }
            else if(temp->next == NULL) 		// The coming shoe number is the greatest number compared to the others.
            {
            	temp->next = temp2;				// Then the created new node temp2 is the last node.
                temp2->quant += 1;				// Then the new shoe's quantity is increased by 1.
                break;
            }
            else if(temp2->size < temp->size)	// If the new node's size the smallest number compared to the others.
			{
            	temp2->next = temp;				// Temp2's next is assigned to temp
            	temp2->quant += 1;				// The new shoe's quantity is increased by
            	head = temp2;						// head pointer is the temp2 pointer anymore.
            	break;
            }
            else if(temp2->size < temp->next->size && temp->next != NULL) // If the new node's size smaller than the last node and 
            {																// greater than the first node			
                temp2->next = temp->next;
                temp->next = temp2;
                temp2->quant += 1;
            	break;
            }
            else
            {
				temp = temp->next;
            }
        }
    }
}

void stock::sell(int x)
{
    node *control = head;			// Control pointer assigned to head pointer
    node *control2 = new node;		// Control2 pointer assigned to the new node. New node created.
    control2->next = control;			// Control2's next equals control.
    if(control == NULL)
	{
        cout << "NO_STOCK"<<endl;	// If there is not any node, there is no stock.
    }
    else if(control->next == NULL)	// If control's next equals NULL. That means there is one node.
    {
        head = NULL;					// That shoe number is selling thus head pointer equals NULL
        delete control;				// That node is delete. Free space.
    }
        else
		{
        	while(control->next != NULL)	// More than one nodes
        	{
            	if(control->size == -x)		// -x writed beacuse wanted shoe numbers given as negative numbers.
            	{
                	if(control->quant > 1)	// If that size have more than one quantity
                	{
                    	control->quant -= 1;	// Quantity decreased by 1.
                    	break;
                	}
                	else if(control->quant == 1 && control == head)	// If the quantity of the wanted shoe number is one and there is only one node
                	{												// First node
                    	head = control->next;		// Head pointer is assigned to control's next. The shoe sold.
                    	delete control;			// Delete control. Free space.
                    	break;
	                }
	                else if(control->quant == 1 && control != head)	// If the quantity of the wanted shoe number is one.
	                {												// More than one nodes.
	                    control2->next = control->next;				// Control2's next assigned to control's next for don't lose the element(s) after control.
	                    delete control;								// Delete control
	                    break;
	                }
	            }
	            control2 = control;
	            control = control->next;
	        }
        if(control->next == NULL)
		{
            if(control->size == -x)
            {
                if(control->quant > 1)
                {
                    control->quant -= 1;			// If there is more than 1 quantity of the wanted shoe size, decreased quantity by 1.
                }
                else
                {
                    control2->next = NULL;
                    delete control;
                }
            }
            else{  cout << "NO_STOCK" << endl; } 
        }
    }
}
void stock::current_stock()
{
    node *control = head;
    while(control != NULL)
	{
        cout << control->size << ":" << control->quant <<endl;
        control = control->next;
    }
}
void stock::clear()
{
    node* iter = head;
    while(head != NULL)
    {
        iter = head->next;
        delete head;
        head = iter;
    }
}

int main(int argc, char *argv[])
{
    int num;
    struct stock shop;
    ifstream input(argv[1]);
    shop.create();
    while (input >> num){
        if (num == 0){
            shop.current_stock();
        }
        if(num > 0){
            shop.add_stock(num);
        }
        if(num < 0){
            shop.sell(num);
        }
    }
    input.close();
    shop.clear();
}
