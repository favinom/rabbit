#ifndef NodalPostProcessorAux_H
#define NodalPostProcessorAux_H

#include "AuxKernel.h"

class NodalPostProcessorAux;

template<>
InputParameters validParams<NodalPostProcessorAux>();

class NodalPostProcessorAux : public AuxKernel
{
public:
  NodalPostProcessorAux( InputParameters const & parameters );
    
protected:
  virtual Real computeValue();

     unsigned _component;
    
    VariableValue & _potential;

    Real *ciao;
    unsigned counter;
    
};

#endif // ELASTICENERGYAUX_H
