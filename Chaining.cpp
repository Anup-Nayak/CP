#include "Chaining.h"

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

Chaining::Chaining(){
    size=0;
}

void Chaining::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    Account *acc = new Account();
    acc->balance=count;
    acc->id=id;
    int h = hash(id);
    if(bankStorage2d.empty()){
        bankStorage2d.assign(100003,bankStorage1d);
    }

    bankStorage2d[h].push_back(*acc);

    size++;
    acc=nullptr;
    delete[] acc;

}

std::vector<int> Chaining::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE

    std::vector<int> temp;
    int s=databaseSize();
    if(s==0){
        return temp;
    }
    for(int i=0;i<bankStorage2d.size();i++){
        if(!bankStorage2d[i].empty()){
            for(int j=0;j<bankStorage2d[i].size();j++){
                temp.push_back(bankStorage2d[i][j].balance);
            }
        }
    }
    if(temp.size()==0){
        return temp;
    }
    std::vector<int> sortedVector = mergeSort(temp);
    
    if(k>size){
        return sortedVector;
    }else{
        std::vector<int> temp1;
        for(int i=0;i<k;i++){
            temp1.push_back(sortedVector[i]);
        }

        return temp1;

    }

}

int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);

    if(doesExist(id)){
        for(int i=0; i<bankStorage2d[h].size();i++){
            if(bankStorage2d[h][i].id==id){
                return bankStorage2d[h][i].balance;
            }
        }
        return -1;
    }else{
        return -1;
    }

}

void Chaining::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);

    if(doesExist(id)){
        for(int i=0; i<bankStorage2d[h].size();i++){
            if(bankStorage2d[h][i].id==id){
                bankStorage2d[h][i].balance+=count;
            }
        }
    }else{
        createAccount(id,count);
    }

}

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);


    if(!bankStorage2d[h].empty()){
            for(int j=0;j<bankStorage2d[h].size();j++){
                if(bankStorage2d[h][j].id==id){
                    return true;
                }
            }
        }

    return false;

}

bool Chaining::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);

    if(doesExist(id)){
        for(int j=0;j<bankStorage2d[h].size();j++){
                if(bankStorage2d[h][j].id==id){
                    bankStorage2d[h].erase(bankStorage2d[h].begin()+j);
                    size--;
                    return true;
                }
            }
    }
        return false;

}
int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Chaining::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h =0;
    for(int i=0;i<id.size();i++){
        ull a=int(id[i]);
        ull g=i%5;
        ull t=i%3;
        ull b= a*(power(11,g))+power(a,t);
        h+= b;


    }
    return h%100003;
}
