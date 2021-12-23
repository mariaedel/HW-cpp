#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main() {

    ifstream file("in.txt");

    float xn;
    float yn;

    float x0;
    float y0;
    
    file >> x0 >> y0;

    float final_x_right = 0;
    float final_y_right = 0;

    float final_x_left = 0;
    float final_y_left = 0;

    float cos_r = 1;
    float cos_l = 1;
    float dist_l = 0;
    float dist_r = 0;

    float new_cos;

    while (!file.eof()) {

        file >> xn >> yn;
        new_cos = (xn * x0 + yn * y0) / (sqrt((xn * xn + yn * yn) * (x0 * x0 + y0 * y0)));
        
        if ((x0 * yn - y0 * xn) > 0) {
            if (new_cos < cos_l) {
                cos_l = new_cos; 
                final_x_left = xn;
                final_y_left = yn;
            } else if (cos_l == new_cos) {
                float new_dist = sqrt(xn * xn + yn * yn);
                float prev_dist = sqrt(final_x_left * final_x_left + final_y_left * final_y_left);
                if (new_dist > prev_dist) {
                    cos_l = new_cos;
                    final_x_left = xn;
                    final_y_left = yn;
                }
            }
        } else {
            if (cos_r > new_cos) {
                cos_r = new_cos;
                final_x_right = xn;
                final_y_right = yn;
            }
            else if (cos_r == new_cos) {
                float new_dist = sqrt(xn * xn + yn * yn);
                float prev_dist = sqrt(final_x_right * final_x_right + final_y_right * final_y_right);
                if (new_dist > prev_dist) {
                    cos_r = new_cos;
                    final_x_right = xn;
                    final_y_right = yn;
                }
            } 
        }
   
    }

    cout << "Leftmost: " << final_x_left << ' ' << final_y_left << endl;
    cout << "Rightmost: " << final_x_right << ' ' << final_y_right << endl << endl;
    return 0;
}
