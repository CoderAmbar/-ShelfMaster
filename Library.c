#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define MAX_BOOKS 100
#define MAX_USERS 100
#define PASSWORD_FILE "password.txt"

// Structures
typedef struct
{
    int id;
    char title[50];
    char author[50];
    char category[50];
    char issuedDate[50];
} Book;

typedef struct
{
    int id;
    char name[50];
    char issuedBookTitle[50];
    char issuedBookAuthor[50];
    char issuedBookDate[20];
    char category[50];
} User;

// Arrays to store books and users
Book books[MAX_BOOKS];
User users[MAX_USERS];
int bookCount = 0;
int userCount = 0;

// Function prototypes
void Password();
void securePasswordInput();
void Menu();
void addbook();
void deleteBook();
void listBooks();
void searchBookByTitle();
void addUser();
void deleteUser();
void listUsers();
void searchUserByName();
void ReturnToMain();
void change_password();
void cap();
void saveBooks();
void saveUsers();

int main()
{
    int choice;

    Password();

    printf("Welcome to Library Management System");
    Sleep(1000);

    for (int i = 0; i < 3; i++)
    {
        printf(".");
        Sleep(300);
    }
    system("cls");

    do
    {
        printf("\n--- Main Menu ---\n");
        printf("1. Manage Books\n");
        printf("2. Manage Users\n");
        printf("3. Change Password\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");

        switch (choice)
        {
        case 1:
            int bookChoice;
            do
            {
                printf("\n--- Book Management ---\n");
                printf("1. Add Book\n");
                printf("2. Delete Book\n");
                printf("3. List Books\n");
                printf("4. Search Book by Title\n");
                printf("5. Go back to Main Menu\n");
                printf("Enter your choice: ");
                scanf("%d", &bookChoice);
                system("cls");

                switch (bookChoice)
                {
                case 1:
                    addbook();
                    break;
                case 2:
                    deleteBook();
                    break;
                case 3:
                    listBooks();
                    break;
                case 4:
                    searchBookByTitle();
                    break;
                case 5:
                    break;
                default:
                    printf("Invalid choice! Please try again\n");
                    Sleep(800);
                    break;
                }
            } while (bookChoice != 5);
            break;

        case 2:
            int userChoice;
            do
            {
                printf("\n--- User Management ---\n");
                printf("1. Add User\n");
                printf("2. Delete User\n");
                printf("3. List Users\n");
                printf("4. Search User by Name\n");
                printf("5. Go back to Main Menu\n");
                printf("Enter your choice: ");
                scanf("%d", &userChoice);
                system("cls");

                switch (userChoice)
                {
                case 1:
                    addUser();
                    break;
                case 2:
                    deleteUser();
                    break;
                case 3:
                    listUsers();
                    break;
                case 4:
                    searchUserByName();
                    break;
                case 5:
                    break;
                default:
                    printf("Invalid choice! Please try again\n");
                    Sleep(800);
                    break;
                }
            } while (userChoice != 5);
            break;

        case 3:
            change_password();
            break;

        case 4:
            printf("Exiting the system");
            for (int i = 0; i < 3; i++)
            {
                printf(".");
                Sleep(500);
            }
            exit(0);

        default:
            printf("Invalid choice! Please try again\n");
            Sleep(800);
            break;
        }

    } while (choice != 4);

    return 0;
}

// Function to display the menu
void Menu()
{
    printf("\n--- Library Management System ---\n");
    printf("1. Add Book\n");
    printf("2. Delete Book\n");
    printf("3. List Books\n");
    printf("4. Search Book by Title\n");
    printf("5. Add User\n");
    printf("6. Delete User\n");
    printf("7. List Users\n");
    printf("8. Search User by Name\n");
    printf("9. Change Password\n");
    printf("10. Exit\n");
}

