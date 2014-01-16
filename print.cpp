#include<iostream.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>
#include<stdlib.h>
#include<conio.h>






class sno {

	
public:

	int inte;

	
	sno() { inte=0;}

	void display() { cout<<setw(3)<<inte; }
	
	void enter(int n) { inte=n; }
	
	void write_file(fstream file) { file<<setw(3)<<inte; }
	
	void read_file(fstream file) { file>>inte; }


};




class integer {
	
	
public:

	int inte;
	

	integer() { inte=0; }

	void display() { cout<<setw(7)<<inte; }
	
	void enter() {	cin>>inte; }
	
	void write_file(fstream file) { file<<setw(7)<<inte; }
	
	void read_file(fstream file) { file>>inte; }


};




class string {
	

public:

	char str[15];
	

	string() { strcpy(str, "NULL"); }
	
	void display() { cout<<setw(15)<<str; }
	
	void enter() { cin>>str; }
	
	void write_file(fstream file) { file<<setw(15)<<str; }
	
	void read_file(fstream file) { file>>str; }


};



class date {


public:

	char d[11];

	
	date() { strcpy(d, "00-00-0000"); }

	void display() { cout<<d; }
	
	void enter() { cin>>d; }
	
	void write_file(fstream file) { file<<d; }
	
	void read_file(fstream file) { file>>d; }


};	




class attributes {


public:


	int no_att;
	int no_tup;
	char table_name[15];

	struct attribute {
		int no;
		char type;
		int type_no;
		char name[15]; } attribute[15];
	
	struct tuple {
		integer field_i[7];
		sno sno;
		string field_s[4];
		date field_d[3]; } tuple[20];


	attributes() {
		int i;
		no_att=no_tup=0;
		
		for (i=0; i<11; i++) {
			attribute[i].no=attribute[i].type_no=0;
			strcpy (attribute[i].name, "null");
			attribute[i].type='e'; } }



	void write_file(fstream file) {	file.write((char*)this, sizeof(attributes)); }

	void read_file(fstream file) { file.read((char*)this, sizeof(attributes)); }


} attributes;




class tuple {



public:

	
	integer field_i[7];
	sno sno;
	string field_s[4];
	date field_d[3];


	void display() {
		
		int i;
		
		cout<<"|";
		
		for (i=0; i<=attributes.no_att; i++) {
			cout<<" ";
			switch (attributes.attribute[i].type) {
			case 'i': field_i[attributes.attribute[i].type_no].display();
				break;
			case 's': field_s[attributes.attribute[i].type_no].display();
				break;
			case 'd': field_d[attributes.attribute[i].type_no].display();
				break;
			case 'n': sno.display();
				break; } }
		
		cout<<" |"; }



	void enter(int n) {
	
		int i;
		
		sno.enter(n);
		
		for (i=1; i<=attributes.no_att; i++) {
			cout<<attributes.attribute[i].name<<": ";
			switch (attributes.attribute[i].type) {
			case 'i': field_i[attributes.attribute[i].type_no].enter();
				break;
			case 's': field_s[attributes.attribute[i].type_no].enter();
				break;
			case 'd': field_d[attributes.attribute[i].type_no].enter();
				break;
			case 'n': sno.enter(n);
				break;
			default: cout<<"Invalid field.";
				break; } } }
	
	
	
	void write_file(int n, fstream file) {
		
		int i;
		
		file<<"|";
		
		for (i=0; i<=attributes.no_att; i++) {
			file<<" ";
			switch (attributes.attribute[i].type) {
			case 'i': field_i[attributes.attribute[i].type_no].write_file(file);
				break;
			case 's': field_s[attributes.attribute[i].type_no].write_file(file);
				break;
			case 'd': field_d[attributes.attribute[i].type_no].write_file(file);
				break;
			case 'n': sno.write_file(file);
				break; } } 
		
		file<<" |"; 

		for (i=0; i<=attributes.no_att; i++) {
			switch (attributes.attribute[i].type) {
			case 'i': attributes.tuple[n].field_i[attributes.attribute[i].type_no].inte=field_i[attributes.attribute[i].type_no].inte;
				break;
			case 's': strcpy(attributes.tuple[n].field_s[attributes.attribute[i].type_no].str, field_s[attributes.attribute[i].type_no].str);
				break;
			case 'd': strcpy(attributes.tuple[n].field_d[attributes.attribute[i].type_no].d, field_d[attributes.attribute[i].type_no].d);
				break;
			case 'n': attributes.tuple[n].sno.inte=sno.inte;
				break; } }}



