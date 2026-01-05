#include <iostream>   // Input and output (cin, cout)
#include <vector>     // Used to store a list of items that can grow or shrink
#include <string>     // Use of strings and variables
#include <iomanip>    // Used to format the output alignin, text, setting and spacing


using namespace std;  // Allows the use of  C++ features like cout, cin, string and vector without  writting std each time



/*

========================================================================
ITEM CLASS // This represents a single item sold by the vending machine

========================================================================

*/

class Item {

public:

    string code;         // Unique item code (S1, D1,etc.)
    string name;         // Item name
    string category;     // Item category ( Sandwiches, Drinks, Snacks)
    double price;        // Price of the item
    int stock;           // Number of items available


    // Constructor to initialise an item
    Item(string c, string n, string cat, double p, int s) {
        code = c;
        name = n;
        category = cat;
        price = p;
        stock = s;
    }
};



/*

================================================================
VENDING MACHINE CLASS
Controls the vending machine operations

================================================================

*/

class VendingMachine {

private:

    vector<Item> items; // Stores ( keeps all vending machine items
    double balance = 0.0;       // Stores the user`s current balance

    // Searches for the item using its code
    // Returns the index if found, otherwise -1
    int findItem(string code) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i].code == code)
                return i;

        }
        return -1; // Item code not found

    }
 
 public:
     // Adds a new item to the vending machine
     void addItem (Item item) {
         items.push_back(item);
     }


     // Displays the menu with items grouped category
     void showMenu() {
         cout << "\n=========       MEAL DEAL FOR EVERYONE =========\n";


         string lastCategory = "";  // Stores the previous category to avoid printing the sane category header twice

         
         for (int i = 0; i < items.size(); i++) {      // Loop through all items in the vending machine
             
             if (items[i].category != lastCategory) {   // Print category header when it changes

                 cout << "\n--- " << items[i].category << " ---\n";  // It shows the category heading when a new category is found
                 lastCategory = items[i].category;     // Updates lastCategory to the current category
             
             }
       
             
             
             cout << items[i].code << " _ "   // Display item details
                  << setw(20) << left << items [i].name
                  << " GBP " << items[i].price
                  << " | Stock: " << items[i].stock << "\n";
             
       }
 
       cout << "\nMEAL DEAL: Sandwich + Drink + Snack = GBP 5.00\n";
       cout << "Current balance: GBP " << balance << "\n\n";

    }


    // This section allows the user to insert money
    void insertMoney() {
        double amount;
        cout << "Enter money (GBP): ";
        cin >> amount;

        // Reject invalid amounts
        if (amount <= 0) {
            cout << "Invalid amount entered.\n\n";
            return;
        } 

   
    balance += amount;
    cout << "Balance updated: GBP " << balance << "\n\n";
    } 
 

  // Allows the user to buy a single item
  void buySingle() {
      string code;
      cout << "Enter item code: ";
      cin >> code;
 
      int index = findItem(code);

     
      // Check if the item code is valid
      if (index == -1) {
          cout << "Invalid code entered: " << code << "\n\n";
          return;
     }

      Item &item = items[index];

      // Check stock availability
      if (item.stock <= 0) {
          cout << "Item out of stock. \n\n";
          return;

     }

      // Check Balance 
      if (balance < item.price) {
        cout << "Not enough money. \n\n";
        return;

     }

      // Dispense item
      item.stock--;
      balance -= item.price;

 
      cout << "\nDispensing: " << item.name << "\n";
      cout << "Remaining balance: GBP " << balance << "\n";

 
     // Sugest the meal deal depending on the category
      if (item.category == "Sandwiches")
      cout << "Tip: Add a drink and snack for the meal deal. \n";
  else if (item.category == "Cold Drinks"|| item.category == "Hot Drinks")
      cout << "Tip: Add a sandwich and snack for the meal deal.\n";
  else if (item.category == "Snacks")
      cout << "Tip: Add a sandwich and drink for the meal deal.\n";

  cout << "\n";

}


