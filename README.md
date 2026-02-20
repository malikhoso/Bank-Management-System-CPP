# Bank Management System (C++)

A robust console-based application designed to automate banking operations. This project was developed as part of my **Programming Fundamentals** coursework, focusing on structured programming, file handling, and data persistence.

## 🚀 Key Features

* **Account Operations:** Create, delete, and search for accounts.
* **Transactions:** Deposit, withdraw, and transfer funds between accounts with real-time balance validation.
* **Loan Management:** Apply for loans with 10% interest and specific installment plans (12, 24, 36 months).
* **Data Persistence:** Uses `fstream` to save all account details to a text file, ensuring data is kept even after the program closes.
* **Security:** Features a PIN-protected administrative view for sensitive bank data.
* **Auto-ID Generation:** Tracks and assigns unique account numbers automatically.

## 🛠️ Technical Concepts Used

* **Structures (`struct`):** To organize complex data types.
* **File I/O (`fstream`):** For reading and writing data to `accounts.txt`.
* **Pointers & Memory:** Manual memory management using `new` and `delete`.
* **Input Parsing:** Using `istringstream` and `ws` for clean data loading from files.
* **Validation:** Logic to handle insufficient funds and invalid account inputs.

## 📂 Project Structure

* `main.cpp` - The core logic and menu-driven interface.
* `accounts.txt` - The storage file for account records.
* `nextAccountNumber.txt` - Stores the next ID to be assigned.

## 💻 How to Run

1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/malikhoso/Bank-Management-System-CPP.git](https://github.com/malikhoso/Bank-Management-System-CPP.git)
    ```
2.  **Compile:**
    ```bash
    g++ main.cpp -o BankSystem
    ```
3.  **Execute:**
    ```bash
    ./BankSystem
    ```

---
**Note:** The default admin password to display all bank data is `4507`.
