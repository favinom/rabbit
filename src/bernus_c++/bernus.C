#include "bernus.h"
#include <vector>

bernus::bernus() : Iionmodel() {
  // nothing to do here
}

// destructor
bernus::~bernus() {
  // nothing to do, array pointers have to be deleted externally.
}

// initializes all gates to their steady-state value for V = -90.272 mV
void bernus::initialize(std::vector<double>* gates) {
  // Resize both vectors to number of gating variables in the Bernus model.
  (*gates).resize(bernus::ngates);

  // Resting potential of Bernus model
  double const Vrest = -90.272;

  (*gates)[m_gate] = bnf.alpha_m(Vrest) / (bnf.alpha_m(Vrest) + bnf.beta_m(Vrest));
  (*gates)[v_gate] = bnf.v_inf(Vrest);
  (*gates)[f_gate] = bnf.alpha_f(Vrest) / (bnf.alpha_f(Vrest) + bnf.beta_f(Vrest));
  (*gates)[to_gate] = bnf.alpha_to(Vrest) / (bnf.alpha_to(Vrest) + bnf.beta_to(Vrest));
  (*gates)[x_gate] = bnf.x_inf(Vrest);
}
