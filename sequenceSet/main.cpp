#include <iostream>
#include <bits/stdc++.h>
using namespace std;
string charToString(char arr[],int length)
{
    string stringToReturn="";
    for (int i = 0; i < length; ++i) {
        stringToReturn+=arr[i];
    }
    return stringToReturn;
}
string fillTheSpace(int value,string space,int length)
{
    string stringWithSpaces= to_string(value);
    while(stringWithSpaces.length()<length)
    {
        string spaceChar = space;
        stringWithSpaces=spaceChar.append(stringWithSpaces);
    }
    return stringWithSpaces;
}
int headerEmp(){
    ifstream sequenceSet;
    sequenceSet.open("sequenceSet.txt",ios::in);
    string hEmp = "";
    char hE;
    for (int i = 0; i < 4; ++i) {
        sequenceSet>>hE;
        hEmp+=hE;
    }
    if (hEmp=="00-1"){
        return -1;
    }
    int firstEmpRecord = stoi(hEmp);
    return firstEmpRecord;
}
int headerNonEmpty(){
    ifstream sequenceSet;
    sequenceSet.open("sequenceSet.txt",ios::in);
    sequenceSet.seekg(4);
    string hEmp = "";
    char hE;
    for (int i = 0; i < 4; ++i) {
        sequenceSet>>hE;
        hEmp+=hE;
    }
    if (hEmp=="00-1"){
        return -1;
    }
    int firstEmpRecord = stoi(hEmp);
    return firstEmpRecord;
}
void createBlocks(int numOfBlocks, int numOfRecords){
    ifstream checkFile;
    checkFile.open("sequenceSet.txt",ios::in);
    if ( checkFile.good() ){
        return;
    }
    ofstream sequenceSet;
    sequenceSet.open("sequenceSet.txt",ios::out);
    int maxVal = 0000;
    int numOfBlock = 2;
    string full = "";
    sequenceSet << setfill ('0') <<setw (4);
    sequenceSet << 1 ;
    sequenceSet << setfill ('0') <<setw (4);
    sequenceSet << -1 ;
    for (int i = 0; i < numOfRecords*8 ; ++i) {
        full+="@";
    }
    for(int i=0 ; i < numOfBlocks-1 ; i++){
        sequenceSet << setfill ('0') <<setw (4);
        sequenceSet << numOfBlock ;
        numOfBlock++;
        sequenceSet << setfill ('0') <<setw (4);
        sequenceSet << maxVal ;
        sequenceSet<<full;
    }

    sequenceSet << setfill ('0') <<setw (4);
    sequenceSet << -1 ;
    sequenceSet << setfill ('0') <<setw (4);
    sequenceSet << maxVal ;
    sequenceSet<<full;
    sequenceSet.close();
}
int getNext(int recordNo, int numOfRecords)
{
    ifstream sequenceSet;
    sequenceSet.open("sequenceSet.txt", ios::in);
    int z =(8 + (recordNo - 1) * (numOfRecords+1) * 8);
    sequenceSet.seekg(8 + (recordNo - 1) * (numOfRecords+1) * 8);
    char x ;
    string y;
    for (int i = 0; i < 4; ++i) {
        sequenceSet >> x;
        y +=x;
    }
    sequenceSet.close();
    if(y=="00-1")
        return -1;
    return stoi(y);
    int c;
}
void setNext(int recordNo,int next, int numOfRecords)
{
    fstream sequenceSet;
    sequenceSet.open("sequenceSet.txt", ios::in|ios::out);
    sequenceSet.seekg(8 + (recordNo - 1) * (numOfRecords+1) * 8);

    sequenceSet << fillTheSpace(next,"0",4);

    sequenceSet.close();

}
int getMax(int recordNo, int numOfRecords)
{
    ifstream sequenceSet;
    sequenceSet.open("sequenceSet.txt", ios::in);
    int pos=12 + (recordNo - 1) * (numOfRecords+1) * 8;
    sequenceSet.seekg(pos);
    char x ;
    string y="";
    for (int i = 0; i < 4; ++i) {
        sequenceSet >> x;
        y+=x;
    }
    sequenceSet.close();
    if(y=="00-1")
        return -1;
    return stoi(y);
}
int turnRRnToByte(int rrn,int numOfRecords){
    int x=(8 + (rrn-1)*8*(numOfRecords+1));
    return x ;
}
int searchBlock(int key, int numOfRecords){
    //insertion search
    //return RRn of block that val in.
    //search by key
    int rrnOfBlock;//RRn
    ifstream sequenceSet;
    sequenceSet.open("sequenceSet.txt", ios::in);
    int curBlock,maxVal,nextBlock;
    curBlock= headerNonEmpty();
    while(true){
        maxVal= getMax(curBlock,numOfRecords);
        nextBlock= getNext(curBlock,numOfRecords);
        if (key <= maxVal || nextBlock == -1){
            return curBlock;
        }
        curBlock=nextBlock;
    }
}
string loadBlock(int posOfBegBlock, int numOfRecords){
    string block="";
    ifstream sequenceSet;
    sequenceSet.open("sequenceSet.txt",ios::in);
    sequenceSet.seekg(posOfBegBlock);
    char pt;
    for (int i = 0; i < (numOfRecords+1)*8; ++i) {
        sequenceSet>>pt;
        block+=pt;
    }
    return block;
}//take block from file to string
void returnBlock(string newBlock,int posOfBegBlock){
    fstream sequenceSet;
    sequenceSet.open("sequenceSet.txt",ios::out|ios::in);
    sequenceSet.seekp(posOfBegBlock);
    sequenceSet<<newBlock;
    sequenceSet.close();
}//return new block to file
string sortBlock(string unSortedBlock){
    int numEmptySpaces=0;
    string block="";
    for (int i = 0; i < unSortedBlock.length(); ++i) {
        if (unSortedBlock[i]!='@'){
            block+=unSortedBlock[i];
        }
        else
        {
            numEmptySpaces++;
        }
    }
    if(8+numEmptySpaces==unSortedBlock.length())
    {//if all the block is empty
        unSortedBlock[4]='0';
        unSortedBlock[5]='0';
        unSortedBlock[6]='0';
        unSortedBlock[7]='0';
        return unSortedBlock;
    }
    vector<pair<int,int>>rec;
    string ke="";
    string va="";
    int kk;
    int vv;

    for (int i = 8; i < block.length()-4; ++i) {
        ke+=block[i];
        va+=block[i + 4];
        if ( i%4 == 3 && i!=0){
            i+=4;
            kk = stoi(ke);
            vv = stoi(va);
            rec.push_back({kk,vv});
            ke="";
            va="";
        }
    }
    sort(rec.begin(), rec.end());
    int maxK=rec[rec.size() - 1].first;
    string sortedBlock="";
    for (int i = 0; i < 4; ++i) {
        sortedBlock+=block[i];
    }
    string maxValue= to_string(maxK);
    while(maxValue.length()<4)
    {
        string zero="0";
        maxValue=zero.append(maxValue);
    }
    sortedBlock+=maxValue;
    for (int i = 0; i < rec.size(); ++i) {
        string keyy= to_string(rec[i].first);
        while(keyy.length()<4)
        {
            string zero="0";
            keyy=zero.append(keyy);
        }
        string value= to_string(rec[i].second);
        sortedBlock+=keyy;
        while(value.length()<4)
        {
            string zero="0";
            value=zero.append(value);
        }
        sortedBlock+=value;
        //cout<<rec[i].first<<" "<<rec[i].second<<"\n";
    }
    for (int i = 0; i < numEmptySpaces; ++i) {
        sortedBlock.append("@");
    }
    return sortedBlock;
}
void editMax(int recordNum,int numOfRecords)
{
    int blockPosition=turnRRnToByte(recordNum,numOfRecords);
    string block= loadBlock(blockPosition,numOfRecords);
    block = sortBlock(block);
    returnBlock(block,blockPosition);
}
void insert(string block,int key, int val,int blockNum,int numOfRecords){
    //val*4 key*4
    //4"@@@@key"4"val"
    string value= to_string(val);
    while(value.length()<4)
    {
        string zero="0";
        value=zero.append(value);
    }
    string curKey= to_string(key);
    while(curKey.length()<4)
    {
        string zero="0";
        curKey=zero.append(curKey);
    }
    for (int i = 0; i < block.length(); ++i) {
        if (block[i]=='@'){
            for (int j = 0; j < 4; ++j) {
                block[j+i]=curKey[j];
            }
            i+=4;
            for (int j = 0; j < 4; ++j) {
                block[j+i]=value[j];
            }
            break;
        }
    }
    returnBlock(sortBlock(block), turnRRnToByte(blockNum, numOfRecords));
}

