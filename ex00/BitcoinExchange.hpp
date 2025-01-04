#ifndef BITCOINEXCHANGE_H
# define BITCOINEXCHANGE_H

# include <fstream>
# include <iostream>
# include <map>
# include <string>
# include <stdio.h>
# include <sstream>
# include <cstdlib>



class BitcoinExchange
{
    private:
        std::string     _filedata;
        std::string     _fileinput;
        std::map<std::string, double>    _btcData;
    
    public:
        BitcoinExchange(void);
        BitcoinExchange(std::string filename);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange(void);


        void    exchange(std::string fileName);
        std::string const getFile() const;
        std::map<std::string, double>    const getData() const;
        double                           getValue(std::string) const;
        bool    isDate(std::string  const s);
        bool    isValue(std::string const s);
        int     convertDate(std::string date);
        std::string closestDate(std::string date, std::map<std::string, double> data);
        void    addData(std::string & s);
        void    calculate(std::string & line);
        void    execfile(std::string &, void (BitcoinExchange::*)(std::string &));
        bool    isLeapYear(int year);

        class ReadfileException: public std::exception
        {
            public:
                virtual const char* what() const throw() {return "Error: could not read file";}
        };    

};

#endif
