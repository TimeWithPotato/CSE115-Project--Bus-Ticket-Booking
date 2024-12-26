# Online Ticket Booking System

## **Overview**

This project is a C-based console application for an online ticket booking system. 
It supports functionalities such as inserting, displaying, searching, updating, appending, and canceling tickets. Users can register, log in, and manage their bookings easily.

---

## **Features**

-  **User Authentication**
    - New users can register and create accounts.
    - Existing users can log in securely with passwords.
      
- **Ticket Management**
    - **Insert** new ticket reservations.
    -  **Display** all ticket details.
    -  **Search** tickets by ID.
    -  **Cancel** tickets.
    -  **Update** ticket details.
    -  **Append** new tickets without overwriting existing data.

---


## **Usage**

1. **Login or Create Account**  
   - Run the program and select either Login or Create Account.  

2. **Choose Operations**  
   - Insert a ticket.  
   - View all ticket details.  
   - Search for a specific ticket using ID.  
   - Cancel or update ticket information.  
   - Append new data without overwriting previous records.  

3. **Exit**  
   - Safely exit the program when done.  

---

# Prerequisite

   - **C Compiler: Ensure a GCC compiler (e.g., Code::Blocks, Dev-C++, or Visual Studio Code with C extension).**

   - **Text Editor/IDE: Use any IDE or text editor that supports C programming.**

---

# Setup Instructions

  
1. **Clone the Repository:**
   ```bash
   git clone <repository-url>
   cd CSE115-Project--Bus-Ticket-Booking

 2. **Compile the Program:**
    ```bash
    gcc main.c -o main

3. **Run the Program**
   ```bash
   main.exe
   
4. **Follow the Menu:**

   - Enter 1 to log in if you already have an account.

   - Enter 2 to create a new account if not registered.

---

# Input Example

  ```cpp
  Enter your name: John
  Enter your password: 12345
  
  1. INSERT
  2. DISPLAY
  3. SEARCH
  4. CANCEL
  5. UPDATE
  6. APPEND
  7. EXIT
 ```
# Output Example

    ```cpp
     ID : 1001
     Name : John Doe
     Origin : Dhaka
     Destination : Sylhet
     Journey Date : 2024-12-30
     Departure Time : 9:00
    ```
---

# Contributions

  - **Developer:**
      - Mohammed Arif Mainuddin
      - Rafat Jahan
      - Mst.Magferat Khatun

  - **Instructor:** Tns1 Faculty, CSE115, North South University (NSU)