void splitBlock(int blockNum,string block,int numOfRecords){
    block = sortBlock(block);
    int firstEmptyBlock=headerEmp();
    int secondEmptyBlock= getNext(firstEmptyBlock,numOfRecords);
    string firstBlock="00000000";
    string secondBlock="00000000";
    for (int i = 8; i < block.length(); ++i) {
        if(i<(numOfRecords)*8)
        {
            firstBlock+=block[i];
        }
        else
        {
            secondBlock+=block[i];
        }
    }
    while(firstBlock.length()<8*(numOfRecords+1))
    {

        firstBlock.append("@");
    }
    while(secondBlock.length()<8*(numOfRecords+1))
    {
        secondBlock.append("@");
    }
    firstBlock=sortBlock(firstBlock);
    secondBlock= sortBlock(secondBlock);
    int next1=getNext(blockNum,numOfRecords);

    returnBlock(firstBlock, turnRRnToByte(blockNum,numOfRecords));
    returnBlock(secondBlock, turnRRnToByte(firstEmptyBlock,numOfRecords));
    fstream sequenceSet;
    sequenceSet.open("sequenceSet.txt",ios::out|ios::in);
    sequenceSet<<fillTheSpace(secondEmptyBlock,"0",4);
    setNext(firstEmptyBlock,next1 ,numOfRecords);
    setNext(blockNum,firstEmptyBlock,numOfRecords);

}
void insertRecord(int key,int value,int numOfRecords){
    //search rrn of block
    //load rnn
    //insert
    //sortBlock
    //return
    // next block Done if split
    //
    int blockNum;//rrn
    fstream sequenceSet;
    sequenceSet.open("sequenceSet.txt",ios::out|ios::in);
    if (headerNonEmpty() == -1){
        blockNum=1;
        sequenceSet<<"0002";
        sequenceSet<<"0001";
        sequenceSet<<"00-1";
    }
    else{
        blockNum= searchBlock(key, numOfRecords);
    }
    int blockByteOff;
    blockByteOff = turnRRnToByte(blockNum,numOfRecords);
    string block = loadBlock(blockByteOff,numOfRecords);
    if (block[block.length()-1]!='@'){
        //overflow
        block.append(fillTheSpace(key,"0",4));
        block.append(fillTheSpace(value,"0",4));
        splitBlock(blockNum,block,numOfRecords);
    }
    else{
        insert(block,key,value,blockNum, numOfRecords);
    }
}

