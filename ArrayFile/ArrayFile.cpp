#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;

typedef double *pDouble;

const int max_size = 100;

// Input array size from the console
int ConsoleInputSizeArray()
{
    int size = 0;
    do
    {
        cout << "Array size (max " << max_size << ") ";
        cin >> size;
    } while (size <= 0 || size >= max_size); // Repeat the loop under these conditions
    return size;
}

// Input array elements from the console
int ConsoleInputArray(double A[])
{
    int size = ConsoleInputSizeArray();
    for (int i = 0; i < size; i++)
    {
        cout << "Array[" << i << "] ";
        cin >> A[i];
    }
    return size;
}

// Generate random array elements
int InputRndArray(double A[])
{
    int size = ConsoleInputSizeArray();
    double r1 = 0, r2 = 0;
    srand(time(nullptr)); // Random generator starting value

    for (int i = 0; i < size; i++)
    {
        // Numbers -100-100
        r1 = rand() % 201 - 100;
        r2 = rand() % 201 - 100;
        A[i] = 100.0 * r1    // Calculate random element
               / (1.0 + r2); // Prevent division by 0
        cout << A[i] << " ";
    }
    return size;
}

// Write array elements to a text file
void WriteArrayTextFile(int n, double *arr, const char *fileName)
{
    ofstream fout(fileName);
    if (fout.fail()) // Check for failure
        return;
    fout << n << endl;          // Write size to file
    for (int i = 0; i < n; i++) // Write elements to file
        fout << arr[i] << "   ";
    fout.close();
}

// Read array elements from a text file
int ReadArrayTextFile(int n, double *arr, const char *fileName)
{
    int size;
    ifstream fin(fileName);
    if (fin.fail()) // Check for failure
        return 0;
    fin >> size; // Read size from file
    if (size <= 0)
        return 0;
    if (size > n)
        size = n;
    for (int i = 0; i < n; i++) // Read elements from file
        fin >> arr[i];
    fin.close();
    return size;
}

// Write array elements to a binary file
void WriteArrayBinFile(int n, double *arr, const char *fileName)
{
    ofstream bfout(fileName, ios_base::binary);
    if (bfout.fail()) // Check for failure
        return;
    bfout.write((const char *)&n, sizeof(int));                  // Write size to file
    streamsize cn = static_cast<streamsize>(n) * sizeof(double); // Calculate the number of bytes to write for the array
    bfout.write((const char *)arr, cn);                          // Write array to file
    bfout.close();
}

// Read array elements from a binary file
int ReadArrayBinFile(int n, double *arr, const char *fileName)
{
    int size = 0;
    ifstream bfin(fileName, ios_base::binary);
    if (bfin.fail()) // Check for failure
        return 0;
    bfin.read((char *)&size, sizeof(int)); // Read size from file
    if (size <= 0)
        return 0;
    if (size > n)
        size = n;
    bfin.read((char *)arr, static_cast<std::streamsize>(size) * sizeof(double)); // Read array from file
    bfin.close();
    return size;
}

// Display the main menu
void ShowMainMenu()
{
    cout << "    Main Menu  \n";
    cout << "    1.  Task 1  \n";
    cout << "    2.  Task 2  \n";
    cout << "    3.  Task 3  \n";
}

// Display the menu for selecting input method
void MenuInput()
{
    cout << "    Menu Input   \n";
    cout << "    1.  Console all \n";
    cout << "    2.  Console - size, array - random \n";
    cout << "    3.  Write to text file, read from text file \n";
    cout << "    4.  Write to binary file, read from binary file \n";
    cout << "    5.  Exit \n";
}

/*
Задано одновимірний масив А розміру N.
Вилучити всі від’ємні елементи масиву.
*/

// Remove negative elements from an array
void RemoveNegative(double A[], int &size)
{
    int newSize = 0;
    for (int i = 0; i < size; i++)
    {
        if (A[i] >= 0)
        {
            A[newSize] = A[i]; // Copy element to new variable if non-negative
            newSize++;         // Increment size
        }
    }
    size = newSize; // Change to a new size variable
}

/*
Знайти номер першого максимального значення серед від’ємних елементів,
розташованих до першого елемента, рівного Т.
*/

// Find the index of the first maximum negative element before T
int FindFirstMaxNegativeIndex(double A[], int size, double T)
{
    int max_index = -1;
    double maxNegative = -1000000;
    for (int i = 0; i < size; i++)
    {
        if (A[i] < 0 && A[i] > maxNegative && i < T)
        {
            max_index = A[i]; // Update max negative
            max_index = i;    // Update max negative index
        }
    }
    return max_index;
}

/*
Задано a, b координати школи та (x1, y1),(x2, y2),..., (xn, yn)(n<=100) - координати будинків.
Розробити програму, яка обчислює середню віддаль від будинків до школи.
*/

