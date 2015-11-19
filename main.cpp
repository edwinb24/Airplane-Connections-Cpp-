#include <iostream>
#include <string>
#include<fstream>  //preprocesser for input and output file.
#include <my_global.h>
#include <mysql.h>

#include <conio.h>
#include <string>

using namespace std;
 //input file declaration.
// reads in a password without echoing it to the screen
string myget_passwd()
{
	string passwd;

	for(;;)
	{
		char ch;
		ch=getch();           // get char WITHIOUT echo!
		if (ch==13 || ch==10) // if done ...
			break;           //  stop reading chars!
		cout << '*';  // dump * to screen
		passwd+=ch;   // addd char to password
	}
	cin.sync(); // flush anything else in the buffer (remaining newline)
	cout << endl;  // simulate the enter that the user pressed

	return passwd;
}

int main()
{
	// mysql connection and query variables
	MYSQL *conn, // actual mysql connection
		mysql;   // local mysql data
	MYSQL_RES *res; // mysql query results
	MYSQL_ROW row;  // one row of a table (result)

	// strings for mysql hostname, userid, ...
	string db_host;
	string db_user;
	string db_password;
	string db_name;

	// set up the client (this machine) to use mysql
	cout << "initializing client DB subsystem ..."; cout.flush();
	mysql_init(&mysql);
	cout << "Done!" << endl;

	// get user credentials and mysql server info
	cout << "Enter MySQL database hostname (or IP adress):";
	cin >> db_host;

	cout << "Enter MySQL database username:";
	cin >> db_user;

	cout << "Enter MySQL database password:";
	db_password=myget_passwd();

	// could also prompt for this, if desired
	db_name=db_user;


	// go out and connect to the mysql server
	cout << "Connecting to remote DB ..."; cout.flush();
	conn = mysql_real_connect(&mysql, 
		                    db_host.c_str(), db_user.c_str(), db_password.c_str(), db_user.c_str(),
				             0,0,0); // last three are usually 0's

	// if we couldn't setup the connection ...
	if (conn==NULL)
	{
		// print out the error message as to why ...
		cout << mysql_error(&mysql) << endl;
		return 1; // ... and exit the program. 
	}
	else
		cout << "DB connection established" << endl;


				/*START OF THE ACTUAL PROGRAM!!!*/
int cho; //Keep the choice of the user, which part of the program want to execute
int max; //keep the maximum number of conections required by the user
int status; //keep the error shooting of the SQL Queries
int tot;
char com[40]; //Keep the strings that are going to be sent to SQL 
char com2[100]; //Keep the strings that are going to be sent to SQL 
char airname[81];//Keep the airlines names before they are sent to SQL
char code[2];//Keep the codes before sended to SQL
char state[3];// Keep the state before sended to SQL
char arrive[3];//Keep the arrives before sended to SQL
char depart[3];//Keep the depart before sended to SQL
char cost [6];//Keep the cost before sended to SQL
char file[20]; //keep the file name
char numgates[2]; //keep the number of gates before sended to SQL
bool sw; //control the reading from the files


do{
cout<<"*************************** MAIN MENU ************************";
cout<<"\n";
cout<<"\n1. Create the underlying tables";
cout<<"\n2. Enter information for a new airport";
cout<<"\n3. Enter information for a new flight";
cout<<"\n4. Read information in for multiple new airports from a file";
cout<<"\n5. Read information in for multiple new flights from a file";
cout<<"\n6. Display flight options for a requested trip";
cout<<"\n7. Update the cost of flight";
cout<<"\n8. Delete a flight";
cout<<"\n9. Delete an airport";
cout<<"\n10. Query how well each state is being seviced";
cout<<"\n11. Update airline name";
cout<<"\n12. Quit\n";
cout<<"\n";
cout<<"\n";
cout<<"\nPlease Select an option:\n";
cin>>cho;//take the choice of the user

if(cho ==1){/*Process the Option 1*/
/*Creating the table AIRPORTS*/
	cout <<"Creating Table AIRPORTS ..."; 
		status = mysql_query(conn, "CREATE TABLE AIRPORTS(CODE CHAR(3), STATE CHAR(2), NumGates INT, PRIMARY KEY (CODE))");

	if (status!=0)//Sent an error if there is a problem with the creation of the table,
		          //in general sent a message when a table has already be created
	{

		cout << "\n"<<mysql_error(&mysql)  << endl;
	}
	else
		cout << "Done" << endl;

/*Creating the table FLIGHTS*/
	cout <<"Creating Table FLIGHTS ..."; 
		status = mysql_query(conn, "CREATE TABLE FLIGHTS(AIRLINE CHAR(2), AirlineName CHAR(80), Depart CHAR(3), Arrives CHAR(3), Cost FLOAT, PRIMARY KEY(AIRLINE, AirlineName, Depart, Arrives, Cost))");

	if (status!=0)//Sent an error if there is a problem with the creation of the table,
		          //in general sent a message when a table has already be created
	{
		cout << "\n"<<mysql_error(&mysql)  << endl;
	}
	else
		cout << "Done" << endl;
}

else if(cho ==2){/*Process the Option 2*/
	cout<<"\n Please insert the code:";
cin>>code;//read the code from the keyboard to C++
			cout<<"\n Please insert the State:";
cin>>state;//read the state from the keyboard to C++
				cout<<"\n Please insert the Number of gates:";
cin>> numgates;//read the number of gates from the keyboard to C++

/*Make the query command to be sent to SQL*/
strcpy(com,"INSERT INTO AIRPORTS VALUES('");
strcat(com,code);/*include the value of code in the query*/
strcat(com, "', '");
strcat(com, state);/*include the value of state in the query*/
strcat(com, "', ");
strcat(com, numgates);/*include the value of numgates in the query*/
strcat(com, ");");
cout <<"Entering Information ...\n"; 
		status = mysql_query(conn, com);//sent the query to SQL

	if (status!=0)//check if there is any error with the sent of the query
				  //in this time check most for duplication of datas
	{
		cout << mysql_error(&mysql) << endl;
	}
	else
		cout << "Done" << endl;



}

else if(cho ==3){/*Process the Option 3*/
	cout<<"\n Please insert the new airline code:";
cin>>code;//read the code from the keyboard to C++
			cout<<"\n Please insert the Airline Name:";
cin>>airname;//read the airline name from the keyboard to C++
				cout<<"\n Please insert the Depart:";
cin>> depart;//read the depart from the keyboard to C++
		cout<<"\n Please insert the Arrival:";
cin>> arrive;//read the arrive from the keyboard to C++
cout<<"\n Please insert the Cost:";
cin>> cost;//read the cost from the keyboard to C++
/*Make the query command to be sent to SQL*/
strcpy(com,"INSERT INTO FLIGHTS VALUES('");
strcat(com,code);/*include the value of code in the query*/
strcat(com, "', '");
strcat(com, airname);/*include the value of airname in the query*/
strcat(com, "', '");
strcat(com, depart);/*include the value of depart in the query*/
strcat(com, "', '");
strcat(com, arrive);/*include the value of arrive in the query*/
strcat(com, "', ");
strcat(com, cost);/*include the value of cost in the query*/
strcat(com, ");");
cout <<"Entering Information ..."; 
		status = mysql_query(conn, com); //sent the query

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the user try to insert a value that is already in the Table
		cout << mysql_error(&mysql) << endl;
	}
	else
		cout<<"\n Total number of datas procesed sucesfully: "<<tot;
		cout << "\nDone" << endl;

}

else if(cho ==4){/*Process the Option 4*/
	tot= 0;
ifstream fin;//reader from file
	cout<<"Please insert the name of the data file:";
		cin>>file;
	//Open the input file.
	fin.open(file,ios::in); 
cout <<"Entering Information ..."; 
	do{
fin>>code; //read the code from the file
fin>>state; //read the state from the file
fin>>numgates;//read the numgates from the file
sw= isalpha(state[0]);//Check if the end of the file have been reached

if(sw){	


/*Make the query command to be sent to SQL*/
strcpy(com2,"INSERT INTO AIRPORTS VALUES('");
strcat(com2,code);
strcat(com2, "', '");
strcat(com2, state);
strcat(com2, "', ");
strcat(com2, numgates);
strcat(com2, ");");


		status = mysql_query(conn, com2);

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the user try to insert a value that is already in the Table
		cout<<"\n\nError presented reading: ";
		cout<<com2;	
		cout<<"\nError Log: ";
		cout << mysql_error(&mysql) << endl;
	}
	else{	
		tot=tot+1;
		cout << "Done" << endl;
	}
}

}while(sw); //keep reading until the file end
	cout<<"\n Total number of datas procesed sucesfully: \n"<<tot;
	fin.close();//close the file
}

