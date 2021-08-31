#include <torch/csrc/utils/pybind.h>
#include <ATen/Config.h>

#if AT_MKL_ENABLED()
#include <mkl.h>
#endif

#if AT_MKLDNN_ENABLED()
#include <ATen/native/mkldnn/MKLDNNCommon.h>
#endif

namespace torch {

int _mkl_set_verbose(int enable) {
#if AT_MKL_ENABLED()
  return mkl_verbose(enable);
#else
  return 0;
#endif
}

int _mkldnn_set_verbose(int level) {
#if AT_MKLDNN_ENABLED()
  return at::native::set_verbose(level);
#else
  return 0;
#endif
}

void initVerboseBindings(PyObject* module) {
  auto m = py::handle(module).cast<py::module>();

  auto verbose = m.def_submodule("_verbose", "MKL, MKLDNN verbose");
  verbose.def("mkl_set_verbose", _mkl_set_verbose);
  verbose.def("mkldnn_set_verbose", _mkldnn_set_verbose);
}
} // namespace torch
