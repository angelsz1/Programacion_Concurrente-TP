#include "password_generator.h"

std::mutex m_index;
std::mutex m_vec;

int index = 0;
std::vector<int> result;
std::string password;

int fromCharToInt(char character)
{
    if (character < 'A')
    {
        std::cout << "Not a letter" << std::endl;
        return -1;
    }
    if (character > 'Z')
    {
        return handleMinus(character);
    }
    return character - 'A' + 1;
}

int handleMinus(char character)
{
    if (character < 'a' || character > 'z')
    {
        std::cout << "Not a letter" << std::endl;
        return -1;
    }
    return character - 'a' + 1;
}

int convert()
{
    int conversion = fromCharToInt(password[index]);
    index++;
    if (conversion == -1)
    {
        std::cout << "INVALID PASSWORD" << std::endl; 
        exit(-1);
    }
    return conversion;
}

void push_to_vec(int digit)
{
    result.push_back(digit);
    std::cout << digit << std::endl;
}

void characterConverter(int amountCharToProcess) // threadDo
{
    int converted;
    for (int i = 0; i < amountCharToProcess; i++)
    {
        m_index.lock();
        m_vec.lock();
        std::cout << "thread_" << std::this_thread::get_id() << " pushed ";
        converted = convert();
        push_to_vec(converted);
        m_vec.unlock();
        m_index.unlock();
    }
}

int main(int argc, char* argv[])
{
    if (argc != AMOUNT_PARAMETERS)
    {
        std::cout << "Not enough parameters" << std::endl;
        return -1;
    }
    password = argv[1];
    result = {};
    int len = password.length();

    std::thread thread_1 = std::thread(characterConverter, len/2);
    std::thread thread_2 = std::thread(characterConverter, len/2);

    thread_2.join();
    thread_1.join();

    std::cout << "Resultado : " << std::endl; 
    for (int i = 0; i < len; i++)
    {
        std::cout << result[i] << " ";
    }
}
