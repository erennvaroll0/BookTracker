# 📚 Book Tracker System

A professional book tracking application developed in C, featuring a modular architecture and dynamic memory management.

## 🚀 Features
- **CRUD Operations:** Add, list, update, and delete books.
- **Data Persistence:** Books are stored permanently in binary format in `books.dat`.
- **Dynamic Memory:** Data is managed at runtime using `malloc` and `realloc`.
- **Modular Structure:** Clean architecture with separated Header (.h) and Source (.c) files.

## 🛠️ Installation & Execution

### Prerequisites
Make sure you have a C compiler (like GCC) installed on your system.

### Compilation
Clone the project to your computer and run the following command in your terminal:

```bash
gcc src/main.c src/book.c -Iinclude -o book_tracker