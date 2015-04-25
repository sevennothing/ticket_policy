#include <string>
#include <vector>
#include <iostream>
#include <v8.h>
#include <node.h>
#include <node_buffer.h>
#include <time.h>
#include <stdlib.h>

using namespace std;
using namespace v8;
using namespace node;



typedef struct sellerInfo {
    int sellerID;
    int historyOrderCnt;
    int todayOrderCnt;
    int todayPushCnt;
    float historyRate;
    float pushRate;
    float alpha;
    float beta;
    float grade;
}SI;

typedef struct range {
   float left;
   float right;
}RANGE;

class ticketPolicy {
    public:
        ticketPolicy();
        ~ticketPolicy();

        int init_ticket_policy(long *pTickets);
        int init_ticket_policy(float *pTickets);
        int run_ernie();
        int set_compensation(long advance_tickets);

    private:
        long compensationFactor;
        vector<float> ticketsPolicy;
        vector<RANGE> ticketRange;


};

ticketPolicy::ticketPolicy(){
	//cout<< "ticketPolicy()"<<endl;
}

ticketPolicy::~ticketPolicy(){
	//cout<< "~ticketPolicy()"<<endl;

}

int ticketPolicy::init_ticket_policy(long *pTickets){
    if( pTickets != NULL){
        ticketsPolicy.push_back((float)1/(*pTickets));
    }

    int size = ticketsPolicy.size();
    RANGE tr;
    tr.left = 0;
    tr.right = 0;
	vector<float>::iterator it;
    for( it=ticketsPolicy.begin(); it!=ticketsPolicy.end(); it++){
        tr.left = tr.right;
        tr.right = tr.left + *it;
        ticketRange.push_back(tr);
    }

#if 0
    for(int i=0; i<size; i++){
        cout<< "ticketsPolicy[" << i << "]=" << ticketsPolicy[i] <<endl;
    }
    for(int i=0; i<size; i++){
            cout<< "ticketRange[" << i << "]=" << ticketRange[i].left << " " << ticketRange[i].right <<endl;
    }
#endif
    return 0;
}

int ticketPolicy::init_ticket_policy(float *pTickets){
    if( pTickets == NULL){
		return -1;
    }
	while(*pTickets != '\0'){
		ticketsPolicy.push_back(*pTickets);
		pTickets++;
	}

    int size = ticketsPolicy.size();
    RANGE tr;
    tr.left = 0;
    tr.right = 0;
	vector<float>::iterator it;
    for(it=ticketsPolicy.begin(); it!=ticketsPolicy.end(); it++){
        tr.left = tr.right;
        tr.right = tr.left + *it;
        ticketRange.push_back(tr);
    }

#if 0
    for(int i=0; i<size; i++){
        cout<< "float ticketsPolicy[" << i << "]=" << ticketsPolicy[i] <<endl;
    }
    for(int i=0; i<size; i++){
            cout<< "float ticketRange[" << i << "]=" << ticketRange[i].left << " " << ticketRange[i].right <<endl;
    }
#endif
    return 0;
}


int ticketPolicy::run_ernie(){
    srand((unsigned)time(NULL));

    float value = rand() / double(RAND_MAX);

    //查询落在哪个区间
    for(int i=0; i < ticketRange.size(); i++ ){
        if(value >= ticketRange[i].left && value < ticketRange[i].right){
            return i;
        }else if( (i ==( ticketRange.size() -1)) && (value == ticketRange[i].right)){
            return i;
        }
    }
    return -1;
}

Handle <Value> ticket_policy(const Arguments &args){

    HandleScope scope;
    ticketPolicy *pTicketPolicy = new ticketPolicy();

    Handle<Array> array = Handle<Array>::Cast(args[0]);

#if 0
    //确保参数是回调函数，是函数
    if (!args[1]->IsFunction()) {
	  return ThrowException(Exception::TypeError(
			  String::New("Second argument must be a callback function")));
	}
	Local<Function> callback = Local<Function>::Cast(args[1]);
#endif

    float *ticketArray = new float[array->Length() + 1];

	int i = 0;
    for(i=0; i<array->Length(); i++){
       //*(ticketArray+i) = array->Get(i)->NumberValue()->Value();
       *(ticketArray+i) = array->Get(i)->NumberValue();
    }
	*(ticketArray+i) = '\0';
#if 0
	for(int i=0; i<array->Length(); i++)
		cout << "ticketArray = " << ticketArray[i]<<endl;
#endif
    pTicketPolicy->init_ticket_policy(ticketArray);

    delete []ticketArray;

    int ticketItem = pTicketPolicy->run_ernie();

    return scope.Close(Integer::New(ticketItem));
}

void init(Handle <Object> target){
    target->Set(String::NewSymbol("ticket_policy"),FunctionTemplate::New(ticket_policy)->GetFunction());
}

NODE_MODULE(ticket_policy, init);
