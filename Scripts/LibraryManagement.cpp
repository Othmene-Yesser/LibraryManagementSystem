#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class Book
{
    private:
        string title;
        string author;
        string date;
        string ISBN;

    public:
        // We assign each variable with its perspective value :D
        Book(const string& title, const string& author, const string& date, const string& ISBN):title(title),author(author),date(date),ISBN(ISBN){}

        string GetTitle() const
        {
            return title;
        }
        string GetAuthor() const
        {
            return author;
        }
        string GetDate() const 
        {
            return date;
        }
        string GetISBN() const
        {
            return ISBN;
        }
        string Display() const
        {
            cout <<"Title: "<<title <<", Author: "<< author <<", Date: "<< date << ", ISBN: " <<ISBN<< endl;
        }
        string BookToString() const 
        {
            return title + ";" + author + ":" + date + "|" + ISBN;
        }
};
class Library
{
    private:
        string fileName;
        vector<Book> books; // We use vector because we don't know how many books we have it's like an array but it's dynamic ;)

        void LoadBooksFromFile()
        {
            ifstream inFile(fileName);
            string line;
            while (getline(inFile,line)) // It checks if the ifstream 'inFile' has no errors  then returns !fail()
            {
                size_t pos1 = line.find(';');
                size_t pos2 = line.find(':');
                size_t pos3 = line.find('|');
                if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) // If one the pos werent found we don't execute these lines of code 
                {
                    string title = line.substr(0, pos1);
                    string author = line.substr(pos1, pos2);
                    string date = line.substr(pos2, pos3);
                    string ISBN = line.substr(pos3 + 1);
                    books.emplace_back(title,author,date,ISBN);
                }
            }
        }

        void SaveBooksToFile() const
        {
            ofstream outFile(fileName);
            for (const auto& book : books) // Basically a foreach loop "for each Book in books" the const variable just to make sure that we read only from the vector
            {
                outFile << book.BookToString() << endl;
            }
        }

        public:
            Library(const string& fileName):fileName(fileName)
            {
                LoadBooksFromFile(); // Load all book on the moment we construct the library
            }
            void AddBook(const string& title, const string& author, const string& date, const string& ISBN)
            {
                books.emplace_back(title,author,date,ISBN);
                SaveBooksToFile();
            }
            void DisplayAllBooks()const
            {
                for (const auto& book : books) 
                {
                    book.Display();
                }
            }
            void SearchByTitle(const string& title)const
            {
                for (const auto& book : books) 
                {
                    if (book.GetTitle() == title)
                    {
                        book.Display();
                        return;
                    }
                }
                cout << "No book was found with this Title: "<< title<< endl;
            }
            void SearchByAuthor(const string& author)const
            {
                for (const auto& book : books) 
                {
                    if (book.GetAuthor() == author)
                    {
                        book.Display();
                        return;
                    }
                }
                cout << "No book was found with this Author: "<< author<< endl;
            }
            void SearchByDate(const string& date)const
            {
                bool displayedAtLeastOne = false;
                for (const auto& book : books)
                {
                    if (book.GetDate() == date)
                    {
                        book.Display();
                        displayedAtLeastOne = true;
                    }
                }
                if (!displayedAtLeastOne)
                {
                    cout << "No book was found with this Date: "<< date<< endl;
                }
            }
            void SearchByISBN(const string& ISBN)const
            {
                for (const auto& book : books)
                {
                    if (book.GetISBN() == ISBN)
                    {
                        book.Display();
                        return;
                    }
                }
                cout << "No book was found with this ISBN: "<< ISBN<< endl;
            }
};



int main()
{
    Library library("MyLibrary.txt");
    int choice;
    string title, author, date, ISBN;

    while (true)
    {
        cout << "\nLibrary Management System\n";
        cout << "1. Add a new book\n";
        cout << "2. Remove a book\n";
        cout << "3. Display all books\n";
        cout << "4. Search for a book by title\n";
        cout << "5. Search for a book by author\n";
        cout << "6. Search for a book by date 'Note: It will display all books with that date' \n";
        cout << "7. Search for a book by ISBN\n";
        cout << "8. Sort Library \n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1:
                // Add Book
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book date: ";
                getline(cin, date);
                cout << "Enter book ISBN: ";
                getline(cin, ISBN);
                library.AddBook(title, author, date, ISBN);
                cout << "Book added successfully.\n";
                break;
            case 2:
                // Remove Book
                break;
            case 3:
                // Display all books
                library.DisplayAllBooks();
                break;
            case 4:
                // Search by title 
                cout << "Enter book title to search: ";
                getline(cin, title);
                library.SearchByTitle(title);
                break;
            case 5:
                // Search by author 
                cout << "Enter book author to search: ";
                getline(cin, author);
                library.SearchByAuthor(author);
                break;
            case 6:
                // Search by date
                break;
            case 7:
                // Search by ISBN 
                break;
            case 8:
                // Sort Library
                break;;
            case 9:
                // Exit
                cout << "Exiting the system. Goodbye!\n";
                return 0;
            default:
                // ???
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
    

    cout << "Hello World!"<< endl;
    return 0;
}