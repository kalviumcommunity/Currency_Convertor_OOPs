#include <iostream>
#include <iomanip> 
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// Class to represent a currency with code and rate
class Currency {
public:
    string code;  // Currency code (like "inr", "usd")
    double rate;  // Conversion rate to USD

    // Constructor to initialize currency code and rate
    Currency(string code = "", double rate = 0.0) {
        this->code = code;  // Using 'this' pointer to refer to class members
        this->rate = rate;  // 'this' refers to the current object
    }
};

// Class to convert dollars to different currencies
class CurrencyConverter {
private:
    double dollar;  // Amount in USD
    string currency;  // Chosen currency code
    
    // Array of Currency objects to store different currency rates
    Currency currencies[6] = {
        Currency("inr", 75.13),
        Currency("gbp", 0.73),
        Currency("eur", 0.86),
        Currency("aud", 1.34),
        Currency("jpy", 109.95),
        Currency("cad", 1.25)
    };

public:
    // Constructor to initialize dollar and currency with default values
    CurrencyConverter() {
        this->dollar = 0;
        this->currency = "";
    }

    // Function to set dollar value (input validation)
    void setDollar(double amount) {
        if (amount > 0) {
            this->dollar = amount;  // 'this' pointer used to refer to class member
        } else {
            cout << "Invalid amount. Please enter a positive number.\n";
        }
    }

    // Function to set currency code
    void setCurrency(string curr) {
        // Convert input currency code to lowercase for consistency
        transform(curr.begin(), curr.end(), curr.begin(), ::tolower);
        this->currency = curr;  // 'this' pointer used to refer to class member
    }

    // Function to convert USD to the chosen currency
    double convert() {
        // Loop through the array of Currency objects to find the matching currency
        for (int i = 0; i < 6; i++) {
            if (currencies[i].code == this->currency) {
                // Return the converted amount
                return this->dollar * currencies[i].rate;
            }
        }
        return -1;  // If the currency is not found, return -1
    }

    // Function to display the conversion result
    void displayResult(double result) {
        cout << fixed << setprecision(2);  // Set output format to 2 decimal places
        // Loop through the array to match the currency and display the result
        for (int i = 0; i < 6; i++) {
            if (currencies[i].code == this->currency) {
                // Display result in the correct format
                cout << this->dollar << " Dollars = " << result << " in " << currencies[i].code << " (" << currencies[i].code << ")\n";
                return;
            }
        }
        cout << "Invalid currency code!\n";  // If currency code is invalid
    }
};

int main() {
    // Create an object of the CurrencyConverter class
    CurrencyConverter converter;
    string currency;
    double dollar;
    char choice = 'y';

    cout << "---- CURRENCY CONVERTER ----\n";

    while (choice == 'y' || choice == 'Y') {
        
        // Input validation for dollar amount
        bool validInput = false;
        while (!validInput) {
            cout << "\nEnter the amount in American Dollars (USD): ";
            cin >> dollar;

            if (cin.fail()) {  // Check if the input is not a number
                cout << "Invalid input. Please enter a valid number.\n";
                cin.clear();  // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the invalid input
            } else if (dollar <= 0) {
                cout << "Invalid amount. Please enter a positive number.\n";
            } else {
                validInput = true;  // Input is valid, exit the loop
            }
        }

        // Set the dollar amount in the converter object
        converter.setDollar(dollar);

        // Input currency code
        cout << "Enter currency code (INR, GBP, EUR, AUD, JPY, CAD): ";
        cin >> currency;

        // Set the currency code in the converter object
        converter.setCurrency(currency);

        // Perform the currency conversion
        double result = converter.convert();

        // Display the result if the currency is valid
        if (result != -1) {
            converter.displayResult(result);
        } else {
            cout << "Invalid currency code entered!\n";
        }

        // Ask if the user wants to convert another amount
        cout << "\nDo you want to convert another amount? (Y/N): ";
    }
        cin >> choice;
        

    cout << "Thank you for using the Currency Converter!\n";
    return 0;
}
