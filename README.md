# ShelfMaster - Library Management System

**ShelfMaster** is a simple and efficient Library Management System designed to manage books and users. This system includes features for adding, deleting, searching, and listing books and users. It also includes secure password handling and customizable settings to ensure smooth library operations.

## Features

- **Password Management**  
  Secure password input and change functionality for system administrators.

- **Book Management**  
  - Add a new book to the library.
  - Delete a book from the library.
  - List all books in the library.
  - Search for a book by its title.

- **User Management**  
  - Add a new user to the system.
  - Delete a user from the system.
  - List all registered users.
  - Search for a user by their name.

- **Main Menu Navigation**  
  - Easy-to-use main menu for accessing different sections of the system.
  - Option to return to the main menu from any section.

## Functions

### `void Password()`
Handles secure password input and validation.

### `void securePasswordInput()`
Secures the password input process for administrative access.

### `void Menu()`
Displays the main menu and handles user navigation.

### `void addbook()`
Adds a new book to the library catalog.

### `void deleteBook()`
Deletes an existing book from the library catalog.

### `void listBooks()`
Lists all the books currently available in the library.

### `void searchBookByTitle()`
Searches for a book by its title.

### `void addUser()`
Adds a new user to the library system.

### `void deleteUser()`
Deletes a user from the library system.

### `void listUsers()`
Lists all users registered in the system.

### `void searchUserByName()`
Searches for a user by their name.

### `void ReturnToMain()`
Returns to the main menu from any section.

### `void change_password()`
Allows the admin to change their password.

### `void cap()`
Handles capitalization of input fields or display.

### `void saveBooks()`
Saves the current list of books to a file.

### `void saveUsers()`
Saves the current list of users to a file.

## How to Use

1. **Run the Program**  
   Compile and run the program using your preferred C compiler.

2. **Login**  
   Access the system using the administrator's credentials.

3. **Choose an Option from the Menu**  
   After logging in, select the appropriate option to manage books or users.

4. **Manage Books or Users**  
   Add, delete, search, or list books and users as needed.

5. **Return to Main Menu**  
   Use the return options to navigate back to the main menu.

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/CoderAmbar/shelfmaster.git
