#ifndef BOOK_H
#define BOOK_H

#define MAX_NAME 100
#define DB_FILE "books.dat"

typedef struct {
    char title[MAX_NAME];
    int current_page;
} Book;


int load_books(Book **list, int *count);
int save_books(const Book *list, int count);
void list_books(const Book *list, int count);
int search_book(const Book *list, int count, const char *query);


void delete_book(Book **list, int *count, int index);
void update_page(Book *list, int index, int new_page);


void clear_input_buffer();

#endif