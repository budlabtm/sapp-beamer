#ifndef SAPP_BEAMER_CORE_H
#define SAPP_BEAMER_CORE_H

#include "gsl/gsl_multimin.h"
#include "proto/beamer-cfg.pb.h"
#include "proto/beamer-out.pb.h"
#include <vector>

namespace budlab::sapp::beamer {

struct FrameData {
  double val_;
  FrameConfiguration cfg_;

  FrameData(double val, FrameConfiguration cfg) {
    val_ = val;
    cfg_ = cfg;
  }
};

double func(const gsl_vector *v, void *d);
void dfunc(const gsl_vector *v, void *d, gsl_vector *df);
void ddfunc(const gsl_vector *v, void *d, double *f, gsl_vector *df);

class Fit {
private:
  const gsl_multimin_fdfminimizer_type *type_;
  gsl_multimin_function_fdf function_;
  gsl_multimin_fdfminimizer *minimizer_;
  gsl_vector *result_;

public:
  Fit();
  ~Fit();
  BeamerResult fit(std::vector<FrameData> &frames);
};

} // namespace budlab::sapp::beamer

#endif // SAPP_BEAMER_CORE_H