#include <iostream>
#include "Student.h"
using namespace std;

// ================= MAIN =================
int main()
{
    srand(time(0));

    Student students[MAX_STUDENTS];
    double grades[MAX_STUDENTS][NUM_ASSIGNMENTS];

    int count = 0;

    loadStudents(students, count);
    generateGrades(grades, count);  // initialize grades for existing students

    int choice;

    do
    {
        cout << "\n===== STUDENT SYSTEM =====\n";
        cout << "1. Display All Students Info\n";
        cout << "2. Update Assignment\n";
        cout << "3. Add Student\n";
        cout << "4. Save to File\n";
        cout << "5. Highlight Student / Assignment\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";


        cin >> choice;

        switch (choice)
        {
        case 1:
            calculateAverages(grades, students, count);
            displayAllStudentInfo(grades, students, count);
            break;

        case 2:
            updateAssignment(grades, students, count);
            calculateAverages(grades, students, count); // recompute after change
            displayAllStudentInfo(grades, students, count);
            break;

        case 3:
            addStudent(students, count, grades); // also initializes grades row
            calculateAverages(grades, students, count);
            displayAllStudentInfo(grades, students, count);
            break;

        case 4:
            saveStudents(students, count);
            break;

        case 5:
            highlightSearch(grades, students, count);
            break;

        case 6:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}