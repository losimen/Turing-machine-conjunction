#include <iostream>
#include <unistd.h>

class IState {
public:
    virtual std::string DoStateWork(std::string &programm, int &currentIndex, std::string &currentState) = 0;

    static void Setter(std::string &programm, const int &currentIndex, const char &toSet) {
        if (toSet == 'N')
            return;

        programm[currentIndex] = toSet;
    }

    static void Mover(int &currentIndex, const bool &isRight, const bool &isMove = true) {
        if (!isMove)
            return;

        if (isRight)
            currentIndex++;
        else
            currentIndex--;
    }
};


class State0: public IState{
public:
    std::string DoStateWork(std::string &programm, int &currentIndex, std::string &currentState) override {
        char currentSymbol = programm[currentIndex];

        if (currentSymbol == '0' || currentSymbol == '1')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, true);
            return "Q0";
        }
        else if (currentSymbol == 'x')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, false);
            return "Q1";
        }
        else {
            return "Qf";
        }

    }
};


class State1: public IState{
public:
    std::string DoStateWork(std::string &programm, int &currentIndex, std::string &currentState) override {
        char currentSymbol = programm[currentIndex];

        if (currentSymbol == '0')
        {
            Setter(programm, currentIndex, 'x');
            Mover(currentIndex, false);
            return "Q2";
        }
        else if (currentSymbol == '1')
        {
            Setter(programm, currentIndex, 'x');
            Mover(currentIndex, false);
            return "Q3";
        }
        else
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, false, false);
            return "Qf";
        }

    }
};


class State2: public IState{
public:
    std::string DoStateWork(std::string &programm, int &currentIndex, std::string &currentState) override {
        char currentSymbol = programm[currentIndex];

        if (currentSymbol == '0' || currentSymbol == '1')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, false);
            return "Q2";
        }
        else if (currentSymbol == '^')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, false);
            return "Q4";
        }
        else
        {
            return "Qf";
        }
    }
};


class State3: public IState{
public:
    std::string DoStateWork(std::string &programm, int &currentIndex, std::string &currentState) override {
        char currentSymbol = programm[currentIndex];

        if (currentSymbol == '0' || currentSymbol == '1')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, false);
            return "Q3";
        }
        else if (currentSymbol == '^')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, false);
            return "Q5";
        }
        else
        {
            return "Qf";
        }
    }
};


class State4: public IState{
public:
    std::string DoStateWork(std::string &programm, int &currentIndex, std::string &currentState) override {
        char currentSymbol = programm[currentIndex];

        if (currentSymbol == '0')
        {
            Setter(programm, currentIndex, 'x');
            Mover(currentIndex, false);
            return "Q6";
        }
        else if (currentSymbol == '1')
        {
            Setter(programm, currentIndex, 'x');
            Mover(currentIndex, false);
            return "Q7";
        }
        else if (currentSymbol == 'x')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, false);
            return "Q4";
        }
        else {
            return "Qf";
        }
    }
};


class State5: public IState{
public:
    std::string DoStateWork(std::string &programm, int &currentIndex, std::string &currentState) override {
        char currentSymbol = programm[currentIndex];

        if (currentSymbol == '0' || currentSymbol == '1')
        {
            Setter(programm, currentIndex, 'x');
            Mover(currentIndex, false);
            return "Q7";
        }
        else if (currentSymbol == 'x')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, false);
            return "Q5";
        }
        else {
            return "Qf";
        }
    }
};


class State6: public IState{
public:
    std::string DoStateWork(std::string &programm, int &currentIndex, std::string &currentState) override {
        char currentSymbol = programm[currentIndex];

        if (currentSymbol == '0' || currentSymbol == '1')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, false);
            return "Q6";
        }
        else if (currentSymbol == 'x')
        {
            Setter(programm, currentIndex, '0');
            Mover(currentIndex, false, false);
            return "Q8";
        }
        else {
            return "Qf";
        }
    }
};


class State7: public IState{
public:
    std::string DoStateWork(std::string &programm, int &currentIndex, std::string &currentState) override {
        char currentSymbol = programm[currentIndex];

        if (currentSymbol == '0' || currentSymbol == '1')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, false);
            return "Q7";
        }
        else if (currentSymbol == 'x')
        {
            Setter(programm, currentIndex, '1');
            Mover(currentIndex, false, false);
            return "Q8";
        }
        else {
            return "Qf";
        }
    }
};


