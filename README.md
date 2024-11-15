# E-commerce Platform

This project is a simple e-commerce platform implemented in C, featuring user registration, product browsing, purchasing functionality, and personalized recommendations based on browsing and purchase history. 

## Features

- **User  Registration and Login**: Users can sign up with a username and password, and log in to access their account.
- **Product Management**: Users can view available products, including their details (name, price, quantity).
- **Purchase Functionality**: Users can purchase products, which updates their purchase history.
- **Browsing History**: Users can browse products, which updates their browsing history.
- **Recommendations**: Based on browsing and purchase history, the platform recommends products to users.
- **Data Storage**: User and product information is stored in hash tables for efficient access.

## Run the code
```sh
gcc jackfruit.c
./a.out
```

## Code Structure

### create_user: Creates a new user.
### create_prod: Creates a new product.
### insert_user: Inserts a new user into the hash table.
### insert_item: Inserts a new item into the hash table.
### display_users: Displays all users in the system.
### display_prod: Displays all products in the system.
### recommend: Generates product recommendations for a user.

## Data Structures

### User Structure
```c
typedef struct user_details {
    char username[100];
    char password[100];
    TREE *browsing_history;
    TREE *purchase_history;
    TREE *browse_rec;
    TREE *purchase_rec;
    struct user_details *next;
} USER;
```

### Item Structure
```c
typedef struct item_details {
    int item_no;
    char item_name[100];
    char item_type[100];
    int item_rec_flag;  // 0: Default, 1: Browsed, 2: Purchased
    int price;
    int quantity;
    struct item_details *next; // for hashtable
    struct item_details* left; // for tree
    struct item_details* right; // for tree
} ITEM;
```

### Hash Table Structure
```c
typedef struct user_hash {
    int count;
    USER *head;
} USER_HASH;

typedef struct item_hash {
    int count;
    ITEM *head;
} ITEM_HASH;
```
### Tree Structure
```c
typedef struct tree {
    ITEM *root;
} TREE;
```

## Devoloped By

**SHAKIRTH ANISHA: PES2UG23CS927**
**SHRESHT AHUJA: PES2UG23CS558**
**SIDDHARTHA AAKASH RAO: PES2UG23CS927**