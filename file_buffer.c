#include <Python.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static const int CHUNK_SIZE  = 128;

static unsigned char *buffer = NULL;


PyObject *
init(PyObject *self, PyObject *args){
    buffer = malloc(CHUNK_SIZE * 1024);

    return Py_BuildValue("");
};

PyObject *
openFile(PyObject *self, PyObject *args){
    return Py_BuildValue("");
};

PyObject *
closeFile(PyObject *self, PyObject *args){
    return Py_BuildValue("");
};

PyObject *
getByte(PyObject *self, PyObject *args){
    int address = 0;

    PyArg_Parse(args, "(i)", &address);

    return Py_BuildValue("i", address);
};

PyObject *
setByte(PyObject *self, PyObject *args){
    return Py_BuildValue("");
};

PyObject *
saveChanges(PyObject *self, PyObject *args){
    return Py_BuildValue("");
};


/* таблица регистрации */
static PyMethodDef file_buffer_methods[] = {
    {"init", init, METH_VARARGS, ""},
    {"openFile", openFile, METH_VARARGS, ""},
    {"closeFile", closeFile, METH_VARARGS, ""},
    {"getByte", getByte, METH_VARARGS, ""},
    {"setByte", setByte, METH_VARARGS, ""},
    {"saveChanges", saveChanges, METH_VARARGS, ""},

    {NULL, NULL, 0, NULL}
};

/* структура определения модуля */
static struct PyModuleDef file_buffer_module = {
    PyModuleDef_HEAD_INIT,
    "file_buffer",
    NULL,
    -1,
    file_buffer_methods
};

/* инициализация модуля */
PyMODINIT_FUNC
PyInit_file_buffer(){
    return PyModule_Create(&file_buffer_module);
}
