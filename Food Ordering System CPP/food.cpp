#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;
struct MenuItem {
    int id;
    string name;
    double price;
};

// Function to display the menu
void displayMenu(const vector<MenuItem>& menu) {
    cout << "================= Menu =================" << endl;
    cout << setw(5) << "ID" << setw(20) << "Item" << setw(10) << "Price" << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& item : menu) {
        cout << setw(5) << item.id << setw(20) << item.name << setw(10) << fixed << setprecision(2) << item.price << endl;
    }
    cout << "========================================" << endl;
}

//order
void takeOrder(const vector<MenuItem>& menu) {
    vector<MenuItem> order;
    int choice;
    double totalPrice = 0;

    cout << "\nEnter the item ID to order (0 to finish): ";
    while (cin >> choice && choice != 0) {
        bool found = false;
        for (const auto& item : menu) {
            if (item.id == choice) {
                order.push_back(item);
                totalPrice += item.price;
                cout << item.name << " added to your order." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Invalid item ID. Try again." << endl;
        }
        cout << "Enter next item ID (0 to finish): ";
    }

    if (order.empty()) {
        cout << "No items ordered. Exiting..." << endl;
        return;
    }
    // Display order
    cout << "\n========== Order Summary ==========" << endl; 
    for (const auto& item : order) {
        cout << item.name << " - $" << fixed << setprecision(2) << item.price << endl;
    }
    cout << "------------------------------------" << endl;
    cout << "Total Price: $" << totalPrice << endl;

    // Save order
    ofstream orderFile("order.txt", ios::app);
    if (orderFile.is_open()) {
        orderFile << "========== New Order ==========\n";
        for (const auto& item : order) {
            orderFile << item.name << " - $" << fixed << setprecision(2) << item.price << endl;
        }
        orderFile << "Total Price: $" << totalPrice << "\n\n";
        orderFile.close();
        cout << "Order saved to 'order.txt'." << endl;
    } else {
        cerr << "Error: Unable to save order to file." << endl;
    }
}

//user authentication
bool authenticateUser() {
    string username, password;
    cout << "Please enter your username: ";
    cin >> username;
    cout << "Please enter your password: ";
    cin >> password;

    ifstream userFile("users.txt");
    if (!userFile) {
        cerr << "Error: Unable to open users.txt" << endl;
        return false;
    }

    string fileUsername, filePassword;
    while (userFile >> fileUsername >> filePassword) {
        if (username == fileUsername && password == filePassword) {
            userFile.close();
            return true; 
        }
    }

    userFile.close();
    return false;  
}

// Function for user registration
bool registerUser() {
    string username, password;
    cout << "Enter your desired username: ";
    cin >> username;

    // Check if username already exists
    ifstream userFile("users.txt");
    string fileUsername;
    while (userFile >> fileUsername) {
        if (username == fileUsername) {
            cout << "Username already exists. Please try a different one." << endl;
            userFile.close();
            return false;  // Username already taken
        }
    }
    userFile.close();

    // Get password and store the new user
    cout << "Enter your desired password: ";
    cin >> password;

    // Add new user to users.txt
    ofstream userFileOut("users.txt", ios::app);
    if (!userFileOut) {
        cerr << "Error: Unable to open users.txt for writing." << endl;
        return false;
    }

    userFileOut << username << " " << password << endl;
    userFileOut.close();
    cout << "User registered successfully!" << endl;
    return true; 
}

// Main function
int main() {
    //log in or register
    int choice;
    cout << "Welcome to the Food Ordering System!" << endl;
    cout << "1. Log in\n2. Register\n0. Exit\nChoose an option: ";
    cin >> choice;

    if (choice == 1) {
        // Authenticate user
        if (!authenticateUser()) {
            cout << "Invalid username or password. Exiting..." << endl;
            return 0;
        }
    } else if (choice == 2) {
        // Register new user
        if (!registerUser()) {
            cout << "Registration failed. Exiting..." << endl;
            return 0;
        }
    } else {
        cout << "Exiting the program." << endl;
        return 0;  
    }

    vector<MenuItem> menu = {
        {1, "Burger", 5.99},
        {2, "Pizza", 8.99},
        {3, "Pasta", 7.99},
        {4, "Salad", 4.99},
        {5, "Soda", 1.99},
        {6, "Fries", 2.99},
        {7, "Sandwich", 4.49},
        {8, "Coffee", 3.49},
        {9, "Milkshake", 4.99},
        {10, "Chicken Wings", 6.99},
        {11, "Tacos", 3.99},
        {12, "Nachos", 5.49},
        {13, "Ice Cream", 2.99},
        {14, "Grilled Cheese", 4.79},
        {15, "Hot Dog", 3.99},
        {16, "Onion Rings", 2.99},
        {17, "Cupcake", 1.99},
        {18, "Brownie", 2.49},
        {19, "Smoothie", 4.99},
        {20, "Steak", 12.99},
        {21, "Chicken Caesar Salad", 7.99},
        {22, "Veggie Wrap", 5.49},
        {23, "Pulled Pork Sandwich", 6.99},
        {24, "Buffalo Wings", 7.49},
        {25, "Caesar Salad", 5.99},
        {26, "Clam Chowder", 4.99},
        {27, "Lobster Roll", 15.99},
        {28, "BBQ Ribs", 14.99},
        {29, "Cheese Pizza", 7.49},
        {30, "Pepperoni Pizza", 8.49}
    };

    int option;
    do {
        cout << "\n1. View Menu\n2. Place Order\n0. Exit\nChoose an option: ";
        cin >> option;

        switch (option) {
            case 1:
                displayMenu(menu);
                break;
            case 2:
                takeOrder(menu);
                break;
            case 0:
                cout << "Thank you! Visit again." << endl;
                break;
            default:
                cout << "Invalid option. Try again." << endl;
        }
    } while (option != 0);

    return 0;
}
