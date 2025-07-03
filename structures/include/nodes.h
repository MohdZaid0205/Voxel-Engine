#ifndef STRUCTURES_NODES_H
#define STRUCTURES_NODES_H

namespace Structures {

    template<typename Type> class uNode;        // uni-directional
    template<typename Type> class bNode;        // bi-directional

    template<typename T> using uN = uNode<T>;   // shorthand for uNode
    template<typename T> using bN = bNode<T>;   // shorthand for bNode


    // uni-directional Node Implementation
    template<typename Type> class uNode {
    private:
        Type* __item;                           // store pointer to the element.
        uNode* __next;                          // store pointer to next node.
    public:
        uNode()                                 : __item(nullptr), __next(nullptr) {}
        uNode(Type* item)                       : __item(item)   , __next(nullptr) {}
        uNode(Type* item, uNode<Type>* next)    : __item(item)   , __next(next)    {}
        ~uNode() {
            delete __item;                      // delete the item stored.
            delete __next;                      // trigger delete for next node.
        };
    public:
        Type* getItem() { return __item; }
        uNode* getNext() { return __next; }
        void setItem(Type* item) { __item = item; }
        void setNext(uNode* next) { __next = next; }
    };

    // bi-directional Node Implementation
    template<typename Type> class bNode {
    private:
        Type* __item;                           // store pointer to the element.
        bNode* __prev;                          // store pointer to previous node.
        bNode* __next;                          // store pointer to next node.
    public:
        bNode()                                                 : __item(nullptr), __next(nullptr), __prev(nullptr) {}
        bNode(Type* item)                                       : __item(item)   , __next(nullptr), __prev(nullptr) {}
        bNode(Type* item, bNode<Type>* next)                    : __item(item)   , __next(next)   , __prev(nullptr) {}
        bNode(Type* item, bNode<Type>* next, bNode<Type>* prev) : __item(item)   , __next(next)   , __prev(prev)    {}
        ~bNode() {
            delete __item;                      // delete the item stored.
            delete __next;                      // trigger delete for next node.
            // we do not delete previous node as current node does not own previous node (its the opposite).
            // I however am un aware of how this is done prooperly, so this is subjected to change in future.
            // delete __prev;                   // uncomment this line to delete previous node too.
        }
    public:
        Type* getItem() { return __item; }
        uNode* getNext() { return __next; }
        uNode* getPrev() { return __prev; }
        void setItem(Type* item) { __item = item; }
        void setNext(uNode* next) { __next = next; }
        void setPrev(uNode* prev) { __prev = prev; }
    };

    // One may use this for unideirectional or bidirectional Liked List as follows, i dont feel the need to make a linked
    // list class for this purpose, i will however make required functions to support operations on linked lists.
    // (change of plans) i am implimenting Linked list class for making it more efficient to use Linked List.
    // linked list for our case is just a pointer to a nNode<Type>, havent planned for this yet.
    
    template<typename T> class uLinkedList;
    template<typename T> class bLinkedList;

    // unidorectional Liked list implimentaion
    template<typename T> class uLinkedList {
    private:
        uN<T>* __head;         // Store head of linked list
        uN<T>* __tail;         // Store tail (not madatory but is there for perfoemance in some cases).
        int __size;         // Specifically for converson to other promitive types.

    public:
        uLinkedList() : __head(nullptr), __tail(nullptr), __size(0) {}

    public:

        // attach<DIRECTION> and detach<DIRECTION> is there only for special purposes like to make stack and queue.
        // stack -> attachL and detachL. LIFO
        // queue -> attachR and detachL. FIFO

        void attachL(T item);       // to attach a node to left of the linked list. { visually: |new| -> |head| -> |...| -> |tail| }
        void attachR(T item);       // to attach a node to right of the linked list. { visually: |head| -> |...| -> |tail| -> |new| }
        T& detachL();        // to detach left most and move head to next. { returns: head, moves to next element to head and detaches previous. }
        T& detachR();        // to detach right most node. { returns: tail, no need to previous of tail becomes new tail. }

        void insert(T item, int index);     // insert an item to specified index.
        T& remove(int index);                // remove element form specified index.
        uN<T>& get(int index);                 // get element at specified index.
    };

    // TODO: impliment type conversions from Linked List to an array and from an array to Linked List
    // TODO: impliment variant for both dynamic and atatic array <--> uni and bi directional LL.
}

#include "nodes.inl"

#endif