else if(cho == 5){/*Process the Option 5*/
ifstream fin;//reader from file
tot= 0;
	cout<<"Please insert the name of the data file:";
		cin>>file;
	//Open the input file.
	fin.open(file,ios::in); 
cout <<"Entering Information ..."; 
	do{
fin>>code; //read the code from the file
fin>>airname; //read the airline name from the file
fin>>depart; //read the depart from the file
fin>>arrive; //read the arrive from the file
fin>>cost; //read the cost from the file
sw= isdigit(cost[0]); //Check if the end of the file have been reached

if(sw){	

/*Make the query command to be sent to SQL*/
strcpy(com,"INSERT INTO FLIGHTS VALUES('");
strcat(com,code);
strcat(com, "', '");
strcat(com, airname);
strcat(com, "', '");
strcat(com, depart);
strcat(com, "', '");
strcat(com, arrive);
strcat(com, "', ");
strcat(com, cost);
strcat(com, ");");

		status = mysql_query(conn, com);

	if (status!=0)//Check if there is an error in the query
	{             //Error will be sent if the user try to insert a value that is already in the Table
		cout<<"\n\nError presented reading";
		cout<<"\nError Log: ";
		cout << mysql_error(&mysql) << endl;
	}
	else{
		tot=tot+1;	
		cout << "Done" << endl;
	}
}

}while(sw);//keep reading until the file end
cout<<"\n Total number of datas procesed sucesfully: \n"<<tot;
	fin.close();//close the file
}

