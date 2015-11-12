#include "RabbitApp.h"
#include "Moose.h"
#include "AppFactory.h"
//#include "ModulesApp.h"

#include"ElectrocardioMonodomainDiffusion.h"
#include"ElectrocardioTimeDerivative.h"
#include"FixedRotation.h"

template<>
InputParameters validParams<RabbitApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

RabbitApp::RabbitApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  //ModulesApp::registerObjects(_factory);
  RabbitApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  //ModulesApp::associateSyntax(_syntax, _action_factory);
  RabbitApp::associateSyntax(_syntax, _action_factory);
}

RabbitApp::~RabbitApp()
{
}

// External entry point for dynamic application loading
extern "C" void RabbitApp__registerApps() { RabbitApp::registerApps(); }
void
RabbitApp::registerApps()
{
  registerApp(RabbitApp);
}

// External entry point for dynamic object registration
extern "C" void RabbitApp__registerObjects(Factory & factory) { RabbitApp::registerObjects(factory); }
void
RabbitApp::registerObjects(Factory & factory)
{
    registerKernel(ElectrocardioMonodomainDiffusion);
    registerKernel(ElectrocardioTimeDerivative);
    
    registerMaterial(FixedRotation);
    
}

// External entry point for dynamic syntax association
extern "C" void RabbitApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { RabbitApp::associateSyntax(syntax, action_factory); }
void
RabbitApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
