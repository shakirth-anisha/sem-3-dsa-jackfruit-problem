#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct item_details {
    int item_no;
    char item_name[100];
    char item_type[100];
    int item_rec_flag;  //0: Default, 1: Browsed, 2: Purchased
    int price;
    int quantity;
    struct item_details *next; //for hashtable
    struct item_details* left; //for tree
    struct item_details* right; //for tree
} ITEM;

typedef struct item_hash {
    int count;
    ITEM *head;
} ITEM_HASH;

typedef struct tree {
    ITEM *root;
}TREE;

typedef struct user_details {
    char username[100];
    char password[100];
    TREE *browsing_history;
    TREE *purchase_history;
    TREE *browse_rec;
    TREE *purchase_rec;
    struct user_details *next;
} USER;

typedef struct user_hash {
    int count;
    USER *head;
} USER_HASH;


#define SIZE 100

//SHAKIRTH ANISHA PES2UG23CS927
USER* create_user(char *username, char *pass) {
    USER *nn = (USER*)malloc(sizeof(USER));
    if (!nn) {
        printf("Memory allocation error\n");
        exit(1);
    }
    strcpy(nn->username, username);
    strcpy(nn->password, pass);
    //allocating memory to trees
    nn->browsing_history = (TREE *)malloc(sizeof(TREE));
    nn->purchase_history = (TREE *)malloc(sizeof(TREE));
    nn->browse_rec = (TREE *) malloc(sizeof(ITEM_HASH));
    nn->purchase_rec = (TREE *) malloc(sizeof(ITEM_HASH));
    //setting said trees to NULL
    nn->browsing_history->root = NULL;
    nn->purchase_history->root = NULL;
    nn->browse_rec = NULL;
    nn->purchase_rec = NULL;
    nn->next = NULL;
    return nn;
}

//SHAKIRTH ANISHA PES2UG23CS927
ITEM* create_prod(int item_no, char *item_name, char *item_type, int rec_flag, int price, int quantity) {
    ITEM *nn = (ITEM*)malloc(sizeof(ITEM));
    if (!nn) {
        printf("Memory allocation error\n");
        exit(1);
    }
    nn->item_no = item_no;
    strcpy(nn->item_name, item_name);
    strcpy(nn->item_type, item_type);
    nn->item_rec_flag = rec_flag;
    nn->price = price;
    nn->quantity = quantity;
    nn->next = NULL;
    return nn;
}

//SHAKIRTH ANISHA PES2UG23CS927
void insert_user(char *username, char *pass, USER_HASH *hashTable) {
    int key = strlen(username)/2;
    int hash = key % SIZE; // k mod n ; n here is the size
    USER *current = hashTable[hash].head;
    while (current) {
        if (strcmp(current->username, username) == 0) {
            printf("User  %s already exists.\n", username);
            return;
        }
        current = current->next;
    }
    USER *nn = create_user(username, pass);
    nn->next = hashTable[hash].head;
    hashTable[hash].head = nn;
    hashTable[hash].count++;
}

//SHAKIRTH ANISHA PES2UG23CS927
void insert_item(int item_no, char *item_name, char *item_type, int rec_flag, int price, int quantity, ITEM_HASH *hashTable) {
    int hash = item_no % SIZE; // k mod n 
    ITEM *current = hashTable[hash].head;
    while (current) {
        if (strcmp(current->item_name, item_name) == 0) {
            current->quantity++;
        }
        current = current->next;
    }
    ITEM *nn = create_prod(item_no, item_name, item_type, rec_flag, price, quantity);
    nn->next = hashTable[hash].head;
    hashTable[hash].head = nn;
    hashTable[hash].count++;
}

//SHAKIRTH ANISHA PES2UG23CS927
void display_users(USER_HASH *hashTable) {
    int found = 0; 
    for (int i = 0; i < SIZE; i++) {
        USER *t = hashTable[i].head;
        while (t) {
            printf("Username: %s\n", t->username);
            printf("Password: %s\n\n", t->password);
            t = t->next;
            found = 1; 
        }
    }
    if (!found) {
        printf("No users found in the hash table.\n");
    }
}

