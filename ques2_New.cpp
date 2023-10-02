#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <chrono>

using namespace std;

string allbooks[100][23];
string allmagazines[81][10];
string alljournals[99][1];

void readCSVBooks(string file_path, char delimiter, bool hasHeaderRow, int rowCount, int columnCount)
{
    string line, word;
    fstream file(file_path);

    if (file.is_open())
    {
        int lineCount = 0;

        while (getline(file, line))
        {
            stringstream str(line);
            int count = 0;
            bool quoteDetected = false;

            while (getline(str, word, delimiter))
            {
                if (!word.empty() && word.front() == '"' && word.back() == '"')
                {
                    allbooks[lineCount][count] = word.substr(1, word.length() - 2);
                    count++;
                }
                else if (!word.empty() && word.front() == '"')
                {
                    allbooks[lineCount][count] = allbooks[lineCount][count] + word.substr(1, word.length() - 1);
                    quoteDetected = true;
                }
                else if (!word.empty() && word.back() == '"')
                {
                    allbooks[lineCount][count] = allbooks[lineCount][count] + delimiter + word.substr(0, word.length() - 1);
                    quoteDetected = false;
                    count++;
                }
                else if (quoteDetected)
                {
                    allbooks[lineCount][count] = allbooks[lineCount][count] + delimiter + word;
                }
                else
                {
                    allbooks[lineCount][count] = allbooks[lineCount][count] + word;
                    count++;
                }
            }
            lineCount++;
        }
    }
}

void readCSVMagazine(string file_path, char delimiter, bool hasHeaderRow, int rowCount, int columnCount)
{
    cout << "In read csv of mag" << endl;
    string line, word;
    fstream file(file_path);

    if (file.is_open())
    {
        int lineCount = 0;

        while (getline(file, line))
        {
            stringstream str(line);
            int count = 0;
            bool quoteDetected = false;

            while (getline(str, word, delimiter))
            {
                if (!word.empty() && word.front() == '"' && word.back() == '"')
                {
                    word.substr(1, word.size() - 2);
                    allmagazines[lineCount][count] = word.substr(1, word.size() - 2);
                    count++;
                }
                else if (!word.empty() && word.front() == '"')
                {
                    allmagazines[lineCount][count] = allmagazines[lineCount][count] + word.substr(1, word.length() - 1);
                    quoteDetected = true;
                }
                else if (!word.empty() && word.back() == '"')
                {
                    allmagazines[lineCount][count] = allmagazines[lineCount][count] + delimiter + word.substr(0, word.length() - 1);
                    quoteDetected = false;
                    count++;
                }
                else if (quoteDetected)
                {
                    allmagazines[lineCount][count] = allmagazines[lineCount][count] + delimiter + word;
                }
                else
                {
                    allmagazines[lineCount][count] = allmagazines[lineCount][count] + word;
                    count++;
                }
            }
            lineCount++;
        }
    }
}

void readCSVJournal(string file_path, char delimiter, bool hasHeaderRow, int rowCount, int columnCount)
{
    cout << "Readig jurnal data" << endl;
    string line, word;
    fstream file(file_path);

    if (file.is_open())
    {
        int lineCount = 0;

        while (getline(file, line))
        {
            stringstream str(line);
            int count = 0;
            bool quoteDetected = false;

            while (getline(str, word, delimiter))
            {
                cout << "Word=" << word << endl;
                if (!word.empty() && word.front() == '"' && word.back() == '"')
                {
                    cout << "Scenario 1" << endl;
                    alljournals[lineCount][count] = word.substr(1, word.length() - 2);
                    count++;
                }
                else if (!word.empty() && word.front() == '"')
                {
                    alljournals[lineCount][count] = alljournals[lineCount][count] + word.substr(1, word.length() - 1);
                    quoteDetected = true;
                }
                else if (!word.empty() && word.back() == '"')
                {
                    alljournals[lineCount][count] = alljournals[lineCount][count] + delimiter + word.substr(0, word.length() - 1);
                    quoteDetected = false;
                    count++;
                }
                else if (quoteDetected)
                {
                    alljournals[lineCount][count] = alljournals[lineCount][count] + delimiter + word;
                }
                else
                {
                    alljournals[lineCount][count] = alljournals[lineCount][count] + word;
                    count++;
                }
            }
            lineCount++;
        }
    }
}

enum class ItemType
{
    Physical,
    Electronic
};

string getItemTypeString(ItemType itemType)
{
    if (itemType == ItemType::Physical)
    {
        return "Physical";
    }
    else
    {
        return "Electronic";
    }
};

