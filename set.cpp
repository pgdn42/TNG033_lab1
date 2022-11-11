#include "set.hpp"

// std::size_t is defined in the C++ standard library
// std::size_t is an unsigned integer type that can store the maximum size of any possible object
// sizes are non-negative integers -- i.e. unsigned integer type

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ******************************************************** */

// Default constructor
Set::Set()
    : head(new Node{0, nullptr}), counter(0)
{}

// Constructor for creating a set from an int
Set::Set(int v) 
    : Set{}
{
    insert(v);
}

// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements
Set::Set(const std::vector<int>& V) 
    : Set{}
{
    for (int value : V) {
        insert(value);
    }
}

// copy constructor
Set::Set(const Set& source) 
    : Set{}
{
    Node* ptr = source.head->next;
    while (ptr != nullptr) {
        insert(ptr->value);
        ptr = ptr->next;
    }

}

// Assignment operator: copy-and-swap idiom
Set& Set::operator=(Set s) {

    std::swap(head, s.head);
    std::swap(counter, s.counter);

    return *this;
}

// Destructor: deallocate all nodes
Set::~Set() {
    Node* ptr = head;

    while (ptr != nullptr) {
        head = ptr->next;
        remove(ptr);
        ptr = head;
    }
}

// Return number of elements in the set
std::size_t Set::cardinality() const {
    return counter;
}

// Test if set is empty
bool Set::empty() const {
    // ADD CODE

    return counter > 0 ? false : true;  // delete if needed
}

// Test if x is an element of the set
bool Set::member(int x) const {
    
    Node* ptr = head;

    while (ptr != nullptr) {
        if (ptr->value == x) {
            return true;
        }
        ptr = ptr->next;
    }

    return false; 
}

bool Set::operator<=(const Set& b) const {
    
    Node* R = head->next;

    while (R != nullptr && b.member(R->value)) {
        R = R->next;
    }
    if (R == nullptr) {
        return true;
    }

    return false;  
}


bool Set::operator==(const Set& b) const {

    return(b <= *this && *this <= b) ? true : false;

}

bool Set::operator!=(const Set& b) const {

    return(!(b == *this)) ? true : false;

}

bool Set::operator<(const Set& b) const {
    
    return((b != *this) && (*this <= b)) ? true : false;

}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const {
    
    Node* ptr = b.head->next;
    Node* hptr = head->next;
    std::vector<int> v;

    while (ptr != nullptr) {
        v.push_back(ptr->value);
            ptr = ptr->next;
    }
    while (hptr != nullptr) {
        v.push_back(hptr->value);
        hptr = hptr->next;
    }

    return Set{v};  // delete if needed
}

// Set intersection
Set Set::operator*(const Set& b) const {

    Node* ptr = b.head->next;
    std::vector<int> v;

    while (ptr != nullptr) {
        if (member(ptr->value)){
            v.push_back(ptr->value);
        }
        ptr = ptr->next;

    }

    return Set{v};  // delete if needed
}

// Set difference
Set Set::operator-(const Set& b) const {

    Node* ptr = head->next;
    std::vector<int> v;

    while (ptr != nullptr) {
        if (!b.member(ptr->value)) { //!member not work, b.memeber work b.head/head
            v.push_back(ptr->value);
          
        }
        ptr = ptr->next;
    }

    return(v.empty()) ? Set{} : Set{ v };  // delete if needed
}

// set difference with set {x}
Set Set::operator-(int x) const {

    //return(member(x)) ? Set{ x } : Set{}; why no work
    return *this - Set{ x };
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Set& theSet) {
    if (theSet.empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp != nullptr) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/

//Insert node after given ptr
void Set::insert(Node* ptr, int v) {
    Node* temp = new Node(v, ptr->next);
    ptr->next = temp;
    counter++;
}
//Insert after last valid ptr
void Set::insert(int v) {
    Node* ptr = head;

    while (ptr->next != nullptr && ptr->next->value < v) {
        ptr = ptr->next;
    }
    if (ptr->next == nullptr || ptr->next->value != v) {
        insert(ptr, v);
    }

}
//remove one node and ptr and decrease counter
void Set::remove(Node* ptr) {
    delete ptr;
    ptr->next = nullptr;
    
    counter--;
}

