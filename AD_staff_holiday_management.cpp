#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class date  // date class to manage time
{    
	private:
	int day, month, year;

    public:
    date(){}    // default constructor
	
    date(int a , int b, int c)  // initialized constructor
    {
		day = a;
		month = b;
		year = c;		
	}

    void enter_date()   // insert a date member function
    {
        cout << "day: ";
        cin >> day;
        cout << "month: ";
        cin >> month;
        cout << "year: ";
        cin >> year;
        cout << endl;
    }

	void show_date()    // print a date
    {
		cout<<day<<"."<<month<<"."<<year<<"\n";
	}

    int elapsed_years()     // calculate elapsed years from a generic year to the current year
    {
        time_t current_time;    //time_t prebuilt class
        current_time = time(NULL);
        int current_year;
        current_year = 1970 + current_time / 31537970;
        int res;
        res = current_year - year;
        return res;
    }

    int transform_days()     // formula to transform a date into a number of days
    {   // Epoque day one is 01.01.0001
        if (month < 3)
        year--, month += 12;
        return 365*year + year/4 - year/100 + year/400 + (153*month - 457)/5 + day - 306;
    }
};

class employee  // general class employee
{
    public:
    string name, surname;   // these attributes should have been private in a better program
    date birth;
    int available_days, taken_days, remaining_days;

    employee() {};  // default constructor

    void enter_data()   // initialize employee based on user data
    {
        cout << "identify the employee!" << endl;
        cout << "name: ";
        cin >> name;
        cout << "surname: ";
        cin >> surname;
        cout << "date of birth: " << endl;
        birth.enter_date();
    }

    void show_data()    // print employee data
    {
        cout << "name: " << name << ", surname: " << surname << ", remaining holiday days: " << available_days << endl;
        cout << "date of birth: ";
        birth.show_date();
        cout << endl;
    }

    void calc_available_days() // calculate if entitled to 30 or 32 days of holidays
    {
        if (birth.elapsed_years() >= 50)
            available_days = 32;
        else
            available_days = 30;
    }

    void update_available_days()    // update remaining days
    {
        date a,b;
        cout <<"plan your holidays!" << endl << "starting date: ";
        a.enter_date();
        cout << "ending date: ";
        b.enter_date();
        taken_days = b.transform_days() - a.transform_days();
        available_days -= taken_days;
        cout << "remaining days of holiday: " << available_days << endl;;
    }

    ~employee() {};    // destructor method

};

class hourly_employee : public employee     // specialized class hourly employee
{
    private:
    float hourly_wage, worked_hours;

    public:
    hourly_employee() {};  // default constructor

    void enter_data()   // initialize hourly employee based on user data
    {
        cout << "identify the hourly employee!" << endl;
        cout << "name: ";
        cin >> name;
        cout << "surname: ";
        cin >> surname;
        cout << "hourly wage: ";
        cin >> hourly_wage;
        cout << "worked hours: ";
        cin >> worked_hours;
        cout << "date of birth: ";
        birth.enter_date();
    }

    void show_data()    // print hourly employee data
    {
        cout << "name: " << name << ", surname: " << surname << ", remaining holiday days: " << available_days << endl;
        cout << "hourly wage: " << hourly_wage << ", worked hours:" << worked_hours << endl;
        cout << "date of birth: " << endl;
        birth.show_date();
        cout << endl;
    }

    ~hourly_employee() {}; // destructor method

};

class salaried_employee : public employee   // specialized class salaried employee
{
    private:
    float salary;

    public:
    salaried_employee() {};  // default constructor

    void enter_data()   // initialize salaried employee based on user data
    {
        cout << "identify the salaried employee!" << endl;
        cout << "name: ";
        cin >> name;
        cout << "surname: ";
        cin >> surname;
        cout << "salary: ";
        cin >> salary;
        cout << "date of birth: " << endl;
        birth.enter_date();
    }

        void show_data()    // print salaried employee data
    {
        cout << "name: " << name << ", surname: " << surname << ", remaining holiday days: " << available_days << endl;
        cout << "salary: " << salary << endl;
        cout << "date of birth: ";
        birth.show_date();
        cout << endl;
    }

    ~salaried_employee() {}; // destructor method  
};

class manager : public employee     // specialized class manager
{
    private:
    float profit_sharing;

    public:
    manager() {};  // default constructor

    void enter_data()   // initialize manager based on user data
    {
        cout << "identify the manager!" << endl;
        cout << "name: ";
        cin >> name;
        cout << "surname: ";
        cin >> surname;
        cout << "profit sharing: ";
        cin >> profit_sharing;
        cout << "date of birth: " << endl;
        birth.enter_date();
    }

