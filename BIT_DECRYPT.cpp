#include <bitset>
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <string>
#include <queue>
#include <list>
#include <math.h>
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
g++ --std=c++11 BIT_DECRYPT.cpp -o BIT_DECRYPT && ./BIT_DECRYPT
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  */
class GET_DATA {
    std::vector<std::pair<std::string, int>> _ENCRYPTED_CONTAINER;
public:
    GET_DATA(std::string FILENAME="Frequencies.txt") {
        std::fstream ENCRYPTED_FILE;
        std::string BUFFER;
        std::regex REGEX("'(.+)',(.+)\r*");
        ENCRYPTED_FILE.open(FILENAME);
        if (!ENCRYPTED_FILE) {
            std::cout << "Unable to open the file "+FILENAME+"\n";
            exit(1);
        }
        while (!ENCRYPTED_FILE.eof()) {
            std::getline(ENCRYPTED_FILE, BUFFER);
            std::smatch MATCHES;
            if (std::regex_match(BUFFER, MATCHES, REGEX)) {
                if (MATCHES.size() > 2) { _ENCRYPTED_CONTAINER.push_back({MATCHES[1].str(), stoi(MATCHES[2])}); }
                else { _ENCRYPTED_CONTAINER.push_back({MATCHES[0].str(), stoi(MATCHES[1])}); }
            }
        } ENCRYPTED_FILE.close();
    }
    std::vector<std::pair<std::string, int>> ENCRYPTED_CONTAINER() { return _ENCRYPTED_CONTAINER; }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
//class NODE {
//public:
//    float _FREQ;
//    std::string _SYMB;
//    NODE(std::string PASSED_SYMB="", float PASSED_FREQ=0) {
//        _SYMB=PASSED_SYMB;
//        _FREQ=PASSED_FREQ;
//    }
//
//
////    virtual std::string SYMB()=0;
////    virtual float FREQ()=0;
//};
class NODE {
public:
    virtual std::string SYMB()=0;
    virtual float FREQ()=0;
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class BRANCH: virtual public NODE {
    NODE* _LEFT;
    NODE* _RIGHT;
public:
    BRANCH(NODE* PASSED_NODE_0, NODE* PASSED_NODE_1): _LEFT(PASSED_NODE_0), _RIGHT(PASSED_NODE_1) {}
    float FREQ() { return _LEFT->FREQ()+_RIGHT->FREQ(); }
    std::string SYMB() { return _LEFT->SYMB()+_RIGHT->SYMB(); }
    NODE* LEFT() { return _LEFT; }
    NODE* RIGHT() { return _RIGHT; }
};
//class BRANCH: virtual public NODE {
//    NODE* _LEFT;
//    NODE* _RIGHT;
//public:
//    BRANCH(NODE* PASSED_NODE_0, NODE* PASSED_NODE_1): _LEFT(PASSED_NODE_0), _RIGHT(PASSED_NODE_1) {}
//    float FREQ() { return _LEFT->_FREQ + _RIGHT->_FREQ; }
//    std::string SYMB() { return _LEFT->_SYMB+_RIGHT->_SYMB; }
//    NODE* LEFT() { return _LEFT; }
//    NODE* RIGHT() { return _RIGHT; }
//};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class LEAF: virtual public NODE {
    float _FREQ;
    std::string _SYMB;
public:
    LEAF(std::string PASSED_SYMB="", float PASSED_FREQ=0) {
        _SYMB=PASSED_SYMB;
        _FREQ=PASSED_FREQ;
    }
    float FREQ() { return _FREQ; }
    std::string SYMB() { return _SYMB; }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
//struct _COMP {
//    bool operator()(std::pair<std::string, int> LEFT, std::pair<std::string, int> RIGHT) const {
//        if (LEFT.second > RIGHT.second) { return true; }
//        else if (fabs(LEFT.second - RIGHT.second) < 0.0001) {
//            if (LEFT.first > RIGHT.first) { return true; }
//        } return false;
//    }
//};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
//struct NODE_COMP {
//    bool operator()(NODE* LEFT, NODE* RIGHT) const {
//        if (LEFT->_FREQ > RIGHT->_FREQ) { return true; }
//        else if (fabs(LEFT->_FREQ - RIGHT->_FREQ) < 0.0001) {
//            if (LEFT->_SYMB > RIGHT->_SYMB) { return true; }
//        } return false;
//    }
//};
struct NODE_COMP {
    bool operator()(NODE* LEFT, NODE* RIGHT) const {
        if (LEFT->FREQ() > RIGHT->FREQ()) { return true; }
        else if (fabs(LEFT->FREQ() - RIGHT->FREQ()) < 0.0001) {
            if (LEFT->SYMB() > RIGHT->SYMB()) { return true; }
        } return false;
    }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class QUEUE_TREE { //dynamic_cast< type* >( node ) : to check for the polymorphism
    NODE* ROOT;
    int COUNT;
//    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, _COMP> _P_QUEUE;
    std::priority_queue<NODE*, std::vector<NODE*>, NODE_COMP> _PRIORITY_QUEUE;
//
//    std::vector<std::string> _GET_BINARY_DATA(std::string FILENAME="Encrypt.bin") {
//        std::fstream BIN_FILE;
//        std::string BUFFER;
//        BIN_FILE.open(FILENAME);
//        if (!BIN_FILE) {
//            std::cout << "Unable to open the file "+FILENAME+"\n";
//            exit(1);
//        }
//        int i=1;
//        while (!ENCRYPTED_FILE.eof()) {
//            std::getline(ENCRYPTED_FILE, BUFFER);
//            std::smatch MATCHES;
//            if (std::regex_match(BUFFER, MATCHES, REGEX)) {
//                if (MATCHES.size() > 2) { _ENCRYPTED_CONTAINER.push_back({MATCHES[1].str(), stoi(MATCHES[2])}); }
//                else { _ENCRYPTED_CONTAINER.push_back({MATCHES[0].str(), stoi(MATCHES[1])}); }
//            }
//        } ENCRYPTED_FILE.close();
//    }
    std::string _DECRYPT(NODE *PQ);
public:
    QUEUE_TREE(std::string FREQUENCY_FILE="Frequency.txt", std::string BINARY_FILE="Encrypt.bin") {
        COUNT=0;
        GET_DATA SOURCE;
        for (auto PAIR : SOURCE.ENCRYPTED_CONTAINER()) {
//            std::cout << PAIR.first << " " << PAIR.second << "\n";
            LEAF *NEW_NODE = new LEAF(PAIR.first, PAIR.second);
//            NEW_NODE->_SYMB = PAIR.first;
//            NEW_NODE->_FREQ = PAIR.second;

            _PRIORITY_QUEUE.push(NEW_NODE);

//            _P_QUEUE.push({PAIR.first, PAIR.second});
            
        }
        int i=1;
        while (!_PRIORITY_QUEUE.empty()) {
            if (_PRIORITY_QUEUE.size()==1) {break;}
            auto PAIR1 = _PRIORITY_QUEUE.top();
            _PRIORITY_QUEUE.pop();
            auto PAIR2 = _PRIORITY_QUEUE.top();
            _PRIORITY_QUEUE.pop();
//            std::cout << i << ". " << PAIR1->_SYMB << " " << PAIR1->_FREQ << "\n";
//            std::cout << ++i << ". " << PAIR2->_SYMB << " " << PAIR2->_FREQ << "\n\n";
            std::cout << i << ". " << PAIR1->SYMB() << " " << PAIR1->FREQ() << "\n";
            std::cout << ++i << ". " << PAIR2->SYMB() << " " << PAIR2->FREQ() << "\n\n";
            BRANCH* NEW_BRANCH = new BRANCH(PAIR1, PAIR2);
            _PRIORITY_QUEUE.push(NEW_BRANCH);
//            delete PAIR1;
//            delete PAIR2;
            i++;
            // add to the tree
        }
    
        auto PQ = _PRIORITY_QUEUE.top();
        std::cout << i << ". " << PQ->SYMB() << " " << PQ->FREQ() << "\n";
        
//        std::cout << PQ.LEFT->SYMB() << "\n";

        
    }
//    NODE* ENQUEUE(NODE* NEW_NODE_0, NODE* NEW_NODE_1) {
//        return
//    }
    void DISPLAY(NODE* PQ) {
        
    }
    std::string ACCESS();
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
int main() {
    GET_DATA SOURCE;
//    for (auto i : SOURCE.ENCRYPTED_CONTAINER()) { std::cout << "'" << i.first << "' " << i.second << "\n"; }
    QUEUE_TREE T;
    return 0;
}
