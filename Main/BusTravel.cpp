#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <ctime>
#include <queue>
//#include <curl.h> // or another HTTP library
//#include <json/json.h>


using namespace std;

//declaration
const int v = 26;	//vertices
vector<tuple<int ,string, string, int ,int>> adj[v]; //vector
int sourceOption, destOption;	//user input of source and destination


//CURL *curl;
//CURLcode res;

//function definition
void addEdge();
int minutes();
void display();
void chooseDestination();

//addition in list
void addEdge(vector<tuple<int ,string, string, int ,int>> adj[], int source, int dest,string s, string d, int distance, int expectedtime){
	adj[source].push_back(make_tuple(dest,s, d, distance, expectedtime));	//connecting both side
    adj[dest].push_back(make_tuple(source,s ,d, distance, expectedtime));	//connecting both side
}

//randomly generating minutes according to given distance
int minutes(int dist){
	int min = dist + 1 + (rand() % 120);
//	if (distance > 1000)
//        min += 400;
//    else if (distance > 900)
//        min += 350;
//    else if (distance > 800)
//        min += 300;
//    else if (distance > 700)
//        min += 250;
//    else if (distance > 600)
//        min += 200;
//    else if (distance > 500)
//        min += 150;
//    else if (distance > 400)
//        min += 100;
//    else if (distance > 300)
//        min += 30;
//    }
    return min;
}

//Display All the connections(vertices and edges)
void display(vector<tuple<int ,string, string, int ,int>> adj[]) {
    for (int u = 0; u<v ; u++) {
        //cout << "Node " << u << " => ";
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++) {
            cout << "Node " << u << " => " << get<0>(*it) << " | City: " << get<1>(*it) << " , " <<get<2>(*it)<<  " | Distance = " << get<3>(*it) << "km | time = " << get<4>(*it) <<"mins" << endl;
        }
        cout << "\n\n";
    }
}

//Choosing Source and Destination
void chooseDestination(){
	cout << "---------------------------- LOCATIONS ----------------------------" << endl;
	cout << "0 - Gilgit\t\t"    		"1 - Skardu\t\t\t"   		"2 - Chilas\n" 
	  	 <<	"3 - Muzaffrabad\t\t"    	"4 - Peshawar\t\t\t"  		"5 - Rawalpindi\n"	
		 <<	"6 - Bannu\t\t"				"7 - Dera Ismail Khan\t\t"	"8 - Faisalabad\n"	
		 << "9 - Lahore\t\t"			"10 - Sahiwal\t\t\t"		"11 - Multan\n" 
		 << "12 - Bhawalpur\t\t"		"13 - Sibi\t\t\t"			"14 - Chaman\n" 			
		 << "15 - Quetta\t\t"			"16 - Kalat\t\t\t"			"17 - Sukkur\n" 
	 	 <<	"18 - Mirpur\t\t"			"19 - Hyderabad\t\t\t"		"20 - Karachi\n" 			
		 << "21 - Bela\t\t"				"22 - Nok Kundi\t\t\t"		"23 - Dalbandin\n" 
	 	 <<	"24 - Gawadar\t\t"			"25 - Pasni\n";
	cout << "-------------------------------------------------------------------" << endl;
	cout << "Choose the option(Number): " << endl;
	cout << "Source:  " ;
	cin >> sourceOption;
	cout << "Destination:  " ;
	cin >> destOption;
}

//shortest path from source to destination by dijkstra
int shortestDistance(){
	chooseDestination();
	
	//as its a adjaceny list so it will be shown as <weight, vertex>
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>  queue;	//declared minheap priority queue
	//initialize distance as infinity
	int distance[v];
	for(int i = 0 ; i< v ; i ++ ){
		distance[i] = INT_MAX;
	}
	
	distance[sourceOption] = 0;
	queue.push(make_pair(0,sourceOption));		//push source vertex and its distance(0) to queue
	
	while(!queue.empty()){		//loop till the loop is not empty
		int dis = queue.top().first;		// returns weight
		int u = queue.top().second;			//return the vertex(who has the min weight)
		queue.pop();		//remove it from queue
		
		for(auto x: adj[u]) {		//checks vertices
            int adjV = get<0>(x);
            int weight = get<3>(x);
			if(distance[adjV] > dis + weight){	
				distance[adjV] = dis + weight;
				queue.push(make_pair(distance[adjV] , adjV));
			}
		}
	}
	cout << distance[destOption]<< endl;
	return distance[destOption];
}

