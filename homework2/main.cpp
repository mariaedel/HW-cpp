#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

template <typename T> 
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

const float g = 9.81;

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

    float h0;
    file >> h0;
    
    float vx0, vy0;
    file >> vx0 >> vy0;

    float xi, hi;
    vector<float> xis;
    vector<float> his;

    float y = h0, t = 0, x = 0.0, vx = vx0, vy = vy0;

    int current_n = 0;

    while (file >> xi >> hi) {
        xis.push_back(xi);
        his.push_back(hi);       
    }

    // finding current section
    while (x > xis[current_n]) {
        current_n++;
    }

    while (true) {
        int dir = sgn(vx);
        int next = (dir > 0) ? current_n : current_n - 1;

        if (next < 0 || next >= xis.size()) {
            cout << current_n;
            return 0;
        }

        float dt = (xis[next] - x) / vx;

        y = y + vy * dt - g * dt * dt / 2;

        if (y <= 0.0) {
            cout << current_n;
            return 0;
        } 
        else if (y >= his[next]) {
            x = xis[next];            
            current_n += dir;
        } 
        else if (y < his[next]) {
            vx = -vx;  
            x = xis[next];
            
        }
        vy = vy - g * dt;
        t += dt;

    }    
    return 0;
}

