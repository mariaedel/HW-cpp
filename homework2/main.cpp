#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

const double g = 9.81;

int main(int argc, char** argv)
{
    string input;
    
    try {
        if (argc == 2)
        {
            input = argv[1];
        }
        else {
            throw invalid_argument("wrong number of arguments");
        }
    }
    catch (invalid_argument e) {
        cout << e.what() << endl;
        return 0;
    }

    ifstream file(input);

    double h0;
    file >> h0;
    
    double vx0, vy0;
    file >> vx0 >> vy0;

    double xi, hi;
    vector<double> X;
    vector<double> H;

    double y = h0, t = 0, x = 0.0, vx = vx0, vy = vy0;

    int current_n = 0;

    while (file >> xi >> hi) {
        X.push_back(xi);
        H.push_back(hi);       
    }

    // finding current section
    while (x > X[current_n]) {
        current_n++;
    }

    while (true) {

        int direction = vx / abs(vx);
        int next_n;
        
        if (direction > 0) {
            next_n = current_n;
        } else {
            next_n = current_n - 1;
        }

        if (next_n < 0 || next_n >= X.size()) {
            cout << current_n;
            return 0;
        }

        double dt = (X[next_n] - x) / vx;

        y = y + vy * dt - g * dt * dt / 2;

        if (y <= 0) {
            cout << current_n;
            return 0;
        } 
        else if (y >= H[next_n]) {
            x = X[next_n];            
            current_n += direction;
        } 
        else {
            vx = -vx;  
            x = X[next_n];
        }
        vy = vy - g * dt;
    }    
    return 0;
}


