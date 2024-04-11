#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std::chrono;

//the given grid and the hook in the end
std::vector<std::vector<int>> grid;
std::vector<std::vector<int>> hook;

//vecrow and veccolumn the position of x and y
std::vector<int> vecrow = {0, 0, 0, 0, 0, 0, 0, 0, 0};
std::vector<int> veccolumn = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//possible values if the hook value is still available
std::vector<bool> possiblevalues = {1, 1, 1, 1, 1, 1, 1, 1, 1};
//defines the positioning of the hook from 0-4
std::vector<int> positions = {0, 0, 0, 0, 0, 0, 0, 0, 0};


//check summation of the numbers around the numbers in the grid
bool checksum(int xvalue, int yvalue, int number){
  if(grid[xvalue][yvalue] != -1){
    int sum = 0;
    int empty = 3;
    int nr = 0;
    if(xvalue>0){
      nr++;
      sum += hook[xvalue-1][yvalue];
      if(hook[xvalue-1][yvalue]) empty--;
    }
    if(xvalue<grid[0].size()-1 ){
      nr++;
      sum += hook[xvalue+1][yvalue];
      if(hook[xvalue+1][yvalue]) empty--;
    }
    if(yvalue <grid[0].size()-1){
      nr++;
      sum+= hook[xvalue][yvalue+1];
      if(hook[xvalue][yvalue+1]) empty--;
    }
    if(yvalue >0){
      nr++;
      sum += hook[xvalue][yvalue-1];
      if(hook[xvalue][yvalue-1]) empty--;
    }
  
    if(nr == 4){
        if((sum+number)+(empty*9)<grid[xvalue][yvalue])return false;
      }
      if(nr == 3){
        if((sum+number)+((empty-1)*9)<grid[xvalue][yvalue])return false;
      }
      if(nr == 2){
        if((sum+number)+((empty-2)*9)<grid[xvalue][yvalue])return false;
      }
    if(sum + number > grid[xvalue][yvalue]) return false;
    
  }
  return true;
}

bool finalcheck(){
  for(int i = 0; i < grid[0].size(); ++i){
    for(int j = 0; j < grid[0].size(); ++j){
      if(hook[i][j]){
        bool marker = false;
        if(i>0 ){
          if(hook[i-1][j]) marker = true;     
        }
        if( j >0){
          if(hook[i][j-1]) marker = true;     
        }
        if(i<grid[0].size()-1){
          if(hook[i+1][j]) marker = true;     
        }
        if(j<grid[0].size()-1){
          if(hook[i][j+1]) marker = true;     
        }
        if(marker == false){
          return false;
        }
      }
      if(grid[i][j]!=-1){
        int sum = 0;
        if(i>0){
          sum += hook[i-1][j];
        }
        if(i<grid[0].size()-1 ){
          sum += hook[i+1][j];
        }
        if(j <grid[0].size()-1){
          sum+= hook[i][j+1];
        }
        if(j >0){
          sum += hook[i][j-1];
        }
         if(sum != grid[i][j]) return false;
      }
    }
  }
  return true;
}


bool checkfunction(int xvalue, int yvalue, int number){

  //return true;
  //std::cout << xvalue << " ";
  //std::cout << yvalue << " \n";
  //return true;
  //check that grid position is empty or the number is zero
    if(grid[xvalue][yvalue] != -1 && number != 0){
      return false;
    }else if(grid[xvalue][yvalue]!=-1 && number == 0){
      return true;
    }

    //check for surrounding squares if they are not all filled
    if(xvalue>0 && yvalue >0){
      if(hook[xvalue-1][yvalue-1]&&hook[xvalue-1][yvalue]&&hook[xvalue][yvalue-1]&&number) return false;
    }

    if(xvalue<grid[0].size()-1 && yvalue <grid[0].size()-1){
      if(hook[xvalue+1][yvalue+1]&&hook[xvalue+1][yvalue]&&hook[xvalue][yvalue+1]&&number) return false;
    }
    
    if(xvalue>0 && yvalue <grid[0].size()-1){
      if(hook[xvalue-1][yvalue+1]&&hook[xvalue-1][yvalue]&&hook[xvalue][yvalue+1]&&number) return false;
    }
    
    if(xvalue<grid[0].size()-1 && yvalue >0){
      if(hook[xvalue+1][yvalue-1]&&hook[xvalue+1][yvalue]&&hook[xvalue][yvalue-1]&&number) return false;
    }

  //check surrounding sums
    if(xvalue>0 ){
          if(checksum(xvalue-1, yvalue, number) == false)return false;     
    }
    if( yvalue >0){
      if(checksum(xvalue, yvalue-1, number) == false)return false;     
    }
    if(xvalue<grid[0].size()-1){
          if(checksum(xvalue+1, yvalue, number) == false)return false;      
        }
    if(yvalue<grid[0].size()-1){
          if(checksum(xvalue, yvalue+1, number) == false)return false;    
    }
   return true; 
}