// Function to save books
void saveBooks()
{
    FILE *file = fopen("Database_Books.csv", "w");

    if (file == NULL)
    {
        printf("Error: Unable to open file for saving books!\n");
        return;
    }

    fprintf(file, "%-5s | %-20s | %-20s | %-15s\n",
            "ID", "Title", "Author", "Category");

    for (int i = 0; i < bookCount; i++)
    {
        fprintf(file, "%-5d | %-20s | %-20s | %-15s\n",
                books[i].id, books[i].title, books[i].author,books[i].category);
    }

    fclose(file);
    // printf("Books saved successfully to Database_Books.csv.\n");
}

// Function to save users
void saveUsers()
{
    FILE *file = fopen("Database_Users.csv", "w");

    if (file == NULL)
    {
        printf("Error: Unable to open file for saving users!\n");
        return;
    }

    fprintf(file, "%-5s | %-20s | %-25s | %-25s | %-15s\n",
            "ID", "Name", "Issued Book Title", "Issued Book Author", "Issued Book Date");

    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "%-5d | %-20s | %-25s | %-25s | %-15s\n",
                users[i].id, users[i].name, users[i].issuedBookTitle,
                users[i].issuedBookAuthor, users[i].issuedBookDate);
    }

    fclose(file);
    // printf("Users saved successfully to Database_Users.csv.\n");
}

// Function to make the password secure
void securePasswordInput(char *password, int maxLength)
{

    int index = 0;
    char ch;

    while ((ch = getch()) != '\r')
    {
        if (ch == '\b' && index > 0)
        {
            printf("\b \b");
            index--;
        }
        else if (index < maxLength - 1 && ch != '\b')
        {
            password[index++] = ch;
            printf("*");
        }
    }

    password[index] = '\0';
    printf("\n");
}

// Function to enter a password
void Password()
{

    char storedPassword[50];
    
    char enteredPassword[50];
    
    FILE *file = fopen(PASSWORD_FILE, "r");

    if (file == NULL)
    {
        printf("Error: Password file not found.\n");
        exit(1);
    }

    fgets(storedPassword, sizeof(storedPassword), file);
    fclose(file);

    storedPassword[strcspn(storedPassword, "\n")] = 0;

    int attempts = 0;
    const int maxAttempts = 3;
    int accessGranted = 0;

    do
    {
        printf("Enter password (Attempt %d of %d): ", attempts + 1, maxAttempts);
        securePasswordInput(enteredPassword, sizeof(enteredPassword));

        if (strcmp(storedPassword, enteredPassword) == 0)
        {
            accessGranted = 1;
            break;
        }
        else
        {
            printf("Incorrect password.\n");
        }

        attempts++;
    } while (attempts < maxAttempts);

    if (accessGranted)
    {
        printf("Access granted");
        for (int i = 0; i < 3; i++)
        {
            printf(".");
            Sleep(500);
        }
        system("cls");
        Sleep(800);
    }
    else
    {
        printf("Access denied! Too many failed attempts.\n");
        exit(1);
    }
}

// Function to change password
void change_password()
{

    char storedPassword[50];
    char enteredPassword[50];
    char newPassword[50];

    FILE *file = fopen(PASSWORD_FILE, "r");
    if (file == NULL)
    {
        printf("Error: Password file not found.\n");
        return;
    }

    fgets(storedPassword, sizeof(storedPassword), file);
    fclose(file);

    storedPassword[strcspn(storedPassword, "\n")] = 0;

    printf("Enter old password: ");
    scanf(" %[^\n]", enteredPassword);

    if (strcmp(storedPassword, enteredPassword) == 0)
    {
        while (1)
        {
            printf("Enter new password: ");
            scanf(" %[^\n]", newPassword);

            if (strcmp(storedPassword, newPassword) == 0)
            {
                printf("New password cannot be the same as the old password.\n");
            }
            else
            {
                file = fopen(PASSWORD_FILE, "w");
                if (file == NULL)
                {
                    printf("Error: Could not open the password file.\n");
                    return;
                }

                fprintf(file, "%s", newPassword);
                fclose(file);

                printf("Password updated successfully!\n");
                break;
            }
        }
    }
    else
    {
        printf("Old password is incorrect. Password update failed.\n");
    }

    ReturnToMain();
}

