#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

int main() {
    Database db = {0}; 

    // Load backend permanent storage
    load_students_from_file(&db);
    load_applications_from_file(&db);
    load_awards_from_file(&db);

    // Setup dummy scholarship criteria
    strcpy(db.scholarships[0].name, "Merit_Scholarship");
    db.scholarships[0].min_gpa = 3.5;
    db.scholarships[0].max_income = 100000.0;
    db.scholarship_count = 1;

    int choice;
    while(1) {
        printf("\n===================================\n");
        printf("    SCHOLARSHIP SYSTEM PORTAL      \n");
        printf("===================================\n");
        printf("1. Student Portal (Apply)\n");
        printf("2. Backend Admin (Add Student)\n");
        printf("3. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // FRONTEND: STUDENT APPLIES
            char id[50], scholarship[50];
            printf("\n--- Student Application ---\n");
            printf("Enter Student ID: ");
            scanf("%s", id);
            printf("Enter Scholarship Name (e.g., Merit_Scholarship): ");
            scanf("%s", scholarship);

            printf("\nProcessing your application...\n");

            // FLOW: Module 2 -> Module 3 (which checks Module 1) -> Module 4
            int app_index = apply_for_scholarship(&db, id, scholarship);
            
            if (app_index != -1) {
                verify_application(&db, app_index);
                finalize_award(&db, app_index);

                // OUTPUT: Show final result to the student
                printf("\n>>> FINAL RESULT: %s <<<\n", db.applications[app_index].status);
            }

            // Save state
            save_applications_to_file(&db);
            save_awards_to_file(&db);

        } else if (choice == 2) {
            // BACKEND: ADD RECORDS
            char id[50], name[50];
            float gpa, income;

            printf("\n--- Backend Data Entry ---\n");
            printf("Enter Student ID: ");
            scanf("%s", id);
            printf("Enter Name (no spaces): ");
            scanf("%s", name);
            printf("Enter GPA: ");
            scanf("%f", &gpa);
            printf("Enter Family Income: ");
            scanf("%f", &income);

            // Call Module 1 to save to backend
            register_student(&db, id, name, gpa, income);
            save_students_to_file(&db);
            
            printf("Backend: Student record added successfully.\n");

        } else if (choice == 3) {
            printf("Exiting system...\n");
            break;
        } else {
            printf("Invalid selection.\n");
        }
    }

    return 0;
}