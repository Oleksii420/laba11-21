#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    int pages;
    int year;

    Book(const string& title, const string& author, int pages, int year)
        : title(title), author(author), pages(pages), year(year) {}

    void display() const {
        cout << "Назва: " << title << ", Автор: " << author
             << ", Кількість сторінок: " << pages << ", Рік видання: " << year << endl;
    }
};

vector<Book> loadBooksFromFile(const string& filename) {
    vector<Book> books;
    ifstream file(filename);

    if (file.is_open()) {
        string title, author;
        int pages, year;

        while (getline(file, title) && getline(file, author) && (file >> pages >> year)) {
            file.ignore();
            books.emplace_back(title, author, pages, year);
        }
        file.close();
    } else {
        cerr << "Не вдалося відкрити файл." << endl;
    }

    return books;
}

void searchByAuthor(const vector<Book>& books, const string& author) {
    bool found = false;
    for (const auto& book : books) {
        if (book.author == author) {
            book.display();
            found = true;
        }
    }
    if (!found) {
        cout << "Книг цього автора не знайдено." << endl;
    }
}

void searchByTitle(const vector<Book>& books, const string& title) {
    bool found = false;
    for (const auto& book : books) {
        if (book.title == title) {
            book.display();
            found = true;
        }
    }
    if (!found) {
        cout << "Книгу з такою назвою не знайдено." << endl;
    }
}

int main() {
    vector<Book> books = loadBooksFromFile("books.txt");

    string searchAuthor, searchTitle;
    cout << "Введіть автора для пошуку: ";
    getline(cin, searchAuthor);
    searchByAuthor(books, searchAuthor);

    cout << "\nВведіть назву книги для пошуку: ";
    getline(cin, searchTitle);
    searchByTitle(books, searchTitle);

    return 0;
}
