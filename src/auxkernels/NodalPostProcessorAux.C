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

 /*   NonlinearVariableName _bounded_var_name;
    NonlinearVariableName _lower_var_name;
    
    MooseVariable & bounded = getVariable(0, _bounded_var_name);
    MooseVariable & lower = getVariable(0, _lower_var_name);
    
    NumericVector<Number> & solution = _var.sys().solution();

      MeshBase::node_iterator nit = _mesh.getMesh().local_nodes_begin();
      const MeshBase::node_iterator nend = _mesh.getMesh().local_nodes_end();
    
    
    for ( ; nit != nend; ++nit)
    {
        const Node & node = *(*nit);
        
        // dofs[0] is the dof number of the bounded variable at this node
        // dofs[1] is the dof number of the lower variable at this node
        std::vector<dof_id_type> dofs(2);
        dofs[0] = node.dof_number(sys_num, _bounded_var_num, 0);
        dofs[1] = node.dof_number(sys_num, _lower_var_num, 0);
        
        // soln[0] is the value of the bounded variable at this node
        // soln[1] is the value of the lower variable at this node
        std::vector<Number> soln(2);
        vec_solution.get(dofs, soln);
        
        //std::cout<<dofs[0]<<" "<<dofs[1]<<std::endl;
        
        // do the bounding
        //    if (soln[0] < soln[1])
        //    {
        
        vec_solution.set(dofs[0], 0.0005*soln[1]*(90.0-soln[1])); // set the bounded variable equal to the lower value
        updatedSolution = true;
        //    }
        
    }

    
//    std::vector<unsigned> dof_indices = _var.dofIndices();
    
//    std::cout<<dof_indices.at(0)<<std::endl;
    
//    std::vector<unsigned> indici(672);
//    for (int i=0; i <672; ++i)
//        indici.at(i)=i;
//    
//    solution.get(indici, ciao);
//    for (int i=0; i <672; ++i)
//        std::cout<<ciao[i]<<" ";
//    std::cout<<std::endl;
    
//    _potential[_qp]=1.0;
//    std::cout<<_potential[_qp]<<std::endl;
    
    //for (int i=0; i <10; ++i)
    //    std::cout<<solution.get(i)<<std::endl;
    
//    Real V =_potential[_qp];
    
//    std::cout<<"scrivo\n";
//    _potential[_qp]=1.0; //V*(1.0-V)*(V-0.2);
    
//    ciao[counter]=_potential[_qp];
  //  counter++;
    
//    if (counter ==672)
//        counter = 0;
    
    //std::cout<<counter<<std::endl;
    
    //std::cout<<std::endl<<std::endl;*/
    return 0.0;

}


