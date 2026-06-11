# 📒 AddressBook-C

A menu-driven **Address Book console application** written in C.  
Contacts are stored in a plain-text file and persist across sessions.

---

##  Features

- Add a new contact (name, phone, e-mail)
- Search contacts by name, phone, or e-mail
- Edit an existing contact field
- Delete a contact by name, phone, or e-mail
- List all contacts in a formatted table
- Save contacts to disk

---

##  Project Structure

```
AddressBook-C/
├── main.c          # Entry point – menu loop & user interaction
├── contact.c       # Core logic – CRUD operations & validation
├── contact.h       # Header – structs, constants & prototypes
└── contacts.txt    # Persistent storage (CSV-style flat file)
```

---

##  Build & Run

```bash
gcc main.c contact.c -o addressbook
./addressbook
```

---

##  Menu Options

```
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exit
```

>  Always choose **option 6 (Save)** before exiting to persist any changes.

---

## ✅ Validation Rules

| Field | Rule |
|-------|------|
| Name  | Alphabets and spaces only, no duplicates (case-insensitive) |
| Phone | Exactly 10 digits, no duplicates |
| Email | Must contain `@` and `.com`, no duplicates |

Each field allows up to **3 attempts** before the operation is cancelled.

---

##  Data Format (`contacts.txt`)

Contacts are stored one per line in comma-separated format:

```
John,1234567890,john@example.com
Bob Johnson,1112223333,bob@company.com
```

---

##  Concepts Used

| Concept | Where Applied |
|---------|---------------|
| **Structures (`struct`)** | `Contact` and `AddressBook` types defined in `contact.h` |
| **File Handling** | `fopen`, `fscanf`, `fprintf`, `fclose` to load/save `contacts.txt` |
| **Pointers** | `AddressBook *` passed to all functions |
| **Arrays** | Fixed-size `contacts[MAX_CONTACTS]` array inside `AddressBook` |
| **String Functions** | `strcpy`, `strcmp`, `strcasecmp`, `strstr`, `strchr`, `strstr` from `<string.h>` |
| **Input Validation** | `isalpha`, `isdigit` from `<ctype.h>` for name and phone checks |
| **Modular Programming** | Logic split across `main.c`, `contact.c`, and `contact.h` |
| **Header Guards** | `#ifndef / #define / #endif` in `contact.h` |
| **`typedef`** | Used to alias `struct` types as `Contact` and `AddressBook` |
| **Switch-Case** | Menu navigation in both `main.c` and sub-menus in `contact.c` |
| **Do-While Loop** | Keeps menu running until the user exits |
| **Preprocessor Macros** | `#define MAX_CONTACTS 100` |
| **Dynamic Input** | `scanf("%[^\n]")` to read strings with spaces |

---

## 👤 Author

**Satheeswaran M**  
GitHub: [@sathees-waran](https://github.com/sathees-waran)
