#include <Python.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int chunk_size  = 128;
int buffer_size = 128*1024;

unsigned int buffer_offset = 0;
unsigned char *buffer = NULL;

unsigned int file_size = 0;
const char *file_path = NULL;


unsigned int
buffering(unsigned int start){
    if(file_path == NULL){
        return 0;
    }

    FILE *user_file = fopen(file_path, "r");
    fseek(user_file, buffer_offset, SEEK_SET);
    fgets(buffer, buffer_size, user_file);
    fclose(user_file);

    buffer_offset = start;

    if(start + buffer_size >= file_size){
        return file_size - 1;
    }

    return start + buffer_size;
}


PyObject *
init(PyObject *self, PyObject *args){
    if(PyArg_Parse(args, "(i)", &chunk_size)){
        if(chunk_size <= 0 ){
            chunk_size = 128;
        };

        buffer_size = chunk_size * 1024;
    }

    buffer = malloc(buffer_size);

    return Py_BuildValue("");
};

PyObject *
openFile(PyObject *self, PyObject *args){
    PyArg_Parse(args, "(s)", &file_path);

    //узнаем размер файла
    FILE *user_file = fopen(file_path, "r");
    fseek(user_file, 0L, SEEK_END);
    file_size = ftell(user_file);
    fclose(user_file);

    buffering(0);

    return Py_BuildValue("i",buffer[7]);
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