	void read_file(int n, fstream file) { 
		
		int i;

		for (i=0; i<=attributes.no_att; i++) {
			switch (attributes.attribute[i].type) {
			case 'i': field_i[attributes.attribute[i].type_no].inte=attributes.tuple[n].field_i[attributes.attribute[i].type_no].inte;
				break;
			case 's': strcpy(field_s[attributes.attribute[i].type_no].str, attributes.tuple[n].field_s[attributes.attribute[i].type_no].str);
				break;
			case 'd': strcpy(field_d[attributes.attribute[i].type_no].d, attributes.tuple[n].field_d[attributes.attribute[i].type_no].d);
				break;
			case 'n': sno.inte=attributes.tuple[n].sno.inte;
				break;
			default: cout<<"Invalid field.";
				break; } } }


};




class heading {



public:

	
	integer field_i[7], sno;
	string field_s[4];
	date field_d[3];


	
	void display() {
	
		int i;
		
		cout<<"| ";
		
		for (i=0; i<=attributes.no_att; i++) {
			switch (attributes.attribute[i].type) {
			case 'i': cout<<setw(7)<<attributes.attribute[i].name;
				break;
			case 's': cout<<setw(15)<<attributes.attribute[i].name;
				break;
			case 'd': cout<<setw(10)<<attributes.attribute[i].name;
				break;
			case 'n': cout<<"SNo";
				break; }
			cout<<" ";	}
		
		cout<<"|"<<endl; }



	void enter() {
		
		int no, i, s, d;
		
		cout<<"Please enter the number of attributes: ";
		cin>>attributes.no_att;
		
		
		i=s=d=0;
		attributes.attribute[0].type='n';
				
		cout<<"Please enter attribute details."<<endl;
		cout<<"===================================================================================="<<endl;
		cout<<"|- A maximum of 7 integer, 4 string and 3 date attributes (total 11) are allowed.  |"<<endl;
		cout<<"|- Serial no. is automatically added and should not be considered as an attribute. |"<<endl;
		cout<<"|- Attribute names must be single words. Longer names will be shortened.           |"<<endl;
		cout<<"|- Attribute types: i-integer, s-string, d-date                                    |"<<endl;
		cout<<"====================================================================================";
		
		for (no=1; no<=attributes.no_att; no++) {
			cout<<endl<<"Attribute "<<no<<": "<<endl;
			cout<<"Name: ";
			cin>>attributes.attribute[no].name;
			cout<<"Type: ";
			cin>>attributes.attribute[no].type;
			switch (attributes.attribute[no].type) {
			case 'i': attributes.attribute[no].type_no=i;
				if (strlen(attributes.attribute[no].name)>7) {
					attributes.attribute[no].name[6]='.';
					attributes.attribute[no].name[7]='\0'; }
				i++;
				break;
			case 's': attributes.attribute[no].type_no=s;
				if (strlen(attributes.attribute[no].name)>15) {
					attributes.attribute[no].name[14]='.';
					attributes.attribute[no].name[15]='\0'; }
				s++;
				break;
			case 'd': attributes.attribute[no].type_no=d;
				if (strlen(attributes.attribute[no].name)>10) {
					attributes.attribute[no].name[9]='.';
					attributes.attribute[no].name[10]='\0'; }
				d++;
				break;
			default: cout<<"Invalid type. Reenter attribute details";
				no--;
				break; } } }
	
	
	
	void write_file(fstream file) {
		
		int i;
		
		file<<"| ";
		
		for (i=0; i<=attributes.no_att; i++) {
			switch (attributes.attribute[i].type) {
			case 'i': file<<setw(7)<<attributes.attribute[i].name;
				break;
			case 's': file<<setw(15)<<attributes.attribute[i].name;
				break;
			case 'd': file<<setw(10)<<attributes.attribute[i].name;
				break;
			case 'n': file<<"SNo";
				break; }
			file<<" "; }
		
		file<<"|"<<endl; }
		
	
	
	void read_file(fstream file);   



};




class line {



public:


	int i, s, d;
	int total;
	int equal_to;


	line() { i=s=d=total=equal_to=0; }



