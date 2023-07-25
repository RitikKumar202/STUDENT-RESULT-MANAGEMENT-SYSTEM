/*=================== HEADER FILE ==========================*/
#include <bits/stdc++.h>
using namespace std;

#define ll long long

/*=================== CLASS USED IN PROJECT ==========================*/
class Student {
public:
  ll roll;
  char StudentName[100];
  char course[100];
  float overallCgpa;
  ll totalNumberOfSemester, batch;
  float semCgpa[8];
  char overallGrade;
  char return_grade(float); // function to return overall grade
  void result();
  long long give_roll();
  void input_info(); // function to accept data from user
  void show_Data();  // function to show data on screen
  void report_card();
};

char Student ::return_grade(float cgpa) {
  if (cgpa >= 9.50)
    return 'O';
  else if (cgpa >= 9.0)
    return 'A';
  else if (cgpa >= 8.0)
    return 'B';
  else if (cgpa >= 7.0)
    return 'C';
  else if (cgpa >= 6.0)
    return 'D';
  else if (cgpa >= 5.0)
    return 'E';
  else
    return 'F';
}

void Student::result() {
  float totalCgpa = 0;
  for (int i = 0; i < totalNumberOfSemester; i++) {
    totalCgpa += semCgpa[i];
  }
  overallCgpa = totalCgpa / totalNumberOfSemester;
  overallGrade = return_grade(overallCgpa);
}

void Student ::input_info() {
  cout << "Enter Roll No.: ";
  cin >> roll;
  cout << "Enter Student Name : ";
  cin.ignore();
  cin.getline(StudentName, 100);
  cout << "Enter Course: ";
  cin.ignore();
  cin.getline(course, 100);
  cout << "Enter Batch: ";
  cin >> batch;
  cout << "Enter Total No. of Semester: ";
  cin >> totalNumberOfSemester;
  for (int i = 0; i < totalNumberOfSemester; i++) {
    if (i == 0) {
      cout << "Enter CGPA of " << i + 1 << "st Semester: ";
    } else if (i == 1) {
      cout << "Enter CGPA of " << i + 1 << "nd Semester: ";
    } else if (i == 2) {
      cout << "Enter CGPA of " << i + 1 << "rd Semester: ";
    } else {
      cout << "Enter CGPA of " << i + 1 << "th Semester: ";
    }
    cin >> semCgpa[i];
  }
  result(); // calculates the results on the basis of Inputs
}

void Student ::show_Data() {
  cout << "Roll Number: " << roll << endl;
  cout << "Student Name: " << StudentName << endl;
  cout << "Course: " << course << endl;
  cout << "Batch: " << batch << endl;
  cout << "Total Number of Semester: " << totalNumberOfSemester << endl;
  for (int i = 0; i < totalNumberOfSemester; i++) {
    if (i == 0) {
      cout << i + 1 << "st Semester CGPA: ";
    } else if (i == 1) {
      cout << i + 1 << "nd Semester CGPA: ";
    } else if (i == 2) {
      cout << i + 1 << "rd Semester CGPA: ";
    } else {
      cout << i + 1 << "th Semester CGPA: ";
    }
    cout << semCgpa[i] << endl;
  }
  cout << "Overall CGPA: " << overallCgpa << endl;
  cout << "Overall Grade: " << overallGrade << "\n\n";
}

void Student ::report_card() {
  cout << StudentName << "\t" << roll << "\t" << course << "\t   " << batch
       << "\t      " << overallCgpa << "\t\t" << overallGrade << "\n";
  cout << "--------------------------------------------------------------------"
       "------------\n";
}

ll Student ::give_roll() { return roll; }

/*=================== FUNCTION TO WRITE IN FILE ==========================*/
void enter_record() {
  Student S;
  ofstream Ofile;
  Ofile.open("student.dat", ios::binary | ios::app);
  S.input_info();
  Ofile.write(reinterpret_cast<char *>(&S), sizeof(Student));
  Ofile.close();
  cout << " \n Record Entered Succesfully \n ";
  cin.ignore();
  cin.get();
}

void intro();

/*=================== FUNCTION TO DISPLAY ALL RECORDS FROM FILE
 * ==========================*/
