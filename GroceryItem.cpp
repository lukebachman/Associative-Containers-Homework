// GroceryItem.cpp

#include "GroceryItem.hpp"

#include <iomanip>
#include <cmath>    // abs()
#include <limits>   // max()
#include <utility>  // move()
#include <string>   // getline()
#include <iostream> // ignore(), streamsize

namespace //unamed, autonomous namespace
{
	//This approximates your floating point values to be within two decimal places so that they can be compared.
	constexpr auto EPSILON = 1.0E-4;
}

//Constructors
GroceryItem::GroceryItem( const std::string & productName,
const std::string & brandName,
const std::string & upcCode,
double price)
	: _upcCode (upcCode),
	_brandName (brandName),
	_productName (productName),
	_price (price)
{}
//Insertion and Extraction Operators//
//Reads data from input file
std::istream& operator>>(std::istream& stream, GroceryItem& groceryItem)
{
	GroceryItem workingItem;

	stream >> std::quoted(workingItem._upcCode)
		>> std::quoted(workingItem._brandName)
		>> std::quoted(workingItem._productName)
		>> workingItem._price;

	stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //consume and ignore everything else on the line and the end-of-line character left behind

	//After this check, Working item is moved into the returned groceryItem.
	groceryItem = std::move(workingItem);

	return stream;
}

//Writes data to output file
std::ostream& operator<<(std::ostream& stream, const GroceryItem& groceryItem)
{
	stream << "UPC: " << std::quoted(groceryItem.upcCode()) << ", "
		<< "Brand: " << std::quoted(groceryItem.brandName()) << ", "
		<< "Product: " << std::quoted(groceryItem.productName()) << ", "
		<< "Price: $" << groceryItem.price() << '\n';
	return stream;
}

//Logical Operators
bool operator==(const GroceryItem& lhs, const GroceryItem& rhs)
{
	if constexpr ((true))
	{
		return lhs._upcCode == rhs._upcCode
			&& lhs._productName == rhs._productName
			&& lhs._brandName == rhs._brandName
			&& std::abs(lhs._price - rhs._price) < EPSILON;
	}
	else
	{
		return !(lhs < rhs) && (rhs < lhs);
	}
}

bool operator< (const GroceryItem& lhs, const GroceryItem& rhs)
{
	if (auto result = lhs._upcCode.compare(rhs._upcCode);    result != 0) return result < 0;
	if (auto result = lhs._productName.compare(rhs._productName); result != 0) return result < 0;
	if (auto result = lhs._brandName.compare(rhs._brandName);   result != 0) return result < 0;
	if (std::abs(lhs._price - rhs._price) >= EPSILON)                         return lhs._price < rhs._price;

	// At this point, all attributes are equal to each other, so the lhs cannot be less than the rhs
	return false;
}

bool operator !=(const GroceryItem& lhs, const GroceryItem& rhs) { return !(lhs == rhs); }
bool operator <=(const GroceryItem& lhs, const GroceryItem& rhs) { return !(rhs < lhs); }
bool operator > (const GroceryItem& lhs, const GroceryItem& rhs) { return  (rhs < lhs); }
bool operator >=(const GroceryItem& lhs, const GroceryItem& rhs) { return !(lhs < rhs); }
