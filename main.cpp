#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }
    int numStudents;
    int numExamScores;
    in >> numStudents;
    in >> numExamScores;
    string *studentsNames = new string[numStudents];
    int **examScores = new int *[numStudents];


    for (int i = 0; i < numStudents; ++i) {
        examScores[i] = new int[numExamScores];
    }

    for (int i = 0; i < numStudents; ++i) {
        string firstName;
        string lastName;
        in >> firstName;
        in >> lastName;
        studentsNames[i] = firstName + " " + lastName;
        for (int j = 0; j < numExamScores; ++j) {
            in >> examScores[i][j];
        }

    }

    out << "Student Scores:" << endl;

    for(int i =0; i < numStudents; ++i)  {
        out << "\t\t  " << studentsNames[i] << " ";
        for(int j = 0; j < numExamScores; ++j)  {
            out << examScores[i][j] << " ";
        }
        out << endl;
    }



      int examNum = 1;
    double averageExamScore[numExamScores];
    double totalScore = 0;
    out << "Exam Averages:" << endl;
    for (int j = 0; j < numExamScores; ++j) {
        for (int i = 0; i < numStudents; ++i) {
            totalScore = totalScore + examScores[i][j];
        }
        averageExamScore[j] = totalScore / numStudents;
        out << "\tExam " << examNum << " Average = " << fixed << setprecision(1) << averageExamScore[j] << endl;
        totalScore = 0;
        examNum = examNum + 1;
    }

    out << "Student Exam Grades:" << endl;
    string letterGrades[numStudents][numExamScores];
    for(int i = 0; i < numStudents; ++i)  {
        out  << setw(20) << studentsNames[i] << setw(6);
        for(int j = 0; j < numExamScores; ++j)  {
            if(averageExamScore[j] - examScores[i][j] <= 5 && examScores[i][j] - averageExamScore[j] <= 5) {
                out << setw(6) << examScores[i][j] << "(C)";
                letterGrades[i][j] = "C";
            }
            else if((examScores[i][j] - averageExamScore[j]) > 5 && (examScores[i][j] - averageExamScore[j]) < 15) {
                out << setw(6) << examScores[i][j] << "(B)";
                letterGrades[i][j] = "B";
            }
            else if((averageExamScore[j] - examScores[i][j]) > 5 && (averageExamScore[j] - examScores[i][j]) < 15) {
                out << setw(6) << examScores[i][j] << "(D)";
                letterGrades[i][j] = "D";
            }
            else if ((examScores[i][j] - averageExamScore[j]) >= 15) {
                out << setw(6) << examScores[i][j] << "(A)";
                letterGrades[i][j] = "A";
            }
            else if ((averageExamScore[j] - examScores[i][j] >= 15))  {
                out << setw(6) << examScores[i][j] << "(E)";
                letterGrades[i][j] = "E";
            }

        }
        out << endl;
    }
    int numAs = 0;
    int numBs = 0;
    int numCs = 0;
    int numDs = 0;
    int numEs = 0;
    out << "Exam Grades:" << endl;
    for(int j = 0; j < numExamScores; ++j)  {
        for(int i = 0; i < numStudents; ++i) {
            if (letterGrades[i][j] == "A") {
                numAs = numAs + 1;
            } else if (letterGrades[i][j] == "B") {
                numBs = numBs + 1;
            } else if (letterGrades[i][j] == "C") {
                numCs = numCs + 1;
            } else if (letterGrades[i][j] == "D") {
                numDs = numDs + 1;
            } else if (letterGrades[i][j] == "E") {
                numEs = numEs + 1;
            }
        }
        out << "\tExam " << j + 1 << setw(6) << numAs << "(A)";
        out << setw(6) << numBs << "(B)";
        out << setw(6) << numCs << "(C)";
        out << setw(6) << numDs << "(D)";
        out << setw(6) << numEs << "(E)";
        out << endl;
        numAs = 0;
        numBs = 0;
        numCs = 0;
        numDs = 0;
        numEs = 0;

        }

    double finalGrades[numStudents];
    double studentTotalPoints = 0;
    int combinedPoints[numStudents];
    double classFinalAverage = 0.0;
    double totalPointsEarned = 0.0;

    for(int i = 0; i < numStudents; ++i)  {
        for(int j = 0; j < numExamScores; ++j)  {
            studentTotalPoints =  studentTotalPoints + examScores[i][j];
        }
        combinedPoints[i] = studentTotalPoints;
        finalGrades[i] = studentTotalPoints / numExamScores;
        studentTotalPoints = 0;
    }

    for(int i = 0; i < numStudents; ++i)  {
        totalPointsEarned = totalPointsEarned + finalGrades[i];
    }
    classFinalAverage = totalPointsEarned / numStudents;


    out << "Student Final Grades:" << endl;

    for(int i = 0; i < numStudents; ++i)  {


        if(finalGrades[i] - classFinalAverage <= 5 && classFinalAverage - finalGrades[i] <= 5) {
                out << setw(20) << studentsNames[i] << setw(6) << finalGrades[i] << "(C)" << endl;

        }
        else if((finalGrades[i] - classFinalAverage) > 5 && (finalGrades[i] - classFinalAverage) < 15) {
            out << setw(20) << studentsNames[i] << setw(6) << finalGrades[i] <<  "(B)" << endl;

        }
        else if((classFinalAverage - finalGrades[i]) > 5 && (classFinalAverage - finalGrades[i]) < 15) {
            out << setw(20) << studentsNames[i] << finalGrades[i] << "(D)" << endl;

        }
        else if ((finalGrades[i] - classFinalAverage) >= 15) {
            out << setw(20) << studentsNames[i] << finalGrades[i] << "(A)" << endl;

        }
        else if ((classFinalAverage - finalGrades[i] >= 15)) {
            out << setw(20) << studentsNames[i] << finalGrades[i] << "(E)" << endl;
        }

    }
    out << " \t" << setw(20) << "Class Average Score = " << classFinalAverage;


    for(int i = 0; i < numStudents; ++i)  {
        delete[] examScores[i];
    }
    delete [] examScores;
    delete[] studentsNames;
    return 0;
}
