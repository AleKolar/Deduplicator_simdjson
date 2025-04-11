#include <Python.h>
#include <simdjson.h>

static PyObject* parse_json(PyObject* self, PyObject* args) {
    const char* json_str;
    if (!PyArg_ParseTuple(args, "s", &json_str)) {
        return NULL;
    }

    simdjson::dom::parser parser;
    simdjson::dom::element element;

    try {
        element = parser.parse(json_str);
    } catch (const simdjson::simdjson_error& e) {
        PyErr_SetString(PyExc_ValueError, e.what());
        return NULL;
    }

    simdjson::dom::object obj = element.get_object();
    return Py_BuildValue("s", obj.serialize().c_str());
}

static PyMethodDef methods[] = {
    {"parse", parse_json, METH_VARARGS, "Parse JSON with simdjson"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "simdjson_parser",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit_simdjson_parser(void) {
    return PyModule_Create(&module);
}