        void show_data()    // print manager data
    {
        cout << "name: " << name << ", surname: " << surname << ", remaining holiday days: " << available_days << endl;
        cout << "profit sharing: " << profit_sharing << endl;
        cout << "date of birth: ";
        birth.show_date();
        cout << endl;
    }

    ~manager() {}; // destructor method
    
};

int main()
{
    int select;     // to navigate the menu
    int tot_employees = 0; // rudimental process to count 500 employees
    employee employees[500];  // array of max 500 employees
    employee emp;   // instances to be initialized and inserted into the array
    hourly_employee hour;
    salaried_employee sal;
    manager man;
    
    do
    {
        cout << "--- MENU ---" << endl;
        cout << "--- INSERT ALL DATES AS DD.MM.YYYY TO NOT RAISE ERRORS ---" << endl;
        cout << "[1] create employee" << endl;
        cout << "[2] delete employee" << endl;
        cout << "[3] enter holiday time" << endl;
        cout << "[4] search for an employee" << endl;
        cout << "[5] show all employees" << endl;
        cout << "[0] terminate" << endl;
        cout << endl << "Please select: ";
        cin >> select;
        switch(select)
        {
        case 1:     // add different type of employees
            {
                int choice;
                cout << "Insert a new employee:" << endl;
                cout << "digit 1 per employee, 2 per hourly employee, 3 per salaried employee and 4 per manager" << endl;
                cin >> choice;
                if (choice==1)
                {
                    emp.enter_data();   // initialize new employee
                    employees[tot_employees] = emp;     // insert new employee in the array
                    employees[tot_employees].calc_available_days();     // calculate entitled holiday days
                    tot_employees++;    // increase count of employees
                    cout << "the employee has been added..." << endl;
                }
                else if (choice==2)
                {
                    hour.enter_data();
                    employees[tot_employees] = hour;
                    employees[tot_employees].calc_available_days();     // calculate entitled holiday days
                    tot_employees++;
                    cout << "the hourly employee has been added..." << endl;
                }
                else if (choice==3)
                {
                    sal.enter_data();
                    employees[tot_employees] = sal;
                    employees[tot_employees].calc_available_days();     // calculate entitled holiday days
                    tot_employees++;
                    cout << "the salaried employee has been added..." << endl;
                }
                else if (choice==4)
                {
                    man.enter_data();
                    employees[tot_employees] = man;
                    employees[tot_employees].calc_available_days();     // calculate entitled holiday days
                    tot_employees++;
                    cout << "the manager has been added..." << endl;
                }
                else
                {
                    cout << "sorry my friend, you did not select the correct number... Try again!" << endl;
                }
                break;
            }
        case 2:     // delete an employee based on his index and shift the array to occupy the empty index
        /* I have only one question, why did not we do vectors before this exercise? */
            {
                int n;
                cout << "You creaded " << tot_employees-1 << " employees" << endl;
                cout << "Select a number from 0 to " << tot_employees-1 << " and the program will delete that employee" << endl;
                cout << "select your number: ";
                cin >> n;
                
                for (int i = n; i < 500; ++i)
                    employees[i] = employees[i + 1]; // copy next element left

                cout << endl << "employee " << n << " terminated" << endl;
                
                tot_employees--; //reduce the count of the employees
                break;
            }
        case 3:
            {
                int n;
                cout << "You creaded " << tot_employees-1 << " employees" << endl;
                cout << "Select a number from 0 to " << tot_employees-1 << " and the program will add holidays for that employee" << endl;
                cout << "select your number: ";
                cin >> n;
                
                employees[n].update_available_days();   // call memeber function to plan holidays
                break;
            }
        case 4:
            {
                int n;
                cout << "You creaded " << tot_employees-1 << " employees" << endl;
                cout << "Select a number from 0 to " << tot_employees-1 << " and the program will show the remaing days of holidays for that employee" << endl;
                cout << "select your number: ";
                cin >> n;
                
                employees[n].show_data();   // call memeber function to show employee data and remaining holiday days
                break;
            }
        case 5:     // print array of the employees with remaining holidays
            {
                cout << "here you have the data of all the inserted employees... SUPER" << endl << endl;
                for (int i=0; i<tot_employees; i++) 
                    employees[i].show_data();
                break;
            }
        case 0:     // terminate the program
            {
                cout << endl << "Goodbye" << endl;
                return 0;
            }
        default:    // check what you digit
            {
                cout << endl << "Incorrect input!" << endl;
                cout << "you have insterted " << tot_employees << " employees" << endl << endl;
            }
        }
    }while(select!=0);

    return 0;
}