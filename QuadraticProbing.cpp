#include "QuadraticProbing.h"

int p = 202067;
#define ull unsigned long long int
ull power(int x, int n){
    ull ans = 1;
    while (n > 0) {
        if (n%2 == 1) 
        {
            ans = ans * x;
        }
        x *=x;
        n/=2; 
    }
    return ans;
}


int exist(std::vector<Account> &v, std::string id,int h, int size){

    
    if(size==0){
        return -1;
    }else{
        if(v[h].id==id){
            return h;
        }else{
            ull n;
            ull j=1;

            while (true){
                n=(h+(j*j))%p;
                if(v[n].id=="u"){
                    return -1;
                }
                else if(v[n].id=="d"){
                    j++;
                }
                else if(v[n].id==id){
                    return n;
                }
                else{
                    j++;
                }
            }
        }

    }
}

void merge(std::vector<int> &arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);

    for (int i = 0; i < n1; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = arr[middle + 1 + j];
    }

    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] >= rightArray[j]) {  
            arr[k++] = leftArray[i++];
        } else {
            arr[k++] = rightArray[j++];
        }
    }

    while (i < n1) {
        arr[k++] = leftArray[i++];
    }

    
    while (j < n2) {
        arr[k++] = rightArray[j++];
    }
}

void mergeSort(std::vector<int> &arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        
        merge(arr, left, middle, right);
    }
}

std::vector<int> mergeSort(std::vector<int> arr) {
    mergeSort(arr, 0, arr.size() - 1);
    return arr;
}

QuadraticProbing::QuadraticProbing(){
    size=0;
}
void QuadraticProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if(bankStorage1d.size()==0){
        Account * temp = new Account;
        temp->balance= -1;
        temp->id = "u";
        bankStorage1d.assign(p,*temp);
        temp=nullptr;
        delete[] temp;
    }
    
    int h=hash(id);
    size++;
    

    if(bankStorage1d[h].id=="u" or bankStorage1d[h].id=="d"){
        bankStorage1d[h].balance=count;
        bankStorage1d[h].id=id;
        return;
    }else{

        ull j=1;
        ull i=(h+1)%p;
        while(true){
            if(bankStorage1d[i].id=="u" or bankStorage1d[i].id=="d"){
                bankStorage1d[i].balance=count;
                bankStorage1d[i].id=id;
                return;
            }else{
                j++;
                i = (h + j*j)%p;
            }
            
        }

    }
}

std::vector<int> QuadraticProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> temp1;
    int s=databaseSize();
    if(s==0 or bankStorage1d.size()==0){
        return temp1;
    }

    // IMPLEMENT YOUR CODE HERE
    std::vector<int> temp;
    for(int j=0;j<bankStorage1d.size();j++){
        temp.push_back(bankStorage1d[j].balance);  
    
    }
    
    for(int i=0;i<temp.size();i++){
        if(temp[i]>=0){
            temp1.push_back(temp[i]);
        }
    }
    if(temp1.size()==0){
        return temp1;
    }
    std::vector<int> sortedVector = mergeSort(temp1);
    
    
    if(k>size){
        return sortedVector;

    }else{
        std::vector<int> temp2;
        for(int i=0;i<k;i++){
            temp2.push_back(sortedVector[i]);
        }
        return temp2;


    }
    return std::vector<int>(); // Placeholder return value
}

int QuadraticProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE

    int hash_val= hash(id);
    int a = databaseSize();

    int b = exist(bankStorage1d,id,hash_val,a);
    if(b==-1){
        return -1;
    }else{
        return bankStorage1d[b].balance;
    }
    
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE

    int hash_val= hash(id);
    int a=databaseSize();

    int b=exist(bankStorage1d,id,hash_val,a);
    if(b==-1){
        createAccount(id,count);
    }else{
        bankStorage1d[b].balance+=count;
    }

    
}

bool QuadraticProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE

    int hash_val= hash(id);
    int a=databaseSize();

    int b=exist(bankStorage1d,id,hash_val,a);
    if(b==-1){
        return false;
    }else{
        return true;
    }

    // int hash_val= hash(id);
    // int a=databaseSize();
    // if(a==0){
    //     return false;
    // }else{
    //     if(bankStorage1d[hash_val].id==id){
    //         return true;
    //     }else{
    //         unsigned long long j=1;
    //         unsigned long long i=hash_val+1;
    //         while(bankStorage1d[i].id!=id && i!=hash_val){
    //             j++;
    //             i=(hash_val + j*j)%p;
    //         }
    //         if(bankStorage1d[i].id == id){
    //             return true;
    //         }
    //     }
    //     return false;

    // }
    // return false; // Placeholder return value
}

bool QuadraticProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE

    int hash_val= hash(id);
    int a=databaseSize();

    int b=exist(bankStorage1d,id,hash_val,a);
    if(b==-1){
        return false;
    }else{
        bankStorage1d[b].id="d";
        bankStorage1d[b].balance=-1;
        size--;
        return true;
    }
     // Placeholder return value
}
int QuadraticProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size;
    // Placeholder return value
}

int QuadraticProbing::hash(std::string id) {
    int h =0;
    for(int i=0;i<id.size();i++){
        ull a=int(id[i]);
        ull g=i%5;
        ull t=i%3;
        ull b= a*(power(11,g))+power(a,t);
        h+= b;

    }
    return h%202067;
}




