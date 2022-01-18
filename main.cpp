#include <iostream>
#include <vector>

#include <getopt.h>

std::vector<std::string>* handled = new std::vector<std::string>();

void handleHelp()
{
    std::cout << "Option --help (-h) was used." << std::endl;
}

void handleVersion()
{
    std::cout << "Option --version (-v) was used." << std::endl;
}

void handleInput(char *arg)
{
    std::cout << "Option --input (-i) with value " << arg << " was used." << std::endl;
}

void handleOutput(char *arg)
{
    std::cout << "Option --output (-o) with value " << arg << " was used." << std::endl;
}

void handleCount()
{
    std::cout << "Option --count (-c) was used." << std::endl;
}

void handleReverse()
{
    std::cout << "Option --reverse (-r) was used." << std::endl;
}

bool isHandled(const std::string& n_option)
{
    for(auto &argument : *handled)
    {
        if (n_option == argument)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    int c_option, i_option = 0;;

    const char* shorts = "hvcri:o:";

    struct option longs[] = {
            {"help",    no_argument, nullptr, 'h'},
            {"version", no_argument, nullptr, 'v'},
            {"input",   required_argument, nullptr, 'i'},
            {"output",  required_argument, nullptr, 'o'},
            {"count",   no_argument, nullptr, 'c'},
            {"reverse", no_argument, nullptr, 'r'},
            {nullptr, 0, nullptr, 0}
    };

    while((c_option = getopt_long(argc, argv, shorts, longs, &i_option)) != -1)
    {
        std::string n_option;

        for(struct option &element : longs)
        {
            if(element.val == c_option)
            {
                n_option = element.name;
                break;
            }
        }

        if(isHandled(n_option))
        {
            continue;
        }
        handled->push_back(n_option);

        switch(c_option)
        {
            case 'h':
                handleHelp();
                break;

            case 'v':
                handleVersion();
                break;

            case 'i':
                handleInput(optarg);
                break;

            case 'o':
                handleOutput(optarg);
                break;

            case 'c':
                handleCount();
                break;

            case 'r':
                handleReverse();
                break;

            case '?':
                break;

            default:
                abort();
        }
    }

    if(optind < argc)
    {
        std::cout << "Non-option argument values:" << std::endl;
        while(optind < argc)
        {
            std::cout << argv[optind++] << std::endl;
        }
    }

    return 0;
}
