/*
Copyright (c) 2020, Moonsik Park
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "brunsli/encode.h"
#include "brunsli/decode.h"

#include "common.h"

static PyObject* brunslipy_encode(PyObject* self, PyObject* image)
{
    Py_buffer inbuf;

    buffer_t outbuf;
    buffer_t_init(&outbuf);
    
    if (!PyArg_ParseTuple(image, "y*", &inbuf))
        return NULL;
    
    EncodeBrunsli((size_t) inbuf.len, (unsigned char*) inbuf.buf, &outbuf, allocate_output);

    return Py_BuildValue("y#", (char*) outbuf.data, (Py_ssize_t) outbuf.len);
}

static PyObject* brunslipy_decode(PyObject* self, PyObject* image)
{
    Py_buffer inbuf;

    buffer_t outbuf;
    buffer_t_init(&outbuf);
    
    if (!PyArg_ParseTuple(image, "y*", &inbuf))
        return NULL;
    
    DecodeBrunsli((size_t) inbuf.len, (unsigned char*) inbuf.buf, &outbuf, allocate_output);

    return Py_BuildValue("y#", (char*) outbuf.data, (Py_ssize_t) outbuf.len);
}

static PyMethodDef BrunsliMethods[] = {
    {"encode",  brunslipy_encode, METH_VARARGS,
     "Encode a JPEG image to JXL image."},
    {"decode",  brunslipy_decode, METH_VARARGS,
     "Decode a JXL image to JPEG image."}
};

static struct PyModuleDef brunslimodule = {
    PyModuleDef_HEAD_INIT,
    "brunsli",
    "Python wrapper for brunsli.",
    0,
    BrunsliMethods
};

PyMODINIT_FUNC PyInit_brunsli(void) {
    return PyModule_Create(&brunslimodule);
}