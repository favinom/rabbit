#include "Electrocardio.h"

template <>
InputParameters validParams<Electrocardio>() {
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar(
      "vmem",
      "Membrane potential needed as input for ion channel model. Unit: mV.");
  //! @todo: For ion channel models that need the diffusion current, have to
  //fetch the value of Imem somehow

  // we restrict output to Imem to avoid warnings about gates being impossible
  // to be used in output
  std::vector<std::string> output_properties;
  output_properties.push_back("Iion");
  params.set<std::vector<std::string> >("output_properties") =
      output_properties;
  return params;
}

Electrocardio::Electrocardio(const InputParameters & parameters) :
    Material(parameters),
    _Iion(declareProperty<Real>("Iion")),
    _gates(declareProperty<std::vector<Real> >("gates")),
    _gates_old(declarePropertyOld<std::vector<Real> >("gates")),
    // coupled variables
    _vmem(coupledValue("vmem")) {
  // Create pointer to a Bernus model object using the factory class
  _ionmodel = IionmodelFactory::factory(IionmodelFactory::BERNUS);
}

void Electrocardio::initQpStatefulProperties() {
  // initialize local gate variable vector
  _ionmodel->initialize(&(_gates[_qp]));
}

/**
 * @todo documentation
 */
void Electrocardio::computeQpProperties() {
    
  // Compute ionforcing
  _Iion[_qp] = _ionmodel->ionforcing(_vmem[_qp], &(_gates_old[_qp]));

  // Copy old values into _gates as initial value
  for (int i = 0; i < _ionmodel->get_ngates(); i++) {
    _gates[_qp][i] = _gates_old[_qp][i];
  }

  // Perform one Rush-Larsen time step to propagate forward gating variables
  _ionmodel->rush_larsen_step(_vmem[_qp], _dt, &(_gates[_qp]));

  /**
   * The mono domain equations reads
   *
   * V_t + div( G grad(V)) = I_ion(V)
   *
   * where G is a conductivity tensor, I_ion the current [unit Ampere] generated
   *by the membrane potential V [unit Volt].
   * The ODE for the membrane states S reads
   *
   * S_t = Z(V,S)
   *
   * with V being the membrane potential.
   * The dependance of I_ion on V and the evolution of the state variables S is
   *given by some membrane model, e.g. Bernus.
   *
   * In propag, the following names are used
   *
   * Vmem = V = membrane potential = variable in reaction-diffusion PDE
   * Iion = I_ion(V) = ion current = reaction term in PDE
   * Imem = diffusion current = div( G grad(V))
   * yyy  = S = cell states = variable in the ODE
   */
}
