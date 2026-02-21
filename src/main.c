#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/book.h"

int main() {
    Book *book_list = NULL;
    int book_count = 0;
    int choice;

    // Load existing data from file at startup
    load_books(&book_list, &book_count);

    do {
        printf("\n==============================");
        printf("\n   BOOK TRACKER SYSTEM v2.0");
        printf("\n==============================");
        printf("\n1. Add New Book");
        printf("\n2. Search Book");
        printf("\n3. List All Books");
        printf("\n4. Update Progress (Page)");
        printf("\n5. Delete Book");
        printf("\n6. Safe Exit");
        printf("\nYour Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {
                Book new_book;
                printf("Enter Title: ");
                fgets(new_book.title, MAX_NAME, stdin);
                new_book.title[strcspn(new_book.title, "\n")] = 0;
                printf("Current Page: ");
                scanf("%d", &new_book.current_page);
                
                book_count++;
                book_list = realloc(book_list, book_count * sizeof(Book));
                book_list[book_count - 1] = new_book;
                save_books(book_list, book_count);
                printf("\n[OK] Book added successfully.\n");
                break;
            }
            case 2: {
                char query[MAX_NAME];
                printf("Search title: ");
                fgets(query, MAX_NAME, stdin);
                query[strcspn(query, "\n")] = 0;
                int idx = search_book(book_list, book_count, query);
                if (idx != -1) 
                    printf("\n[FOUND] %s - Page %d\n", book_list[idx].title, book_list[idx].current_page);
                else 
                    printf("\n[!] Book not found.\n");
                break;
            }
            case 3:
                list_books(book_list, book_count);
                break;
            case 4: {
                list_books(book_list, book_count);
                if (book_count == 0) break;
                int idx, new_p;
                printf("\nUpdate Book ID: ");
                scanf("%d", &idx);
                if (idx > 0 && idx <= book_count) {
                    printf("New page number: ");
                    scanf("%d", &new_p);
                    update_page(book_list, idx - 1, new_p);
                    save_books(book_list, book_count);
                    printf("\n[OK] Progress updated.\n");
                }
                break;
            }
            case 5: {
                list_books(book_list, book_count);
                if (book_count == 0) break;
                int idx;
                printf("\nDelete Book ID: ");
                scanf("%d", &idx);
                if (idx > 0 && idx <= book_count) {
                    delete_book(&book_list, &book_count, idx - 1);
                    printf("\n[OK] Book removed from list.\n");
                }
                break;
            }
        }
    } while (choice != 6);

    printf("\nData saved. See you next time!\n");
    if (book_list) free(book_list);
    return 0;
}