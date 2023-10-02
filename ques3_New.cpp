#include <iostream>
#include <string>

using namespace std;

// Define the maximum number of library items
const int MAX_LIBRARY_ITEMS = 4;

// Define a struct for library items
struct LibraryItem {
    string name;
    double cost;
    bool isAvailable;
};

// Function to search for a library item by name
LibraryItem* searchLibraryItem(LibraryItem items[], int itemCount, const string& itemName) {
    for (int i = 0; i < itemCount; i++) {
        if (items[i].name == itemName) {
            return &items[i];
        }
    }
    return nullptr; // Item not found
}

// Function to borrow a library item
bool borrowLibraryItem(LibraryItem items[], int itemCount, const string& itemName) {
    LibraryItem* itemToBorrow = searchLibraryItem(items, itemCount, itemName);
    if (itemToBorrow != nullptr && itemToBorrow->isAvailable) {
        itemToBorrow->isAvailable = false;
        return true; // Item borrowed successfully
    } else {
        return false; // Item not found or not available
    }
}

int main() {
    // Sample library items
    LibraryItem libraryItems[MAX_LIBRARY_ITEMS] = {
        {"Book 1", 10.0, true},
        {"Book 2", 15.0, true},
        {"Magazine 1", 5.0, true},
        {"Magazine 2", 3.0, true}
    };

    int itemCount = MAX_LIBRARY_ITEMS;

    string itemToBorrow;
    cout << "Enter the name of the item you want to borrow: ";
    getline(cin, itemToBorrow);

    // Attempt to borrow the library item
    bool success = borrowLibraryItem(libraryItems, itemCount, itemToBorrow);

    if (success) {
        cout << "Item '" << itemToBorrow << "' borrowed successfully." << endl;
    } else {
        cout << "Item '" << itemToBorrow << "' not found or not available." << endl;
    }

    return 0;
}
