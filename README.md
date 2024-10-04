# Train Ticketing System

This project is an assignment for the **AAC1084 Programming Concepts and Design II** course. The goal is to create a console-based train ticketing system using the C language, following principles of good program design, modularization, structures and file handling.

**Date submitted:** 5th May 2024

## Features

- 👮 **Staff Management**
    - Login system for existing staff members.
    - Create, Read, Update and Delete (CRUD) staff records.
    - Manage staff account details like `Name`, `Gender`, `Age`, `Password` and `Position`.
    - View and delete member accounts.
    - Data stored in: `staff.bin`.
- 👥 **Member Management**
    - Login and Registration for users.
    - View and update account information such as `Name`, `Gender`, `IC Number`, and `Phone Number`.
    - Manage train bookings (purchase, modify, or cancel tickets).
    - Data stored in: `users.bin` (user accounts) and `memberTickets.txt` (purchased tickets).
- 🚆 **Train Scheduling**
    - Create, Read, Update and Delete (CRUD) train schedules.
    - Manage train details such as `Departure/Arrival station`, `Departure/Arrival time`, and `Number of Seats`.
    - Search functionality based on `Train ID`.
    - Data stored in: `schedules.txt`.
    - Used by: Staff
- 🎫 **Ticket Booking**
    - Create, Read, Update and Delete (CRUD) train tickets.
    - Manage ticket details like `Destination`, `Train ID`, `Departure date`, `Departure time`, and `Price`.
    - Book tickets by selecting a time slot and entering a coach and seat number.
    - Supports viewing booking history, cancellation and modification of booked tickets.
    - Data stored in: `tickets.txt`.
    - Used by: Members (booking and managing tickets) and Staff (overseeing ticket data).

## Default Admin Credentials

- **Username:** `Admin`
- **Password:** `S00Admin`

## Authors

- Member Information Module - [@Zhxua](https://www.github.com/Zhxua)
- Staff Information Module - [@YapSJin](https://www.github.com/YapSJin)
- Train Scheduling Module - [@stlee15](https://www.github.com/stlee15)
- Ticket Booking Module - [@zhon12345](https://www.github.com/zhon12345)


## Run Locally

Clone the project

```bash
  git clone https://github.com/zhon12345/train-ticketing-system.git
```

Go to the project directory

```bash
  cd train-ticketing-system
```

Compile `main.c`

```bash
  gcc -o main main.c
```

Start the program

```bash
  ./main
```
## Appendix

-   **Setting up MinGW-w64 via MSYS2**:

    1. Download and install [MSYS2](https://www.msys2.org/).

    2. Open the MSYS2 terminal and run the following command:

    ```bash
      $ pacman -S mingw-w64-ucrt-x86_64-gcc
    ```

-   **Online compilers or IDEs:**

    -   Online compilers: [Replit](https://replit.com/), [OnlineGDB](https://www.onlinegdb.com/)

    -   IDEs: [Visual Studio](https://visualstudio.microsoft.com/downloads/)