int recordByteSearch(int key, int numOfRecords){
    //insertion search
    //return RRn of block that val in.
    //search by key
    int rrnOfBlock;//RRn
    ifstream sequenceSet;
    sequenceSet.open("sequenceSet.txt", ios::in);
    int curBlock,maxVal,nextBlock;
    curBlock= headerNonEmpty();
    while(true){
        maxVal= getMax(curBlock,numOfRecords);
        nextBlock= getNext(curBlock,numOfRecords);
        if (key <= maxVal || nextBlock == -1){//if the record exists it will be here
            sequenceSet.seekg(turnRRnToByte(curBlock,numOfRecords)+8,ios::cur);
            for (int i = 0; i < numOfRecords; ++i) {
                char reededKey[4];
                sequenceSet.read(reededKey,4);
                if(reededKey[0]=='@')
                {
                    sequenceSet.seekg(4,ios::cur);
                    continue;
                }
                if(stoi(charToString(reededKey,4)) == key)
                {
                    return turnRRnToByte(curBlock,numOfRecords)+8*(i+1);
                }
                sequenceSet.seekg(4,ios::cur);
            }
            return -1;
        }
        curBlock=nextBlock;
    }
}

int valuSearch(int key, int numOfRecords){
    //insertion search
    //return RRn of block that val in.
    //search by key
    int rrnOfBlock;//RRn
    ifstream sequenceSet;
    sequenceSet.open("sequenceSet.txt", ios::in);
    int curBlock,maxVal,nextBlock;
    curBlock= headerNonEmpty();
    while(true){
        maxVal= getMax(curBlock,numOfRecords);
        nextBlock= getNext(curBlock,numOfRecords);
        if (key <= maxVal || nextBlock == -1){//if the record exists it will be here
            sequenceSet.seekg(turnRRnToByte(curBlock,numOfRecords)+8,ios::cur);
            for (int i = 0; i < numOfRecords; ++i) {
                char reededKey[4];
                sequenceSet.read(reededKey,4);
                if(reededKey[0]=='@')
                {
                    sequenceSet.seekg(4,ios::cur);
                    continue;
                }
                if(stoi(charToString(reededKey,4)) == key)
                {
                    char valueToReturn[4];
                    sequenceSet.read(valueToReturn,4);
                    return stoi(charToString(valueToReturn,4));
                }
                sequenceSet.seekg(4,ios::cur);
            }
            return -1;
        }
        curBlock=nextBlock;
    }
}

