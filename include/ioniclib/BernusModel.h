/* File bernus.h */
#ifndef BERNUS_H
#define BERNUS_H

#ifdef __CUDA_ARCH__
#define BERNUS_CUDA_ATTR __device__ __host__
#else
#define BERNUS_CUDA_ATTR
#endif

struct BernusModel
{
  struct gate_t
  {
    double m,v,f,to,x;
  };
  enum param_names
  {
    PARAM_R,
    PARAM_T,
    PARAM_F,
    PARAM_CM,
    PARAM_G_NA,
    PARAM_G_CA,
    PARAM_G_TO,
    PARAM_G_K,
    PARAM_G_K1,
    PARAM_G_CAB,
    PARAM_G_NAB,
    PARAM_G_NAK,
    PARAM_G_NACA,
    PARAM_NA_I,
    PARAM_NA_E,
    PARAM_CA_I,
    PARAM_CA_E,
    PARAM_K_I,
    PARAM_K_E,
  };

  BernusModel(const int,const bool,const bool);
  ~BernusModel();
  void initstate(double*);
  void modelstep(double*,const double);

  BERNUS_CUDA_ATTR
  static void update_rl1(double&,gate_t&,const double[],const double);

  static const int num_gates = 5;
  static const int num_parameters = 19;

  BERNUS_CUDA_ATTR static double alpha_m(const double);
  BERNUS_CUDA_ATTR static double beta_m(const double);
  BERNUS_CUDA_ATTR static double v_inf(const double);
  BERNUS_CUDA_ATTR static double tau_v(const double);
  BERNUS_CUDA_ATTR static double alpha_d(const double);
  BERNUS_CUDA_ATTR static double beta_d(const double);
  BERNUS_CUDA_ATTR static double alpha_f(const double);
  BERNUS_CUDA_ATTR static double beta_f(const double);
  BERNUS_CUDA_ATTR static double alpha_r(const double);
  BERNUS_CUDA_ATTR static double beta_r(const double);
  BERNUS_CUDA_ATTR static double alpha_to(const double);
  BERNUS_CUDA_ATTR static double beta_to(const double);
  BERNUS_CUDA_ATTR static double x_inf(const double);
  BERNUS_CUDA_ATTR static double tau_x_a(const double);
  BERNUS_CUDA_ATTR static double tau_x(const double);
  BERNUS_CUDA_ATTR static double alpha_K1(const double,const double);
  BERNUS_CUDA_ATTR static double beta_K1(const double,const double);
  BERNUS_CUDA_ATTR static double f_NaK(const double,const double);
  BERNUS_CUDA_ATTR static double f_NaKp(const double,const double);
  BERNUS_CUDA_ATTR static double f_NaCa(const double,const double,
    const double,const double,const double);

  const int nodes_;
  gate_t* gates_;
  double* Vm_;
  double parameters_[num_parameters];
  double* parameters_dev_;
  static const double default_parameters[num_parameters];
  const bool use_cuda_;
  const bool verbose_;
};

#endif /* !File bernus.h */
