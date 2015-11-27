[Mesh]
# file = '../../meshes/Ventricles/cm/LV_ellipsoid_tet_Z.e'
# block_id = '1'
# boundary_id = '101 102 103'
# boundary_name = 'ss_endo ss_epi ss_base'
# uniform_refine = 0
 type = GeneratedMesh
 dim = 3
 nx = 100
 ny = 4
 nz = 4
 xmin = 0.0
 xmax = 10.0
 ymin = 0.0
 ymax = 1.0
 zmin = 0.0
 zmax = 1.0
# elem_type = HEX27
 []

 [Problem]
 type = RichardsMultiphaseProblem
 bounded_var = temp
 lower_var = temp
 []
 
[Variables]
 [./potential]  order=FIRST  family=LAGRANGE
    [./InitialCondition]
        type = ConstantIC
        value = -92.0
    [../]
 [../]
[]
 
[AuxVariables]
  [./temp]    order=FIRST     family = LAGRANGE  [../]
[]

[Kernels]
[./euler]
 type = ElectrocardioTimeDerivative
 capacitance = 0.01
 variable = potential
[../]

[./diff]
 type = ElectrocardioMonodomainDiffusion
 variable = potential
 surface_to_volume = 140.0
[../]
 
 [./forcing]
 type = UserForcingFunction
 variable = potential
 function = forcing_func
 [../]

 
[]
 
[Functions]
 
 [./forcing_func]
 type = ParsedFunction
 value = '0.35*(x<=1.5)*(y<=1.5)*(z<=1.5)*(t<=2.0)'
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
 conductivities = '0.13341 0.0176 0.0176'  ## check units 0.1760
 block = 0
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
  type = Transient
  solve_type = 'NEWTON'

  [./TimeStepper]
    type = ConstantDT
    dt = 0.1
  [../]

#line_search = 'none'
 
 petsc_options_iname=' -ksp_type -pc_type -pc_factor_shift_type -pc_factor_mat_solver_package '
 petsc_options_value=' preonly    lu       NONZERO               mumps         '
 
# petsc_options_iname='-snes_type -ksp_type -pc_type -pc_factor_shift_type '
# petsc_options_value=' newtonls   preonly   lu       NONZERO'

#nl_rel_tol=0.999999999
  nl_abs_tol=1e-7
#  nl_rel_step_tol=1e1
#  nl_abs_step_tol=1e1

#  l_tol=1.e-6
#  l_max_its=30
  #l_abs_step_tol=1.e-12
#nl_max_its=10

  start_time=   0.0
  end_time  =   600.0
  dtmin     =   0.1
  dtmax     =   0.1
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
#output_on = ''
  [../]
 []
