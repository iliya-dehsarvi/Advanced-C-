#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class DICTIONARY {
    int _SIZE;
    std::vector<int> KEYS;
    std::vector<std::string> VALUES;
    int _GET_INDEX(int KEY) {
        auto LOCATION = std::find(KEYS.begin(), KEYS.end(), KEY);
        if (LOCATION!=end(KEYS)) { return std::distance(KEYS.begin(), LOCATION); }
        return -1;
    }
public:
    DICTIONARY() { _SIZE = 0; }
    int SIZE() { return _SIZE; }
    std::string & operator [] (int KEY) {
        int INDEX = _GET_INDEX(KEY);
        if (INDEX!=-1) { return VALUES[INDEX]; }
        KEYS.push_back(KEY);
        VALUES.push_back("");
        _SIZE++;
        return VALUES[VALUES.size()-1];
    }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class GET_DATA {
    std::vector<int> _DATA_CONTAINER;
public:
    GET_DATA (std::string FILENAME="Encrypted.txt") {
        std::fstream ENCRYPTED_FILE;
        ENCRYPTED_FILE.open(FILENAME);
        std::string DATA = "";
        if (!ENCRYPTED_FILE) {
            std::cout << "Unable to open the file "+FILENAME+"\n";
            exit(1);
        }
        while (!ENCRYPTED_FILE.eof()) {
            std::getline(ENCRYPTED_FILE, DATA, ',');
            try { _DATA_CONTAINER.push_back(std::stoi(DATA)); }
            catch (const std::exception& ERR) { break; }
        }
        ENCRYPTED_FILE.close();
    }
    std::vector<int> DATA_CONTAINER() { return _DATA_CONTAINER; }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
class DECRYPTION {
    DICTIONARY DICT;
    const int DICT_SIZE=256;
    std::string DECRYPTED_DATA;
    void _DECRYPT(std::vector<int> ENCRYPTED_DATA) {
        std::string ENTERY;
        std::string STR="";
        std::string WORD = STR+static_cast<char>(ENCRYPTED_DATA[0]);
        DECRYPTED_DATA = WORD;
        int KEY;
        for (int I=1; I<ENCRYPTED_DATA.size(); I++) {
            KEY=ENCRYPTED_DATA[I];
            ENTERY = "";
            if (KEY>=0 && KEY<DICT.SIZE()) { ENTERY += DICT[KEY]; }
            else if (KEY == DICT.SIZE()) { ENTERY += WORD+WORD[0]; }
            DECRYPTED_DATA += ENTERY;
            DICT[DICT.SIZE()]=WORD+ENTERY[0];
            WORD=ENTERY;
        }
    }
public:
    DECRYPTION(std::string FILENAME="Encrypted.txt") {
        GET_DATA SOURCE(FILENAME);
        std::string VALUE;
        for (int I=0; I<DICT_SIZE; I++) {
            VALUE="";
            DICT[I]=VALUE+static_cast<char>(I);
        }
        _DECRYPT(SOURCE.DATA_CONTAINER());
    }
    void DISPLAY() { std::cout << std::endl << DECRYPTED_DATA << "\n\n"; }
    std::string ACCESS() { return DECRYPTED_DATA; }
};
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
int main() {
    DECRYPTION TASK;
    TASK.DISPLAY();
    return 0;
}
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
