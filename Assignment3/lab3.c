#include <stdio.h>
#include <stdlib.h>

struct Employee 
{
    // vtable is a table of function pointers
    void **vtable;
    int age;
};

struct HourlyEmployee 
{
    void **vtable;
    int age;
    double hourly_rate;
    double hours;
};

struct CommissionEmployee 
{
    void **vtable;
    int age;
    double sales_amount;
};

struct SeniorSalesman 
{
    void **vtable;
    int age;
    double sales_amount;
};

// Function for employee to say their hourly rate per hour
void Speak_Hourly(struct Employee *employee) 
{
    struct HourlyEmployee *hourlyEmployee = (struct HourlyEmployee *) employee;
    
    // Display hourly rate
    printf("I work for %.2lf dollars per hour :(\n", hourlyEmployee->hourly_rate);
}

// Takes an Employee pointer and returns the employee's total pay
double GetPay_Hourly(struct Employee *employee) 
{
    struct HourlyEmployee * hourlyEmployee = (struct HourlyEmployee *) employee; 
    return hourlyEmployee->hourly_rate * hourlyEmployee->hours;
}

// Function for commissionEmployees and seniorSalesman to say their commission from sales.
void Speak_Commission(struct Employee *employee) 
{
    struct CommissionEmployee *commissionEmployee = (struct CommissionEmployee *) employee;
    
    // Display sales amount
    printf("I made commission on %.2lf dollars from sales!\n", commissionEmployee->sales_amount);
}

// getPay() function for CommissionEmployees
double GetPay_Commission(struct Employee *employee) 
{
  struct CommissionEmployee * commissionEmployee = (struct CommissionEmployee *) employee; 
  return (10 * commissionEmployee->sales_amount) + 40000;
}

// getPay() function for SeniorSalesman
double GetPay_Senior(struct Employee *employee) 
{
  struct SeniorSalesman * seniorCommission = (struct SeniorSalesman *) employee; 
  return 0.0;
}

// "table" array that contains 2 pointers to speak() and getPay() for each employee
void *Vtable_HourlyEmployee[2] = {Speak_Hourly, GetPay_Hourly};
void *Vtable_CommissionEmployee[2] = {Speak_Commission, GetPay_Commission};
void *Vtable_SeniorCommission[1] = {GetPay_Senior};

// Takes a HourlyEmployee pointer and initializes it to their default values
struct HourlyEmployee Construct_Hourly(struct HourlyEmployee *hourlyEmployee) 
{
    hourlyEmployee->vtable = Vtable_HourlyEmployee;
    hourlyEmployee->age = 0;
    hourlyEmployee->hourly_rate = 0;
    hourlyEmployee->hours = 0;
}

// Take CommissionEmployee pointer and initialize it.
struct CommissionEmployee Construct_Commission(struct CommissionEmployee *commissionEmployee) 
{
    commissionEmployee->vtable = Vtable_CommissionEmployee;
    commissionEmployee->age = 0;
    commissionEmployee->sales_amount = 0;
}

// Take SeniorSalesMan pointer and initialize it.
struct SeniorSalesman Construct_Senior(struct SeniorSalesman *seniorSalesman) 
{
    seniorSalesman->vtable = Vtable_SeniorCommission;
    seniorSalesman->age = 0;
    seniorSalesman->sales_amount = 0;
}

int main() 
{
    struct Employee *employee;
    int menuChoice = 0;
    int age = 0;

    struct HourlyEmployee *pHourlyEmployee = (struct HourlyEmployee *) malloc(sizeof(struct HourlyEmployee));
    struct CommissionEmployee *pCommissionEmployee = (struct CommissionEmployee *) malloc(sizeof(struct CommissionEmployee));
    struct SeniorSalesman *pSeniorSalesman = (struct SeniorSalesman *) malloc(sizeof(struct SeniorSalesman));

    // Display the selections. Validate the selection/
    printf("Choose an employee: \n1. Hourly Employee \n2. Commission Employee \n3. Senior Salesman \n4. Quit");
    scanf("%d", &menuChoice);

    printf("How old is the employee?");
    scanf("%d", &age);

    if (menuChoice == 1)
    {  
        int pay_rate = 0;
        int hours = 0;

        printf("What is the employee's pay rate?");
        scanf("%d", &pay_rate);

        printf("How many hours does the employee work?");
        scanf("%d", &hours);

        Construct_Hourly(pHourlyEmployee);

        pHourlyEmployee->hourly_rate = pay_rate;
        pHourlyEmployee->hours = hours;

        employee = (struct Employee *) pHourlyEmployee;
    }
    else if (menuChoice == 2)
    {
        int sale_amount = 0;
        printf("What is the employee's amount of sales?");
        scanf("%d", sale_amount);

        Construct_Commission(pCommissionEmployee);

        pCommissionEmployee->sales_amount = sale_amount;

        employee = (struct Employee *) pCommissionEmployee;
    }
    else if (menuChoice == 3)
    {
        int sale_amount = 0;
        printf("What is the employee's amount of sales?");
        scanf("%d", sale_amount);

        Construct_Senior(pSeniorSalesman);

        pSeniorSalesman->sales_amount = sale_amount;

        employee = (struct Employee *) pSeniorSalesman;
    }
    else
    {
        printf("Done!");
    }
    
    employee->age = age;

    ((void (*)(struct Employee *)) employee->vtable[0])((struct Employee *) employee);

    return 0;
}