#include "csv_writer.hpp"
#include <iostream>

CSVWriter::CSVWriter(const std::string& filename) {
    file.open(filename, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("❌ Failed to open CSV file: " + filename);
    }

    // Optional: write header if file is empty
    file.seekp(0, std::ios::end);
    if (file.tellp() == 0) {
        file << "timestamp,imbalance\n";
    }
}

void CSVWriter::write_line(const std::string& line) {
    file << line << "\n";
    file.flush(); // Ensure data is written immediately
}