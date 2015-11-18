#ifndef FN_H
#define FN_H

#include "Material.h"

class FN;

template <>
InputParameters validParams<FN>();
class FN : public Material
{
public:
  FN(const InputParameters &parameters);

protected:
  virtual void computeQpProperties();
  virtual void initQpStatefulProperties();
protected:
    
  VariableValue & _V;

  MaterialProperty<Real> &_Iion;
    
    MaterialProperty<Real> &_w;
    MaterialProperty<Real> &_w_old;
    
};

#endif
