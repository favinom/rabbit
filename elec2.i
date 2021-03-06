[Mesh]
# file = '../../meshes/Ventricles/cm/LV_ellipsoid_tet_Z.e'
# block_id = '1'
# boundary_id = '101 102 103'
# boundary_name = 'ss_endo ss_epi ss_base'
# uniform_refine = 0
 type = GeneratedMesh
 dim = 3
 nx = 40
 ny = 14
 nz = 6
 xmin = 0.0
 xmax = 2.0
 ymin = 0.0
 ymax = 0.7
 zmin = 0.0
 zmax = 0.3
# elem_type = HEX27
 []

# [Problem]
# type = RichardsMultiphaseProblem
# bounded_var = temp
# lower_var = temp
# []
 
[Variables]
 [./potential]  order=FIRST  family=LAGRANGE
    [./InitialCondition]
#type = RandomIC
        type = ConstantIC
        value = -85.23
    [../]
 [../]
[]
 
[AuxVariables]
  [./temp]    order=FIRST     family = LAGRANGE  [../]
#  [./disp_y]    order=FIRST     family = LAGRANGE  [../]
#  [./disp_z]    order=FIRST     family = LAGRANGE  [../]
#  [./thickness_parameter_from_up] order = FIRST family = LAGRANGE [../]
[]

[Kernels]
[./euler]
 type = ElectrocardioTimeDerivative
 capacitance = 1.0
 variable = potential
[../]

[./diff]
 type = ElectrocardioMonodomainDiffusion
 variable = potential
 surface_to_volume = 1400.0
[../]

 [./forcing]
 type = UserForcingFunction
 variable = potential
 function = forcing_func
 [../]

[./NonLinearReaction]
 type = NonLinearReaction
 variable = potential
 [../]
 
#[./ecforcing]
# type = DeformedElectrocardioForcing
# variable = potential
# forcing_function = ElectrocardioForcing_function
#[../]

[]

#[AuxKernels]
# [./prova]
# type = NodalPostProcessorAux variable = temp potential = potential
#[../]
# []
 
[Functions]
  [./forcing_func]
    type = ParsedFunction
    value = '35.714285*(x<=0.15)*(y<=0.15)*(z<=0.15)*(t<=2.0)'
  [../]
[]

[Materials]
 [./FTE]
 block =0
 type =FixedRotation
 E_fiber = '1 0 0'
 E_sheet = '0 1 0'
 [../]

 [./conductivity]
 type = MonodomainConductivity
 conductivities = '1.3341 0.1760 0.1760'  ## check units 0.1760
 block = 0
 [../]
 
 [./FN]
 block =0
# type =Electrocardio
 type = FN
 vmem = -85.23
 potential = potential
 [../]

[]

# [Preconditioning]
# [./SMP]
#type = FDP
#type = PBP
# type = SMP
# full = true
# [../]
# []
 
[Executioner]

  type=Transient
  solve_type=PJFNK
 
#line_search = 'none'
 
 petsc_options_iname=' -ksp_type -pc_type -pc_factor_shift_type -pc_factor_mat_solver_package '
 petsc_options_value='   preonly   lu       NONZERO               mumps         '
 
# petsc_options_iname='-snes_type -ksp_type -pc_type -pc_factor_shift_type '
# petsc_options_value=' newtonls   preonly   lu       NONZERO'

#nl_rel_tol=0.999999999
#  nl_abs_tol=0.9
#  nl_rel_step_tol=1e1
#  nl_abs_step_tol=1e1

#  l_tol=1.e-6
#  l_max_its=30
  #l_abs_step_tol=1.e-12
#nl_max_its=10

  start_time=   0.0
  end_time  =   100.0
  dtmin     =   0.25
  dtmax     =   0.5
[]


[Outputs]

#[./console]
#   type=Console
#   perf_log=false
#   output_on = 'initial timestep_begin timestep_end'
#   [../]

   [./out]
  type=Exodus
   output_initial = true
  [../]
 []
