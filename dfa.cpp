#include <iostream>
#include <unordered_map>
using namespace std;

// DFA representation
struct DFA {
    unordered_map<int, unordered_map<char, int>> transitions; // Use nested unordered_map for better structure
    int finalState;
};

// Function to check if the string is accepted by the DFA
bool isAccepted(const DFA& dfa, const string& input) { // Pass by reference to avoid copying
    int currentState = 0; // Start state
    cout << "Starting DFA evaluation..." << endl;

    for (char c : input) {
        cout << "Current State: " << currentState << ", Input: " << c << endl;
        if (dfa.transitions.find(currentState) == dfa.transitions.end() || 
            dfa.transitions.at(currentState).find(c) == dfa.transitions.at(currentState).end()) {
            cout << "No valid transition found. Rejecting string." << endl;
            return false; // No valid transition
        }
        currentState = dfa.transitions.at(currentState).at(c);
        cout << "Transitioned to State: " << currentState << endl;
    }
    
    cout << "Final State: " << currentState << endl;
    return (currentState == dfa.finalState); // Check if final state reached
}

int main() {
    DFA dfa;

    // Define DFA transitions for binary strings ending in '01'
    dfa.transitions[0]['0'] = 1;
    dfa.transitions[0]['1'] = 0;
    dfa.transitions[1]['0'] = 1;
    dfa.transitions[1]['1'] = 2;
    dfa.transitions[2]['0'] = 1;
    dfa.transitions[2]['1'] = 2; // Fixed incorrect transition from state 2 on '1'
    dfa.finalState = 2; // Accepting state

    string input;
    cout << "Enter a binary string: ";
    cin >> input;

    // Validate input
    for (char c : input) {
        if (c != '0' && c != '1') {
            cout << "Invalid input. Please enter a binary string." << endl;
            return 1;
        }
    }

    if (isAccepted(dfa, input)) {
        cout << "String is accepted by the DFA." << endl;
    } else {
        cout << "String is rejected by the DFA." << endl;
    }
    
    return 0;
}
