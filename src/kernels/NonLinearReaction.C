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



#include "NonLinearReaction.h"

template <>
InputParameters validParams<NonLinearReaction>() {

  //inherit the parameters of the Kernels:
  InputParameters params = validParams<Kernel>();
  return params;
}

NonLinearReaction::NonLinearReaction(const InputParameters & parameters) :
    //inherit the parameters of the Kernels:
    Kernel(parameters),
    _Iion(getMaterialProperty<Real>("Iion"))
    {}

NonLinearReaction::~NonLinearReaction() {}

Real NonLinearReaction::computeQpResidual() {

//contruction of the diffusive kernel 
//and contraction with the gradient of the test function
  //return  ( _grad_test[_i][_qp] * (_conductivity[_qp] * _grad_u[_qp]) );
    return _Iion[_qp]*_test[_i][_qp];
}
