# Proposal for Bus Ticket Reservation System

## Team Members:
- Havish Chowdhry - 23K-0058 <br> 
- Emaan Arshad    - 23I-2560<br> 
- Dania Khan      - 23K-0072 <br> 
### Batch AI-23
## Individual Contribution:
- Emaan Arshad
  - User Interface (main function)
    -  Log-in
    - Sign-up
    -  Logout
    - Displaying Menu
    -  Exiting the program
    
- Dania Khan
  - Routes Function
    - Display Routes
    - Add Routes
    - Update Routes
    - View All Routes
    
- Havish Chowdhry
  - Booking Functions
     - Reserving a Seat
     - Canceling Reservation
     - Viewing All Bookings
  - File I/O Functions (loading/saving data)







## Project Overview:
This project aims to develop a robust and user-friendly Bus Ticket Reservation System in C language. The system caters to both administrators and customers, providing functionalities such as route management, seat reservation, booking cancellation, and occupancy rate calculation. The project utilizes file handling to persist data, ensuring continuity between program runs.

## Data Structures:

- **Routes Struct:**
  - `pickup`: Source location of the route.
  - `destination`: Destination location of the route.
  - `departureTime`: Time of departure.
  - `ticketPrice`: Price of a ticket for the route.

- **Booking Struct:**
  - `busID`: ID of the bus.
  - `seatNumber`: Number of the reserved seat.
  - `customerName`: Name of the customer who reserved the seat.

- **Admin Struct:**
  - `username`: Admin username for authentication.
  - `password`: Admin password for authentication.

- **Arrays:**
  - seats[][]: 2D array to represent the occupancy status of seats in each bus.
  - Arrays for storing route details, booking information, and admin credentials

- **File Pointers:**
  - Used for reading and writing data to files for persistence.

## Functionalities:

### Admin Functions:

1. **Admin Login:**
   - Authenticate admin by entering a username and password.
   - Restrict access to admin functionalities only after successful authentication.

2. **Admin Signup:**
   - Allow a new admin to sign up by entering a username and password.
   - Persist admin credentials in the file for future logins.

3. **View Bus Routes:**
   - Display a list of all available bus routes with details such as pickup, destination, departure time, and ticket price.

4. **Add Route:**
   - Add a new bus route by providing pickup location, destination, departure time, and ticket price.
   - Limit the number of routes to avoid exceeding system capacity.

5. **Update Route:**
   - Modify the details of an existing route (e.g., change departure time or ticket price).
   - Ensure that only authenticated admins can perform route updates.

6. **Reserve a Seat:**
   - Reserve one or more seats on a specific bus by providing the bus ID, the number of seats, and customer names.
   - Update the occupancy status of the reserved seats.

7. **Cancel Reservation:**
   - Cancel a reservation by providing the bus ID and seat number.
   - Free up the reserved seats and update the booking records.

8. **View All Bookings:**
   - Display a list of all seat reservations with booking ID, bus ID, seat number, and customer name.
   - Provide admins with an overview of all current bookings.

9. **Logout:**
   - Log out the currently authenticated admin.
   - Restrict access to admin functionalities after logout until reauthentication.

10. **Exit:**
    - Save data to files and exit the program.
    - Ensure that data continuity is maintained across program runs.


## Major Challenges Faced:

1. **Error Handling and Exception Handling:**
   - Implementation of robust error handling and handling different scenarios posed a significant challenge.
   - The team encountered difficulties in tracking and managing errors in various situations.

2. **Situational Complexity:**
   - Dealing with the complexity of different situations, such as insufficient account balances for reservations, presented a hurdle.
   - The team found it challenging to implement error tracking in these diverse scenarios.

## Logical Structure:

- **Modular Code:**
  - The code is divided into structured modules for readability and maintainability.
  - User-defined functions handle specific functionalities, promoting code reusability.

- **Menu-Driven Interface:**
  - The program utilizes a menu-driven interface for user interaction.
  - Users, both administrators and customers, can navigate through various options to perform desired actions.

- **Error Messages:**
  - Informative error messages are displayed in case of invalid inputs or system errors.

- **Data Persistence:**
  - Data related to routes, bookings, and admins are persistently stored in files, ensuring data continuity across program executions.

## Future Enhancements:

- **Security Measures:**
  - Implement additional security measures such as encryption for admin credentials.
  - Enhance error tracking mechanisms to improve system security.

- **Graphical User Interface (GUI):**
  - Consider incorporating a graphical user interface for a more intuitive user experience.

- **Online Reservation System:**
  - Extend the system to support online reservations and payments.

- **Enhanced Error Reporting:**
  - Implement a comprehensive error tracking system to handle a variety of scenarios and provide detailed error reports.

## Conclusion:

This Bus Ticket Reservation System project successfully addresses the requirements of both administrators and customers, providing a scalable foundation for future enhancements. The team acknowledges the challenges faced in error handling and situational complexity and is committed to improving these aspects for a more resilient and user-friendly system. The project demonstrates the team's dedication to overcoming obstacles and continuous learning in the development process.

