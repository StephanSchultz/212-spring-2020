#include "DoublyLinkedList.h"

//constructors for the linked list
DoublyLinkedList::DoublyLinkedList() //default constructor (empty list)
{
    //I have implemented this for you. This will initialize all the variables in the linked list.
    m_head = nullptr;
    m_tail = nullptr;
    m_node_count = 0;
}
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other) //copy constructor
{
    (*this) = other; //this will just reuse the code from the assignment operator
}
DoublyLinkedList::DoublyLinkedList(const std::string &data_string)
{
    //This constructor generates a linked list using a string where each node is a character in the string
    if (data_string.size() == 0u)
    {
        m_head = m_tail = nullptr;
        m_node_count = 0;
    }
    else
    {
        std::string::size_type string_length, i;
        string_length = data_string.size();

        m_head = new Node(data_string.at(0));
        m_tail = m_head;
        for (i = 1; i < string_length; i++)
        {
            char character = data_string.at(i);
            Node* new_node = new Node(character);
            new_node->previous = m_tail;
            new_node->next = nullptr;
            m_tail->next = new_node;

            //assign this node as the new tail
            m_tail = new_node;
        }

        //make the list circular
        m_head->previous = m_tail;
        m_tail->next = m_head;

        //set the size correctly
        m_node_count = static_cast<int>(string_length);
    }
}
DoublyLinkedList::~DoublyLinkedList() //destructor
{
    Node *p;

    p = m_head;

    m_head->previous = nullptr;
    m_tail -> next= nullptr;

    while(m_head != nullptr){
        m_head=m_head->next;
        delete p;
        p = m_head;
        }
}

//add to to the end of the list
void DoublyLinkedList::append(char data)
{
    // if the list is empty
    // create a new node pointer p with the characters data
    Node *p = new Node(data);
    //if head is pointeing to null
    if(m_head == nullptr){
        //point head to p with the new data
        m_head = p;
        //point tail to p with the new data
        m_tail = p;
        //and p next points to p
        p->next =p;
        //and previous points to p
        p->previous = p;
        //increment the list by 1 after appending the value
        m_node_count++;
        return;
    }
    //if the list is not empty and want to add a value
    else
    {
        //after adding the element at the end of the list get p to point backwards to tail
        p->previous = m_tail;
        // and get tail to point next to p forward
        m_tail->next = p;
        //and head pointing backwards to p
        m_head->previous = p;
        //and p next to point to tail
        p->next = m_head;
        //update tail to become p
        //and make the list circular
        m_tail = p;
        //increment the list
        m_node_count++;
        return;
    }
    //..............
    // TODO
    //..............
}

//add to the beginning of the list
void DoublyLinkedList::prepend(char data)
{
    //create a new node p the includes data.
    Node *p = new Node(data);
    //if the list is empty append
    if(m_head == nullptr){
        //head points to p
        m_head = p;
        //tail points to pas its the only element in the list
        m_tail = p;
        //p next to point back to p
        p->next =p;
        //and p previous to point back to p
        p->previous = p;
        //increment the list to keep it updated
        m_node_count++;
        return;
    }
    else{
        //if the list is not empty
        //add the element before head and make p next to be head
        p -> next = m_head;
        //and p now points to tail backwards
        p ->previous = m_tail;
        //get head to point back to tail
        m_head -> previous = p;
        //tail next points to p to make the list circular
        m_tail->next = p;
        //update head and now p is head
        m_head = p;
        //increment the list to keep it updated
        m_node_count++;
    }
    //..............
    // TODO
    //..............
}

//add to the middle of the list (index = 0) means insert at the beginning of the list
void DoublyLinkedList::insert(int index, char data)
{
    //create 3 nodes to point one node before the index where we will insert and one to point to the index after where we will insert
    Node *p = new Node(data);
    //if the list is empty append
    if(m_head == nullptr){
        m_head = p;
        m_tail = p;
        p->next =p;
        p->previous = p;
        m_node_count++;
        return;
    }
    else if(index == 0){
        prepend(data);
    }
    else if (index == m_node_count)
    {
        append(data);
    }
    else if(index>m_node_count){
        return;
    }
    //if the list is not emty and need to append data in the middle of the linked list

    else {
        Node *q = m_head;
        Node *r = m_head->next;
        //create a loop through the list untill we find the index to insert the data
        for(int i = 0; i<index-1; i++){
            //q will be the pointing to the element before the index t insert
            q = q->next;
            //r will be pointing to the element after where we want to insert the data
            r = r -> next;
        }
        //add the element and get the data to point next to r
        p->next = r;
        //and get p to point back to q
        p ->previous = q;
        //and get r previous pointing to p
        r ->previous = p;
        // and q next to point to p to make a double linked list
        q -> next = p;
        //update and increment the list
        m_node_count++;


    }

    //..............
    // TODO
    //..............
}

//remove from the end of the list
void DoublyLinkedList::removeLast()
{
    //create a new node p that has the character data
    Node *p;
    //if the the list is empty clear the list
    if(m_node_count == 1){
        clear();
    }
    else if(m_node_count == 0) {
        return;
    }
    //if the list is not empty and want to remove the last element
    else{
        //p points to the element before tail
        p = m_tail->previous;
        //get p to pint to head to not lose the link
        p->next = m_head;
        //head previous now points to p instead to tail
        m_head->previous= p;
        //remove the pointer that was pointing from tail to head and now tail points to null
        m_tail->next = NULL;
        //tail previous now points to null
        m_tail->previous = NULL;
        //delete tail
        delete m_tail;
        //them make tail to become p
        m_tail = p;
        // and decrement the list to keep it updated
        m_node_count--;
    }

    //..............
    // TODO
    //..............
}

