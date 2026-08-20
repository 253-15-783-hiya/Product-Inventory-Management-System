#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product
{
    int productID;
    char productName[50];
    char category[30];
    float price;
    int quantity;
    int supplierID;
    struct Product *left;
    struct Product *right;
} Product;

Product *root = NULL;

Product *createNode()
{
    Product *newNode = (Product *)malloc(sizeof(Product));
    printf("\nEnter Product ID: ");
    scanf("%d", &newNode->productID);
    printf("Enter Product Name: ");
    scanf(" %[^\n]", newNode->productName);
    printf("Enter Category: ");
    scanf(" %[^\n]", newNode->category);
    printf("Enter Price: ");
    scanf("%f", &newNode->price);
    printf("Enter Quantity: ");
    scanf("%d", &newNode->quantity);
    printf("Enter Supplier ID: ");
    scanf("%d", &newNode->supplierID);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Product *insertProduct(Product *root, Product *newNode)
{
    if (root == NULL)
        return newNode;
    if (newNode->productID < root->productID)
        root->left = insertProduct(root->left, newNode);
    else if (newNode->productID > root->productID)
        root->right = insertProduct(root->right, newNode);
    else
        printf("\nDuplicate Product ID is not allowed.\n");
    return root;
}

void inorder(Product *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("\n----------------------------------");
    printf("\nProduct ID : %d", root->productID);
    printf("\nName       : %s", root->productName);
    printf("\nCategory   : %s", root->category);
    printf("\nPrice      : %.2f", root->price);
    printf("\nQuantity   : %d", root->quantity);
    printf("\nSupplierID : %d", root->supplierID);
    inorder(root->right);
}

Product *searchProduct(Product *root, int id)
{
    if (root == NULL)
        return NULL;
    if (root->productID == id)
        return root;
    if (id < root->productID)
        return searchProduct(root->left, id);
    return searchProduct(root->right, id);
}

void displayProduct(Product *p)
{
    if (p == NULL)
    {
        printf("\nProduct Not Found!\n");
        return;
    }
    printf("\n========== PRODUCT DETAILS ==========\n");
    printf("Product ID : %d\n", p->productID);
    printf("Name       : %s\n", p->productName);
    printf("Category   : %s\n", p->category);
    printf("Price      : %.2f\n", p->price);
    printf("Quantity   : %d\n", p->quantity);
    printf("SupplierID : %d\n", p->supplierID);
}

void updateProduct(Product *root)
{
    int id;
    printf("\nEnter Product ID to Update: ");
    scanf("%d",&id);
    Product *temp = searchProduct(root,id);
    if(temp==NULL)
    {
        printf("\nProduct Not Found!\n");
        return;
    }
    printf("\nEnter New Product Name: ");
    scanf(" %[^\n]",temp->productName);
    printf("Enter New Category: ");
    scanf(" %[^\n]",temp->category);
    printf("Enter New Price: ");
    scanf("%f",&temp->price);
    printf("Enter New Quantity: ");
    scanf("%d",&temp->quantity);
    printf("Enter New Supplier ID: ");
    scanf("%d",&temp->supplierID);
    printf("\nProduct Updated Successfully.\n");
}

void preorder(Product *root)
{
    if(root==NULL)
        return;
    displayProduct(root);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Product *root)
{
    if(root==NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    displayProduct(root);
}

Product *findMin(Product *root)
{
    while(root != NULL && root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

Product *deleteProduct(Product *root, int id)
{
    if(root == NULL)
        return NULL;
    if(id < root->productID)
    {
        root->left = deleteProduct(root->left, id);
    }
    else if(id > root->productID)
    {
        root->right = deleteProduct(root->right, id);
    }
    else
    {
        // Case 1 : No Child
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        // Case 2 : One Child
        else if(root->left == NULL)
        {
            Product *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            Product *temp = root->left;
            free(root);
            return temp;
        }
        // Case 3 : Two Children
        else
        {
            Product *temp = findMin(root->right);
            root->productID = temp->productID;
            strcpy(root->productName,temp->productName);
            strcpy(root->category,temp->category);
            root->price = temp->price;
            root->quantity = temp->quantity;
            root->supplierID = temp->supplierID;
            root->right = deleteProduct(root->right,temp->productID);
        }
    }
    return root;
}

void saveFile(Product *root, FILE *fp)
{
    if(root==NULL)
        return;
    fprintf(fp,"%d %s %s %.2f %d %d\n",
            root->productID,
            root->productName,
            root->category,
            root->price,
            root->quantity,
            root->supplierID);
    saveFile(root->left,fp);
    saveFile(root->right,fp);
}

void saveProducts(Product *root)
{
    FILE *fp;
    fp = fopen("products.txt","w");
    if(fp==NULL)
    {
        printf("File Error!\n");
        return;
    }
    saveFile(root,fp);
    fclose(fp);
    printf("\nProducts Saved Successfully.\n");
}

void loadProducts()
{
    FILE *fp;
    fp = fopen("products.txt","r");
    if(fp==NULL)
        return;
    while(1)
    {
        Product *newNode = (Product *)malloc(sizeof(Product));
        if(fscanf(fp,"%d %s %s %f %d %d",
                  &newNode->productID,
                  newNode->productName,
                  newNode->category,
                  &newNode->price,
                  &newNode->quantity,
                  &newNode->supplierID)!=6)
        {
            free(newNode);
            break;
        }
        newNode->left=NULL;
        newNode->right=NULL;
        root=insertProduct(root,newNode);
    }
    fclose(fp);
}
typedef struct Supplier
{
    int supplierID;
    char supplierName[50];
    char phone[20];
    struct Supplier *next;
} Supplier;

Supplier *head = NULL;

Supplier *createSupplier()
{
    Supplier *newNode = (Supplier *)malloc(sizeof(Supplier));

    printf("\nEnter Supplier ID: ");
    scanf("%d", &newNode->supplierID);

    printf("Enter Supplier Name: ");
    scanf(" %[^\n]", newNode->supplierName);

    printf("Enter Phone Number: ");
    scanf("%s", newNode->phone);

    newNode->next = NULL;

    return newNode;
}

void addSupplier()
{
    Supplier *newNode = createSupplier();
    if(head == NULL)
    {
        head = newNode;
        printf("\nSupplier Added Successfully.\n");
        return;
    }
    Supplier *temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("\nSupplier Added Successfully.\n");
}

void displaySuppliers()
{
    Supplier *temp = head;
    if(temp == NULL)
    {
        printf("\nNo Supplier Found.\n");
        return;
    }
    printf("\n========== SUPPLIER LIST ==========\n");
    while(temp != NULL)
    {
        printf("\nSupplier ID : %d", temp->supplierID);
        printf("\nName        : %s", temp->supplierName);
        printf("\nPhone       : %s\n", temp->phone);
        temp = temp->next;
    }
}

Supplier *searchSupplier(int id)
{
    Supplier *temp = head;
    while(temp != NULL)
    {
        if(temp->supplierID == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void updateSupplier()
{
    int id;
    printf("\nEnter Supplier ID: ");
    scanf("%d",&id);
    Supplier *temp = searchSupplier(id);
    if(temp == NULL)
    {
        printf("\nSupplier Not Found!\n");
        return;
    }
    printf("Enter New Name: ");
    scanf(" %[^\n]", temp->supplierName);
    printf("Enter New Phone: ");
    scanf("%s", temp->phone);
    printf("\nSupplier Updated Successfully.\n");
}

void deleteSupplier()
{
    int id;
    printf("\nEnter Supplier ID: ");
    scanf("%d",&id);
    Supplier *temp = head;
    Supplier *prev = NULL;

    while(temp != NULL)
    {
        if(temp->supplierID == id)
        {
            if(prev == NULL)
            {
                head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            free(temp);
            printf("\nSupplier Deleted Successfully.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("\nSupplier Not Found.\n");
}

void supplierMenu()
{
    int choice;
    while(1)
    {
        printf("\n===== SUPPLIER MENU =====\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Update Supplier\n");
        printf("5. Delete Supplier\n");
        printf("6. Back\n");
        printf("Enter Choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                addSupplier();
                break;
            case 2:
                displaySuppliers();
                break;
            case 3:
            {
                int id;
                printf("Enter Supplier ID: ");
                scanf("%d",&id);
                Supplier *temp = searchSupplier(id);
                if(temp == NULL)
                {
                    printf("Supplier Not Found!\n");
                }
                else
                {
                    printf("\nSupplier ID : %d", temp->supplierID);
                    printf("\nName        : %s", temp->supplierName);
                    printf("\nPhone       : %s\n", temp->phone);
                }
                break;
            }
            case 4:
                updateSupplier();
                break;
            case 5:
                deleteSupplier();
                break;
            case 6:
                return;
            default:
                printf("Invalid Choice.\n");
        }
    }
}

typedef struct Stack
{
    Product data;
    struct Stack *next;
} Stack;
Stack *top = NULL;

void push(Product p)
{
    Stack *newNode = (Stack *)malloc(sizeof(Stack));
    newNode->data = p;
    newNode->next = top;
    top = newNode;
}

Product pop()
{
    Product temp;
    if(top == NULL)
    {
        temp.productID = -1;
        return temp;
    }
    Stack *deleteNode = top;
    temp = top->data;
    top = top->next;
    free(deleteNode);
    return temp;
}

void undoDelete()
{
    Product p = pop();
    if(p.productID == -1)
    {
        printf("\nNothing to Undo.\n");
        return;
    }
    Product *newNode = (Product *)malloc(sizeof(Product));
    *newNode = p;
    newNode->left = NULL;
    newNode->right = NULL;
    root = insertProduct(root, newNode);
    printf("\nUndo Successful.\n");
}

typedef struct Queue
{
    Product data;
    struct Queue *next;
} Queue;
Queue *front = NULL;
Queue *rear = NULL;

void enqueue(Product p)
{
    Queue *newNode = (Queue *)malloc(sizeof(Queue));
    newNode->data = p;
    newNode->next = NULL;
    if(front == NULL)
    {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
}

void dequeue()
{
    if(front == NULL)
    {
        printf("\nQueue Empty!\n");
        return;
    }
    Queue *temp = front;
    printf("\nRestocked Product : %s\n", temp->data.productName);
    front = front->next;
    if(front == NULL)
        rear = NULL;
    free(temp);
}

void displayQueue()
{
    Queue *temp = front;
    if(temp == NULL)
    {
        printf("\nNo Product Needs Restock.\n");
        return;
    }
    printf("\n====== RESTOCK QUEUE ======\n");
    while(temp != NULL)
    {
        printf("\nID       : %d", temp->data.productID);
        printf("\nName     : %s", temp->data.productName);
        printf("\nQuantity : %d\n", temp->data.quantity);

        temp = temp->next;
    }
}

void checkLowStock(Product *root)
{
    if(root == NULL)
        return;
    checkLowStock(root->left);
    if(root->quantity <= 5)
    {
        enqueue(*root);
    }
    checkLowStock(root->right);
}

void queueMenu()
{
    int choice;
    while(1)
    {
        printf("\n===== RESTOCK QUEUE =====\n");
        printf("1. Check Low Stock\n");
        printf("2. Display Queue\n");
        printf("3. Restock Product\n");
        printf("4. Back\n");
        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                checkLowStock(root);
                printf("\nQueue Updated.\n");
                break;
            case 2:
                displayQueue();
                break;
            case 3:
                dequeue();
                break;
            case 4:
                return;
            default:
                printf("Invalid Choice.\n");
        }
    }
}

char username[] = "admin";
char password[] = "1234";

void login()
{
    char user[30];
    char pass[30];
    while(1)
    {
        printf("\n========== LOGIN ==========\n");
        printf("Username : ");
        scanf("%s", user);
        printf("Password : ");
        scanf("%s", pass);
        if(strcmp(user, username)==0 && strcmp(pass,password)==0)
        {
            printf("\nLogin Successful.\n");
            break;
        }
        else
        {
            printf("\nWrong Username or Password!\n");
        }
    }
}

void logout()
{
    printf("\nLogged Out Successfully.\n");
    login();
}

int main()
{
    login();
    loadProducts();
    int choice;
    while (1)
    {
        printf("\n\n========== PRODUCT INVENTORY SYSTEM ==========\n");
        printf("1. Add Product\n");
        printf("2. Display Products (Inorder)\n");
        printf("3. Search Product\n");
        printf("4. Update Product\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Delete Product\n");
        printf("8. Supplier Management\n");
        printf("9. Undo Delete\n");
        printf("10. Restock Queue\n");
        printf("11. Logout\n");
        printf("12. Exit\n");
        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                Product *newNode = createNode();
                root = insertProduct(root, newNode);
                printf("\nProduct Added Successfully.\n");
                break;
            }
            case 2:
                inorder(root);
                break;
           case 3:
            {
                int id;
                printf("\nEnter Product ID: ");
                scanf("%d",&id);
                Product *temp = searchProduct(root,id);
                displayProduct(temp);
                break;
            }
            case 4:
                updateProduct(root);
                break;
            case 5:
                preorder(root);
                break;
            case 6:
                postorder(root);
                break;
                case 7:
                {
                    int id;
                    printf("\nEnter Product ID to Delete: ");
                    scanf("%d",&id);
                    Product *temp = searchProduct(root,id);
                        if(temp != NULL)
                        {
                            push(*temp);
                            root = deleteProduct(root,id);
                            printf("\nProduct Deleted Successfully.\n");
                        }
                    else{
                        printf("\nProduct Not Found!\n");
                    }
                    break;
                }
                case 8:
                supplierMenu();
                break;
                            case 9:
                undoDelete();
                break;
                case 10:
                    queueMenu();
                    break;
                    case 11:
                        logout();
                        break;
            case 12:
                saveProducts(root);
                printf("\nThank You.\n");
                exit(0);
            default:
                printf("\nInvalid Choice.");
        }
    }
    saveProducts(root);
    return 0;
}
