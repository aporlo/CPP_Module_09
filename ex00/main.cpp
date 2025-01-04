#include "BitcoinExchange.hpp"

int main(int argc, char  *argv[])
{
    if (argc != 2)
    {
        std::cout << "Error: must ./btc <filename>" << std::endl;
        return (1);
    }
    try {
        BitcoinExchange btc = BitcoinExchange();
        btc.exchange(argv[1]);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return (0);
}
