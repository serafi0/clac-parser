#include <boost/spirit/include/qi.hpp>
#include<boost/spirit/include/phoenix_core.hpp>
#include<boost/spirit/include/phoenix_operator.hpp>
#include<iostream>
#include<string>
#include <fstream>
#include<string>
using namespace std;

namespace client {
    namespace qi=boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;
    using qi::double_;
    using qi::_1;
    using ascii::space;
    using phoenix::ref;
    using qi::phrase_parse;

    template<typename Iterator>
    bool adder(Iterator first , Iterator last , double &n)
    {
        bool r = qi::phrase_parse(first ,last ,

                                  (double_[ref(n) = _1]
                                          >> *('/' >> double_[ref(n) /=_1]|
                                                  '-' >> double_[ref(n) -=_1]|
                                                  '*' >> double_[ref(n) *=_1]|
                                                  '+' >> double_[ref(n) += _1]))
                                         ,space);

        if (first!=last)
            return false;
        return r;

    }
}
int main()
{
    double n;
    string str;
    char ch;
    ifstream infile;
    infile.open("/Users/mohamedelserafy/CLionProjects/parser for calc/calc.txt"); //<---- type text file path here
    while (!infile.eof())
    {
        getline(infile,str);

        if(client::adder(str.begin(),str.end(),n))
        {
            cout<<"---------------------------------"<<endl;
            cout<<str<<"   "<<"parsing successful"<<endl;
            cout<<"result="<<n<<endl;
            cout<<"---------------------------------"<<endl;


        }
        else{
            cout<<"---------------------------------"<<endl;
            cout<<str<<"   ";
            cout<<"parsing failed"<<std::endl;
            cout<<"---------------------------------"<<endl;
        }
    }
}
