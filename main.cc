#include "QtCore/QCoreApplication"
#include "domain/beamer.h"

int main(int argc, char **argv) {
  QCoreApplication app{argc, argv};
  budlab::sapp::beamer::Beamer beamer;

  beamer.start();

  return app.exec();
}