// Function to return to the main menu
void ReturnToMain()
{
    printf("\nPress Enter to return to the main menu...");
    getchar();
    getchar();
    system("cls");
}

// Function to add a book
void addbook()
{
    if (bookCount >= MAX_BOOKS)
    {
        printf("Book List is full\n");
        ReturnToMain();
        return;
    }

    Book newbook;

    newbook.id = bookCount + 1;

    printf("Enter the book Title: ");
    scanf(" %[^\n]", newbook.title);
    cap(newbook.title);

    printf("Enter the author name: ");
    scanf(" %[^\n]", newbook.author);
    cap(newbook.author);

    printf("Choose a Genre:\n");
    printf("1. Fiction\n");
    printf("2. Science\n");
    printf("3. Technology\n");
    printf("4. History\n");
    printf("5. Literature\n");
    printf("6. Other\n");

    int categoryChoice;

    printf("Enter the number corresponding to the Genre: ");
    scanf("%d", &categoryChoice);

    switch (categoryChoice)
    {
    case 1:
        strcpy(newbook.category, "Fiction");
        break;
    case 2:
        strcpy(newbook.category, "Science");
        break;
    case 3:
        strcpy(newbook.category, "Technology");
        break;
    case 4:
        strcpy(newbook.category, "History");
        break;
    case 5:
        strcpy(newbook.category, "Literature");
        break;
    case 6:
        printf("Enter custom Genre: ");
        scanf(" %[^\n]", newbook.category);
        break;
    default:
        printf("Invalid choice. Setting Genre to 'Other'.\n");
        strcpy(newbook.category, "Other");
        break;
    }

    books[bookCount++] = newbook;
    printf("Book added successfully!!!....\n");

    saveBooks();

    ReturnToMain();
}

// Function to delete a book
void deleteBook()
{
    int id, found = 0;
    char confirm[3];
    int attempt = 0;
    printf("Enter the Book ID to delete: ");

    while (scanf("%d", &id) != 1)
    {
        printf("Invalid input. Please enter a valid book ID: ");
        while (getchar() != '\n')
            ;
    }

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == id)
        {
            found = 1;
            printf("Book found: ID = %d, Title = %s\n", books[i].id, books[i].title);
            printf("Are you sure you want to delete this book? This action cannot be undone. (y/n): ");

            while (1)
            {
                getchar();
                scanf("%s", confirm);

                if (strcmp(confirm, "y") == 0 || strcmp(confirm, "Y") == 0 || strcmp(confirm, "yes") == 0 || strcmp(confirm, "Yes") == 0)
                {
                    for (int j = i; j < bookCount - 1; j++)
                    {
                        books[j] = books[j + 1];
                    }
                    bookCount--;
                    printf("\nThe book with ID %d has been deleted successfully.\n", id);
                    saveBooks();
                    break;
                }
                else if (strcmp(confirm, "n") == 0 || strcmp(confirm, "N") == 0 || strcmp(confirm, "no") == 0 || strcmp(confirm, "No") == 0)
                {
                    printf("\nBook deletion has been canceled. The book with ID %d remains in the system.\n", id);
                    break;
                }
                else
                {
                    attempt++;
                    if (attempt >= 3)
                    {
                        printf("Too many invalid attempts. Returning to the main menu.\n");
                        break;
                    }
                    printf("Invalid input. Please type 'y' or 'n' to confirm (or 'yes'/'no'):\n");
                }
            }
            break;
        }
    }

    if (!found)
    {
        printf("Error: Book with ID %d not found in the system.\n", id);
        printf("Please check the ID and try again.\n");
    }

    ReturnToMain();
}

