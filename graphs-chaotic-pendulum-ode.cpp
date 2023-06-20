#include <matplot/matplot.h>
#include <fstream>
#include <vector>

int main() {
    using namespace matplot;
    std::ifstream dataFile("data.txt");
    std::vector<double> t, theta1, omega1, theta2, omega2;
    double value;

    while (dataFile >> value) {
        t.push_back(value);
        dataFile >> value;
        theta1.push_back(value);
        dataFile >> value;
        omega1.push_back(value);
        dataFile >> value;
        theta2.push_back(value);
        dataFile >> value;
        omega2.push_back(value);
    }

    auto fig = gcf();
    auto ax1 = t;
    
    auto yl1 = theta1;
    auto yl2 = omega1;
    plot(t, yl1)->color(gca()->colororder()[0]);
    hold(on);
    plot(t, yl2)->color(gca()->colororder()[1]);

    auto yr1 = theta2;
    auto yr2 = omega2;
    plot(t, yr1)->use_y2(true).color(gca()->colororder()[2]);
    plot(t, yr2)->use_y2(true).color(gca()->colororder()[3]);
    hold(off);

    title("Chaotic double pendulum solution for given initial conditions");
    xlabel("Time (s)");
    ylabel("Theta (rad) | Omega (rad/s)");

    
    auto lgd = ::matplot::legend({"Theta_{1}", "Omega_{1}", "Theta_{2}", "Omega_{2}"});
    lgd->location(legend::general_alignment::topleft);
    lgd->box(false);
    
    save("graph.pdf");
    show();

    return 0;
}