//SHAKIRTH ANISHA PES2UG23CS927
void display_prod(ITEM_HASH *hashTable) {
    if (hashTable->head == NULL) {
        printf("Nothing Yet!\n\n");
        return;
    }
    int found = 0; 
    for (int i = 0; i < SIZE; i++) {
        ITEM *t = hashTable[i].head;
        while (t) {
            printf("Item No: %d\n", t->item_no);
            printf("Item Name: %s\n", t->item_name);
            // printf("Item Type: %s\n", t->item_type);
            // printf("Rec Flag: %d\n", t->item_rec_flag);
            printf("Price: %d\n", t->price);
            printf("Quantity: %d\n\n", t->quantity);
            t = t->next;
            found = 1; 
        }
    }
    if (!found) {
        printf("No users found in the hash table.\n");
    }
}

//SHAKIRTH ANISHA PES2UG23CS927
void display_prod_details(ITEM *t) {
    if(t->item_rec_flag != 2)
        t->item_rec_flag = 1;
    printf("Item No: %d\n", t->item_no);
    printf("Item Name: %s\n", t->item_name);
    // printf("Item Type: %s\n", t->item_type);
    // printf("Rec Flag: %d\n", t->item_rec_flag);
    printf("Price: %d\n", t->price);
    printf("Quantity: %d\n\n", t->quantity);
    t = t->next;
}

//SHAKIRTH ANISHA PES2UG23CS927
void display_prod_name(ITEM_HASH *hashTable) {
    for (int i = 0; i < SIZE; i++) {
        ITEM *t = hashTable[i].head;
        while (t) {
            printf("Item Number: %d\n", t->item_no);
            printf("Item Name: %s\n\n", t->item_name);
            t = t->next;
        }
    }
}

//SIDDHARTHA AAKASH RAO PES2UG23CS577
USER *find_user(char *username, USER_HASH *HashTable) {
    int hash = strlen(username)/2;
    USER *current = HashTable[hash].head;

    while (current) {
        if (strcmp(current->username, username) == 0) {
            return current; 
        }
        current = current->next;
    }
    return NULL;
}

//SIDDHARTHA AAKASH RAO PES2UG23CS577
ITEM *find_item(ITEM_HASH *hashTable, int item_no) {
    int hash = item_no % SIZE;
    ITEM *current = hashTable[hash].head;
        while (current) {
        if (current->item_no == item_no) {
            return current;
        }
        current = current->next;
    }
    printf("Item Number '%d' not found.\n", item_no);
    return NULL;
}

//SIDDHARTHA AAKASH RAO PES2UG23CS577
void traverse_tree_and_set_flag(ITEM *root, ITEM_HASH *hashtable, int flag) {
        if (!root) return;
        traverse_tree_and_set_flag(root->left, hashtable, flag);
        int hash = root->item_no % SIZE;
        ITEM *current = hashtable[hash].head;
        while (current) {
            if (current->item_no == root->item_no) {
                current->item_rec_flag = flag;
                break;
            }
            current = current->next;
        }
        traverse_tree_and_set_flag(root->right, hashtable, flag);
}

//SIDDHARTHA AAKASH RAO PES2UG23CS577
void set_flag_on_login(TREE *browse, TREE *purchase, ITEM_HASH *hashtable) {
    if (browse) 
    traverse_tree_and_set_flag(browse->root, hashtable, 1);
    if (purchase) 
        traverse_tree_and_set_flag(purchase->root, hashtable, 2);
}

//SHAKIRTH ANISHA PES2UG23CS927
void reset_items(ITEM_HASH *hashTable) {
    for (int i = 0; i < SIZE; i++) {
        ITEM *t = hashTable[i].head;
        while (t) {
            t->item_rec_flag = 0;
            t = t->next;
        }
    }
}

