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

#ifndef ELECTROCARDIOTIMEDERIVATIVE_H
#define ELECTROCARDIOTIMEDERIVATIVE_H

#include "TimeDerivative.h"
//#include "ElasticMaterial.h"


class ElectrocardioTimeDerivative;

template <>
InputParameters validParams<ElectrocardioTimeDerivative>();

class ElectrocardioTimeDerivative : public TimeDerivative
{
public:
  ElectrocardioTimeDerivative(const InputParameters &parameters);

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
    
   //const MaterialProperty<Real> &_J;
  
  Real _capacitance;
    
};

#endif
