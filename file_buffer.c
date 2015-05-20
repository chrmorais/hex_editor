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

struct chunk *chunk_store = NULL;
unsigned int chunk_store_size = 0;


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

struct chunk *
find_byte_in_chunk(unsigned int address){
    if(chunk_store == NULL){
        return NULL;
    }

    int inx = 0;
    for (inx=0; inx < chunk_store_size; inx++) {
        if(address >= chunk_store[inx].offset &&
           address < chunk_store[inx].offset + chunk_size ){
            return &chunk_store[inx];
        }
    }

    return NULL;
}

void
create_chunk_for_address(unsigned int address){

    if(file_path == NULL){
        return;
    }

    unsigned int chunk_offset = address - (address % chunk_size);
    struct chunk *new_chunk = malloc(sizeof(struct chunk));
    new_chunk->data = (char *)malloc(chunk_size);

    FILE *user_file = fopen(file_path, "rb");
    fseek(user_file, chunk_offset, SEEK_SET);
    fread(new_chunk->data, 1, chunk_size, user_file);
    fclose(user_file);

    new_chunk->offset = chunk_offset;

    if(chunk_store_size == 0){
        chunk_store = malloc(sizeof(struct chunk));
        chunk_store[0] = *new_chunk;
    }else{
        chunk_store = (struct chunk *)realloc(chunk_store, (chunk_store_size+1) * sizeof(struct chunk));
        chunk_store[chunk_store_size] = *new_chunk;
    }

    chunk_store_size++;
}

unsigned char
__get_byte(size_t address){

    if(address >= file_size){
        return (unsigned char)0;
    }

    struct chunk *chunk_with_address = find_byte_in_chunk(address);
    if(chunk_with_address != NULL){
        return chunk_with_address->data[address - chunk_with_address->offset];
    }

    if(!address_in_buffer(address)){
        buffering(address);
    }

    return buffer[address - buffer_offset];
}

void
save_changes(void){
    if(file_path == NULL){
        return;
    }

    size_t buffer_copy_size = 4096;
    unsigned char *buffer_copy = malloc(buffer_copy_size);

    FILE *copy_file = fopen(strcat(file_path, ".copy"), "wb");

    size_t address = 0;
    size_t pos_in_buffer = 0;
    while(address != file_size){
        buffer_copy[pos_in_buffer] = __get_byte(address);

        pos_in_buffer++;
        address++;

        if (address == file_size){
            fwrite(buffer_copy, 1, pos_in_buffer, copy_file);
        }

        if(pos_in_buffer == buffer_copy_size){
            fwrite(buffer_copy, 1, buffer_copy_size, copy_file);
            pos_in_buffer = 0;
        }
    }

    fclose(copy_file);
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
    size_t address = 0;

    PyArg_Parse(args, "(i)", &address);

    return Py_BuildValue("c", __get_byte(address));
};

PyObject *
set_byte(PyObject *self, PyObject *args){
    unsigned int address = 0;
    unsigned char value;

    PyArg_Parse(args, "(ic)", &address, &value);

    if(find_byte_in_chunk(address) == NULL){
        create_chunk_for_address(address);
    }

    struct chunk *find_chunk = find_byte_in_chunk(address);
    find_chunk->data[address - find_chunk->offset] = value;

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