// Allows the user to buy a meal deal
void buyMealDeal() {

     cout << "\n=== MEAL DEAL (GBP 5.00) ===\n";


     string sCode, dCode, nCode;

   
     // Get item codes from the user
     cout << "Enter sandwich code: ";
     cin >> sCode;
     cout << "Enter drink code: ";
     cin >>dCode;
     cout << "Enter snack code: ";
     cin >> nCode;


     int s = findItem(sCode);
     int d = findItem(dCode);
     int n = findItem(nCode);


     // Validate item codes
     if (s == -1 || d == -1 || n == -1) {
         cout << "One or more invalid codes entered.\n\n";
         return;

     }
 
     
     // Check the correct categories
     if (items[s].category != "Sandwiches" ||
          (items[d].category != "Cold Drinks" && items[d].category != "Hot Drinks") ||
          items[n].category != "Snacks") {
          cout << "Selected items do not match meal deal requirements. \n\n";
          return;

     }

     
     // Check Stock availability
     if (items[s].stock <= 0 || items[d].stock <= 0 || items[n].stock <= 0) {
         cout << "Item out of stock.\n\n";
         return;
     
     }
   

     // Check balance ( meal deal price is GBP 5.00)
     if (balance < 5.00) {
         cout << "Not enough money for the meal deal.\n\n";
         return;

     }

     // DISPENSE ITEM
     items[s].stock--;
     items[d].stock--;
     items[n].stock--;
     balance -= 5.00;


     cout << "\nMeal Deal Dispensed:\n";
     cout << "_ " << items[s].name << "\n";
     cout << "_ " << items[d].name << "\n";
     cout << "_ " << items[n].name << "\n";
     cout << "Your remaining balance is: GBP " << balance << "\n";
     cout << " You can continue buying items.\n\n";
   
  }

  // Exit program
  void finish () {
      cout << "Returning GBP " << balance << ". Thank you!\n\n";
      balance = 0;
  }

  // Main menu
  void run() {
       while (true) {
          cout << "1. View Menu\n";
          cout << "2. Insert Money\n";
          cout << "3. Buy Single Item\n";
          cout << "4. Buy Meal Deal\n";
          cout << "5. Exit\n";
          cout << "Choose an option: ";

          int choice;
          cin >> choice;
          cout << "\n";

         
          switch (choice) {
              case 1: showMenu(); break;
              case 2: insertMoney(); break;
              case 3: buySingle(); break;
              case 4: buyMealDeal(); break;
              case 5: finish(); return;

              default: cout << "Invalid menu option selected.\n\n";
          }
     
        }
   
     }

  };
 

  /*

  ========================================================
   
   MAIN FUNCTION
   
  ========================================================

  */

  int main() {
    VendingMachine vm;

    // Sandwiches
    vm.addItem(Item("S1", "Ham & Cheese", "Sandwiches", 2.75, 10));
    vm.addItem(Item("S2", "Tuna Sandwich", "Sandwiches", 2.80, 8));
    vm.addItem(Item("S3", "Chicken Sandwich", "Sandwiches", 2.90, 7));

    // Cold Drinks
    vm.addItem(Item("D1", "Fruit Juice", "Cold Drinks", 1.50, 12));
    vm.addItem(Item("D2", "Water", "Cold Drinks", 1.00, 20));
    vm.addItem(Item("D3", "Energy Drink", "Cold Drinks", 2.00, 6));

    // Hot Drinks
    vm.addItem(Item("H1", "Hot Chocolate", "Hot Drinks", 1.80, 10));
    vm.addItem(Item("H2", "Coffee", "Hot Drinks", 1.60, 10));

    // Snacks
    vm.addItem(Item("N1", "Crisps", "Snacks", 1.20, 15));
    vm.addItem(Item("N2", "Chocolate Bar", "Snacks", 1.30, 14));

    vm.run();
    return 0;
}
