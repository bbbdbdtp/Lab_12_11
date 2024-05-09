#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct HelpEntry {
    string term;
    string explanation;
    HelpEntry* left;
    HelpEntry* right;
};

HelpEntry* createHelpEntry(const string& term, const string& explanation) {
    HelpEntry* newEntry = new HelpEntry;
    newEntry->term = term;
    newEntry->explanation = explanation;
    newEntry->left = nullptr;
    newEntry->right = nullptr;
    return newEntry;
}

HelpEntry* insertHelpEntry(HelpEntry* root, const string& term, const string& explanation) {
    if (root == nullptr)
        return createHelpEntry(term, explanation);

    if (term < root->term)
        root->left = insertHelpEntry(root->left, term, explanation);
    else if (term > root->term)
        root->right = insertHelpEntry(root->right, term, explanation);

    return root;
}

void printHelp(HelpEntry* root) {
    if (root != nullptr) {
        printHelp(root->left);
        cout << "Term: " << root->term << endl;
        cout << "Explanation: " << root->explanation << endl << endl;
        printHelp(root->right);
    }
}

string findExplanation(HelpEntry* root, const string& term) {
    if (root == nullptr || root->term == term)
        return root ? root->explanation : "Explanation not found.";

    if (term < root->term)
        return findExplanation(root->left, term);
    else
        return findExplanation(root->right, term);
}

void saveHelpEntriesToFile(HelpEntry* root, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        // Perform inorder traversal to save entries to file
        saveHelpEntriesInorder(root, outFile);
        outFile.close();
        cout << "Help entries saved to file successfully." << endl;
    }
    else {
        cout << "Unable to open file for writing." << endl;
    }
}

void saveHelpEntriesInorder(HelpEntry* root, ofstream& outFile) {
    if (root != nullptr) {
        saveHelpEntriesInorder(root->left, outFile);
        outFile << root->term << ":" << root->explanation << endl;
        saveHelpEntriesInorder(root->right, outFile);
    }
}

void loadHelpEntriesFromFile(HelpEntry*& root, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string term, explanation;
        while (getline(inFile, term, ':') && getline(inFile, explanation))
            root = insertHelpEntry(root, term, explanation);
        inFile.close();
        cout << "Help entries loaded from file successfully." << endl;
    }
    else {
        cout << "Unable to open file for reading." << endl;
    }
}

void deleteHelpTree(HelpEntry* root) {
    if (root != nullptr) {
        deleteHelpTree(root->left);
        deleteHelpTree(root->right);
        delete root;
    }
}

HelpEntry* findMin(HelpEntry* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

HelpEntry* deleteHelpEntry(HelpEntry* root, const string& term) {
    if (root == nullptr)
        return root;

    if (term < root->term)
        root->left = deleteHelpEntry(root->left, term);
    else if (term > root->term)
        root->right = deleteHelpEntry(root->right, term);
    else {
        if (root->left == nullptr) {
            HelpEntry* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            HelpEntry* temp = root->left;
            delete root;
            return temp;
        }

        HelpEntry* temp = findMin(root->right);
        root->term = temp->term;
        root->explanation = temp->explanation;
        root->right = deleteHelpEntry(root->right, temp->term);
    }
    return root;
}

void sortHelpEntries(HelpEntry* root) {
    cout << "Help entries cannot be sorted in a binary tree. They are inherently sorted based on their terms." << endl;
}

int main() {
    HelpEntry* helpTree = nullptr;

    string filename;
    cout << "Enter the filename to load help entries from: ";
    cin >> filename;

    // Load initial help entries from file (if any)
    loadHelpEntriesFromFile(helpTree, filename);

    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. View help entries" << endl;
        cout << "2. Search for explanation" << endl;
        cout << "3. Add help entry" << endl;
        cout << "4. Delete help entry" << endl;
        cout << "5. Save help entries to file" << endl;
        cout << "6. Load help entries from file" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Help entries:" << endl;
            printHelp(helpTree);
            break;
        }
        case 2: {
            string term;
            cout << "Enter term to search for: ";
            cin >> term;
            string explanation = findExplanation(helpTree, term);
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
            helpTree = insertHelpEntry(helpTree, term, explanation);
            break;
        }
        case 4: {
            string term;
            cout << "Enter term to delete: ";
            cin >> term;
            helpTree = deleteHelpEntry(helpTree, term);
            break;
        }
        case 5: {
            cout << "Enter the filename to save help entries to: ";
            cin >> filename;
            saveHelpEntriesToFile(helpTree, filename);
            break;
        }
        case 6: {
            deleteHelpTree(helpTree);
            cout << "Enter the filename to load help entries from: ";
            cin >> filename;
            loadHelpEntriesFromFile(helpTree, filename);
            break;
        }
        case 7: {
            break;
        }
        default: {
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
        }
    } while (choice != 7);

    // Cleanup
    deleteHelpTree(helpTree);

    return 0;
}
