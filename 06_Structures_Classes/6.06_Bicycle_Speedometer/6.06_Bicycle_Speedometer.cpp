#include <iostream>
#include <limits>
#include <iomanip>

class BicycleSpeedometer
{
public:
	void setDistance();
	void setTime();
	double getDistance() const;
	int getTime() const;
	double avgSpeed() const;
	//   Postcondition: return average speed in miles per hour
private:
	double distance = 0;
	int time = 0;
	static double inputValidation();
	//   Postcondition: return a valid positive double input from user
	double minuteToHour() const;
	//   Postcondition: return time converted from minutes to hours
};

int main( )
{
	BicycleSpeedometer runner1;
	std::cout << std::fixed << std::showpoint << std::setprecision(1);
	std::cout << "Set distance for runner: \n";
	runner1.setDistance();
	std::cout << "Set time for runner: \n";
	runner1.setTime();
	std::cout << "Average speed: " << runner1.avgSpeed();
	std::cout << "\n";
	return 0;
}

void BicycleSpeedometer::setDistance()
{
	std::cout << "Enter distance (in miles):\n";
	distance = inputValidation();
}

double BicycleSpeedometer::getDistance() const
{
	return distance;
}

void BicycleSpeedometer::setTime()
{
	std::cout << "Enter time (in minutes):\n";
	time = static_cast<int>(inputValidation());
}

int BicycleSpeedometer::getTime() const
{
	return time;
}

double BicycleSpeedometer::avgSpeed() const
{
	return (distance / minuteToHour());
}


double BicycleSpeedometer::inputValidation()
{
	double miles;
	while (true)
	{
		while (!(std::cin >> miles))
		{
			std::cout << "Invalid\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		if (miles > 0) break;
		std::cout << "Value cannot be negative or 0\n";
	}
	return miles;
}

double BicycleSpeedometer::minuteToHour() const
{
	return (time / 60.0);
}
