#include "Student.h"

// ================= LOAD =================
// Reads student text file data into the array until full
void loadStudents(Student students[], int& count)
{
    ifstream inputFile("students.txt");

    while (count < MAX_STUDENTS &&
        inputFile >> students[count].firstName
        >> students[count].lastName
        >> students[count].id
        >> students[count].grade)
    {
        count++;
    }

    inputFile.close();
}

// ================= DISPLAY ALL STUDENT INFO =================
// Prints headers and loops through arrays to display all records and grades
void displayAllStudentInfo(double grades[][NUM_ASSIGNMENTS], Student students[], int count)
{
    cout << "\n===== ALL STUDENT RECORDS =====\n";
    cout << "\033[31m" << "ID\tFName\t\tLName\t\t";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
    {
        cout << "A" << (j + 1) << "\t";
    }
    cout << "AVG \033[0m\n";

    for (int i = 0; i < count; i++)
    {
        cout << students[i].id << "\t"
            << students[i].firstName << "      \t"
            << students[i].lastName << "      \t";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            cout << grades[i][j] << "\t";
        }

        cout << students[i].grade << endl;
    }
}

// ================= GENERATE GRADES =================
// Fills the 2D array with random grade percentages between 60 and 100
void generateGrades(double grades[][NUM_ASSIGNMENTS], int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            grades[i][j] = rand() % 41 + 60;
        }
    }
}

// ================= CALCULATE AVERAGES =================
// Computes row averages from the 2D grades array and saves them to the struct
void calculateAverages(double grades[][NUM_ASSIGNMENTS], Student students[], int count)
{
    for (int i = 0; i < count; i++)
    {
        double sum = 0;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            sum += grades[i][j];
        }

        students[i].grade = sum / NUM_ASSIGNMENTS; // derived value
    }
}

// ================= UPDATE ASSIGNMENT =================
// Finds a student by ID and overwrites a single assignment score
void updateAssignment(double grades[][NUM_ASSIGNMENTS], Student students[], int count)
{
    int id, assignment;
    double newGrade;

    cout << "Enter student ID: ";
    cin >> id;

    cout << "Enter assignment (1-5): ";
    cin >> assignment;

    cout << "Enter new grade: ";
    cin >> newGrade;

    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            grades[i][assignment - 1] = newGrade; // update single cell
            cout << "Assignment updated!\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

// ================= ADD STUDENT =================
// Appends a new student to the array and initializes random grades for them
void addStudent(Student students[], int& count, double grades[][NUM_ASSIGNMENTS])
{
    if (count >= MAX_STUDENTS) {

        cout << "\nMAX reached, cannot add more students!!\n";

        return;
    }
        

    Student s;
    s.grade = 0;

    cout << "firstName, lastName, ID\n";
    cin >> s.firstName >> s.lastName >> s.id;

    students[count] = s;

    // initialize grades row for new student
    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
    {
        grades[count][j] = rand() % 41 + 60;
    }

    count++;

    cout << "\nStudent added!\n";
}

// ================= SAVE =================
// Overwrites the text file with current student data from the array
void saveStudents(Student students[], int count)
{
    ofstream outFile("students.txt");

    for (int i = 0; i < count; i++)
    {
        outFile << students[i].firstName << " "
            << students[i].lastName << " "
            << students[i].id << " "
            << students[i].grade << endl;
    }

    outFile.close();

    cout << "\nData saved to file!\n";
}

// ================= HIGHLIGHT SEARCH =================
// Searches and applies ANSI color codes to highlight a chosen row or column
void highlightSearch(double grades[][NUM_ASSIGNMENTS], Student students[], int count)
{
    int choice;

    cout << "\n1. Highlight Student (Row)\n";
    cout << "2. Highlight Assignment (Column)\n";
    cout << "Choice: ";
    cin >> choice;

    int targetRow = -1;
    int targetCol = -1;

    if (choice == 1)
    {
        int id;
        cout << "Enter student ID: ";
        cin >> id;

        for (int i = 0; i < count; i++)
        {
            if (students[i].id == id)
            {
                targetRow = i;
                break;
            }
        }

        if (targetRow == -1)
        {
            cout << "Student not found.\n";
            return;
        }
    }
    else if (choice == 2)
    {
        cout << "Enter assignment (1-5): ";
        cin >> targetCol;
        targetCol--;
    }
    else
    {
        return;
    }

    // ===== HEADER (match your display function exactly) =====
    cout << "\n===== ALL STUDENT RECORDS =====\n";
    cout << "\033[31mA" << "ID\tFName\t\tLName\t\t";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
    {
        cout << "A" << (j + 1) << "\t";
    }

    cout << "AVG \033[0m\n";

    // ===== DATA ROWS =====
    for (int i = 0; i < count; i++)
    {
        if (i == targetRow)
            cout << "\033[33m";

        cout << students[i].id << "\t"
            << students[i].firstName << "      \t"
            << students[i].lastName << "      \t";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            if (j == targetCol)
                cout << "\033[33m" << grades[i][j] << "\033[0m\t";
            else
                cout << grades[i][j] << "\t";
        }

        // highlight AVG if row is targeted
        if (i == targetRow)
            cout << students[i].grade << "\033[0m\n";
        else
            cout << students[i].grade << endl;
    }
}