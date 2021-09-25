#include <stack>
#include <iostream>

using namespace std;


enum Error_code{not_present, duplicated, success, overflow};
const int maxstack = 10;

// template <typename Stack_entry>

typedef double Stack_entry ;
class Stack
{
public:
    Stack();
    bool empty() const;
    Error_code pop();
    Error_code top(Stack_entry&) const;
    Error_code push(const Stack_entry &item);
private:
    int count;
    Stack_entry entry[maxstack];
};


Stack::Stack(){ count = 0; }
bool Stack::empty() const{
    return count == 0;
}
    // Error_code pop();
    // Error_code top(Stack_entry&) const;
    // Error_code push(const Stack_entry &item);


char get_command()
{
    char command;
     bool waiting = true;
     cout << "Select command";
     while (waiting){
         cin >> command;
         command = tolower(command);
         if (command == '?' || command == '=' || command == '+' ||
         command == '-' || command == '*' || command == '/' || command == 'q'){
             waiting = false;
         }
         else {
             cout << "please send " << endl;
         }
     }
     return command;
}

bool do_command(char command, stack<Stack_entry> &numbers)
{
    double p, q;
    switch(command){
        case '?':
        cout << "enter a real number" << flush;
        cin >> p;
        break;
        // if (numbers.push(p) )

        case '=':
        break;
        case 'q':
        cout << "finished ";
        return false;

    }
    return true;
}



int main()
{
    stack<Stack_entry> stored_numbers;
    // intr

    while ( do_command( get_command(), stored_numbers ));



    // int n;
    // double item;
    // stack<double> numbers;
    // cout << "Types" << endl;

    // cin >> n;
    // for (int i = 0 ; i < n; i++){
    //     cin >> item;
    //     numbers.push(item);
    // }
    // cout << endl << endl;
    // while(!numbers.empty()) {
    //     cout << numbers.top() << " ";
    //     numbers.pop();
    // }
    // cout << endl;
}