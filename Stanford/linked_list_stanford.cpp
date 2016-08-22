#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node* next;
};

// A simple push function that inserts the new value at the beginning of the list.
void Push(node*& head, int value)
{
    struct node* temp = new node();

    temp->data = value;
    temp->next = head;
    head = temp; 
}

// Utility function to print all values of the list.
void printList(node* head)
{
    while (head != NULL)
    {
        cout << head->data << " " ;
        head = head->next;
    }
    cout << endl;
}

// A utility function to create a linked list with 3 nodes.
void build123()
{
    struct node* head = new node();

    // Crate an empty list to start with
    head = NULL;

    Push(head, 1);
    Push(head, 2);
    Push(head, 3);
}

// Q1: Finding length of the linked list.
// P1. Don't use head pointer to traverse the list as head should always point to the First Entry
// P2: Function argument can just be "node* head" instead of "struct node* head"
// http://stackoverflow.com/questions/6526225/struct-keyword-in-function-parameter-and-const-correctness
// http://stackoverflow.com/questions/1675351/typedef-struct-vs-struct-definitions
unsigned int getLength(node* head)
{
    unsigned int length = 0;

    while (head != NULL)
    {
        length++;
        head = head->next;
    }

    return length;
}

// Q2: 
int getNth(node* head, int index)
{
    int temp = 0;
    struct node* tmpHead = head;

    // the given index is not valid
    if (index < 0)
    {
        return -1;
    }

    while (tmpHead != NULL)
    {
        if (temp == index)
        {
            return tmpHead->data;
        }
        tmpHead = tmpHead->next;
        temp++;
    }

    return -1;
}

// Q3: Delete the complete list
void deleteList(node*& headRef)
{
    struct node* temp;

    while (headRef != NULL)
    {
        temp = headRef->next;
        delete headRef;
        headRef = temp;
    }

    // Safety check to make sure headRef is NULL
    headRef = NULL;
}

// Q4. Pop function
int pop(node*& head)
{
    struct node*  temp;
    int data;

    // Fail if the passed in head is not valid
    if (head == NULL)
    {
        return -1;
    }

    data = head->data;
    temp = head->next;

    delete head;
    head = temp;

    return data;
}

// Q5. InsertNth to insert at any place
void insertNth(struct node*& head, unsigned int index, int value)
{
    unsigned int tmpCount = 0;
    struct node* tmpNewNode = new node();
    struct node* tmpHead = head;

    // Proceed only if the index is valid
    if (index <= getLength(head))
    {
        tmpNewNode->data = value;
        tmpNewNode->next = NULL;

        //if (head == NULL)
        if (index == 0)
        {
            tmpNewNode->next = head;
            head = tmpNewNode;
            return;
        }

        while (tmpCount < index-1)
        {
            tmpHead = tmpHead->next;
            tmpCount++;
        }

        tmpNewNode->next = tmpHead->next;
        tmpHead->next = tmpNewNode;
    }
}

// Q5b. InsertNth to insert at any place using Push
/*
void insertNth(struct node*& head, unsigned int index, int value)
{
    unsigned int tmpCount = 0;
    struct node* tmpNewNode = new node();
    struct node* tmpHead = head;

    // Proceed only if the index is valid
    if (index <= getLength(head))
    {
        tmpNewNode->data = value;
        tmpNewNode->next = NULL;

        //if (head == NULL)
        if (index == 0)
        {
            Push(head, value);
            return;
        }

        while (tmpCount < index-1)
        {
            tmpHead = tmpHead->next;
            tmpCount++;
        }

        tmpNewNode->next = tmpHead->next;
        tmpHead->next = tmpNewNode;
    }
}
*/

// Q6:
void sortedInsert(node*& headRef, node* node)
{
    struct node* tmpHead = headRef;

    // This can be combined with the next IF block
/*
    if (tmpHead == NULL)
    {
        // Node should be inserted at Head.
        node->next = tmpHead;
        tmpHead = node;
        return;
    }
    // Insert node at the front of the list
    // IMP: This is WRONG. We should instead use the HeadRef itself
    if (tmpHead == NULL || tmpHead->data > node->data)
    {
        node->next = tmpHead;
        tmpHead = node;
        return;
    }
*/

    if (headRef == NULL || headRef->data > node->data)
    {
        node->next = headRef;
        headRef = node;
        return;
    }

    while (tmpHead->next != NULL)
    {
        if (tmpHead->next->data < node->data)
        {
            tmpHead = tmpHead->next;
        }
        else
        {
            break;
        }
    }

    node->next = tmpHead->next;
    tmpHead->next = node;
}

// Q7:
void insertionSort(node*& headRef)
{
    node* tmpHead = headRef;
    //node* result = new node();
    //result = NULL;
    struct node* result = NULL;
    struct node* next;

    while (tmpHead != NULL)
    {
        next = tmpHead->next;
        sortedInsert(result, tmpHead);
        tmpHead = next;
    }

    headRef = result;
}