int getNumberOfRecords(int blocknum,int numOfRecords)
{
    string block= loadBlock(turnRRnToByte(blocknum,numOfRecords),numOfRecords);
    int numNonEmptyRecords=0;
    for (int i = 0; i < block.size(); ++i) {
        if(block[i]=='@')
            numNonEmptyRecords++;
    }
    numNonEmptyRecords/=8;
    numNonEmptyRecords=numOfRecords-numNonEmptyRecords;
    return numNonEmptyRecords;
}

string popMinRecord(int blockNum, int numOfRecords)
{
    string block= loadBlock(turnRRnToByte(blockNum,numOfRecords),numOfRecords);
    string minRecord="";
    for (int i = 8; i < 16; ++i) {
        minRecord+=block[i];
        block[i]='@';
    }
    block= sortBlock(block);
    returnBlock(block, turnRRnToByte(blockNum,numOfRecords));
    return minRecord;
}

void deleteKey(int  key, int numOfRecords){
    int recordByte= recordByteSearch(key,numOfRecords);
    if(recordByte==-1)
        return;
    int currentBlockRRn;
    currentBlockRRn =searchBlock( key, numOfRecords);
    fstream sequenceSet;
    sequenceSet.open("sequenceSet.txt",ios::out|ios::in);
    sequenceSet.seekp(recordByte,ios::cur);
    sequenceSet<<"@@@@@@@@";
    sequenceSet.close();
    editMax(currentBlockRRn,numOfRecords);
    string block = loadBlock(turnRRnToByte(currentBlockRRn,numOfRecords),numOfRecords);
    int minNumOfRecords =((numOfRecords % 2 + numOfRecords) / 2);

    if(block [minNumOfRecords * 8] == '@')
    {//underflow!

        int nextBlock = getNext(currentBlockRRn,numOfRecords);
        int recordNumInNextBlock = getNumberOfRecords(nextBlock,numOfRecords);
        string recordToShare;

        if(recordNumInNextBlock>minNumOfRecords)
        {//redistribute with the right
            cout<<"first case\n";
            recordToShare= popMinRecord(nextBlock, numOfRecords);
            block.erase(block.length()-8);
            block.append(recordToShare);
            block= sortBlock(block);
            returnBlock(block, turnRRnToByte(currentBlockRRn,numOfRecords));
        }
        else
        {//merge
            cout<<"merge\n";
            block.erase(block.length()-(recordNumInNextBlock*8));
            for (int i = 0; i < recordNumInNextBlock; ++i) {
                block.append(popMinRecord(nextBlock, numOfRecords));
            }
            block=sortBlock(block);
            returnBlock(block, turnRRnToByte(currentBlockRRn,numOfRecords));
            setNext(currentBlockRRn, getNext(nextBlock,numOfRecords),numOfRecords);
            setNext(nextBlock,headerEmp(),numOfRecords);
            sequenceSet.open("sequenceSet.txt",ios::out|ios::in);

            sequenceSet<<fillTheSpace(nextBlock,"0",4);
            sequenceSet.close();
        }
    }
    return;

}

int main() {
    cout<<"Enter number of blocks :";
    int numberOFBlocks;
    cin>>numberOFBlocks;

    cout<<"Enter number of records :";
    int numberOFRecords;
    cin>>numberOFRecords;

    createBlocks(numberOFBlocks,numberOFRecords);

    while (true)
    {
        cout<<"1-Insert"<<endl;
        cout<<"2-delete"<<endl;
        cout<<"3-search"<<endl;
        cout<<"4-exit"<<endl;
        cout<<"Enter your choice:";
        int choice;
        cin>>choice;
        if(choice==1)
        {
            int key,value;
            cout<<"Enter the key to insert:";
            cin>>key;
            cout<<"Enter the value to insert:";
            cin>>value;
            insertRecord(key,value,numberOFRecords);
        }
        else if(choice==2)
        {
            int key;
            cout<<"Enter the key to delete:";
            cin>>key;
            deleteKey(key,numberOFRecords);
        }
        else if(choice==3)
        {
            int key;
            cout<<"Enter the key to search:";
            cin>>key;
            int value=valuSearch(key,numberOFRecords);
            if(value==-1)
            {
                cout<<"Not found"<<endl;
            }
            else
            {
                cout<<"Value : "<<value<<endl;
            }
        }
        else if(choice==4)
        {
            break;
        }
        else
        {
            cout<<"You entered wrong choice"<<endl;
        }
    }

    return 0;
}
// close file in all functions