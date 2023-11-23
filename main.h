#ifndef PARADYGMATY_PROGRAMOWANIA_PROJEKT_2_MAIN_H
#define PARADYGMATY_PROGRAMOWANIA_PROJEKT_2_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

#define MAX_LINE 256
#define MAX_LINES 256

static int WORD_ONE_IS_FIRST = 1, WORD_TWO_IS_FIRST = 2, WORDS_ARE_EQUAL = 0;

void check_args(int argc, char *argv[]);

FILE *readfile(char *filename);

wchar_t **read_words(FILE *fp);

void check_word_and_print_error(wchar_t *word, int word_number);

int which_should_be_first(wchar_t *word1, wchar_t *word2);

int get_letter_index(wchar_t letter);

void **sort(wchar_t **words);

int partition(wchar_t **words, int left, int right);

int word_one_are_first_or_equal(wchar_t *word1, wchar_t *word2);

void **quick_sort(wchar_t **words, int left, int right);

void print_words(wchar_t **words);

void swap(wchar_t **words, int i, int j);

#endif
