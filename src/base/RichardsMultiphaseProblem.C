/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/


#include "RichardsMultiphaseProblem.h"

//#include "NonlinearSystem.h"

template<>
InputParameters validParams<RichardsMultiphaseProblem>()
{
  InputParameters params = validParams<FEProblem>();
  params.addRequiredParam<NonlinearVariableName>("bounded_var", "Variable whose value will be constrained to be greater than lower_var");
  params.addRequiredParam<NonlinearVariableName>("lower_var", "Variable that acts as a lower bound to bounded_var.  It will not be constrained during the solution procedure");
  return params;
}


RichardsMultiphaseProblem::RichardsMultiphaseProblem(const InputParameters & params) :
    FEProblem(params),
    // in the following have to get the names of the variables, and then find their numbers in initialSetup,
    // as their numbers won't be defined at the moment of instantiation of this class
    _bounded_var_name(params.get<NonlinearVariableName>("bounded_var")),
    _lower_var_name(params.get<NonlinearVariableName>("lower_var")),
    _bounded_var_num(0),
    _lower_var_num(0)
{}

RichardsMultiphaseProblem::~RichardsMultiphaseProblem()
{}

void
RichardsMultiphaseProblem::initialSetup()
{
  // the first argument to getVariable is threadID - i hope the following always works
  unsigned int tid = 0;
  MooseVariable & bounded = getVariable(tid, _bounded_var_name);
  MooseVariable & lower = getVariable(tid, _lower_var_name);

  // some checks
  if (!bounded.isNodal() || !lower.isNodal())
    mooseError("Both the bounded and lower variables must be nodal variables in RichardsMultiphaseProblem");
  if (bounded.feType().family != lower.feType().family)
    mooseError("Both the bounded and lower variables must belong to the same element family (eg LAGRANGE) in RichardsMultiphaseProblem");
  if (bounded.feType().order != lower.feType().order)
    mooseError("Both the bounded and lower variables must have the same order (eg FIRST) in RichardsMultiphaseProblem");

  // extract the required info
  _bounded_var_num = bounded.number();
  _lower_var_num = lower.number();

  FEProblem::initialSetup();
}


bool
RichardsMultiphaseProblem::shouldUpdateSolution()
{
  return true;
}

bool
RichardsMultiphaseProblem::updateSolution(NumericVector<Number>& vec_solution, NumericVector<Number>& ghosted_solution)
{
  std::cout<<"ciao, chiamt odopo il solver\n";
  bool updatedSolution = false;  // this gets set to true if we needed to enforce the bound at any node

  unsigned int sys_num = getNonlinearSystem().number();

  // For parallel procs i believe that i have to use local_nodes_begin, rather than just nodes_begin
  // _mesh comes from SystemBase (_mesh = getNonlinearSystem().subproblem().mesh(), and subproblem is this object)
  MeshBase::node_iterator nit = _mesh.getMesh().local_nodes_begin();
  const MeshBase::node_iterator nend = _mesh.getMesh().local_nodes_end();

  std::vector<dof_id_type> dofs;
    for ( ; nit != nend; ++nit)
    {
        const Node & node = *(*nit);
        dofs.push_back(node.dof_number(sys_num, _bounded_var_num, 0));
    }
    std::vector<double> v(dofs.size());
    vec_solution.get(dofs,v);
    for (int i=0;i<v.size();++i)
    {
        //Real u = (v[i]+85.23)/100.0;
        //Real _Iion =8.0*u*(u-0.15)*(u-1.0);

        Real _Iion=1.4e-5*(v[i]-30.0)*(v[i]+85.23)*(v[i]+57.6);
        
        v[i]=v[i]+0.2*_Iion;
    }
    for (int i=0;i<v.size();++i)
        vec_solution.set(dofs[i],v[i]);
    //vec_solution.set(dofs,v);
    
    //int nn=
    //std::copy(&vec_solution[0],&vec_solution[0]+nn,miov.begin());
    
  //for (auto v: )
      vec_solution.close();
    
      return false;
    
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

      vec_solution.set(dofs[0], soln[0]); // set the bounded variable equal to the lower value
      updatedSolution = true;
//    }

  }

  // The above vec_solution.set calls potentially added "set" commands to a queue
  // The following actions the queue (doing MPI commands if necessary), so
  // vec_solution will actually be modified by this following command
  vec_solution.close();

  // if any proc updated the solution, all procs will know about it
  _communicator.max(updatedSolution);

  if (updatedSolution)
  {
    ghosted_solution = vec_solution;
    ghosted_solution.close();
  }

  return updatedSolution;

}