// Function to list all books
void listBooks()
{
    if (bookCount == 0)
    {
        printf("\nNo books available in the library.\n");
        ReturnToMain();
        return;
    }

    int choice;
    int filtered = 0;
    char filterCategory[50];
    char filterAuthor[50];

    printf("\n--- List of Books ---\n");

    printf("Would you like to filter or sort the books?\n");
    printf("1. Sort by Title\n");
    printf("2. Sort by Author\n");
    printf("3. Filter by Genre\n");
    printf("4. Filter by Author\n");
    printf("5. Show all books (no filter/sort)\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            for (int i = 0; i < bookCount - 1; i++)
            {
                for (int j = i + 1; j < bookCount; j++)
                {
                    if (strcmp(books[i].title, books[j].title) > 0)
                    {
                        Book temp = books[i];
                        books[i] = books[j];
                        books[j] = temp;
                    }
                }
            }
            printf("Books sorted by Title.\n");
            break;

        case 2:
            for (int i = 0; i < bookCount - 1; i++)
            {
                for (int j = i + 1; j < bookCount; j++)
                {
                    if (strcmp(books[i].author, books[j].author) > 0)
                    {
                        Book temp = books[i];
                        books[i] = books[j];
                        books[j] = temp;
                    }
                }
            }
            printf("Books sorted by Author.\n");
            break;

        case 3:
            printf("Select Genre to filter by:\n");
            printf("1. Fiction\n");
            printf("2. Science\n");
            printf("3. Technology\n");
            printf("4. History\n");
            printf("5. Literature\n");
            printf("6. Other\n");
            printf("Enter your choice (1-6): ");
            int genreChoice;
            scanf("%d", &genreChoice);

            switch (genreChoice)
            {
                case 1:
                    strcpy(filterCategory, "Fiction");
                    break;
                case 2:
                    strcpy(filterCategory, "Science");
                    break;
                case 3:
                    strcpy(filterCategory, "Technology");
                    break;
                case 4:
                    strcpy(filterCategory, "History");
                    break;
                case 5:
                    strcpy(filterCategory, "Literature");
                    break;
                case 6:
                    strcpy(filterCategory, "Other");
                    break;
                default:
                    printf("Invalid choice. No filter applied.\n");
                    filterCategory[0] = '\0'; 
                    break;
            }

            if (filterCategory[0] != '\0')
            {
                printf("\nFiltered by Genre: %s\n", filterCategory);
                filtered = 1;
            }
            break;

        case 4:
            printf("Enter author name to filter by: ");
            getchar();
            fgets(filterAuthor, sizeof(filterAuthor), stdin);
            filterAuthor[strcspn(filterAuthor, "\n")] = 0;
            printf("\nFiltered by Author: %s\n", filterAuthor);
            filtered = 1;
            break;

        case 5:
            printf("\nDisplaying all available books without any filtering or sorting.\n");

            for (int i = 0; i < bookCount - 1; i++)
            {
                for (int j = i + 1; j < bookCount; j++)
                {
                    if (books[i].id > books[j].id)
                    {
                        Book temp = books[i];
                        books[i] = books[j];
                        books[j] = temp;
                    }
                }
            }
            break;

        default:
            printf("\nInvalid choice. Showing all books without filtering or sorting.\n");
            break;
    }

    printf("\n--- Books ---\n");
    printf("%-5s | %-20s | %-20s | %-15s\n", "ID", "Title", "Author", "Genre");
    printf("---------------------------------------------------------------\n");

    int displayed = 0;
    for (int i = 0; i < bookCount; i++)
    {
        if (filtered)
        {
            if (strcmp(books[i].category, filterCategory) == 0 || strcmp(books[i].author, filterAuthor) == 0)
            {
                printf("%-5d | %-20s | %-20s | %-15s\n",
                       books[i].id, books[i].title, books[i].author, books[i].category);
                displayed++;
            }
        }
        else
        {
            printf("%-5d | %-20s | %-20s | %-15s\n",
                   books[i].id, books[i].title, books[i].author, books[i].category);
            displayed++;
        }
    }

    if (displayed == 0)
    {
        printf("\nNo books match your filter criteria.\n");
    }

    printf("\nTotal number of books available: %d\n", bookCount);
    ReturnToMain();
}

