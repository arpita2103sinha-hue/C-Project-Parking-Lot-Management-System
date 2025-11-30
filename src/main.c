#include <stdio.h>
#include "../include/parking.h" // This links to your header file

int main(int argc, char *argv[]) {
    int op;

    // --- STEP 1: Ask for Date and Day initially ---
    printf("\n--- INITIAL SETUP ---\n");
    printf("Enter Today's Date (e.g., 12/11/2024): ");
    scanf("%s", d_date);
    printf("Enter Today's Day (e.g., Monday): ");
    scanf("%s", d_day);

    while(1) {
        // Menu exactly matches the image
        printf("\n--- Parking Menu (%s) ---\n", d_day);
        printf("1. Add Vehicle\n");
        printf("2. Exit Vehicle\n");
        printf("3. Search by Number\n");
        printf("4. Search by Owner\n");
        printf("5. Display All (History + Current)\n");
        printf("6. Exit Program\n");
        printf("Enter choice: ");
        scanf("%d", &op);

        if(op == 1) new_entry();
        else if(op == 2) checkout();
        else if(op == 3) find_car(); 
        else if(op == 4) find_car(); 
        else if(op == 5) show_list();
        else if(op == 6) return 0;
        else printf("Invalid option!\n");
    }
}
