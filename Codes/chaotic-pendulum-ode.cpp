#include <fstream>
#include <iostream>
#include <valarray>
#include <cmath>
#include <string>

#include "rk4.h"

typedef std::valarray<double> state_t;

void fderiv(const state_t & s, state_t & dsdt, double time);
void write(const state_t & s, double time);

const double L1 = 1.0; // Lenght of the first rope
const double L2 = 1.0; // Lenght of the second rope
const double M1 = 1.0; // Mass of the first rope
const double M2 = 1.0; // Mass of the second rope
const double G = 9.81; // Gravity of the Earth

int main(int argc, char **argv) {
  // State vector
  // s = [theta1, omega1, thetha2, omega2]
    state_t s(4);
  
  // Inicial conditions
    s[0] = 30.0 * M_PI / 180.0; // rad
    s[1] = 0.0;  // rad/s
    s[2] = 30.0 * M_PI / 180.0; // rad
    s[3] = 0.0;  // rad/s

  // Evolve the system
    integrate_rk4(fderiv, s, 0.0, 5.0, 0.001, write);

  return 0;
}

void fderiv(const state_t & s, state_t & dsdt, double time)
{
    double num1 = -G * (2.0 * M1 + M2) * std::sin(s[0]) - M2 * G * std::sin(s[0] - 2.0 * s[2]) - 2.0 * std::sin(s[0] - s[2]) * M2 * (std::pow(s[3], 2.0) * L2 + std::pow(s[1], 2) * L1 * std::cos(s[0] - s[2]));
    double den1 = L1 * (2.0 * M1 + M2 - M2 * std::cos(2.0 * s[0] - 2.0 * s[2]));
    double num2 = 2.0 * std::sin(s[0] - s[2]) * (std::pow(s[1], 2.0) * L1 * (M1 + M2) + G * (M1 + M2) * std::cos(s[0]) + std::pow(s[3], 2.0) * L2 * M2 * std::cos(s[0] - s[2]));
    double den2 = L2 * (2.0 * M1 + M2 - M2 * std::cos(2.0 * s[0] - 2.0 * s[2]));
    
    dsdt[0] = s[1];
    dsdt[1] = num1 / den1;
    dsdt[2] = s[3];
    dsdt[3] = num2 / den2;
  }

void write(const state_t & s, double time)
{
    std::cout << time << "\t"
              << s[0] << "\t" << s[1] << "\t" // Results regarding theta1 and omega1
              << s[2] << "\t" << s[3] << "\n";// Results regarding theta2 and omega2
}