// Function to search book by title
void searchBookByTitle()
{
    char keyword[50], normalizedKeyword[50];
    int found = 0;
    int searchAgain = 0;

    const char *genres[] = {"Fiction", "Non-Fiction", "Science", "History", "Technology", "Others"};
    int genreCount = sizeof(genres) / sizeof(genres[0]);

    do
    {
        printf("Enter book title to search (partial matching allowed): ");
        scanf(" %[^\n]", keyword);

        strcpy(normalizedKeyword, keyword);
        cap(normalizedKeyword);

        found = 0;

        char filterCategoryChoice;

        printf("\nDo you want to filter by Genre? (y/n): ");
        scanf(" %c", &filterCategoryChoice);
        system("cls");

        char selectedCategory[50] = "";

        if (filterCategoryChoice == 'y' || filterCategoryChoice == 'Y')
        {
            printf("Select a Genre:\n");
            for (int i = 0; i < genreCount; i++)
            {
                printf("%d. %s\n", i + 1, genres[i]);
            }

            int genreChoice;

            do
            {
                printf("Enter your choice (1-%d): ", genreCount);
                scanf("%d", &genreChoice);

                if (genreChoice < 1 || genreChoice > genreCount)
                {
                    printf("Invalid choice. Please select again.\n");
                }
            } while (genreChoice < 1 || genreChoice > genreCount);

            strcpy(selectedCategory, genres[genreChoice - 1]);
        }

        printf("\nMatching Books:\n");

        for (int i = 0; i < bookCount; i++)
        {
            char bookTitle[50];
            strcpy(bookTitle, books[i].title);
            cap(bookTitle);

            if (strstr(bookTitle, normalizedKeyword) != NULL &&
                (strlen(selectedCategory) == 0 || strcmp(books[i].category, selectedCategory) == 0))
            {
                printf("ID: %d | Title: %s | Author: %s | Genre: %s\n",
                       books[i].id, books[i].title, books[i].author, books[i].category);
                found = 1;
            }
        }

        if (!found)
        {
            printf("No matching books found! Do you want to add this book? (y/n): ");
            char choice[10];
            scanf(" %s", choice);
            system("cls");

            if (strcmp(choice, "y") == 0 || strcmp(choice, "Y") == 0 ||
                strcmp(choice, "yes") == 0 || strcmp(choice, "Yes") == 0)
            {
                Book newbook;
                newbook.id = bookCount + 1;

                printf("Enter the book title: ");
                scanf(" %[^\n]", newbook.title);
                cap(newbook.title);

                printf("Enter the author name: ");
                scanf(" %[^\n]", newbook.author);
                cap(newbook.author);

                printf("Select a Genre:\n");
                for (int i = 0; i < genreCount; i++)
                {
                    printf("%d. %s\n", i + 1, genres[i]);
                }

                int genreChoice;

                do
                {
                    printf("Enter your choice (1-%d): ", genreCount);
                    scanf("%d", &genreChoice);

                    if (genreChoice < 1 || genreChoice > genreCount)
                    {
                        printf("Invalid choice. Please select again.\n");
                    }
                } while (genreChoice < 1 || genreChoice > genreCount);

                strcpy(newbook.category, genres[genreChoice - 1]);

                printf("Enter the issued date (dd-mm-yy) or 'N/A': ");
                scanf(" %[^\n]", newbook.issuedDate);

                books[bookCount++] = newbook;
                printf("Book added successfully!\n");
            }
            else
            {
                printf("Search again? (y/n): ");
                char choice2[10];
                scanf(" %s", choice2);
                system("cls");

                if (strcmp(choice2, "y") == 0 || strcmp(choice2, "Y") == 0 ||
                    strcmp(choice2, "yes") == 0 || strcmp(choice2, "Yes") == 0)
                {
                    searchAgain = 1;
                }
                else
                {
                    printf("Search ended.\n");
                    searchAgain = 0;
                }
            }
        }
        else
        {
            printf("\nWould you like to search again? (y/n): ");
            char choice[10];
            scanf(" %s", choice);
            system("cls");

            if (strcmp(choice, "y") == 0 || strcmp(choice, "Y") == 0 ||
                strcmp(choice, "yes") == 0 || strcmp(choice, "Yes") == 0)
            {
                searchAgain = 1;
            }
            else
            {
                printf("Search ended.\n");
                searchAgain = 0;
            }
        }

    } while (searchAgain);

    ReturnToMain();
}

