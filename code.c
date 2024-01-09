/*
Programmer: Havish Chowdhry, Emaan Arshad, Dania Khan
Date: 21/12//2023 

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define totalSeats 50
#define totalBuses 10
#define totalRoutes 50
#define totalAdmins 3
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_GRAY "\x1b[90m"

typedef struct {
    char pickup[50];
    char destination[50];
    char departureTime[10];
    float ticketPrice;
} Routes;

typedef struct {
    int busID;
    int seatNumber;
    char customerName[50];
} Booking;

typedef struct {
    char username[20];
    char password[20];
} Admin;
void saveRouteToFile(const Routes *route);
void displayRoutes(Routes routes[], int numRoutes);
void saveAdminsToFile(const Admin admins[], int numAdmins);
void saveBookingsToFile(const Booking bookings[], int numBookings);
void saveRoutesToFile(const Routes routes[], int numRoutes);
void viewAllBookings(Booking bookings[], int *numBookings);
void cancelReservation(int seats[][50], int numBuses, Booking bookings[], int *numBookings);
void updateRoute(Routes routes[], int numRoutes);
void displayRoutes(Routes routes[], int numRoutes);


int main() {
    // DECLARATION OF ARRAYS OF STRUCT TYPES
    Routes routes[totalRoutes];
    Booking bookings[totalSeats];
    Admin admins[totalAdmins];

    // OTHER NECESSARY VARIABLE AND ARRAY DECLARATIONS
    int seats[totalBuses][totalSeats];
    int numRoutes = 0;
    int numBookings = 0;
    int numAdmins = 0;
    int choice;
    int isAdminAuthenticated = 0;
    Admin currentAdmin;

    // Load data from files at the beginning of the program
    numRoutes = loadRoutesFromFile(routes, totalRoutes);
    numBookings = loadBookingsFromFile(bookings, totalSeats);
    numAdmins = loadAdminsFromFile(admins, totalAdmins);

    // Admin authentication loop
    do {
        system("cls");
        printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------\n"ANSI_COLOR_RESET);
       printf(ANSI_COLOR_GRAY "\t\t\t\t         _______________________________\n" ANSI_COLOR_RESET);

		printf(ANSI_COLOR_GRAY"\t\t\t\t  <-----| "  ANSI_COLOR_CYAN "Bus Ticket Reservation System"  ANSI_COLOR_GRAY" |----->\n" ANSI_COLOR_RESET);


        printf(ANSI_COLOR_CYAN"\n------------------------------------------------------------------------------------------------------------------------\n"ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GRAY"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"ANSI_COLOR_RESET );
        printf("==> You have the following choices:\n\n");
        printf("   1) Press '0' if you want to exit the program.\n   -------------------------------------\n");
        printf("   2) Press '1' if you want to log in as an Admin.\n   -------------------------------------\n");
        printf("   3) Press '2' if you want to sign up as an Admin.\n");
        printf(ANSI_COLOR_GRAY"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"ANSI_COLOR_RESET );

        printf("==> Enter your choice: ");
        scanf("%d", &choice);
        system("cls");
         printf(ANSI_COLOR_GRAY"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"ANSI_COLOR_RESET );

        switch (choice) {
            case 0:
                // Exit the program
                printf("\n      ***Data Saved To The Files***\n  ***Now The program Will Be Exited***\n");
                printf(ANSI_COLOR_GRAY"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"ANSI_COLOR_RESET );
                break;

            case 1:
                // Log in as an Admin
                isAdminAuthenticated = authenticateAdmin(admins, numAdmins, &currentAdmin);
                if (!isAdminAuthenticated) {
                    printf("***Authentication Failed Access Denied***\n");
                    sleep(2);
                } else {
                    printf("\n   ***Authentication Successful***\n      -------------------------\n\t***Welcome, %s***\n", currentAdmin.username);
                   printf(ANSI_COLOR_GRAY"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"ANSI_COLOR_RESET );
                    sleep(2);
                }
                break;

            case 2:
                // Sign up as an Admin
                numAdmins = signupAdmin(admins, &numAdmins);
                printf("\n***Admin Signup Successful***\n");
                sleep(2);
                break;

            default:
                printf("\n***Invalid Choice. Please Enter A Valid Option.\n");
                sleep(2);
        }

    } while (choice != 0 && !isAdminAuthenticated);

    // Menu choices loop (accessible only after successful authentication)
    while (isAdminAuthenticated) {
        system("cls");
 printf(ANSI_COLOR_CYAN "------------------------------------------------------------------------------------------------------------------------\n"ANSI_COLOR_RESET);
       printf(ANSI_COLOR_GRAY "\t\t\t\t         _______________________________\n" ANSI_COLOR_RESET);

		printf(ANSI_COLOR_GRAY"\t\t\t\t  <-----| "  ANSI_COLOR_CYAN"Bus Ticket Reservation System"  ANSI_COLOR_GRAY" |----->\n" ANSI_COLOR_RESET);


        printf(ANSI_COLOR_CYAN"\n------------------------------------------------------------------------------------------------------------------------\n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GRAY"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"ANSI_COLOR_RESET );
        printf("==> You have the following choices:\n\n");
        printf("   1) Press '0' if you want to exit the program.\n   -------------------------------------\n");
        printf("   3) Press '3' if you want to view bus routes.\n   -------------------------------------\n");
        printf("   4) Press '4' if you want to add a route.\n   -------------------------------------\n");
        printf("   5) Press '5' if you want to update a route.\n   -------------------------------------\n");
        printf("   6) Press '6' if you want to reserve a seat.\n   -------------------------------------\n");
        printf("   7) Press '7' if you want to cancel a reservation.\n   -------------------------------------\n");
        printf("   8) Press '8' if you want to view all bookings.\n   -------------------------------------\n");
        printf("   9) Press '9' if you want to log out of the system.\n");
printf(ANSI_COLOR_GRAY"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"ANSI_COLOR_RESET );

        printf("==> Enter your choice: ");
        scanf("%d", &choice);
        system("cls");
printf(ANSI_COLOR_GRAY"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"ANSI_COLOR_RESET );

        switch (choice) {
            case 0:
                // Save data to files before exiting
                saveAdminsToFile(admins, numAdmins);
                saveRoutesToFile(routes, numRoutes);
                saveBookingsToFile(bookings, numBookings);
                printf("\n      ***Data Saved To The Files***\n  ***Now The program Will Be Exited***\n");
printf(ANSI_COLOR_GRAY"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"ANSI_COLOR_RESET );
                break;

            case 3:
                // View bus routes
                displayRoutes(routes, numRoutes);
                sleep(5);
                break;

            case 4:
                // Add a route
                numRoutes = addRoute(routes, numRoutes);
                printf("\n==> Updated Routes");
                displayRoutes(routes, numRoutes);
                printf("\n==> The program will now ask you to choose an option again.\n");
                sleep(4);
                break;

            case 5:
                // Update a route
                updateRoute(routes, numRoutes);
                printf("\n==> Updated Routes");
                displayRoutes(routes, numRoutes);
                printf("\n==> The program will now ask you to choose an option again.\n");
                sleep(4);
                break;

            case 6:
                // Reserve a seat
                displayRoutes_bus(routes,numRoutes);
                reserveSeat(seats, totalBuses, bookings, &numBookings);
                printf("\n==> The program will now ask you to choose an option again.\n");
                printf("\n==> Updated Bookings");
                viewAllBookings(bookings, &numBookings);
                sleep(4);
                break;

            case 7:
                // Cancel a reservation
                cancelReservation(seats, totalBuses, bookings, &numBookings);
                printf("\n==> The program will now ask you to choose an option again.\n");
                printf("\n==> Updated Bookings");
                viewAllBookings(bookings, &numBookings);
                sleep(4);
                break;

            case 8:
                // View all bookings
                viewAllBookings(bookings, &numBookings);
                printf("\n==> The program will now ask you to choose an option again.\n");
                sleep(5);
                break;

            case 9:
                // Log out
                isAdminAuthenticated = 0;
                printf("\t***Logout Successful***\n");
                printf("\n==> The program will now ask you to choose an option again.\n");
                sleep(2);
                break;

            default:
                printf("\n***Invalid Choice. Please Enter A Valid Option.\n");
                printf("==> The program will now ask you to choose an option again.");
printf(ANSI_COLOR_GRAY"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"ANSI_COLOR_RESET );
                sleep(5);
                system("cls");
        }
    } while (choice != 0 && isAdminAuthenticated);

    return 0;
}


void initializeRoutes(Routes routes[], int numRoutes)
{
    int index;
    for (index = 0; index < numRoutes; index++)
    {
        strcpy(routes[index].pickup, "");
        strcpy(routes[index].destination, "");
        strcpy(routes[index].departureTime, "");
        routes[index].ticketPrice = 0.0;
    }

    saveRoutesToFile(routes, numRoutes);
}


int addRoute(Routes routes[], int numRoutes)
{
    if (numRoutes < totalRoutes)
    {
        printf("==> Enter the pickup location: ");
        scanf("%s", routes[numRoutes].pickup);

        printf("==> Enter the destination location: ");
        scanf("%s", routes[numRoutes].destination);

        printf("==> Enter the departure time: ");
        scanf("%s", routes[numRoutes].departureTime);

        printf("==> Enter the ticket price: ");
        scanf("%f", &routes[numRoutes].ticketPrice);

        
        saveRouteToFile(&routes[numRoutes]);

        printf("\n	**Route Added Successfully**\n");
        printf("==> The program will now ask you to choose an option again.");
        printf("\n\n*--------------------\n");
        sleep(5);
        system("cls");

        return numRoutes + 1; 
    }
    else
    {
        printf("**Maximum Routes Reached. Cannot Add More Routes**\n");
        return numRoutes;
    }
}


void saveRouteToFile(const Routes *route)
{
    FILE *file = fopen("route.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for appending\n");
        return;
    }

    fprintf(file, "%s %s %s %.2f\n", route->pickup, route->destination,
            route->departureTime, route->ticketPrice);

    fclose(file);
}


void displayRoutes_bus(Routes routes[], int numRoutes)
{
    printf("Num Routes: %d",numRoutes);
    int index;
    printf("\n\t\t\t|* Bus Routes *|\n");
    printf("			--------------------\n\n");
    printf("|Bus|\t|Pickup|\t|Destination|\t|Departure Time| |Ticket Price|\n");
    printf("-----------------------------------------------------------------------\n");

    
    for (index = 0; index < numRoutes; index++)
    {
        printf("%d\t%.7s\t\t%.7s\t\t%.4s\t\t %.2f\n", index+1 , routes[index].pickup, routes[index].destination,
               routes[index].departureTime, routes[index].ticketPrice);
    }

    FILE *file = fopen("route.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading\n");
        return;
    }

    Routes fileRoute;
    while (fscanf(file, "%s %s %s %f\n", fileRoute.pickup, fileRoute.destination,
                  fileRoute.departureTime, &fileRoute.ticketPrice) == 4)
    {
        
        int foundInMemory = 0;
        for (index = 0; index < numRoutes; index++)
        {
            if (strcmp(routes[index].pickup, fileRoute.pickup) == 0 &&
                strcmp(routes[index].destination, fileRoute.destination) == 0)
            {
                foundInMemory = 1;
                break;
            }
        }

        if (!foundInMemory)
        {
         
            printf("%s\t%s\t%s\t%.2f\n", fileRoute.pickup, fileRoute.destination,
                   fileRoute.departureTime, fileRoute.ticketPrice);
        }
    }
    

    fclose(file);
}



void displayRoutes(Routes routes[], int numRoutes)
{
    printf("Num Routes: %d",numRoutes);
    int index;
    printf("\n\t\t\t|* Bus Routes *|\n");
    printf("			--------------------\n\n");
    printf("|Pickup|\t|Destination|\t|Departure Time| |Ticket Price|\n");
    printf("-----------------------------------------------------------------------\n");

    
    for (index = 0; index < numRoutes; index++)
    {
        printf("%.7s\t\t%.7s\t\t%.4s\t\t %.2f\n", routes[index].pickup, routes[index].destination,
               routes[index].departureTime, routes[index].ticketPrice);
    }

    FILE *file = fopen("route.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading\n");
        return;
    }

    Routes fileRoute;
    while (fscanf(file, "%s %s %s %f\n", fileRoute.pickup, fileRoute.destination,
                  fileRoute.departureTime, &fileRoute.ticketPrice) == 4)
    {
        
        int foundInMemory = 0;
        for (index = 0; index < numRoutes; index++)
        {
            if (strcmp(routes[index].pickup, fileRoute.pickup) == 0 &&
                strcmp(routes[index].destination, fileRoute.destination) == 0)
            {
                foundInMemory = 1;
                break;
            }
        }

        if (!foundInMemory)
        {
         
            printf("%s\t%s\t%s\t%.2f\n", fileRoute.pickup, fileRoute.destination,
                   fileRoute.departureTime, fileRoute.ticketPrice);
        }
    }
    

    fclose(file);
}


Routes findRoute(Routes routes[], int numRoutes, const char pickup[], const char destination[])
{
    Routes notFoundRoute = {"", "", "", 0.0}; 

    int index;
    for (index = 0; index < numRoutes; index++)
    {
        if (strcmp(routes[index].pickup, pickup) == 0 && strcmp(routes[index].destination, destination) == 0)
        {
            return routes[index];
        }
    }

   
    FILE *file = fopen("route.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading\n");
        return notFoundRoute;
    }

    Routes fileRoute;
    while (fscanf(file, "%s %s %s %f\n", fileRoute.pickup, fileRoute.destination,
                  fileRoute.departureTime, &fileRoute.ticketPrice) == 4)
    {
        if (strcmp(fileRoute.pickup, pickup) == 0 && strcmp(fileRoute.destination, destination) == 0)
        {
            fclose(file);
            return fileRoute;
        }
    }

    fclose(file);
    return notFoundRoute; 
}


void updateRoute(Routes routes[], int numRoutes) {
    char pickup[50], destination[50];

    printf("Enter source of the route to update: ");
    scanf("%s", pickup);

    printf("Enter destination of the route to update: ");
    scanf("%s", destination);

    FILE *file = fopen("route.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    FILE *tempFile = fopen("temp_route.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file for writing.\n");
        fclose(file);
        return;
    }
    int index;
    for (index = 0; index < numRoutes; index++) {
        if (fscanf(file, "%49s %49s %9s %f\n", routes[index].pickup, routes[index].destination,
                   routes[index].departureTime, &routes[index].ticketPrice) != 4) {
            break;  
        }

        if (strcmp(routes[index].pickup, pickup) == 0 &&
            strcmp(routes[index].destination, destination) == 0) {
            // Route found, update it
            printf("Enter new departure time: ");
            scanf("%s", routes[index].departureTime);

            printf("Enter new ticket price: ");
            scanf("%f", &routes[index].ticketPrice);

            printf("Route updated successfully!\n");
        }

        fprintf(tempFile, "%s %s %s %.2f\n", routes[index].pickup, routes[index].destination,
                routes[index].departureTime, routes[index].ticketPrice);
    }

    fclose(file);
    fclose(tempFile);

 
    remove("route.txt");
    rename("temp_route.txt", "route.txt");

    if (index == numRoutes) {
        printf("Route not found. Cannot update.\n");
    }
}




void initializeBookings(Booking bookings[], int numBookings)
{
    
    FILE *file = fopen("booking.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading\n");
        return;
    }

   
    int index;
    for (index = 0; index < numBookings; index++)
    {
        
        if (fscanf(file, "%d %d %s", &bookings[index].busID, &bookings[index].seatNumber,
                   bookings[index].customerName) != 3)
        {
            break; 
        }
    }

    fclose(file);
}


void displayBookings(Booking bookings[], int numBookings)
{
    printf("\n** \t Seat Reservations \t **\n");
    printf("Bus ID\t Seat Number\t Customer Name\n");

    
    FILE *file = fopen("booking.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading\n");
        return;
    }


    while (fscanf(file, "%d %d %s", &bookings[numBookings].busID, &bookings[numBookings].seatNumber,
                  bookings[numBookings].customerName) == 3)
    {
        printf("%d\t%d\t%s\n", bookings[numBookings].busID, bookings[numBookings].seatNumber, bookings[numBookings].customerName);
        numBookings++;
    }

    fclose(file);
}


int reserveSeat(int seats[][totalSeats], int numBuses, Booking bookings[], int *numBookings)
{
    int busID, seatNum, index;

    printf("Enter the bus ID: ");
    scanf("%d", &busID);

    if (busID < 1 || busID > numBuses)
    {
        printf("Invalid bus ID.\n");
        return -1;
    }

    printf("Available seats for Bus %d:\n", busID);
    for (index = 0; index < totalSeats; index++)
    {
        if (seats[busID - 1][index] == 0)
        {
            printf("Seat %d\n", index + 1);
        }
    }

    printf("Enter the number of seats to book: ");
    scanf("%d", &seatNum);

    if (seatNum < 1 || seatNum > totalSeats)
    {
        printf("Invalid number of seats.\n");
        return -1;
    }

    int availableSeats = 0;
    for (index = 0; index < totalSeats; index++)
    {
        if (seats[busID - 1][index] == 0)
        {
            availableSeats++;
        }
    }

    if (seatNum > availableSeats)
    {
        printf("Not enough available seats.\n");
        return -1;
    }

    printf("Enter customer name(s):\n");
    for (index = 0; index < seatNum; index++)
    {
        int seatIndex;
        printf("Enter name for seat %d: ", index + 1);
        scanf("%49s", bookings[*numBookings].customerName);

        for (seatIndex = 0; seatIndex < totalSeats; seatIndex++)
        {
            if (seats[busID - 1][seatIndex] == 0)
            {
                seats[busID - 1][seatIndex] = 1;
                bookings[*numBookings].busID = busID;
                bookings[*numBookings].seatNumber = seatIndex + 1;

                FILE *file = fopen("booking.txt", "a");
                if (file == NULL)
                {
                    printf("Error opening file for appending.\n");
                    return -1;
                }

                fprintf(file, "%d %d %s\n", busID, seatIndex + 1, bookings[*numBookings].customerName);

                fclose(file);

                (*numBookings)++;
                printf("Seat reserved successfully.\n");
                break;
            }
        }
    }

    return 0;
}
void cancelReservation(int seats[][totalSeats], int numBuses, Booking bookings[], int *numBookings)
{
    int seatNumber, busId, index;
    printf("Enter the bus ID: ");
    scanf("%d", &busId);
    
    printf("Enter the seat number to cancel the reservation: ");
    scanf("%d", &seatNumber);

    if (busId < 1 || busId > numBuses || seatNumber < 1 || seatNumber > totalSeats)
    {
        printf("Invalid bus ID or seat number.\n");
        return;
    }

    int bookingIndex = -1;
    for (index = 0; index < *numBookings; index++)
    {
        if (bookings[index].busID == busId && bookings[index].seatNumber == seatNumber)
        {
            bookingIndex = index;
            break;
        }
    }

    if (bookingIndex != -1)
    {
        seats[bookings[bookingIndex].busID - 1][seatNumber - 1] = 0;

        FILE *file = fopen("booking.txt", "r");
        if (file == NULL)
        {
            printf("Error opening file for reading.\n");
            return;
        }

        FILE *tempFile = fopen("temp_booking.txt", "w");
        if (tempFile == NULL)
        {
            printf("Error opening temp file for writing.\n");
            fclose(file);
            return;
        }

        while (fscanf(file, "%d %d %s", &bookings[index].busID, &bookings[index].seatNumber, bookings[index].customerName) == 3)
        {
            if (bookings[index].busID != busId || bookings[index].seatNumber != seatNumber)
            {
                fprintf(tempFile, "%d %d %s\n", bookings[index].busID, bookings[index].seatNumber, bookings[index].customerName);
            }
        }

        fclose(file);
        fclose(tempFile);

        remove("booking.txt");

        rename("temp_booking.txt", "booking.txt");

        (*numBookings)--;
        printf("Reservation canceled successfully!\n");
    }
    else
    {
        printf("No reservation found for bus ID %d and seat %d.\n", busId, seatNumber);
    }
}

void viewAllBookings(Booking bookings[], int *numBookings)
{
 
    FILE *file = fopen("booking.txt", "r");
    if (file == NULL)
    {
        printf("*Error opening file for reading*\n");
        return;
    }

    int index = 0;
    printf("\n\t      |*** All Bookings ***|\n");
    printf(ANSI_COLOR_CYAN"	      ----------------------\n",ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"---------------------------------------------------------------\n"ANSI_COLOR_RESET);
    printf("|Booking ID|\t|Bus ID|\t|Seat Number|\t|Customer Name|\n");
    printf(ANSI_COLOR_CYAN"---------------------------------------------------------------\n"ANSI_COLOR_RESET);
    while (fscanf(file, "%d %d %s", &bookings[index].busID, &bookings[index].seatNumber, bookings[index].customerName) == 3)
    {
        printf(" %d\t\t %d\t\t  %d\t\t %s\n", index + 1, bookings[index].busID, bookings[index].seatNumber, bookings[index].customerName);
        index++;
    }
    printf(ANSI_COLOR_CYAN"---------------------------------------------------------------\n"ANSI_COLOR_RESET);
    *numBookings = index;

    fclose(file);
}


void cancelBookingAdmin(Booking bookings[], int *numBookings)
{
    int bookingID, index;
    printf("==> Enter the booking ID to cancel: ");
    scanf("%d", &bookingID);

    if (bookingID >= 1 && bookingID <= *numBookings)
    {
        FILE *file = fopen("booking.txt", "r");
        if (file == NULL)
        {
            printf("*Error opening file for reading*\n");
            return;
        }

        FILE *tempFile = fopen("temp_booking.txt", "w");
        if (tempFile == NULL)
        {
            printf("*Error opening temporary file for writing*\n");
            fclose(file);
            return;
        }

        int currentBookingID;
        for (index = 0; index < *numBookings; index++)
        {
            fscanf(file, "%d", &currentBookingID);
            if (currentBookingID != bookingID)
            {
                fprintf(tempFile, "%d %d %s\n", bookings[index].busID, bookings[index].seatNumber, bookings[index].customerName);
            }
        }

        fclose(file);
        fclose(tempFile);

        remove("booking.txt");
        if (rename("temp_booking.txt", "booking.txt") != 0)
        {
            printf("*Error renaming file*\n");
        }

        (*numBookings)--;
        printf("==> Booking canceled successfully.\n");
    }
    else
    {
        printf("==> Invalid booking ID. No booking found.\n");
    }
}


void viewOccupancyRate(int seats[][totalSeats], int numBuses)
{
    int index1, index2;
    printf("\n*** Occupancy Rates ***\n");

    FILE *file = fopen("booking.txt", "r");
    if (file == NULL)
    {
        printf("*Error opening file: booking.txt*\n");
        return;
    }

    for (index1 = 0; index1 < numBuses; index1++)
    {
        int reservedSeats = 0;
        for (index2 = 0; index2 < totalSeats; index2++)
        {
            fscanf(file, "%*d %*d %*s"); 
            if (seats[index1][index2] == 1)
            {
                reservedSeats++;
            }
        }

        double occupancyRate = (double)reservedSeats / totalSeats * 100;

        printf("Bus %d, %.2lf%%\n", index1 + 1, occupancyRate);
    }

    fclose(file);
}
int loadRoutesFromFile(Routes routes[], int maxRoutes)
{
    FILE *file = fopen("route.txt", "r");
    if (file == NULL)
    {
        perror("*Error opening route.txt*");
        return 0;
    }

    int numRoutes = 0;
    while (fscanf(file, "%s %s %s %f\n", routes[numRoutes].pickup, routes[numRoutes].destination,
                  routes[numRoutes].departureTime, &routes[numRoutes].ticketPrice) == 4)
    {
        numRoutes++;
        if (numRoutes == maxRoutes)
        {
            break;
        }
    }

    fclose(file);
    return numRoutes;
}

void saveRoutesToFile(const Routes routes[], int numRoutes)
{
    FILE *file = fopen("route.txt", "w");
    if (file == NULL)
    {
        perror("*Error opening route.txt for writing*");
        return;
    }
	int i;
    for (i = 0; i < numRoutes; i++)
    {
        fprintf(file, "%s %s %s %.2f\n", routes[i].pickup, routes[i].destination,
                routes[i].departureTime, routes[i].ticketPrice);
    }

    fclose(file);
}

int loadBookingsFromFile(Booking bookings[], int maxBookings)
{
    FILE *file = fopen("booking.txt", "r");
    if (file == NULL)
    {
        perror("*Error opening booking.txt*");
        return 0;
    }

    int numBookings = 0;
    while (fscanf(file, "%d %d %s\n", &bookings[numBookings].busID, &bookings[numBookings].seatNumber,
                  bookings[numBookings].customerName) == 3)
    {
        numBookings++;
        if (numBookings == maxBookings)
        {
            break;
        }
    }

    fclose(file);
    return numBookings;
}

void saveBookingsToFile(const Booking bookings[], int numBookings)
{
    FILE *file = fopen("booking.txt", "w");
    if (file == NULL)
    {
        perror("*Error opening booking.txt for writing*");
        return;
    }
		int i;
    for ( i = 0; i < numBookings; i++)
    {
        fprintf(file, "%d %d %s\n", bookings[i].busID, bookings[i].seatNumber,
                bookings[i].customerName);
    }

    fclose(file);
}

int loadAdminsFromFile(Admin admins[], int maxAdmins)
{
    FILE *file = fopen("admin.txt", "r");
    if (file == NULL)
    {
        perror("*Error opening admin.txt*");
        return 0;
    }

    int numAdmins = 0;
    while (fscanf(file, "%s %s\n", admins[numAdmins].username, admins[numAdmins].password) == 2)
    {
        numAdmins++;
        if (numAdmins == maxAdmins)
        {
            break;
        }
    }

    fclose(file);
    return numAdmins;
}

void saveAdminsToFile(const Admin admins[], int numAdmins)
{
    FILE *file = fopen("admin.txt", "w");
    if (file == NULL)
    {
        perror("*Error opening admin.txt for writing*");
        return;
    }
	int i;
    for ( i = 0; i < numAdmins; i++)
    {
        fprintf(file, "%s %s\n", admins[i].username, admins[i].password);
    }

    fclose(file);
}
int signupAdmin(Admin admins[], int *numAdmins) {
    Admin newAdmin;

    printf("==> Enter new admin username: ");
    scanf("%19s", newAdmin.username);

    printf("==> Enter new admin password: ");
    scanf("%19s", newAdmin.password);

    admins[*numAdmins] = newAdmin;
    (*numAdmins)++;

    FILE *file = fopen("admin.txt", "a");
    if (file == NULL) {
        printf("*Error opening file for appending*\n");
        return *numAdmins;
    }

    fprintf(file, "%s %s\n", newAdmin.username, newAdmin.password);

    fclose(file);

    printf("==> Admin signup successful!\n");

    return *numAdmins;
}
int authenticateAdmin(Admin admins[], int numAdmins, Admin *currentAdmin) {
    char username[20], password[20];

    printf("==> Enter admin username: ");
    scanf("%19s", username);

    printf("==> Enter admin password: ");
    scanf("%19s", password);
    printf("\n");
    system("cls");
    printf(ANSI_COLOR_GRAY"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"ANSI_COLOR_RESET);

    FILE *file = fopen("admin.txt", "r");
    if (file == NULL) {
        printf("*Error Opening File For Reading*\n");
        return 0;
    }

    int authSuccess = 0; 

    while (fscanf(file, "%s %s", currentAdmin->username, currentAdmin->password) == 2) {
        if (strcmp(currentAdmin->username, username) == 0 && strcmp(currentAdmin->password, password) == 0) {
            authSuccess = 1;
            break;
        }
    }

    fclose(file);

    return authSuccess;
}
void signupAdminToFile() {
    FILE *file = fopen("admin.txt", "a"); 

    if (file == NULL) {
        printf("*Error opening file for appending*\n");
        return;
    }

    Admin newAdmin;

    printf("==> Enter new admin username: ");
    scanf("%19s", newAdmin.username);

    printf("==> Enter new admin password: ");
    scanf("%19s", newAdmin.password);

    fprintf(file, "%s %s\n", newAdmin.username, newAdmin.password);

    fclose(file);

    printf("==> Admin signup successful!\n");
}


