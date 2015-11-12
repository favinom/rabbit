#ifndef FIXEDROTATION_H
#define FIXEDROTATION_H

#include "FibersMaterial.h"

class FixedRotation;

template <>
InputParameters validParams<FixedRotation>();

/**
 * TensorMechanicsMaterial handles a fully anisotropic, single-crystal
 * material's elastic
 * constants.  It takes all 21 independent stiffness tensor inputs, or only 9,
 * depending on the
 * boolean input value given.  This can be extended or simplified to specify
 * HCP, monoclinic,
 * cubic, etc as needed.
 */
class FixedRotation : public FibersMaterial
{
public:
  FixedRotation(const InputParameters &parameters);

  void computeQpProperties();
    
    RealVectorValue E_fiber;
    RealVectorValue E_sheet;
    RealVectorValue E_normal;
    
    
};

#endif
