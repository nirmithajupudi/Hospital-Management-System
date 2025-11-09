#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    char doctor[50];
    char date[15]; // dd-mm-yyyy
};

struct Doctor {
    int id;
    char name[50];
    char specialization[50];
    char experience[20];
};

struct Patient *patients = NULL;
struct Doctor *doctors = NULL;
int pCount = 0, dCount = 0;

// Add patient
void addPatient() {
    pCount++;
    patients = realloc(patients, pCount * sizeof(struct Patient));
    printf("\nEnter patient ID: ");
    scanf("%d", &patients[pCount - 1].id);
    printf("Enter name: ");
    scanf(" %[^\n]", patients[pCount - 1].name);
    printf("Enter age: ");
    scanf("%d", &patients[pCount - 1].age);
    printf("Enter gender: ");
    scanf(" %[^\n]", patients[pCount - 1].gender);
    printf("Enter disease: ");
    scanf(" %[^\n]", patients[pCount - 1].disease);
    printf("Enter doctor name: ");
    scanf(" %[^\n]", patients[pCount - 1].doctor);
    printf("Enter date joined (dd-mm-yyyy): ");
    scanf(" %[^\n]", patients[pCount - 1].date);
    printf("\n✅ Patient added successfully!\n");
}

// Add doctor
void addDoctor() {
    dCount++;
    doctors = realloc(doctors, dCount * sizeof(struct Doctor));
    printf("\nEnter doctor ID: ");
    scanf("%d", &doctors[dCount - 1].id);
    printf("Enter name: ");
    scanf(" %[^\n]", doctors[dCount - 1].name);
    printf("Enter specialization: ");
    scanf(" %[^\n]", doctors[dCount - 1].specialization);
    printf("Enter experience (e.g. 10 years): ");
    scanf(" %[^\n]", doctors[dCount - 1].experience);
    printf("\n✅ Doctor added successfully!\n");
}

// Display all patients
void displayPatients() {
    if (pCount == 0) {
        printf("\n⚠️ No patients available.\n");
        return;
    }
    printf("\n=====================================================\n");
    printf("          NIRMITHA MULTI SPECIALITY HOSPITAL\n");
    printf("=====================================================\n");
    printf("                     PATIENT RECORDS\n");
    printf("-----------------------------------------------------\n");
    printf("%-5s %-5s %-12s %-15s %-5s %-8s %-15s %-15s\n",
           "S.No", "ID", "Date", "Name", "Age", "Gender", "Disease", "Doctor");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < pCount; i++) {
        printf("%-5d %-5d %-12s %-15s %-5d %-8s %-15s %-15s\n",
               i + 1,
               patients[i].id,
               patients[i].date,
               patients[i].name,
               patients[i].age,
               patients[i].gender,
               patients[i].disease,
               patients[i].doctor);
    }
    printf("-----------------------------------------------------\n");
}

// Display all doctors
void displayDoctors() {
    if (dCount == 0) {
        printf("\n⚠️ No doctors available.\n");
        return;
    }
    printf("\n=====================================================\n");
    printf("          NIRMITHA MULTI SPECIALITY HOSPITAL\n");
    printf("=====================================================\n");
    printf("                     DOCTOR RECORDS\n");
    printf("-----------------------------------------------------\n");
    printf("%-5s %-5s %-15s %-20s %-10s\n",
           "S.No", "ID", "Name", "Specialization", "Experience");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < dCount; i++) {
        printf("%-5d %-5d %-15s %-20s %-10s\n",
               i + 1,
               doctors[i].id,
               doctors[i].name,
               doctors[i].specialization,
               doctors[i].experience);
    }
    printf("-----------------------------------------------------\n");
}

// Search patient by ID
void searchPatient() {
    int id, found = 0;
    printf("\nEnter patient ID to search: ");
    scanf("%d", &id);
    for (int i = 0; i < pCount; i++) {
        if (patients[i].id == id) {
            found = 1;
            printf("\nPatient Found:\n");
            printf("Name: %s\nAge: %d\nGender: %s\nDisease: %s\nDoctor: %s\nDate Joined: %s\n",
                   patients[i].name, patients[i].age, patients[i].gender,
                   patients[i].disease, patients[i].doctor, patients[i].date);
            break;
        }
    }
    if (!found) printf("❌ Patient not found!\n");
}

