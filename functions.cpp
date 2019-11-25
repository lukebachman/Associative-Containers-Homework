#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "functions.hpp"
#include "GroceryItemDatabase.hpp"
#include "GroceryItem.hpp"

Inventory_DB loadInventory() {
	//temp variables to store data that's read in
	std::string upc;
	unsigned int quantity = 0;
	Inventory_DB inventory; //inventory map

	std::ifstream file("GroceryStoreInventory.dat");
	if (file.is_open()) //check to make sure file is open
	{
		while (!file.eof())
		{
			file >> upc >> quantity;
			inventory.insert({ upc, quantity });
		}
		file.close();
	}

	else std::cout << "Unable to open file";
	return inventory;
}

void processCustomerShoppingCarts(ShoppingCarts const& shoppingCarts, Inventory_DB& inventory) {
	ShoppingCart current_cart;
	GroceryItemDatabase& storeDataBase = GroceryItemDatabase::instance();

	for (auto carts : shoppingCarts) //Range-Based For-loop to iterate through shoppingCarts Tree
	{
		double amountDue = 0.0;
		std::cout << carts.first << "'s" << " shopping cart contains:\n"; //Prints name of current customer
		current_cart = carts.second;
		for (auto items : current_cart) //Prints out Items in current cart
		{
			GroceryItem* full_item = storeDataBase.find(items.first); //Scans the item from the cart and checks database
			if (full_item != nullptr)
			{
				std::cout << *full_item; //outputs item info
				amountDue += full_item->price();
				auto quantity = inventory.find(full_item->upcCode()); //STL map::find() function
				if (quantity != inventory.end()) //error check for bad search
				{
					quantity->second--; //updates store's inventory with the correct quantity of the item
				}
			}
		}
		std::cout << std::fixed << std::setprecision(2) << std::showpoint //Prints out Total Due for current cart
			<< std::string(25, '-') << '\n'
			<< "Total  $" << amountDue << "\n\n";
	}

}

void reorderItems(ShoppingCarts const& shoppingCarts, Inventory_DB& inventory) {
	ShoppingCart current_cart;
	for (auto carts : shoppingCarts)
	{
		current_cart = carts.second;
		for (auto items : current_cart) //Checks the Grocery Store Inventory and updates accordingly
		{
			auto quantity = inventory.find(items.first); //STL map::find() function
			if (quantity != inventory.end()) //error check for bad search
			{
				if (quantity->second < 15)
				{
					std::cout << '"' << quantity->first << '"' << " at " << quantity->second
						<< ", " << "re-ordering 20 more\n";
					inventory[quantity->first] = inventory.at(items.first) + 20;
				}
			}
		}
	}
}
