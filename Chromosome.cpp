//
// Created by kevin on 2018/10/12.
//

#include "Param.h"

using namespace std;

bool Chromosome::cmp(const Chromosome &c1, const Chromosome &c2) {
    return c1._fitnewssValue < c2._fitnewssValue;
}

Chromosome::Chromosome() {}
Chromosome::Chromosome(bool isRandom) {
    _fitnewssValue = 0;
    _wheelProbability = 0;

    for (int i : DefaultTimeWindow) {
        _timeWindows.emplace_back(TimeWindow(i));
    }
    updateNumberOfTimeWindows();
    if(isRandom) random();
    calculateFitnessValue();
}

Chromosome::Chromosome(const Chromosome &c) {
    _fitnewssValue = c._fitnewssValue;
    _wheelProbability = c._wheelProbability;
    _timeWindows.assign(c._timeWindows.begin(), c._timeWindows.end());
}

float Chromosome::calculateFitnessValue() {
    updateNumberOfTimeWindows();
    int sum1 = 0, sum2 = 0;
    int j = 0;
    for (int i = 0; i < NumberOfDeterministicCustomers - 1; i++) {
        j = _timeWindows.at(i).getCase() - 1;
        sum1 += minimumCostForAssigningCustomer[i][j];
    }
    sum1 *= Alpha;

    for (int numberOfTimeWindow : numberOfTimeWindows) {
        if ((numberOfTimeWindow - T) > 0)
            sum2 += (numberOfTimeWindow - T);
    }
    sum2 *= Beta;
    _fitnewssValue = sum1 + sum2;
    if (_fitnewssValue == 0) _fitnewssValue = 0.1;
    return _fitnewssValue;
}

void Chromosome::random() {
    for(unsigned int i = 1; i < _timeWindows.size(); i++) {
        int j = static_cast<int>((std::rand() % (NumberOfTimeWindowCase)) + 1);
        _timeWindows.at(i).setTimeWindowCase(j);
    }
}

void Chromosome::getTimeWindowCases() {
    for (auto &_timeWindow : _timeWindows)
        cout << _timeWindow.getCase() << " ";
    cout << " Fitness Value : " << _fitnewssValue;
    cout << endl;
}

void Chromosome::getNumberOfTimeWindows() {
    for (int numberOfTimeWindow : numberOfTimeWindows)
        cout << numberOfTimeWindow << " ";
    cout << endl << endl;
}

void Chromosome::updateNumberOfTimeWindows() {
    numberOfTimeWindows.clear();
    for (unsigned int i = 0; i < NumberOfTimeWindowCase + 1; i++) numberOfTimeWindows.emplace_back(0);
    for (auto &_timeWindow : _timeWindows) {
        numberOfTimeWindows.at(static_cast<unsigned int>(_timeWindow.getCase()))++;
    }
}

bool Chromosome::isExists(int cID) {
    for (auto &_timeWindow : _timeWindows)
        if (_timeWindow.getCase() == cID) return true;
    return false;
}

double Chromosome::getWheelProbability() {
    return _wheelProbability;
}

void Chromosome::setWheelProbability(double p) {
    _wheelProbability = p;
}

