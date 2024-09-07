#include <iostream>
#include <string>
using namespace std;

class CurrencyConverter {
private:
    double dollar;
    string currency;

public:
    CurrencyConverter() {
        this->dollar = 0;
        this->currency = "";
    }

    void setDollar(double amount) {
        this->dollar = amount;
    }

    void setCurrency(string curr) {
        this->currency = curr;
    }

    void displayValues() {
        cout << "Dollar: " << this->dollar << ", Currency: " << this->currency << endl;
    }
};

class UserInteraction {
public:
    void getInput() {
        cout << "Getting user input (this is just a placeholder for now)." << endl;
    }
};

int main() {
    CurrencyConverter converter;
    UserInteraction ui;

    converter.displayValues();
    ui.getInput();

    return 0;
}
