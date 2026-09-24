#pragma once

#include <string>
#include <cstdint>
#include <functional>
#include <unordered_map>
#include <utility>

class UndergroundSystem {
public:
    void check_in(int passenger_id,
                  const std::string& station,
                  int time){
        travel_data[passenger_id] = TravelInfo{station, time};
    }

    void check_out(int passenger_id,
                   const std::string& station,
                   int time){
        TravelInfo info = travel_data[passenger_id];
        std::pair<std::string, std::string> route{info.start_station, station};
        std::int64_t travel_time = static_cast<std::int64_t>(time) - info.travel_time;
        auto& route_entry = route_data[route];
        route_entry.first += travel_time;
        route_entry.second += 1;
        travel_data.erase(passenger_id);
    }

    double average_time(const std::string& start_station,
                        const std::string& end_station) const{
        std::pair<std::string, std::string> route{start_station, end_station};
        const auto& route_entry = route_data.at(route);
        return static_cast<double>(route_entry.first) / route_entry.second;
    }

private:
        struct TravelInfo {
            std::string start_station;
            int travel_time;
        };

        struct pair_hash {
            template <class T1, class T2>
            std::size_t operator()(const std::pair<T1, T2>& p) const {
                auto h1 = std::hash<T1>{}(p.first);
                auto h2 = std::hash<T2>{}(p.second);
                return h1 ^ (h2 << 1);
            }
        };

        std::unordered_map<int, TravelInfo> travel_data;
        std::unordered_map<std::pair<std::string, std::string>,
                   std::pair<std::int64_t, std::size_t>, pair_hash> route_data;
        
};