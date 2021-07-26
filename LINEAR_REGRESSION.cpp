#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <regex>
#include <cmath>
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
g++ --std=c++11 LINEAR_REGRESSION.cpp -o LR && ./LR
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  */
class GRAPHER {
    std::vector<std::vector<std::string>> _GRAPH_MATRIX;
    int _WIDTH;
    int _HEIGHT;
    int _FIRST_X;
    int _FIRST_Y;
    bool _FIRST_POINT=true;
public:
    GRAPHER(const int PASSED_WIDTH=80, const int PASSED_HEIGHT=20) {
        _WIDTH=PASSED_WIDTH;
        _HEIGHT=PASSED_HEIGHT;
        std::vector<std::vector<std::string>> GRAPH_MATRIX(PASSED_HEIGHT, std::vector<std::string>(PASSED_WIDTH, " "));
        _GRAPH_MATRIX = GRAPH_MATRIX;
    }
    int WIDTH() { return _WIDTH; }
    int HEIGHT() { return _HEIGHT; }
    void PLOT_POINT(float X, float Y) {
        try { _GRAPH_MATRIX[Y][X]="•"; }
        catch (...) { return; }
    }
    void DISPLAY() {
        std::string LINE="";
        for (int INDEX=0; INDEX<_WIDTH; INDEX++) { LINE+='_'; }
        std::cout << LINE << "\n";
        for (int ROW=0; ROW<_HEIGHT; ROW++) {
            for (int COLUMN=0; COLUMN<_WIDTH; COLUMN++) { std::cout << _GRAPH_MATRIX[ROW][COLUMN]; }
            std::cout << "|\n";
        } std::cout << LINE << "|\n";
    }
};
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
class LINEAR_REGRESSION {
    GRAPHER _GRAPH;
    float _EQUATION(int X) { return _Y_INTERCEPT+(_SLOPE*(-1))*X; }
    std::vector<std::vector<float>> _DATA;
    float _SLOPE;
    float _Y_INTERCEPT;
    bool _ADD_DATA(std::string TO_BE_PARSED) {
        std::regex REGEX("(.+),(.+)");
        std::smatch MATCHES;
        if (std::regex_match(TO_BE_PARSED, MATCHES, REGEX)) {
            try {
                _DATA.push_back({std::stof(MATCHES[1]), std::stof(MATCHES[2])});
                return true;
            } catch (...) { return false; }
        } return false;
    }
    void _SET_DATA(std::string FILENAME) {
        std::fstream CSV;
        std::string LINE("");
        CSV.open(FILENAME);
        while (CSV >> LINE) { _ADD_DATA(LINE); }
        CSV.close();
    }
public:
    LINEAR_REGRESSION(GRAPHER GRAPH, std::string FILENAME="Cos.csv") {
        _GRAPH=GRAPH;
        _SET_DATA(FILENAME);
        auto X_MAX=_DATA[0][0];
        auto X_MIN=_DATA[0][0];
        auto Y_MAX=_DATA[0][1];
        auto Y_MIN=_DATA[0][1];
        for (auto DATA: _DATA) {
            if (DATA[0]>X_MAX) { X_MAX=DATA[0]; }
            if (DATA[0]<X_MIN) { X_MAX=DATA[0]; }
            if (DATA[1]>Y_MAX) { Y_MAX=DATA[1]; }
            if (DATA[1]<Y_MIN) { Y_MIN=DATA[1]; }
        }
        ARANGE_AND_PLOT_DATA(X_MAX, X_MIN, Y_MAX, Y_MIN);
        for (int X=0; X<_GRAPH.WIDTH()-5; X++) {
            if (_EQUATION(X)<_GRAPH.HEIGHT() && _EQUATION(X)>0) { _GRAPH.PLOT_POINT(X, _EQUATION(X)); }
        }
    }
    void ARANGE_AND_PLOT_DATA(float X_MAX,float X_MIN,float Y_MAX,float Y_MIN) {
        std::vector<float> SUMS(4,0);
        bool NEGATIVE_X_MIN=false;
        bool NEGATIVE_Y_MIN=false;
        if (X_MIN<0) { NEGATIVE_X_MIN=true; }
        if (Y_MIN<0) { NEGATIVE_Y_MIN=true; }
        auto X_DATA_RANGE=X_MAX-X_MIN;
        auto Y_DATA_RANGE=Y_MAX-Y_MIN;
        for (auto DATA: _DATA) {
            auto X=DATA[0];
            auto Y=DATA[1];
            if (NEGATIVE_X_MIN) { X+=(X_MIN*(-1)); }
            if (NEGATIVE_Y_MIN) { Y+=(Y_MIN*(-1)); }
            X=((_GRAPH.WIDTH()-1)*X)/X_DATA_RANGE;
            Y=_GRAPH.HEIGHT()-1-(((_GRAPH.HEIGHT()-1)*Y)/Y_DATA_RANGE);
            _GRAPH.PLOT_POINT(X, Y);
            SUMS[0]+=X;
            SUMS[1]+=std::pow(X,2);
            SUMS[2]+=Y;
            SUMS[3]+=Y*X;
        }
        _SLOPE=(_DATA.size()*SUMS[3]-SUMS[0]*SUMS[2])/(_DATA.size()*SUMS[1]-std::pow(SUMS[0],2));
        _Y_INTERCEPT=(SUMS[2]-_Y_INTERCEPT*SUMS[0])/_DATA.size();
        std::cout << "Y = " << _Y_INTERCEPT << " + (" << _SLOPE << ") * X\n";
    }
    GRAPHER GRAPH() { return _GRAPH; }
    std::vector<std::vector<int>> DATA();
};
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
int main() {
    GRAPHER GRAPH(100, 50);
    LINEAR_REGRESSION RG(GRAPH);
    RG.GRAPH().DISPLAY();
    return 0;
}



