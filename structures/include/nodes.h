#ifndef STRUCTURES_NODES_H
#define STRUCTURES_NODES_H

#include <exception>
#include "arrays.h"     // to include exceptions and for conversions of type A->B.

namespace Structures {

    template<typename T> class uNode;               // uni-directional node
    template<typename T> class bNode;               // bi-directional node
    template<typename T> class uLinkedList;         // uni-directional linked list
    template<typename T> class bLinkedList;         // bi-directional linked list

#pragma region typeAcronyms

    template<typename T> using uN = uNode<T>;
    template<typename T> using bN = bNode<T>;
    template<typename T> using uLL = uLinkedList<T>;
    template<typename T> using bLL = bLinkedList<T>;

#pragma endregion

#pragma region uNodeImplementation
    /*
    * @brief *uni-directional* node (contains refernce to only the next node)
    *
    * @details
    * conventional one-directional node that keeps information about its next node in sequence.
    * usage consist typically to make linked list (unidirectional) and impliment stack and queue.
    *
    * @tparam T  Type of the implementation class.
    *
    * @par Usage
    * @code
    * uNode<int>* node = new uNode<int>(value1);        // declare a node
    * uNode<int>* next = new uNode<int>(value2);        // declare next node
    * node->setNext(next);                              // make a link between nodes
    * @endcode
    *
    *  connect it in a manner as : [NODE] -> [NEXT] -> |nullptr|
    */
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
        uNode<Type>* getNext() { return __next; }
        void setItem(Type* item) { __item = item; }
        void setNext(uNode<Type>* next) { __next = next; }
    };
#pragma endregion

#pragma region nNodeImplementaion
    /*
    * @brief *bi-directional* node (contains refernce to next & previous nodes)
    *
    * @details
    * conventional bi-directional node that keeps information about its next and previous nodes.
    * usage consist typically to make linked list (bi-directional) and impliment dequeue.
    *
    * @tparam T  Type of the implementation class.
    *
    * @par Usage
    * @code
    * bNode<int>* prev = new bNode<int>(value0);        // declare prev node
    * bNode<int>* node = new bNode<int>(value1);        // declare a node
    * bNode<int>* next = new bNode<int>(value2);        // declare next node
    * @endcode
    *
    * connect it in a manner as : |nullptr| <- [PREV] <=> [NODE] <=> [NEXT] -> |nullptr|
    */
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
        bNode<Type>* getNext() { return __next; }
        bNode<Type>* getPrev() { return __prev; }
        void setItem(Type* item) { __item = item; }
        void setNext(bNode<Type>* next) { __next = next; }
        void setPrev(bNode<Type>* prev) { __prev = prev; }
    };
#pragma endregion

#pragma region un-neccessesary-insight
    // One may use this for unideirectional or bidirectional Liked List as follows, i dont feel the need to make a linked
    // list class for this purpose, i will however make required functions to support operations on linked lists.
    // (change of plans) i am implimenting Linked list class for making it more efficient to use Linked List.
    // linked list for our case is just a pointer to a nNode<Type>, havent planned for this yet.
#pragma endregion

#pragma region uLinkedListImplementaion
    /**
    * @brief *uni-directional* linked list (built using uNode)
    *
    * @details
    * conventional one-directional linked list that stores a sequence of nodes connected in a forward-only manner.
    * provides basic operations like insert, remove, search, and traversal.
    * internally uses uNode to manage each element and the pointer to the next node.
    *
    * @tparam T  Type of the data stored in the list.
    */
    template<typename T> class uLinkedList {
    private:
        uN<T>* __head;          // Store head of linked list
        uN<T>* __tail;          // Store tail (not madatory but is there for perfoemance in some cases).
        int __size;             // Specifically for conversion to other primitive types.

    public:
        uLinkedList() : __head(nullptr), __tail(nullptr), __size(0) {}

    public:

        // attach<DIRECTION> and detach<DIRECTION> is there only for special purposes like to make stack and queue.
        // stack -> attachL and detachL. LIFO
        // queue -> attachR and detachL. FIFO

        void attachL(T item);                   // to attach a node to left of the linked list.
        void attachR(T item);                   // to attach a node to right of the linked list.
        T& detachL();                           // to detach left most and move head to next.
        T& detachR();                           // to detach right most node.

        void insert(T item, int index);         // insert an item to specified index.
        T& remove(int index);                   // remove element form specified index.
        uN<T>& get(int index);                  // get element at specified index.
    };
#pragma endregion

#pragma region bLinkedListImplementation
    /**
    * @brief *bi-directional* linked list (built using bNode)
    *
    * @details
    * conventional two-way linked list where each node stores a reference to both its previous and next nodes.
    * allows traversal in both directions and supports more efficient insert/remove operations from either end or middle.
    * internally uses bNode to manage each element and its neighboring connections.
    *
    * @tparam T  Type of the data stored in the list.
    */
    template<typename T> class bLinkedList {
    private:
        bN<T>* __head;          // Store head of linked list
        bN<T>* __tail;          // Store tail (same reason as previous).
        int __size;             // Specifically for conversion to other primitive types.

    public:
        bLinkedList() : __head(nullptr), __tail(nullptr), __size(0) {}

    public:

        // attach<DIRECTION> and detach<DIRECTION> is there only for special purposes like to make stack and queue.
        // stack -> attachL and detachL. LIFO, unidirectional
        // queue -> attachR and detachL. FIFO, bidirectional
        // it makes sense that bidirectional LL is used for this purpose.

        void attachL(T item);                   // to attach a node to left of the linked list.
        void attachR(T item);                   // to attach a node to right of the linked list. 
        T& detachL();                           // to detach left most and move head to next.
        T& detachR();                           // to detach right most node.

        void insert(T item, int index);         // insert an item at specified index.
        T& remove(int index);                   // remove element from specified index.
        bN<T>& get(int index);                  // get element at specified index.
    };

#pragma endregion

#pragma region typeConversionFunctions
    // TODO: impliment type conversions from Linked List to an array and from an array to Linked List
    // TODO: impliment variant for both dynamic and atatic array <--> uni and bi directional LL.
#pragma endregion

};

#include "nodes.inl"

#endif