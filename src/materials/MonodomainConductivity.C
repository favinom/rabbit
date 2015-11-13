#include "MonodomainConductivity.h"
//#include "TensorHelpers.h"

template <>
InputParameters validParams<MonodomainConductivity>() {
  InputParameters params = validParams<Material>();
  params.addRequiredParam<std::vector<Real> >(
      "conductivities",
      "Conductivities in fibre, sheet and sheet-normal direction. Unit: S/cm.");
  return params;
}

MonodomainConductivity::MonodomainConductivity(const InputParameters & parameters) :
    Material(parameters),
    _fXf(getMaterialProperty<RealTensorValue>("fiberOuterFiber")),
    _sXs(getMaterialProperty<RealTensorValue>("sheetOuterSheet")),
    _nXn(getMaterialProperty<RealTensorValue>("normalOuterNormal")),
    _conductivities(getParam<std::vector<Real> >("conductivities")),
    _conductivity(declareProperty<RealTensorValue>("conductivity")) {
  if (_conductivities.size() != 3)
    mooseError(
        "MonodomainConductivity: conductivities must contain exactly 3 "
        "numbers");
}

void MonodomainConductivity::computeQpProperties() {
      
      _conductivity[_qp] =
      _conductivities[0] * _fXf[_qp]+
      _conductivities[1] * _sXs[_qp] +
      _conductivities[2] * _nXn[_qp];
}
