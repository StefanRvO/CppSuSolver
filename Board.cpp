#include<algorithm>
#include<iostream>
#include<random>
#include<stdlib.h>
#include<time.h>
using namespace std;
class Board { //Class to hold the board currently being solved
    private:
    bool OldSolvedNumbers[81];
    bool OldSolvedNumbers_B[81];
    int Candidates[81][9];
    int Candidates_B[81][9];
    int OldCandidates[81][9];
    int OldCandidates_B[81][9];
    bool SolvedNumbers[81];
    bool SolvedNumbers_B[81];
    bool GroupIsGood(int*);
    int OldBoardNumbers[81];
    int OldBoardNumbers_B[81];
    void CopyCandidates();    
    void FillCandidates();
    void CopyBoardNumbers();
    void CopySolvedNumbers();
    bool IsSameBoard(int*, int*);
    bool IsSameCandidates(int (*) [9],int (*) [9]);
    bool FindNakedSingles();
    bool IsSameCandidates();
    bool IsSolved();
    bool FindHiddenSingles();
    bool InCandidates(int, int);
    bool isInArray(int* array,int arraylen,int num);
    int CandidateLen(int * );
    int BruteForceRandom(int );
    bool BrFoRa=false;
    int BoardNumbers_B[81];
    bool FindPointingPairs();
    void RemoveCandidate(int,int);
    public:
    Board(char*);
    bool solved=false;
    int BoardNumbers[81];
    int BruteForce();
    void PrintBoard();
    bool CheckMissPlacements();
    bool CheckMissPlacements(int);
    bool LogicSolveBoard();
    bool BruteForceRandomParrent();
    void PrintBoardBrute();
    
    
};
Board::Board(char *BoardNum) {
    for(int i=0;i<81;i++) {
        for (int j=0;j<9;j++) Candidates[i][j]=0;
        if (BoardNum[i]-'0'>=1 and BoardNum[i]-'0'<=9) {
            SolvedNumbers[i]=true;
            BoardNumbers[i]=BoardNum[i]-'0';
            Candidates[i][0]=BoardNumbers[i];
            }
        else {
            SolvedNumbers[i]=false;
            BoardNumbers[i]=0;
        }
    }
    FillCandidates();
    srand(time(NULL));
}
bool Board::IsSameBoard(int *Board1,int *Board2) {
    for (int i=0;i<81;i++) {
        if (Board1[i]!=Board2[i]) return false;
        }
    return true;
    }
bool Board::IsSameCandidates(int Candidates1[81][9],int Candidates2[81][9]) {
    for (int i=0;i<81;i++) {
        for(int j=0;j<9;j++) {
            if (Candidates1[i][j]!=Candidates2[i][j]) return false;
            }
        }
    return true;
    }
bool Board::IsSolved() {
    if (!BrFoRa) {
        for (int i=0;i<81;i++) {
            if (SolvedNumbers[i]) continue;
                return false;
            }
        return true;
        }
    for (int i=0;i<81;i++) {
        if (SolvedNumbers_B[i]) continue;
             return false;
        }
    return true;
    }
bool Board::LogicSolveBoard() {
    int naked=0;
    int hidden=0;
    int PointingPairs=0;
    FillCandidates();
    while(true) {
        CopyBoardNumbers();
        while(true) {
            FindPointingPairs();
            naked=FindNakedSingles();
            hidden=FindHiddenSingles();
            if (!(hidden or naked)) break;
            else {
                if(!BrFoRa) {
                    if (!IsSameBoard(BoardNumbers,OldBoardNumbers)) FillCandidates();
                    }
                else {
                    if (!IsSameBoard(BoardNumbers_B,OldBoardNumbers_B)) FillCandidates();
                    }
                //FindNakedPairsTripplesQuads();
                //FindHiddenPairsTripplesQuads();
                }
           }
        while(true) {
            CopyCandidates();
            //NakedGroups=NakedGroups=FindNakedPairsTripplesQuads();
            //HiddenGroups=FindHiddenPairsTripplesQuads();
            PointingPairs=FindPointingPairs();
            if (!BrFoRa) {
                if (IsSameCandidates(Candidates,OldCandidates)) break;
                }
            else {
                if (IsSameCandidates(Candidates_B,OldCandidates_B)) break;
                }
            }
        naked=FindNakedSingles();
        hidden=FindHiddenSingles();
        if (!(hidden or naked)) break;
        else FillCandidates();
        
    }
    return IsSolved();
}

