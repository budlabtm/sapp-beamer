#ifndef SAPP_BEAMER_FITTER_H
#define SAPP_BEAMER_FITTER_H

#define EM_H_DEF 0.0
#define EM_V_DEF 0.0
#define DEP_DEF 0.0

#include <gsl/gsl_multimin.h>
#include "beamer/proto/beamer-res.pb.h"
#include "beamer/proto/beamer-cfg.pb.h"

namespace budlab::beamer {

struct Frame {
  double value;
  const FrameConfiguration *cfg;

  Frame(double value_, const FrameConfiguration *cfg_)
      : value(value_), cfg(cfg_) {}
};

double func(const gsl_vector *v, void *d);
void dfunc(const gsl_vector *v, void *d, gsl_vector *df);
void ddfunc(const gsl_vector *v, void *d, double *f, gsl_vector *df);

class Fitter {
 private:
  gsl_multimin_function_fdf function_;
  gsl_multimin_fdfminimizer *minimizer_;
  gsl_vector *result_;

 public:
  Fitter();
  ~Fitter();

  BeamerResult fit(std::vector<Frame> &frames);
};

}  // namespace budlab::beamer

#endif  // SAPP_BEAMER_FITTER_H