C++ Banking System


A secure and menu-driven Banking System implemented in C++17.
This project showcases Object-Oriented Programming (OOP), secure authentication with hashing, and persistent storage using the filesystem — simulating the core features of real-world banking software.

✨ Features

🔐 Secure Authentication – user passwords hashed with std::hash (no plain-text storage).

📂 Persistent Account Storage – each account saved as a .txt file using std::filesystem.

👤 Account Management – open accounts with unique account numbers, validated mobile numbers, and emails.

💰 Banking Operations – deposit, withdraw, check balance, and view account details.

⚡ Robust Error Handling – validation for invalid inputs and insufficient funds.

🖥 Menu-Driven Interface – intuitive CLI navigation.

🛠 Tech Stack

Language: C++17

Paradigm: Object-Oriented Programming (OOP)

Libraries Used:

<iostream> – I/O handling

<fstream> – file operations

<filesystem> – persistent account storage

<algorithm> – data validation

<functional> – hashing for password security

📂 Project Structure
cpp-banking-system/
├── users/                 # Auto-created folder storing account data
├── main.cpp               # Main source code
└── README.md              # Project documentation


Each account file:

account_number
name
address
mobile
email
hashed_password
balance

▶️ Getting Started
🔧 Prerequisites

C++17 compatible compiler (e.g., g++, clang++, or MSVC).

A terminal/console environment.

⚙️ Installation & Run

Clone the repository:

git clone https://github.com/mohamedghareeb9/cpp-banking-system.git
cd cpp-banking-system


Compile the program:

g++ -std=c++17 main.cpp -o banking


Run the executable:

./banking

📌 Example Menu
WELCOME TO SECTION CAIRO BANK

1. Open New Account
2. Check Account Info
3. Withdraw Amount
4. Deposit Amount
5. Check Balance Info
6. Exit

🎯 Learning Outcomes

This project demonstrates:

Applying OOP principles in C++

Using file systems for persistent storage

Implementing basic security practices (hashed passwords)

Writing robust input validation and error handling

Building scalable, multi-user applications

🤝 Contributing

Contributions are welcome! Please open an issue or submit a pull request with proposed improvements.

📜 License

This project is licensed under the Apache License 2.0.
You are free to use, modify, and distribute this project with attribution.


