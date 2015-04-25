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

class couponPolicy {
    public:
        couponPolicy();
        ~couponPolicy();

        int init_coupon_policy(long *pTickets);
        int init_coupon_policy(float *pTickets);
        int run_ernie();
        int set_compensation(long advance_coupons);

    private:
        long compensationFactor;
        vector<float> couponsPolicy;
        vector<RANGE> couponRange;


};

couponPolicy::couponPolicy(){
	//cout<< "couponPolicy()"<<endl;
}

couponPolicy::~couponPolicy(){
	//cout<< "~couponPolicy()"<<endl;

}

int couponPolicy::init_coupon_policy(long *pTickets){
    if( pTickets != NULL){
        couponsPolicy.push_back((float)1/(*pTickets));
    }

    int size = couponsPolicy.size();
    RANGE tr;
    tr.left = 0;
    tr.right = 0;
	vector<float>::iterator it;
    for( it=couponsPolicy.begin(); it!=couponsPolicy.end(); it++){
        tr.left = tr.right;
        tr.right = tr.left + *it;
        couponRange.push_back(tr);
    }

#if 0
    for(int i=0; i<size; i++){
        cout<< "couponsPolicy[" << i << "]=" << couponsPolicy[i] <<endl;
    }
    for(int i=0; i<size; i++){
            cout<< "couponRange[" << i << "]=" << couponRange[i].left << " " << couponRange[i].right <<endl;
    }
#endif
    return 0;
}

int couponPolicy::init_coupon_policy(float *pTickets){
    if( pTickets == NULL){
		return -1;
    }
	while(*pTickets != '\0'){
		couponsPolicy.push_back(*pTickets);
		pTickets++;
	}

    int size = couponsPolicy.size();
    RANGE tr;
    tr.left = 0;
    tr.right = 0;
	vector<float>::iterator it;
    for(it=couponsPolicy.begin(); it!=couponsPolicy.end(); it++){
        tr.left = tr.right;
        tr.right = tr.left + *it;
        couponRange.push_back(tr);
    }

#if 0
    for(int i=0; i<size; i++){
        cout<< "float couponsPolicy[" << i << "]=" << couponsPolicy[i] <<endl;
    }
    for(int i=0; i<size; i++){
            cout<< "float couponRange[" << i << "]=" << couponRange[i].left << " " << couponRange[i].right <<endl;
    }
#endif
    return 0;
}


int couponPolicy::run_ernie(){
   // srand((unsigned)time(NULL));

    float value = rand() / double(RAND_MAX);

    //查询落在哪个区间
    for(int i=0; i < couponRange.size(); i++ ){
        if(value >= couponRange[i].left && value < couponRange[i].right){
            return i;
        }else if( (i ==( couponRange.size() -1)) && (value == couponRange[i].right)){
            return i;
        }
    }
    return -1;
}

Handle <Value> coupon_policy(const Arguments &args){

    HandleScope scope;
    couponPolicy *pTicketPolicy = new couponPolicy();

    Handle<Array> array = Handle<Array>::Cast(args[0]);

#if 0
    //确保参数是回调函数，是函数
    if (!args[1]->IsFunction()) {
	  return ThrowException(Exception::TypeError(
			  String::New("Second argument must be a callback function")));
	}
	Local<Function> callback = Local<Function>::Cast(args[1]);
#endif

    float *couponArray = new float[array->Length() + 1];

	int i = 0;
    for(i=0; i<array->Length(); i++){
       //*(couponArray+i) = array->Get(i)->NumberValue()->Value();
       *(couponArray+i) = array->Get(i)->NumberValue();
    }
	*(couponArray+i) = '\0';
#if 0
	for(int i=0; i<array->Length(); i++)
		cout << "couponArray = " << couponArray[i]<<endl;
#endif
    pTicketPolicy->init_coupon_policy(couponArray);

    delete []couponArray;

    int couponItem = pTicketPolicy->run_ernie();

    return scope.Close(Integer::New(couponItem));
}

void init(Handle <Object> target){
    target->Set(String::NewSymbol("coupon_policy"),FunctionTemplate::New(coupon_policy)->GetFunction());
}

NODE_MODULE(coupon_policy, init);
