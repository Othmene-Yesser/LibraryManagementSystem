#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <filesystem>

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
        void Display() const
        {
            cout <<"Title: "<<title <<", Author: "<< author <<", Date: "<< date << ", ISBN: " <<ISBN<< endl;
        }
        string BookToString() const 
        {
            return title + ";" + author + ";" + date + ";" + ISBN;
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
                int pos1 = line.find(';');
                int pos2 = line.find(';', pos1 + 1);
                int pos3 = line.find(';', pos2 + 1);

                if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) // If one the pos werent found we don't execute these lines of code 
                {
                    string title = line.substr(0, pos1);
                    string author = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
                    string ISBN = line.substr(pos3 + 1);
                    books.emplace_back(title,author,date,ISBN);
                }
            }
            inFile.close();
        }

        void SaveBooksToFile() const
        {
            ofstream outFile(fileName);
            for (const auto& book : books) // Basically a foreach loop "for each Book in books" the const variable just to make sure that we read only from the vector
            {
                outFile << book.BookToString() << endl;
            }
            outFile.close();
        }
        void SaveBooksToFile(int x) const // Overloaded method so that it only saves the books exxcept the one numbered 'x'
        {
            int k = 0;
            ofstream outFile(fileName);
            for (const auto& book : books)
            {
                if (k != x)
                {
                    outFile << book.BookToString() << endl;
                }
                k++;
            }
            outFile.close();
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
            void RemoveBook(int x)
            {
                // We save all the books except the one we will delete then we clear our books then we load them again
                SaveBooksToFile(x);
                books.clear();
                LoadBooksFromFile();
            }
            void DisplayAllBooks()const
            {
                for (const auto& book : books) 
                {
                    book.Display();
                }
            }
            void SearchByTitle(const string& title, bool remove = false)
            {
                int x = 0;
                for (const auto& book : books) 
                {
                    if (book.GetTitle() == title)
                    {
                        if (remove)
                        {
                            RemoveBook(x);
                            return;
                        }
                        book.Display();
                        return;
                    }
                    x++;
                }
                cout << "No book was found with this Title: "<< title<< endl;
            }
            void SearchByAuthor(const string& author, bool remove = false)
            {
                bool hasFound = false;
                int x = 0;
                for (const auto& book : books) 
                {
                    if (book.GetAuthor() == author)
                    {
                        if (remove)
                        {
                            RemoveBook(x);
                            return;
                        }
                        book.Display();
                        hasFound = true;
                    }
                    x++;
                }
                if (!hasFound)
                {
                    cout << "No book was found with this Author: "<< author<< endl;
                }
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
            void SearchByISBN(const string& ISBN, bool remove = false)
            {
                int x = 0;
                for (const auto& book : books)
                {
                    if (book.GetISBN() == ISBN)
                    {
                        if (remove)
                        {
                            RemoveBook(x);
                        }
                        book.Display();
                        return;
                    }
                    x++;
                }
                cout << "No book was found with this ISBN: "<< ISBN<< endl;
            }
            /*
            void SortByISBN()
            {
                bool hasSwapped = false;
                
            }
            */
};

string ReadDate()
{
    int day;
    int month;
    int year;

    cout << "dd = ";
    cin >> day;
    cout <<"mm = ";
    cin >> month;
    cout << "yyyy = ";
    cin >> year;

    return to_string(day)+"-"+to_string(month)+"-"+to_string(year);
}


int main()
{
    // Make sure you change your directory based on your needs :D 
    Library library("D:\\C++Project\\LibraryManagementSystem\\Scripts\\Library.txt");
    int choice;
    string title, author, date, ISBN;
    filesystem::path current_path = filesystem::current_path();
    cout << "Current working directory: " << current_path << endl;

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
        //cout << "8. Sort Library \n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        cout << "----------------------------------"<< endl;

        switch (choice)
        {
            case 1:
                // Add Book
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book ISBN: ";
                getline(cin, ISBN);
                cout << "Enter book date: "<<endl;
                date = ReadDate();
                library.AddBook(title, author, date, ISBN);
                cout << "Book added successfully.\n";
                break;
            case 2:
                // Remove Book
                cout << "1. Delete by Title \n";
                cout << "2. Delete by Author \n";
                cout << "3. Delete by ISBN \n";
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();

                switch(choice)
                {
                    case 1:
                        // Delete by Title
                        cout << "Enter book title to delete: ";
                        getline(cin, title);
                        library.SearchByTitle(title, true);
                        break;
                    case 2:
                        // Delete by Author
                        cout << "Enter book author to delete: ";
                        getline(cin, author);
                        library.SearchByAuthor(author, true);
                        break;
                    case 3:
                        // Delete by ISBN
                        cout << "Enter book ISBN to delete: ";
                        getline(cin, ISBN);
                        library.SearchByISBN(ISBN, true);
                        break;
                    default:
                        // ???
                        cout << "Invalid choice. Please try again.\n";
                        break;
                }
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
                cout << "Enter book date to search: "<< endl;
                date = ReadDate();
                library.SearchByDate(date);
                break;
            case 7:
                // Search by ISBN 
                cout << "Enter book ISBN to search: ";
                getline(cin, ISBN);
                library.SearchByISBN(ISBN);
                break;
            /*
            case 8:
                // Sort Library
                cout << "1. Sort by Title \n";
                cout << "2. Sort by Author \n";
                cout << "3. Sort by Date \n";
                cout << "4. Sort by ISBN \n";
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();

                switch(choice)
                {
                    case 1:
                        // Sort by Title
                        break;
                    case 2:
                        // Sort by Author
                        break;
                    case 3:
                        // Sort by Date
                        break;
                    case 4:
                        // Sort by ISBN
                        break;
                    default:
                        // ???
                        cout << "Invalid choice. Please try again.\n";
                        break;
                }

                break;
            */
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
    
    return 420;
}