//shortest path from source to destination by PRIMS
void shortestDistancePath(){
	chooseDestination();
	
	int path[v];
	for(int i = 0 ; i<v ; i++){
		path[i] = INT_MAX;
	}
	int value = -1;
	vector<int> parent(v, -1);		//stores parent vertex
    vector<int> weight(v, INT_MAX);	//stores weight vertex
    vector<bool> visited(v, false);	
    weight[sourceOption] = 0;
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(0, sourceOption));
    
    while (!pq.empty()) {
        int v = pq.top().second;
        pq.pop();
     
		if(v == destOption)
			break;
        visited[v] = true;
        path[++value] = v;
		cout<< v << endl;
        for(auto x : adj[v]) {
            int adjV = get<0>(x);
            int w = get<3>(x);
            if (visited[adjV] == (false || 0) && weight[adjV] >  w) {
            	visited[adjV] = true;
                parent[adjV] = v;
                weight[adjV] =  w;
                pq.push(make_pair(weight[adjV],adjV));
            }
        }
    }
    cout << "SHORTEST PATH: " << endl;
    for(int i = 0; i<v ; i++){
    	if(path[i] != INT_MAX){
    		cout << "- " ;
    		switch(path[i]){
				case 0: 		cout << "Gilgit" << endl ; 				break; 
				case 1: 		cout << "Skardu" << endl ; 				break; 
				case 2: 		cout << "Chilas" << endl ; 				break; 
				case 3: 		cout << "Muzaffrabad" << endl ; 		break; 
				case 4: 		cout << "Peshawar" << endl ; 			break; 
				case 5: 		cout << "Rawalpindi" << endl ; 			break;  
				case 6: 		cout << "Bannu" << endl ; 				break;  
				case 7: 		cout << "Dera Ismail Khan" << endl ; 	break;  
				case 8: 		cout << "Faisalabad" << endl ; 			break;  
				case 9: 		cout << "Lahore" << endl ; 				break;  
				case 10: 		cout << "Sahiwal" << endl ; 			break;   
				case 11: 		cout << "Multan" << endl ; 				break;  
				case 12: 		cout << "Bhawalpur" << endl ; 			break;  
				case 13: 		cout << "Sibi" << endl ; 				break; 
				case 14:		cout << "Chaman" << endl ; 				break;  
				case 15: 		cout << "Quetta" << endl ; 				break;  
				case 16: 		cout << "Kalat" << endl ; 				break;  
				case 17: 		cout << "Sukkur" << endl ; 				break;  
				case 18: 		cout << "Mirpur" << endl ; 				break; 
				case 19: 		cout << "Hyderabad" << endl ; 			break;  
				case 20: 		cout << "Karachi" << endl ; 			break;  
				case 21: 		cout << "Bela" << endl ; 				break;  
				case 22: 		cout << "Nok Kundi" << endl ; 			break;  
				case 23: 		cout << "Dalbandin" << endl ; 			break;  
				case 24: 		cout << "Gawadar" << endl ; 			break;  
				case 25: 		cout << "Pasni" << endl ; 				break;  
			}
		}
	}
}

//returns adjacent cities
void adjacentCity(){
	chooseDestination();    //inputs source and destination points
	for (auto it = adj[sourceOption].begin(); it!=adj[sourceOption].end(); it++) {
        int v = get<0>(*it);
		cout << v << endl;
    }
}

//Display just stations
void displayStation(){
	cout << "---------------------------- LOCATIONS ----------------------------" << endl;
	cout << "0 - Gilgit\t\t"    		"1 - Skardu\t\t\t"   		"2 - Chilas\n" 
	  	 <<	"3 - Muzaffrabad\t\t"    	"4 - Peshawar\t\t\t"  		"5 - Rawalpindi\n"	
		 <<	"6 - Bannu\t\t"				"7 - Dera Ismail Khan\t\t"	"8 - Faisalabad\n"	
		 << "9 - Lahore\t\t"			"10 - Sahiwal\t\t\t"		"11 - Multan\n" 
		 << "12 - Bhawalpur\t\t"		"13 - Sibi\t\t\t"			"14 - Chaman\n" 			
		 << "15 - Quetta\t\t"			"16 - Kalat\t\t\t"			"17 - Sukkur\n" 
	 	 <<	"18 - Mirpur\t\t"			"19 - Hyderabad\t\t\t"		"20 - Karachi\n" 			
		 << "21 - Bela\t\t"				"22 - Nok Kundi\t\t\t"		"23 - Dalbandin\n" 
	 	 <<	"24 - Gawadar\t\t"			"25 - Pasni\n" <<endl;
}

