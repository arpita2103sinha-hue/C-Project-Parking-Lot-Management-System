#include <stdio.h>
#include <string.h>
#include "../include/parking.h" // Links to the header you just made

// Global variable definitions
struct Car data[100];
int cnt = 0;
char d_date[20], d_day[20];

// Function to check if a specific slot is empty
int check_slot(int s) {
    int i;
    for(i = 0; i < cnt; i++) {
        // If slot matches AND status is 'P' (Parked), it's busy
        if(data[i].slot_id == s && data[i].type == 'P') {
            return 0; 
        }
    }
    return 1; // Slot is free
}

void new_entry() {
    if(cnt >= 100) {
        printf("Memory Full.\n");
        return;
    }

    struct Car temp;
    int i;

    printf("\n--- Entry Form ---\n");
    printf("Enter vehicle number: ");
    scanf("%s", temp.no);

    // Check if this car is already inside (Duplicate check)
    for(i = 0; i < cnt; i++) {
        if(strcmp(data[i].no, temp.no) == 0 && data[i].type == 'P') {
            printf("Error: This vehicle is already inside the parking lot!\n");
            return;
        }
    }

    printf("Enter owner name: ");
    scanf(" %[^\n]s", temp.name); // Reads name with spaces

    printf("Enter parking slot: ");
    scanf("%d", &temp.slot_id);

    // Validate if slot is free
    if(check_slot(temp.slot_id) == 0) {
        printf("Slot %d is currently occupied!\n", temp.slot_id);
        return;
    }

    printf("Enter entry time (0-23 hours): ");
    scanf("%d", &temp.t_in);

    temp.type = 'P'; // Set status to Parked
    temp.t_out = 0;

    data[cnt] = temp; // Save to array
    cnt++;
    
    printf("Vehicle added successfully on %s (%s)!\n", d_date, d_day);
}

void checkout() {
    int s, t, i, found = -1;
    
    printf("\n--- Exit Form ---\n");
    printf("Enter slot to exit: ");
    scanf("%d", &s);

    // Find the car in this slot that is currently parked
    for(i = 0; i < cnt; i++) {
        if(data[i].slot_id == s && data[i].type == 'P') {
            found = i;
            break;
        }
    }

    if(found == -1) {
        printf("No active vehicle found in slot %d!\n", s);
        return;
    }

    printf("Enter exit time: ");
    scanf("%d", &t);

    // Calculate duration
    int dur = t - data[found].t_in;
    if(dur <= 0) dur = dur + 24; // Fix for overnight parking

    // Calculate fee (Min 20 Rs)
    int amt = dur * 20;
    if(amt < 20) amt = 20;

    // Update status to 'E' (Exited) instead of deleting
    data[found].type = 'E';
    data[found].t_out = t;

    printf("\nReceipt:\n");
    printf("Date: %s | Day: %s\n", d_date, d_day);
    printf("Vehicle: %s\n", data[found].no);
    printf("Duration: %d hours\n", dur);
    printf("Total Fee: Rs %d\n", amt);
    printf("Vehicle removed from active slots.\n");
}

// Combined search function for Number and Owner
void find_car() {
    int choice, i, flag = 0;
    char query[30];

    printf("\nSearch by: 1.Number 2.Owner\nOption: ");
    scanf("%d", &choice);

    printf("Enter Value: ");
    scanf(" %[^\n]s", query);

    for(i = 0; i < cnt; i++) {
        int match = 0;
        // Check based on user choice
        if(choice == 1 && strcmp(data[i].no, query) == 0) match = 1;
        if(choice == 2 && strcmp(data[i].name, query) == 0) match = 1;

        if(match) {
            char *statStr = (data[i].type == 'P') ? "PARKED" : "EXITED";
            printf("\nFound (%s):\nNumber: %s | Slot: %d | In: %d", 
                   statStr, data[i].no, data[i].slot_id, data[i].t_in);
            
             if(data[i].type == 'E') printf(" | Out: %d\n", data[i].t_out);
             else printf("\n");

            flag = 1;
        }
    }
    if(flag == 0) printf("Not found in records!\n");
}

void show_list() {
    int i;
    if(cnt == 0) {
        printf("No records found!\n");
        return;
    }

    printf("\n====================================================================\n");
    printf(" PARKING REPORT | Date: %s | Day: %s\n", d_date, d_day);
    printf("====================================================================\n");
    printf("%-5s %-15s %-15s %-10s %-8s %-8s %-10s\n", 
           "S.No", "Vehicle No", "Owner", "Slot", "InTime", "OutTime", "Status");
    printf("--------------------------------------------------------------------\n");


    for(i = 0; i < cnt; i++) {
        printf("%-5d %-15s %-15s %-10d %-8d ", 
               i+1, data[i].no, data[i].name, data[i].slot_id, data[i].t_in);
        
        // Display Exit time only if car has left
        if(data[i].type == 'E') {
            printf("%-8d %-10s\n", data[i].t_out, "EXITED");
        } else {
            printf("%-8s %-10s\n", "-", "PARKED");
        }
    }
    printf("====================================================================\n");
}