// Base class
class Item
{
protected:
    string title;
    int identifier;
    string type;
    ItemType itemType;

public:
    // Constructor
    Item() {}
    // Getter for title
    string gettitle()
    {
        return title;
    }
    Item(string title, int itemid)
    {
        this->title = title;
        this->identifier = itemid;
    }
    // getter for identifier
    int getidentifier()
    {
        return identifier;
    }
};

// Modified derived class
class Book : public Item
{
public:
    // Additional attributes for Book
    static int bookId;
    int booksCount;
    int isbn;
    string authors;
    // Constructor for Book
public:
    Book() {}
    Book(
        int booksCount,
        int isbn,
        string title,
        string authors)

    {
        this->identifier = (bookId++);
        this->type = "Book";
        this->title = title;
        this->itemType = ItemType::Physical;
        this->bookId = bookId;
        this->isbn = isbn;
        this->booksCount = booksCount;
        this->authors = authors;
    }
    void display()
    {
        cout << this->title << endl;
    }
    // Getter for bookCount
    int getbooksCount()
    {
        return booksCount;
    }
    // Setter for booksCount
    void setbooksCount(int count)
    {
        this->booksCount = count;
    }
    // Getter for ISBN
    int getISBN()
    {
        return isbn;
    }
    // Getter for author
    string getAuthor()
    {
        return authors;
    }
};
int Book::bookId = 1;

class Publication : public Item
{
private:
    static int publishId;

public:
    Publication() {}
    Publication(
        string publication)
    {
        this->identifier = (publishId++);
        this->type = "Publication";
        this->title = publication;
        this->itemType = ItemType::Electronic;
    }
    void display()
    {
        cout << this->title << endl;
    }
};

int Publication ::publishId = 1;
class Journal : public Item
{
private:
    static int journalId;

public:
    Journal() {}
    Journal(string title)
    {
        this->identifier = (journalId++);
        this->type = "Publication";
        this->title = title;
        this->itemType = ItemType::Electronic;
    }
    void display()
    {
        cout << this->title << endl;
    }

    // Add a method to get the title
    string getTitle() const
    {
        return title;
    }
};
int Journal ::journalId = 2;

class User
{
private:
    string password;
    string userName;
    static int userIndex;
    string type;
    string userId;

public:
    User() {}

    User(string &userName, string &password, string &type)
    {
        this->userName = userName;
        this->password = password;
        this->userId = "user" + to_string(userIndex++);
        this->type = type;
    }
    string gettype()
    {
        return type;
    }
    string getuserId()
    {
        return userId;
    }
    string getUserName()
    {
        return userName;
    }
    string getPassword()
    {
        return password;
    }
};
int User ::userIndex = 1;

class issueInfo
{
private:
    string identifier;
    string borrowDate;
    string returnDate;
    User userId;
    string title;

public:
    issueInfo() {}

    string setBorrowDateToCurrentDate()
    {
        string borrowDate1;
        {
            auto currentTime = chrono::system_clock::now();
            time_t currentTimeT = chrono::system_clock::to_time_t(currentTime);
            return (ctime(&currentTimeT));
        }

        // borrowDate = to_string(borrowDate1);
    }
    // Function to calculate return date
    // CORRECT THE RETURN DATE FUNCTION
    string calculateReturnDate()
    {
        if (userId.gettype() == "Faculty")
        {
            // Return date for faculty: 1 month from the borrow date
            time_t borrowTimeT;
            struct tm tm;
            if (strptime(borrowDate.c_str(), "%c", &tm))
            {
                borrowTimeT = mktime(&tm);
                borrowTimeT += 30 * 24 * 60 * 60; // Add 30 days
                return ctime(&borrowTimeT);
            }
        }
        else // if (userId.gettype() == "Student")
        {
            // Return date for students: 6 months from the borrow date
            time_t borrowTimeT;
            struct tm tm;
            if (strptime(borrowDate.c_str(), "%c", &tm))
            {
                borrowTimeT = mktime(&tm);
                borrowTimeT += 6 * 30 * 24 * 60 * 60; // Add 6 months (approximate)
                return ctime(&borrowTimeT);
            }
        }
        return "";
    }
    issueInfo(int identifier, string title, User userId)
    {
        this->identifier = identifier;
        this->borrowDate = setBorrowDateToCurrentDate();
        this->returnDate = calculateReturnDate();
        this->userId = userId;
        this->title = title;
    }

