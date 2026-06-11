/*********************************************************************
 * FILE:     contact.c
 * BREIF:   Implementation of all address-book operations.
 * 
 *          Covers: initialisation from file, contact creation with
 *          full validation, searching, editing, deleting, listing,
 *          and saving contacts back to disk.
 **********************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

//Prints the table header
void printTitle()
{
    printf("%3s\t%-15s\t%-15s\t%-20s\n", "SI.", "Name", "Phone", "Mail");

    printf("------------------------------------------------------\n");
}

//Prints a single contact entry as a numbered table row.
void printcontact(AddressBook *addressBook, int index)
{
    printf("%3d. %-15s %-15s %-20s\n",
           index + 1,
           addressBook->contacts[index].name,
           addressBook->contacts[index].phone,
           addressBook->contacts[index].email);
}

/* Validates that a name contains only alphabetic characters */ 
int validate_name(char name[])
{
    int i = 0;

    while (name[i] != '\0' && name[i] != '\n')
    {
        if (!(isalpha(name[i]) || name[i] == ' '))
        {
            return 0;
        }
        i++;
    }

    return 1;
}
/*Validates that a phone number consists of exactly 10 decimal digits*/
int validate_phone(char phone[])
{
    int i = 0, count = 0;

    while (phone[i] != '\0' && phone[i] != '\n')
    {
        if (!isdigit(phone[i]))
        {
            return 0;
        }

        count++;
        i++;
    }

    if (count != 10)
    {
        return 0;
    }

    return 1;
}
/* Validates a basic e-mail address format */
int validate_mail(char mail[])
{
    if (strchr(mail, '@') && strstr(mail, ".com"))
    {
        return 1;
    }

    return 0;
}
/* Initialises the AddressBook by loading contacts from "contacts.txt" */
void initialize(AddressBook *addressBook)
{
    FILE *fptr;
    addressBook->contactCount = 0;

    fptr = fopen("contacts.txt", "r");
    if (fptr == NULL)
    {
        printf("File opening Failed !!\n");
        return;
    }

    while (fscanf(fptr, " %49[^,],%19[^,],%49[^\n]",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fptr);
}
/* Prints all contacts in the address book */
void listContacts(AddressBook *addressBook)
{
    printTitle();
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%3d. %-15s %-15s %-20s\n", i + 1, 
            addressBook->contacts[i].name, 
            addressBook->contacts[i].phone, 
            addressBook->contacts[i].email);
    }
}
/* creates and stores a new contact */
void createContact(AddressBook *addressBook)
{
    int i, valid;
    int limit;

    char name[30];
    char phone[20];
    char mail[30];

    getchar();

    // ================= NAME ================= //

    limit = 3;

    while (limit > 0)
    {
        printf("Enter name : ");
        scanf("%[^\n]", name);

        valid = 1;

        // duplicate check
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcasecmp(name, addressBook->contacts[i].name) == 0)
            {
                printf("Error: Name already exists\n");
                valid = 0;
                limit--;
                break;
            }
        }

        if (valid)
        {
            break;
        }
    }

    if (limit == 0)
    {
        return;
    }

    limit = 3;

    while (limit > 0)
    {
        valid = validate_name(name);

        if (valid)
        {
            break;
        }

        printf("Invalid name\n");

        printf("Enter name : ");
        scanf(" %[^\n]", name);

        limit--;
    }

    if (limit == 0)
    {
        return;
    }

    // ================= PHONE ================= //

    limit = 3;

    while (limit > 0)
    {
        printf("Enter phone : ");
        scanf(" %[^\n]", phone);

        valid = 1;

        // duplicate check
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(phone, addressBook->contacts[i].phone) == 0)
            {
                printf("Error: Phone already exists\n");
                valid = 0;
                limit--;
                break;
            }
        }

        if (valid)
        {
            break;
        }
    }

    if (limit == 0)
    {
        return;
    }

    limit = 3;

    while (limit > 0)
    {
        valid = validate_phone(phone);

        if (valid)
        {
            break;
        }

        printf("Invalid phone number\n");

        printf("Enter phone : ");
        scanf(" %[^\n]", phone);

        limit--;
    }

    if (limit == 0)
    {
        return;
    }

    // ================= MAIL ================= //

    limit = 3;

    while (limit > 0)
    {
        printf("Enter mail : ");
        scanf(" %[^\n]", mail);

        valid = 1;

        // duplicate check
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(mail, addressBook->contacts[i].email) == 0)
            {
                printf("Error: Mail already exists\n");
                valid = 0;
                limit--;
                break;
            }
        }

        if (valid)
        {
            break;
        }
    }

    if (limit == 0)
    {
        return;
    }

    limit = 3;

    while (limit > 0)
    {
        valid = validate_mail(mail);

        if (valid)
        {
            break;
        }

        printf("Invalid mail\n");

        printf("Enter mail : ");
        scanf(" %[^\n]", mail);
        limit--;
    }

    if (limit == 0)
    {
        return;
    }

    // ================= STORE CONTACT ================= //

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);

    addressBook->contactCount++;

    printf("Contact created successfully\n");
}
/* Searches the address book by name, phone, or e-mail */
void searchContact(AddressBook *addressBook)
{
    int op, i, printed;
    char name[30];
    char phone[20];
    char mail[30];

    do
    {
        printf("\n--- Search by ---\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Mail\n");
        printf("4. exit\n");
        printf("Enter your option: ");
        scanf("%d", &op);

        switch (op)
        {
             /* ---------- Search by Name ---------- */
        case 1:
        {
            printed = 0;
            printf("Enter name : ");
            scanf(" %[^\n]", name);

            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].name, name))
                {
                    if (printed == 0)
                    {
                        printTitle();
                    }

                    printcontact(addressBook, i);

                    printed = 1;
                }
            }
            if (printed == 0)
            {
                printf("\t\tContact not found !!\n");
            }
            break;
        }
         /* ---------- Search by Phone ---------- */
        case 2:
        {
            printed = 0;
            printf("Enter phone : ");
            scanf(" %[^\n]", phone);
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].phone, phone))
                {
                    if (printed == 0)
                    {
                        printTitle();
                    }

                    printcontact(addressBook, i);

                    printed = 1;
                }
            }
            if (printed == 0)
            {
                printf("\t\tContact not found !!\n");
            }
            break;
        }
         /* ---------- Search by Mail-id ---------- */
        case 3:
        {
            printed = 0;
            printf("Enter Mail-id : ");
            scanf(" %[^\n]", mail);

            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].email, mail))
                {
                    if (printed == 0)
                    {
                        printTitle();
                    }

                    printcontact(addressBook, i);

                    printed = 1;
                }
            }
            if (printed == 0)
            {
                printf("\t\tContact not found !!\n");
            }
            break;
        }
        case 4:
            return;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (1);
}
/*  Edits a field of an existing contact */
void editContact(AddressBook *addressBook)
{
    int op, i, j, flag, valid;
    char name[30];
    char phone[20];
    char mail[30];

    do
    {
        printf("\n--- Edit by ---\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Mail\n");
        printf("4. exit\n");
        printf("Enter your option: ");
        scanf("%d", &op);

        switch (op)
        {
         /* ---------- Edit Name ---------- */
        case 1:
        {
            flag = 0;
            printf("Enter name : ");
            scanf(" %[^\n]", name);
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasecmp(addressBook->contacts[i].name, name) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                int org_index = i;
                printf("Enter New name : ");
                scanf(" %[^\n]", name);
                valid = validate_name(name);
                if (valid == 0)
                {
                    printf("\t\tInvalid Name\n");
                    return;
                }

                 /* Duplicate check for new name */
                for (i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcasecmp(addressBook->contacts[i].name, name) == 0)
                    {
                        printf("\t\tDublicate Name !! \n");
                        return;
                    }
                }
                strcpy(addressBook->contacts[org_index].name, name);
                printf("Contact updated successfully\n");
            }
            else
            {
                printf("\t\tContact Not found !!\n");
                return;
            }
            break;
        }
        /* ---------- Edit Phone ---------- */
        case 2:
        {
            flag = 0;
            printf("Enter Number : ");
            scanf(" %[^\n]", phone);
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                int org_index = i;
                printf("Enter New Number : ");
                scanf(" %[^\n]", phone);
                valid = validate_phone(phone);
                if (valid == 0)
                {
                    printf("\t\tInvalid Number\n");
                    return;
                }
                /* Duplicate check for new phone */
                for (i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                    {
                        printf("\t\tDublicate Number !! \n");
                        return;
                    }
                }
                strcpy(addressBook->contacts[org_index].phone, phone);
                printf("Contact updated successfully\n");
            }
            else
            {
                printf("\t\tContact Not found !!\n");
                return;
            }
            break;
        }
        /* ---------- Edit E-mail ---------- */
        case 3:
        {
            flag = 0;
            printf("Enter Mail-id : ");
            scanf(" %[^\n]", mail);
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasecmp(addressBook->contacts[i].email, mail) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                int org_index = i;
                printf("Enter New Mail-id : ");
                scanf(" %[^\n]", mail);
                valid = validate_mail(mail);
                if (valid == 0)
                {
                    printf("\t\tInvalid Mail-id\n");
                    return;
                }

                /* Duplicate check for new e-mail */
                for (i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcasecmp(addressBook->contacts[i].email, mail) == 0)
                    {
                        printf("\t\tDublicate Mail-id !!\n");
                        return;
                    }
                }
                strcpy(addressBook->contacts[org_index].email, mail);
                printf("Contact updated successfully\n");
            }
            else
            {
                printf("\t\tContact Not found !!\n");
                return;
            }
            break;
        }
        case 4:
            return;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (1);
}