class State8: public IState{
public:
    std::string DoStateWork(std::string &programm, int &currentIndex, std::string &currentState) override {
        char currentSymbol = programm[currentIndex];

        if (currentSymbol == '0' || currentSymbol == '1' || currentSymbol == 'x')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, true);
            return "Q8";
        }
        else if (currentSymbol == '^')
        {
            Setter(programm, currentIndex, 'N');
            Mover(currentIndex, true);
            return "Q0";
        }
        else {
            return "Qf";
        }
    }
};


class StateManager {
private:
    std::string currentState;
    int currentIndex;

    State0 state0;
    State1 state1;
    State2 state2;
    State3 state3;
    State4 state4;
    State5 state5;
    State6 state6;
    State7 state7;
    State8 state8;
public:
    explicit StateManager(const std::string &programm) {
        std::size_t chr_indx = programm.find('^');
        if (chr_indx == std::string::npos){
            currentIndex = 0;
            currentState = "Qf";
        }

        currentIndex = int(chr_indx)+1;
        currentState = "Q0";
    }

    void DoStateWork(std::string &programm) {
        if (currentState == "Q0")
            currentState = state0.DoStateWork(programm, currentIndex, currentState);
        else if (currentState == "Q1")
            currentState = state1.DoStateWork(programm, currentIndex, currentState);
        else if (currentState == "Q2")
            currentState = state2.DoStateWork(programm, currentIndex, currentState);
        else if (currentState == "Q3")
            currentState = state3.DoStateWork(programm, currentIndex, currentState);
        else if (currentState == "Q4")
            currentState = state4.DoStateWork(programm, currentIndex, currentState);
        else if (currentState == "Q5")
            currentState = state5.DoStateWork(programm, currentIndex, currentState);
        else if (currentState == "Q6")
            currentState = state6.DoStateWork(programm, currentIndex, currentState);
        else if (currentState == "Q7")
            currentState = state7.DoStateWork(programm, currentIndex, currentState);
        else if (currentState == "Q8")
            currentState = state8.DoStateWork(programm, currentIndex, currentState);
    }

    std::string GetCurrentState() {
        return currentState;
    }

    int GetCurrentIndex() const {
        return currentIndex;
    }
};


void RunByStep(const std::string &programm) {
    StateManager stateManager(programm);

    int lenOfStrProgramm = int(programm.length());
    std::string programmCopy = programm;

    std::cout << "Hit enter for each step" << std::endl;

    while (stateManager.GetCurrentState() != "Qf") {
        getchar();

        for (int i = 0; i < lenOfStrProgramm; i++) {
            if (stateManager.GetCurrentIndex() == i)
                std::cout << " [" << programmCopy[i] << "]" << " ";
            else
                std::cout << "  " << programmCopy[i] << "  ";
        }
        std::cout << "| " << stateManager.GetCurrentState();

        stateManager.DoStateWork(programmCopy);

    }
}


void RunAutomaticaly(const std::string &programm) {
    StateManager stateManager(programm);

    int lenOfStrProgramm = int(programm.length());
    std::string programmCopy = programm;

    while (stateManager.GetCurrentState() != "Qf") {
        for (int i = 0; i < lenOfStrProgramm; i++) {
            if (stateManager.GetCurrentIndex() == i)
                std::cout << " [" << programmCopy[i] << "]" << " ";
            else
                std::cout << "  " << programmCopy[i] << "  ";
        }
        std::cout << "| " << stateManager.GetCurrentState() << std::endl;

        stateManager.DoStateWork(programmCopy);

        usleep(300000);
    }
}


int main() {
    std::string programm = "xxxx0001^1100x";

    std::cout << "Enter option: \n"
              << "1-> By step \n"
              << "2-> Automatically \n"
              << ">> ";
    int choice = -1;
    std::cin >> choice;

    if (choice == 1)
    {
        RunByStep(programm);
    }
    else if (choice == 2)
    {
        RunAutomaticaly(programm);
    }

    return 0;
}