#include "Jug.h"

#include <iostream>
#include <sstream>

/*
 * Variable definitions:
 *
 * Ca and Cb are the capacities of the jugs A and B
 * N is the goal
 * cfA is the cost to fill A
 * cfB is the cost to fill B
 * ceA is the cost to empty A
 * ceB is the cost to empty B
 * cpAB is the cost to pour A to B
 * cpBA is the cost to pour B to A
*/

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) :
    Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA)
{
    // Generate the graph
    Vertex cfA_v("cfA");
    Vertex cfB_v("cfB");
    Vertex ceA_v("ceA");
    Vertex ceB_v("ceB");
    Vertex cpAB_v("cpAB");
    Vertex cpBA_v("cpBA");

    cfA_v.neighbors.push_back(std::pair<int, int>(1, cfB));
    cfA_v.neighbors.push_back(std::pair<int, int>(2, ceA));
    cfA_v.neighbors.push_back(std::pair<int, int>(3, ceB));
    cfA_v.neighbors.push_back(std::pair<int, int>(4, cpAB));

    cfB_v.neighbors.push_back(std::pair<int, int>(0, cfA));
    cfB_v.neighbors.push_back(std::pair<int, int>(2, ceA));
    cfB_v.neighbors.push_back(std::pair<int, int>(3, ceB));
    cfB_v.neighbors.push_back(std::pair<int, int>(5, cpBA));

    ceA_v.neighbors.push_back(std::pair<int, int>(0, cfA));
    ceA_v.neighbors.push_back(std::pair<int, int>(1, cfB));
    ceA_v.neighbors.push_back(std::pair<int, int>(3, ceB));
    ceA_v.neighbors.push_back(std::pair<int, int>(5, cpBA));

    ceB_v.neighbors.push_back(std::pair<int, int>(0, cfA));
    ceB_v.neighbors.push_back(std::pair<int, int>(1, cfB));
    ceB_v.neighbors.push_back(std::pair<int, int>(2, ceA));
    ceB_v.neighbors.push_back(std::pair<int, int>(4, cpAB));

    cpAB_v.neighbors.push_back(std::pair<int, int>(0, cfA));
    cpAB_v.neighbors.push_back(std::pair<int, int>(1, cfB));
    cpAB_v.neighbors.push_back(std::pair<int, int>(2, ceA));
    cpAB_v.neighbors.push_back(std::pair<int, int>(3, ceB));
    cpAB_v.neighbors.push_back(std::pair<int, int>(5, cpBA));

    cpBA_v.neighbors.push_back(std::pair<int, int>(0, cfA));
    cpBA_v.neighbors.push_back(std::pair<int, int>(1, cfB));
    cpBA_v.neighbors.push_back(std::pair<int, int>(2, ceA));
    cpBA_v.neighbors.push_back(std::pair<int, int>(3, ceB));
    cpBA_v.neighbors.push_back(std::pair<int, int>(4, cpAB));

    graph.push_back(cfA_v);  // 0
    graph.push_back(cfB_v);  // 1
    graph.push_back(ceA_v);  // 2
    graph.push_back(ceB_v);  // 3
    graph.push_back(cpAB_v); // 4
    graph.push_back(cpBA_v); // 5
}

Jug::~Jug()
{
    graph.clear();
}

int Jug::solve(std::string& solution)
{
    std::vector<int> steps;

    if (!isValidInputs())
    {
        solution = "";
        return -1;
    }

    steps = attempt();

    if (!steps.empty())
    {
        // Found a solution
        process(steps, solution);
        return 1;
    }
    else
    {
        solution = "";
        return 0;
    }
}

bool Jug::isValidInputs() const
{
    return (N >= 0 && cfA >= 0 && cfB >= 0 && ceA >= 0 && ceB >= 0 && cpAB >= 0 && cpBA >= 0)
        && (Ca > 0 && Ca <= Cb) && (N <= Cb && Cb <= 1000);
}

bool Jug::isCorrectAmount(std::list<std::pair<int, int>> steps)
{
    return steps.back().first /* A */ == 0 && steps.back().second /* B */ == N;
}

