Give the definition of two classes, Patient and Billing, whose objects are records
for a clinic. Patient will be derived from the class Person given in Programming
Project 14.4. A Patient record has the patient’s name (inherited from
the class Person) and primary physician, of type Doctor defined in Programming
Project 14.3. A Billing object will contain a Patient object and a Doctor object,
and an amount due of type double. Be sure your classes have a reasonable complement
of constructors and accessor methods, an overloaded assignment operator,
and a copy constructor. First write a driver program to test all your methods, then
write a test program that creates at least two patients, at least two doctors, at least
two Billing records, then prints out the total income from the Billing records.

---

## Program Logic
Overall, the program models a simple clinic billing system where each `Patient` has a primary `Doctor`, each `Billing` ties a patient to a doctor and an amount due, and the driver builds two billing records and reports their total income.

- `Person` (`14_05_Person`)
  - Base class for people in the clinic, storing a single field `name`.
  - Default constructor initializes the name to `"No name"`.
  - `operator>>` reads and validates the full name using `myNamespaceValidation::readName` from `14_04_Input_Validation`.
  - `operator<<` prints the full name.

- `Doctor` (`14_03_Doctor`)
  - Derived from `SalariedEmployee` → `Employee`.
  - Adds `specialty` and `fee` (office visit fee).
  - `readData()` interactively reads name, SSN, weekly salary, specialty (from a fixed list) and visit fee.
  - Accessors `getSpecialty()` and `getFee()` expose the specialty and fee.

- `Patient` (`14_05_Patient`)
  - Derived from `Person` and contains a `Doctor` member `physician` representing the primary physician.
  - Default constructor: patient name and physician name start as `"No name"`.
  - Constructor `Patient(const Doctor& aDoctor, const std::string& theName = "No name")` allows creating a patient with a given doctor and optional name.
  - `operator>>`:
    - If the patient name is `"No name"`, it reads the patient name via the `Person` input operator.
    - If the physician's name is `"No name"`, it calls `physician.readData()` to read doctor data.
  - `operator<<` prints the patient (via `Person`) and then the doctor name, specialty, and fee.

- `Billing` (`14_05_Billing`)
  - Represents a billing record for a visit.
  - Contains:
    - A `Patient` (`aPatient`).
    - A `Doctor` (`aDoctor`) copied from the patient's primary physician or from a given doctor.
    - A `double amountDue` representing the visit fee including VAT.
  - Default constructor initializes an empty patient, doctor, and `amountDue` to `0`.
  - Constructor `Billing(const Doctor& theDoctor, const std::string& theName = "No name")` builds a `Patient` from the given doctor and patient name, copies the doctor, and computes the amount due.
  - `setAmountDue()` sets `amountDue` to `doctor fee * (1 + VAT)`, using a constant `VAT = 0.22`.
  - `operator>>` reads a `Patient`, copies its primary physician into `aDoctor`, and recalculates `amountDue`.
  - `operator<<` prints the patient details, doctor data, and the total amount due.

- `main` (`14_05_Application`)
  - Creates the first patient `patient1` using the default constructor and reads their data (name and primary physician) from the user.
  - Creates a second doctor `doctor2`, reads its data with `readData()`, then creates a second patient `patient2` whose primary physician is `doctor2`.
  - Creates a first billing record `aBill(doctor2, patient1.getName())`, which associates `doctor2` with `patient1`'s name and computes the visit amount including VAT, then prints it.
  - Creates a second billing record `aBill2` by reading patient and doctor information from input via `operator>>`, then prints it.
  - Computes and prints the grand total as `aBill.getAmountDue() + aBill2.getAmountDue()`.

