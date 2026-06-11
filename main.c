/********************************************************************************
 * FILE:   main.c
 * NAME:   SATHEESWARAN M
 * BREIF:  Entry point for the Address Book console application.
 *
 *          Presents a menu-driven interface that allows the user to:
 *            1. Create a new contact
 *            2. Search contacts (by name / phone / e-mail)
 *            3. Edit an existing contact
 *            4. Delete a contact
 *            5. List all contacts
 *            6. Save contacts to disk
 *            7. Exit
 *
 *          On startup the address book is loaded from "contacts.txt".
 *          The user is responsible for saving (option 6) before exiting
 *          if they wish to keep any changes.
 ******************************************************************************/
#include <stdio.h>
#include<stdlib.h>
#include "contact.h"

int main()
 {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
       
    do {
        /* -------- Main menu -------- */
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. save contact\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                saveContactsToFile(&addressBook);
                break;
            case 7:
                    exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
    
       return 0;
}
