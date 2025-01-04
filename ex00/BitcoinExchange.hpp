#ifndef BITCOINEXCHANGE_H
# define BITCOINEXCHANGE_H

# include <fstream>
# include <iostream>
# include <map>
# include <string>
# include <stdio.h>
# include <sstream>
# include <cstdlib>
# include <regex>


class BitcoinExchange
{
    private:
        std::string     _filedata;
        std::string     _fileinput;
        std::map<std::string, float>    _btcData;

        // void    _addData(std::string & s);
        // void    _cal(std::string & line);
        // void    _execfile(std::string &, void (BitcoinExchange::*)(std::string &));
        // void    _execfile(std::string &);
    
    public:
        BitcoinExchange(void);
        BitcoinExchange(std::string filename);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange(void);


        void    exchange(std::string fileName);
        std::string const getFile() const;
        std::map<std::string, float>    const getData() const;
        float                           getValue(std::string) const;
        bool    isDate(std::string  const s);
        bool    isValue(std::string const s, bool isInt);
        int     convertDate(std::string date);
        std::string closestDate(std::string date, std::map<std::string, float> data);
        void    addData(std::string & s);
        void    calculate(std::string & line);
        void    execfile(std::string &, void (BitcoinExchange::*)(std::string &));
        bool    isLeapYear(int year);

        class ReadfileException: public std::exception
        {
            public:
                virtual const char* what() const throw() {return "Error: could noot open file";}
        };    

};

#endif
