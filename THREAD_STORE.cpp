#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <fstream>
#include <regex>
#include <bitset>
#include <math.h>
#include <map>
#include <sstream>
#include <algorithm>
#include <queue>
#include <thread>
#include <mutex>
std::mutex GLOBAL_MUTEX;
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
g++ --std=c++11 THREAD_STORE.cpp -o THREAD_STORE && ./THREAD_STORE
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  */
 class BARCODES {
    std::vector<std::pair<std::string, std::string>> _CONTAINER;
public:
    BARCODES() {
        _CONTAINER.push_back(std::pair<std::string, std::string>(" ", "nwwnnnwnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("-", "nwnnnnwnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("+", "nwnnnwnwn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("$", "nwnwnwnnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("%", "nnnwnwnwn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("*", "nwnnwnwnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>(".", "wwnnnnwnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("/", "nwnwnnnwn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("0", "nnnwwnwnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("1", "wnnwnnnnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("2", "nnwwnnnnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("3", "wnwwnnnnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("4", "nnnwwnnnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("5", "wnnwwnnnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("6", "nnwwwnnnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("7", "nnnwnnwnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("8", "wnnwnnwnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("9", "nnwwnnwnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("A", "wnnnnwnnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("B", "nnwnnwnnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("C", "wnwnnwnnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("D", "nnnnwwnnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("E", "wnnnwwnnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("F", "nnwnwwnnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("G", "nnnnnwwnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("H", "wnnnnwwnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("I", "nnwnnwwnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("J", "nnnnwwwnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("K", "wnnnnnnww"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("L", "nnwnnnnww"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("M", "wnwnnnnwn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("N", "nnnnwnnww"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("O", "wnnnwnnwn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("P", "nnwnwnnwn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("Q", "nnnnnnwww"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("R", "wnnnnnwwn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("S", "nnwnnnwwn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("T", "nnnnwnwwn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("U", "wwnnnnnnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("V", "nwwnnnnnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("W", "wwwnnnnnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("X", "nwnnwnnnw"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("Y", "wwnnwnnnn"));
        _CONTAINER.push_back(std::pair<std::string, std::string>("Z", "nwwnwnnnn"));
    }
    std::string operator [] (std::string KEY) {
        std::string NEW_KEY = "";
        for (auto CHAR: KEY) {
            if (CHAR=='0') { NEW_KEY+='n'; }
            else { NEW_KEY+='w'; }
        }
        for (auto CHAR: _CONTAINER) {
            if (CHAR.second==NEW_KEY) { return CHAR.first; }
        } return "";
    }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class PRODUCT_INFO {
    BARCODES _CODES;
    std::string _PRODUCT_NAME(std::string PASSED_BARCODE) {
        int CHAR_COUNT=0;
        std::string CHAR_HOLDER="";
        std::string NEW_NAME="";
        for (char CHAR: PASSED_BARCODE) {
            CHAR_HOLDER+=CHAR;
            CHAR_COUNT++;
            if (CHAR_COUNT==9) {
                NEW_NAME+=_CODES[CHAR_HOLDER];
                CHAR_HOLDER="";
                CHAR_COUNT=0;
            }
        } return NEW_NAME;
    }
public:
    std::string _BARCODE;
    std::string _NAME;
    double _PRICE;
    PRODUCT_INFO(std::string PASSED_BARCODE, double PASSED_PRICE) {
        _NAME = _PRODUCT_NAME(PASSED_BARCODE);
        _BARCODE = PASSED_BARCODE;
        _PRICE = PASSED_PRICE;
    }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class PRODUCT_DATABASE {
    std::vector<PRODUCT_INFO> _DATABASE;
public:
    void INSERT(PRODUCT_INFO NEW_PRODUCT) { _DATABASE.push_back(NEW_PRODUCT); }
    std::unique_ptr<PRODUCT_INFO> operator [] (std::string PASSED_HEX_CODE) {
        for (auto OBJECT: _DATABASE) {
            if (OBJECT._BARCODE == PASSED_HEX_CODE) {
                std::unique_ptr<PRODUCT_INFO> OBJECT_PTR(new PRODUCT_INFO(OBJECT));
                return OBJECT_PTR;
            }
        } return nullptr;
    }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class XML_PROCESSOR {
    PRODUCT_DATABASE _DB;
public:
    XML_PROCESSOR(std::string FILENAME="ProductPrice.xml") {
        std::ifstream DATABASE_FILE;
        std::regex REGEX("<.*>(.*)</.*>");
        std::string BUFFER;
        std::string NEW_BARCODE;
        int MODULE = 0;
        DATABASE_FILE.open(FILENAME);
        if (!DATABASE_FILE) {
            std::cout << "UNABLE TO OPEN THE FILE, '"+FILENAME+"'.\n";
            exit(1);
        } while (DATABASE_FILE >> BUFFER) {
            std::smatch MATCHES;
            std::regex_match(BUFFER, MATCHES, REGEX);
            if (MATCHES.size()) {
                if (MODULE%2) { NEW_BARCODE=MATCHES[1].str(); }
                else {
                    PRODUCT_INFO PRODUCT(NEW_BARCODE, std::stod(MATCHES[1].str()));
                    _DB.INSERT(PRODUCT);
                }
            } MODULE++;
        } DATABASE_FILE.close();
    }
    PRODUCT_DATABASE DB() { return _DB; }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
struct ORDER_INFO {
    std::string ID;
    std::vector<std::string> PRODUCTS;
    ORDER_INFO(std::string PASSED_ID, std::vector<std::string> PASSED_PRODUCTS) {
        ID = PASSED_ID;
        PRODUCTS = PASSED_PRODUCTS;
    }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class CUSTOMER_ORDERS {
    std::vector<ORDER_INFO> _ORDERS;
    std::string _CHECK_REGEX(std::string TO_BE_CHECKED) {
        std::regex REGEX("([A-Z0-9]+)");
        std::smatch MATCHES;
        if (std::regex_match(TO_BE_CHECKED, MATCHES, REGEX)) { return MATCHES[0]; }
        return "";
    }
public:
    CUSTOMER_ORDERS(std::string FILENAME="Carts.csv") {
        std::ifstream ORDERS_FILE;
        std::string CART_NAME;
        std::string HEX_ORDERS;
        std::string PARSER;
        ORDERS_FILE.open(FILENAME);
        if (!ORDERS_FILE) {
            std::cout << "UNABLE TO OPEN THE FILE, '"+FILENAME+"'.\n";
            exit(1);
        } while (ORDERS_FILE >> CART_NAME) {
            ORDERS_FILE >> HEX_ORDERS;
            PARSER="";
            std::vector<std::string> ITEM_LIST;
            std::smatch MATCHES;
            for (auto CHAR: HEX_ORDERS) {
                if (CHAR==',' && _CHECK_REGEX(PARSER)!="") {
                    ITEM_LIST.push_back(PARSER);
                    PARSER="";
                } else if (CHAR!=',') { PARSER+=CHAR; }
            } if (_CHECK_REGEX(PARSER)!="") { ITEM_LIST.push_back(PARSER); }
            ORDER_INFO NEW_ORDER(CART_NAME,ITEM_LIST);
            _ORDERS.push_back(NEW_ORDER);
        } ORDERS_FILE.close();
    }
    std::vector<std::deque<ORDER_INFO>> ORDERS() {
        std::vector<std::deque<ORDER_INFO>> _LANES;
        for (int _INDEX=0; _INDEX<12; _INDEX++) { _LANES.push_back(std::deque<ORDER_INFO>()); }
        for (int _INDEX=0; _INDEX<_ORDERS.size(); _INDEX++) { _LANES[_INDEX%12].push_back(_ORDERS[_INDEX]); }
        return _LANES;
    }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
struct HASH_NODE {
    std::string CART_ID;
    std::vector<PRODUCT_INFO> ITEMS;
    HASH_NODE(std::string PASSED_CART_ID, std::vector<PRODUCT_INFO> PASSED_ITEMS) {
        CART_ID=PASSED_CART_ID;
        ITEMS=PASSED_ITEMS;
    }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class HASH {
    XML_PROCESSOR _STORE_DATABASE;
    std::deque<std::thread> _LANE_THREADS;
    PRODUCT_DATABASE _DATABASE = _STORE_DATABASE.DB();
    std::vector<HASH_NODE> _TABLE;
    std::string _CONEVRT(std::string HEX_CODE) {
        std::string BARCODE = "";
        std::for_each(HEX_CODE.begin(), HEX_CODE.end(), [&BARCODE](char& CHAR) {
            if (CHAR >= 'A' && CHAR <= 'Z') {
                char NEW_CHAR = CHAR - 55;
                std::bitset<4> BITS(NEW_CHAR);
                BARCODE += BITS.to_string();
            } else {
                std::bitset<4> BITS(CHAR);
                BARCODE += BITS.to_string();
            }
        }); return BARCODE;
    }
    void _PUSH_BACK(ORDER_INFO ORDER) {
        std::vector<PRODUCT_INFO> CONVERTED_ORDERS;
        for (auto DATA: ORDER.PRODUCTS) {
            auto RETURNED = _DATABASE[_CONEVRT(DATA)];
            if (RETURNED) { CONVERTED_ORDERS.push_back(*RETURNED); }
        } if (CONVERTED_ORDERS.size()==0) { return; }
        for (auto DATA: _TABLE) {
            if (DATA.CART_ID == ORDER.ID) {
                DATA.ITEMS.insert(DATA.ITEMS.end(), CONVERTED_ORDERS.begin(), CONVERTED_ORDERS.end());
                return;
            }
        }
        HASH_NODE NEW_NODE(ORDER.ID, CONVERTED_ORDERS);
        _TABLE.push_back(NEW_NODE);
    }
    void _LANE_THREAD_CALLBACK(std::deque<ORDER_INFO> LANE) {
        GLOBAL_MUTEX.lock();
        for (auto CART: LANE) { _PUSH_BACK(CART); }
        GLOBAL_MUTEX.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
public:
    std::vector<HASH_NODE> PROCESS(std::vector<std::deque<ORDER_INFO>> LANES) {
        for (auto LANE: LANES) { _LANE_THREADS.emplace_back(std::thread (&HASH::_LANE_THREAD_CALLBACK, this, LANE)); }
        for_each(_LANE_THREADS.begin(), _LANE_THREADS.end(), [](std::thread& LANE_THREAD) { LANE_THREAD.join(); });
        return _TABLE;
    }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class THREADING {
    std::vector<std::deque<HASH_NODE>> _LANES;
    std::deque<std::thread> _LANE_THREADS;
    void _DISPLAY_CART(HASH_NODE CART, int INDEX) {
        double TOTAL=0;
        std::cout << "\nLANE " << INDEX+1 << ":  " << CART.CART_ID
                  << "\n- - - - - - - - - - - - - - - --\n";
        for (auto _DATA: CART.ITEMS) {
            TOTAL+=_DATA._PRICE;
            std::cout << _DATA._NAME << ":\t\t\t$" << _DATA._PRICE << "\n";
        } std::cout << "- - - - - - - - - - - - - - - --\nTOTAL:\t\t\t$"
                    << TOTAL << "\n--------------------------------\n";
    }
    void _LANE_THREAD_CALLBACK(std::deque<HASH_NODE> LANE, int INDEX) {
        GLOBAL_MUTEX.lock();
        for (auto CART: LANE) { _DISPLAY_CART(CART, INDEX); }
        GLOBAL_MUTEX.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
public:
    THREADING(std::vector<HASH_NODE> PASSED_TABLE) {
        int INDEX=0;
        for (int _INDEX=0; _INDEX<12; _INDEX++) { _LANES.push_back(std::deque<HASH_NODE>()); }
        for (int _INDEX=0; _INDEX<PASSED_TABLE.size(); _INDEX++) { _LANES[_INDEX%12].push_back(PASSED_TABLE[_INDEX]); }
        for (auto LANE: _LANES) {
            _LANE_THREADS.emplace_back(std::thread (&THREADING::_LANE_THREAD_CALLBACK, this, LANE, INDEX));
            INDEX++;
        } for_each(_LANE_THREADS.begin(), _LANE_THREADS.end(), [](std::thread& LANE_THREAD) { LANE_THREAD.join(); });
    }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class STORE {
    XML_PROCESSOR _STORE_DATABASE;
    CUSTOMER_ORDERS _STORE_ORDERS;
    HASH _HASHED_ORDERS;
public:
    STORE() { THREADING LANES(_HASHED_ORDERS.PROCESS(_STORE_ORDERS.ORDERS())); }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
int main() {
    STORE LOCAL_STORE;
    return 0;
}