bool Board::FindNakedSingles() {
    if (!BrFoRa) {
    
        bool Changed=false;
        for (int i=0;i<81;i++) {
            if (SolvedNumbers[i]==false) {
                if (Candidates[i][1]==0) {
                    Changed=true;
                    BoardNumbers[i]=Candidates[i][0];
                    SolvedNumbers[i]=true;
                    }
                }
            }
        return Changed;
        }
    bool Changed=false;
    for (int i=0;i<81;i++) {
        if (SolvedNumbers_B[i]==false) {
            if (Candidates_B[i][1]==0) {
                Changed=true;
                BoardNumbers_B[i]=Candidates_B[i][0];
                SolvedNumbers_B[i]=true;
                }
            }
        }
    return Changed;
    
    }
bool Board::InCandidates(int Cell,int num) {
    if (!BrFoRa) {
        for (int i=0;i<9;i++) {
            if (Candidates[Cell][i]==num) return true;
            if (Candidates[Cell][i]==0) return false;
            }
        return false;
        }
    for (int i=0;i<9;i++) {
        if (Candidates_B[Cell][i]==num) return true;
        if (Candidates_B[Cell][i]==0) return false;
        }
    return false;
    }
bool Board::FindPointingPairs() {
    bool Changed=false;
    int cells[3][2];
    int SkipThese[3];
    int SkipTheseCount=0;
    int cellcount=0;
    for (int x=0;x<3;x++) {
        for (int y=0;y<3;y++) {
            for(int num=1;num<10;num++) {
                cellcount=0;
                for(int i=0;i<3;i++) {
                    for (int j=0;j<3;j++) {
                        if (InCandidates((3*x+i)*9+(3*y+j),num)) {
                            if (cellcount<3) {
                                cells[cellcount][0]=3*x+i;
                                cells[cellcount][1]=3*y+j;
                                }
                            
                            cellcount++;
                            }
                        }
                    }
                if (cellcount==3 or cellcount==2) {
                    bool SameRow=true;
                    bool SameCollumn=true;
                    int row=cells[0][0];
                    int collumn=cells[0][1];
                    for (int i=1;i<cellcount;i++) {
                        if (cells[i][0]!=row) SameRow=false;
                        if (cells[i][1]!=collumn) SameCollumn=false;
                        }
                    if (SameRow) {
                        SkipTheseCount=0;
                        for (int i=0;i<cellcount;i++) {
                            SkipThese[SkipTheseCount]=cells[i][1];
                            SkipTheseCount++;
                            }
                        for(int thiscollumn=0;thiscollumn<9;thiscollumn++) {
                            if (!isInArray(SkipThese,SkipTheseCount,thiscollumn)){
                                RemoveCandidate(row*9+thiscollumn,num);
                                Changed=1;
                                }
                            }
                        }
                    else if (SameCollumn) {
                        SkipTheseCount=0;
                        for (int i=0;i<cellcount;i++) {
                            SkipThese[SkipTheseCount]=cells[i][0];
                            SkipTheseCount++;
                            }
                        for(int thisrow=0;thisrow<9;thisrow++) {
                            if (!isInArray(SkipThese,SkipTheseCount,thisrow)){
                                RemoveCandidate(thisrow*9+collumn,num);
                                Changed=1;
                                }
                            }
                        }
                    }
                }
            }
        }
        return Changed;
    }
                    
                        
                        
