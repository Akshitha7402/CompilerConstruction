/*
Kleen star : *
Min one time : +
once or none : ?
concatenation : #
Union : |
*/

#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

int state_number = -1;

class NFA {
public:
    set<int> states;
    set<char> symbols;
    map<pair<int, char>, set<int>> transitionFunction;
    int startState; 
    set<int> finalStates; 
    map<int, set<int>> epsilonTransitions;
    
    NFA()
    {
        startState = state_number;
    }

    void addState(int state)
    {
        states.insert(state);
    }

    void addSymbol(char symbol)
    {
        symbols.insert(symbol);
    }

    void addTransition(int state, char symbol, int nextState) {
        transitionFunction[{state, symbol}].insert(nextState);
    }

    void setStartState(int state)
    {
        if (states.find(state) != states.end())
        {
            startState = state;
        } else
        {
            cerr << "State does not exist." << endl;
        }
    }

    void addfinalState(int state)
    {
        if (states.find(state) != states.end()) 
        {
            finalStates.insert(state);
        } 
        else 
        {
            cout<<"\nstate = "<<state;
            cerr << "\nState does not exist." << endl;
        }
    }

    void addEpsilonTransition(int state, int nextState)
    {
        epsilonTransitions[state].insert(nextState);
    }

    bool checkAlpha(char symbol)
    {
        if(symbol != 'a' && symbol != 'b')
            return false;
        else
            return true;
    }

    set<int> epsilonClosure(const NFA& nfa, const set<int>& states)
    {
        set<int> closure = states;

        stack<int> s;
        for (int state : states)
        {
            s.push(state);
        }

        while (!s.empty()) {
            int state = s.top();
            s.pop();
            auto itr = nfa.epsilonTransitions.find(state);
            if (itr != nfa.epsilonTransitions.end()) {
                for (int nextState : itr->second)
                {
                    //if it is not in the closure add it in it and push into stack 
                    if (closure.find(nextState) == closure.end()) 
                    {
                        closure.insert(nextState);
                        s.push(nextState);
                    }
                }
            }
        }
        return closure;
    }    

    bool accepts(const NFA& nfa, const string& input) {
        set<int> currentStates = epsilonClosure(nfa, {nfa.startState});
        for (char c : input)
        {
            set<int> nextStates;
            for (int state : currentStates)
            {
                auto itr = nfa.transitionFunction.find({state, c});
                //find if this itr is in transitionFunction and if it is there...
                if (itr != nfa.transitionFunction.end())
                {
                    // map<pair<int, char>, set<int>> transitionFunction;
                    auto canGoTo = itr->second;
                    nextStates.insert(canGoTo.begin(), canGoTo.end());
                }
            }
            currentStates = epsilonClosure(nfa, nextStates);
        }

        for (int state : currentStates) 
        {
            auto itr = nfa.finalStates.find(state);
            if (itr != nfa.finalStates.end()) {
                return true;
            }
        }
        return false;
    }  

};

set<int> epsilonClosure2(const NFA& nfa, int state)
{
    set<int> closure;
    closure.insert(state);
    queue<int> stateTrack;
    stateTrack.push(state);

    while(!stateTrack.empty())
    {
        int currentState = stateTrack.front();
        stateTrack.pop();

        auto itr = nfa.epsilonTransitions.find(currentState);

        if(itr != nfa.epsilonTransitions.end())
        {
            for(int nextState: itr->second)
           {
                if(closure.find(nextState) == closure.end())
                {
                    closure.insert(nextState);
                    stateTrack.push(nextState);
                }
            }
        }
    }

    return closure;
}

struct DFA {
    vector<set<int>> states;
    set<char> symbols;
    int startState;
    set<int> startClosure;
    set<set<int>> finalStates;
    map<pair<set<int>, char>, set<int>> transitionFunction;
};

