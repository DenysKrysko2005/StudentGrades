#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>

class Person {
private:
    std::string name;
    std::string surname;
    std::vector<double> homework;
    double exam;
    double finalGrade;

public:
    // Constructor
    Person(std::string n="", std::string s="") : name(n), surname(s), exam(0), finalGrade(0) {}

    // Copy constructor
    Person(const Person &p) {
        name = p.name;
        surname = p.surname;
        homework = p.homework;
        exam = p.exam;
        finalGrade = p.finalGrade;
    }

    // Destructor
    ~Person() {}

    // Assignment operator
    Person& operator=(const Person &p) {
        if (this == &p) return *this;
        name = p.name;
        surname = p.surname;
        homework = p.homework;
        exam = p.exam;
        finalGrade = p.finalGrade;
        return *this;
    }

    // Input method
    void input() {
        std::cout << "Enter name and surname: ";
        std::cin >> name >> surname;

        double hwScore;
        homework.clear();
        std::cout << "Enter homework scores (enter -1 to stop): ";
        while (true) {
            std::cin >> hwScore;
            if (hwScore == -1) break;
            homework.push_back(hwScore);
        }

        std::cout << "Enter exam score: ";
        std::cin >> exam;
    }

    // Calculate final grade (average)
    void calculateFinalGrade() {
        double hwAvg = std::accumulate(homework.begin(), homework.end(), 0.0) / homework.size();
        finalGrade = 0.4 * hwAvg + 0.6 * exam;
    }

    // Output method
    void display() const {
        std::cout << std::setw(10) << name
                  << std::setw(10) << surname
                  << std::setw(10) << std::fixed << std::setprecision(2)
                  << finalGrade << "\n";
    }
};

int main() {
    std::vector<Person> students;
    int n;
    std::cout << "How many students? ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        Person p;
        p.input();
        p.calculateFinalGrade();
        students.push_back(p);
    }

    std::cout << "\nName      Surname     Final_Point(Aver.)\n";
    std::cout << "--------------------------------------\n";
    for (const auto &p : students) p.display();

    return 0;
}
