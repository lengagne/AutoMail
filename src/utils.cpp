#include <iostream>
#include "utils.h"
#include <fstream>
#include <sstream>
#include <map>

void print_help()
{
	std::cout<<"help"<<std::endl;
	std::cout<<"create example of txt file :    AutoMail new_txt "<<std::endl;
	std::cout<<"create the bash file : Automail odsfile txtfile"<<std::endl;
}

void do_the_stuff(	const QString & fileods,
					const QString & filetxt)
{

	qDebug()<<"Start reading the file "<< filetxt;
	std::ifstream in(filetxt.toStdString());
    if(!in)
    {
            qDebug() << "cannot open file " << filetxt;
            exit(0);
    }
	std::stringstream out;
    out << in.rdbuf();
    QString content= QString::fromStdString(out.str());

	std::cout<<"Il y a ca dans le txt: "<<std::endl<<content.toStdString()<<std::endl;

	qDebug()<<"Start reading the file "<< fileods;
	QFile file(fileods);
	if (!file.exists())
	{
		qDebug() << "No such file: " << fileods;
		return;
	}
	ods::Book book_in(fileods);
	auto *sheet_in = book_in.sheet(0);
	if (sheet_in == nullptr)
	{
		qDebug() << "No sheet at 0";
		return;
	}

	unsigned int nom_row =0;
	auto *current_row = sheet_in->row(nom_row++);


	std::vector<QString> first_line;
	ods::Cell *cellule = nullptr;
	unsigned int nb_col=0;
	cellule= current_row->cell(nb_col++);
	do
	{
		QString tmp = *(cellule->value()).AsString();

		qDebug()<<" we found item "<< tmp;
		first_line.push_back(tmp.simplified());

		cellule= current_row->cell(nb_col++);
	}while(cellule && !cellule->value().NoValue());
	qDebug()<<"on sort du while";

	current_row = sheet_in->row(nom_row++);


    std::ofstream outfile ("auto_mail_output.sh");

	


	while(current_row != nullptr)
	{
// 		std::cout<<"We found one line "<<std::endl;
		std::map<QString,QString> infos;	
		for (int i=0;i<first_line.size();i++)
		{
//                         std::cout<<"i = "<<i <<std::endl;
                        cellule= current_row->cell(i);
			QString tmp;
			if(cellule && (cellule->value()).IsString())
			{
			 	tmp = *(cellule->value()).AsString();
			}
			else if(cellule&& (cellule->value()).IsDouble())
			{
			 	tmp = QString::number( *(cellule->value()).AsDouble());
			}
			else
                        {
                                tmp="EMPTY";
                                qDebug()<<" Error cannot find item" <<first_line[i] <<" on line "<< nom_row+1;
                        }

// 			std::cout<<" we found item "<< tmp.toStdString()<<" for "<< first_line[i].toStdString()<<std::endl;
			infos[first_line[i]] = tmp.simplified();
			// on créé les lignes dans le sh

			

		}
		outfile << "echo \"";

		QString texte = content;
		 	
		for(std::map<QString,QString>::const_iterator it = infos.begin();it!=infos.end();it++)
		{
			QString change = "$"+it->first+"$";
			texte.replace(change,it->second);
		}

		// program keywords
		texte.replace("@OBJECT@","\" | mutt -s ");
		texte.replace("@TO@"," ");
		texte.replace("@CC@"," -c ");
		// qDebug()<<"text = "<< texte ;
		outfile << texte.toStdString()<<std::endl;

		current_row = sheet_in->row(nom_row++);
	}
    outfile.close();

}