set<int> computeNextClosure(const NFA& nfa, const set<int>& currentState, char symbol)
{
  set<int> nextClosure;
  for (int state : currentState) 
  {
    for (const auto& transition : nfa.transitionFunction) 
    {
      if (transition.first.first == state && transition.first.second == symbol) 
      {
        nextClosure.insert(transition.second.begin(), transition.second.end());
      }
    }
  }
  return nextClosure;
}

set<int> computeEpsilonNextClosure(const NFA& nfa, const set<int>& nextClosure)
{
  set<int> epsilonNextClosure;
  for (int state : nextClosure) 
  {
    set<int> epsilonClosureSet = epsilonClosure2(nfa, state);
    epsilonNextClosure.insert(epsilonClosureSet.begin(), epsilonClosureSet.end());
  }
  return epsilonNextClosure;
}

bool isNewState(const set<set<int>>& statesTravelled, const set<int>& epsilonNextClosure)
{
  for (const auto& state : statesTravelled) 
  {
    if (state == epsilonNextClosure) 
    {
      return false;
    }
  }
  return true;
}

void computeFinalStates(const NFA& nfa, DFA& dfa)
{
  for (int i = 0; i < dfa.states.size(); ++i) 
  {
    const auto& dfaState = dfa.states[i];
    bool isFinal = false;
    for (auto nfaFinalState : nfa.finalStates) 
    {
      for (int state : dfaState) 
      {
        if (state == nfaFinalState) 
        {
          dfa.finalStates.insert(dfaState);
          isFinal = true;
          break;
        }
      }
      if (isFinal) {
        break;
      }
    }
  }
}


//NFA with epsilon transitions to DFA
DFA convertNFAToDFA(const NFA& nfa) 
{
  DFA dfa;
  dfa.startClosure = epsilonClosure2(nfa, nfa.startState);
  dfa.states.push_back(dfa.startClosure);
  dfa.startState = 0;
  
  queue<set<int>> stateQueue;
  stateQueue.push(dfa.startClosure);
  
  set<set<int>> statesTravelled;
  statesTravelled.insert(dfa.startClosure);

  while (!stateQueue.empty()) 
  {
    set<int> currentState = stateQueue.front();
    stateQueue.pop();

    for (char symbol : nfa.symbols)
    {
      set<int> nextClosure = computeNextClosure(nfa, currentState, symbol);
      set<int> epsilonNextClosure = computeEpsilonNextClosure(nfa, nextClosure);

      if (!epsilonNextClosure.empty() && isNewState(statesTravelled, epsilonNextClosure)) 
      {
        dfa.states.push_back(epsilonNextClosure);
        stateQueue.push(epsilonNextClosure);
        statesTravelled.insert(epsilonNextClosure);
      }

      dfa.transitionFunction[{currentState, symbol}] = epsilonNextClosure;
    }
  }

  dfa.symbols = nfa.symbols;
  computeFinalStates(nfa, dfa);

  return dfa;
}

bool acceptsDFA(const DFA& dfa, const string& input) {
    set<int> currentStates = dfa.states[dfa.startState]; // Start at DFA's start state

    for (char c : input) 
    {
        //find if the current state and symbol pair exists in the table
        auto itr = dfa.transitionFunction.find({currentStates, c});
        //if it does
        if (itr != dfa.transitionFunction.end()) {
            //then move to the value state in the map
            auto canGoTo = itr->second;
            currentStates = canGoTo;
        }
        else 
        {
            return false;
        }
    }

    // Check if the current state set is one of the final states set
    if (dfa.finalStates.find(currentStates) != dfa.finalStates.end()) {
        return true;
    } else {
        return false;
    }
}

