#ifndef RABBITAPP_H
#define RABBITAPP_H

#include "MooseApp.h"

class RabbitApp;

template<>
InputParameters validParams<RabbitApp>();

class RabbitApp : public MooseApp
{
public:
  RabbitApp(InputParameters parameters);
  virtual ~RabbitApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* RABBITAPP_H */