//fills each level hook of the grid --> works fine
bool fillhook(int level){

  // goes through all possible hook values
  for(int i = 1; i <= possiblevalues.size(); ++i){
      if(i <= 2*level-1 && possiblevalues[i-1]==1){
        
      std::vector<int> numbervector(i, i);
      std::vector<int> zerovector(2*level-1-i, 0);
      numbervector.insert(numbervector.end(), zerovector.begin(), zerovector.end());
      sort(numbervector.begin(), numbervector.end());
      /*if(i==5){
        for (std::size_t j = 0; j < numbervector.size(); ++j) {
                    std::cout << numbervector[j] << " ";
                      }
                    std::cout << std::endl;
      }*/

      //permutes all options and goes one hook level higher
      do{
        bool dec = true;
        if(positions[level-1] == 0){
          //checks of hookposition is doable and if yess fills hook ---> mistake
          for(int l = 0; level-1 >= l ; ++l){
            if(dec && checkfunction(vecrow[level-1]+l, veccolumn[level-1], numbervector[l])){
              hook[vecrow[level-1]+l][veccolumn[level-1]]=numbervector[l];
            }else{ dec = false; hook[vecrow[level-1]+l][veccolumn[level-1]]=0;};
          }
          for(int l = 1; level-1 >= l ; ++l){
            if(dec && checkfunction(vecrow[level-1], veccolumn[level-1]+l, numbervector[l+level-1])){
              hook[vecrow[level-1]][veccolumn[level-1]+l]=numbervector[l+level-1];
            }else {dec = false; hook[vecrow[level-1]][veccolumn[level-1]+l]=0;};

        }
        }
        if(positions[level-1] == 1&& dec){
          for(int l = 0; level-1 >= l ; ++l){
            if(dec && checkfunction(vecrow[level-1]-l, veccolumn[level-1], numbervector[l])){
              hook[vecrow[level-1]-l][veccolumn[level-1]]=numbervector[l];
            }else{ dec = false; hook[vecrow[level-1]-l][veccolumn[level-1]]=0;};
          }
          for(int l = 1; level-1 >= l ; ++l){
            if(dec && checkfunction(vecrow[level-1], veccolumn[level-1]+l, numbervector[l+level-1])){
              hook[vecrow[level-1]][veccolumn[level-1]+l]=numbervector[l+level-1];
            }else {dec = false;hook[vecrow[level-1]][veccolumn[level-1]+l]=0;};

        }
        }
        if(positions[level-1] == 2&& dec){
          for(int l = 0; level-1 >= l ; ++l){
            if(dec && checkfunction(vecrow[level-1]+l, veccolumn[level-1], numbervector[l])){
              hook[vecrow[level-1]+l][veccolumn[level-1]]=numbervector[l];
            }else{ dec = false; hook[vecrow[level-1]+l][veccolumn[level-1]]=0;};
          }
          for(int l = 1; level-1 >= l ; ++l){
            if(dec && checkfunction(vecrow[level-1], veccolumn[level-1]-l, numbervector[l+level-1])){
              hook[vecrow[level-1]][veccolumn[level-1]-l]=numbervector[l+level-1];
            }else {dec = false;hook[vecrow[level-1]][veccolumn[level-1]-l]=0;};

        }
        }
        if(positions[level-1] == 3){
          for(int l = 0; level-1 >= l ; ++l){
            if(dec && checkfunction(vecrow[level-1]-l, veccolumn[level-1], numbervector[l])){
              hook[vecrow[level-1]-l][veccolumn[level-1]]=numbervector[l];
            }else{ dec = false; hook[vecrow[level-1]-l][veccolumn[level-1]]=0;};
          }
          for(int l = 1; level-1 >= l ; ++l){
            if(dec && checkfunction(vecrow[level-1], veccolumn[level-1]-l, numbervector[l+level-1])){
              hook[vecrow[level-1]][veccolumn[level-1]-l]=numbervector[l+level-1];
            }else {dec = false;hook[vecrow[level-1]][veccolumn[level-1]-l]=0;};

        }
        }
            //std::cout << level << " \n";
            //if we manage to fill level 5 we reached our goal
            if(level == 9 && dec == true){
              if(finalcheck()){
                std::cout << "SUCCESS" << " \n";
              
               std::cout << "\nPrinting Matrix:\n";
               for (std::size_t i = 0; i < grid[0].size(); ++i) {
                  for (std::size_t j = 0; j < grid[0].size(); ++j) {
                    std::cout << hook[i][j] << " ";
                      }
                    std::cout << std::endl;
                }
                  std::cout << std::endl;
                  for (int i = 0; i < vecrow.size(); ++i) {
                      std::cout << vecrow[i] << " ";
                  }
                  std::cout << std::endl;
                  for (int i = 0; i < veccolumn.size(); ++i) {
                      std::cout << veccolumn[i] << " ";
                  }
                  std::cout << std::endl;
                  std::cout << std::endl;
              }
                            
            }
            
            possiblevalues[i-1]= 0;
            if(dec && level < 9) fillhook(level+1);
            possiblevalues[i-1]=1;

          if(positions[level-1] == 0){
            //zero the hooks out after failure
            for(int l = 0; level-1 >= l ; ++l){
              hook[vecrow[level-1]+l][veccolumn[level-1]]=0;}
            for(int l = 1; level-1 >= l ; ++l){
              hook[vecrow[level-1]][veccolumn[level-1]+l]=0;}
          }
        if(positions[level-1] == 1){
          for(int l = 0; level-1 >= l ; ++l){
            hook[vecrow[level-1]-l][veccolumn[level-1]]=0;}
          for(int l = 1; level-1 >= l ; ++l){
            hook[vecrow[level-1]][veccolumn[level-1]+l]=0;}
        }
        if(positions[level-1] == 2){
          for(int l = 0; level-1 >= l ; ++l){
            hook[vecrow[level-1]+l][veccolumn[level-1]]=0;}
          for(int l = 1; level-1 >= l ; ++l){
            hook[vecrow[level-1]][veccolumn[level-1]-l]=0;}
        }
        if(positions[level-1] == 3){
          for(int l = 0; level-1 >= l ; ++l){
           hook[vecrow[level-1]-l][veccolumn[level-1]]=0;}
          for(int l = 1; level-1 >= l ; ++l){
            hook[vecrow[level-1]][veccolumn[level-1]-l]=0;}
        }
            
       
        
      }while (std::next_permutation(numbervector.begin(), numbervector.end()));
      }
  
  }
  return false;
}


