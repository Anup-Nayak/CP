#include "Chaining.h"
#include "LinearProbing.h"
#include "QuadraticProbing.h"
#include "CubicProbing.h"
#include "Comp.h"
#include <cassert>

void testDatabase(BaseClass *db) {
    db->createAccount("CDAD7786825_7990768648", 1000);
    db->createAccount("DCDA7547234_9919615552", 1500);
    db->createAccount("AACB1850545_7974534788", 2000);

    assert(db->getBalance("CDAD7786825_7990768648") == 1000);
    assert(db->getBalance("DCDA7547234_9919615552") == 1500);
    assert(db->getBalance("AACB1850545_7974534788") == 2000);

    db->addTransaction("CDAD7786825_7990768648", -200);
    db->addTransaction("DCDA7547234_9919615552", 300);
    db->addTransaction("AACB1850545_7974534788", -400);

    assert(db->getBalance("CDAD7786825_7990768648") == 800);
    assert(db->getBalance("DCDA7547234_9919615552") == 1800);
    assert(db->getBalance("AACB1850545_7974534788") == 1600);

    std::vector<int> topBalances = db->getTopK(2);
    assert(topBalances.size() == 2);
    assert(topBalances[0] == 1800);
    assert(topBalances[1] == 1600);

    assert(db->databaseSize() == 3);

    assert(db->doesExist("CDAD7786825_7990768648"));
    assert(!db->doesExist("CDAD7786825_7990968648"));
}


int main() {
    Chaining chainingDB;
    LinearProbing linearProbingDB;
    QuadraticProbing quadraticProbingDB;
    CubicProbing cubicProbingDB;
    Comp compDB;

    std::cout << "Testing Chaining:" << std::endl;
    testDatabase(&chainingDB);

    std::cout << "\nTesting Linear Probing:" << std::endl;
    testDatabase(&linearProbingDB);

    std::cout << "\nTesting Quadratic Probing:" << std::endl;
    testDatabase(&quadraticProbingDB);

    std::cout << "\nTesting Cubic Probing:" << std::endl;
    testDatabase(&cubicProbingDB);

    std::cout << "\nTesting Comp:" << std::endl;
    testDatabase(&compDB);
    return 0;
}
