/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef MEOW_H
#define MEOW_H

// #include <libcgc.h>
#include "array.h"
#include "hashtable.h"

#define MAX_MEOW_STRING 128

#define STATE_PARSING_MEOW 0
#define STATE_PARSING_KEY 1
#define STATE_PARSING_STRING 2

typedef enum meow_type {
    MEOW_INT = 0,
    MEOW_DOUBLE = 1,
    MEOW_STRING = 2,
    MEOW_OBJECT = 3,
    MEOW_ARRAY = 4,
    MEOW_BOOLEAN = 5,
    MEOW_NULL = 6,
    MEOW_CAT = 7
} meow_type_t;

typedef struct meow_item {
    meow_type_t type;
    union data {
        char i_bool;
        int i_int;
        double i_double;
        struct {
            char *s;
            int len;
        } i_string;
        array_t *i_array;
        htbl_t *i_object;
    } item;
} meow_item_t;

typedef void (meow_dumps_fn) (meow_item_t *meow);
typedef meow_item_t* (meow_loads_fn) (char *str);

typedef struct meow_parser {
    unsigned int cats;
    array_t *nyan_says;
    meow_dumps_fn *dumps;
    meow_loads_fn *loads;
} meow_parser_t;

int meow_init(meow_parser_t *parser);
void free_meow_item(void *e);

void meow_dumps(meow_item_t *meow);
meow_item_t* meow_loads(char *str);

#endif
