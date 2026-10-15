#include <stdio.h>
#include <string.h>
#include "database.h"

int apply_for_scholarship(Database *db, const char *student_id, const char *scholarship_name) {
    if (db->application_count >= MAX_RECORDS) return -1;
    
    int index = db->application_count;
    Application *app = &db->applications[index];
    
    strcpy(app->student_id, student_id);
    strcpy(app->scholarship_name, scholarship_name);
    strcpy(app->status, "Pending_Verification");
    
    db->application_count++;
    return index; // Return the position of this new application
}

void save_applications_to_file(Database *db) {
    FILE *file = fopen("applications.txt", "w");
    if (!file) return;
    for (int i = 0; i < db->application_count; i++) {
        fprintf(file, "%s %s %s\n", db->applications[i].student_id, db->applications[i].scholarship_name, db->applications[i].status);
    }
    fclose(file);
}

void load_applications_from_file(Database *db) {
    FILE *file = fopen("applications.txt", "r");
    if (!file) return; 
    while (fscanf(file, "%s %s %s", db->applications[db->application_count].student_id, db->applications[db->application_count].scholarship_name, db->applications[db->application_count].status) == 3) {
        db->application_count++;
    }
    fclose(file);
}