void Board::RemoveCandidate(int Cell,int num) {
    if(!BrFoRa) {
        for (int i=0;i<9;i++) {
            if (Candidates[Cell][i]==num) {
                Candidates[Cell][i]=0;
                std::sort(Candidates[Cell],Candidates[Cell]+9,std::greater<int>());
                break;
                }
             else if (Candidates[Cell][i]==0) break;
            }
        }
    else {
        for (int i=0;i<9;i++) {
            if (Candidates_B[Cell][i]==num) {
                Candidates_B[Cell][i]=0;
                std::sort(Candidates_B[Cell],Candidates_B[Cell]+9,std::greater<int>());
                break;
                }
             else if (Candidates_B[Cell][i]==0) break;
            }
        }
    }
bool Board::FindHiddenSingles() {
    //Check each row, collumn and block, and if a number only is candidate in one cell, it means that it must be that cell
    //Blocks: 
    bool Changed=false;
    int cell=-1;
    int cellcount=0;
    //Blocks:
    if (!BrFoRa) {
        for (int x=0;x<3;x++) {
            for (int y=0;y<3;y++) {
                for(int num=1;num<10;num++) {
                    cell=-1;
                    cellcount=0;
                    for(int i=0;i<3;i++) {
                        for (int j=0;j<3;j++) {
                            if (InCandidates((3*x+i)*9+(3*y+j),num)) {
                                cell=(3*x+i)*9+(3*y+j);
                                cellcount++;
                                }
                            }
                        }
                    if (cellcount==1 and BoardNumbers[cell]==0) {
                        BoardNumbers[cell]=num;
                        SolvedNumbers[cell]=true;
                        Candidates[cell][0]=num;
                        if (Candidates[cell][1]!=0) {
                            for (int j=1;j<9;j++) Candidates[cell][j]=0;
                            }
                        Changed=true;
                        }
                    }
                }
            }
        //Rows
        for (int x=0;x<9;x++) {
            for(int num=1;num<10;num++) {
                cell=-1;
                cellcount=0;
                for (int y=0;y<9;y++) {
                    if (InCandidates(x*9+y,num)) {
                        cell=x*9+y;
                        cellcount++;
                        }
                    }
                if (cellcount==1 and BoardNumbers[cell]==0) {
                    BoardNumbers[cell]=num;
                    SolvedNumbers[cell]=true;
                    Candidates[cell][0]=num;
                    if (Candidates[cell][1]!=0) {
                        for (int j=1;j<9;j++) Candidates[cell][j]=0;
                        }
                    Changed=true;
                    }
                }
            }
        //Collumns
        for (int y=0;y<9;y++) {
            for(int num=1;num<10;num++) {
                cell=-1;
                cellcount=0;
                for (int x=0;x<9;x++) {
                    if (InCandidates(x*9+y,num)) {
                        cell=x*9+y;
                        cellcount++;
                        }
                    }
                if (cellcount==1 and BoardNumbers[cell]==0) {
                    BoardNumbers[cell]=num;
                    SolvedNumbers[cell]=true;
                    Candidates[cell][0]=num;
                    if (Candidates[cell][1]!=0) {
                        for (int j=1;j<9;j++) Candidates[cell][j]=0;
                        }
                    Changed=true;
                    }
                }
            }
        return Changed;
        }
    //Blocks:
    for (int x=0;x<3;x++) {
        for (int y=0;y<3;y++) {
            for(int num=1;num<10;num++) {
                cell=-1;
                cellcount=0;
                for(int i=0;i<3;i++) {
                    for (int j=0;j<3;j++) {
                        if (InCandidates((3*x+i)*9+(3*y+j),num)) {
                            cell=(3*x+i)*9+(3*y+j);
                            cellcount++;
                            }
                        }
                    }
                if (cellcount==1 and BoardNumbers_B[cell]==0) {
                    BoardNumbers_B[cell]=num;
                    SolvedNumbers_B[cell]=true;
                    Candidates_B[cell][0]=num;
                    if (Candidates_B[cell][1]!=0) {
                        for (int j=1;j<9;j++) Candidates_B[cell][j]=0;
                        }
                    Changed=true;
                    }
                }
            }
        }
    //Rows
    for (int x=0;x<9;x++) {
        for(int num=1;num<10;num++) {
            cell=-1;
            cellcount=0;
            for (int y=0;y<9;y++) {
                if (InCandidates(x*9+y,num)) {
                    cell=x*9+y;
                    cellcount++;
                    }
                }
            if (cellcount==1 and BoardNumbers_B[cell]==0) {
                BoardNumbers_B[cell]=num;
                SolvedNumbers_B[cell]=true;
                Candidates_B[cell][0]=num;
                if (Candidates_B[cell][1]!=0) {
                    for (int j=1;j<9;j++) Candidates_B[cell][j]=0;
                    }
                Changed=true;
                }
            }
        }
    //Collumns
    for (int y=0;y<9;y++) {
        for(int num=1;num<10;num++) {
            cell=-1;
            cellcount=0;
            for (int x=0;x<9;x++) {
                if (InCandidates(x*9+y,num)) {
                    cell=x*9+y;
                    cellcount++;
                    }
                }
            if (cellcount==1 and BoardNumbers_B[cell]==0) {
                BoardNumbers_B[cell]=num;
                SolvedNumbers_B[cell]=true;
                Candidates_B[cell][0]=num;
                if (Candidates_B[cell][1]!=0) {
                    for (int j=1;j<9;j++) Candidates_B[cell][j]=0;
                    }
                Changed=true;
                }
            }
        }
    return Changed;
}
                        
           
                