//shortest time from source to destination by dijkstra
void shortestTime(){
	
}

//shortest time from source to destination by dijkstra
void shortestTimePath(){

}

void cost(){
	int people;
	int distance = shortestDistance();
	cout<< "How many people are travelling?: " << endl;
	cin >> people;
	int cost = 0;
	
	cost = people*distance*100;
	cout << "Cost: Rs. " << cost;
}

void fuel(){
	int distance = shortestDistance();
	int fuel;
	fuel = distance*1.01;
	cout << "Fuel: " << fuel <<"$" << endl;
}

void approxTime(){
	int distance = shortestDistance();
	int time = distance;
	if (distance > 1500)
        time += 600;
    if (distance > 1200)
        time += 500;
	if (distance > 1000)
        time += 400;
	if (distance > 1000)
        time += 400;
    else if (distance > 900)
        time += 350;
    else if (distance > 800)
        time += 300;
    else if (distance > 700)
        time += 250;
    else if (distance > 600)
        time += 200;
    else if (distance > 500)
        time += 150;
    else if (distance > 400)
        time += 100;
    else if (distance > 300)
        time += 30;
    cout << "Time: " << time << "mins"<< endl;
}

void BusesTime(){
	cout << "All Buses Timing: " << endl;
	cout << "Morning 9:00am";
}

void delivery(){
	
}

//connects edges with distance and weights
void connectingEdge(){
	//ADDING VERTICES AND CONNECTING EDGES
	addEdge(adj, 0, 1,"Gilgit","Skardu", 260, minutes(260));
	addEdge(adj, 0, 2,"Gilgit","Chilas", 228, minutes(228));
	addEdge(adj, 0, 3,"Gilgit","Muzaffrabad", 525, minutes(525));
	
	addEdge(adj, 1, 2,"Skardu","Chilas", 520, minutes(520));
	addEdge(adj, 1, 3,"Skardu","Muzaffrabad", 157, minutes(157));

	addEdge(adj, 2, 3,"Chilas","Muzaffrabad", 110, minutes(110));
    addEdge(adj, 2, 4,"Chilas","Peshawar", 550, minutes(550));
    
    addEdge(adj, 3, 4,"Muzaffrabad","Peshawar", 480, minutes(480));
    addEdge(adj, 3, 5,"Muzaffrabad","Muzaffrabad", 210, minutes(210));
    addEdge(adj, 3, 9,"Muzaffrabad","Lahore", 411, minutes(411));
    
    addEdge(adj, 4, 6,"Peshawar","Bannu", 160, minutes(160));
    
    addEdge(adj, 5, 6,"Rawalpindi","Bannu", 240, minutes(240));
    addEdge(adj, 5, 7,"Rawalpindi","Dera Ismail Khan", 427, minutes(427));
    addEdge(adj, 5, 11,"Rawalpindi","Multan", 720, minutes(720));
    addEdge(adj, 5, 9,"Rawalpindi","Lahore", 330, minutes(330));
    
    addEdge(adj, 6, 7,"Bannu","Dera Ismail Khan", 130, minutes(130));
    
    addEdge(adj, 7, 9,"Dera Ismail Khan","Lahore", 595, minutes(595));
    addEdge(adj, 7, 11,"Dera Ismail Khan","Multan", 420, minutes(420));
    addEdge(adj, 7, 13,"Dera Ismail Khan","Sibi", 719, minutes(719));
    
    addEdge(adj, 8, 9,"Faisalabad","Lahore", 90, minutes(90));
    addEdge(adj, 8, 10,"Faisalabad","Sahiwal ", 170, minutes(170));
    addEdge(adj, 8, 11,"Faisalabad","Multan", 320, minutes(320));
    
    addEdge(adj, 9, 10,"Lahore","Sahiwal ", 220, minutes(220));
    
    addEdge(adj, 10, 11,"Skardu","Multan", 250, minutes(250));
    addEdge(adj, 10, 12,"Skardu","Bhawalpur", 350, minutes(350));
    
    addEdge(adj, 11, 12,"Multan","Bhawalpur", 110, minutes(110));
    addEdge(adj, 11, 13,"Multan","Sibi", 998, minutes(998));
    addEdge(adj, 11, 17,"Multan","Sukkur", 650, minutes(650));
    
    addEdge(adj, 12, 17,"Bhawalpur","Sukkur", 550, minutes(550));
    addEdge(adj, 12, 18,"Bhawalpur","Mirpur", 1011, minutes(1011));
    
    addEdge(adj, 13, 17,"Sibi","Sukkur", 711, minutes(711));
    addEdge(adj, 13, 19,"Sibi","Hyderabad", 1008, minutes(1008));
    addEdge(adj, 13, 21,"Sibi","Bela", 818, minutes(818));
    addEdge(adj, 13, 16,"Sibi","Kalat", 480, minutes(480));
    addEdge(adj, 13, 15,"Sibi","Quetta", 280, minutes(280));
    addEdge(adj, 13, 14,"Sibi","Chaman", 480, minutes(480));
    
    addEdge(adj, 14, 15,"Chaman","Quetta", 118, minutes(118));
    
    addEdge(adj, 15, 16,"Quetta","Kalat", 380, minutes(380));
    
    addEdge(adj, 16, 21,"Kalat","Bela", 845, minutes(845));
    addEdge(adj, 16, 23,"Kalat","Dalbandin", 720, minutes(720));
    addEdge(adj, 16, 25,"Kalat","Pasni", 1201, minutes(1201));
    
    addEdge(adj, 17, 18,"Sukkur","Mirpur", 661, minutes(661));
    addEdge(adj, 17, 19,"Sukkur","Hyderabad", 619, minutes(619));
    
    addEdge(adj, 18, 19,"Mirpur","Hyderabad", 599, minutes(599));
    
    addEdge(adj, 19, 20,"Hyderabad","Karachi", 180, minutes(180));
    
    addEdge(adj, 20, 21,"Karachi","Bela", 679, minutes(679));
    
    addEdge(adj, 21, 25,"Bela","Pasni", 1101, minutes(1101));
    
    addEdge(adj, 22, 23,"Nok Kundi","Dalbandin", 515, minutes(515));
    addEdge(adj, 22, 24,"Dalbandin","Gawadar", 916, minutes(916));
    
    addEdge(adj, 23, 24,"Dalbandin","Gawadar", 995, minutes(995));
    
    addEdge(adj, 24, 25,"Gawadar","Pasni", 501, minutes(501));
}