int count = 0;

//defines the next hook to be tested->works fine
void nextstephook(int relativeposition, int absx, int absy, int step){
  if(step < 9){
    positions[step] = relativeposition;
  }

  if(step == 0){
      count += 1;
    fillhook(1);
    /*for (int i = 0; i < vecrow.size(); ++i) {
        std::cout << vecrow[i] << " ";
    }
    std::cout << std::endl;
     for (int i = 0; i < veccolumn.size(); ++i) {
        std::cout << veccolumn[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;*/
    return;
    
  }

  for(int j = 0; j<4; j++){
    if(relativeposition == 0){
      if(j==0){
        vecrow[step-1] = 1+absx;
        veccolumn[step-1] = 1+absy;
        if(step!=0) nextstephook(0, 1+absx,1+absy,  step-1);
        
      }
      if(j==1){
        vecrow[step-1] = absx+step;
        veccolumn[step-1] = absy+1;
        if(step!=0 && step!=1) nextstephook(1, absx+step,absy+1, step-1);
        
      }
      if(j==2){
        vecrow[step-1] = absx+1;
        veccolumn[step-1] = absy + step;
        if(step!=0&& step!=1) nextstephook(2, absx+1,absy + step, step-1);
        
      }
      if(j==3){
        vecrow[step-1] = absx+step;
        veccolumn[step-1] = absy+ step;
        if(step!=0&& step!=1) nextstephook(3,absx+step,absy+ step, step-1);
        
      }
    }
    if(relativeposition == 1){
      if(j==0){
        vecrow[step-1] = absx-step;
        veccolumn[step-1] = 1 + absy;
        if(step!=0) nextstephook(0, absx-step,1+absy,  step-1);
        
      }
      if(j==1){
        vecrow[step-1] = absx-1;
        veccolumn[step-1] = 1 + absy;
        if(step!=0&& step!=1) nextstephook(1, absx-1,absy+1, step-1);
        
      }
      if(j==2){
        vecrow[step-1] = absx-step;
        veccolumn[step-1] = absy+step;
        if(step!=0&& step!=1) nextstephook(2, absx-step,absy+step, step-1);
        
      }
      if(j==3){
        vecrow[step-1] = absx-1;
        veccolumn[step-1] = absy+ step;
        if(step!=0&& step!=1) nextstephook(3,absx-1,absy+ step, step-1);
        
      }
    }
    if(relativeposition == 2){
      if(j== 0){
        vecrow[step-1] = 1 + absx;
        veccolumn[step-1] = absy-step;
        if(step!=0) nextstephook(0, 1+absx,absy-step,  step-1);
        
      }
      if(j==1){
        vecrow[step-1] = absx+step;
        veccolumn[step-1] = absy-step;
        if(step!=0&& step!=1) nextstephook(1, absx+step,absy-step, step-1);
        
      }
      if(j==2){
        vecrow[step-1] = absx+1;
        veccolumn[step-1] = absy-1;
        if(step!=0&& step!=1) nextstephook(2, absx+1,absy-1, step-1);
        
      }
      if(j==3){
        vecrow[step-1] = step + absx;
        veccolumn[step-1] = absy-1;
        if(step!=0&& step!=1) nextstephook(3,absx+step,absy-1, step-1);
        
      }
    }
    if(relativeposition == 3){
      if(j== 0){
        vecrow[step-1] = absx-step;
        veccolumn[step-1] = absy-step;
        if(step!=0) nextstephook(0, absx-step,absy-step,  step-1);
        
      }
      if(j==1){
        vecrow[step-1] = absx-1;
        veccolumn[step-1] = absy-step;
        if(step!=0&& step!=1) nextstephook(1, absx-1,absy-step, step-1);
        
      }
      if(j==2){
        vecrow[step-1] = absx-step;
        veccolumn[step-1] = absy-1;
        if(step!=0&& step!=1) nextstephook(2, absx-step,absy-1, step-1);
        
      }
      if(j==3){
        vecrow[step-1] = absx-1;
        veccolumn[step-1] = absy-1;
        if(step!=0&& step!=1) nextstephook(3,absx-1,absy-1, step-1);
        
      }
    }
  } 
}


void solveproblem(std::vector<std::vector<int>> grid){
  
  nextstephook(0, -1,-1, 9);
  std::cout << count << " ";
  
}

int main() {

  
  int row = 9;
  int column = 9;
  grid.resize(row, std::vector<int>(column, -1));
  hook.resize(row, std::vector<int>(column, 0));

  grid[0][1] = 18;
  grid[2][2] = 9;
  grid[4][1] = 5;
  grid[6][1] = 9;
  grid[8][2] = 22;
  grid[4][3] = 11;
  grid[1][4] = 12;
  grid[7][4] = 14;
  grid[4][5] = 22;
  grid[0][6] = 7;
  grid[6][6] = 19;
  grid[2][7] = 31;
  grid[4][7] = 22;
  grid[8][7] = 15;


 auto start = high_resolution_clock::now();
  solveproblem(grid);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  return 0;
}