void Board::CopyCandidates() {
    if (!BrFoRa) {
        for(int i=0;i<81;i++) {
            for(int j=0;j<9;j++) {
                OldCandidates[i][j]=Candidates[i][j];
                }
            }
        }
    else {
        for(int i=0;i<81;i++) {
            for(int j=0;j<9;j++) {
                OldCandidates_B[i][j]=Candidates_B[i][j];
                }
            }
        }
    }
void Board::CopyBoardNumbers() {
    if (!BrFoRa) {
        for (int i=0;i<81;i++) {
            OldBoardNumbers[i]=BoardNumbers[i];
            }
        }
    else {
        for (int i=0;i<81;i++) {
            OldBoardNumbers_B[i]=BoardNumbers_B[i];
            }
        }
    }
bool Board::isInArray(int* array,int arraylen,int num) {
    for (int i=0;i<arraylen;i++) {
        if (array[i]==num) return true;
        }
    return false;
    }
int Board::CandidateLen(int *Candidatelist) {
    for (int i=0;i<9;i++) {
        if (Candidatelist[i]==0) return i;
        }
    return 8;
    }
bool Board::BruteForceRandomParrent() {
    if (IsSolved()) return true;
    BrFoRa=true;
    int nextNumberOfTries=30;
    int tries=-nextNumberOfTries;
    while(true) {
        tries+=nextNumberOfTries;
        if(!(BruteForceRandom(nextNumberOfTries)<0)) break;
        nextNumberOfTries+=10;
        }
    cout << tries << endl;
    bool State= IsSolved() ;
    BrFoRa=false;
    if (State==true) {
        for (int i=0;i<81;i++) {
            BoardNumbers[i]=BoardNumbers_B[i];
            SolvedNumbers[i]=SolvedNumbers_B[i];
            for (int j=0;j<9;j++) Candidates[i][j]=Candidates_B[i][j];
            }
        }
    return State;
    }