// Update patient info
void updatePatient() {
    int id, found = 0;
    printf("\nEnter patient ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < pCount; i++) {
        if (patients[i].id == id) {
            found = 1;
            printf("Enter new disease: ");
            scanf(" %[^\n]", patients[i].disease);
            printf("Enter new doctor: ");
            scanf(" %[^\n]", patients[i].doctor);
            printf("✅ Patient record updated!\n");
            break;
        }
    }
    if (!found) printf("❌ Patient not found!\n");
}

// Delete patient
void deletePatient() {
    int id, found = 0;
    printf("\nEnter patient ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < pCount; i++) {
        if (patients[i].id == id) {
            found = 1;
            for (int j = i; j < pCount - 1; j++)
                patients[j] = patients[j + 1];
            pCount--;
            patients = realloc(patients, pCount * sizeof(struct Patient));
            printf("✅ Patient deleted successfully!\n");
            break;
        }
    }
    if (!found) printf("❌ Patient not found!\n");
}

// Delete doctor
void deleteDoctor() {
    int id, found = 0;
    printf("\nEnter doctor ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < dCount; i++) {
        if (doctors[i].id == id) {
            found = 1;
            for (int j = i; j < dCount - 1; j++)
                doctors[j] = doctors[j + 1];
            dCount--;
            doctors = realloc(doctors, dCount * sizeof(struct Doctor));
            printf("✅ Doctor deleted successfully!\n");
            break;
        }
    }
    if (!found) printf("❌ Doctor not found!\n");
}

// Sort patients by date (dd-mm-yyyy)
int dateValue(char date[]) {
    int d, m, y;
    sscanf(date, "%d-%d-%d", &d, &m, &y);
    return y * 10000 + m * 100 + d;
}

void sortPatientsByDate() {
    struct Patient temp;
    for (int i = 0; i < pCount - 1; i++) {
        for (int j = i + 1; j < pCount; j++) {
            if (dateValue(patients[i].date) > dateValue(patients[j].date)) {
                temp = patients[i];
                patients[i] = patients[j];
                patients[j] = temp;
            }
        }
    }
    printf("\n✅ Patients sorted by joining date!\n");
}

// Save data to file
void saveToFile() {
    FILE *fp = fopen("hospital_data.txt", "w");
    if (!fp) {
        printf("❌ File error!\n");
        return;
    }
    fprintf(fp, "NIRMITHA MULTI SPECIALITY HOSPITAL\n\n");
    fprintf(fp, "PATIENT RECORDS:\n");
    fprintf(fp, "S.No ID Date Name Age Gender Disease Doctor\n");
    for (int i = 0; i < pCount; i++) {
        fprintf(fp, "%d %d %s %s %d %s %s %s\n", i + 1,
                patients[i].id, patients[i].date, patients[i].name,
                patients[i].age, patients[i].gender,
                patients[i].disease, patients[i].doctor);
    }
    fprintf(fp, "\nDOCTOR RECORDS:\n");
    fprintf(fp, "S.No ID Name Specialization Experience\n");
    for (int i = 0; i < dCount; i++) {
        fprintf(fp, "%d %d %s %s %s\n", i + 1,
                doctors[i].id, doctors[i].name,
                doctors[i].specialization, doctors[i].experience);
    }
    fclose(fp);
    printf("✅ Records saved to 'hospital_data.txt'!\n");
}

// Main
int main() {
    int choice;
    do {
        printf("\n==============================================\n");
        printf("   NIRMITHA MULTI SPECIALITY HOSPITAL SYSTEM\n");
        printf("==============================================\n");
        printf("1. Add Patient\n");
        printf("2. Add Doctor\n");
        printf("3. Display Patients\n");
        printf("4. Display Doctors\n");
        printf("5. Search Patient by ID\n");
        printf("6. Update Patient Info\n");
        printf("7. Delete Patient\n");
        printf("8. Delete Doctor\n");
        printf("9. Sort Patients by Date\n");
        printf("10. Save Data to File\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: addDoctor(); break;
            case 3: displayPatients(); break;
            case 4: displayDoctors(); break;
            case 5: searchPatient(); break;
            case 6: updatePatient(); break;
            case 7: deletePatient(); break;
            case 8: deleteDoctor(); break;
            case 9: sortPatientsByDate(); break;
            case 10: saveToFile(); break;
            case 11: printf("\n👋 Exiting... Thank you!\n"); break;
            default: printf("\n❌ Invalid choice! Try again.\n");
        }
    } while (choice != 11);

    free(patients);
    free(doctors);
    return 0;
}