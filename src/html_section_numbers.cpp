//  HTML section numbers generator  ------------------------------------------//

//  � Copyright Beman Dawes, 2007, 2012

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt)


//----------------------------------------------------------------------------// 

#include <fstream>
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/test/included/prg_exec_monitor.hpp>

using namespace std;

namespace
{
  int section[] = {0,0,0,0,0,0,0,0,0,0};

  const string spaces("  ");

  void generate_section_number(string& buf, string::size_type pos, int level)
  {
    int i;
    for (i = 1; i <= level; ++i)
    {
      if (i == level)
        ++section[i];
      string number(boost::lexical_cast<string>(section[i]));
      buf.insert(pos, number);
      pos += number.size();
      if (i == level)
        buf.insert(pos, spaces);
      else
      {
        buf.insert(pos, 1, '.');
        ++pos;
      }
    }

    // reset any higher section numbers to 0
    for (; i < sizeof(section)/sizeof(int) && section[i] > 0; ++i)
      section[i] = 0;
  }
}  // unnamed namespace

//----------------------------------------------------------------------------// 

int cpp_main( int argc, char* argv[] )
{
  if (argc > 1)
  {
    cout << "Usage: html_section_numbers\n"
            "  Reads input from stdin\n"
            "  Writes output to stdout\n"
            ;
     return 1;
  }

  string buf;
  getline(cin, buf, '\0' ); // read entire file

  string::size_type pos;

  for ( pos = 0; (pos = buf.find( "<h", pos )) < buf.size() - 4; ++pos )
  {
    // get level
    if (buf[pos+2] < '1' || buf[pos+2] > '9') // not a heading
    {
      pos += 2;
      continue;
    }
    int level = buf[pos+2] - '0';
    pos += 4;
    generate_section_number(buf, pos, level);
  }

  // generate the output file
  std::cout << buf;

  return 0;
}