// Function to add a user
void addUser()
{
    if (userCount >= MAX_USERS)
    {
        printf("User list is full!!!...\n");
        ReturnToMain();
        return;
    }

    User newUser;

    newUser.id = userCount + 1;

    printf("Enter user name: ");
    scanf(" %[^\n]", newUser.name);
    cap(newUser.name);

    printf("Enter the title of the book issued: ");
    scanf(" %[^\n]", newUser.issuedBookTitle);
    cap(newUser.issuedBookTitle);

    printf("Enter the author of the book issued: ");
    scanf(" %[^\n]", newUser.issuedBookAuthor);
    cap(newUser.issuedBookAuthor);

    printf("Select the Genre of the book issued:\n");
    printf("1. Fiction\n");
    printf("2. Science\n");
    printf("3. Technology\n");
    printf("4. History\n");
    printf("5. Literature\n");
    printf("6. Other\n");

    int genreChoice;

    const char *genres[] = {"Fiction", "Science", "Technology", "History", "Literature", "Other"};
    printf("Enter the number corresponding to the Genre: ");
    scanf("%d", &genreChoice);

    if (genreChoice >= 1 && genreChoice <= 6)
    {
        strcpy(newUser.category, genres[genreChoice - 1]);
    }
    else
    {
        strcpy(newUser.category, "Other");
        printf("Invalid choice. Defaulting to 'Other'.\n");
    }

    printf("Enter the issued date of the book (dd-mm-yy): ");
    scanf(" %[^\n]", newUser.issuedBookDate);

    users[userCount++] = newUser;
    printf("User added successfully!!!...\n");

    saveUsers();

    ReturnToMain();
}

// Function to delete a user
void deleteUser()
{
    int id, found = 0;
    char confirm[3];
    int attempt = 0;

    printf("Enter the User ID to delete: ");

    while (scanf("%d", &id) != 1)
    {
        printf("Invalid input. Please enter a valid User ID (numeric only): ");

        while (getchar() != '\n')
            ;
    }

    for (int i = 0; i < userCount; i++)
    {
        if (users[i].id == id)
        {
            found = 1;
            printf("User found: ID = %d, Name = %s\n", users[i].id, users[i].name);
            printf("Are you sure you want to delete this user? This action cannot be undone. (y/n)\n");

            while (1)
            {
                getchar();
                scanf("%s", confirm);

                if (strcmp(confirm, "y") == 0 || strcmp(confirm, "Y") == 0 || strcmp(confirm, "yes") == 0 || strcmp(confirm, "Yes") == 0)
                {
                    for (int j = i; j < userCount - 1; j++)
                    {
                        users[j] = users[j + 1];
                    }
                    userCount--;
                    printf("\nUser with ID %d has been deleted successfully.\n", id);
                    saveUsers();
                    break;
                }
                else if (strcmp(confirm, "n") == 0 || strcmp(confirm, "N") == 0 || strcmp(confirm, "no") == 0 || strcmp(confirm, "No") == 0)
                {
                    printf("\nUser deletion has been canceled. User with ID %d remains in the system.\n", id+1);
                    break;
                }
                else
                {
                    attempt++;

                    if (attempt >= 3)
                    {
                        printf("Too many invalid attempts. Returning to the main menu...\n");
                        break;
                    }
                    printf("Invalid input. Please enter 'y' or 'n' to confirm (or 'yes'/'no'):\n");
                }
            }
            break;
        }
    }

    if (!found)
    {
        printf("Error: User with ID %d not found in the system.\n", id);
        printf("Please verify the User ID and try again.\n");
    }

    ReturnToMain();
}

