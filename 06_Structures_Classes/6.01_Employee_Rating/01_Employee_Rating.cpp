/*
Write a rating program for a software development firm with the following rating
policies.
a. Core competency – This parameter measures an employee’s involvement, innovation,
and passion toward their assigned tasks, and is graded on 10 points.
b. Performance evaluation – This parameter measures an employee’s performance
over the year, and is graded on 30 points.
c. Ideation – An employee is measured on their patent submissions, patents
awarded, technical papers presented, etc. and is graded on 10 points.
d. The performance evaluation accounts for 50% of an employee’s final rating,
core competency accounts for 30%, and ideation accounts for 20%.
The total points obtained by an employee are summed up and normalized. Employees
with points of 80 or more are rated a 1, those between 60 to 79 are rated a
2, those between 50 to 59 are rated a 3, and those less than 50 are rated a 4.
The program will read an employee’s points against the three criteria and output
the total points obtained on a scale of 100, and the final rating point. Define and
use a structure for the employee records.
*/

#include <iostream>
#include <limits>
#include <iomanip>

constexpr double MAX_PERFORMANCE = 30.0;
constexpr double MAX_COMPETENCY = 10.0;
constexpr double MAX_IDEATION = 10.0;
constexpr double WEIGHT_PERFORMANCE = 0.50;
constexpr double WEIGHT_COMPETENCY = 0.30;
constexpr double WEIGHT_IDEATION = 0.20;

struct Skills
{
	double coreCompetency = 0;
	double performance = 0;
	double ideation = 0;
};

bool setSkills(Skills& employee);
//   Postcondition: prompts user to input skills values for the employee structure.

double inputData();
//   Postcondition: reads and returns a double value from user input.

double normalize(const Skills& employee);
//   Postcondition: normalizes and returns the total score of the employee based on weights.

int rateEmployee(double total);
//   Precondition: employee total score is between 0 and 100.
//   Postcondition: returns the rating of the employee based on total score.

void printResults(double total, int rate);
//	 Precondition: total is the normalized score and rate is the employee rating.	
//   Postcondition: prints the total score and rating of the employee.

int main( )
{
	Skills employee;

	if (!setSkills(employee)) return -1;
	const double totalScore = normalize(employee);
	const int rate = rateEmployee(totalScore);
	printResults(totalScore, rate);

	std::cout << "\n";
	return 0;
}

bool setSkills(Skills& employee)
{
	double coreCompetency, performanceEvaluation, ideation;
	while (true)
	{
		std::cout << "Enter core competency up to 10 points or -1 to exit:\n";
		coreCompetency = inputData();
		if (coreCompetency == -1)	return false;
		if (coreCompetency < 0 || coreCompetency > MAX_COMPETENCY) continue;
		break;
	}
	while (true)
	{
		std::cout << "Enter performance evaluation up to 30 points or -1 to exit:\n";
		performanceEvaluation = inputData();
		if (performanceEvaluation == -1)	return false;
		if (performanceEvaluation < 0 || performanceEvaluation > MAX_PERFORMANCE) continue;
		break;
	}
	while (true)
	{
		std::cout << "Enter Ideation up to 10 points or -1 to exit:\n";
		ideation = inputData();
		if (ideation == -1)	return false;
		if (ideation < 0 || ideation > MAX_IDEATION) continue;
		break;
	}
	employee.coreCompetency = coreCompetency;
	employee.performance = performanceEvaluation;
	employee.ideation = ideation;
	return true;
}

double inputData()
{
	double value;
	if (!(std::cin >> value)) {
		std::cout << "Wrong input\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return value;
}

double normalize(const Skills& employee)
{
	const double normalizedCompetency = (employee.coreCompetency / MAX_COMPETENCY) * WEIGHT_COMPETENCY * 100.0;
	const double normalizedPerformance = (employee.performance / MAX_PERFORMANCE) * WEIGHT_PERFORMANCE * 100.0;
	const double normalizedIdeation = (employee.ideation / MAX_IDEATION) * WEIGHT_IDEATION * 100.0;
	return (normalizedCompetency + normalizedPerformance + normalizedIdeation);
}

int rateEmployee(const double total)
{
	if (total >= 80.0)	return 1;
	if (total >= 60.0)	return 2;
	if (total >= 50.0)	return 3;
	return 4;
}

void printResults(const double total, const int rate)
{
	std::cout << std::fixed << std::showpoint << std::setprecision(1);
	std::cout << "Employee's total (out of 100): " << total << "\n";
	std::cout << "Employee's rating: " << rate << "\n";
}
