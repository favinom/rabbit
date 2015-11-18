#include "FN.h"

template <>
InputParameters validParams<FN>() {
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("potential","potential");
  return params;
}

FN::FN(const InputParameters & parameters) :
    Material(parameters),
    _V(coupledValue("potential")),
    _Iion(declareProperty<Real>("Iion")),
_w(declareProperty<Real>("w")),
_w_old(declarePropertyOld<Real>("w"))
{}

void
FN::initQpStatefulProperties()
{
    _w[_qp] = 0.0;
}

void FN::computeQpProperties() {
      
//      _Iion[_qp] =_V[_qp]*(1.0-_V[_qp]/13.0)*(1.0-_V[_qp]/100.0); // dorian
    Real u = (_V[_qp]+85.23)/100.0;
    
    _w[_qp] = (_w_old[_qp]+_dt*0.012*u)/ (1.0+ _dt *0.012);
    
//    if (_w[_qp] < 1e-9)
//    std::cout<<_w[_qp]<<std::endl;
    
    //      _Iion[_qp] =8.0*u*(u-0.15)*(u-1.0) - 4.4*_w[_qp]; //mio
    
    _Iion[_qp] = 1.4e-5*(_V[_qp]-30.0)*(_V[_qp]+85.23)*(_V[_qp]+57.6);
    
}