	void display() {
	
		int i=0;
		
		for (i=0; i<equal_to; i++) { cout<<'='; }
		cout<<endl; }


		
	void enter() {

		int n;

		i=s=d=total=equal_to=0;
		
		for (n=1; n<=attributes.no_att; n++) {
			switch (attributes.attribute[n].type) {
			case 'i': i++;
				break;
			case 's': s++;
				break;
			case 'd': d++;
				break; } }
		
		total=i+s+d;
		equal_to=7+total+(i*7)+(s*15)+(d*10); }



	void read_file (fstream file) {

		int n;

		i=s=d=total=equal_to=0;
		
		for (n=1; n<=attributes.no_att; n++) {
			switch (attributes.attribute[n].type) {
			case 'i': i++;
				break;
			case 's': s++;
				break;
			case 'd': d++;
				break; } }
		
		total=i+s+d;
		equal_to=7+total+(i*7)+(s*15)+(d*10); }



	void write_file (fstream file) {
		
		int i=0;
		
		for (i=0; i<equal_to; i++) { file<<'='; }
		file<<endl; }
	
	
	
};




class table {



public:
	
	
	heading heading;
	tuple tuple[20];
	int no_tup;
	char name[15];
	line line;
	
	
	table() { no_tup=0; }

	

	void display() {
	
		int i=0;
		
		cout<<endl<<"Table: "<<name<<endl<<endl;
		
		line.display();
		heading.display();
		line.display();
		
		for (i=0; i<no_tup; i++) {
			tuple[i].display();
			cout<<endl; }
		
		line.display(); }



	void enter() {

		int i;

		cout<<"Please name your table [one word]: ";
		cin>>name;
		
		heading.enter();
		line.enter();
		
		cout<<endl<<endl<<"Enter number of tuples: ";
		cin>>no_tup;
		
		attributes.no_tup=no_tup;
		
		for(i=0; i<no_tup; i++) {
			cout<<endl<<"Tuple "<<i+1<<": "<<endl;
			tuple[i].enter(i+1); } }



	void write_file(fstream file) {
		
		int i=0;
		
		file<<"Table: "<<name<<endl<<endl;
		
		strcpy (attributes.table_name, name);
		
		line.write_file(file);
		heading.write_file(file);
		line.write_file(file);
		
		for (i=0; i<no_tup; i++) {
			tuple[i].write_file(i, file);
			file<<endl; }
		line.write_file(file); }



	void read_file(fstream file) {
		
		int i;

		no_tup=attributes.no_tup;
		strcpy (name, attributes.table_name);
		
		line.read_file(file); 
		
		for (i=0; i<no_tup; i++) { tuple[i].read_file(i, file); } }  



} table;

	


void create() {
	
	
	char ch;
	int check=1;
	fstream file ("_temp.txt", ios::out),
		att_list ("temp\\temp_data.dat", ios::binary|ios::out);

	
	cout<<endl<<endl;
	table.enter();



	do {
		
		
		cout<<endl<<endl<<"Table has been created. Please check preview below."<<endl<<endl;
		
		table.display();

		cout<<"\n\n\t1. Save";
		cout<<"\n\n\t2. Edit a data entry";
		cout<<"\n\n\t3. Go back to main menu";
		cout<<"\n\n";
		cin>>ch;

		
		switch (ch) {
		
		case '1': char file_name[20], att_name[30];
			
			table.write_file(file);
			attributes.write_file(att_list);
			file.close();
			att_list.close();
			
			cout<<"Please enter a file name [one word]: ";
			cin>>file_name;
						
			strcpy(att_name, "temp\\");
			strcat(att_name, file_name);
			strcat(file_name, ".txt");
			
			rename ("_temp.txt", file_name);
			
			strcat(att_name, "_data.dat");
			
			rename ("temp\\temp_data.dat", att_name);
			
			{	fstream file_list("temp\\filelist.dat", ios::binary|ios::app);
				file_list<<file_name<<endl;
				file_list.close(); }
			
			cout<<endl<<"File has been successfully saved!";
			cout<<endl<<"To print, please go to file \""<<file_name<<"\".";
			
			check=0;
			
			break;
		
		case '2': int i;
		
			cout<<"Enter SNo of tuple to be edited: ";
			cin>>i;
			
			if (i>table.no_tup) { cout<<"Tuple does not exist!"; }
			else { table.tuple[i-1].enter(i); } 
			
			break;
		
		case '3': check=0;
			
			break;
		
		default: cout<<"Option does not exist. Please try again.\n";
			
			break; } } while (check); }