else if(cho == 7){/*Process the Option 7*/
	cout<<"\n Please insert the airline code: ";
cin>>code;//read the code from the keyboard to C++
				cout<<"\n Please insert the Depart: ";
cin>> depart;//read the depart from the keyboard to C++
		cout<<"\n Please insert the Arrival: ";
cin>> arrive;//read the arrive from the keyboard to C++
cout<<"\n Please insert the New Cost: ";
cin>> cost;//read the cost from the keyboard to C++

/*Make the query command to be sent to SQL*/
strcpy(com2,"UPDATE FLIGHTS SET Cost= ");
strcat(com2, cost);/*include the value of cost in the query*/
strcat(com2," WHERE AIRLINE = '");
strcat(com2,code);/*include the value of code in the query*/
strcat(com2, "' AND Depart= '");
strcat(com2, depart);/*include the value of depart in the query*/
strcat(com2, "' AND Arrives= '");
strcat(com2, arrive);/*include the value of arrive in the query*/
strcat(com2, "';");

cout<<com2;
cout <<"Entering Information ..."; 
		status = mysql_query(conn, com2);//sent the query

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the user try to insert a value that is already in the Table
	
		cout << mysql_error(&mysql) << endl;
	}
	else{	
		cout << "Done" << endl;
	}
cout<<tot;//print the total of values transfered
}

else if(cho == 8){/*Process the Option 8*/

cout<<"\n Please insert the airline code:";
cin>>code;//read the code from the keyboard to C++
				cout<<"\n Please insert the Depart:";
cin>> depart;//read the depart from the keyboard to C++
		cout<<"\n Please insert the Arrival:";
cin>> arrive;//read the arrive from the keyboard to C++

/*Make the query command to be sent to SQL*/
strcpy(com2,"DELETE FROM FLIGHTS");
strcat(com2," WHERE AIRLINE = '");
strcat(com2,code);/*include the value of code in the query*/
strcat(com2, "' AND Depart= '");
strcat(com2, depart);/*include the value of depart in the query*/
strcat(com2, "' AND Arrives= '");
strcat(com2, arrive);/*include the value of arrive in the query*/
strcat(com2, "';");

cout<<com2;
cout <<"deleating Information ..."; 
		status = mysql_query(conn, com2);//sent the query

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the user try to insert a value that is already in the Table
		cout << mysql_error(&mysql) << endl;
	}
	else
		cout << "Done" << endl;
}

else if(cho == 11){/*Process the Option 11*/

cout<<"\n Please insert the airline code:";
cin>>code;//read the code from the keyboard to C++
		cout<<"\n Please insert the New Airline name:";
cin>> airname;//read the airline name from the keyboard to C++

/*Make the query command to be sent to SQL*/
strcpy(com2,"UPDATE FLIGHTS SET AirlineName= '");
strcat(com2, airname);/*include the value of airname in the query*/
strcat(com2,"' WHERE AIRLINE = '");
strcat(com2,code);/*include the value of code in the query*/
strcat(com2, "';");

cout<<com2;
cout <<"Entering Information ..."; 
		status = mysql_query(conn, com2);//sent the query

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the user try to modified a cost of a not existing Airline
	
		cout << mysql_error(&mysql) << endl;
	}
	else
		cout << "Done" << endl;
}

