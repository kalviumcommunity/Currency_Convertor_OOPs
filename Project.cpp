#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

// Abstract Base Class (introducing the concept of abstract class)
class Converter {
protected:
    double dollar;        // Protected members accessible in derived class
    string currency;      // Protected members accessible in derived class

public:
    // Constructor for base class
    Converter() {
        dollar = 0;
        currency = "";
    }

    // Setter for dollar amount (defined in the base class to adhere to LSP)
    virtual void setDollar(double amount) {
        if (amount > 0) {
            dollar = amount;
        } else {
            cout << "Invalid amount. Please enter a positive number.\n";
        }
    }

    // Setter for currency (defined in the base class to adhere to LSP)
    virtual void setCurrency(string curr) {
        transform(curr.begin(), curr.end(), curr.begin(), ::tolower);
        currency = curr;
    }

    // Pure virtual function to make this an abstract class
    virtual double convert() = 0;

    // Virtual function to display the result
    virtual void displayResult(double result) const = 0;

    // Virtual destructor to ensure proper cleanup in polymorphic usage
    virtual ~Converter() {
        // Destructor logic (if needed in future)
    }
};

// Derived class CurrencyConverter inherits from abstract class Converter
class CurrencyConverter : public Converter {
private:
    // Exchange rates (private and hidden from the user)
    const double GBP = 0.73;
    const double EUR = 0.86;
    const double INR = 75.13;
    const double AUD = 1.34;
    const double JPY = 109.95;
    const double CAD = 1.25;

public:
    // Constructor for derived class
    CurrencyConverter() : Converter() {}

    // Override the pure virtual function from the base class
    double convert() override {
        if (currency == "inr") {
            return dollar * INR;
        } else if (currency == "eur") {
            return dollar * EUR;
        } else if (currency == "gbp") {
            return dollar * GBP;
        } else if (currency == "aud") {
            return dollar * AUD;
        } else if (currency == "jpy") {
            return dollar * JPY;
        } else if (currency == "cad") {
            return dollar * CAD;
        } else {
            return -1;  // Invalid currency code
        }
    }

    // Override the virtual function to display the result
    void displayResult(double result) const override {
        cout << fixed << setprecision(2);
        if (currency == "inr") {
            cout << dollar << " Dollars = " << result << " Indian Rupees (INR)\n";
        } else if (currency == "eur") {
            cout << dollar << " Dollars = " << result << " Euros (EUR)\n";
        } else if (currency == "gbp") {
            cout << dollar << " Dollars = " << result << " British Pounds (GBP)\n";
        } else if (currency == "aud") {
            cout << dollar << " Dollars = " << result << " Australian Dollars (AUD)\n";
        } else if (currency == "jpy") {
            cout << dollar << " Dollars = " << result << " Japanese Yen (JPY)\n";
        } else if (currency == "cad") {
            cout << dollar << " Dollars = " << result << " Canadian Dollars (CAD)\n";
        } else {
            cout << "Invalid currency code!\n";
        }
    }
};

int main() {
    // Polymorphism in action: Base class pointer pointing to derived class object
    Converter* converter = new CurrencyConverter();
    string currency;
    double dollar;
    char choice = 'y';

    cout << "---- CURRENCY CONVERTER ----\n";

    while (choice == 'y' || choice == 'Y') {
        
        cout << "\nEnter the amount in American Dollars (USD): ";
        cin >> dollar;

        // Call base class method (overridden in the derived class)
        converter->setDollar(dollar);

        // Input currency code
        cout << "Enter currency code (INR, GBP, EUR, AUD, JPY, CAD): ";
        cin >> currency;

        // Set the currency in the object
        converter->setCurrency(currency);

        // Perform the conversion using polymorphism
        double result = converter->convert();

        // Display the result if the conversion was valid
        if (result != -1) {
            converter->displayResult(result);
        } else {
            cout << "Invalid currency code entered!\n";
        }

        // Ask if the user wants to convert another amount
        cout << "\nDo you want to convert another amount? (Y/N): ";
        cin >> choice;
    }

    cout << "Thank you for using the Currency Converter!\n";

    // Freeing memory allocated for the base class pointer
    delete converter;

    return 0;
}