void display() {

  Student S;
  ifstream Ifile;
  Ifile.open("student.dat", ios::binary);
  if (!Ifile) {
    cout << "Failed To Open File!! Press Any Key To Return Main Menu.. ";
    cin.ignore();
    cin.get();
    return;
  }
  cout << "================== ALL STUDENT RECORD !!! ==================\n\n";
  while (Ifile.read(reinterpret_cast<char *>(&S), sizeof(Student))) {
    S.show_Data();
    cout << "====================================\n";
  }

  cout << "Press Any Key To Return Main Menu...  ";
  Ifile.close();
  cin.ignore();
  cin.get();
}

/*=================== FUNCTION TO SEARCH SPECIFIC RECORD FROM FILE
 * ==========================*/
void search(ll r) {
  Student S;
  ifstream Ifile;
  Ifile.open("student.dat", ios::binary);
  if (!Ifile) {
    cout << "Failed To Open File!! Press Any Key to Return Main Menu.. ";
    cin.ignore();
    cin.get();
    return;
  } else {
    bool found = 0;
    while (Ifile.read(reinterpret_cast<char *>(&S), sizeof(Student))) {
      if (S.give_roll() == r) {
        S.show_Data();
        found = 1;
        cout << "Press Any Key To Return Main Menu...  ";
      }
    }
    if (found == 0) {
      cout << "Student Record Not Found!! Press Any Key to Return Main Menu.. ";
    }
    Ifile.close();
  }
  cin.ignore();
  cin.get();
}

/*=================== FUNCTION TO MODIFY RECORD FROM FILE
 * ==========================*/
void modify(ll r) {
  bool found = 0;
  Student S;
  fstream Ifile;
  Ifile.open("student.dat", ios::binary | ios::in | ios::out);
  if (!Ifile) {
    cout << "Student Not Found!! Press any Key to continue... ";
    cin.ignore();
    cin.get();
    return;
  }
  while (!(Ifile.eof()) && found == 0) {
    Ifile.read(reinterpret_cast<char *>(&S), sizeof(Student));
    if (S.give_roll() == r) {
      S.show_Data();
      cout << "\n\nPlease Enter The New Details of student" << endl;
      S.input_info();
      ll position = (-1) * static_cast<int>(sizeof(S));
      Ifile.seekp(position, ios::cur);
      Ifile.write(reinterpret_cast<char *>(&S), sizeof(Student));
      cout << "\n\n\tStudent Details Updated \n";
      found = 1;
    }
  }
  Ifile.close();
  if (found == 0) {
    cout << "Student Not Found!! Press any Key to continue... ";
  }
  cin.ignore();
  cin.get();
}

/*=================== FUNCTION TO DELETE RECORD FROM FILE
 * ==========================*/
void delete_record(ll n) {
  int flag = 0;
  Student st;
  ifstream inFile;
  inFile.open("student.dat", ios::binary);
  if (!inFile) {
    cout << "File could not be open!! Press any Key to Return Main Menu.. ";
    cin.ignore();
    cin.get();
    return;
  }
  ofstream outFile;
  outFile.open("Temp.dat", ios::out);
  inFile.seekg(0, ios::beg);
  while (inFile.read(reinterpret_cast<char *>(&st), sizeof(Student))) {
    if (st.give_roll() != n) {
      outFile.write(reinterpret_cast<char *>(&st), sizeof(Student));
    }
    if (st.give_roll() == n) {
      flag = 1;
    }
  }
  outFile.close();
  inFile.close();
  remove("student.dat");
  rename("Temp.dat", "student.dat");

  if (flag == 1) {
    cout << "Record Deleted Succesfully.\n\n";
  } else {
    cout << "Unable to Delete as Record Not Found!\n\n";
  }
  cout << "Press any Key to Return Main Menu.. ";
  cin.ignore();
  cin.get();
}

/*=================== FUNCTION TO DISPLAY ALL STUDENTS GRADE FROM FILE
 * ==========================*/
