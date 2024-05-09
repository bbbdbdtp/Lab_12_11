#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct HelpEntry {
    string term;
    string explanation;
    HelpEntry* next;
};

void addHelpEntry(HelpEntry*& head, const string& term, const string& explanation) {
    HelpEntry* newEntry = new HelpEntry;
    newEntry->term = term;
    newEntry->explanation = explanation;
    newEntry->next = nullptr;

    if (head == nullptr)
        head = newEntry;
    else {
        HelpEntry* current = head;
        while (current->next != nullptr)
            current = current->next;
        current->next = newEntry;
    }
}

void printHelp(HelpEntry* head) {
    HelpEntry* current = head;
    while (current != nullptr) {
        cout << "Term: " << current->term << endl;
        cout << "Explanation: " << current->explanation << endl << endl;
        current = current->next;
    }
}

string findExplanation(HelpEntry* head, const string& term) {
    HelpEntry* current = head;
    while (current != nullptr) {
        if (current->term == term)
            return current->explanation;
        current = current->next;
    }
    return "Explanation not found.";
}

void saveHelpEntriesToFile(HelpEntry* head, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        HelpEntry* current = head;
        while (current != nullptr) {
            outFile << current->term << ":" << current->explanation << endl;
            current = current->next;
        }
        outFile.close();
        cout << "Help entries saved to file successfully." << endl;
    }
    else
        cout << "Unable to open file for writing." << endl;
}

void loadHelpEntriesFromFile(HelpEntry*& head, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string term, explanation;
        while (getline(inFile, term, ':') && getline(inFile, explanation))
            addHelpEntry(head, term, explanation);
        inFile.close();
        cout << "Help entries loaded from file successfully." << endl;
    }
    else
        cout << "Unable to open file for reading." << endl;
}

void deleteHelpList(HelpEntry*& head) {
    while (head != nullptr) {
        HelpEntry* temp = head;
        head = head->next;
        delete temp;
    }
}

void deleteHelpEntry(HelpEntry*& head, const string& term) {
    HelpEntry* current = head;
    HelpEntry* prev = nullptr;

    while (current != nullptr) {
        if (current->term == term) {
            if (prev == nullptr) {
                head = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            cout << "Help entry with term '" << term << "' deleted successfully." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Help entry with term '" << term << "' not found." << endl;
}

void sortHelpEntries(HelpEntry*& head) {
    if (head == nullptr || head->next == nullptr)
        return;

    HelpEntry* sorted = nullptr;
    HelpEntry* current = head;

    while (current != nullptr) {
        HelpEntry* next = current->next;

        if (sorted == nullptr || sorted->term >= current->term) {
            current->next = sorted;
            sorted = current;
        }
        else {
            HelpEntry* search = sorted;
            while (search->next != nullptr && search->next->term < current->term) {
                search = search->next;
            }
            current->next = search->next;
            search->next = current;
        }

        current = next;
    }

    head = sorted;
    cout << "Help entries sorted successfully." << endl;
}

int main() {
    HelpEntry* helpText = nullptr;

    string filename;
    cout << "Enter the filename to load help entries from: ";
    cin >> filename;

    // Load initial help entries from file (if any)
    loadHelpEntriesFromFile(helpText, filename);

    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. View help entries" << endl;
        cout << "2. Search for explanation" << endl;
        cout << "3. Add help entry" << endl;
        cout << "4. Delete help entry" << endl;
        cout << "5. Save help entries to file" << endl;
        cout << "6. Load help entries from file" << endl;
        cout << "7. Sort help entries" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Help entries:" << endl;
            printHelp(helpText);
            break;
        }
        case 2: {
            string term;
            cout << "Enter term to search for: ";
            cin >> term;
            string explanation = findExplanation(helpText, term);
            cout << "Explanation: " << explanation << endl;
            break;
        }
        case 3: {
            string term, explanation;
            cout << "Enter term to add: ";
            cin >> term;
            cout << "Enter explanation: ";
            cin.ignore(); // Clear input buffer
            getline(cin, explanation);
            addHelpEntry(helpText, term, explanation);
            break;
        }
        case 4: {
            string term;
            cout << "Enter term to delete: ";
            cin >> term;
            deleteHelpEntry(helpText, term);
            break;
        }
        case 5: {
            cout << "Enter the filename to save help entries to: ";
            cin >> filename;
            saveHelpEntriesToFile(helpText, filename);
            break;
        }
        case 6: {
            deleteHelpList(helpText);
            cout << "Enter the filename to load help entries from: ";
            cin >> filename;
            loadHelpEntriesFromFile(helpText, filename);
            break;
        }
        case 7: {
            sortHelpEntries(helpText);
            break;
        }
        case 8: {
            break;
        }
        default: {
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
        }
    } while (choice != 8);

    // Cleanup
    deleteHelpList(helpText);

    return 0;
}