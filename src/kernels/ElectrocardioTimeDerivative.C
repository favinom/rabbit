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
/* Kernel to compute the time derivative of the potential.      */
/****************************************************************/

#include "ElectrocardioTimeDerivative.h"
//#include "ElasticMaterial.h"

template <>
InputParameters validParams<ElectrocardioTimeDerivative>() {

  //inherit the parameters of the TimeDerivative:
  InputParameters params = validParams<TimeDerivative>();

  params.addRequiredParam<Real>("capacitance","Capacitance of membrane in muF/cm^2. Default: 1.0");
  return params;
}

ElectrocardioTimeDerivative::ElectrocardioTimeDerivative(const InputParameters & parameters) :

    //inherit the parameters of the TimeDerivative:
    TimeDerivative(parameters),

    //inherit some material properties:
     //_J(getMaterialProperty<Real>("deformationDeterminant")),

     //we can specify the capacitance. Default value=1:
     _capacitance(getParam<Real>("capacitance"))
     {}

Real ElectrocardioTimeDerivative::computeQpResidual() {

  //computes the residual in the reference configuration through TimeDerivative::computeQpResidual()
  return _capacitance * TimeDerivative::computeQpResidual();

}

Real ElectrocardioTimeDerivative::computeQpJacobian() {

  //computes the jacobian in the reference configuration through TimeDerivative::computeQpJacobian()
  return  _capacitance * TimeDerivative::computeQpJacobian();
}
