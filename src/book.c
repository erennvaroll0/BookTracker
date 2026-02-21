#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/book.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int load_books(Book **list, int *count) {
    FILE *file = fopen(DB_FILE, "rb");
    if (!file) {
        *count = 0;
        *list = NULL;
        return 0;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    if (size <= 0) {
        *count = 0;
        *list = NULL;
        fclose(file);
        return 0;
    }
    
    *count = size / sizeof(Book);
    *list = malloc(size);
    if (*list) fread(*list, sizeof(Book), *count, file);
    fclose(file);
    return 1;
}

int save_books(const Book *list, int count) {
    FILE *file = fopen(DB_FILE, "wb");
    if (!file) return 0;
    if (count > 0 && list != NULL) {
        fwrite(list, sizeof(Book), count, file);
    }
    fclose(file);
    return 1;
}

void list_books(const Book *list, int count) {
    if (count == 0 || list == NULL) {
        printf("\n[!] No books found in the library.\n");
        return;
    }
    printf("\n--- Registered Books (%d) ---\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d. %-20s | Page: %d\n", i + 1, list[i].title, list[i].current_page);
    }
}

int search_book(const Book *list, int count, const char *query) {
    for (int i = 0; i < count; i++) {
        if (strstr(list[i].title, query)) return i;
    }
    return -1;
}

void delete_book(Book **list, int *count, int index) {
    for (int i = index; i < (*count) - 1; i++) {
        (*list)[i] = (*list)[i + 1];
    }
    (*count)--;
    if (*count > 0) {
        *list = realloc(*list, (*count) * sizeof(Book));
    } else {
        free(*list);
        *list = NULL;
    }
    save_books(*list, *count);
}

void update_page(Book *list, int index, int new_page) {
    list[index].current_page = new_page;
}