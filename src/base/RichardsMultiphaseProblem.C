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
    _lower_var_num(0),
    upsol(false)
{}

RichardsMultiphaseProblem::~RichardsMultiphaseProblem()
{
  delete ionicmodel;
}

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

  int N = std::distance(_mesh.getMesh().local_nodes_begin(),
      _mesh.getMesh().local_nodes_end());
  ionicmodel = new BernusModel(N,true,true);
  int counter = 0;
  upsol = true;

  FEProblem::initialSetup();
}

void
RichardsMultiphaseProblem::timestepSetup()
{
    FEProblem::timestepSetup();

    unsigned int sys_num = getNonlinearSystem().number();
    NumericVector<Number>& sol = _nl.solutionOld();
    MeshBase::node_iterator nit = _mesh.getMesh().local_nodes_begin();
    const MeshBase::node_iterator nend = _mesh.getMesh().local_nodes_end();

    std::vector<dof_id_type> dofs;
    for ( ; nit != nend; ++nit)
    {
        const Node & node = *(*nit);
        dofs.push_back(node.dof_number(sys_num, _bounded_var_num, 0));
    }
    std::vector<double> v(dofs.size());
    sol.get(dofs,v);

    if (counter==0)
        ionicmodel->initstate(&v[0]);
    ionicmodel->modelstep(&v[0],_dt);
    counter++;

    // assign back the values
    for (int i=0;i<v.size();++i)
        sol.set(dofs[i],v[i]);

    sol.close();
}

bool
RichardsMultiphaseProblem::shouldUpdateSolution()
{
  return false;
}

bool
RichardsMultiphaseProblem::updateSolution(NumericVector<Number>& vec_solution, NumericVector<Number>& ghosted_solution)
{
  return false;
}
