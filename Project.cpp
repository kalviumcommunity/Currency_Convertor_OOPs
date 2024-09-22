#include <iostream>
#include <iomanip> 
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

class Currency {
public:
    string code;
    double rate;

    Currency(string code = "", double rate = 0.0) {
        this->code = code;
        this->rate = rate;
    }
};

class CurrencyConverter {
private:
    double dollar;
    string currency;
    Currency currencies[6] = {
        Currency("inr", 75.13),
        Currency("gbp", 0.73),
        Currency("eur", 0.86),
        Currency("aud", 1.34),
        Currency("jpy", 109.95),
        Currency("cad", 1.25)
    };

public:
    CurrencyConverter() {
        this->dollar = 0;
        this->currency = "";
    }

    void setDollar(double amount) {
        if (amount > 0) {
            this->dollar = amount;
        } else {
            cout << "Invalid amount. Please enter a positive number.\n";
        }
    }

    void setCurrency(string curr) {
        transform(curr.begin(), curr.end(), curr.begin(), ::tolower);
        this->currency = curr;
    }

    double convert() {
        for (int i = 0; i < 6; i++) {
            if (currencies[i].code == this->currency) {
                return this->dollar * currencies[i].rate;
            }
        }
        return -1;
    }

    void displayResult(double result) {
        cout << fixed << setprecision(2);
        for (int i = 0; i < 6; i++) {
            if (currencies[i].code == this->currency) {
                cout << this->dollar << " Dollars = " << result << " in " << currencies[i].code << " (" << currencies[i].code << ")\n";
                return;
            }
        }
        cout << "Invalid currency code!\n";
    }
};

int main() {
    CurrencyConverter converter;
    string currency;
    double dollar;
    char choice = 'y';

    cout << "---- CURRENCY CONVERTER ----\n";

    while (choice == 'y' || choice == 'Y') {
        
        bool validInput = false;
        while (!validInput) {
            cout << "\nEnter the amount in American Dollars (USD): ";
            cin >> dollar;

            if (cin.fail()) {
                cout << "Invalid input. Please enter a valid number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else if (dollar <= 0) {
                cout << "Invalid amount. Please enter a positive number.\n";
            } else {
                validInput = true;
            }
        }

        converter.setDollar(dollar);

        cout << "Enter currency code (INR, GBP, EUR, AUD, JPY, CAD): ";
        cin >> currency;

        converter.setCurrency(currency);

        double result = converter.convert();

        if (result != -1) {
            converter.displayResult(result);
        } else {
            cout << "Invalid currency code entered!\n";
        }

        cout << "\nDo you want to convert another amount? (Y/N): ";
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Thank you for using the Currency Converter!\n";
    return 0;
}