int Board::BruteForceRandom(int tryborder) {
    //Find Random Cells
    int testing=0;
    int cells[]={-1,-1,-1,-1};
    for (int i=0;i<4;i++) {
        while(true) {
            int RandomCell=rand()%81;
            if (!(SolvedNumbers[RandomCell] or isInArray(cells,i,RandomCell))) {
                cells[i]=RandomCell;
                break;
                }
            }
        }
    int Candidates0Len=CandidateLen(Candidates[cells[0]]);
    int Candidates1Len=CandidateLen(Candidates[cells[1]]);
    int Candidates2Len=CandidateLen(Candidates[cells[2]]);
    int Candidates3Len=CandidateLen(Candidates[cells[3]]);
    for (int a=Candidates0Len;a>=0;a--) {
        BoardNumbers_B[cells[0]]=Candidates[cells[0]][a];
        if (a!=Candidates0Len) SolvedNumbers_B[cells[0]]=true;
        else SolvedNumbers_B[cells[0]]=false;
        for (int b=Candidates1Len;b>=0;b--) {
            BoardNumbers_B[cells[1]]=Candidates[cells[1]][b];
            if (b!=Candidates1Len) SolvedNumbers_B[cells[1]]=true;
            else SolvedNumbers_B[cells[1]]=false;
            for (int c=Candidates2Len;c>=0;c--) {
                BoardNumbers_B[cells[2]]=Candidates[cells[2]][c];
                if (c!=Candidates2Len) SolvedNumbers_B[cells[2]]=true;
                else SolvedNumbers_B[cells[2]]=false;
                for (int d=Candidates3Len;d>=0;d--) {
                    BoardNumbers_B[cells[3]]=Candidates[cells[3]][d];
                    if (d!=Candidates3Len) SolvedNumbers_B[cells[3]]=true;
                    else SolvedNumbers_B[cells[3]]=false;
                    for (int ii=0;ii<81;ii++) {
                        if (isInArray(cells,4,ii)) continue;
                        BoardNumbers_B[ii]=BoardNumbers[ii];
                        SolvedNumbers_B[ii]=SolvedNumbers[ii];
                        }
                    if (testing>tryborder) return -3;
                    if (CheckMissPlacements()) {
                        if (LogicSolveBoard() and CheckMissPlacements()){
                            SolvedNumbers_B[cells[3]]=false;
                            SolvedNumbers_B[cells[2]]=false;
                            SolvedNumbers_B[cells[1]]=false;
                            SolvedNumbers_B[cells[0]]=false;
                            LogicSolveBoard();
                            return 1;
                            }
                        }
                    }
                }
            }
        }
                    
    return -1;
    }
            
int Board::BruteForce() {
    int CurrentCell=-1;
    bool BackStepped=false;
    bool LastNotValid=false;
    int Jumps=0;
    int CurCandidate[81]={0};
    while(true) {
        Jumps++;
        //if (Jumps%20000==0) PrintBoard();
        while(true) {
            CurrentCell++;
            if (CurrentCell>80) return Jumps;
            if (SolvedNumbers[CurrentCell]==false) break;
        }
        CurCandidate[CurrentCell]=0;
        BoardNumbers[CurrentCell]=Candidates[CurrentCell][CurCandidate[CurrentCell]];
        while(true) {
            if(BackStepped) {
                BackStepped=false;
                if (CurCandidate[CurrentCell]!=8 && Candidates[CurrentCell][CurCandidate[CurrentCell]+1]!=0) {
                    CurCandidate[CurrentCell]++;
                    BoardNumbers[CurrentCell]=Candidates[CurrentCell][CurCandidate[CurrentCell]];
                }
                else LastNotValid=true;
            }
            if (LastNotValid or CheckMissPlacements(CurrentCell)==false) {
                LastNotValid=false;
                CurCandidate[CurrentCell]++;
                if (CurCandidate[CurrentCell]!=9 && Candidates[CurrentCell][CurCandidate[CurrentCell]]!=0) {
                    BoardNumbers[CurrentCell]=Candidates[CurrentCell][CurCandidate[CurrentCell]];
                }
                else {
                    BoardNumbers[CurrentCell]=0;
                    while(true) {
                        CurrentCell--;
                        BackStepped=1;
                        if (CurrentCell<0) return -1;
                        if (!SolvedNumbers[CurrentCell]) break;
                        
                    }
                }
            }
            else break;
        }
    }    
        
    
            
}

