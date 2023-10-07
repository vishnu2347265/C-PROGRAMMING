#include <stdio.h>
#include <string.h>

struct Medicine {
    int id, price, quantity;
    char medicineName[100], Company[100], Mfg_Date[11], Exp_Date[11];
    char info[5000]; // Add a field for medicine review or info
};

struct Customer {
    char name[100];
    char contact[15];
    char address[500];
    char email[100];
};

void PurchaseMedicine(struct Medicine m[], int *number);
void MedicineDetails(struct Medicine m[], int number);
void StockOfMedicine(struct Medicine m[], int number);
void UpdateMedicine(struct Medicine m[], int *number);

void WriteDataToFile(struct Medicine m[], int number) {
    FILE *file = fopen("medicine_data.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    int i;

    for (i = 0; i < number; i++) {
        if (m[i].id != 0) {
            fprintf(file, "%d,%s,%d,%d,%s,%s,%s,%s,%s\n", m[i].id, m[i].medicineName, m[i].price, m[i].quantity, m[i].Company, m[i].Mfg_Date, m[i].Exp_Date, m[i].info);
        }
    }

    fclose(file);
}

void ReadDataFromFile(struct Medicine m[], int *number) {
    FILE *file = fopen("medicine_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    *number = 0; // Reset the number of medicines

    while (fscanf(file, "%d,%[^,],%d,%d,%[^,],%[^,],%[^,],%[^,],%[^,]\n", &m[*number].id, m[*number].medicineName, &m[*number].price, &m[*number].quantity, m[*number].Company, m[*number].Mfg_Date, m[*number].Exp_Date, m[*number].info) != EOF) {
        (*number)++;
    }

    fclose(file);
}

int main() {
    struct Medicine m[100];
    int i, choice, number = 0, c;
    ReadDataFromFile(m, &number);

    do {
        printf("\nEnter\n1 - Purchase Medicine\n2 - Medicine Details\n3 - Stock of Medicine in Store\n4 - Update Medicine\n5 - Write To Database\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                PurchaseMedicine(m, &number);
                break;
            }
            case 2: {
                MedicineDetails(m, number);
                break;
            }
            case 3: {
                StockOfMedicine(m, number);
                break;
            }
            case 4: {
                UpdateMedicine(m, &number);
                break;
            }
            case 5:{
                WriteDataToFile(m,number);
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\nTo Continue with other Options Enter 1, Else any other number: ");
        scanf("%d", &c);
        getchar(); // Consume newline character
    } while (c == 1);

    return 0;
}

void PurchaseMedicine(struct Medicine m[], int *number) {
    struct Customer customer;
    int check, i, quantity[100], flag = 0;
    char name[100];
    int total_price = 0; // Initialize total_price here

    for (i = 0; i < 100; i++) {
        quantity[i] = 0;
    }

    int c;

    printf("\nEnter Customer Name: ");
    scanf(" %[^\n]s", customer.name); // Read input with spaces
    getchar(); // Consume newline character

    printf("Enter Customer Contact: ");
    fgets(customer.contact, sizeof(customer.contact), stdin);
    customer.contact[strcspn(customer.contact, "\n")] = 0;

    printf("Enter Customer Address: ");
    fgets(customer.address, sizeof(customer.address), stdin);
    customer.address[strcspn(customer.address, "\n")] = 0;

    printf("Enter Customer Email: ");
    fgets(customer.email, sizeof(customer.email), stdin);
    customer.email[strcspn(customer.email, "\n")] = 0;

    do {
        printf("\nEnter 1 if you know ID else any other number to enter Name of Medicine: ");
        scanf("%d", &check);

        if (check == 1) {
            int id, c;
            printf("\nEnter Id to purchase Medicine: ");
            scanf("%d", &id);

            for (i = 0; i < *number; i++) {
                if (m[i].id == id) {
                    flag = 1;
                    printf("\nThese are the details of Medicine\n");
                    printf("Name=%s\nPrice=%d\nAvailable Quantity=%d\nCompany=%s\nMfg Date=%s\nExp Date=%s\n", m[i].medicineName, m[i].price, m[i].quantity, m[i].Company, m[i].Mfg_Date, m[i].Exp_Date);

                    if (strcmp(m[i].info, "") == 0) {
                        printf("Medicine Review/Info=Not Available\n");
                    } else {
                        printf("Medicine Review/Info=%s\n", m[i].info);
                    }

                    printf("Do you want to purchase %s? If Yes, Enter 1, else any other number: ");
                    scanf("%d", &c);

                    if (c == 1) {
                        printf("Enter Quantity to Purchase: ");
                        scanf("%d", &quantity[i]);

                        if (m[i].quantity >= quantity[i]) {
                            int medicine_total_price = quantity[i] * m[i].price;
                            total_price += medicine_total_price; // Accumulate total_price correctly

                            printf("\nMedicine Name: %s\n", m[i].medicineName);
                            printf("Quantity Purchased: %d\n", quantity[i]);
                            printf("Total Price: %d\n", medicine_total_price);

                            m[i].quantity -= quantity[i]; // Update the quantity in the inventory correctly
                        } else {
                            printf("Please Enter quantity below or equal to Available Quantity\n");
                        }
                    }
                }
            }
            if (flag == 0) {
                printf("Medicine not available in the store.\n");
            }
        } else {
            printf("Enter Name to search and Purchase: ");
            scanf(" %[^\n]s", name); // Read input with spaces

            for (i = 0; i < *number; i++) {
                if (strcmp(m[i].medicineName, name) == 0) {
                    flag = 1;
                    printf("\nThese are the details of Medicine\n");
                    printf("Name=%s\nPrice=%d\nAvailable Quantity=%d\nCompany=%s\nMfg Date=%s\nExp Date=%s\n", m[i].medicineName, m[i].price, m[i].quantity, m[i].Company, m[i].Mfg_Date, m[i].Exp_Date);

                    if (strcmp(m[i].info, "") == 0) {
                        printf("Medicine Review/Info=Not Available\n");
                    } else {
                        printf("Medicine Review/Info=%s\n", m[i].info);
                    }

                    printf("Do you want to purchase %s? If Yes, Enter 1, else any other number: ", m[i].medicineName);
                    scanf("%d", &c);

                    if (c == 1) {
                        printf("Enter Quantity to Purchase: ");
                        scanf("%d", &quantity[i]);

                        if (m[i].quantity >= quantity[i]) {
                            int medicine_total_price = quantity[i] * m[i].price;
                            total_price += medicine_total_price; // Accumulate total_price correctly

                            printf("\nMedicine Name: %s\n", m[i].medicineName);
                            printf("Quantity Purchased: %d\n", quantity[i]);
                            printf("Total Price: %d\n", medicine_total_price);

                            m[i].quantity -= quantity[i]; // Update the quantity in the inventory correctly
                        } else {
                            printf("Please Enter quantity below or equal to Available Quantity\n");
                        }
                    }
                }
            }
            if (flag == 0) {
                printf("Medicine not available in the store.\n");
            }
        }
        printf("To Continue purchasing Enter 1, Else any other number: ");
        scanf("%d", &check);
    } while (check == 1);

    // Print the invoice
    printf("Total Price of all purchased medicines: %d\n", total_price);
    printf("\nInvoice:\n");
    printf("Customer Name: %s\n", customer.name);
    printf("Customer Contact: %s\n", customer.contact);
    printf("Customer Address: %s\n", customer.address);
    printf("Customer Email: %s\n", customer.email);
    printf("Total Price: %d\n", total_price);
    printf("\nPurchased Medicines:\n");

    for (i = 0; i < *number; i++) {
        if (quantity[i] > 0) {
            printf("Medicine Name: %s\n", m[i].medicineName);
            printf("Price per unit: %d\n", m[i].price);
            printf("Quantity Purchased: %d\n", quantity[i]);
            int medicine_total_price = quantity[i] * m[i].price;
            printf("Total Price for this medicine: %d\n\n", medicine_total_price);
        }
    }
}

void MedicineDetails(struct Medicine m[], int number) {
    int choice;
    do {
        printf("\nEnter\n1 - View Information about Medicine\n2 - Products About to Expire\n3 - Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int i;
                char name[100];
                printf("Enter Name of the medicine you want to see Review and Info: ");
                getchar(); // Consume newline character
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;

                int found = 0;
                for (i = 0; i < number; i++) {
                    if (strcmp(m[i].medicineName, name) == 0) {
                        found = 1;
                        printf("\nThese are the details of Medicine\n");
                        printf("Name=%s\nPrice=%d\nAvailable Quantity=%d\nCompany=%s\nMfg Date=%s\nExp Date=%s\n", m[i].medicineName, m[i].price, m[i].quantity, m[i].Company, m[i].Mfg_Date, m[i].Exp_Date);

                        if (strcmp(m[i].info, "") != 0) {
                            printf("Review or Info=%s\n", m[i].info);
                        } else {
                            printf("Review or Info=Not Available\n");
                        }
                    }
                }

                if (!found) {
                    printf("Entered Name Not Found\n");
                }
                break;
            }
            case 2: {
                // Products About to Expire
                printf("\nProducts About to Expire:\n");
                // Implement logic to find and display products about to expire here
                break;
            }
            case 3:
                printf("Exiting Medicine Details.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

void StockOfMedicine(struct Medicine m[], int number) {
    int choice;
    do {
        printf("\nEnter\n1 - Find Out of Stock Products\n2 - Find Current Stock\n3 - Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int i;
                printf("\nOut of Stock Products:\n");
                for (i = 0; i < number; i++) {
                    if (m[i].quantity == 0) {
                        printf("Medicine Name: %s is Out of Stock.\n", m[i].medicineName);
                    }
                }
                break;
            }
            case 2: {
                int i;
                printf("\nCurrent Stock:\n");
                for (i = 0; i < number; i++) {
                    if (m[i].id != 0) {
                        printf("Id=%d\nName=%s\t\tAvailable Quantity=%d\n", m[i].id, m[i].medicineName, m[i].quantity);
                    }
                }
                break;
            }
            case 3:
                printf("Exiting Stock of Medicine.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

void UpdateMedicine(struct Medicine m[], int *number) {
    int choice;
    char info[5000]; // Declare info variable here
    do {
        printf("\nEnter\n1 - Add Medicine\n2 - Delete Medicine\n3 - Change Medicine Details\n4 - Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Add Medicine
                char name[100];
                printf("\nEnter Medicine Id: ");
                scanf("%d", &(m[*number].id));
                getchar(); // Consume newline character
                printf("Enter Medicine Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                strcpy(m[*number].medicineName, name);
                printf("Enter Company Name: ");
                fgets(m[*number].Company, sizeof(m[*number].Company), stdin);
                m[*number].Company[strcspn(m[*number].Company, "\n")] = 0;
                printf("Enter Manufacturing Date: ");
                fgets(m[*number].Mfg_Date, sizeof(m[*number].Mfg_Date), stdin);
                m[*number].Mfg_Date[strcspn(m[*number].Mfg_Date, "\n")] = 0;
                printf("Enter Expiry Date: ");
                fgets(m[*number].Exp_Date, sizeof(m[*number].Exp_Date), stdin);
                m[*number].Exp_Date[strcspn(m[*number].Exp_Date, "\n")] = 0;
                printf("Enter Price: ");
                scanf("%d", &(m[*number].price));
                printf("Enter Quantity: ");
                scanf("%d", &(m[*number].quantity));
                printf("Enter Medicine Review/Info: ");
                getchar(); // Consume newline character
                fgets(info, sizeof(info), stdin);
                info[strcspn(info, "\n")] = 0;
                strcpy(m[*number].info, info);
                (*number)++;
                break;
            }
            case 2: {
                // Delete Medicine
                int id, i;
                printf("\nEnter Medicine Id to delete: ");
                scanf("%d", &id);

                for (i = 0; i < *number; i++) {
                    if (m[i].id == id) {
                        m[i].id = 0; // Mark the medicine as deleted
                        printf("Medicine with ID %d has been deleted.\n", id);
                        break;
                    }
                }
                break;
            }
            case 3: {
                // Change Medicine Details
                int id, i;
                printf("\nEnter Medicine Id to change details: ");
                scanf("%d", &id);

                for (i = 0; i < *number; i++) {
                    if (m[i].id == id) {
                        printf("\nEnter New Details:\n");
                        printf("Enter Medicine Name: ");
                        getchar(); // Consume newline character
                        fgets(m[i].medicineName, sizeof(m[i].medicineName), stdin);
                        m[i].medicineName[strcspn(m[i].medicineName, "\n")] = 0;
                        printf("Enter Company Name: ");
                        fgets(m[i].Company, sizeof(m[i].Company), stdin);
                        m[i].Company[strcspn(m[i].Company, "\n")] = 0;
                        printf("Enter Manufacturing Date: ");
                        fgets(m[i].Mfg_Date, sizeof(m[i].Mfg_Date), stdin);
                        m[i].Mfg_Date[strcspn(m[i].Mfg_Date, "\n")] = 0;
                        printf("Enter Expiry Date: ");
                        fgets(m[i].Exp_Date, sizeof(m[i].Exp_Date), stdin);
                        m[i].Exp_Date[strcspn(m[i].Exp_Date, "\n")] = 0;
                        printf("Enter Price: ");
                        scanf("%d", &(m[i].price));
                        printf("Enter Quantity: ");
                        scanf("%d", &(m[i].quantity));
                        printf("Enter Medicine Review/Info: ");
                        getchar(); // Consume newline character
                        fgets(info, sizeof(info), stdin);
                        info[strcspn(info, "\n")] = 0;
                        strcpy(m[i].info, info);
                        printf("Details for Medicine with ID %d have been updated.\n", id);
                        break;
                    }
                }
                break;
            }
            case 4:
                printf("Exiting Update Medicine.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

