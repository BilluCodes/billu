#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
using namespace std;
#include <cassert>

template <typename T>
struct Node
{
	T element;
	Node* next;
};

template <typename T>
class LinkedList
{
private:
	Node<T>* mergeSort(Node<T>*);
	void breakList(Node<T>*, Node<T>* &, Node<T>* &);
	Node<T>* mergeLists(Node<T>*, Node<T>*);

	Node<T> *head;


public:
	class Iterator;
	LinkedList();
	void insertAtStart(T const element);
	void insertAtEnd(T const element);
	void deleteAtStart();
	void deleteAtEnd();
	void print() const;
	bool search(T const element) const;
	void reverse();
	void deleteAllOccurancesOf(T const element);
	void sort();
	void sortedInsert(T const element);
	Iterator begin() const;
	Iterator end() const;
	~LinkedList();


};

template <typename T>
class LinkedList<T>::Iterator
{
private:
	Node<T> *curr;
	friend class LinkedList<T>;
public:
	Iterator()
	{
		curr = nullptr;
	}

	Iterator(LinkedList<T>::Iterator const& that)
	{

		this->curr = that.curr;
	}

	Iterator(LinkedList<T> const& list)
	{
		curr = list.head;
	}

	T& operator*()
	{
		assert(this->curr != nullptr);
		return this->curr->element;
	}

	bool operator!=(LinkedList<T>::Iterator that)const
	{
		return (this->curr != that.curr);

	}
	bool operator==(Iterator const& that) const
	{
		return (this->curr == that.curr);
	}

	Iterator& operator++()
	{
		assert(this->curr != nullptr);

		this->curr = curr->next;
		return *this;

	}
	LinkedList<T>::Iterator operator++(int)
	{
		assert(this->curr != nullptr);
		Iterator newIterator(*this);

		this->curr = curr->next;
		return newIterator;
	}
};


