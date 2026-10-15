#include <stdio.h>
#include <string.h>
#include "database.h"

void verify_application(Database *db, int app_index) {
    if (app_index < 0) return;
    Application *app = &db->applications[app_index];
    
    // 1. Call Module 1 to check backend records
    Student *student = get_student_record(db, app->student_id);
    
    if (student == NULL) {
        strcpy(app->status, "Rejected_No_Record_Found");
        return;
    }

    // 2. Find Scholarship Criteria
    Scholarship *scholarship = NULL;
    for (int j = 0; j < db->scholarship_count; j++) {
        if (strcmp(db->scholarships[j].name, app->scholarship_name) == 0) {
            scholarship = &db->scholarships[j];
            break;
        }
    }

    // 3. Verify Criteria
    if (scholarship != NULL) {
        if (student->gpa >= scholarship->min_gpa && student->family_income <= scholarship->max_income) {
            strcpy(app->status, "Verified_Eligible");
        } else {
            strcpy(app->status, "Rejected_Ineligible");
        }
    }
}