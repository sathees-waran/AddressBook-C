/*********************************************************************
 * FILE:     contact.h
 * BREIF:   Header file for the Address Book application.
 *          Defines the Contact and AddressBook data structures,
 *          symbolic constants, and all function prototypes
 *          used across the project.
 **********************************************************************/
#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

// Represents a single address-book entry
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

//A fixed-capacity collection of Contact records.
typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

//All function declrations
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
#endif
