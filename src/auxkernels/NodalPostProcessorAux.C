#include "NodalPostProcessorAux.h"


template<>
InputParameters validParams<NodalPostProcessorAux>()
{
  InputParameters params = validParams<AuxKernel>();
    params.addRequiredCoupledVar("potential", "potential");
  return params;
}

NodalPostProcessorAux::NodalPostProcessorAux( InputParameters const & parameters ) :
AuxKernel( parameters ),
_potential(coupledValue("potential"))
{
    ciao = new Real [672];
    counter=0;
}

Real NodalPostProcessorAux::computeValue()
{


    ciao[counter]=_potential[_qp];
    counter++;
    
    if (counter ==672)
        counter = 0;
    
    //std::cout<<counter<<std::endl;
    
    //std::cout<<std::endl<<std::endl;
    return _potential[_qp];

}


