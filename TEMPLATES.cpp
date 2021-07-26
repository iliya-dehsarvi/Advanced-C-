#include <iostream>
#include <ostream>

template <typename TYPE>
struct Node {
    TYPE DATA;
    Node *NEXT;
};

template <typename TYPE>
class LinkedList {
    Node<TYPE> *HEAD;
    int COUNT;
public:
    LinkedList() {
        HEAD = new Node<TYPE>;
        HEAD->NEXT = NULL;
        COUNT = 0;
    }
    // ~LinkedList() { delete HEAD; }
    void TRAVERSE() {
        Node<TYPE> *NODE_PTR=HEAD;
        while(NODE_PTR->NEXT){
            std::cout << NODE_PTR->DATA << std::endl;
        }
    }
    void APPEND(TYPE NEW_DATA) {
        Node<TYPE> *NEW_NODE = new Node<TYPE>;
        Node<TYPE> *NODE_PTR = HEAD;
        NEW_NODE->DATA = NEW_DATA;
        while (NODE_PTR->NEXT) { std::cout << NODE_PTR->DATA << std::endl; }
        NODE_PTR->NEXT = NEW_NODE;
        NEW_NODE->NEXT = NULL;
        COUNT++;
    }

    void INSTER(TYPE NEW_DATA) {
        Node<TYPE> *NEW_NODE = new Node<TYPE>;
        Node<TYPE> *NODE_PTR = HEAD;
        NEW_NODE->DATA = NEW_DATA;
        while (NODE_PTR->NEXT || NODE_PTR->DATA > NEW_DATA) { std::cout << NODE_PTR->DATA << std::endl; }
        NODE_PTR->NEXT = NEW_NODE;
        NEW_NODE->NEXT = NULL;
    }

    void DELETE(TYPE DATA_TO_DELETE) {
        Node<TYPE> *PRE_PTR = HEAD;
        Node<TYPE> *CURR_PTR = HEAD->NEXT;
        Node<TYPE> *NODE_PTR = NULL;

        while (CURR_PTR || CURR_PTR->DATA != DATA_TO_DELETE) {
            PRE_PTR = CURR_PTR;
            CURR_PTR = CURR_PTR->NEXT;
        }

        NODE_PTR = CURR_PTR;
        PRE_PTR->NEXT = CURR_PTR->NEXT;
        delete NODE_PTR;
    }


};

struct Data {
    std::string NAME;
    int AGE;
};

int main() {
    Data DATA;
    DATA.NAME = "ILIYA";
    DATA.AGE = 20;
        
    std::string NAME = "ILIYA";
    
    LinkedList<std::string> LIST;

    LIST.APPEND(NAME);

    LIST.TRAVERSE();

    return 0;
}
