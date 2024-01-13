#include <glog/logging.h>
#include <string>

#include "fitter.h"

using namespace std;
using namespace budlab::beamer;

double budlab::beamer::func(const gsl_vector *v, void *d) {
  std::vector<Frame> *frames = (std::vector<Frame> *)d;

  double em = gsl_vector_get(v, 0);
  double dp = gsl_vector_get(v, 1);
  double result = 0;

  for (auto &frame : *frames) {
    double val_sq = frame.value * frame.value;
    double part_root, d;

    switch (frame.cfg->type()) {
      case FrameConfiguration_FrameType_FRAME_TYPE_HORIZONTAL:
        d = dp * frame.cfg->etta();
        part_root = val_sq - (em * frame.cfg->beta()) - (d * d);
        break;

      case FrameConfiguration_FrameType_FRAME_TYPE_VERTICAL:
        part_root = val_sq - (em * frame.cfg->beta());
        break;
    }

    result += part_root * part_root;
  }

  return result;
}

void budlab::beamer::dfunc(const gsl_vector *v, void *d, gsl_vector *df) {
  std::vector<Frame> *frames = (std::vector<Frame> *)d;

  double em = gsl_vector_get(v, 0);
  double dp = gsl_vector_get(v, 1);

  double dem = 0;
  double ddp = 0;

  for (auto &frame : *frames) {
    double val_sq = frame.value * frame.value;
    double d = dp * frame.cfg->etta();

    switch (frame.cfg->type()) {
      case FrameConfiguration_FrameType_FRAME_TYPE_HORIZONTAL:
        dem += frame.cfg->beta() * (-2) *
               (val_sq - em * frame.cfg->beta() - d * d);
        ddp += frame.cfg->etta() * frame.cfg->etta() * (-4) * dp *
               (val_sq - em * frame.cfg->beta() - d * d);
        break;

      case FrameConfiguration_FrameType_FRAME_TYPE_VERTICAL:
        dem += frame.cfg->beta() * (-2) * (val_sq - em * frame.cfg->beta());
        break;
    }
  }

  gsl_vector_set(df, 0, dem);
  gsl_vector_set(df, 1, ddp);
}

void budlab::beamer::ddfunc(const gsl_vector *v, void *d, double *f,
                            gsl_vector *df) {
  *f = func(v, d);
  dfunc(v, d, df);
}

Fitter::Fitter() {
  function_.n = 2;
  function_.f = &func;
  function_.df = &dfunc;
  function_.fdf = &ddfunc;

  minimizer_ = gsl_multimin_fdfminimizer_alloc(
      gsl_multimin_fdfminimizer_vector_bfgs2, 2);
  start_ = gsl_vector_alloc(2);

  gsl_vector_set(start_, 0, EM_DEF);
  gsl_vector_set(start_, 1, DP_DEF);
}

Fitter::~Fitter() {
  gsl_multimin_fdfminimizer_free(minimizer_);
  gsl_vector_free(start_);
}

BeamerResult Fitter::fit(std::vector<Frame> &frames) {
  BeamerResult res;
  unsigned long long iteration = 0;
  int status;

  function_.params = (void *)&frames;
  gsl_multimin_fdfminimizer_set(minimizer_, &function_, start_, 1, 1e-2);

  do {
    iteration++;
    status = gsl_multimin_fdfminimizer_iterate(minimizer_);

    if (status) break;

    status = gsl_multimin_test_gradient(minimizer_->gradient, 1e-3);
  } while (status == GSL_CONTINUE && iteration < 100);

  LOG(INFO) << status;
  res.set_em(gsl_vector_get(minimizer_->x, 0));
  res.set_dp(gsl_vector_get(minimizer_->x, 1));

  LOG(INFO) << "Em: " << res.em() << ", Dp: " << res.dp()
            << ", F: " << minimizer_->f << ", I: " << iteration;

  return res;
}