/* Deletes a contact identified by name, phone, or e-mail */
void deleteContact(AddressBook *addressBook)
{
    int op, i, j, flag;
    char name[30];
    char phone[20];
    char mail[30];

    do
    {
        printf("\n--- Delete by ---\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Mail\n");
        printf("4. exit\n");
        printf("Enter your option: ");
        scanf("%d", &op);

        switch (op)
        {
           /* ---------- Delete by Name ---------- */
        case 1:
        {
            flag = 0;
            printf("Enter name : ");
            scanf(" %[^\n]", name);
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasecmp(addressBook->contacts[i].name, name) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                for (j = i; j < addressBook->contactCount - 2; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;
                printf("\t\tContact Deleted !!\n");
            }
            else
            {
                printf("\t\tContact Not found !!\n");
                return;
            }
            break;
        }
        /* ---------- Delete by Phone ---------- */
        case 2:
        {
            flag = 0;
            printf("Enter phone : ");
            scanf(" %[^\n]", phone);
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasecmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                for (j = i; j < addressBook->contactCount - 2; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;
                printf("\t\tContact Deleted !!\n");
            }
            else
            {
                printf("\t\tContact Not found !!\n");
                return;
            }
            break;
        }
        /* ---------- Delete by Mail ---------- */
        case 3:
        {
            flag = 0;
            printf("Enter Mail-id : ");
            scanf(" %[^\n]", mail);
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasecmp(addressBook->contacts[i].email, mail) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                for (j = i; j < addressBook->contactCount - 2; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;
                printf("\t\tContact Deleted !!\n");
            }
            else
            {
                printf("\t\tContact Not found !!\n");
                return;
            }
            break;
        }
        case 4:
            return;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (1);
}
/*Persists all contacts to "contacts.txt", overwriting the file*/
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr;
    fptr = fopen("contacts.txt", "w");
    if (fptr == NULL)
    {
        printf("File opening Failed !!\n");
        return;
    }
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
         fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
    fclose(fptr);
    printf("Contacts saved successfully\n");
}

