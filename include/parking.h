#ifndef PARKING_H
#define PARKING_H

// Structure to store car details
struct Car {
    char no[20];
    char name[30];
    int slot_id;
    int t_in;      // Entry time
    int t_out;     // Exit time
    char type;     // 'P' = Parked, 'E' = Exited
};

// Global variables (We use 'extern' to tell the main file they exist)
extern struct Car data[100];
extern int cnt;
extern char d_date[20], d_day[20];

// Function Prototypes (List of features)
int check_slot(int s);
void new_entry();
void checkout();
void find_car();
void show_list();

#endif
