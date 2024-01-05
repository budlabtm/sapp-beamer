#include "fitter.h"

using namespace budlab::beamer;

double budlab::beamer::func(const gsl_vector *v, void *d) {
  std::vector<Frame> *frames = (std::vector<Frame> *)d;

  double eh = gsl_vector_get(v, 0);
  double ev = gsl_vector_get(v, 1);
  double dp = gsl_vector_get(v, 2);

  double result = 0;

  for (auto &frame : *frames) {
    double val_sq = frame.value * frame.value;
    double part_root, d;

    switch (frame.cfg->type()) {
      case FrameConfiguration::FRAME_TYPE_HORIZONTAL:
        d = dp * frame.cfg->etta();
        part_root = val_sq - (eh * frame.cfg->beta()) - (d * d);
        break;

      case FrameConfiguration::FRAME_TYPE_VERTICAL:
        part_root = val_sq - (ev * frame.cfg->beta());
        break;

      case FrameConfiguration_FrameType_FrameConfiguration_FrameType_INT_MIN_SENTINEL_DO_NOT_USE_:
      case FrameConfiguration_FrameType_FrameConfiguration_FrameType_INT_MAX_SENTINEL_DO_NOT_USE_:
        part_root = 0;
        break;
    }

    result += part_root * part_root;
  }

  return result;
}

void budlab::beamer::dfunc(const gsl_vector *v, void *d, gsl_vector *df) {
  std::vector<Frame> *frames = (std::vector<Frame> *)d;

  double eh = gsl_vector_get(v, 0);
  double ev = gsl_vector_get(v, 1);
  double dp = gsl_vector_get(v, 2);

  double deh = 0;
  double dev = 0;
  double ddp = 0;

  for (auto &frame : *frames) {
    double val_sq = frame.value * frame.value;
    double d = dp * frame.cfg->etta();

    switch (frame.cfg->type()) {
      case FrameConfiguration::FRAME_TYPE_HORIZONTAL:
        deh += frame.cfg->beta() * (-2) *
               (val_sq - eh * frame.cfg->beta() - d * d);
        ddp += frame.cfg->etta() * frame.cfg->etta() * (-4) * dp *
               (val_sq - eh * frame.cfg->beta() - d * d);
        break;

      case FrameConfiguration::FRAME_TYPE_VERTICAL:
        dev += frame.cfg->beta() * (-2) * (val_sq - ev * frame.cfg->beta());
        break;

      case FrameConfiguration_FrameType_FrameConfiguration_FrameType_INT_MIN_SENTINEL_DO_NOT_USE_:
      case FrameConfiguration_FrameType_FrameConfiguration_FrameType_INT_MAX_SENTINEL_DO_NOT_USE_:
        break;
    }
  }

  gsl_vector_set(df, 0, deh);
  gsl_vector_set(df, 1, dev);
  gsl_vector_set(df, 2, ddp);
}

void budlab::beamer::ddfunc(const gsl_vector *v, void *d, double *f,
                            gsl_vector *df) {
  *f = func(v, d);
  dfunc(v, d, df);
}

Fitter::Fitter() {
  function_.n = 3;
  function_.f = &func;
  function_.df = &dfunc;
  function_.fdf = &ddfunc;

  minimizer_ = gsl_multimin_fdfminimizer_alloc(
      gsl_multimin_fdfminimizer_conjugate_fr, 3);
  result_ = gsl_vector_alloc(3);

  gsl_vector_set(result_, 0, EM_H_DEF);
  gsl_vector_set(result_, 1, EM_V_DEF);
  gsl_vector_set(result_, 2, DEP_DEF);
}

Fitter::~Fitter() {
  gsl_multimin_fdfminimizer_free(minimizer_);
  gsl_vector_free(result_);
}

BeamerResult Fitter::fit(std::vector<Frame> &frames) {
  BeamerResult result;
  int iteration = 0, status;

  function_.params = (void *)&frames;
  gsl_multimin_fdfminimizer_set(minimizer_, &function_, result_, 0.01, 1e-4);

  do {
    iteration++;
    status = gsl_multimin_fdfminimizer_iterate(minimizer_);

    if (status) break;

    status = gsl_multimin_test_gradient(minimizer_->gradient, 1e-3);

    if (status == GSL_SUCCESS) {
      result.set_em_h(gsl_vector_get(result_, 0));
      result.set_em_v(gsl_vector_get(result_, 1));
      result.set_dep(gsl_vector_get(result_, 2));
    }

  } while (status == GSL_CONTINUE && iteration < 100);

  return result;
}