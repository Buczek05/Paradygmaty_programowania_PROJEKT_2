#include "main.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    check_args(argc, argv);
    FILE *fp = readfile(argv[1]);
    wchar_t **words = read_words(fp);
    sort(words);
    print_words(words);
    return 0;
}

void check_args(int argc, char *argv[]) {
    if (argc != 2) {
        wprintf(L"Usage: %s <text file>\n", argv[0]);
        exit(1);
    }
}

FILE *readfile(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        wprintf(L"Error: could not open %s\n", filename);
        exit(1);
    }
    return fp;
}

wchar_t **read_words(FILE *fp) {
    wchar_t **words = malloc(sizeof(wchar_t *) * MAX_LINES);
    wchar_t *word = malloc(sizeof(wchar_t) * MAX_LINE);
    int i = 0;
    while (fwscanf(fp, L"%ls", word) != EOF) {
        check_word_and_print_error(word, i+1);
        words[i] = malloc(sizeof(wchar_t) * wcslen(word));
        wcscpy(words[i], word);
        i++;
    }
    words[i] = NULL;
    return words;
}


void check_word_and_print_error(wchar_t *word, int word_number) {
    int i = 0;
    while (word[i]) {
        if (get_letter_index(word[i]) == -1) {
            wprintf(L"Error: word \"%ls\" contains invalid character %lc - %d\n", word, word[i], word[i]);
            wprintf(L"Word number: %d\n", word_number);
            wprintf(L"Character number: %d\n", i + 1);
            exit(1);
        }
        i++;
    }
}


int which_should_be_first(wchar_t *word1, wchar_t *word2) {
    int i = 0, word_one_letter_index, word_two_letter_index;
    while (word1[i] && word2[i]) {
        word_one_letter_index = get_letter_index(word1[i]);
        word_two_letter_index = get_letter_index(word2[i]);
        if (word_one_letter_index < word_two_letter_index) return WORD_ONE_IS_FIRST;
        if (word_one_letter_index > word_two_letter_index) return WORD_TWO_IS_FIRST;
        i++;
    }
    if (word1[i] == '\0' && word2[i] == '\0') return WORDS_ARE_EQUAL;
    if (word1[i] == '\0') return WORD_ONE_IS_FIRST;
    return WORD_TWO_IS_FIRST;
}

int get_letter_index(wchar_t letter) {
    wchar_t litery[] = {'A', 'a', 260, 261, 'B', 'b', 'C', 'c', 262, 263, 'D', 'd', 'E', 'e', 280, 281, 'F', 'f', 'G', 'g',
                     'H', 'h', 'I', 'i', 'J', 'j', 'K', 'k', 'L', 'l', 321, 322, 'M', 'm', 'N', 'n', 193, 324,
                     'O', 'o', 211, 243, 'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's', 346, 347, 'T', 't', 'U', 'u',
                     'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z', 377, 378, 379, 380, '1', '2', '3', '4',
                     '5', '6', '7', '8', '9', '0', '!', '.', ',', '?', ':', '-', '_', '"', '\'', '[', ']', '(',
                     ')', '{', '}', '\\', '=', '*', '+', '\0'};
    int i = 0;
    while (litery[i]) {
        if (letter == litery[i]) return i;
        i++;
    }
    return -1;
}

void **sort(wchar_t **words){
    int right = 0;
    while(words[right]) right++;
    printf("%d\n", right);
    quick_sort(words, 0, right - 1);
}

int partition(wchar_t **words, int left, int right){
    wchar_t *pivot = words[right];
    int i = left-1;
    for (int j=left; j<right; j++){
        if(word_one_are_first_or_equal(words[j], pivot)){
            i++;
            swap(words, i, j);
        }
    }
    swap(words, i+1, right);
    return i+1;
}

int word_one_are_first_or_equal(wchar_t *word1, wchar_t *word2){
    int info = which_should_be_first(word1, word2);
    if(info == WORD_ONE_IS_FIRST || info == WORDS_ARE_EQUAL) return 1;
    return 0;
}

void **quick_sort(wchar_t **words, int left, int right) {
    if(left<right){
        int pivot_index = partition(words, left, right);
        quick_sort(words, left, pivot_index-1);
        quick_sort(words, pivot_index+1, right);
    }
}

void print_words(wchar_t **words) {
    int i = 0;
    while (words[i]) {
        wprintf(L"%ls\n", words[i]);
        i++;
    }
}

void swap(wchar_t **words, int i, int j) {
    wchar_t *temp = words[i];
    words[i] = words[j];
    words[j] = temp;
}