void result() {
  system("cls");
  Student S;
  ifstream file;
  file.open("student.dat", ios::binary);
  if (!file) {
    cout << "Failed To Open File!! Press Any Key To Return Main Menu.. ";
    cin.ignore();
    cin.get();
    return;
  }
  cout << "\n\n\t\t\tALL STUDENTS RESULT \n\n";
  cout << "===================================================================="
       "============ \n";
  cout << "  NAME          R.NO           COURSE      BATCH   OVERALL-CGPA  "
       "OVERALL-GRADE"
       << endl;
  cout << "===================================================================="
       "============\n";
  while (file.read(reinterpret_cast<char *>(&S), sizeof(Student))) {
    S.report_card();
  }
  cout << "\nPress Any Key To Return Main Menu...  ";
  file.close();
  cin.ignore();
  cin.get();
}

/*=================== FUNCTION TO DISPLAY RESULT MENU
 * ==========================*/
void overall() {

  system("cls");
  char choice;
  ll se;
  cout << "\n\n\tRESULT MENU";
  cout << "\n\n\t01. STUDENT RESULTS";
  cout << "\n\t02. INDIVIDUAL RESULT";
  cout << "\n\t03. BACK TO MAIN MENU";
  cout << "\n\n\tEnter Choice (1 / 2 / 3) ? ";
  cin >> choice;
  system("cls");
  switch (choice) {
  case '1':
    result();
    break;
  case '2':
    cout << "Enter Student Roll Number : ";
    cin >> se;
    cout << "\n";
    search(se);
  case '3':
    break;
  default:
    cout << "Wrong Choice \n";
  }
}

/*=================== ENTRY/EDIT MENU ==========================*/
void main_menu() {
  int choice;
  system("cls");
  cout << "\n\n\n\tENTRY MENU";
  cout << "\n\n\t01. CREATE STUDENT RECORD";
  cout << "\n\n\t02. DISPLAY ALL STUDENTS RECORD";
  cout << "\n\n\t03. SEARCH STUDENT RECORD";
  cout << "\n\n\t04. MODIFY STUDENT RECORD";
  cout << "\n\n\t05. DELETE STUDENT RECORD";
  cout << "\n\n\t06. BACK TO MAIN MENU";
  cout << "\n\n\tPlease Enter Your Choice (1 - 6) ";
  cin >> choice;
  system("cls");
  switch (choice) {
  case 1:
    enter_record();
    break;
  case 2:
    display();
    break;
  case 3:
    ll roll;
    cout << "Enter Student Roll Number to Find all Details: ";
    cin >> roll;
    cout << "\n";
    search(roll);
    break;
  case 4:
    cout << "Enter Student Current Roll Number to Modify: ";
    cin >> roll;
    cout << "\n";
    modify(roll);
    break;
  case 5:
    cout << "Enter Student Roll Number to Delete Record: ";
    cin >> roll;
    cout << "\n";
    delete_record(roll);
    break;
  case 6:
    break;
defualt:
    cout << "\a";
    main_menu();
  }
}

/*=================== INTRO FUNCTION ==========================*/
void intro() {
  system("cls");
  cout << "============================================================\n";
  cout << "\t\t  WELCOME";
  cout << "\n\n\t\t     TO";
  cout << "\n\n\tSTUDENT RESULT MANAGEMENT SYSTEM";
  cout << "\n\n\n\t    MADE BY : RITIK KUMAR\n";
  cout << "============================================================\n\n";
  cout << "Press Any Key to Return to Main Menu!  ";
  cin.get();
}

/*=================== THE MAIN FUNCTION OF PROGRAM ==========================*/
int main() {
  intro();
  int choice;
  do {
    system("cls");
    cout << "\n\n";
    cout << "\t\t Main Menu\n\n";
    cout << "\t\t 01. Result Menu\n";
    cout << "\t\t 02. Entry / Edit Menu\n";
    cout << "\t\t 03. Exit\n";
    cout << "\t\t Please Enter Your Choice (1 - 3) : ";
    cin >> choice;
    switch (choice) {
    case 1:
      overall();
      break;
    case 2:
      main_menu();
      break;
    case 3:
      exit(0);
    default:
      cout << "Wrong Submission\n";
    }
  } while (choice != 3);
  return 0;
}