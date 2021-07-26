#include <bitset>
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>
#include <queue>
#include <list>
#include <math.h>
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
g++ --std=c++11 BIT_DECRYPTION.cpp -o BIT_DECRYPTION && ./BIT_DECRYPTION
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
struct frequency {
    char _SYMB;
    float _FREQ;
    frequency(char PASSED_SYMB, float PASSED_FREQ) { _SYMB = PASSED_SYMB; _FREQ = PASSED_FREQ; }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
std::vector<frequency> TABLE = {
frequency(' ',8.0),\
frequency('!',0.0306942),\
frequency('"',0.000183067),\
frequency('#',0.00854313),\
frequency('$',0.00970255),\
frequency('%',0.00170863),\
frequency('&',0.00134249),\
frequency('\'',0.000122045),\
frequency('(',0.000427156),\
frequency(')',0.00115942),\
frequency('*',0.0241648),\
frequency('+',0.00231885),\
frequency(',',0.00323418),\
frequency('-',0.0197712),\
frequency('.',0.0316706),\
frequency('/',0.00311214),\
frequency('0',2.74381),\
frequency('1',4.35053),\
frequency('2',3.12312),\
frequency('3',2.43339),\
frequency('4',1.94265),\
frequency('5',1.88577),\
frequency('6',1.75647),\
frequency('7',1.621),\
frequency('8',1.66225),\
frequency('9',1.79558),\
frequency(':',0.00189169),\
frequency(';',0.00207476),\
frequency('<',0.000427156),\
frequency('=',0.00140351),\
frequency('>',0.000183067),\
frequency('?',0.00207476),\
frequency('@',0.0238597),\
frequency('A',0.130466),\
frequency('B',0.0806715),\
frequency('C',0.0660872),\
frequency('D',0.0698096),\
frequency('E',0.0970865),\
frequency('F',0.0417393),\
frequency('G',0.0497332),\
frequency('H',0.0544319),\
frequency('I',0.070908),\
frequency('J',0.0363083),\
frequency('K',0.0460719),\
frequency('L',0.0775594),\
frequency('M',0.0782306),\
frequency('N',0.0748134),\
frequency('O',0.0729217),\
frequency('P',0.073715),\
frequency('Q',0.0147064),\
frequency('R',0.08476),\
frequency('S',0.108132),\
frequency('T',0.0801223),\
frequency('U',0.0350268),\
frequency('V',0.0235546),\
frequency('W',0.0320367),\
frequency('X',0.0142182),\
frequency('Y',0.0255073),\
frequency('Z',0.0170252),\
frequency('[',0.0010984),\
frequency('\\',0.00115942),\
frequency(']',0.0010984),\
frequency('^',0.00195272),\
frequency('_',0.0122655),\
frequency('\'',0.00115942),\
frequency('a',7.52766),\
frequency('b',2.29145),\
frequency('c',2.57276),\
frequency('d',2.76401),\
frequency('e',7.0925),\
frequency('f',1.2476),\
frequency('g',1.85331),\
frequency('h',2.41319),\
frequency('i',4.69732),\
frequency('j',0.836677),\
frequency('k',1.96828),\
frequency('l',3.77728),\
frequency('m',2.99913),\
frequency('n',4.56899),\
frequency('o',5.17),\
frequency('p',2.45578),\
frequency('q',0.346119),\
frequency('r',4.96032),\
frequency('s',4.61079),\
frequency('t',3.87388),\
frequency('u',2.10191),\
frequency('v',0.833626),\
frequency('w',1.24492),\
frequency('x',0.573305),\
frequency('y',1.52483),\
frequency('z',0.632558),\
frequency('{',0.000122045),\
frequency('|',0.000122045),\
frequency('}',0.000122045),\
frequency('~',0.00152556)\
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
class NODE {
public:
    virtual std::string SYMB()=0;
    virtual float FREQ()=0;
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
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
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
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
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
struct NODE_COMP {
    bool operator () (NODE* LEFT, NODE* RIGHT) { return LEFT->FREQ() > RIGHT->FREQ(); }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
class QUEUE_TREE {
    std::string _DECRYPTED_MESSAGE="";
    std::priority_queue<NODE*, std::vector<NODE*>, NODE_COMP> _PRIORITY_QUEUE;
    /*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
    std::string _GET_BINARY_DATA(std::string FILENAME="Compress.bin") {
        std::string BITS_CONTAINER="";
        std::streampos SIZE;
        unsigned char *MEMBLOCK;
        std::ifstream BIN_FILE;
        BIN_FILE.open(FILENAME, std::ios::in | std::ios::binary);
        if (!BIN_FILE) {
            std::cout << "UNABLE TO OPEN THE FILE "+FILENAME+"\n";
            exit(1);
        }
        BIN_FILE.seekg(0, std::ios::end);
        SIZE = BIN_FILE.tellg();
        BIN_FILE.seekg(0, std::ios::beg);
        MEMBLOCK = new unsigned char[SIZE];
        BIN_FILE.read((char*)MEMBLOCK, SIZE);
        BIN_FILE.close();
        for (int INDEX=0; INDEX<SIZE; INDEX++) { BITS_CONTAINER+=std::bitset<8>(char(MEMBLOCK[INDEX])).to_string(); }
        delete [] MEMBLOCK;
        return BITS_CONTAINER;
    }
    /*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
    std::string _DECRYPT(NODE *ROOT) {
        NODE* NODE_PTR = ROOT;
        for (auto CHAR : _GET_BINARY_DATA()) {
            if (BRANCH *BRANCH_PTR = dynamic_cast<BRANCH*>(NODE_PTR)) {
                if (CHAR=='0') { NODE_PTR=BRANCH_PTR->LEFT(); }
                else { NODE_PTR=BRANCH_PTR->RIGHT(); }
            }
            if (LEAF *LEAF_PTR = dynamic_cast<LEAF*>(NODE_PTR)) {
                _DECRYPTED_MESSAGE+=LEAF_PTR->SYMB();
                NODE_PTR=ROOT;
            }
        } return _DECRYPTED_MESSAGE;
    }
    /*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
public:
    QUEUE_TREE(std::string BINARY_FILE="Compress.bin") {
        for (auto PAIR : TABLE) {
            std::string BUFFER;
            BUFFER.push_back(PAIR._SYMB);
            LEAF *NEW_NODE = new LEAF(BUFFER, PAIR._FREQ);
            _PRIORITY_QUEUE.push(NEW_NODE);
        }
        while (_PRIORITY_QUEUE.size()>1) {
            auto PAIR1 = _PRIORITY_QUEUE.top();
            _PRIORITY_QUEUE.pop();
            auto PAIR2 = _PRIORITY_QUEUE.top();
            _PRIORITY_QUEUE.pop();
            BRANCH* NEW_BRANCH = new BRANCH(PAIR1, PAIR2);
            _PRIORITY_QUEUE.push(NEW_BRANCH);
        }
        auto PQ = _PRIORITY_QUEUE.top();
        BRANCH *ROOT = dynamic_cast<BRANCH*>(PQ);
        _DECRYPT(ROOT);
    }
    void DISPLAY() { std::cout << "\n" << _DECRYPTED_MESSAGE << "\n\n";}
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
int main() {
    QUEUE_TREE DECRYPT;
    DECRYPT.DISPLAY();
    return 0;
}