void mergeNFA(NFA& nfa, NFA& nfa1)
{
    // Merge states from nfa1 and nfa2 into nfa
    for (int state : nfa1.states) 
    {
        nfa.addState(state);
    }
    

    // Merge symbols from nfa1 and nfa2 into nfa
    for (char symbol : nfa1.symbols) 
    {
        nfa.addSymbol(symbol);
    }
    

    // Merge transitions from nfa1 and nfa2 into nfa
    for (auto& it : nfa1.transitionFunction) 
    {
        for (int nextState : it.second) 
        {
            nfa.addTransition(it.first.first, it.first.second, nextState);
        }
    }    

    // Merge epslion-transitions from nfa1 and nfa2 into nfa
    for (auto& it : nfa1.epsilonTransitions) 
    {
        for (int nextState : it.second) 
        {
            nfa.addEpsilonTransition(it.first, nextState);
        }
    }
}

//NFA for epsilon transition
NFA rule1(int i, int j)
{
    NFA nfa;
    nfa.addState(i);
    nfa.addState(j);
    nfa.setStartState(i);
    nfa.addfinalState(j);
    nfa.addEpsilonTransition(i,j);

    return nfa;
}

//NFA for 'a','b' single char
NFA rule2(string input, int i)
{
    NFA nfa;
    char c = input[i];
   
    int x = ++state_number;
    nfa.addState(x);
    nfa.setStartState(x);

    int y = ++state_number;
    nfa.addState(y);
    nfa.addfinalState(y);

    nfa.addSymbol(c);
    nfa.addTransition(x, c, y);
    return nfa;
}

//NFA for a|b
NFA rule3(NFA nfa1, NFA nfa2) 
{
    NFA nfa;
    int newStart = ++state_number;
    int newFinal = ++state_number;

    
    nfa.addState(newStart);
    nfa.addState(newFinal);
    nfa.setStartState(newStart);
    nfa.addfinalState(newFinal);

    // Add epslion-transitions from newStart to the start states of nfa1 and nfa2
    nfa.addEpsilonTransition(newStart, nfa1.startState);

    mergeNFA(nfa, nfa1);

    mergeNFA(nfa, nfa2);
    nfa.addEpsilonTransition(newStart, nfa2.startState);

    // Add epslion-transitions from the final states of nfa1 and nfa2 to newFinal
    for (int finalState : nfa1.finalStates) 
    {
        nfa.addEpsilonTransition(finalState, newFinal);
    }
    for (int finalState : nfa2.finalStates) 
    {
        nfa.addEpsilonTransition(finalState, newFinal);
    }

    return nfa;
}

//NFA for a#b
NFA rule4(NFA nfa1, NFA nfa2) 
{
    NFA nfa;
   
    mergeNFA(nfa, nfa1);
    mergeNFA(nfa, nfa2);

    for (int finalState : nfa1.finalStates) 
    {
        nfa.addEpsilonTransition(finalState, nfa2.startState);
    }

    nfa.setStartState(nfa1.startState);

    for (int finalState : nfa2.finalStates) 
    {
        nfa.addfinalState(finalState);
    }

    return nfa;
}

//NFA a*...kleen star
NFA rule5(NFA nfa1)
{
    NFA nfa;

    //make new final and start state
    int newStart = ++state_number;
    int newFinal = ++state_number;

    nfa.addState(newStart);
    nfa.addState(newFinal);
    nfa.setStartState(newStart);
    nfa.addfinalState(newFinal);  
   
    mergeNFA(nfa,nfa1);

    //add epsilon transitions
    //new start to nfa1's start
    nfa.addEpsilonTransition(newStart, nfa1.startState);

    //old finals to new finals
    for (int finalState : nfa1.finalStates) {
        nfa.addEpsilonTransition(finalState, newFinal);
    }

    //old final to old start
    for (int finalState : nfa1.finalStates) {
        nfa.addEpsilonTransition(finalState, nfa1.startState);
    }
    //new start to new final
    nfa.addEpsilonTransition(newStart, newFinal);

    return nfa;  
}

