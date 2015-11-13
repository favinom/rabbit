/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/*       HART - ICS Electromechanical simulation framework      */
/*                Prepared by Mathias Winkel,                   */
/*                  ICS, USI, 6900 Lugano                       */
/*                                                              */
/* Kernel to compute the diffusion of the potential.            */
/****************************************************************/



#include "ElectrocardioMonodomainDiffusion.h"

template <>
InputParameters validParams<ElectrocardioMonodomainDiffusion>() {

  //inherit the parameters of the Kernels:
  InputParameters params = validParams<Kernel>();

  //we need to specify the surface to volume parameter:
  params.addRequiredParam<Real>("surface_to_volume","Surface-to-volume ratio in 1/cm.");
  
  return params;
}

ElectrocardioMonodomainDiffusion::ElectrocardioMonodomainDiffusion(const InputParameters & parameters) :
    //inherit the parameters of the Kernels:
    Kernel(parameters),

    //we need to specify the surface to volume parameter:
     _surface_to_volume(getParam<Real>("surface_to_volume")),
    _conductivity(getMaterialProperty<RealTensorValue>("conductivity"))
    {}

ElectrocardioMonodomainDiffusion::~ElectrocardioMonodomainDiffusion() {}

Real ElectrocardioMonodomainDiffusion::computeQpResidual() {

//contruction of the diffusive kernel 
//and contraction with the gradient of the test function
  //return  ( _grad_test[_i][_qp] * (_conductivity[_qp] * _grad_u[_qp]) );
    return (1.0 / _surface_to_volume) *_grad_test[_i][_qp] * (_conductivity[_qp] * _grad_u[_qp]);
}

Real ElectrocardioMonodomainDiffusion::computeQpJacobian()
{
  //contruction of the diffusive kernel
  //and contraction with the gradient of the test function
  //return (1.0 / _surface_to_volume) * ( _grad_test[_i][_qp] * (_conductivity[_qp] * _grad_phi[_j][_qp])       );
    return (1.0 / _surface_to_volume) *_grad_test[_i][_qp]* (_conductivity[_qp] * _grad_phi[_j][_qp]);
}
