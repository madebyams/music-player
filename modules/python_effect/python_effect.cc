#include "python_effect.hh"

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <filesystem>

#include <spdlog/spdlog.h>

constexpr std::string_view PROCESS_FUNCTION_NAME {"process"};

player_buffer python_effect::run(
  std::string script_path,
  player_buffer samples
) {
  std::filesystem::path path{script_path};
  std::string dir = path.parent_path().empty() ? "." : path.parent_path().string();
  std::string module_name = path.stem().string();

  Py_Initialize();

  PyObject* py_dir = PyUnicode_DecodeFSDefault(dir.c_str());
  PyList_Insert(PySys_GetObject("path"), 0, py_dir);
  Py_DECREF(py_dir);

  PyObject* py_module = PyImport_ImportModule(module_name.c_str());
  if(py_module == NULL) {
    spdlog::error("Failed to import PyFx script {}", script_path);
    PyErr_Print();
    Py_FinalizeEx();
    return samples;
  }

  PyObject* process_function = PyObject_GetAttrString(
   py_module,
   PROCESS_FUNCTION_NAME.data()
  );

  if(process_function == NULL || !PyCallable_Check(process_function)) {
    spdlog::error("PyFx script {} has no callable '{}' function", script_path, PROCESS_FUNCTION_NAME);
    PyErr_Print();
    Py_XDECREF(process_function);
    Py_DECREF(py_module);
    Py_FinalizeEx();
    return samples;
  }

  PyObject* py_samples = PyList_New(samples.size());
  for(Py_ssize_t i = 0; i < static_cast<Py_ssize_t>(samples.size()); ++i) {
    PyList_SET_ITEM(py_samples, i, PyFloat_FromDouble(samples[i]));
  }

  PyObject* args = PyTuple_Pack(1, py_samples);
  Py_DECREF(py_samples);

  PyObject* result = PyObject_CallObject(process_function, args);
  Py_DECREF(args);

  player_buffer output = samples;
  if(result == NULL) {
    PyErr_Print();
  } else if(!PyList_Check(result)) {
    spdlog::error("PyFx script {} did not return a list of samples", script_path);
  } else {
    output.clear();
    output.reserve(PyList_Size(result));
    for(Py_ssize_t i = 0; i < PyList_Size(result); ++i) {
      output.push_back(static_cast<float>(PyFloat_AsDouble(PyList_GetItem(result, i))));
    }
  }
  Py_XDECREF(result);

  Py_DECREF(process_function);
  Py_DECREF(py_module);
  Py_FinalizeEx();
  return output;
}
