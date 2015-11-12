[Mesh]
# file = '../../meshes/Ventricles/cm/LV_ellipsoid_tet_Z.e'
# block_id = '1'
# boundary_id = '101 102 103'
# boundary_name = 'ss_endo ss_epi ss_base'
# uniform_refine = 0
 type = GeneratedMesh
 dim = 3
 nx = 3
 ny = 7
 nz = 20
 xmin = 0.0
 xmax = 3.0
 ymin = 0.0
 ymax = 7.0
 zmin = 0.0
 zmax = 20.0
 elem_type = HEX27
 []

[Variables]
 [./potential]  order=FIRST  family=LAGRANGE
    [./InitialCondition]
#type = RandomIC
        type = ConstantIC
        value = -82.23
    [../]
 [../]
[]

#[AuxVariables]
#  [./disp_x]    order=FIRST     family = LAGRANGE  [../]
#  [./disp_y]    order=FIRST     family = LAGRANGE  [../]
#  [./disp_z]    order=FIRST     family = LAGRANGE  [../]
#  [./thickness_parameter_from_up] order = FIRST family = LAGRANGE [../]
#[]

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
 
#[./ecforcing]
# type = DeformedElectrocardioForcing
# variable = potential
# forcing_function = ElectrocardioForcing_function
#[../]

[]

[Functions]
  [./forcing_func]
    type = ParsedFunction
    value = '50000.0*(x<1.5)*(y<1.5)*(z<1.5)*(t<2.0)'
  [../]
[]

[Materials]
 [./FTE]
 block =0
 type =FixedRotation
 E_fiber = '0 0 1'
 E_sheet = '0 1 0'
 [../]

 
#[./ElasticityPiolaTransformation]
# type = ElasticityPiolaTransformation
# block =1
# disp_x = disp_x
# disp_y = disp_y
# disp_z = disp_z
# [../]

# [./conductivity]
# type = MonodomainConductivity
# conductivities = '0.006 0.006 0.006'
# block = 1
# [../]

#[./ApplyPiolaTransformation]
# type = ApplyPiolaTransformation
# block = 1
#[../]
 
#  [./electrocardio]
#    type = Electrocardio
#    vmem = 'potential'
#    block = 1
#    outputs = all
#  [../]

[]

 [Preconditioning]
 [./SMP]
#type = FDP
#type = PBP
 type = SMP
 full = true
 [../]
 []
 
[Executioner]

  type=Transient
  solve_type=PJFNK
 
#line_search = 'none'
 
 petsc_options_iname=' -ksp_type -pc_type -pc_factor_shift_type -pc_factor_mat_solver_package '
 petsc_options_value='   preonly   lu       NONZERO               mumps         '
 
# petsc_options_iname='-snes_type -ksp_type -pc_type -pc_factor_shift_type '
# petsc_options_value=' newtonls   preonly   lu       NONZERO'

#nl_rel_tol=1e-5
#  nl_abs_tol=1e-5
#  nl_rel_step_tol=1e-6
#  nl_abs_step_tol=1e-6

#  l_tol=1.e-6
#  l_max_its=30
  #l_abs_step_tol=1.e-12
  #l_max_its=20

  start_time=   0.0
  end_time  =   10.0
  dtmin     =   0.5
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
#output_on = ''
  [../]
 []