void edit() { 



	char ch;
	int check=1;
	char file_name[20], file_open[20], att_name[30];
	fstream file_list("temp\\filelist.dat", ios::binary|ios::in);

	
	cout<<endl<<endl;
	cout<<endl<<"List of files: "<<endl;
	
	file_list>>file_name;
	while (!file_list.eof()) {
		cout<<"- "<<file_name<<endl;
		file_list>>file_name; }
	file_list.close();
	

	cout<<"Please select file to be edited: ";
	cin>>file_open;

	strcpy(att_name, "temp\\");
	strcat(att_name, file_open);
	strcat(att_name, "_data.dat");
	strcat(file_open, ".txt");
	
	fstream att_list(att_name, ios::in);	
	fstream file(file_open, ios::in);

	attributes.read_file(att_list);
	table.read_file(file);
	table.display();
	
	file.close();
	att_list.close();
	
	
	
	do {
		
		cout<<"\n\n\t1. Edit full table (including attributes)";
		cout<<"\n\n\t2. Edit a data entry";
		cout<<"\n\n";
		cin>>ch;


		switch (ch) {
		
		case '1': table.enter();
		
			check=0;
			
			break;
		
		case '2': int i;
		
			cout<<"Enter SNo of tuple to be edited: ";
			cin>>i;
			
			if (i>table.no_tup) { cout<<"Tuple does not exist!"; }
			else { table.tuple[i-1].enter(i); }
			
			check=0;
			
			break;
		
		default: cout<<"Option does not exist. Please try again.\n";
			
			break; } } while (check);
			
	
	file.open("_temp.txt", ios::out);
	att_list.open("temp\\temp_data.dat", ios::binary|ios::out);


	check=1;
	
	do {
	
		table.display();
		table.write_file(file);

		cout<<"\n\n\t1. Edit another data entry";
		cout<<"\n\n\t2. Save";
		cout<<"\n\n\t3. Save as";
		cout<<"\n\n\t4. Go back to main menu";
		cout<<"\n\n";
		cin>>ch;

	
		switch (ch) {
		
		case '1': int i;
		
			cout<<"Enter SNo of tuple to be edited: ";
			cin>>i;
			
			if (i>table.no_tup) { cout<<"Tuple does not exist!"; }
			else { table.tuple[i-1].enter(i); } 
			
			break;
		
		case '2': char file_name[15], att_name[20];
			
			attributes.write_file(att_list);
			
			file.close();
			att_list.close();
			
			strcpy (file_name, file_open);
			file_name[strlen(file_name)-4]='\0';
			strcpy(att_name, "temp\\");
			strcat(att_name, file_name);
			strcat(file_name, ".txt");
			
			remove (file_name);
			rename ("_temp.txt", file_name);
			
			strcat(att_name, "_data.dat");
			
			remove (att_name);
			rename ("temp\\temp_data.dat", att_name);
			
			cout<<endl<<"File has been successfully saved!";
			cout<<endl<<"To print, please go to file \""<<file_name<<"\".";
			
			check=0; 
		
			break;
			
		case '3': attributes.write_file(att_list);
		
			file.close();
			att_list.close();
			
			cout<<"Please enter a file name [one word]:";
			cin>>file_name;
			
			strcpy(att_name, "temp\\");
			strcat(att_name, file_name);
			strcat(file_name, ".txt");
			
			rename ("_temp.txt", file_name);
			
			strcat(att_name, "_data.dat");
			
			rename ("temp\\temp_data.dat", att_name);
			
			{	fstream file_list("temp\\filelist.dat", ios::binary|ios::app);
				file_list<<file_name<<endl;
				file_list.close(); }
			
			cout<<endl<<"File has been successfully saved!";
			cout<<endl<<"To print, please go to file \""<<file_name<<"\".";
			
			check=0; 
			
			break;
		
		case '4': check=0;
			
			break;
		
		default: cout<<"Option does not exist. Please try again.\n";
			
			break; } } while (check); 	
		
				

 }




void main() {



	char ch;
	int check=1;


	do {

		cout<<"\n\n\t1. Create new table";
		cout<<"\n\n\t2. Edit existing table";
		cout<<"\n\n\t3. Exit";
		cout<<"\n\n";
		cin>>ch;

			
		switch (ch) {
		
		case '1': create();
		
			break;
		
		case '2': edit();
		
			break;
		
		case '3': check=0;
		
			break;
		
		default: cout<<"Option does not exist. Please try again.\n";
			
			break; } } while (check); }