// Distance between two points
double Distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main()
{
    ShowMainMenu();

    int choice;

    do
    {
        cout << "Choice ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Task 1
        {
            MenuInput();
            int inputChoice;
            do
            {
                cout << "Choice ";
                cin >> inputChoice;

                switch (inputChoice)
                {
                case 1: // Console all
                {
                    double A[max_size];
                    int size = ConsoleInputArray(A);
                    RemoveNegative(A, size);
                    for (int i = 0; i < size; i++)
                    {
                        cout << A[i] << " ";
                    }
                    cout << endl;
                    inputChoice = 5;
                    break;
                }
                case 2: // Console size & random array
                {
                    double A[max_size];
                    int size = InputRndArray(A);
                    cout << endl;
                    RemoveNegative(A, size);
                    for (int i = 0; i < size; i++)
                    {
                        cout << A[i] << " ";
                    }
                    cout << endl;
                    inputChoice = 5;
                    break;
                }
                case 3: // Write to file, read from file
                {
                    double A[max_size];
                    int size = ConsoleInputArray(A);
                    WriteArrayTextFile(size, A, "1.txt");
                    size = ReadArrayTextFile(max_size, A, "1.txt");
                    RemoveNegative(A, size);
                    for (int i = 0; i < size; i++)
                    {
                        cout << A[i];
                    }
                    cout << endl;
                    inputChoice = 5;
                    break;
                }
                case 4: // Write to binary, read from binary
                {
                    double A[max_size];
                    int size = ConsoleInputArray(A);
                    WriteArrayBinFile(size, A, "1.bin");
                    RemoveNegative(A, size);
                    WriteArrayBinFile(size, A, "1.bin");
                    size = ReadArrayBinFile(max_size, A, "1.bin");
                    for (int i = 0; i < size; i++)
                    {
                        cout << A[i];
                    }
                    cout << endl;
                    inputChoice = 5;
                    break;
                }
                case 5: // Exit
                    break;
                default:
                    cout << "Invalid choice.\n";
                    break;
                }
            } while (inputChoice != 5);
            choice = 5;
            break;
        }
        case 2: // Task 2
        {
            MenuInput();
            int inputChoice;
            do
            {
                cout << "Choice ";
                cin >> inputChoice;

                switch (inputChoice)
                {
                case 1: // Console all
                {
                    double A[max_size];
                    int size = ConsoleInputArray(A);
                    double T;
                    do
                    {
                        cout << "Enter T ";
                        cin >> T;
                    } while (T <= 0 || T >= size);
                    int index = FindFirstMaxNegativeIndex(A, size, T);
                    if (index != -1)
                    {
                        cout << "First max negative index before T " << index << endl;
                    }
                    else
                    {
                        cout << "No negatives before T" << endl;
                    }
                    inputChoice = 5;
                    break;
                }
                case 2: // Console size & random array
                {
                    double A[max_size];
                    int size = InputRndArray(A);
                    double T;
                    do
                    {
                        cout << "Enter T ";
                        cin >> T;
                    } while (T <= 0 || T >= size);
                    int index = FindFirstMaxNegativeIndex(A, size, T);
                    if (index != -1)
                    {
                        cout << "First max negative index before T " << index << endl;
                    }
                    else
                    {
                        cout << "No negatives before T" << endl;
                    }
                    inputChoice = 5;
                    break;
                }
                case 3: // Write to file, read from file
                {
                    double A[max_size];
                    int size = ConsoleInputArray(A);
                    double T;
                    do
                    {
                        cout << "Enter T ";
                        cin >> T;
                    } while (T <= 0 || T >= size);
                    WriteArrayTextFile(size, A, "2.txt");
                    size = ReadArrayTextFile(max_size, A, "2.txt");
                    int index = FindFirstMaxNegativeIndex(A, size, T);
                    if (index != -1)
                    {
                        cout << "First max negative index before T " << index << endl;
                    }
                    else
                    {
                        cout << "No negatives before T" << endl;
                    }
                    inputChoice = 5;
                    break;
                }
                case 4: // Write to binary, read from binary
                {
                    double A[max_size];
                    int size = ConsoleInputArray(A);
                    double T;
                    do
                    {
                        cout << "Enter T ";
                        cin >> T;
                    } while (T <= 0 || T >= size);
                    WriteArrayBinFile(size, A, "2.bin");
                    int index = FindFirstMaxNegativeIndex(A, size, T);
                    if (index != -1)
                    {
                        cout << "First max negative index before T " << index << endl;
                    }
                    else
                    {
                        cout << "No negatives before T" << endl;
                    }
                    inputChoice = 5;
                    break;
                }
                case 5: // Exit
                    break;
                default:
                    cout << "Invalid choice\n";
                    break;
                }
            } while (inputChoice != 5);
            choice = 5;
            break;
        }
        case 3: // Task 3
        {
            int inputChoice;
            double schoolX, schoolY;
            cout << "School coordinates (x,y) ";
            cin >> schoolX >> schoolY;

            int numBuildings;
            do
            {
                cout << "Number of buildings ";
                cin >> numBuildings;
            } while (numBuildings <= 0);
            double totalDistance = 0.0;
            for (int i = 0; i < numBuildings; ++i)
            {
                double buildingX, buildingY;
                cout << "Building " << i + 1 << " coordinates (x,y) ";
                cin >> buildingX >> buildingY;
                totalDistance += Distance(schoolX, schoolY, buildingX, buildingY);
            }

            double averageDistance = totalDistance / numBuildings;
            cout << "Average distance " << averageDistance << endl;

            choice = 5;
            break;
        }
        case 5: // Exit
            break;
        default:
            cout << "Invalid choice\n";
            break;
        }
    } while (choice != 5);

    return 0;
}