//NFA for a+
NFA rule6(NFA nfa1)
{
    NFA nfa;
    //New Start state attached to nfa1's start state
    int newStart = ++state_number;
    int newFinal = ++state_number;

    nfa.addState(newStart);
    nfa.addState(newFinal);
    nfa.setStartState(newStart);
    nfa.addfinalState(newFinal);


    mergeNFA(nfa, nfa1);
    //add epsilon transitions
    //new start to nfa1's start
    nfa.addEpsilonTransition(newStart, nfa1.startState);

    //old final to new finals
    for (int finalState : nfa1.finalStates)
    {
        nfa.addEpsilonTransition(finalState, newFinal);
    }

    //new final to new start
    nfa.addEpsilonTransition(newFinal, newStart);

    return nfa;
}

//NFA for ?
//either once or none
NFA rule7(NFA nfa1)
{
    NFA nfa;

    //make new final and start state
    int newStart = ++state_number;
    int newFinal = ++state_number;

    nfa.addState(newStart);
    nfa.addState(newFinal);
    nfa.setStartState(newStart);
    nfa.addfinalState(newFinal);
   
    mergeNFA(nfa, nfa1);

    //add epsilon transitions
    //new start to nfa1's start
    nfa.addEpsilonTransition(newStart, nfa1.startState);

    //old finals to new finals
    for (int finalState : nfa1.finalStates) {
        nfa.addEpsilonTransition(finalState, newFinal);
    }

    //new start to new final
    nfa.addEpsilonTransition(newStart, newFinal);

    return nfa;
}

NFA constructNFA(const string postfix, stack<NFA>& fragments)
{
    for(int i = 0; i < postfix.length(); i++) 
    {
        if (postfix[i] == 'a' || postfix[i] == 'b') {
            NFA nfa = rule2(postfix, i);
            fragments.push(nfa);
        }
        else if (postfix[i] == '|' || postfix[i] == '#')
        {
            NFA nfa2 = fragments.top();
            fragments.pop();
            NFA nfa1 = fragments.top();
            fragments.pop();

            if(postfix[i] == '|')
            {
                NFA nfa = rule3(nfa1, nfa2);
                fragments.push(nfa);
            }
            else if(postfix[i] == '#')
            {
                NFA nfa = rule4(nfa1, nfa2);
                fragments.push(nfa);
            }
             
        }
       
        else if (postfix[i] == '*' || postfix[i] == '+' || postfix[i] == '?')
        {
            NFA nfa1 = fragments.top();
            fragments.pop();

            if(postfix[i] == '*')  
            {
                NFA nfa = rule5(nfa1);
                fragments.push(nfa);
            }
            else if(postfix[i] == '+')  
            {
                NFA nfa = rule6(nfa1);
                fragments.push(nfa);
            }
            else if(postfix[i] == '?')  
            {
                NFA nfa = rule7(nfa1);
                fragments.push(nfa);
            }        
        }
    }

    NFA finalNFA = fragments.top();
    fragments.pop();

    return finalNFA;
}

//the function won't change the argument so use const
string infixToPostfix(const string& input)
{
  stack<char> s;
  queue<char> output;
  
  for (int i = 0; i < input.length(); i++)
  {
    char symbol = input[i];
    
    switch (symbol)
    {
      case '|':
        while (!s.empty() && s.top() != '(')
        {
          char temp = s.top();
          s.pop();
          output.push(temp);
        }
        s.push(symbol);
        break;
        
      case ')':
        while (!s.empty() && s.top() != '(')
        {
          char temp = s.top();
          s.pop();
          output.push(temp);
        }
        if (!s.empty())
        {
          s.pop();
        }
        break;
        
      case 'a':
      case 'b':
        output.push(symbol);
        break;
        
      case '(':
        s.push(symbol);
        break;
        
      case '*':
      case '?':
      case '+':
      case '#':
        while (!s.empty() && (s.top() == '*' || s.top() == '+' || s.top() == '?'))
        {
          char temp = s.top();
          s.pop();
          output.push(temp);
        }
        s.push(symbol);
        break;
    }
  }

  while (!s.empty())
  {
    char temp = s.top();
    s.pop();
    output.push(temp);
  }

  string postfix = "";
  while (!output.empty())
  {
    postfix += output.front();
    output.pop();
  }
  
  return postfix;
}

