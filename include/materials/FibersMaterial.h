#ifndef FIBERSMATERIAL_H
#define FIBERSMATERIAL_H

#include "Material.h"

class FibersMaterial;

template <>
InputParameters validParams<FibersMaterial>();

/**
 * TensorMechanicsMaterial handles a fully anisotropic, single-crystal
 * material's elastic
 * constants.  It takes all 21 independent stiffness tensor inputs, or only 9,
 * depending on the
 * boolean input value given.  This can be extended or simplified to specify
 * HCP, monoclinic,
 * cubic, etc as needed.
 */
class FibersMaterial : public Material
{
public:
    
    FibersMaterial(const InputParameters &parameters);
    virtual void computeQpProperties()=0;
    virtual void computeQpTensorProperties();

protected:
  /// Material property base name to allow for multiple TensorMechanicsMaterial
  /// to coexist in the same simulation
  //    std::string _base_name;

  MaterialProperty<RealVectorValue> &_fiberDirection;
  MaterialProperty<RealVectorValue> &_sheetDirection;
  MaterialProperty<RealVectorValue> &_normalDirection;
  MaterialProperty<RealTensorValue> &_fXf;
  MaterialProperty<RealTensorValue> &_sXs;
  MaterialProperty<RealTensorValue> &_fXs;
  MaterialProperty<RealTensorValue> &_nXn;
  //MaterialProperty<RealTensorValue> &_fXn;
  //MaterialProperty<RealTensorValue> &_sXn;
  MaterialProperty<RealTensorValue> &_rotationTensor;
};

#endif
