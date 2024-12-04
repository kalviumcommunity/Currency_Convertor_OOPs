#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <map>

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

// New abstract base class for currencies
class CurrencyConversionStrategy {
public:
    virtual double getConversionRate() const = 0; // Pure virtual function for the rate
    virtual string getCurrencyName() const = 0;  // Pure virtual function for currency name
    virtual ~CurrencyConversionStrategy() {}
};

// Concrete Currency Strategy Classes
class INRConversion : public CurrencyConversionStrategy {
public:
    double getConversionRate() const override { return 75.13; }
    string getCurrencyName() const override { return "Indian Rupees (INR)"; }
};

class EURConversion : public CurrencyConversionStrategy {
public:
    double getConversionRate() const override { return 0.86; }
    string getCurrencyName() const override { return "Euros (EUR)"; }
};

class GBPConversion : public CurrencyConversionStrategy {
public:
    double getConversionRate() const override { return 0.73; }
    string getCurrencyName() const override { return "British Pounds (GBP)"; }
};

class AUDConversion : public CurrencyConversionStrategy {
public:
    double getConversionRate() const override { return 1.34; }
    string getCurrencyName() const override { return "Australian Dollars (AUD)"; }
};

class JPYConversion : public CurrencyConversionStrategy {
public:
    double getConversionRate() const override { return 109.95; }
    string getCurrencyName() const override { return "Japanese Yen (JPY)"; }
};

class CADConversion : public CurrencyConversionStrategy {
public:
    double getConversionRate() const override { return 1.25; }
    string getCurrencyName() const override { return "Canadian Dollars (CAD)"; }
};

// Derived class CurrencyConverter inherits from abstract class Converter
class CurrencyConverter : public Converter {
private:
    map<string, CurrencyConversionStrategy*> strategies; // Map for strategies

public:
    // Constructor for derived class
    CurrencyConverter() : Converter() {
        strategies["inr"] = new INRConversion();
        strategies["eur"] = new EURConversion();
        strategies["gbp"] = new GBPConversion();
        strategies["aud"] = new AUDConversion();
        strategies["jpy"] = new JPYConversion();
        strategies["cad"] = new CADConversion();
    }

    // Destructor to clean up dynamically allocated strategies
    ~CurrencyConverter() {
        for (auto& strategy : strategies) {
            delete strategy.second;
        }
    }

    // Override the pure virtual function from the base class
    double convert() override {
        if (strategies.find(currency) != strategies.end()) {
            return dollar * strategies[currency]->getConversionRate();
        } else {
            return -1;  // Invalid currency code
        }
    }

    // Override the virtual function to display the result
    void displayResult(double result) const override {
        cout << fixed << setprecision(2);
        if (strategies.find(currency) != strategies.end()) {
            cout << dollar << " Dollars = " << result << " " << strategies[currency]->getCurrencyName() << "\n";
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