    void display()
    {
        cout << "User ID : " << userId.getuserId() << endl;
        cout << "Title of the item : " << this->title << endl;
        cout << "Borrow Date of item : " << this->borrowDate << endl;
        cout << "Return Date of item : " << this->returnDate << endl;
    }

    // string setBorrowDateNew()
    // {
    //     auto currentTime = chrono::system_clock::now();
    //     auto borrowTime = currentTime + chrono::hours(7 * 24);  // Add 7 days (7 * 24 hours) to the current time
    //     time_t borrowTimeT = chrono::system_clock::to_time_t(borrowTime);
    //     return ctime(&borrowTimeT);
    // }

    // void display2()
    // {
    //     cout << "User ID : " << userId.getuserId() << endl;
    //     cout << "Title of the item : " << this->title << endl;
    //     cout << "Borrow Date of item : " << this->borrowDate << endl;
    //     cout << "Return Date of item : " << this->returnDate << endl;
    // }
};

class Library
{
public:
    Book books[100];
    Publication magazines[81];
    Journal journal[100];
    int bookIndex = 1;
    int magazineIndex = 1;
    int journalIndex = 1;
    issueInfo info[100];
    string item;
    User userNames[100];
    int userIndex = 1;

public:
    Library() {}
    void addBook(Book book)
    {
        books[bookIndex++] = book;
    }

    void addMagazine(Publication magazine)
    {
        magazines[magazineIndex++] = magazine;
    }

    void addJournal(Journal journal)
    {
        this->journal[journalIndex++] = journal;
    }

    // Function to add user login details
    void userlogin(string userName, string password, string type)
    {
        User newUser(userName, password, type);
        userNames[userIndex++] = newUser;
    }

    // Function to check if a user with the given username and password exists
    bool existingAuthentication(string userName, string password)
    {
        for (int i = 1; i < userIndex; i++)
        {
            cout << userNames[i].getUserName();
            cout << userNames[i].getPassword();

            if (userNames[i].getUserName() == userName && userNames[i].getPassword() == password)
            {
                return true; // User exists
            }
        }
        return false; // User doesn't exist
    }
    int borrow(User user, int n, string title)
    {
        int item; int value =0;
        bool flag = false;
        if (n == 1) // Book
        {
            for (int i = 1; i < 100; i++)
            {
                if (books[i].gettitle() == title)
                {
                    if (books[i].getbooksCount() > 0)
                    {
                        flag = true;
                        int count = books->getbooksCount();
                        count--;
                        books[i].setbooksCount(count);
                        item = books[i].getidentifier();
                        cout << "Book is available" << endl;
                        value = 1;
                        break;
                    }
                }
            }
            if (flag == true)
            {
                // true indicates that item is found from self library
                issueInfo obj(item, title, user);
                obj.display();
                return value; // 1 for True.
            }
            else if (flag == false)
            {
                return value;
            }
        }
    
        else if(n==2)
        {
            for (int i = 1; i < 81; i++)
            {
                if (magazines[i].gettitle() == title )
                {
                    flag = true;
                    break;
                }
            }
            if (flag == false)
            {
                cout << "Magazine is not available." << endl;
                return 0;
            }
            else if (flag == true)
            {
                int item = magazines->getidentifier();
                issueInfo obj(item,title, user);
                cout << "Magazine is available." << endl;
                obj.display();
                return 1;
            }
        }
        else if (n==3)
        {
            for (int i = 1; i < 100; i++)
            {
                if (journal[i].gettitle() == title )
                {
                    cout << "Journal is available." << endl;
                    item = journal->getidentifier();
                    flag = true;
                    break;
                }
            }
            if (flag == true)
            {
                issueInfo obj(item,title, user);
                cout << "Journal is  available." << endl;
                return 1;
                obj.display();
            }
            else
            {
                cout << "Journal is not available." << endl;
                return 0;
            }
         }
         return value;
    }
    

