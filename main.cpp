#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

double median(std::vector<double> scores) {
    std::sort(scores.begin(), scores.end());
    size_t n = scores.size();
    if (n % 2 == 0) {
        return (scores[n/2 - 1] + scores[n/2]) / 2.0;
    } else {
        return scores[n/2];
    }
}

class Person {
private:
    std::string name;
    std::string surname;
    std::vector<double> homework;
    double exam;
    double finalGrade;

public:
    Person(std::string n="", std::string s="") : name(n), surname(s), exam(0), finalGrade(0) {}

    Person(const Person &p) {
        name = p.name;
        surname = p.surname;
        homework = p.homework;
        exam = p.exam;
        finalGrade = p.finalGrade;
    }

    Person& operator=(const Person &p) {
        if (this == &p) return *this;
        name = p.name;
        surname = p.surname;
        homework = p.homework;
        exam = p.exam;
        finalGrade = p.finalGrade;
        return *this;
    }

    ~Person() {}

    void inputFromVector(const std::vector<double>& hwScores, double ex) {
        homework = hwScores;
        exam = ex;
    }

    void generateRandomScores(int numHW) {
        homework.clear();
        for (int i = 0; i < numHW; ++i) {
            homework.push_back(rand() % 11); // 0-10
        }
        exam = rand() % 11; // 0-10
    }

    void calculateFinalGrade(const std::string& method) {
        double hwAvg = std::accumulate(homework.begin(), homework.end(), 0.0) / homework.size();
        if (method == "A" || method == "a") {
            finalGrade = 0.4 * hwAvg + 0.6 * exam;
        } else if (method == "M" || method == "m") {
            finalGrade = 0.4 * median(homework) + 0.6 * exam;
        }
    }

    void display() const {
        std::cout << std::setw(10) << name
                  << std::setw(12) << surname
                  << std::setw(12) << std::fixed << std::setprecision(2)
                  << finalGrade << "\n";
    }

    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
};

int main() {
    srand(time(0)); // initialize random seed
    std::vector<Person> students;

    std::string method;
    std::cout << "Calculate final grade using Average (A) or Median (M)? ";
    std::cin >> method;

    // Ask user if they want random generation or file input
    char choice;
    std::cout << "Use random scores? (Y/N): ";
    std::cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        int numStudents, numHW;
        std::cout << "Number of students: ";
        std::cin >> numStudents;
        std::cout << "Number of homework assignments: ";
        std::cin >> numHW;

        for (int i = 0; i < numStudents; ++i) {
            std::string n, s;
            std::cout << "Enter name and surname for student " << i+1 << ": ";
            std::cin >> n >> s;
            Person p(n, s);
            p.generateRandomScores(numHW);
            p.calculateFinalGrade(method);
            students.push_back(p);
        }
    } else {
        std::ifstream file("Students.txt");
        if (!file.is_open()) {
            std::cerr << "Error opening Students.txt\n";
            return 1;
        }
        std::string header;
        getline(file, header); // skip header

        std::string name, surname;
        while (file >> name >> surname) {
            Person p(name, surname);
            std::vector<double> hwScores;
            double score;
            // read all but last number as homework
            for (int i = 0; i < 5; ++i) {
                file >> score;
                hwScores.push_back(score);
            }
            double exam;
            file >> exam;

            p.inputFromVector(hwScores, exam);
            p.calculateFinalGrade(method);
            students.push_back(p);
        }
        file.close();
    }

    // Sort by name
    std::sort(students.begin(), students.end(), [](const Person &a, const Person &b){
        return a.getName() < b.getName();
    });

    std::cout << "\nName      Surname     Final_Grade(" 
              << (method == "A" || method == "a" ? "Avg." : "Med.") << ")\n";
    std::cout << "------------------------------------------\n";

    for (const auto &p : students) p.display();

    return 0;
}
