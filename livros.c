#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a book
typedef struct Book {
    int code;
    char title[100];
    char author[100];
    int year;
    struct Book *next;
} Book;

// Structure to represent a category
typedef struct Category {
    char name[100];
    Book *books;
    struct Category *next;
} Category;

// Structure to represent the library
typedef struct Library {
    Category *categories;
} Library;

// Function to create a new book
Book* createBook(int code, char title[], char author[], int year) {
    Book *newBook = (Book*)malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newBook->code = code;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->year = year;
    newBook->next = NULL;
    return newBook;
}

// Function to create a new category
Category* createCategory(char name[]) {
    Category *newCategory = (Category*)malloc(sizeof(Category));
    if (newCategory == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newCategory->name, name);
    newCategory->books = NULL;
    newCategory->next = NULL;
    return newCategory;
}

// Function to insert a book into a category
void insertBook(Category *category, Book *newBook) {
    if (category->books == NULL) {
        category->books = newBook;
    } else {
        Book *temp = category->books;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
}

// Function to list all books in a category
void listBooks(Category *category) {
    printf("Books in category '%s':\n", category->name);
    Book *temp = category->books;
    while (temp != NULL) {
        printf("Code: %d, Title: %s, Author: %s, Year: %d\n", temp->code, temp->title, temp->author, temp->year);
        temp = temp->next;
    }
}

// Function to search for a book by title in a category (linear search)
Book* searchBook(Category *category, char title[]) {
    Book *temp = category->books;
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Function to delete a book by code from a category
void deleteBook(Category *category, int code) {
    Book *temp = category->books;
    Book *prev = NULL;
    while (temp != NULL && temp->code != code) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Book not found!\n");
        return;
    }
    if (prev == NULL) {
        category->books = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("Book with code %d deleted successfully!\n", code);
}

// Function to update book information
void updateBook(Book *book, char title[], char author[], int year) {
    strcpy(book->title, title);
    strcpy(book->author, author);
    book->year = year;
}


int main() {
    // Create a library
    Library library;
    library.categories = NULL;

    // Create categories
    Category *category1 = createCategory("Fiction");
    Category *category2 = createCategory("Non-Fiction");

    // Insert categories into the library
    library.categories = category1;
    category1->next = category2;

    // Insert books into categories
    insertBook(category1, createBook(1, "Harry Potter", "J.K. Rowling", 1997));
    insertBook(category1, createBook(2, "Lord of the Rings", "J.R.R. Tolkien", 1954));
    insertBook(category2, createBook(3, "Sapiens", "Yuval Noah Harari", 2011));
    insertBook(category2, createBook(4, "Cosmos", "Carl Sagan", 1980));

    int choice;
    char title[100];
    int code, year;
    char author[100];

    do {
        printf("\nMenu:\n");
        printf("1. List books in a category\n");
        printf("2. Search for a book\n");
        printf("3. Update book information\n");
        printf("4. Delete a book\n");
      
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter category name: ");
                scanf("%s", title);
                Category *cat = library.categories;
                while (cat != NULL) {
                    if (strcmp(cat->name, title) == 0) {
                        listBooks(cat);
                        break;
                    }
                    cat = cat->next;
                }
                if (cat == NULL) {
                    printf("Category not found!\n");
                }
                break;

            case 2:
                printf("Enter book title to search: ");
                scanf("%s", title);
                cat = library.categories;
                while (cat != NULL) {
                    Book *book = searchBook(cat, title);
                    if (book != NULL) {
                        printf("Book found in category '%s':\n", cat->name);
                        printf("Code: %d, Title: %s, Author: %s, Year: %d\n", book->code, book->title, book->author, book->year);
                        break;
                    }
                    cat = cat->next;
                }
                if (cat == NULL) {
                    printf("Book not found!\n");
                }
                break;

            case 3:
                printf("Enter book code to update: ");
                scanf("%d", &code);
                printf("Enter new title: ");
                scanf("%s", title);
                printf("Enter new author: ");
                scanf("%s", author);
                printf("Enter new year: ");
                scanf("%d", &year);
                cat = library.categories;
                while (cat != NULL) {
                    Book *book = searchBook(cat, title);
                    if (book != NULL) {
                        updateBook(book, title, author, year);
                        printf("Book information updated successfully!\n");
                        break;
                    }
                    cat = cat->next;
                }
                if (cat == NULL) {
                    printf("Book not found!\n");
                }
                break;

            case 4:
                printf("Enter category name: ");
                scanf("%s", title);
                cat = library.categories;
                while (cat != NULL) {
                    if (strcmp(cat->name, title) == 0) {
                        printf("Enter book code to delete: ");
                        scanf("%d", &code);
                        deleteBook(cat, code);
                        break;
                    }
                    cat = cat->next;
                }
                if (cat == NULL) {
                    printf("Category not found!\n");
                }
                break;
        }
    } while (choice);

    return 0;
}