int Jug::process(std::vector<int>& steps, std::string& solution) const
{
    std::ostringstream outSS;
    int totalCost = 0;

    for (unsigned i = 0; i < steps.size(); ++i)
    {
        if (steps.at(i) == 0)
        {
            totalCost += cfA;
            outSS << "fill A" << std::endl;
        }
        else if (steps.at(i) == 1)
        {
            totalCost += cfB;
            outSS << "fill B" << std::endl;
        }
        else if (steps.at(i) == 2)
        {
            totalCost += ceA;
            outSS << "empty A" << std::endl;
        }
        else if (steps.at(i) == 3)
        {
            totalCost += ceB;
            outSS << "empty B" << std::endl;
        }
        else if (steps.at(i) == 4)
        {
            totalCost += cpAB;
            outSS << "pour A B" << std::endl;
        }
        else if (steps.at(i) == 5)
        {
            totalCost += cpBA;
            outSS << "pour B A" << std::endl;
        }
    }

    // Append total cost
    outSS << "success " << totalCost;
    solution = outSS.str();

    return totalCost;
}

std::vector<int> Jug::attempt()
{
    std::list<std::pair<int, int>> aRoute;
    std::list<std::pair<int, int>> bRoute;

    std::vector<int> aSteps;
    std::vector<int> bSteps;

    aRoute.push_back(std::pair<int, int>(0, 0));
    bRoute.push_back(std::pair<int, int>(0, 0));

    aSteps = traverse(0, aSteps, aRoute);
    bSteps = traverse(1, bSteps, bRoute);

    // Steps are empty, so we do not have a solution
    if (aSteps.empty() && bSteps.empty())
    {
        return aSteps;
    }

    // String only for process
    // Return which is better in cost
    std::string temp;
    return process(aSteps, temp) < process(bSteps, temp) ? aSteps : bSteps;
}

int Jug::doStep(int& aAmount, int& bAmount, const int& stepIndex)
{
    if (graph.at(stepIndex).key == "cfA")
    {
        aAmount = Ca;
    }
    else if (graph.at(stepIndex).key == "cfB")
    {
        bAmount = Cb;
    }
    else if (graph.at(stepIndex).key == "ceA")
    {
        aAmount = 0;
    }
    else if (graph.at(stepIndex).key == "ceB")
    {
        bAmount = 0;
    }
    else if (graph.at(stepIndex).key == "cpAB")
    {
        if (aAmount + bAmount <= Cb)
        {
            bAmount += aAmount;
            aAmount = 0;
        }
        else
        {
            aAmount -= (Cb - bAmount);
            bAmount = Cb;
        }
    }
    else if (graph.at(stepIndex).key == "cpBA")
    {
        if (aAmount + bAmount <= Ca)
        {
            aAmount += bAmount;
            bAmount = 0;
        }
        else
        {
            bAmount -= (Ca - aAmount);
            aAmount = Ca;
        }
    }

    return stepIndex;
}

std::vector<int> Jug::traverse(int index, std::vector<int> steps, std::list<std::pair<int, int>> route)
{
    std::vector<int> v2;
    std::vector<int> vT;
    int currentA;
    int currentB;
    int t;

    if (isCorrectAmount(route))
    {
        return steps;
    }

    std::list<std::pair<int, int>> neighbors = graph.at(index).neighbors;

    auto it = neighbors.begin();

    while (it != neighbors.end()) // Finding best route
    {
        currentA = route.back().first;
        currentB = route.back().second;
        t = doStep(currentA, currentB, it->first);

        if (!compare(currentA, currentB, route))
        {
            steps.push_back(t);
            route.push_back(std::pair<int, int>(currentA, currentB));
            if (v2.size() == 0)
            {
                v2 = traverse(t, steps, route);
            }
            else
            {
                std::string temp;

                vT = traverse(t, steps, route);
                if (process(v2, temp) > process(vT, temp))
                {
                    v2 = vT;
                }
            }

            steps.pop_back();
            route.pop_back();
        }

        it++;
    }

    return v2;
}

bool Jug::compare(int aAmount, int bAmount, std::list<std::pair<int, int>> route)
{
    auto it = route.begin();

    while (it != route.end())
    {
        if (it->first == aAmount && it->second == bAmount)
        {
            return true;
        }

        it++;
    }

    return false;
}