void Board::FillCandidates() {
    if (!BrFoRa) {
        for (int i=0;i<81;i++) {
            if (BoardNumbers[i]!=0){ //This can be optimized, just skip if cell is solved.
                Candidates[i][0]=BoardNumbers[i];
                if (Candidates[i][1]!=0) {
                    for (int j=1;j<9;j++) Candidates[i][j]=0;
                }
            }
            else {
                for (int j=0;j<9;j++) Candidates[i][j]=0;
                for (int j=1;j<10;j++) {
                    BoardNumbers[i]=j;
                    if(CheckMissPlacements(i)) Candidates[i][j-1]=j;
                    }
                std::sort(Candidates[i],Candidates[i]+9,std::greater<int>());
                if (Candidates[i][1]==0) {
                    BoardNumbers[i]=Candidates[i][0];
                    SolvedNumbers[i]=true;
                    }
                else BoardNumbers[i]=0;
                }
            }
        }
    else {
        for (int i=0;i<81;i++) {
            if (BoardNumbers_B[i]!=0){ //This can be optimized, just skip if cell is solved.
                Candidates_B[i][0]=BoardNumbers_B[i];
                if (Candidates_B[i][1]!=0) {
                    for (int j=1;j<9;j++) Candidates_B[i][j]=0;
                }
            }
            else {
                for (int j=0;j<9;j++) Candidates_B[i][j]=0;
                for (int j=1;j<10;j++) {
                    BoardNumbers_B[i]=j;
                    if(CheckMissPlacements(i)) Candidates_B[i][j-1]=j;
                    }
                std::sort(Candidates_B[i],Candidates_B[i]+9,std::greater<int>());
                if (Candidates_B[i][1]==0) {
                    BoardNumbers_B[i]=Candidates_B[i][0];
                    SolvedNumbers_B[i]=true;
                    }
                else BoardNumbers_B[i]=0;
                }
            }
        }
    }
    

bool Board::GroupIsGood(int* Group) {
    std::sort(Group,Group+9);
    for (int i=0;i<8;i++) {
        if (Group[i]==0) continue;
        if (Group[i]==Group[i+1]) return false;
        }
    return true;
}
            
