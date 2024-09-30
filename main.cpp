/*

Program 1: Program that assigns passenger seats in an airplane.
Author Chanelle Russell 
Date Created: 9/11/2024
*/

#include <iostream>
#include <vector>
#include <stdexcept> // Include standard exceptions

using namespace std;

// Function prototype
void displayChart(const vector<vector<char>>& seatChart);
void assign_seat(vector<vector<char>>& seatChart, int rowChoice, int seatChoice, int rows, int seatsPerRow);

int main() 
{
    int rows, seatsPerRow;
    
    // Step 1: Get the number of rows and seats per row
    cout << "Enter the number of rows in the plane: ";
    cin >> rows;
    cout << "Enter the number of seats per row: ";
    cin >> seatsPerRow;
    
    // Step 2: Initialize the seating chart
    vector<vector<char>> seatChart(rows, vector<char>(seatsPerRow, '0')); // '0' represents available seats

    // Display initial seat chart
    displayChart(seatChart);

    int rowChoice, seatChoice;
    char moreSeats = 'Y';
    int totalSeats = rows * seatsPerRow;
    int seatsTaken = 0;
    
    while (moreSeats == 'Y' || moreSeats == 'y') 
    {
        try 
        {
            // Step 3: Ask the user for seat choice
            cout << "Which row would you like to sit in (1-" << rows << ")? ";
            cin >> rowChoice;
            cout << "Which seat in row " << rowChoice << " would you like (1-" << seatsPerRow << ")? ";
            cin >> seatChoice;

            // Step 4: Attempt to assign the seat
            assign_seat(seatChart, rowChoice, seatChoice, rows, seatsPerRow);
            seatsTaken++;

            cout << "Seat assigned successfully!\n";
        } 
        catch (const out_of_range& e) 
        {
            // Catch out_of_range exception for invalid seat selection
            cout << "Error: " << e.what() << " Please select a valid seat.\n";
        }
        catch (const invalid_argument& e) 
        {
            // Catch invalid_argument exception for already taken seat
            cout << "Error: " << e.what() << " Please choose a different seat.\n";
        }
        
        // Step 5: Ask if they want to reserve another seat
        cout << "Would you like to book another seat? (Y/N): ";
        cin >> moreSeats;

        // Display updated seat chart
        displayChart(seatChart);
    }
    
    // Step 6: Display the final seating chart and number of available seats
    int seatsAvailable = totalSeats - seatsTaken;
    cout << "Final Seating Chart:\n";
    displayChart(seatChart);
    cout << "Total seats available: " << seatsAvailable << endl;
    cout << "Seats taken: " << seatsTaken << endl;

    return 0;
}

void displayChart(const vector<vector<char>>& seatChart) 
{
    cout << "Seat Chart (0: Available, X: Unavailable):\n";
    for (int i = 0; i < seatChart.size(); ++i) 
    {
        cout << "Row " << i + 1 << ": ";
        for (char seat : seatChart[i]) 
        {
            cout << seat << " ";
        }
        cout << endl;
    }
}

void assign_seat(vector<vector<char>>& seatChart, int rowChoice, int seatChoice, int rows, int seatsPerRow) 
{
    if (rowChoice < 1 || rowChoice > rows || seatChoice < 1 || seatChoice > seatsPerRow) 
    {
        // Throw out_of_range exception for invalid seat selection
        throw out_of_range("Seat selection out of bounds.");
    }

    if (seatChart[rowChoice - 1][seatChoice - 1] != '0') 
    {
        // Throw invalid_argument exception if the seat is already taken
        throw invalid_argument("Seat is already taken.");
    }

    // If no exceptions, assign the seat
    seatChart[rowChoice - 1][seatChoice - 1] = 'X';
}
