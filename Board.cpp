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
    
    public:
    Board(char*);
    bool solved=false;
    int BoardNumbers[81];
    int BruteForce();
    void PrintBoard();
    bool CheckMissPlacements();
    bool CheckMissPlacements(int);
    
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
        if (Jumps%20000==0) PrintBoard();
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
