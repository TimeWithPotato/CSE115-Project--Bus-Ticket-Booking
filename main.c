#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structures
struct info {
    int id;
    char name[30];
    char origin[30];
    char dest[30];
    char time[30];
    char date[30];
} u;

struct access {
    char uname[10];
    char pass[20];
} s;

// Function Prototypes
void login();
void create();
void insert();
void display();
void search();
void cancel();
void update();
int avlid(int n);
int emptychecking();
void append();
void menu();

// Function Definitions

void login() {
    FILE *fp, *fp_1;
    char temp[20];
    fflush(stdin);
    printf("Enter your username: ");
    fgets(s.uname, sizeof(s.uname), stdin);
    s.uname[strcspn(s.uname, "\n")] = 0; // Remove trailing newline

    if ((fp = fopen(s.uname, "r")) == NULL) {
        printf("You're not registered.\nCreate an account.\n");
        exit(1);
    } else {
        fp_1 = fopen("pass.txt", "r");
        if (!fp_1) {
            printf("Error reading password file.\n");
            fclose(fp);
            exit(1);
        }
        printf("Enter your password: ");
        fgets(s.pass, sizeof(s.pass), stdin);
        s.pass[strcspn(s.pass, "\n")] = 0;

        fscanf(fp_1, "%s", temp);
        if (strcmp(s.pass, temp) != 0) {
            printf("Wrong password.\n");
            fclose(fp);
            fclose(fp_1);
            exit(1);
        }
    }
    fclose(fp);
    fclose(fp_1);
    printf("Login successful.\n");
}

void create() {
    FILE *fp, *fp_1;
    fflush(stdin);
    printf("Enter your username: ");
    fgets(s.uname, sizeof(s.uname), stdin);
    s.uname[strcspn(s.uname, "\n")] = 0;

    if ((fp = fopen(s.uname, "w")) == NULL) {
        printf("Error creating account.\n");
        exit(1);
    }
    fp_1 = fopen("pass.txt", "w");
    if (!fp_1) {
        printf("Error creating password file.\n");
        fclose(fp);
        exit(1);
    }

    printf("Enter password: ");
    fgets(s.pass, sizeof(s.pass), stdin);
    s.pass[strcspn(s.pass, "\n")] = 0;

    fprintf(fp_1, "%s", s.pass);
    fclose(fp);
    fclose(fp_1);
    printf("Account created successfully.\n");
}

void insert() {
    FILE *fp = fopen("BUS", "w");
    if (!fp) {
        printf("Error opening file for writing.\n");
        return;
    }

    fflush(stdin);
    printf("Enter National ID: ");
    scanf("%d", &u.id);
    getchar(); // Clear newline

    printf("Enter Name: ");
    fgets(u.name, sizeof(u.name), stdin);
    u.name[strcspn(u.name, "\n")] = 0;

    printf("\n1.Dhaka\t2.Chittagong\n3.Barisal\t4.Khulna\n5.Mymensingh\t6.Rajshahi\n7.Rangpur\t8.Sylhet\n");
    printf("Enter Origin From Above: ");
    fgets(u.origin, sizeof(u.origin), stdin);
    u.origin[strcspn(u.origin, "\n")] = 0;

    printf("Select Destination From Above: ");
    fgets(u.dest, sizeof(u.dest), stdin);
    u.dest[strcspn(u.dest, "\n")] = 0;

    printf("Enter Journey Date: ");
    fgets(u.date, sizeof(u.date), stdin);
    u.date[strcspn(u.date, "\n")] = 0;

    printf("Enter Departure Time: ");
    fgets(u.time, sizeof(u.time), stdin);
    u.time[strcspn(u.time, "\n")] = 0;

    fwrite(&u, sizeof(u), 1, fp);
    fclose(fp);
    printf("Ticket inserted successfully.\n");
}

void display() {
    FILE *fp = fopen("BUS", "r");
    if (!fp) {
        printf("Error opening file for reading.\n");
        return;
    }

    while (fread(&u, sizeof(u), 1, fp)) {
        printf("\nID: %d\nName: %s\nOrigin: %s\nDestination: %s\nJourney Date: %s\nDeparture Time: %s\n",
               u.id, u.name, u.origin, u.dest, u.date, u.time);
    }
    fclose(fp);
}