// Function to list all users
void listUsers()
{
    if (userCount == 0)
    {
        printf("\nNo users found.\n");
        ReturnToMain();
        return;
    }

    int choice;
    int filtered = 0;
    char filterCategory[50];
    char filterName[50];

    printf("\n--- List of Users ---\n");

    printf("Would you like to filter or sort the users?\n");
    printf("1. Sort by Name\n");
    printf("2. Sort by Book Title\n");
    printf("3. Filter by Book Genre\n");
    printf("4. Filter by User Name\n");
    printf("5. Show all users (no filter/sort)\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            for (int i = 0; i < userCount - 1; i++)
            {
                for (int j = i + 1; j < userCount; j++)
                {
                    if (strcmp(users[i].name, users[j].name) > 0)
                    {
                        User temp = users[i];
                        users[i] = users[j];
                        users[j] = temp;
                    }
                }
            }
            printf("Users sorted by Name.\n");
            break;

        case 2:
            for (int i = 0; i < userCount - 1; i++)
            {
                for (int j = i + 1; j < userCount; j++)
                {
                    if (strcmp(users[i].issuedBookTitle, users[j].issuedBookTitle) > 0)
                    {
                        User temp = users[i];
                        users[i] = users[j];
                        users[j] = temp;
                    }
                }
            }
            printf("Users sorted by Book Title.\n");
            break;

        case 3:
            printf("Select Genre to filter by:\n");
            printf("1. Fiction\n");
            printf("2. Science\n");
            printf("3. Technology\n");
            printf("4. History\n");
            printf("5. Literature\n");
            printf("6. Other\n");
            printf("Enter your choice (1-6): ");
            int genreChoice;
            scanf("%d", &genreChoice);

            switch (genreChoice)
            {
                case 1:
                    strcpy(filterCategory, "Fiction");
                    break;
                case 2:
                    strcpy(filterCategory, "Science");
                    break;
                case 3:
                    strcpy(filterCategory, "Technology");
                    break;
                case 4:
                    strcpy(filterCategory, "History");
                    break;
                case 5:
                    strcpy(filterCategory, "Literature");
                    break;
                case 6:
                    strcpy(filterCategory, "Other");
                    break;
                default:
                    printf("Invalid choice. No filter applied.\n");
                    filterCategory[0] = '\0'; 
                    break;
            }

            if (filterCategory[0] != '\0')
            {
                printf("\nFiltered by Genre: %s\n", filterCategory);
                filtered = 1;
            }
            break;

        case 4:
            printf("Enter user name to filter by: ");
            getchar();
            fgets(filterName, sizeof(filterName), stdin);
            filterName[strcspn(filterName, "\n")] = 0;

            printf("\nFiltered by Name: %s\n", filterName);
            filtered = 1;
            break;

        case 5:
            printf("\nDisplaying all available users without any filtering or sorting.\n");

            for (int i = 0; i < userCount - 1; i++)
            {
                for (int j = i + 1; j < userCount; j++)
                {
                    if (users[i].id > users[j].id)
                    {
                        User temp = users[i];
                        users[i] = users[j];
                        users[j] = temp;
                    }
                }
            }
            break;

        default:
            printf("\nInvalid choice. Showing all users without filtering or sorting.\n");
            break;
    }

    printf("\n--- Users ---\n");
    printf("%-5s | %-20s | %-20s | %-20s | %-15s | %-15s\n",
           "ID", "Name", "Book Title", "Book Author", "Genre", "Issue Date");
    printf("---------------------------------------------------------------------------------------------\n");

    int displayed = 0;
    for (int i = 0; i < userCount; i++)
    {
        if (filtered)
        {
            if (strcmp(users[i].category, filterCategory) == 0 || strcmp(users[i].name, filterName) == 0)
            {
                printf("%-5d | %-20s | %-20s | %-20s | %-15s | %-15s\n",
                       users[i].id, users[i].name, users[i].issuedBookTitle,
                       users[i].issuedBookAuthor, users[i].category, users[i].issuedBookDate);
                displayed++;
            }
        }
        else
        {
            printf("%-5d | %-20s | %-20s | %-20s | %-15s | %-15s\n",
                   users[i].id, users[i].name, users[i].issuedBookTitle,
                   users[i].issuedBookAuthor, users[i].category, users[i].issuedBookDate);
            displayed++;
        }
    }

    if (displayed == 0)
    {
        printf("\nNo users match your filter criteria.\n");
    }

    printf("\nTotal number of users: %d\n", userCount);
    ReturnToMain();
}