//remove from the beginning of the list
void DoublyLinkedList::removeFirst()
{

    // create a new node p that has the data
    Node *p;
    //if the list is empty clear the list
    if(m_node_count == 1){
        clear();
    }
    if(m_node_count == 0){
        return;
    }
    //if the list is not empty
    else{
        //get p to point to the element infront of head
        p = m_head ->next;
        //get p previous to point to tail
        p->previous = m_tail;
        //tail next now point to p instead of head
        m_tail -> next = p;
        //head next points to null
        m_head -> next = NULL;
        //and head previous to point to null so head doesnt point to any of the elements in the list
        m_head->previous = NULL;
        //delete head
        delete m_head;
        //then get head to become p and p is now head
        m_head = p;
        // decrement th list to keep it updated
        m_node_count--;

    }
    //..............
    // TODO
    //..............
}

//remove from a specific position in the list
void DoublyLinkedList::removeAt(int index)
{
    if(index < 0) {
         return;
     }
         // if list is empty, just return
    if (m_node_count == 0)
        return;
    // if removing at index = 0, just call removeFirst()
    if (index == 0)
    {
        removeFirst();
        return;
    }
    // if removing at index = m_node_count - 1, just call removeLat()
    else if (index == m_node_count - 1)
    {
        removeLast();
        return;
    }
    // find the node at index
    Node * node = m_head;
    for (int i = 0; i < index; ++i)
        node = node->next;
    // get the previous and the next nodes of this node
    Node * previous = node->previous;
    Node * next = node->next;
    // delete the node
    delete node;
    // decrease node count
    m_node_count--;
    // if list becomes empty
    if (m_node_count == 0)
        // set the head and tail as nullptr
        m_head = m_tail = nullptr;
    // if list is not emtpy
    else
    {
        // set previous and next of previous and next nodes properly
        previous->next = next;
        next->previous = previous;
    }
    //..............
    // TODO
    //..............
}

//remove all nodes from the linked list
void DoublyLinkedList::clear()
{

    // starting from the head
    Node * node = m_head;
    while (m_node_count > 0)
    {
        // get the next node
        Node * next = node->next;
        // delete current node
        delete node;
        // set the next node as current
        node = next;
        // decrease node count
        m_node_count--;
    }
    // set the head and tail as nullptr
    m_head = m_tail = nullptr;
    // set node count to 0
    m_node_count = 0;
    //..............
    // TODO
    //..............
}

//get a value at a position in the linked list
char DoublyLinkedList::get(int index) const
{

        // find the node at index
    Node * node = m_head;
    for (int i = 0; i < index; ++i)
        node = node->next;
    // return its data
    return node->data;
    //..............
    // TODO
    //..............
}

//modify a value at a position in the linked list
void DoublyLinkedList::set(int index, char new_value)
{


    // find the node at index
    Node * node = m_head;
    for (int i = 0; i < index; ++i)
        node = node->next;
    // update its data
    node->data = new_value;
    //..............
    // TODO
    //..............
}

//find the first occurence of "search char" in the linked list and return its position. Return -1 if the character is not found.
int DoublyLinkedList::findFirstOf(char search_char) const
{


    // starting from the head
    int result = -1;
    Node * node = m_head;
    for (int i = 0; i < m_node_count; ++i)
    {
        // if the data matches the given char, return its index
        if (node->data == search_char)
            return i;
        // otherwise, get the next node
        node = node->next;
    }
    // if not found, return -1
    return result;

    //..............
    // TODO
    //..............
}

//find the last occurence of "search_char" in the linked list and return its position. Return -1 if the character is not found.
int DoublyLinkedList::findLastOf(char search_char) const
{

        // starting from the tail
    int result = -1;
    Node * node = m_tail;
    for (int i = m_node_count - 1; i >= 0; --i)
    {
        // if the data matches the given char, return its index
        if (node->data == search_char)
            return i;
        // otherwise, get the previous node
        node = node->previous;
    }
    // if not found, return -1
    return result;
    //..............
    // TODO
    //..............
}

//functions that you do NOT have to implement
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& other)
{
    clear();
    if (other.m_node_count > 0)
    {
        Node* o_current, *t_current;

        m_head = new Node(other.m_head->data);
        t_current = m_head;

        o_current = other.m_head->next;
        for (int i = 1; i < other.m_node_count; i++)
        {
            t_current->next = new Node(o_current->data);
            t_current->next->previous = t_current;
            o_current = o_current->next;
            t_current = t_current->next;
        }
        m_tail = t_current;

        m_head->previous = m_tail;
        m_tail->next = m_head;
    }
    return (*this);
}
char DoublyLinkedList::operator[](int index) const
{
    return get(index);
}
Node *DoublyLinkedList::firstNode()
{
    return m_head;
}
int DoublyLinkedList::getSize() const
{
    return m_node_count;
}
std::string DoublyLinkedList::toString() const
{
    std::string str;
    if (m_head != nullptr)
    {
        Node* current = m_head;
        str.reserve(static_cast<std::string::size_type>(m_node_count));
        for (int i = 0; i < m_node_count; i++)
        {
            str.push_back(current->data);
            current = current->next; //move to the next node
        }
    }
    return str;
}
//node constructors
Node::Node() :previous(nullptr), next(nullptr), data('0') {}
Node::Node(char c) :previous(nullptr), next(nullptr), data(c) {}