//SHAKIRTH ANISHA PES2UG23CS927
void free_users(USER_HASH *hashTable) {
    for (int i = 0; i < SIZE; i++) {
        USER *current = hashTable[i].head;
        while (current) {
            USER *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

//SHAKIRTH ANISHA PES2UG23CS927
void free_items(ITEM_HASH *hashTable) {
    for (int i = 0; i < SIZE; i++) {
        ITEM *current = hashTable[i].head;
        while (current) {
            ITEM *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

//Trees for browse and purchase history 
//SHRESHT AHUJA PES2UG23CS558
void insert_tree(TREE *t, int item_no, char *item_name, char *item_type, int rec_flag, int price, int quantity) {
    ITEM *curr = t->root, *prev = NULL, *temp;
    temp = (ITEM *)malloc(sizeof(ITEM));
    if (!temp) {
        printf("Memory allocation error\n");
        exit(1);
    }
    temp->item_no = item_no;
    strcpy(temp->item_name, item_name);
    strcpy(temp->item_type, item_type);
    temp->item_rec_flag = rec_flag;
    temp->price = price;
    temp->quantity = quantity;
    temp->left = temp->right = NULL;
    if (curr == NULL) {
        t->root = temp;
        return;
    }
    while (curr != NULL) {
        prev = curr;
        if (item_no == curr->item_no) {
            free(temp);
            return;
        } else if (item_no > curr->item_no) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }
    if (item_no > prev->item_no) {
        prev->right = temp;
    } else {
        prev->left = temp;
    }
}

//SHRESHT AHUJA PES2UG23CS558
void delete_tree(TREE *t, int item_no) {
    ITEM *curr = t->root, *prev = NULL, *temp, *p;
    while (curr != NULL && curr->item_no != item_no) {
        prev = curr;
        if (item_no < curr->item_no)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (curr == NULL) {
        return;
    }
    // No children
    if (curr->left == NULL && curr->right == NULL) {
        if (prev == NULL) // Deleting the root node
            t->root = NULL;
        else if (prev->left == curr)
            prev->left = NULL;
        else
            prev->right = NULL;
        free(curr);
    }
    // One child
    else if (curr->left == NULL || curr->right == NULL) {
        ITEM *child = (curr->left != NULL) ? curr->left : curr->right;
        if (prev == NULL)
            t->root = child;
        else if (prev->left == curr)
            prev->left = child;
        else
            prev->right = child;
        free(curr);
    }
    // Two children by inorder successor
    else {
        p = NULL;
        temp = curr->right;
        while (temp->left != NULL) {
            p = temp;
            temp = temp->left;
        }
        curr->item_no = temp->item_no;
        strcpy(curr->item_name, temp->item_name);
        strcpy(curr->item_type, temp->item_type);
        curr->price = temp->price;
        curr->quantity = temp->quantity;
        if (p != NULL)
            p->left = temp->right;
        else
            curr->right = temp->right;
        free(temp);
    }
}

//SHRESHT AHUJA PES2UG23CS558
void browse_purchase(USER *user, ITEM_HASH *item_hashTable) {
    if (!user->browsing_history) {
        user->browsing_history = (TREE *)malloc(sizeof(TREE));
        user->browsing_history->root = NULL;
    }
    if (!user->purchase_history) {
        user->purchase_history = (TREE *)malloc(sizeof(TREE));
        user->purchase_history->root = NULL;
    }
    TREE *browse = user->browsing_history;
    TREE *purchase = user->purchase_history;
    for (int i = 0; i < SIZE; i++) {
        ITEM *t = item_hashTable[i].head;
        while (t) {
            if (t->item_rec_flag == 1) {
                insert_tree(browse, t->item_no, t->item_name, t->item_type, t->item_rec_flag, t->price, t->quantity);
            } else if (t->item_rec_flag == 2) {
                delete_tree(browse, t->item_no);
                insert_tree(purchase, t->item_no, t->item_name, t->item_type, t->item_rec_flag, t->price, t->quantity);
            }
            t = t->next;
        }
    }
}

//SHRESHT AHUJA PES2UG23CS558
void display_tree(ITEM *root) {   //INORDER
    if (root != NULL) {
        display_tree(root->left);
        display_prod_details(root);
        display_tree(root->right);
    }
}

//SHRESHT AHUJA PES2UG23CS558
void add_rec_by_item_type(ITEM *root, char *item_type, TREE *found) {
    if (root == NULL) {
        return;
    }
    add_rec_by_item_type(root->left, item_type, found);
    if (strcmp(item_type, root->item_type) == 0) {
        insert_tree(found, root->item_no, root->item_name, root->item_type, root->item_rec_flag, root->price, root->quantity);
    }
    add_rec_by_item_type(root->right, item_type, found);
}

//SHAKIRTH ANISHA PES2UG23CS927
void recommend(USER *user, ITEM_HASH *item_hashTable) {
    if (user->browse_rec == NULL) {
        user->browse_rec = (TREE *)malloc(sizeof(TREE));
        user->browse_rec->root = NULL;
    }
    if (user->purchase_rec == NULL) {
        user->purchase_rec = (TREE *)malloc(sizeof(TREE));
        user->purchase_rec->root = NULL;
    }
    ITEM *browsing_item = user->browsing_history->root;
    while (browsing_item != NULL) {
        add_rec_by_item_type(browsing_item, browsing_item->item_type, user->browse_rec);
        browsing_item = browsing_item->right;
    }
    for (int i = 0; i < SIZE; i++) {
        ITEM *current = item_hashTable[i].head;
        while (current != NULL) {
            ITEM *temp = user->browsing_history->root;
            while (temp != NULL) {
                if (strcmp(current->item_type, temp->item_type) == 0) {
                    insert_tree(user->browse_rec, current->item_no, current->item_name, current->item_type, current->item_rec_flag, current->price, current->quantity);
                }
                temp = temp->right;
            }
            current = current->next;
        }
    }
    ITEM *purchase_item = user->purchase_history->root;
    while (purchase_item != NULL) {
        add_rec_by_item_type(purchase_item, purchase_item->item_type, user->purchase_rec);
        purchase_item = purchase_item->right;
    }
    for (int i = 0; i < SIZE; i++) {
        ITEM *current = item_hashTable[i].head;
        while (current != NULL) {
            ITEM *temp = user->purchase_history->root;
            while (temp != NULL) {
                if (strcmp(current->item_type, temp->item_type) == 0) {
                    insert_tree(user->purchase_rec, current->item_no, current->item_name, current->item_type, current->item_rec_flag, current->price, current->quantity);
                }
                temp = temp->right;
            }
            current = current->next;
        }
    }
    printf("\nRecommendations based on your browsing and purchase history:\n");
    printf("=====================================================================\n");
    printf("Browse History Recommendations:\n");
    display_tree(user->browse_rec->root);
    printf("=====================================================================\n");
    printf("Purchase History Recommendations:\n");
    display_tree(user->purchase_rec->root);
    printf("=====================================================================\n");
}

//SHAKIRTH ANISHA PES2UG23CS927
void ui_component(USER_HASH *u_h, ITEM_HASH *i_h){
    //LOG IN OPTIONS
    int log_in_option, main_option, prod_option, rec_option;
    char username[100], c_password[100], check_username[100], check_password[100], new_username[100], new_password[100], buy_option[10];
    USER *sample;
    printf("=====================================================================\n\n");
    printf("                          E-commerce Platform\n\n");
    printf("=====================================================================\n\n\n");

    log_in:
    printf("=====================================================================\n\n");
    printf("                             Login/Sign Up\n\n");
    printf("=====================================================================\n\n");
    printf("                  |           1.)  Sign Up        |\n");
    printf("                  |           2.)  Log In         |\n");
    printf("                  |           3.)  Exit           |\n");
    printf("\n=====================================================================\n\n");
    printf("                       Enter your choice: ");
    scanf("%d", &log_in_option);
    switch (log_in_option) {
    case 1:
    printf("=====================================================================\n\n");
    printf("                Enter your new username: ");
    scanf("%s", new_username);
    if (find_user(new_username, u_h) == NULL) {
        printf("                Enter your new password: ");
        scanf("%s", new_password);
        printf("\n");
        printf("=====================================================================\n\n\n");
        insert_user(new_username, new_password, u_h);
        sample = find_user(new_username, u_h);
        set_flag_on_login(sample->browsing_history, sample->purchase_history, i_h);
    } 
    else {
        printf("User already Exists!\n\n");
        goto log_in;
    }
    break;

case 2:
    printf("=====================================================================\n\n");
    printf("\n                          Enter your username: ");
    scanf("%s", check_username);
    sample = find_user(check_username, u_h);
    if (sample != NULL) {
        printf("                          Enter your password: ");
        scanf("%s", check_password);
        printf("\n=====================================================================\n\n\n");
        if (strcmp(sample->password, check_password) != 0) {
            printf("\n\nWrong Password!\n\n");
            goto log_in;
        }
        set_flag_on_login(sample->browsing_history, sample->purchase_history, i_h);
    } else {
        printf("\n\nUser does not exist! Try Sign Up.\n\n");
        goto log_in;
    }
    break;

    case 3:
        goto exit_shop;

    default:
        printf("Invalid Option. Try Again.\n\n");
        goto log_in;
    }


    //SHOPPING OPTIONS
    main_menu:
    printf("                    What would you like to access?\n\n");
    printf("=====================================================================\n");
    printf("                  |      1.)  Available Products  |\n");
    printf("                  |      2.)  Recommendations     |\n");
    printf("                  |      3.)  User Details        |\n");
    printf("                  |      4.)  Log Out             |\n");
    printf("=====================================================================\n\n");

    printf("                       Enter your choice: ");
    scanf("%d", &main_option);
    if (!sample) {
        printf("Error: User data not initialized.\n");
        return; // Exit the function to prevent segmentation fault
    }
    switch (main_option)
    {
    case 1:
        display_prod_name(i_h);
        printf("               Browse Product Number: ");
        scanf("%d", &prod_option);
        display_prod_details(find_item(i_h, prod_option));
        printf("                  Buy Product? (Y/N): ");
        scanf("%s", buy_option);
        if((strcmp(buy_option, "Y")==0)|| (strcmp(buy_option, "y")==0)){
            find_item(i_h, prod_option)->item_rec_flag = 2;
            find_item(i_h, prod_option)->quantity--;
        }
        browse_purchase(sample, i_h);
        // printf("browse");
        // display_tree(sample->browsing_history->root);
        // printf("purchase");
        // display_tree(sample->purchase_history->root);
        goto main_menu;
        break;
    
    case 2:
        recommend(sample, i_h);
        goto main_menu;
    case 3:
        printf("\n\n=====================================================================\n\n");
        printf("                             Your Profile\n\n");
        printf("=====================================================================\n\n");
        printf("                           Username: %s\n", sample->username);
        printf("\n=====================================================================\n\n");
        goto main_menu;

    case 4:
        reset_items(i_h);
        goto log_in;
    default:
        break;
    }           


    exit_shop:
    printf("Thanks for Visiting! :)\n\n");
}

//SHAKIRTH ANISHA PES2UG23CS927
int main() {
    USER_HASH hashTable[SIZE] = {0};
    ITEM_HASH hashTable_p[SIZE] = {0};

    insert_user("anisha", "1234", hashTable);
    insert_user("shresht", "3333", hashTable);
    insert_user("sid", "idk", hashTable);

    insert_item(1, "samosa", "food", 0, 15, 45, hashTable_p);
    insert_item(2, "chocolate", "food", 0, 20, 5, hashTable_p);
    insert_item(3, "popcorn", "food", 0, 45, 10, hashTable_p);
    insert_item(4, "MacBook", "laptop", 0, 2000000, 2, hashTable_p);
    insert_item(5, "Windows", "laptop", 0, 1500, 4, hashTable_p);
    insert_item(6, "Glitter", "Stationary", 0, 10, 450, hashTable_p);
    insert_item(7, "Scale", "Stationary", 0, 15, 25, hashTable_p);
    insert_item(8, "Pen", "Stationary", 0, 20, 45, hashTable_p);
    insert_item(9, "Glue", "Stationary", 0, 40, 50, hashTable_p);
    insert_item(10, "Stapler", "Stationary", 0, 100, 14, hashTable_p);
    
    ui_component(hashTable, hashTable_p);
    // display_users(hashTable);
    // display_prod(hashTable_p);
    
    free_users(hashTable);
    free_items(hashTable_p);

    return 0;
}