vector<pair<string, int>> lexTool(const string& input, const vector<DFA>& dfa_regexes, const vector<NFA>& nfa_regexes)
{    
    vector<pair<string, int>> output;
    int i = 0;
    vector<int> unmatchedIndex;   
    if(input.length()==0) 
    {
        for(int i = 0; i < dfa_regexes.size(); i++) 
        {          
                if(acceptsDFA(dfa_regexes[i], input))
                {
                    output.push_back({"$", i + 1}); 
                }
        } 
        return output;
    }

    while(i < input.length())
    {
        string matchedLexeme = "";
        int longestMatchedLen = 0;
        int matchedRegexIndex = 0; // 1-based indexing


        for(int currRegexIndex = 0; currRegexIndex < dfa_regexes.size(); currRegexIndex++)
        {
            for(int j = i; j < input.length(); j++)
            {

                string currLexeme = input.substr(i, j - i + 1);
                if(acceptsDFA(dfa_regexes[currRegexIndex], currLexeme))
                {
                    int currMatchedLen = currLexeme.length();
                    if(currMatchedLen > longestMatchedLen)
                    {
                        longestMatchedLen = currMatchedLen;
                        matchedLexeme = currLexeme;
                        matchedRegexIndex = currRegexIndex + 1; //1-based indexing
                    }
                }
            }
        }

        if(longestMatchedLen > 0)
        {
            // If there's a match => add it to the output
            output.push_back({matchedLexeme, matchedRegexIndex});
            i += longestMatchedLen; // Move past the matched lexeme
        }
        else
        {
            output.push_back({input.substr(i, 1), 0});
            i++;
        }
    }
    return output;
}

bool checkAlpha(char symbol)
{
    if(symbol != 'a' && symbol != 'b')
        return false;
    else
        return true;
}

string insertConcat(const string& input) 
{
    string result;
    int i = 0;
    while(i<input.size()) 
    {
        result += input[i];

        if (input[i] == ')' && input[i + 1] == '(')
        {
            result += '#';
        }
        i++;
    }
    result += input.back(); // Append the last character of the input
    return result;
}

int main()
{
    vector<string> infixes;
    vector<string> postfixes;
    vector<NFA> nfa_regexes;
    vector<DFA> dfa_regexes;
    string input;
    vector<pair<string, int> > output;
    string line;

    fstream in("input.txt", ios::in); 
    
    if(in.is_open())
    {
        getline(in, input,'\n');
        input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
        while(getline(in,line,'\n'))
        {
            infixes.push_back(line);
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        }

        in.close();
    }
    else
        cout<<"\nError!";

    for(int i=0; i<infixes.size(); i++)
    {
        infixes[i] = insertConcat(infixes[i]);
    }

    for(int i=0; i<infixes.size(); i++)
    {
        string temp = infixToPostfix(infixes[i]);
        postfixes.push_back(temp);
    }

    for(int i=0; i<postfixes.size(); i++)
    {
        stack<NFA> fragments;
        NFA nfa = constructNFA(postfixes[i], fragments);
        nfa_regexes.push_back(nfa);
    }

    for(int i=0 ; i<nfa_regexes.size(); i++)
    {
        DFA dfa = convertNFAToDFA(nfa_regexes[i]);
        dfa_regexes.push_back(dfa);
    }

    output = lexTool(input, dfa_regexes, nfa_regexes);

    ofstream out("output.txt");
    if(out.is_open())
    {
        for (const auto& it : output)
        {
            out << "<" << it.first<< "," << it.second <<">";
        }
    }
    else
        cout<<"\nERROR!";
    
    return 0;
}