void search() {
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    if (avlid(id) == 0) {
        printf("ID %d is not available.\n", id);
        return;
    }

    FILE *fp = fopen("BUS", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&u, sizeof(u), 1, fp)) {
        if (u.id == id) {
            printf("\nID: %d\nName: %s\nOrigin: %s\nDestination: %s\nJourney Date: %s\nDeparture Time: %s\n",
                   u.id, u.name, u.origin, u.dest, u.date, u.time);
            break;
        }
    }
    fclose(fp);
}

void cancel() {
    int id;
    printf("Enter the ID you want to delete: ");
    scanf("%d", &id);

    if (avlid(id) == 0) {
        printf("ID %d is not available in the record.\n", id);
        return;
    }

    FILE *fp = fopen("BUS", "r");
    FILE *temp = fopen("temp", "w");
    if (!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&u, sizeof(u), 1, fp)) {
        if (u.id != id) {
            fwrite(&u, sizeof(u), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);

    remove("BUS");
    rename("temp", "BUS");
    printf("Ticket canceled successfully.\n");
}

void update() {
    int id, choice;
    printf("Enter the ID to update: ");
    scanf("%d", &id);

    if (avlid(id) == 0) {
        printf("ID %d is not available.\n", id);
        return;
    }

    FILE *fp = fopen("BUS", "r");
    FILE *temp = fopen("temp", "w");
    if (!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&u, sizeof(u), 1, fp)) {
        if (u.id == id) {
            printf("\n1. Update Origin\n2. Update Destination\n3. Update Date\n4. Update Time\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();

            switch (choice) {
                case 1:
                    printf("Enter new Origin: ");
                    fgets(u.origin, sizeof(u.origin), stdin);
                    u.origin[strcspn(u.origin, "\n")] = 0;
                    break;
                case 2:
                    printf("Enter new Destination: ");
                    fgets(u.dest, sizeof(u.dest), stdin);
                    u.dest[strcspn(u.dest, "\n")] = 0;
                    break;
                case 3:
                    printf("Enter new Date: ");
                    fgets(u.date, sizeof(u.date), stdin);
                    u.date[strcspn(u.date, "\n")] = 0;
                    break;
                case 4:
                    printf("Enter new Time: ");
                    fgets(u.time, sizeof(u.time), stdin);
                    u.time[strcspn(u.time, "\n")] = 0;
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
        }
        fwrite(&u, sizeof(u), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("BUS");
    rename("temp", "BUS");
    printf("Record updated successfully.\n");
}

int avlid(int n) {
    FILE *fp = fopen("BUS", "r");
    if (!fp) {
        return 0;
    }

    while (fread(&u, sizeof(u), 1, fp)) {
        if (u.id == n) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n1. Insert\n2. Display\n3. Search\n4. Cancel\n5. Update\n6. Append\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insert(); break;
            case 2: display(); break;
            case 3: search(); break;
            case 4: cancel(); break;
            case 5: update(); break;
            case 6: append(); break;
            case 7: exit(0);
            default: printf("Invalid choice. Try again.\n"); break;
        }
    } while (choice != 7);
}

int emptychecking() {
    FILE *fp = fopen("BUS", "r");
    if (!fp || fgetc(fp) == EOF) {
        fclose(fp);
        return 1;
    }
    fclose(fp);
    return 0;
}

void append() {
    FILE *fp = fopen("BUS", "a");
    if (!fp) {
        printf("Error opening file for appending.\n");
        return;
    }

    printf("Enter National ID: ");
    scanf("%d", &u.id);
    getchar(); // Clear newline

    printf("Enter Name: ");
    fgets(u.name, sizeof(u.name), stdin);
    u.name[strcspn(u.name, "\n")] = 0;

    printf("Enter Origin: ");
    fgets(u.origin, sizeof(u.origin), stdin);
    u.origin[strcspn(u.origin, "\n")] = 0;

    printf("Enter Destination: ");
    fgets(u.dest, sizeof(u.dest), stdin);
    u.dest[strcspn(u.dest, "\n")] = 0;

    printf("Enter Journey Date: ");
    fgets(u.date, sizeof(u.date), stdin);
    u.date[strcspn(u.date, "\n")] = 0;

    printf("Enter Departure Time: ");
    fgets(u.time, sizeof(u.time), stdin);
    u.time[strcspn(u.time, "\n")] = 0;

    fwrite(&u, sizeof(u), 1, fp);
    fclose(fp);
    printf("Data appended successfully.\n");
}

// Main function
int main() {
    int choice;
    printf("\n1. Login\n2. Create Account\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            login();
            menu();
            break;
        case 2:
            create();
            menu();
            break;
        default:
            printf("Invalid choice. Exiting.\n");
            exit(1);
    }

    return 0;
}
