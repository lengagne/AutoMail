/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include <ods/ods>
#include <QtCore>
#include <iostream>
#include "utils.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

    if (argc == 2)
    {
        QString command(argv[1]);
        if (command == "help")
        {
            print_help();
            return 1;
        }else if ( command =="new")
        {
			std::cout<<"ouais il faut qu'on le fasse"<<std::endl;
		}
		return 1;
    }else if (argc == 4)
    {
        QString command(argv[1]);
        qDebug()<<" command = "<< command;
        if (command =="do")
        {
            QString fileods(argv[2]);
            QString filetxt(argv[3]);
			qDebug()<<"fileods = "<< fileods;
			qDebug()<<"filetxt = "<< filetxt;            
            return 1;
        }
	}
	print_help();
	return 0;
}