else if(cho == 9){/*Process the Option 9*/

cout<<"\n Please insert the Code:";
cin>>code;//read the code from the keyboard to C++

/*Make the query command to be sent to SQL*/
strcpy(com2,"DELETE FROM AIRPORTS");
strcat(com2," WHERE CODE = '");
strcat(com2,code);/*include the value of code in the query*/
strcat(com2, "';");

cout<<com2;
cout <<"deleating Information ..."; 
		status = mysql_query(conn, com2);

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the user try delete introducing a not existing code
		cout << mysql_error(&mysql) << endl;
	}
	else
		cout << "Done" << endl;
cout<<"\n";

/*Make the query command to be sent to SQL*/
strcpy(com2,"DELETE FROM FLIGHTS");
strcat(com2," WHERE Arrives = '");
strcat(com2,code);/*include the value of code in the query*/
strcat(com2, "' ");
strcat(com2, "OR Depart = '");
strcat(com2,code);/*include the value of code in the query*/
strcat(com2, "';");


cout<<com2;
cout <<"deleating Information ..."; 
		status = mysql_query(conn, com2);

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the user try to delete a value refering a airport that does not have flies
		cout << mysql_error(&mysql) << endl;
	}
	else
		cout << "Done" << endl;

}


else if(cho == 10){/*Process the Option 10*/



status = mysql_query(conn, "SELECT STATE, CODE, SUM(NumGates)as AVGGates  FROM AIRPORTS GROUP BY STATE;");//sent the query

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the process to calculate the Average is wrong
		cout << mysql_error(&mysql) << endl;
	}
	else{
		res = mysql_store_result(conn);	
	//	cout<<res; TAKE OUT TO THE SCREEM THE RESULT
	cout<<"\nSTATE CODE   SUM\n";
		// Printing the table with Average and the states
	for(row=mysql_fetch_row(res);
		row!=NULL;
		row=mysql_fetch_row(res))
	{
		cout << row[0] << "    " << row[1] <<"    "<< row[2]<< endl;
	}
	

	}






status = mysql_query(conn, "SELECT STATE, CODE, AVG(NumGates)as AVGGates  FROM AIRPORTS GROUP BY STATE;");//sent the query

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the process to calculate the Average is wrong
		cout << mysql_error(&mysql) << endl;
	}
	else{
		res = mysql_store_result(conn);	
	//	cout<<res; TAKE OUT TO THE SCREEM THE RESULT
	cout<<"\nSTATE   CODE   AVG\n";
		// Printing the table with Average and the states
	for(row=mysql_fetch_row(res);
		row!=NULL;
		row=mysql_fetch_row(res))
	{
		cout << row[0] << "     " << row[1] <<"    "<< row[2]<< endl;
	}
	

	}

}

else if(cho == 6){/*Process the Option 6*/
				cout<<"\n Please insert the Depart:";
cin>> depart;//read the depart from the keyboard to C++
		cout<<"\n Please insert the Arrival:";
cin>> arrive;//read the arrive from the keyboard to C++
cout<<"\n Please insert the maximum number of connections:";
cin>> max;//read the maximum number of scales one for the user

/*****for 0 scales******/
/*Make the query command to be sent to SQL*/
cout<<"\nFights Without connection\n";
strcpy(com2,"SELECT AIRLINE, Cost FROM FLIGHTS");
strcat(com2," WHERE Arrives = '");
strcat(com2, arrive);/*include the value of arrives in the query*/
strcat(com2, "' ");
strcat(com2, "AND Depart = '");
strcat(com2,depart);/*include the value of depart in the query*/
strcat(com2, "';");

status = mysql_query(conn, com2); //sent the query

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the query have an error on it calculation
		cout << mysql_error(&mysql) << endl;
	}
	else{
		res = mysql_store_result(conn);	
	
		cout << "Done" << endl;

	//Printing the query with the airline and costs
		for(row=mysql_fetch_row(res);
		row!=NULL;
		row=mysql_fetch_row(res))
	{
		
		cout << row[0] << "  " << row[1] << endl;
	}
	}

