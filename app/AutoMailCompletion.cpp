//      GestionNoteCompletion.cpp
//      Copyright (C) 2012 lengagne (lengagne@gmail.com)
//
//      This program is free software: you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation, either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//      This program was developped in the following labs:
//	from 2013 : Université Blaise Pascal / axis : ISPR / theme MACCS

#include <iostream>
#include <QString>

int main(int argc, char* argv[])
{
//    std::cout<<"argc="<<argc<<std::endl;
	if(QString(argv[argc-1]) != "args")
	{
		std::cerr<<"Error in the completion file"<<std::endl;
		exit(0);
	}
	if (argc == 2)
    {
        std::cout<<"help new_txt do "<<std::endl;
    }else if (argc ==3)
    {
        QString command(argv[1]);
        if(command == "do")
        {
            std::cout<<"file: ods"<<std::endl;
        }
    }else if (argc ==4)
    {
        QString command(argv[1]);
        if(command == "do")
        {
            std::cout<<" file: txt"<<std::endl;
        }
    }
	return 1;
}