template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() const
{
	LinkedList<T>::Iterator it(*this);
	return it;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() const
{
	Iterator it;
	it.curr = nullptr;
	return it;

}

template <typename T>
LinkedList<T>::LinkedList()
{
	this->head = nullptr;
}

template <typename T>
void LinkedList<T>::insertAtStart(T const element)
{
	//case 1: head is empty;
	if (this->head == nullptr)
	{
		this->head = new Node<T>();
		this->head->element = element;
		this->head->next = nullptr;
		return;
	}

	Node<T> *newHead = new Node<T>();
	newHead->element = element;
	newHead->next = this->head;
	this->head = newHead;
	return;
}

template <typename T>
void LinkedList<T>::insertAtEnd(T const element)
{
	//case 1: head is empty;
	if (this->head == nullptr)
	{
		this->head = new Node<T>();
		this->head->element = element;
		this->head->next = nullptr;
		return;
	}

	Node<T> *curr = this->head;
	while (curr->next != nullptr)
		curr = curr->next;

	//create new node
	Node<T> *newTailNode = new Node<T>;
	newTailNode->element = element;
	newTailNode->next = nullptr;
	curr->next = newTailNode;
}

template <typename T>
void LinkedList<T>::print() const
{
	Node<T> *curr = this->head;
	while (curr != nullptr)
	{
		cout << curr->element << endl;
		curr = curr->next;
	}

}

template <typename T>
bool LinkedList<T>::search(T const element) const
{
	Node<T> *curr = this->head;
	while (curr != nullptr)
	{
		if (curr->element == element)
			return true;
		curr = curr->next;
	}

	return false;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	Node<T> *curr = this->head;
	while (curr != nullptr)
	{
		Node<T> *deleteNode = curr;
		curr = curr->next;
		delete deleteNode;
	}

}

template <typename T>
void LinkedList<T>::deleteAllOccurancesOf(T const element)
{
	Node<T> *ptr = this->head;
	Node<T> *prv = nullptr;
	Node<T> *temp;
	while (ptr != nullptr)
	{
		if (ptr->element == element)
		{

			if (prv == nullptr)
			{
				temp = ptr->next;
				delete ptr;
				ptr = temp;
				prv = nullptr;
			}

			else
			{
				temp = ptr->next;
				delete ptr;
				ptr = temp;
				prv->next = ptr;
			}
		}

		else
		{
			prv = ptr;
			ptr = ptr->next;
		}
	}
}


template <typename T>
void LinkedList<T>::deleteAtEnd()
{
	//there is no element in the list
	if (this->head == nullptr)
		return;

	Node<T>* curr = this->head;

	//there is only one element in the list
	if (curr->next == nullptr)
	{
		delete this->head;
		this->head = nullptr;
		return;
	}

	while (curr->next->next != nullptr)
	{
		curr = curr->next;
	}

	Node<T> *deleteNode = curr->next;
	curr->next = nullptr;
	delete deleteNode;
}


template <typename T>
void LinkedList<T>::deleteAtStart()
{
	if (this->head == nullptr)
		return;

	Node<T> *deleteNode = this->head;
	this->head = this->head->next;
	delete deleteNode;
}

template <typename T>
void LinkedList<T>::reverse()
{
	if (this->head == nullptr)
		return;

	Node<T> *curr = this->head,
		*prev = nullptr,
		*next = curr->next;

	while (next != nullptr)
	{
		curr->next = prev;
		prev = curr;
		curr = next;
		next = curr->next;
	}

	this->head = curr;
	this->head->next = prev;

}

template <typename T>
void LinkedList<T>::sort()
{
	this->head = this->mergeSort(this->head);


}

template <typename T>
Node<T>* LinkedList<T>::mergeSort(Node<T>* node)
{
	if (node == nullptr)
		return nullptr;
	else if (node->next == nullptr)
		return node;

	Node<T>* firstHalf;
	Node<T>* secondHalf;

	breakList(node, firstHalf, secondHalf);
	Node<T>* firstHalfSorted = mergeSort(firstHalf);
	Node<T>* secondHalfSorted = mergeSort(secondHalf);

	return mergeLists(firstHalfSorted, secondHalfSorted);
}

template <typename T>
void LinkedList<T>::breakList(Node<T>* list, Node<T>* & firstHalf, Node<T>* & secondHalf)
{

	Node<T>*  firstPointer = list;
	Node<T>* secondPointer = list;
	Node<T>* prevToFirstPointer = nullptr;
	while (secondPointer != nullptr)
	{
		prevToFirstPointer = firstPointer;
		firstPointer = firstPointer->next;
		secondPointer = secondPointer->next;

		if (secondPointer != nullptr)
			secondPointer = secondPointer->next;
	}

	firstHalf = list;
	secondHalf = firstPointer;
	prevToFirstPointer->next = nullptr;

}


template <typename T>
Node<T>* LinkedList<T>::mergeLists(Node<T>* firstHalfSorted, Node<T>* secondHalfSorted)
{
	Node<T> *curr = nullptr;
	Node<T>*list;
	if (firstHalfSorted->element <= secondHalfSorted->element)
	{
		curr = firstHalfSorted;
		firstHalfSorted = firstHalfSorted->next;
	}
	else
	{
		curr = secondHalfSorted;
		secondHalfSorted = secondHalfSorted->next;

	}

	list = curr;
	while (firstHalfSorted != nullptr && secondHalfSorted != nullptr)
	{
		if (firstHalfSorted->element <= secondHalfSorted->element)
		{
			curr->next = firstHalfSorted;
			firstHalfSorted = firstHalfSorted->next;
			curr = curr->next;
		}
		else
		{
			curr->next = secondHalfSorted;
			secondHalfSorted = secondHalfSorted->next;
			curr = curr->next;
		}

	}

	if (firstHalfSorted == nullptr)
	{
		curr->next = secondHalfSorted;
	}
	else curr->next = firstHalfSorted;

	return list;
}

template <typename T>
void LinkedList<T>::sortedInsert(T const element)
{
	Node<T>*curr = this->head;
	Node<T>*prev = nullptr;

	while (curr != nullptr)
	{
		if (curr->element < element)
		{
			prev = curr;
			curr = curr->next;

		}
		else break;
	}

	Node<T>*newNode = new Node<T>();
	newNode->element = element;
	newNode->next = curr;

	//if the new element is to be inserted at head
	if (prev == nullptr)
	{
		this->head = newNode;
		return;
	}

	prev->next = newNode;
}



#endif

template<typename k,typename v>
class HeapItem
{
public:
    k key;
    v value;
};
template<typename k,typename v>
class Heap
{
    HeapItem<k,v> *h;
    int capacity;
    int totalItems;
public:
    Heap()
    {
        h=nullptr;
        capacity=0;
        totalItems=0;
    }
    Heap(int s)
    {
        capacity=s;
        h=new HeapItem<k,v>[capacity];
        totalItems=0;
    }
    void Insert(k key,v value)
    {
        if(totalItems==capacity)
        {
            int i;
            HeapItem<k,v> *t=h;
            capacity=capacity*2;
            h=new HeapItem<k,v>[capacity];
            for(i=0;capacity/2;i++)
            {
                h[i]=t[i];
            }
        }
        if(totalItems<capacity)
        {
            totalItems++;
            h[totalItems].key=key;
            h[totalItems].value=value;
            int i=totalItems;
            while(i>1 && h[i].key>h[i/2].key)
            {
                swap(h[i],h[i/2]);
                i=i/2;
            }
        }
    }
    void setCapacity(int _capacity)
    {
        capacity=_capacity;
        h=new HeapItem<k,v>[capacity];
    }
    void Heapify(int i)
    {
        int max=i;
        if(2*i<=totalItems && h[2*i].key>h[max].key)
        {
            max=2*i;
        }
        if(2*i+1<=totalItems && h[2*i+1].key>h[max].key)
        {
            max=2*i+1;
        }
        if(max!=i)
        {
            swap(h[i], h[max]);
            Heapify(max);
        }
    }
    //Removes Max
    HeapItem<k,v> Remove()
    {
        
        HeapItem<k,v>m=h[1];
        swap(h[1], h[totalItems]);
        totalItems--;
        Heapify(1);
        return m;
    }
    void getMax(v& _value)
    {
        if(totalItems>0)
            _value=h[1].value;
        else
             cout<<"Heap is Empty!!!!!\n";
    }
    bool isEmpty()
    {
        if(totalItems==0)
            return false;
        else
            return true;
    }
    void BuiltHeap(int *a,int n)
    {
        int i=0;
        for(i=0;i<n;i++)
            h[i+1]=a[i];
        
        hsize=n;
        
        for(i=n/2;i>=1;i++)
            Heapify(i);
        
        i=n;
        while(i>1)
        {
            swap(h[i],h[hsize]);
            hsize--;
            Heapify(1);
            i--;
        }
    }
    void BuiltHeapandSort(int *a,int n)
       {
           int i=0;
           for(i=0;i<n;i++)
               h[i+1]=a[i];
           
           hsize=n;
           
           for(i=n/2;i>=1;i++)
               Heapify(i);
           
           i=n;
           while(i>1)
           {
               swap(h[i],h[hsize]);
               hsize--;
               Heapify(1);
               i--;
           }
           for(i=0;i<n;i++)
               a[i]=h[i+1];
       }
    void HeapSort(int *arr,int n)
    {
        Heap H(n+1);
        H.BuiltHeap(arr,n);
    }
    void Print()
    {
        for(int i=1;i<=totalItems;i++)
        {
            cout<<h[i].key<<"\t"<<h[i].value<<"\n";
        }
        cout<<endl;
    }
    ~Heap()
    {
        if(h!=nullptr)
        {
            delete[]h;
        }
    }
};

template <class T>
class Stack
{
    Node<T> *s;
public:
    Stack()
    {
        s=nullptr;
    }
    void initializeStack()
    {
        Node<T> *t;
        while(s!=nullptr)
        {
            t=s;
            s=s->next;
            delete t;
        }
    }
    void Push(const T &d)
    {
        Node<T> *n=new Node<T>;
        n->data=d;
        n->next=s;
        s=n;
       // cout<<d<<"\t is Pushed.\n";
    }
    bool isFull()const
    {
        return false;
    }
    bool isEmpty()const
    {
        return (s==nullptr);
    }
    void Pop()
    {
        Node<T> *n=new Node<T>;
        //cout<<s->data<<"\t is Popped.\n";
        if(s!=nullptr)
        {
            n=s;
            s=s->next;
            delete n;
        }
        else
            cout<<"s is Empty.\n";
    }
    T Top()
    {
        //cout<<"Top :\t";
          if(s!=nullptr)
              return s->data;
        else
            return 0;
    }
    ~Stack()
    {
        initializeStack();
    }
};

class Helper
{
public:
    static char* GetStringFromBuffer(const char *s)
    {
        long l=strlen(s)+1;
        char *str=new char [l];
        strcpy(str,s);
        return str;
    }
};
template <class T>
class Queue
{
    T *q;
    int front;
    int end;
    int maxSize, size;
public:
    Queue(int size)
    {
        maxSize=size;
        q=new T [size];
        front=0;
        end=-1;
    }
    void Enqueue(const T &d)
    {
        if(!isFull())
        {
            if(end==maxSize)
                end=0;
            end++;
            q[end]=d;
            size++;
            cout<<"Enqueued \n";
        }
    }
    void Dequeue()
    {
        if(!isEmpty())
        {
            T d;
            d=q[front];
            size--;
            if(front==maxSize)
            {
                front=0;
            }
            front++;
            cout<<"Dequeued \n";
        }
    }
    T  Front()
    {
        if(!isEmpty())
        {
            T d;
            d=q[front];
            return d;
        }
        else if(isEmpty())
        {
            cout<<"Nothing in Queue \n";
            return 0;
        }
    }
    bool isFull()
    {
        return (size==maxSize);
    }
    bool isEmpty()
    {
        return size=0;
    }
};

template <class T>
class SortedStacklessBST
{
    Node<T>* root;
    bool isSuccessor;
    
    //Functions
    
    
    //Use Method of listing in Insert and Removal to set nextInOrder
    //Insert Function
    void Insert(T d,Node<T> *& R)
    {
        //Making new node
        Node<T> *buffer=new Node<T>;
        buffer->data=d;
        buffer->left=buffer->right=buffer->nextInOrder=nullptr;
        Node<T> *tail=getmax(root);
        Node<T> *head=getMin(root);
        if(R==nullptr)
        {
            R=buffer;
            tail=R;
            head=R;
        }
        else
        {
            Node<T> *temp=nullptr;
            Node<T> *cur=R;
            
            //Finding destination node
            while(cur!=nullptr)
            {
                temp=cur;
                if(d>=cur->data)
                    cur=cur->right;
                else
                    cur=cur->left;
            }
            
            //Puts buffer on a specific node
            if(d>=temp->data)
            {
                temp->right=buffer;
            }
            else
            {
                temp->left=buffer;
            }
            
            //Sets Position of Node nextInOrder
            if(buffer->data>=tail->data)
            {
                tail=buffer;
                tail->nextInOrder=nullptr;
                temp->nextInOrder=buffer;
            }
            else if(buffer->data<=head->data)
            {
                head=buffer;
                buffer->nextInOrder=temp;
            }
            else
            {
                //Gets Previous node and sets node inbetween two nodes
                Node<T> *bi2=head;
                while(bi2->nextInOrder!=nullptr)
                           {
                               if(buffer->data>=bi2->data && buffer->data<=bi2->nextInOrder->data)
                               {
                                   break;
                               }
                               else
                                   bi2=bi2->nextInOrder;
                           }
                           Node<T> *temp1=bi2->nextInOrder;
                           bi2->nextInOrder=buffer;
                           buffer->nextInOrder=temp1;
                }
        }
    }
    
    //Function to Find minimum and maximum
    Node<T>* getmax(Node<T>*& r)
    {
        Node<T>* temp = r;
        if(temp==nullptr)
            return nullptr;
        else if(temp->right==nullptr)
            return temp;
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp;
    }
    Node<T>* getMin(Node<T> *&node)
    {
    Node<T>* current = node;
        if(current==nullptr)
            return nullptr;
        else if(current->left==nullptr)
            return current;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
    }
    
    //Removal Function
    bool Remove(T d, Node<T>*& r)
    {
        Node<T> *head=getMin(root);
        Node<T> *tail=getmax(root);
        if (r == nullptr)
        {
            return false;
        }
        if (d < r->data)
        {
            return Remove(d, r->left);
        }
        else if (d > r->data)
        {
            return Remove(d, r->right);
        }
        else
        {
            if (r->left == nullptr && r->right == nullptr)
            {
                if(d==head->data)
                {
                    head=head->nextInOrder;
                }
                else if(d==tail->data)
                {
                    //Gets the previous to last node and sets its nextInOrder as nullptr
                    Node<T> *bi2=head;
                       while(bi2->nextInOrder!=nullptr)
                                  {
                                      if(d>=bi2->data && d<=bi2->nextInOrder->data)
                                      {
                                          break;
                                      }
                                      else
                                          bi2=bi2->nextInOrder;
                                  }
                    bi2->nextInOrder=nullptr;
                }
                else
                {
                    //Gets the inbetweens nodes previous and links it to the next of inbetween
                    Node<T> *bi2=head;
                    while(bi2->nextInOrder!=nullptr)
                               {
                                   if(d>=bi2->data && d<=bi2->nextInOrder->data)
                                   {
                                       break;
                                   }
                                   else
                                       bi2=bi2->nextInOrder;
                               }
                    bi2->nextInOrder=r->nextInOrder;
                }
                delete r;
                r = nullptr;
            }
            else if (r->left != nullptr && r->right != nullptr)
            {
                r= getmax(r->left);
                Remove(r->data, r->left);
            }
            else
            {
                Node<T>* temp;
                if (r->left != nullptr)
                    temp = r->left;
                else
                    temp = r->right;
                    if(d==head->data)
                    {
                        head=head->nextInOrder;
                    }
                    else if(d==tail->data)
                    {
                        //Gets the previous to last node and sets its nextInOrder as nullptr
                        Node<T> *bi2=head;
                           while(bi2->nextInOrder!=nullptr)
                                      {
                                          if(d>=bi2->data && d<=bi2->nextInOrder->data)
                                          {
                                              break;
                                          }
                                          else
                                              bi2=bi2->nextInOrder;
                                      }
                        bi2->nextInOrder=nullptr;
                    }
                    else
                    {
                        //Gets the inbetweens nodes previous and links it to the next of inbetween
                        Node<T> *bi2=head;
                        while(bi2->nextInOrder!=nullptr)
                               {
                                   if(d>=bi2->data && d<=bi2->nextInOrder->data)
                                   {
                                       break;
                                   }
                                   else
                                       bi2=bi2->nextInOrder;
                               }
                        bi2->nextInOrder=r->nextInOrder;
                    }
                    delete r;
                    r = temp;
            }
        }
        return false;
    }
    
    //Print using isSuccessor
    void Print(Node<T> * root)
    {
        Node<T> *temp;
        if (root)
            {
                if(isSuccessor==true)
                    temp=getMin(root);
                else
                    temp=getmax(root);
                while(temp!=nullptr)
                    {
                        cout<<temp->data<<"\t";
                        temp=temp->nextInOrder;
                    }
                cout<<endl;
            }
    }
    //Changes position of nextinOrder
    Node<T>* ReverseOrder(Node<T> *&r)
    {
        if(r==nullptr)
            return nullptr;
        if(r->nextInOrder==nullptr)
        {
            return r;
        }
        Node<T> *temp=ReverseOrder(r->nextInOrder);
        temp->nextInOrder=r;
        r->nextInOrder=nullptr;
        return r;
    }
    
    //Make a deep copy of Data
    Node<T>* deepcopy(const Node<T>* n)
       {
           if (n == nullptr)
           {
               return nullptr;
           }
           else
           {
               Node<T>* temp = new Node<T>;
               temp->data = n->data;
               temp->nextInOrder=n->nextInOrder;
               temp->left = deepcopy(n->left);
               temp->right = deepcopy(n->right);
               return temp;
           }
       }
    
public:
   
    //Constructor
    SortedStacklessBST()
    {
        root=nullptr;
        isSuccessor=true;
    }
    //Copy Constructor
    SortedStacklessBST(const SortedStacklessBST& rhs)
    {
        isSuccessor=true;
        root = deepcopy(rhs.root);
    }
    //Assignment Operator
    SortedStacklessBST& operator=(const SortedStacklessBST& rhs)
    {
        //isSuccessor=true;
        root =  deepcopy(rhs.root);
        return *this;
    }
    
    //Insert Wrapper function
    bool Insert(T d)
    {
        if(Search(d)==true)
            return false;
        else
            Insert(d,root);
            return true;
    }
    
    //Removal Wrapper Function
    bool Remove(T d)
    {
        if(Search(d)==true)
        {
            Remove(d, root);
            return true;
        }
        else if(root==nullptr)
            return false;
        else
            return false;
    }
    
    //Search Function
    bool Search(T d)
    {
        Node<T> *cur=root;
        
        //Finding node
        while(cur!=nullptr)
            {
                if(cur->data==d)
                    {
                        //if Found return true
                        return true;
                        break;
                    }
                    else if(d>=cur->data)
                            cur=cur->right;
                        else
                            cur=cur->left;
            }
        return false;
    }
    Node<T> *SearchnextInOrder(T d)
    {
        Node<T> *cur;
        if(isSuccessor==true)
            cur=getMin(root);
        else
            cur=getmax(root);
        while(cur!=nullptr)
        {
            if(cur->data==d)
            {
                return cur;
                break;
            }
            else
                cur=cur->nextInOrder;
        }
            return nullptr;
    }
    //To count number of Leaf nodes
    T GetCountofLeafNodes(Node<T> *root)
    {
       if(root==nullptr)
           return 0;
        if(root->left==nullptr && root->right==nullptr)
            return 1;
        else
            return GetCountofLeafNodes(root->left)+GetCountofLeafNodes(root->right);
    }
    T GetMax(T a,T b)
    {
        if(a>b)
            return a;
        else
            return b;
    }
    //To get height of BST
    T GetHeight(Node<T> *root)
    {
        static int leftLength=0;
        static int rightLength=0;
        if(root==nullptr)
            return 0;
        else
        {
            leftLength=GetHeight(root->left);
            rightLength=GetHeight(root->right);
        }
        return 1+GetMax(leftLength,rightLength);
    }
    //Function to check if the tree is Balanced
    bool IsLeafBalance()
    {
        int leafCount=GetCountofLeafNodes(root);
        int height=GetHeight(root)-1;
        if(leafCount==(2^height))
            return true;
        else
            return false;
    }
    
    //Reverse Wrapper Function
    void ReverseOrder()
    {
        //Sets Value of isSuccessor
        if(isSuccessor==true)
        {
            isSuccessor=false;
            Node<T> *r=getMin(root);
            ReverseOrder(r);
        }
        else
        {
            isSuccessor=true;
            Node<T> *r=getmax(root);
            ReverseOrder(r);
        }
    }
    
    //Print Wrapper Function
    void Print()
    {
        if(isSuccessor==true)
        {
            Print(root);
        }
        else
        {
            Print(root);
        }
    }
    
    //Print from a Specific Position
    void Print(T low,T high)
    {
        Node<T> *temp;
           if (root)
               {
                   if(isSuccessor==true)
                   {
                       temp=SearchnextInOrder(low);
                       Node<T> *h=SearchnextInOrder(high);
                        while(temp!=h->nextInOrder)
                            {
                                cout<<temp->data<<"\t";
                                temp=temp->nextInOrder;
                            }
                        cout<<endl;
                   }
                   else
                   {
                       temp=SearchnextInOrder(high);
                       Node<T> *l=SearchnextInOrder(low);
                       while(temp!=l->nextInOrder)
                           {
                               cout<<temp->data<<"\t";
                               temp=temp->nextInOrder;
                           }
                       cout<<endl;
                   }
               }
    }
    //Destructor
    ~SortedStacklessBST()
    {
        Node<T> *temp;
        Node<T> *buffer=root;
          while(buffer != nullptr) {
              if (buffer->left == nullptr)
              {
                  temp = buffer->right;
                  delete buffer;
              }
              else
              {
                  temp = buffer->left;
                  buffer->left = temp->right;
                  temp->right = buffer;
              }
              buffer=temp;
          }
//        Node<T> *temp=getMin(root);
//        while(temp!=nullptr)
//        {
//            delete temp;
//            temp=temp->nextInOrder;
//        }
    }
};

template<class T>
class BST
{
    Bnode<T>* root;
public:
    BST()
    {
        root = nullptr;
    }
    void insert(T d)
    {
        insert(d, root);
    }
    void insert(T d, Bnode<T>*& r)
    {
        if (r == nullptr)
        {
            Bnode<T>* temp = new Bnode<T>;
            temp->data = d;
            temp->left = temp->right = nullptr;
            r = temp;
        }
        if (d == r->data)
        {
            return;
        }
        if (d < r->data)
            insert(d, r->left);
        else
            insert(d, r->right);
    }
    void Printsorted()
    {
        printsorted(root);
    }
    void printsorted(Bnode<T>* r)
    {
        if (r)
        {
            printsorted(r->left);
            cout << r->data << endl;
            printsorted(r->right);
        }
    }
    bool remove(T& d)
    {
        return remove(d, root);
    }
    bool remove(T& d, Bnode<T>*& r)
    {
        if (r == nullptr)
        {
            return false;
        }
        if (d < r->data)
        {
            return remove(d, r->left);
        }
        else if (d > r->data)
        {
            return remove(d, r->right);
        }
        else if (r->left == r->right == nullptr)
        {
            delete r;
            r = nullptr;
        }
        if (r->left != nullptr && r->right != nullptr)
        {
            r->data = getmax(r->left);
            remove(r->data, r->left);
        }
        else
        {
            Bnode<T>* temp;
            if (r->left != nullptr)
                temp = r->left;
            else
            {
                temp = r->right;
                delete r;
                r = temp;
            }
        }
    }
    int geth(Bnode<T>* p)
    {
        if (p != nullptr)
            return p->height;
        else
            return -1;
    }
    void rotateleft(Bnode<T>*& x)
    {
        Bnode<T>* y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = 1 + max(geth(x->left), geth(x->right));
        y->height = 1 + max(geth(y->left), geth(y->right));
        x = y;
    }
    void rotateright(Bnode<T>*& x)
    {
        Bnode<T>* y = x->left;
        x->left = y->right;
        y->right = x;
        x->height = 1 + max(geth(x->left), geth(x->right));
        y->height = 1 + max(geth(y->left), geth(y->right));
        x = y;
    }
    void doublerotateleft(Bnode<T>*& x)
    {
        rotateright(x->right);
        rotateleft(x);
    }
    void doublerotateright(Bnode<T>*& x)
    {
        rotateleft(x->left);
        rotateright(x);
    }
    /*void insert(T d)
    {
        insert(d, root);
    }
    void insert(T d, Bnode<T>*& r)
    {
        if (r == nullptr)
        {
            r = new Bnode<T>;
            r->data = d;
            r->left = r->right = nullptr;
            r->height = 0;
            return;
        }
        if (r->data == d)
        {
            return;
        }
        if (r->data > d)
        {
            insert(d, r->left);
            if (geth(r->left) - geth(r->right) == 2)
            {
                if (d < r->left->data)
                    rotateright(r);
                else
                    doublerotateright(r);
            }
        }
        else
        {
            insert(d, r->right);
            if (geth(r->left) - geth(r->right) == -2)
            {

            }
            r->height = 1 + max(geth(r->left), geth(r->right));
        }
    }*/
    void destroy(Bnode<T>* r)
    {
        if (r)
        {
            destroy(r->left);
            destroy(r->right);
            delete r;
        }
    }
    ~BST()
    {
        destroy(root);
    }
};