// Function to search user by name
void searchUserByName()
{
    char name[50], normalizedInput[50];

    int found;

    do
    {
        found = 0;

        printf("Enter user name to search (partial name is allowed): ");
        scanf(" %[^\n]", name);

        strcpy(normalizedInput, name);
        cap(normalizedInput);

        printf("\n--- Search Results ---\n");

        for (int i = 0; i < userCount; i++)
        {
            char userName[50];
            strcpy(userName, users[i].name);
            cap(userName);
            if (strstr(userName, normalizedInput) != NULL)
            {
                printf("ID: %d | Name: %s | Book Title: %s | Book Author: %s | Genre: %s\n",
                       users[i].id, users[i].name, users[i].issuedBookTitle, users[i].issuedBookAuthor, users[i].category);
                found = 1;
            }
        }

        if (!found)
        {
            printf("No users found matching the name '%s'.\n", name);
            printf("Do you want to add this user? (y/n): ");
            char choice[10];
            scanf(" %s", choice);

            if (strcmp(choice, "y") == 0 || strcmp(choice, "Y") == 0 ||
                strcmp(choice, "yes") == 0 || strcmp(choice, "Yes") == 0)
            {
                if (userCount >= MAX_USERS)
                {
                    printf("User list is full! Cannot add more users.\n");
                }
                else
                {
                    User newUser;
                    newUser.id = userCount + 1;

                    strcpy(newUser.name, name);
                    cap(newUser.name);

                    printf("Enter the title of the book issued: ");
                    scanf(" %[^\n]", newUser.issuedBookTitle);
                    cap(newUser.issuedBookTitle);

                    printf("Enter the author of the book issued: ");
                    scanf(" %[^\n]", newUser.issuedBookAuthor);
                    cap(newUser.issuedBookAuthor);

                    printf("Select the genre of the book issued:\n");
                    printf("1. Fiction\n");
                    printf("2. Science\n");
                    printf("3. Technology\n");
                    printf("4. History\n");
                    printf("5. Literature\n");
                    printf("6. Other\n");

                    int genreChoice;

                    const char *genres[] = {"Fiction", "Science", "Technology", "History", "Literature", "Other"};
                    printf("Enter the number corresponding to the Genre: ");
                    scanf("%d", &genreChoice);

                    if (genreChoice >= 1 && genreChoice <= 6)
                    {
                        strcpy(newUser.category, genres[genreChoice - 1]);
                    }
                    else
                    {
                        strcpy(newUser.category, "Other");
                        printf("Invalid choice. Defaulting to 'Other'.\n");
                    }

                    users[userCount++] = newUser;
                    printf("User added successfully!\n");
                }
            }
        }

        if (!found)
        {
            printf("Do you want to search again? (y/n): ");
            char searchAgain[10];
            scanf(" %s", searchAgain);
            system("cls");

            if (!(strcmp(searchAgain, "y") == 0 || strcmp(searchAgain, "Y") == 0 ||
                  strcmp(searchAgain, "yes") == 0 || strcmp(searchAgain, "Yes") == 0))
            {
                printf("Search Ended.\n");
                break;
            }
        }

    } while (!found);

    ReturnToMain();
}

// Fuction to make user input case insensitive
void cap(char CAP[])
{
    int i = 0;
    do
    {
        if (CAP[i] >= 'A' && CAP[i] <= 'Z')
        {
            CAP[i] = CAP[i] - 'A' + 'a';
        }
        i++;
    } while (CAP[i] != '\0');
};