//  Q8:
void appendLists(node*& list1, node*& list2)
{
    if (list1 == NULL)
    {
        list1 = list2;
        list2 = NULL;
    }
    else
    {
        struct node* tmpList1 = list1;
        while (tmpList1 -> next != NULL)
        {
            tmpList1 = tmpList1->next;
        }
        tmpList1->next = list2;
        list2 = NULL;
    }
}

// Q9:
void frontBackSplit(node* original, node*& frontList, node*& backList)
{
    unsigned int count = 0;
    unsigned int half = (getLength(original) / 2) + 1;

    if (original == NULL || original->next == NULL)
    {
        frontList = original;
        return;
    }

    frontList = original;
    while (count < half)
    {
        frontList = frontList->next;
    }

    backList = frontList->next ; 
    frontList->next = NULL;
}

// Q10:
void removeDuplicates(node* head)
{
    node* tmpHead = head;
    node* tmpHold;
    int tempVal;
    bool deleteHappened = false;

    while (tmpHead != NULL)
    {
        deleteHappened = false;
        if (tmpHead->next != NULL)
        {
            deleteHappened = true;
            if (tmpHead->data == tmpHead->next->data)
            {
                tmpHold = tmpHead->next->next;
                delete tmpHead->next;
                tmpHead->next = tmpHold;
            }

            // IMP: only advance if no deletion. Else we cannot delete more than
            // TWO duplicates
            else
            {
                tmpHead = tmpHead->next;
            }
        }

        if (!deleteHappened)
        {
            tmpHead = tmpHead->next;
        }
    }
}

// Q11: Move Node
void moveNode(node*& dstList, node*&srcList)
{
    if (srcList == NULL)
    {
        return ;
    }

    node* tmpDst = srcList->next;

    srcList->next = dstList;
    dstList = srcList;
    srcList = tmpDst;

}

// Q12 Alternating Split
void alternatingSplit(node* src, node*& aRef, node*& bRef)
{
    node* tmpSrc = src;
    while (tmpSrc != NULL)
    {
        moveNode(aRef, tmpSrc);
        if (tmpSrc != NULL)
        {
            moveNode(bRef, tmpSrc);
        }
    }
}

//Q13: ShuffleMerge
node* shuffleMerge(node* a, node* b)
{
    node* srcMerged = NULL;
    node** merged = &srcMerged;
    while (a != NULL && b != NULL)
    {
        moveNode(*merged, a);
        merged=&((*merged)->next);
        moveNode(*merged, b);
        merged=&((*merged)->next);
    }
    
    while (a != NULL)
    {
        moveNode(*merged, a);
        merged=&((*merged)->next);
    }

    while (b != NULL)
    {
        moveNode(*merged, b);
        merged=&((*merged)->next);
    }

    return srcMerged;
}

// Helper routine to move first node from node b to node a
// This rountine when called on a linked list will reverse the complete list.
void moveNode2(struct node*& a, struct node*& b)
{
    if (b != NULL)
    {
        struct node* temp = a;
        a = b;
        b = b->next;
        a->next = temp;
    }
}

// Bloomberg Coding Prep 2.
// Problem 1: 
//      Given the root node to a singly linked list, reverse the last 5
//      nodes in the list. For a list with 5 or less nodes, reverse the whole list.
// Algorithm:
//      Have first node pointing to head and second node pointing to the node 5 steps
//      ahead.
//
//      Then traverse both head and the other node till the other node reaches NULL.
//      Now we will have head pointing to last but 5 nodes.
//
// Complexity: O(N)
void reverseLast5Node(struct node*& head)
{
    // We will never move the position of head.
    struct node* tmpHead = head;   // A temporary node storing head's position. We will never mo
    struct node* headFive = head;   // A temp node that points five nodes ahead.
    struct node* result = NULL;     // A temporary node to store the reversed list.
    unsigned int count = 0;

    while (headFive != NULL &&
           count < 5)
    {
        headFive = headFive->next;
        count++;
    }

    // If count is five and tmpHead is not null, then we have more atleast five nodes
    if (count == 5 && headFive != NULL)
    {
        // Now "tmpHead" is 5 steps behind. So move both tmpHead and headFive till headFive
        // reaches NULL. Then tmpHead will be pointing to the last five nodes.
        while(headFive->next != NULL)
        {
            tmpHead = tmpHead->next;
            headFive = headFive->next;
        }

        // Reverse the last five nodes of the linked list.
        while(tmpHead->next != NULL)
        {
            moveNode2(result, tmpHead->next);
        }

        // Set the next pointer to point to the reversed list.
        tmpHead->next = result;
    }
    else
    {
        // This takes care of reversing the linked list if it has 5 or lesser nodes.
        while(head != NULL)
        {
            moveNode2(result, head);
        }

        head = result;
    }
}

