#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <fstream>
#include <sstream>

using namespace std;

const int BUCKET_COUNT = 10; // number of buckets in the hash table

// structure to represent each entry in the hash table
struct Entry {
    string name; // name associated with entry
    string phone; // phone number associated with entry

    // constructor to initialize an entry
    Entry(const string &name, const string &phone) : name(name), phone(phone) {}
};

// hash table class using separate chaining for collision handling
class HashTable {
private:
    vector<list<Entry> > table; // vector of lists to store entries (separate chaining)

    // hash function to map a key to a bucket index
    int hashFunction(const string &key) {
        hash<string> hashFn;
        return hashFn(key) % BUCKET_COUNT;
    }
    
    // helper function to check if an entry matches a given full name
    bool matchEntry(const Entry &entry, const string &fullName) {
        return entry.name == fullName;
    }

public:
    // constructor to initialize the hash table with a fixed number of buckets
    HashTable() : table(BUCKET_COUNT) {}

    // function to insert an entry into the hash table
    void insert(const string &name, const string &phone) {
        int index = hashFunction(name);
        table[index].push_back(Entry(name, phone));
        cout << "Inserted: " << name << " " << phone << " at index " << index << endl;
    }
    
    // function to display the contents of the hash table
    void display() {
        for (int i = 0; i < BUCKET_COUNT; ++i) {
            cout << "Bucket " << i << ": ";
            for (const auto &entry : table[i]) {
                cout << "[" << entry.name << ": " << entry.phone << "] ";
            }
            cout << endl;
            cout << endl;
        }
    }

    // function to search for entries by first name and display them (ex: Liam in main class)
    void search(const string &firstName) {
        bool found = false;

        for (int i = 0; i < BUCKET_COUNT; ++i) {
            for (const auto &entry : table[i]) {
                stringstream ss(entry.name);
                string firstPart;
                ss >> firstPart;  // extracts the first name

                if (firstPart == firstName) {
                    cout << entry.name << ": " << entry.phone << endl;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "No entries found for first name " << firstName << endl;
        }
    }

    // function to delete entries by full name from the hash table
    void deleteEntries(const string &fullName) {
        int index = hashFunction(fullName);  // compute the bucket index
        auto &bucket = table[index]; // gets bucket
        

        // iterates over the entries in the bucket
        for (auto it = bucket.begin(); it != bucket.end(); ) {
            if (matchEntry(*it, fullName)) {
                it = bucket.erase(it); // removes the entry if it matches the full name
                cout << "Deleted entry for " << fullName << endl;
            } else {
                ++it;
            }
        }
    }
};

// function to load data from a CSV file and insert it into the hash table
void loadCSV(HashTable &hashTable, const string &fileName) {
    ifstream file(fileName);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, phone;

        getline(ss, name, ',');
        getline(ss, phone, ',');

        hashTable.insert(name, phone); // insert each entry into the hash table
    }
}

int main() {
    HashTable hashTable;

    // loads CSV data
    loadCSV(hashTable, "/Users/tiffany/Desktop/CS 5393-002/CS 5393-002/Lab3_Problem2_DSC++.csv");

    // displays initial hash table content
    cout << "\nHash Table:\n";
    hashTable.display();

    // searches for entries with first name "Liam"
    cout << "\nSearch for 'Liam':\n";
    hashTable.search("Liam");

    // deletes entries with the full name: "Isabella Anderson"
    cout << "\nDeleting 'Isabella Anderson':\n";
    hashTable.deleteEntries("Isabella Anderson");
    hashTable.display();

    // searches for "Shaibal Chakrabarty" and "Lucas Li"
    cout << "\nSearch for 'Shaibal Chakrabarty' and 'Lucas Li':\n";
    hashTable.search("Shaibal Chakrabarty");
    hashTable.search("Lucas Li");

    // then inserts new entries of "Shaibal Chakrabarty" and "Lucas Li"
    cout << "\nInserting new entries:\n";
    hashTable.insert("Shaibal Chakrabarty", "214-768-2000");
    hashTable.insert("Lucas Li", "469-555-1212");

    // displays the update hash table
    cout << "\nUpdated Hash Table:\n";
    hashTable.display();

    return 0;
}
