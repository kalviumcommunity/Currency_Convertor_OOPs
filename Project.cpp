#include <iostream>
#include <string>
using namespace std;


class CurrencyConverter {
private:
    double dollar;      
    string currency;    

public:
    
    CurrencyConverter() {
        dollar = 0;
        currency = "";
    }

    
    void setDollar(double amount) {
        dollar = amount;
    }

    
    void setCurrency(string curr) {
        currency = curr;
    }

    
    void displayValues() {
        cout << "Dollar: " << dollar << ", Currency: " << currency << endl;
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
