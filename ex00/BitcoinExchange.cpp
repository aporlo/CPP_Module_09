#include "BitcoinExchange.hpp"

// bool    isDate(std::string  const s);
// bool    isValue(std::string const s, bool isInt);
// int     convertDate(std::string date);
// std::string closestDate(std::string date, std::map<std::string, float> data);



BitcoinExchange::BitcoinExchange():_filedata("data.csv") {
    execfile(this->_filedata, &BitcoinExchange::addData);
}

BitcoinExchange::BitcoinExchange(std::string name): _filedata(name) {
    execfile(this->_filedata, &BitcoinExchange::addData);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& other)
{
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const& other)
{
    if (this != &other)
    {
        this->_btcData = other._btcData;
        this->_filedata = other._filedata;
        this->_fileinput = other._fileinput;
    }
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

std::string const BitcoinExchange::getFile() const {
    return this->_filedata;
}

std::map<std::string, float> const BitcoinExchange::getData() const {
    return this->_btcData;
}

float BitcoinExchange::getValue(std::string key) const {
    return this->_btcData.at(key);
}

void    BitcoinExchange::exchange(std::string fileName) {
    this->_fileinput = fileName;
    execfile(fileName, &BitcoinExchange::calculate);
}

void    BitcoinExchange::addData(std::string  & s) {
    std::string key = s.substr(0, s.find(","));
    std::string value = s.substr(s.find(",") + 1);
    if (!isDate(key))
        return;
    else if (!isValue(value, false))
        return;
    else
        this->_btcData[key] = std::atof(value.c_str());
}

void    BitcoinExchange::calculate(std::string & line) {
    
    std::size_t	pipe = line.find('|');
  
    line.erase(0, line.find_first_not_of(' '));
    line.erase(line.find_last_not_of(' ') + 1);
    if (line.length() < 14 || pipe == std::string::npos)
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return ((void)NULL);
    }
    std::cout << "line " << line << std::endl;
    std::string date = line.substr(0, pipe - 1);
    std::string value = line.substr(pipe + 2);
    if (!isDate(date))
        return;
    else if (!isValue(value, true))
        return;
    float v = atof(value.c_str());
    if (v < 0)
    {
        std::cerr << "Error: not a positive number" << std::endl;
        return ((void) NULL);
    }
    if (v > 1000)
    {
        std::cerr << "Error: too large number" << std::endl;
        return ((void) NULL);
    }
    float data;
    if (this->_btcData.find(date) != this->_btcData.end())
        data = this->_btcData.at(date);
    else
        data = this->_btcData.at(closestDate(date, this->_btcData));
    std::cout <<"data: " << data << std::endl;
    std::cout << date << " => " << v << " => " << v*data << std::endl;
    
}

void    BitcoinExchange::execfile(std::string & filename, void (BitcoinExchange::*func)(std::string & line)) {
    std::fstream    file;
    std::string     line;
    file.open(filename.c_str());
    if (!file)
        throw BitcoinExchange::ReadfileException();
    else
    {
        int i = 0;
        while (true)
        {
            if (i++ && !std::getline(file, line))
                break;
            if (i > 2)
                (this->*func)(line);
        }
        std::cin.clear();
        file.close();
    }
}

bool    BitcoinExchange::isLeapYear(int year) {
    return (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)? true : false);
}


bool    BitcoinExchange::isDate(std::string const s) {
    if (s.length() != 10 || s.at(4) != '-' || s.at(7) != '-')
    {
        std::cerr << "Error: bad input => " << s << std::endl;
        return (false);
    }
    int year = atoi(s.substr(0, 4).c_str());
    int month = atoi(s.substr(5, 2).c_str());
    int day = atoi(s.substr(8, 2).c_str());

    if (year < 1990 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        std::cerr << "Error: bad input => " << s << std::endl;
        return (false);
    }
    if (month == 2 && (isLeapYear(year) && day > 29))
    {
        std::cerr << "Error: bad input => " << s << std::endl;
        return (false);
    }
    if (month == 2 && (!isLeapYear(year) && day > 28))
    {
        std::cerr << "Error: bad input => " << s << std::endl;
        return (false);
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        std::cerr << "Error: bad in put => " << s << std::endl;
        return (false);
    }
    return true;
}

bool    BitcoinExchange::isValue(std::string const s, bool isInt) {
    std::regex   integer_expr("[+-]?([0-9]*[.])?[0-9]+");
    if(s.length() == 0 || s.empty())
    {
        std::cerr << "Error: invalid value => " << s << std::endl;
        return (false);
    }
    for (int i = 0; i < (int) s.length(); i++) {
        if (!isInt && !regex_match(s, integer_expr))
        {
            std::cerr << "Error: invalid value => " << s << std::endl;
            return (false);
        }
        if (isInt && !regex_match(s, std::regex("[+-]?([0-9]*)")))
			return (std::cerr << "Error: invalid value => " << s << std::endl, false);
    }
    return true;
}

int BitcoinExchange::convertDate(std::string date) {
    int dt = 60 * 24;
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());
    return (year * 365 * dt) + (month * 30 * dt) + (day * dt);
}

std::string BitcoinExchange::closestDate(std::string date, std::map<std::string, float> data) {
    int timestamp = convertDate(date);
    for (std::map<std::string, float>::reverse_iterator it = data.rbegin(); it != data.rend(); ++it) {
        if (convertDate(it->first) < timestamp) {
            return it->first;
        }
    }
    return data.begin()->first;
}
