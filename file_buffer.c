#include <Python.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int chunk_size  = 128;
int buffer_size = 128*1024;

unsigned int buffer_offset = 0;
unsigned char *buffer = NULL;

unsigned int file_size = 0;
const char *file_path = NULL;


struct chunk {
    unsigned int offset;
    unsigned char *data;
};


unsigned int
buffering(unsigned int start){
    if(file_path == NULL){
        return 0;
    }

    FILE *user_file = fopen(file_path, "rb");
    fseek(user_file, buffer_offset, SEEK_SET);
    fread(buffer, 1, buffer_size, user_file);
    fclose(user_file);

    buffer_offset = start;

    if(start + buffer_size >= file_size){
        return file_size - 1;
    }

    return start + buffer_size;
}

bool
address_in_buffer(unsigned int address){
    if( address >= buffer_offset &&
        address < buffer_offset + buffer_size){
        return true;
    }

    return false;
}

unsigned int
calculate_buffer_start(unsigned int address){
    long start = address - (buffer_size / 2);

    if(start < 0){ return 0;}

    return (unsigned int)start;
}

void
save_changes(void){
};

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
open_file(PyObject *self, PyObject *args){
    PyArg_Parse(args, "(s)", &file_path);

    //узнаем размер файла
    FILE *user_file = fopen(file_path, "rb");
    fseek(user_file, 0L, SEEK_END);
    file_size = ftell(user_file);
    fclose(user_file);

    buffering(0);

    return Py_BuildValue("i",file_size);
};

PyObject *
close_file(PyObject *self, PyObject *args){
    save_changes();
    file_path = NULL;
    buffer_offset = 0;
    file_size = 0;

    return Py_BuildValue("");
};

PyObject *
get_byte(PyObject *self, PyObject *args){
    unsigned int address = 0;

    PyArg_Parse(args, "(i)", &address);

    if(address >= file_size){
        return Py_BuildValue("c", 0);
    }

    if(!address_in_buffer(address)){
        buffering(address);
    }

    return Py_BuildValue("c", buffer[address - buffer_offset]);
};

PyObject *
set_byte(PyObject *self, PyObject *args){
    return Py_BuildValue("");
};


/* таблица регистрации */
static PyMethodDef file_buffer_methods[] = {
    {"init", init, METH_VARARGS, ""},
    {"open_file", open_file, METH_VARARGS, ""},
    {"close_file", close_file, METH_VARARGS, ""},
    {"get_byte", get_byte, METH_VARARGS, ""},
    {"set_byte", set_byte, METH_VARARGS, ""},

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