bool Board::CheckMissPlacements() {
    //Blocks
    if(!BrFoRa) {
    
        for (int x=0;x<3;x++) {
            for (int y=0;y<3;y++) {
                int BlockNumbers[9]={0,0,0,0,0,0,0,0,0};
                for (int i=0;i<3;i++) {
                    for (int j=0;j<3;j++) BlockNumbers[j+3*i]=BoardNumbers[(3*x+i)*9+(3*y+j)];
                    }
                if(!GroupIsGood(BlockNumbers)) return false;
            }
        }
        //Rows
        for (int x=0;x<9;x++) {
            int RowNumbers[9]={0,0,0,0,0,0,0,0,0};
            for (int y=0;y<9;y++) RowNumbers[y]=BoardNumbers[x*9+y];
            if (!GroupIsGood(RowNumbers)) return false;
            }
        //Collumns
        for (int y=0;y<9;y++) {
            int CollumnNumbers[9]={0,0,0,0,0,0,0,0,0};
            for (int x=0;x<9;x++) CollumnNumbers[x]=BoardNumbers[x*9+y];
            if (!GroupIsGood(CollumnNumbers)) return false;
            }
        return true;
    }
    else {
        
        for (int x=0;x<3;x++) {
            for (int y=0;y<3;y++) {
                int BlockNumbers[9]={0,0,0,0,0,0,0,0,0};
                for (int i=0;i<3;i++) {
                    for (int j=0;j<3;j++) BlockNumbers[j+3*i]=BoardNumbers_B[(3*x+i)*9+(3*y+j)];
                    }
                if(!GroupIsGood(BlockNumbers)) return false;
            }
        }
        //Rows
        for (int x=0;x<9;x++) {
            int RowNumbers[9]={0,0,0,0,0,0,0,0,0};
            for (int y=0;y<9;y++) RowNumbers[y]=BoardNumbers_B[x*9+y];
            if (!GroupIsGood(RowNumbers)) return false;
            }
        //Collumns
        for (int y=0;y<9;y++) {
            int CollumnNumbers[9]={0,0,0,0,0,0,0,0,0};
            for (int x=0;x<9;x++) CollumnNumbers[x]=BoardNumbers_B[x*9+y];
            if (!GroupIsGood(CollumnNumbers)) return false;
            }
        return true;
    }
                
}
bool Board::CheckMissPlacements(int CellNum) {
    if(!BrFoRa) {
        //Blocks
        int x=(CellNum%9)/3;
        int y=CellNum/27;
        int BlockNumbers[9]={0,0,0,0,0,0,0,0,0};
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                BlockNumbers[j+3*i]=BoardNumbers[(3*x+i)*9+(3*y+j)];
                }
            }
        if(!GroupIsGood(BlockNumbers)) return false;
        //Rows
        x=CellNum/9;
        int RowNumbers[9]={0,0,0,0,0,0,0,0,0};
        for (int y=0;y<9;y++) RowNumbers[y]=BoardNumbers[x*9+y];
        if (!GroupIsGood(RowNumbers)) return false;
        
        //Collumns
        y=CellNum%9;
        int CollumnNumbers[9]={0,0,0,0,0,0,0,0,0};
        for (int x=0;x<9;x++) CollumnNumbers[x]=BoardNumbers[x*9+y];
        if (!GroupIsGood(CollumnNumbers)) return false;
        return true;
    }
    else {
        //Blocks
        int x=(CellNum%9)/3;
        int y=CellNum/27;
        int BlockNumbers[9]={0,0,0,0,0,0,0,0,0};
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                BlockNumbers[j+3*i]=BoardNumbers_B[(3*x+i)*9+(3*y+j)];
                }
            }
        if(!GroupIsGood(BlockNumbers)) return false;
        //Rows
        x=CellNum/9;
        int RowNumbers[9]={0,0,0,0,0,0,0,0,0};
        for (int y=0;y<9;y++) RowNumbers[y]=BoardNumbers_B[x*9+y];
        if (!GroupIsGood(RowNumbers)) return false;
        
        //Collumns
        y=CellNum%9;
        int CollumnNumbers[9]={0,0,0,0,0,0,0,0,0};
        for (int x=0;x<9;x++) CollumnNumbers[x]=BoardNumbers_B[x*9+y];
        if (!GroupIsGood(CollumnNumbers)) return false;
        return true;
    }
}

void Board::PrintBoard() {
    int counter=0;
    for(int i=0;i<9;i++) {
        if (i%3==0 && i!=0) cout << "---------------------" << endl;
        counter=0;
        for(int j=i*9;j<(i+1)*9;j++) 
        {
            if (counter%3==0 && counter!=0) cout << "| ";
            if (BoardNumbers[j]!=0) 
            {
                if (counter%3==2) cout << BoardNumbers[j] << " ";
                else cout << BoardNumbers[j] << " ";
            }
            else cout << ". ";
            counter++;
        }
        cout << endl;
    }
    cout << "\n\n";
}
void Board::PrintBoardBrute() {
    int counter=0;
    for(int i=0;i<9;i++) {
        if (i%3==0 && i!=0) cout << "---------------------" << endl;
        counter=0;
        for(int j=i*9;j<(i+1)*9;j++) 
        {
            if (counter%3==0 && counter!=0) cout << "| ";
            if (BoardNumbers_B[j]!=0) 
            {
                if (counter%3==2) cout << BoardNumbers_B[j] << " ";
                else cout << BoardNumbers_B[j] << " ";
            }
            else cout << ". ";
            counter++;
        }
        cout << endl;
    }
    cout << "\n\n";
}