    void location(User user, int locSearchType, string title, string author, int isbn)
    {

        int id;
        int loc;
        switch (locSearchType)
        {
        case 1: // title
        {
            for (int i = 1; i < 100; i++)
            {
                if (books[i].gettitle() == title)
                {
                    cout << books[i].getidentifier();
                    id = books[i].getidentifier();
                    loc = id;
                    loc = loc % 20; // Each shelf has 20 books
                    cout << "Location of the book is at the shelf number - " << loc << " Kindly access from there. Thanks !!" << endl;
                    break;
                }
            }
            break;
        }
        case 2: // author
        {
            for (int i = 1; i < 100; i++)
            {
                if (books[i].getAuthor() == author)
                {
                    id = books[i].getidentifier();
                    loc = id;
                    loc = loc % 20; // Each shelf has 20 books
                    cout << "Location of the book is at the shelf number - " << loc << "Kindly access from there. Thanks !!" << endl;
                    break;
                }
            }
            break;
        }
        case 3: // isbn
        {
            for (int i = 1; i < 100; i++)
            {
                if (books[i].getISBN() == isbn)
                {
                    id = books[i].getidentifier();
                    loc = id;
                    loc = loc % 20; // Each shelf has 20 books
                    cout << "Location of the book is at the shelf number - " << loc << "Kindly access from there. Thanks !!" << endl;
                    break;
                }
            }
            break;
        }
        }
    }
};

int main()
{
    Library *lib = new Library();
    Library *lib2 = new Library();
    User user;
    Book book1(9, 56789, "xyz", "Vani");
    lib2->books[0] = book1;
    Book book2(11, 123456, "The positive path", "AK");
    lib2->books[1] = book2;

    // Read book data
    readCSVBooks("books.csv", ',', true, 100, 23);
    for (int i = 1; i < 100; i++)
    {
        Book item(stoi(allbooks[i][5]), stoi(allbooks[i][6]), allbooks[i][10], allbooks[i][7]);
        item.display();
        lib->addBook(item);
    }

    // Read magazine data
    readCSVMagazine("magazines.csv", ',', true, 81, 10);
    for (int i = 1; i < 81; i++)
    {
        Publication item(allmagazines[i][0]);
        item.display();
        lib->addMagazine(item);
    }

    // Read journal data
    readCSVJournal("journals.csv", ',', true, 99, 1);
    for (int i = 1; i < 100; i++)
    {
        Journal item(alljournals[i][0]);
        item.display();
        lib->addJournal(item);
    }

    int n;
    string name, typeUser, password, title, author; string userType;
    int isbn;
    int x;
    cout << "Enter the user type Student | Teacher" << endl;
    getline(cin, userType);
    cout << "Enter the type of the file. Press (1) if it is a book. Press (2) if it is a magazine. Press (3) if it is a journal." << endl;
    cin >> n;
    cin.ignore(); // Consume newline character
    cout << "Select the service by pressing the number respectively" << endl;
    cout << "Enter the title of the item you want to issue: ";
    getline(cin, title);
    int value = lib->borrow(user, n, title);
    //cout << value << endl;
    if (value == 0)
    {
        cout << "In LIB2" << endl;
        //int item; 
         for (int i = 0; i <= lib2->bookIndex; i++)
            {
                if (lib2->books[i].gettitle() == title)
                {
                    if (lib2->books[i].getbooksCount() > 0)
                    {
                        string displayBooks = lib2->books[i].gettitle();
                        cout << displayBooks << endl; 
                        int count = lib2->books[i].getbooksCount();
                        count--;
                        lib2->books[i].setbooksCount(count);
                        //item = lib2->books[i].getidentifier();
                        cout << "Book is available in the second library (lib2)." << endl;
                        time_t currentTime;
                        time(&currentTime);
                        const int secondsInADay = 24 * 60 * 60;
                        time_t borrowTime = currentTime + 7 * secondsInADay;
                        struct tm* borrowDate = localtime(&borrowTime);
                        cout << "Borrow Date: " << asctime(borrowDate);

                        // return date
                        struct tm returnDate = *borrowDate; // copy borrow date to return date
                        if (userType == "student") 
                        {
                            // Add 1 month (approximately 30 days)
                            returnDate.tm_mon++; 
                            if (returnDate.tm_mon > 11) 
                            { 
                            returnDate.tm_mon = 0;  // Wrap around to January
                            returnDate.tm_year++;  // Move to the next year
                            } 
                        }
                        else if (userType == "teacher") 
                        {
                            // Add 6 months (approximately 180 days)
                            returnDate.tm_mon += 6;
                            if (returnDate.tm_mon > 11) 
                            {
                                returnDate.tm_mon %= 12;                            returnDate->tm_hour = borrowDate->tm_hour; // Hours
                                returnDate.tm_year++;
                            }
                        }
                        time_t returnTime = mktime(&returnDate);
                        cout << "Return Date and Time: " << asctime(&returnDate);

                        value = 1;
                        break;
                    }
                }
            }
    }
             if (value == 0)
             {
                cout << "Book is not available in any libaray." << endl;
             }

    return 0;
}
