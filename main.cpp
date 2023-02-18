/***********************************************************************
Matr.-Nr:   3154171
Nachname/Surname:    Senhaby
Vorname/Given name:    Mohamed
Uni-Email:   mohamed.senhaby@stud.uni-due.de
Studiengang/Course of studis:    Bachelor of Science/Computer Engineering, ISE, Vert. Software
***********************************************************************/







#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;


//1
struct station
{
    string name_of_line;
    int time_of_travel;
    station* next;
    station* prev;
    station* connection;
};



station* head_2;


struct station* generate_metro_line(int line_number, int stations_number)
{
    station* temp = nullptr;
    for (int x = stations_number; x >= 1; x--)
    {
        station* newstation = new station();
        newstation->name_of_line = "line " + to_string(line_number) + " station " + to_string(x);
        newstation->connection = nullptr;
        if (x == stations_number)
        {
            newstation->time_of_travel = 0;
        }
        else
        {
            newstation->time_of_travel = (rand() % 5) + 1;
        }

        newstation->next = temp;

        if (temp != nullptr)
            temp->prev = newstation;

        temp = newstation;
        if (x == 1)
            return newstation;
    }
};



void output(station* head)
{
    cout << head->name_of_line;
    if (head->time_of_travel != 0)
        cout << " : time to next: " << head->time_of_travel;
    else
        cout << " End station ";

    if (head->connection != nullptr)
        cout << " (here connection to " << head->connection->name_of_line << " )";

    cout << " \n";
}

void output_line(station* head_2)
{
    station* temp_2 = head_2;
    while (temp_2 != NULL)
    {
        output(temp_2);
        temp_2 = temp_2->next;
    }
}

struct Train
{
    string metro_name;
    int time_to_next;
    bool destination;
    station* next_station;
};

void init(Train& train, string metro_name, station* intial_station)
{
    train.metro_name = metro_name;
    train.next_station = intial_station;
    train.destination = true;
    train.time_to_next = 0;
}

void output(Train& train)
{
    if (train.time_to_next == 0)
        cout << train.metro_name << " : stop at: " << train.next_station->name_of_line << endl;
    else
    {
        if (train.destination)
            cout << train.metro_name << " : " << train.time_to_next << " minute(s) to " << train.next_station->name_of_line << endl;
        else
            cout << train.metro_name << " : " << train.time_to_next << " minute(s) to " << train.next_station->name_of_line << "(on way back)" << endl;
    }
}

void output_all_trains(Train arr[], int simulation, int length)
{
    cout << " time simulation: " << simulation << " min " << "\n";


    for (int x = 0; x < length; x++)
    {
        output(arr[x]);
    }
}


double get_km_of_line(station* head_2, double avarage_speed)
{
    double sum = 0;
    double length_of_line;
    station* temp = head_2;
    while (temp->next != NULL)
    {
        sum += 2 + (2 * temp->time_of_travel);
        temp = temp->next;
    }

    sum = sum / 60;
    length_of_line = sum * avarage_speed;

    return length_of_line;
}

int main()
{
    int sim = 0;
    char chose;
    int line_number;
    int line_number2;
    int station_number;
    int station_number2;
    double avarage_speed;
    unsigned int sv;
    station* metro[2];
    station* connection_1 = nullptr;
    station* connection_2 = nullptr;
    station* temp = nullptr;
    Train train[2];


    cout << " seed value for initialisation of random number generator (try 3, 5, 7, ...)? ";
    cin >> sv;
    srand(sv);
    cout << " input number of stations of line 1: ";
    cin >> station_number;
    metro[0] = generate_metro_line(1, station_number);
    cout << " input number of stations of line 2: ";
    cin >> station_number;
    metro[1] = generate_metro_line(2, station_number);
    init(train[0], "train 1", metro[0]);
    init(train[1], "train 2", metro[1]);



    do {
        cout << "e end" << endl
            << "c connection option of lines" << endl
            << "k total km complete outward and return ride of line" << endl
            << "l line output" << endl
            << "t train output" << endl
            << "1 simulate 1 minute" << endl
            << ">>";
        cin >> chose;
        switch (chose)
        {
        case 'l':
        {
            cout << " which line? ";
            cin >> line_number;
            output_line(metro[line_number - 1]);
            break;
        }

        case 't':
        {

            output_all_trains(train, sim, sizeof(train) / sizeof(*train));

            break;
        };

        case '1':
        {
            sim++;
            for (int x = 0; x < (sizeof(train) / sizeof(*train)); x++)
            {
                if (train[x].time_to_next > 0)
                    train[x].time_to_next--;
                else
                {
                    if (train[x].destination == true && train[x].next_station->next == 0)
                        train[x].destination = false;
                    else if (train[x].destination == false && train[x].next_station->prev == 0)
                        train[x].destination = true;

                    if (train[x].destination == true)
                    {
                        train[x].next_station = train[x].next_station->next;
                        train[x].time_to_next = train[x].next_station->prev->time_of_travel;
                    }
                    else if (train[x].destination == false)
                    {
                        train[x].next_station = train[x].next_station->prev;
                        train[x].time_to_next = train[x].next_station->time_of_travel;
                    }
                }
            }
            output_all_trains(train, sim, sizeof(train) / sizeof(*train));
            break;
        }
        case 'k':
        {
            cout << "which line? ";
            cin >> line_number;
            cout << " average speed in km/h? ";
            cin >> avarage_speed;
            cout << " length of line: " << get_km_of_line(metro[line_number - 1], avarage_speed) << endl;
            break;
        }

        case 'c':
        {
            cout << " connection of which two line numbers? ";
            cin >> line_number >> line_number2;
            cout << " connection of which stations on line " << line_number << " ? ";
            cin >> station_number;
            cout << " connection of which stations on line " << line_number2 << " ? ";
            cin >> station_number2;

            temp = metro[line_number - 1];

            for (int x = 1; x < station_number; x++)
            {
                temp = temp->next;
            }
            connection_1 = temp;

            temp = metro[line_number2 - 1];
            for (int x = 1; x < station_number2; x++)
            {
                temp = temp->next;
            }
            connection_2 = temp;

            connection_1->connection = connection_2;
            connection_2->connection = connection_1;

            break;
        }



        default:
        {
            break;
        }
        }


    } while (chose != 'e');


};