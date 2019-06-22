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

// #include <libcgc.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "meow.h"

#define MAX_MEOW_LENGTH 8192

meow_parser_t *parser;
meow_item_t *my_meow;

int read_until(FILE* fp, char *buf, size_t len, char delim)
{
    size_t i;
    char *c = buf;

    for (i = 0; i < len; ++i) {
        size_t rx;

        if ((rx = fread(c, 1, 1, fp)) != 1)
            return -1;

        if (*(c++) == delim)
            break;
    }

    *(c - 1) = '\0';
    return c - buf;
}

void import_MEOW(char *buf)
{
    if (my_meow != NULL) {
        free_meow_item(my_meow);
        my_meow = NULL;
    }

    parser->cats = 0;
    my_meow = parser->loads(buf);

    if (my_meow == NULL)
        printf("Error!\n");
}

void print_MEOW()
{
    if (my_meow == NULL) {
        printf("Error!\n");
        return;
    }

    parser->cats = 0;
    parser->dumps(my_meow);
    printf("\n");
}

void nyan()
{
    int i;
    char *c;
    char buf[256] = {0};
    char *nyan_cat = "\n\n\
+      o     +              o\n\
    +             o     +       +\n\
o          +\n\
    o  +           +        +\n\
+        o     o       +        o\n\
-_-_-_-_-_-_-_,------,      o\n\
_-_-_-_-_-_-_-|   /\\_/\\\n\
-_-_-_-_-_-_-~|__( ^ .^)  +     +\n\
_-_-_-_-_-_-_-\"\"  \"\"\n\
+      o         o   +       o\n\
    +         +\n\
o        o         o      o     +\n\
    o           +\n\
+      +     o        o      +\n\n";

    if (my_meow == NULL) {
        printf("Error!\n");
        return;
    }

    parser->dumps(my_meow);
    printf("\n");

    if (parser->cats < 3)
        return;

    printf("%s", nyan_cat);
    c = buf;

    for (i = 0; i < array_length(parser->nyan_says); ++i) {
        meow_item_t *item = array_get(parser->nyan_says, i);
        strcpy(c, item->item.i_string.s);
        c += item->item.i_string.len;
    }

    printf("NYAN SAYS...\n\"\n%s\n\"\n", buf);
}

void quit()
{
    printf("\n\n=^.^=// Bye!\n\n");
    exit(0);
}

void menu()
{
    printf("=======================\n");
    printf(" 1. Import MEOW\n");
    printf(" 2. Print MEOW\n");
    printf(" 3. Quit\n");
    printf("=======================\n");
}

int main()
{
    // disable buffering on stdout
    setvbuf(stdout, NULL, _IONBF, 0);
    char buf[MAX_MEOW_LENGTH];
    char select[16];
    printf("MEOW Pretty Printer v0.1\n");
    parser = (meow_parser_t *) malloc(sizeof(meow_parser_t));
    meow_init(parser);
    menu();
    printf("> ");

    while (read_until(stdin, select, sizeof(select), '\n') > 0) {
        int menu = strtol(select, NULL, 10);

        switch (menu) {
        case 1:
            printf("MEOW? ");

            if (read_until(stdin, buf, MAX_MEOW_LENGTH, '\n') > 0)
                import_MEOW(buf);
            else
                printf("Error!\n");

            break;

        case 2:
            print_MEOW();
            break;

        case 3:
            quit();

        case 777:
            nyan();
            break;

        default:
            printf("Invalid menu. Try again.\n");
            break;
        }

        printf("> ");
    }

    return 0;
}
