#pragma once
#include <cmath>

template <class state_t, class deriv_t, class print_t>
void integrate_rk4(deriv_t deriv, state_t & s, double ta, double tb, double dt, print_t print)
{
  const int NSTEPS = std::lrint((tb-ta)/dt);
  state_t dsdt(s.size());

  print(s, ta);

  for (int tstep = 1; tstep < NSTEPS; tstep++) {
      double time = ta + tstep*dt;
    //s = s + dt*dsdt; // euler, assumed to use array computing
    deriv(s, dsdt, time);
    state_t k1 = dsdt;
    deriv(s + dt*k1/2, dsdt, time + dt/2);
    state_t k2 = dsdt;
    deriv(s + dt*k2/2, dsdt, time + dt/2);
    state_t k3 = dsdt;
    deriv(s + dt*k3, dsdt, time + dt);
    state_t k4 = dsdt;
    s = s + dt*(k1 + 2*k2 + 2*k3 + k4)/6;
    print(s, time);
  }
}
