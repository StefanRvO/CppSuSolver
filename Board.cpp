#include<algorithm>
#include<iostream>
using namespace std;
class Board { //Class to hold the board currently being solved
    private:
    int Candidates[81][9];
    int OldCandidates[81][9];
    bool SolvedNumbers[81];
    bool GroupIsGood(int*);
    int OldBoardNumbers[81];
    void CopyCandidates();    
    void FillCandidates();
    void CopyBoardNumbers();
    bool IsSameBoard(int*, int*);
    bool IsSameCandidates(int (*) [9],int (*) [9]);
    bool FindNakedSingles();
    bool IsSameCandidates();
    bool IsSolved();
    bool FindHiddenSingles();
    bool InCandidates(int, int);
    
    public:
    Board(char*);
    bool solved=false;
    int BoardNumbers[81];
    int BruteForce();
    void PrintBoard();
    bool CheckMissPlacements();
    bool CheckMissPlacements(int);
    bool LogicSolveBoard();
    
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
    for (int i=0;i<81;i++) {
        if (SolvedNumbers[i]) continue;
            return false;
        }
    return true;
    }
bool Board::LogicSolveBoard() {
    int naked=0;
    int hidden=0;
    FillCandidates();
    while(true) {
        CopyBoardNumbers();
        while(true) {
            //FindPointingPairs();
            naked=FindNakedSingles();
            hidden=FindHiddenSingles();
            cout << naked << hidden <<  endl;
            if (!(hidden or naked)) break;
            else {
                if (!IsSameBoard(BoardNumbers,OldBoardNumbers)) FillCandidates();
                //FindNakedPairsTripplesQuads();
                //FindHiddenPairsTripplesQuads();
                }
           }
        while(true) {
            CopyCandidates();
            //NakedGroups=NakedGroups=FindNakedPairsTripplesQuads();
            //HiddenGroups=FindHiddenPairsTripplesQuads();
            //PointingPairs=FindPointingPairs();
            if (IsSameCandidates(Candidates,OldCandidates)) break;
            }
        naked=FindNakedSingles();
        hidden=FindHiddenSingles();
        cout << naked << hidden << endl;
        if (!(hidden or naked)) break;
        else FillCandidates();
        
    }
    return IsSolved();
}

bool Board::FindNakedSingles() {
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
bool Board::InCandidates(int Cell,int num) {
    for (int i=0;i<9;i++) {
        if (Candidates[Cell][i]==num) return true;
        if (Candidates[Cell][i]==0) return false;
        }
    return false;
    }
bool Board::FindHiddenSingles() {
    //Check each row, collumn and block, and if a number only is candidate in one cell, it means that it must be that cell
    //Blocks: 
    bool Changed=false;
    int cell=-1;
    int cellcount=0;
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
                        
           
                
void Board::CopyCandidates() {
    for(int i=0;i<81;i++) {
        for(int j=0;j<9;j++) {
            OldCandidates[i][j]=Candidates[i][j];
            }
        }
    }
    
void Board::CopyBoardNumbers() {
    for (int i=0;i<81;i++) {
        OldBoardNumbers[i]=BoardNumbers[i];
        }
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
    for (int i=0;i<81;i++) {
        if (BoardNumbers[i]!=0){ //This can be optimized, just skip if cell is solved.
            Candidates[i][0]=BoardNumbers[i];
            if (Candidates[i][1]!=0) {
                for (int j=1;j<9;j++) Candidates[i][j]=0;
            }
        }
        else {
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
bool Board::CheckMissPlacements(int CellNum) {
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