main(){
	
	connectingEdge();
	//cost();
	//cout <<INT_MAX +INT_MAX+INT_MAX+INT_MAX+INT_MAX+INT_MAX<< endl;
//	shortestDistance();
//	shortestDistancePath();
	//shortestTimePath();
	fuel();
//displayStation();
//approxTime();
display(adj);
//    cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<< BUS STATION >>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
//	
//	cout << "\t0. Exit\n"
//		 << "\t1. shortest distance from source to destination\n"
//		 << "\t2. shortest time from source to destination\n"
//		 << "\t3. shortest path [by distance] from source to destination\n"
//		 << "\t4. shortest path [by time] from source to destination\n"
//		 << "\t5. display whole map\n"
//		 << "\t6. display all the stations" << endl;
//	int option;
//    do{
//    	cout << "\n-------------------------------------------------------------------" << endl;
//	    cout << "Option: ";
//	    cin >> option;
//	    switch(option){
//	    	case 1: 
//	    		minimum(destOption);
//	    		break;
//	    	case 2: 
//	    		
//	    		break;
//	    	case 3: 
//	    
//	    		break;
//	    	case 4: 
//	    		
//	    		break;
//	   		case 5: 
//	    		display(adj);
//	    		break;
//	    	case 6: 
//	    		displayStation();
//	    		break;
//	    	case 7: 
//	    		
//	    		break;
//		}
//	} while(option != 0);

	// 0 - Gilgit
	// 1 - Skardu
	// 2 - Chilas
	// 3 - Muzaffrabad
	// 4 - Peshawar
	// 5 - Rawalpindi
	// 6 - Bannu
	// 7 - Dera Ismail Khan
	// 8 - Faisalabad
	// 9 - Lahore
	// 10 - Sahiwal 
	// 11 - Multan
	// 12 - Bhawalpur
	// 13 - Sibi
	// 14 - Chaman
	// 15 - Quetta
	// 16 - Kalat
	// 17 - Sukkur
	// 18 - Mirpur
	// 19 - Hyderabad
	// 20 - Karachi
	// 21 - Bela
	// 22 - Nok Kundi
	// 23 - Dalbandin
	// 24 - Gawadar
	// 25 - Pasni
}
