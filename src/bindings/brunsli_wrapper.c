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

#include <stdio.h>
#include <stdlib.h>

#include "brunsli/encode.h"

typedef struct buffer_st
{
    unsigned char *data;
    size_t size;
} buffer_st;


int read_file(const char* filepath, buffer_st* buf)
{
    FILE *f = fopen(filepath, "r");
    fseek(f, 0, SEEK_END);
    buf->size = ftell(f);
    rewind(f);
    buf->data = malloc(buf->size);
    fread(buf->data, sizeof(buf->data), buf->size, f);
    fclose(f);
    return 0;
}

size_t allocate_output(void* data, const unsigned char* buf, size_t count)
{
    buffer_st *buffer = (buffer_st *) data;
    buffer->data = realloc(buffer->data, buffer->size + count);
    if (!buffer->data) {
        return 0;
    }
    memcpy(buffer->data + buffer->size, buf, count);
    buffer->size += count;
    return count;
}

int encode_image(const buffer_st* inbuf, buffer_st* outbuf)
{
    int ret = -1;
    outbuf->data = NULL;
    outbuf->size = 0;
    ret = EncodeBrunsli(inbuf->size, inbuf->data, outbuf, allocate_output);
    if (ret == 1) {
        ret = 0;
    }
    return ret;
}

int write_file(const char* filepath, const buffer_st* buf)
{
    int ret = -1;
    FILE *f = fopen(filepath, "w");
    if (!f) {
        return ret;
    }
    ret = fwrite(buf->data, sizeof(unsigned char), buf->size, f);
    return ret;

}

void usage()
{
    fprintf(stdout, "Syntax: brunsli_wrapper [input_file] [output_file]\n\n");
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        usage();
        return -1;
    }

    buffer_st in_file;
    buffer_st out_file;

    read_file(argv[1], &in_file);
    encode_image(&in_file, &out_file);
    write_file(argv[2], &out_file);
    fprintf(stdout, "Convert success! before=%zd after=%zd %.2f%%\n", in_file.size, out_file.size, (float) out_file.size / in_file.size * 100);

    free(in_file.data);
    free(out_file.data);

    return 0;
}
