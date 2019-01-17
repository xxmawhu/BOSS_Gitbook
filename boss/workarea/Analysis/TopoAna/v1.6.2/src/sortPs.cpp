#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::sortPs(vector<int> & vPid,vector<int> & vMidx)
{
  if(vPid.size()!=vMidx.size())
    {
      cerr<<"Error: The two vectors vPid and vMidx have different sizes!"<<endl;
      cerr<<"Infor: The size of the vector vPid is "<<vPid.size()<<"."<<endl;
      cerr<<"Infor: The size of the vector vMidx is "<<vMidx.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  /*cout<<"Before sort:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl;
    }*/

  vector<int> vPidFnl,vMidxFnl,vIdxFnl;
  vector<int> vPidOld,vMidxOld,vIdxOld,vNSmPidsOld;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      //if(((unsigned int) vMidx[i])==i) Sometimes, users may set Midx[i] at -1 rather than i when the pid of the mother of the partilce i does not appear in the array Pid. Note that the arrays Pid and Midx are the branches stored in the tree of the input root files. In order to make the program can handle such cases as well, this statement is revised to be the following one.
      if((((unsigned int) vMidx[i])==i)||(vMidx[i]==-1))
	{
          if(vPid[i]!=22) vPidOld.push_back(vPid[i]);
          else if(m_ignoreISR==false) vPidOld.push_back(m_pidOfISRGam);
          else continue;
          //vMidxOld.push_back(vMidx[i]); Sometimes, users may set Midx[i] at -1 rather than i when the pid of the mother of the partilce i does not appear in the array Pid. Note that the arrays Pid and Midx are the branches stored in the tree of the input root files. In order to make the program can handle such cases as well, this statement is revised to be the following one. Then, the following parts of the program do not have to change any more.
          vMidxOld.push_back(i);
          vIdxOld.push_back(i);
	}
    }
  sortByPidAndPchrg(vPidOld,vMidxOld,vIdxOld,vNSmPidsOld);
  for(unsigned int i=0;i<vPidOld.size();i++)
    {
      vPidFnl.push_back(vPidOld[i]);
      vMidxFnl.push_back(vMidxOld[i]);
      vIdxFnl.push_back(vIdxOld[i]);
    }

  unsigned int hHdEvtBrs=1;
  
  unsigned int nCmltSmPids;
  vector<int> vIdxYng, vNSmPidsYng;
  bool isIdPid; // Codes related to the variable is used to ignore the decay of the particles specified in the input card and stored in the vector m_vIddPid.
  bool isIddPid; // Codes related to the variable is used to ignore the decay of the daughters of the particles specified in the input card and stored in the vector m_vIddPid.
  vector< vector<int> > vVPidYngSbst,vVMidxYngSbst,vVIdxYngSbst,vVNSmPidsYngSbst;
  vector<int> vPidYngSbst,vMidxYngSbst,vIdxYngSbst,vNSmPidsYngSbst;
  while(hHdEvtBrs<m_hHdEvtBrsMax&&vIdxOld.size()!=0)
    {
      nCmltSmPids=0;
      vIdxYng.clear();
      vNSmPidsYng.clear();
      for(unsigned int i=0;i<vNSmPidsOld.size();i++)
        {
          isIdPid=false;
          for(unsigned int j=0;j<m_vIdPid.size();j++)
            {
              if(vPid[vIdxOld[nCmltSmPids]]==m_vIdPid[j])
                {
                  isIdPid=true;
                  break;
                }
            }
          if(isIdPid==true)
            {
              nCmltSmPids=nCmltSmPids+vNSmPidsOld[i]; // Don't miss out the statement. Otherwise, the program will go wrong where the variable nCmltSmPids is used. 
              continue;
            }

          isIddPid=false;
          for(unsigned int j=0;j<m_vIddPid.size();j++)
            {
              if(vPid[vIdxOld[nCmltSmPids]]==m_vIddPid[j])
                {
                  isIddPid=true;
                  break;
                }
            }

          vVPidYngSbst.clear();
          vVMidxYngSbst.clear();
          vVIdxYngSbst.clear();
          vVNSmPidsYngSbst.clear();
          for(unsigned int j=0;j<((unsigned int) vNSmPidsOld[i]);j++)
            {
              vPidYngSbst.clear();
              vMidxYngSbst.clear();
              vIdxYngSbst.clear();
              vNSmPidsYngSbst.clear();
              for(unsigned int k=0;k<vPid.size();k++)
	            {
                  //if((((unsigned int) vMidx[k])!=k)&&vMidx[k]==vIdxOld[nCmltSmPids+j]) Sometimes, users may set Midx[i] at -1 rather than i when the pid of the mother of the partilce i does not appear in the array Pid. Note that the arrays Pid and Midx are the branches stored in the tree of the input root files. In order to make the program can handle such cases as well, this statement is revised to be the following one.
                  if(((((unsigned int) vMidx[k])!=k)&&(vMidx[k]!=-1))&&vMidx[k]==vIdxOld[nCmltSmPids+j])
	                {
                      if(abs(vPid[k])!=22)
                        {
                          vPidYngSbst.push_back(vPid[k]);
                        }
                      else if(vPid[k]==-22)
                        {
                          if(m_ignoreGFSR==false) vPidYngSbst.push_back(vPid[k]);
                          else continue;
                        }
                      else
                        { 
                          bool isgFSR=false;
                          // In the following conditions, (k-l) is necessary to be converted from (unsigned int) type to (int) type. Or, the condition will lose its effectiveness when k<l.
                          for(unsigned int l=1;((k+l)<vPid.size()||((int)(k-l))>=0);l++)
                            {
                              if((k+l)<vPid.size())
                                {
                                  if(vMidx[k+l]==vMidx[k])
                                    {
                                      if(abs(vPid[k+l])==11||abs(vPid[k+l])==13||abs(vPid[k+l])==211||abs(vPid[k+l])==321||abs(vPid[k+l])==2212)
                                        {
                                           isgFSR=true;
                                           break;
                                        }
                                    }
                                }
                              if(((int)(k-l))>=0)
                                {
                                  if(vMidx[k-l]==vMidx[k])
                                    {
                                      if(abs(vPid[k-l])==11||abs(vPid[k-l])==13||abs(vPid[k-l])==211||abs(vPid[k-l])==321||abs(vPid[k-l])==2212)
                                        {
                                           isgFSR=true;
                                           break;
                                        }
                                    }
                                }                                      
                            }
                          if(isgFSR==true)
                            {
                              if(m_ignoreGFSR==false) vPidYngSbst.push_back(m_pidOfgFSRGam);
                              else continue;
                            }
                          else
                            {
                              vPidYngSbst.push_back(vPid[k]);
                            }
                        }
	                  vMidxYngSbst.push_back(vMidx[k]);
	                  vIdxYngSbst.push_back(k);
	                }
	            }
              if(vPidYngSbst.size()>0)
                {
                  sortByPidAndPchrg(vPidYngSbst,vMidxYngSbst,vIdxYngSbst,vNSmPidsYngSbst);
                  // The following four statements should be put in the scope of the if statement, or empty vectors might be pushed back to these vectors of vector. 
                  vVPidYngSbst.push_back(vPidYngSbst);
                  vVMidxYngSbst.push_back(vMidxYngSbst);
                  vVIdxYngSbst.push_back(vIdxYngSbst);
                  vVNSmPidsYngSbst.push_back(vNSmPidsYngSbst);
                }
            }
        if(vVPidYngSbst.size()>1) sortBySzPidAndPchrg(vVPidYngSbst,vVMidxYngSbst,vVIdxYngSbst,vVNSmPidsYngSbst);
        for(unsigned int j=0;j<vVPidYngSbst.size();j++)
          {
            for(unsigned int k=0;k<vVPidYngSbst[j].size();k++)
	      {
	        vPidFnl.push_back(vVPidYngSbst[j][k]);
	        vMidxFnl.push_back(vVMidxYngSbst[j][k]);
                vIdxFnl.push_back(vVIdxYngSbst[j][k]);
              }
            if(isIddPid==false)
              {
                for(unsigned int k=0;k<vVPidYngSbst[j].size();k++)
                  {
	            vIdxYng.push_back(vVIdxYngSbst[j][k]);
	          }
                for(unsigned int k=0;k<vVNSmPidsYngSbst[j].size();k++)
                  {
                    vNSmPidsYng.push_back(vVNSmPidsYngSbst[j][k]);
                  }
              }            
          }
        nCmltSmPids=nCmltSmPids+vNSmPidsOld[i];
      }
      vIdxOld.clear();
      vIdxOld=vIdxYng;
      vNSmPidsOld.clear();
      vNSmPidsOld=vNSmPidsYng;
      hHdEvtBrs++;
    }

  for(unsigned int i=0;i<vMidxFnl.size();i++)
    {
      for(unsigned int j=0;j<vMidxFnl.size();j++)
        {
          if(vIdxFnl[j]==vMidxFnl[i])
            {
              vMidxFnl[i]=j;
              break;
            }
        }
    }
  vPid.clear();
  vMidx.clear();
  vPid=vPidFnl;
  vMidx=vMidxFnl;

  /*cout<<"After sort:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl; 
    }*/
}