//like C++ Pseudocode

struct RegInfo {
  string reg; // this has eax ebx and so no
  int val;    // this has just value
};

vector<RegInfo> returnAllRegInfoThatHasSameValueWithOriginalProtected(RegInfo originalProtectedReg, gadget checkGadget){
  vector<RegInfo> watchRegs;
  watchRegs.push_back(RegInfo(originalProtectedReg));
  
  for(auto&op : checkGadget.operatoin) {
    
    //For now only mov. This add other watchReg to watchRegs. 
    //If I can know all situation to add watchReg, I can add them.
    
    vector<RegInfo> tmp;
    for(int i=0;i<watchRegs.size();++i){
      if(op._opeartion == "mov" && op._reg2 == watchRegs[i].reg) 
        tmp.push_back(RegInfo(op._reg1, watchRegs[i].val));
    }
    watchRegs.insert(watchRegs.end(), tmp.begin(), tmp.end());
    
    
    //For now only mov. This delete some watchReg if they are destroyed.
    //If I can know all situation to destroy watchReg, I can destroy them.
    
    for(int i=0;i<watchRegs.size();++i){
      //Another value(might be but might not) are stored to watchedReg so destroy.
      if(op._opeartion == "mov" && op._reg1 == watchRegs[i].reg) 
        watchRegs[i].reg = "!"; // mark ! and delete it later.
    }
    //delete watchReg that has ! isDestroyReg is function that check if it has ! or not and return bool
    watchRegs.erase(remove_if(watchRegs.begin(), watchRegs.end(), isDestroyReg ), watchRegs.end());
     
    
  }
  
  //here, watchRegs should have all RegInfo that has same value that the original protected Register had.
}



  
  
