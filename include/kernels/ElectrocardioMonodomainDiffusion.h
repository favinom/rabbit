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
/* Kernel to compute the monodomain diffusion of the potential. */
/****************************************************************/

#ifndef ELECTROCARDIOMONODOMAINDIFFUSION_H
#define ELECTROCARDIOMONODOMAINDIFFUSION_H

#include "Kernel.h"
//#include "libmesh/tensor_value.h"

class ElectrocardioMonodomainDiffusion;

template <>
InputParameters validParams<ElectrocardioMonodomainDiffusion>();

class ElectrocardioMonodomainDiffusion : public Kernel
{
public:
  ElectrocardioMonodomainDiffusion(const InputParameters &parameters);
  virtual ~ElectrocardioMonodomainDiffusion();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  Real _surface_to_volume;

  //const MaterialProperty<RealTensorValue> &_conductivity;
};

#endif
