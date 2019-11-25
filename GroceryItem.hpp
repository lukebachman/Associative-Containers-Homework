#pragma once //include guard

#include <iostream>
#include <string>

class GroceryItem {
	//Insertion and Extraction operators
	friend std::ostream& operator<<(std::ostream& stream, const GroceryItem& grocerItem);
	friend std::istream& operator>>(std::istream& stream, GroceryItem& groceryItem);

	// Logical Operators
	friend bool operator==(const GroceryItem& lhs, const GroceryItem& rhs);
	friend bool operator< (const GroceryItem& lhs, const GroceryItem& rhs);

private:
	std::string _upcCode;
	std::string _brandName;
	std::string _productName;
	double      _price = 0.0;

public:
	// Constructors
	GroceryItem() = default;
	GroceryItem(const std::string& productName,
		const std::string& brandName = {},
		const std::string& upcCode = {},
		double price = 0.0);
	// Mutators
	void set_upc(const std::string& upcCode) { _upcCode = upcCode; }
	void set_brand(const std::string& brandName) { _brandName = brandName; }
	void set_product(const std::string& productName) { _productName = productName; }
	void set_price(double             price) { _price = price; }

	//Accessors
	std::string upcCode()     const { return _upcCode; }
	std::string brandName()   const { return _brandName; }
	std::string productName() const { return _productName; }
	double      price()       const { return _price; }
};

//Logical Operators
bool operator==(const GroceryItem& lhs, const GroceryItem& rhs);
bool operator!=(const GroceryItem& lhs, const GroceryItem& rhs);

bool operator< (const GroceryItem& lhs, const GroceryItem& rhs);
bool operator<=(const GroceryItem& lhs, const GroceryItem& rhs);
bool operator> (const GroceryItem& lhs, const GroceryItem& rhs);
bool operator>=(const GroceryItem& lhs, const GroceryItem& rhs);
