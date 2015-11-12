#include "FixedRotation.h"


template <>
InputParameters validParams<FixedRotation>() {
  InputParameters params = validParams<FibersMaterial>();
  params.addRequiredParam<RealVectorValue>("E_fiber","E_fiber");
  params.addRequiredParam<RealVectorValue>("E_sheet","E_sheet");
  return params;
}

FixedRotation::FixedRotation(const InputParameters & parameters) :
FibersMaterial(parameters),
E_fiber(getParam<RealVectorValue>("E_fiber")),
E_sheet(getParam<RealVectorValue>("E_sheet"))
{
  Real norm_E_fiber=
    std::sqrt(E_fiber(0) * E_fiber(0) + E_fiber(1) * E_fiber(1) + E_fiber(2) * E_fiber(2));

  for (int i = 0; i < 3; ++i)
    E_fiber(i) = E_fiber(i) / norm_E_fiber;
  
  E_sheet=E_sheet-E_fiber.contract(E_sheet)*E_fiber;

  Real norm_E_sheet=
    std::sqrt(E_sheet(0) * E_sheet(0) + E_sheet(1) * E_sheet(1) + E_sheet(2) * E_sheet(2));

  for (int i = 0; i < 3; ++i)
    E_sheet(i) = E_sheet(i) / norm_E_sheet;

  E_normal = E_fiber.cross(E_sheet);


//std::cout<<"E_fiber="<<E_fiber<<std::endl;
//std::cout<<"E_sheet="<<E_sheet<<std::endl;
//std::cout<<"E_normal="<<E_normal<<std::endl;
}

void FixedRotation::computeQpProperties()
{

  // Someone has to test is "=" operator between RealVectorValue is defined 
  for (unsigned i=0; i<3; ++i)
  {
    _fiberDirection[_qp](i)=E_fiber(i);
    _sheetDirection[_qp](i)=E_sheet(i);
    _normalDirection[_qp](i)=E_normal(i);
  }

  computeQpTensorProperties();

}