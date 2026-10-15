#include <stdio.h>
#include <string.h>
#include "database.h"

void finalize_award(Database *db, int app_index) {
    if (app_index < 0) return;
    Application *app = &db->applications[app_index];
    
    // Check if Module 3 approved them
    if (strcmp(app->status, "Verified_Eligible") == 0) {
        strcpy(app->status, "Award_Granted");
        
        AwardRecord *record = &db->award_history[db->award_count++];
        strcpy(record->student_id, app->student_id);
        strcpy(record->scholarship_name, app->scholarship_name);
        strcpy(record->date_awarded, "2026-10-15"); // Current date
    }
}

void save_awards_to_file(Database *db) {
    FILE *file = fopen("awards.txt", "w");
    if (!file) return;
    for (int i = 0; i < db->award_count; i++) {
        fprintf(file, "%s %s %s\n", db->award_history[i].student_id, db->award_history[i].scholarship_name, db->award_history[i].date_awarded);
    }
    fclose(file);
}

void load_awards_from_file(Database *db) {
    FILE *file = fopen("awards.txt", "r");
    if (!file) return;
    while (fscanf(file, "%s %s %s", db->award_history[db->award_count].student_id, db->award_history[db->award_count].scholarship_name, db->award_history[db->award_count].date_awarded) == 3) {
        db->award_count++;
    }
    fclose(file);
}