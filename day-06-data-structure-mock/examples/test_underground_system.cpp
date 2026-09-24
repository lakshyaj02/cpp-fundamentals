#include "underground_system.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

namespace {

bool approximately_equal(double left, double right) {
    return std::abs(left - right) < 1e-9;
}

void test_single_journey() {
    UndergroundSystem system;

    system.check_in(1, "Central", 3);
    system.check_out(1, "North", 13);

    assert(approximately_equal(system.average_time("Central", "North"), 10.0));
}

void test_average_across_passengers() {
    UndergroundSystem system;

    system.check_in(1, "Central", 3);
    system.check_in(2, "Central", 8);
    system.check_out(1, "North", 13);
    system.check_out(2, "North", 23);

    assert(approximately_equal(system.average_time("Central", "North"), 12.5));
}

void test_routes_are_directional_and_independent() {
    UndergroundSystem system;

    system.check_in(1, "A", 2);
    system.check_out(1, "B", 12);
    system.check_in(2, "B", 20);
    system.check_out(2, "A", 50);
    system.check_in(3, "A", 60);
    system.check_out(3, "C", 65);

    assert(approximately_equal(system.average_time("A", "B"), 10.0));
    assert(approximately_equal(system.average_time("B", "A"), 30.0));
    assert(approximately_equal(system.average_time("A", "C"), 5.0));
}

void test_passenger_can_take_multiple_journeys() {
    UndergroundSystem system;

    system.check_in(7, "A", 10);
    system.check_out(7, "B", 20);
    system.check_in(7, "A", 30);
    system.check_out(7, "B", 50);

    assert(approximately_equal(system.average_time("A", "B"), 15.0));
}

void test_large_aggregate_does_not_overflow() {
    UndergroundSystem system;

    for (int passenger_id = 1; passenger_id <= 3; ++passenger_id) {
        system.check_in(passenger_id, "A", 0);
        system.check_out(passenger_id, "B", 1'000'000'000);
    }

    assert(approximately_equal(system.average_time("A", "B"), 1'000'000'000.0));
}

} // namespace

int main() {
    test_single_journey();
    test_average_across_passengers();
    test_routes_are_directional_and_independent();
    test_passenger_can_take_multiple_journeys();
    test_large_aggregate_does_not_overflow();

    std::cout << "All underground system tests passed.\n";
}