/***FOR 1 SCALE***/
	if(max> 0){
cout<<"\nFlights With 1 connection\n";
/*Make the query command to be sent to SQL*/
strcpy(com2,"CREATE VIEW HELP1 AS SELECT AIRLINE, Arrives, Cost FROM FLIGHTS WHERE Depart= '");
strcat(com2,depart);
strcat(com2, "';");

//Create a new view that keep the arrives of the flights where the depart port is the indicated
status = mysql_query(conn, com2); //sent the query
if (status!=0){
status = mysql_query(conn, "DROP VIEW HELP1;"); //Drop the view, in the case it already exist

/*Make the query command to be sent to SQL*/
strcpy(com2,"CREATE VIEW HELP1 AS SELECT AIRLINE, Arrives, Cost FROM FLIGHTS WHERE Depart= '");
strcat(com2,depart);
strcat(com2, "';");

status = mysql_query(conn, com2);//Create a new view that keep the arrives of the flights where the depart port is the indicated

}

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the process to take the arrive ports fail
		cout << mysql_error(&mysql) << endl;
	
	}
	else{
		res = mysql_store_result(conn);	
	
		/*Make the query command to be sent to SQL*/
strcpy(com2,"SELECT DISTINCT FLIGHTS.AIRLINE, HELP1.AIRLINE, Depart, FLIGHTS.Cost+HELP1.Cost AS TOTAL FROM FLIGHTS, HELP1 WHERE Depart=HELP1.Arrives AND FLIGHTS.Arrives = '");
strcat(com2,arrive);
strcat(com2, "';");
status = mysql_query(conn, com2);//sent the query

	if (status!=0)//Check if there is an error in the query
	{			  //Error will be sent if the process to take the middle airports fail
		cout << mysql_error(&mysql) << endl;
	}
	else{
		res = mysql_store_result(conn);	
		cout << "Done" << endl;
}

	// Printing the table with Average and the states	
	for(row=mysql_fetch_row(res);
		row!=NULL;
		row=mysql_fetch_row(res))
	{
		// print out the first 2 colums; they are stored in
		//    an "array-like" manner
		cout << row[0] << " "<<row[1]<<" "<<row[2]<<" "<<row[3]<< endl;
	}


	}//termina el else de que Se pudo ejecutar la 1ra parte



	}
/***FOR 2 SCALES***/
	if(max>1){

cout<<"\nFlights With 2 connection\n";
//Create a view that will keep the connection flight and partial cost
status = mysql_query(conn, "CREATE VIEW HELP2 AS SELECT FLIGHTS.Depart, FLIGHTS.Arrives, FLIGHTS.Cost+HELP1.Cost AS TOTAL FROM FLIGHTS, HELP1 WHERE Depart=HELP1.Arrives;");

if (status!=0)//Check if there is an error in the query
	{		  //Error will be sent if the process to take the middle airports fail
status = mysql_query(conn, "DROP VIEW HELP2;");

status = mysql_query(conn, "CREATE VIEW HELP2 AS SELECT FLIGHTS.Depart, FLIGHTS.Arrives, FLIGHTS.Cost+HELP1.Cost AS TOTAL FROM FLIGHTS, HELP1 WHERE Depart=HELP1.Arrives;");

}

	
/*Make the query command to be sent to SQL*/	

strcpy(com2,"SELECT DISTINCT HELP2.Depart, HELP2.Arrives, FLIGHTS.Cost+HELP2.TOTAL AS TOTAL FROM FLIGHTS, HELP2 WHERE FLIGHTS.Depart=HELP2.Arrives AND FLIGHTS.Arrives = '");
strcat(com2,arrive);
strcat(com2, "';");

	status = mysql_query(conn, com2);
	
		if (status!=0)//Check if there is an error in the query
	 { //Error will be sent if the process to take the middle airports fail
	
		cout << mysql_error(&mysql) << endl;
	}
	else{
		res = mysql_store_result(conn);	
		cout << "Done" << endl;
		
		//printing the query with the conections 
		for(row=mysql_fetch_row(res);
		row!=NULL;
		row=mysql_fetch_row(res))
	{
		// print out the first colum; they are stored in
		//    an "array-like" manner
		cout << row[0] << row[1]<< row[2]<<endl;
	}
	}
	
	}
}

else if(cho == 12)/*Process the Option 12*/
return 1;//End the program


}while(cho!=12);

	// clean up the query
	mysql_free_result(res);

	// clean up the connection
	mysql_close(conn);

	return 0;
}