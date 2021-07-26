#include <bitset>
#include <iostream>
#include <vector>
#include <math.h>
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
//g++ --std=c++11 BITSET.cpp -o BITSET && ./BITSET
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
void CALCULATIONS(std::vector<int> POSITIONS, char CHAR) {
    std::vector<int> POWERS;
    std::cout << "(";
    for (int i=0; i < POSITIONS.size()-1; i++) {
        POWERS.push_back(pow(2,POSITIONS[i]));
        std::cout << "2^" << POSITIONS[i] << " and ";
    }
    POWERS.push_back(pow(2,POSITIONS[POSITIONS.size()-1]));
    std::cout << "2^" << POSITIONS[POSITIONS.size()-1] << ") = ";
    for (int i=0; i < POWERS.size()-1; i++) {
        std::cout << POWERS[i] << " + ";
    } std::cout << POWERS[POSITIONS.size()-1] << " = " << static_cast<int>(CHAR) << " = '" << CHAR << "'\n";
}
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
void SET_POSITIONS(char CHAR='A') {
    std::cout << "\n";
    std::vector<int> POSITIONS;
    std::bitset<8> BITS(CHAR);
    for (int i=0; i < BITS.size(); i++) {
        if (BITS[i]%2) { POSITIONS.push_back(i); }
    }
    std::cout << CHAR << ": " << BITS << "\nBITS: ";
    for (int i=0; i<POSITIONS.size()-1; i++) {
        std::cout << POSITIONS[i] << ", ";
    } std::cout << POSITIONS[POSITIONS.size()-1];
    std::cout << "\n";
    CALCULATIONS(POSITIONS, CHAR);
    std::cout << "\n";
}
/*~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~*/
int main() {
    for (int i='A'; i<='Z'; i++) { SET_POSITIONS(i); }
    return 0;
}