// Minimum node in a linked list
void minimumNode(node* head)
{
    struct node* minNode = new node();
    minNode->data = INT_MAX;
    minNode->next = NULL;

    while (head != NULL)
    {
        // If the minimum element is M and we have N elements greater than M which are
        // ahead of M, then the if block will be executed N times.
        if (minNode->data > head->data)
        {
            minNode->data = head->data;
        }
        head = head->next;
    }

    cout << minNode->data << endl;
}

// Delte Nodes that have a certain value
void removeNode(node*& head, int val)
{
    if (head == NULL)
    {
        return;
    }

    node* cur = head;

    while (cur != NULL && cur->data == val)
    {
        node* tmp = cur->next;
        delete cur;
        head = tmp;
        cur = tmp;
    }

    struct node* curNext = cur->next;
    while(curNext != NULL)
    {
        if(curNext->data == val)
        {
            cur->next = curNext->next;
            delete curNext;

            curNext = cur->next;
        }

        else
        {
            cur = cur->next;
            curNext = cur->next;
        }
    }
}

// Main Function
int main()
{
    cout << "Stanford Linked List Problems" << endl;

    // Create an empty list to start with
    node* head = new node();
    head = NULL;

//    node* head2 = new node();
    node* head2 = NULL;

    // Fill in values
    {
        /*
        Push(head2, 1);
        Push(head2, 2);
        Push(head2, 3);
        */

        Push(head, 1);
        Push(head, 2);
        Push(head, 3);
        Push(head, 4);
        Push(head, 5);
        Push(head, 6);
        Push(head, 7);
        Push(head, 8);
    }

    // Reversing the List
    {
        //moveNode2(head2, head);

        printList(head);
        reverseLast5Node(head);
        printList(head);

        //reverseLast5Node(head2);
        //printList(head2);
    }

    // Get Nth Element
    {
        cout << "Get Nth Element: " << endl;
        cout << getNth(head, 0) << endl;
        cout << getNth(head, 1) << endl;
        cout << getNth(head, 2) << endl;
    }

    //deleteList(head);
    printList(head);

    // Pop
    {
        cout << "Pop: " << endl;
        cout << pop(head) << endl;
        cout << pop(head) << endl;
        cout << pop(head) << endl;
        cout << pop(head) << endl;
    }

    // InsertNth
    {
        head = NULL;
        insertNth(head, 0, 5);
        insertNth(head, 0, 10);
        insertNth(head, 0, 10);
        insertNth(head, 0, 10);
        insertNth(head, 0, 10);
        insertNth(head, 3, 16);
        insertNth(head, 2, 3);

        insertNth(head, 0, 5);
        insertNth(head, 0, 2);
        insertNth(head, 0, 1);
        insertNth(head, 3, 6);
        insertNth(head, 2, 3);

        cout << endl << "Insert Nth" << endl;
        printList(head);
    }

    // Sorted Insert
    {
        node* temp2 = new node();
        temp2->next = NULL;
        temp2->data = 0;

        node* temp3 = new node();
        temp3->next = NULL;
        temp3->data = 0;

        node* temp4 = new node();
        temp4->next = NULL;
        //temp4->data = 17;
        temp4->data = 5;

        sortedInsert(head, temp2);
        sortedInsert(head, temp3);
        sortedInsert(head, temp4);
        //printList(head);
    }

    // Insertion Sort
    {
        cout << endl <<  "Insertion Sort" << endl;
        insertionSort(head);
        printList(head);
    }

    // Remove Duplicates
    {
        cout << endl <<  "Remove Duplicates" << endl;
        removeDuplicates(head);
        printList(head);
    }

    cout << "Another List" << endl;
    printList(head2);

    // Move Node
    {
        cout << endl <<  "Move Node" << endl;
        moveNode(head, head2);
        printList(head);
        printList(head2);
        cout << "Move Node again" << endl;
        moveNode(head, head2);
        moveNode(head, head2);
        printList(head);
        printList(head2);
    }

    // Alternating Split
    node* aRef = NULL;
    node* bRef = NULL;
    {
        cout << endl << "Alternating Split" << endl;
        alternatingSplit(head, aRef, bRef);
        printList(aRef);
        printList(bRef);
    }

    // Shuffle Merge
    node* merged = NULL;
    {
        cout << endl << "Shuffle Merge" << endl;
        merged = shuffleMerge(aRef, bRef);
        printList(merged);
    }

    // Minimum Node in the list
    {
        cout << endl << "Minimum Node" << endl;
        printList(merged);
        minimumNode(merged);
    }

    // Delete nodes containing a Value
    {
        node* head = NULL;
        insertNth(head, 0, 5);
        insertNth(head, 0, 5);
        insertNth(head, 0, 5);
        insertNth(head, 0, 3);
        insertNth(head, 0, 5);
        insertNth(head, 0, 5);
        insertNth(head, 0, 5);


        cout << endl << "Delete Node" << endl;
        int val = 5;
        removeNode(head, val);
        printList(head);
    }

    cout << endl;
    return 0;
}

