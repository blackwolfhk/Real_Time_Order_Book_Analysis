#ifndef CSV_WRITER_HPP
#define CSV_WRITER_HPP

#include <fstream>
#include <string>

class CSVWriter {
public:
    explicit CSVWriter(const std::string& filename);
    void write_line(const std::string& line);

private:
    std::ofstream file;
};

#endif // CSV_WRITER_HPP