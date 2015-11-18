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

#ifndef NONLINEARREACTION_H
#define NONLINEARREACTION_H

#include "Kernel.h"

class NonLinearReaction;

template <>
InputParameters validParams<NonLinearReaction>();

class NonLinearReaction : public Kernel
{
public:
  NonLinearReaction(const InputParameters &parameters);
  virtual ~NonLinearReaction();

protected:
  virtual Real computeQpResidual();

private:
  const MaterialProperty<Real> &_Iion;
};

#endif
