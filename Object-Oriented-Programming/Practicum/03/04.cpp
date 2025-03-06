#include <iostream>

using namespace std;

const double EPSILON = 0.0001;

const int MAX_PRODUCTS = 50;
const int MAX_PRODUCT_NAME_LENGTH = 20;

class Product
{
    char name[MAX_PRODUCT_NAME_LENGTH];
    double price;
    int quantity;

public:
    Product()
    {
        price = 0.0;
        quantity = 0;
    }

    Product(const char *name, double price, int quantity)
    {
        setName(name);
        setPrice(price);
        setQuantity(quantity);
    }

    void setName(const char *newName)
    {
        strcpy(this->name, newName);
    }

    void setPrice(double newPrice)
    {
        this->price = newPrice;
    }

    void setQuantity(int newQuantity)
    {
        this->quantity = newQuantity;
    }
};

class Store
{
    Product products[MAX_PRODUCTS];
};