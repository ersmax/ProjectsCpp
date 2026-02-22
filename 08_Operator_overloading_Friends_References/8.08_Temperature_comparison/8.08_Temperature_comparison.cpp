// define NDEBUG        // uncomment this line to disable assertions
#include <iostream>
#include <limits>
#include <cassert>

constexpr double EPSILON = 1e-6;

class Temperature
{
public:
	Temperature() : degrees(0), scale('C') {};
	Temperature(const double degreeValue, const char scaleValue) {set(degreeValue, scaleValue); }
	bool operator ==(const Temperature& anotherTemperature) const;
	//   Precondition: anotherTemperature is a valid Temperature object.
	//   Postcondition: Returns true if the two temperatures have same degrees in Celsius or Fahrenheit

	friend std::istream& operator >>(std::istream& inputStream, Temperature& temperature);
	//   Precondition: inputStream is a valid input stream and temperature is a valid Temperature object.
	//   Postcondition: Reads the temperature value and scale from the input stream and stores them in the temperature object.

	friend std::ostream& operator <<(std::ostream& outputStream, const Temperature& temperature);
	//   Precondition: outputStream is a valid output stream and temperature is a valid Temperature object.
	//   Postcondition: Writes the temperature value in Fahrenheit to the output stream.

private:
	double degrees;
	char scale;
	//   'F' for Fahrenheit or 'C' for Celsius
	void set(double newDegrees, char newScale);
	//   Postcondition: sets the member variables to the values given as arguments;
	const Temperature fahrenheitToCelsius() const;
	//   Precondition: scale is 'F'.
	//   Postcondition: Returns a new Temperature object with the degrees converted to Celsius and scale set to 'C'.

	const Temperature celsiusToFahrenheit() const;
	//   Precondition: scale is 'C'.
	//   Postcondition: Returns a new Temperature object with the degrees converted to Fahrenheit and scale set to 'F'.
};


Temperature temperatureValidation();

int main( )
{
	try
	{
		std::cout << "Enter a valid temperature in F/C (e.g. 18C):\n";
		Temperature temperature1 = temperatureValidation();
		std::cout << "Enter a second temperature in F/C (e.g. 18C):\n";
		Temperature temperature2 = temperatureValidation();
		std::cout << "Enter a third temperature in F/C (e.g. 18C):\n";
		Temperature temperature3 = temperatureValidation();

		std::cout << "Temperature 1: " << temperature1 << '\n';
		std::cout << "Temperature 2: " << temperature2 << '\n';
		std::cout << "Temperature 3: " << temperature3 << '\n';

		if (temperature1 == temperature2)
			std::cout << "First two temperatures are equal\n";
		if (temperature1 == temperature3)
			std::cout << "First and third temperatures are equal\n";
		if (temperature2 == temperature3)
			std::cout << "Last two temperatures are equal\n";
	} catch (const std::invalid_argument& error)
	{
		std::cout << "Error defining the scale: " << error.what() << '\n';
	}
	std::cout << '\n';
	return 0;
}

std::istream& operator >>(std::istream& inputStream, Temperature& temperature)
{
	double newDegrees;
	char newScale;
	inputStream >> newDegrees >> newScale;
	if (newScale != 'F' && newScale != 'C')
	{
		// mark the stream as failed
		inputStream.setstate(std::ios::failbit);
		return inputStream;
	}
	temperature.degrees = newDegrees;
	temperature.scale = newScale;
	return inputStream;
}

std::ostream& operator <<(std::ostream& outputStream, const Temperature& temperature)
{
	if (temperature.scale == 'F')
		outputStream << temperature.degrees << temperature.scale;
	else if (temperature.scale == 'C')
	{
		const Temperature anotherTemperature = temperature.celsiusToFahrenheit();
		outputStream << anotherTemperature.degrees << anotherTemperature.scale;
	}
	return outputStream;
}

bool Temperature::operator ==(const Temperature& anotherTemperature) const
{
	// Preliminary check if two objects have different scale
	assert(this->scale == 'C' || this->scale == 'F');
	assert(anotherTemperature.scale == 'C' || anotherTemperature.scale == 'F');
	const double temp1 = (this->scale == 'F') ? this->degrees : this->celsiusToFahrenheit().degrees;
	const double temp2 = (anotherTemperature.scale == 'F') ? anotherTemperature.degrees : anotherTemperature.celsiusToFahrenheit().degrees;

	return std::abs(temp1 - temp2) < EPSILON;
}

void Temperature::set(const double newDegrees, const char newScale)
{
	if (newScale != 'F' && newScale != 'C')
		throw std::invalid_argument("Degree not in Fahrenheit nor Celsius\n");
	degrees = newDegrees;
	scale = newScale;
}

const Temperature Temperature::fahrenheitToCelsius() const 
{
	if (scale != 'F')
		throw std::invalid_argument("Temperature not in Fahrenheit\n");

	const double newDegrees = (degrees - 32.0) / (9.0 / 5);
	return Temperature(newDegrees, 'C');
}

const Temperature Temperature::celsiusToFahrenheit() const
{
	if (scale != 'C')
		throw std::invalid_argument("Temperature not in Celsius\n");

	const double newDegrees = (9.0 / 5) * degrees + 32.0;
	return Temperature(newDegrees, 'F');
}

Temperature temperatureValidation()
{
	Temperature newTemperature;
	while (true)
	{
		if (!(std::cin >> newTemperature))
		{
			std::cout << "Not a valid temperature\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return newTemperature;
	}
}
