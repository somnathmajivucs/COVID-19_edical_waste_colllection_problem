/* Truth Is Beauty*/
/*multi path routing problem with risk ....OBL based initialization/..RW/probabilistic selection/....cyclic/comparison cross/...OBL based mutation....Solve by OB_GA....*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#define node 10
#define noc 10 //100
#define ps 0.75
#define maxgen 1000//1000
#define maxseed 10
#define pc 0.49
#define pm 0.31
#define nov 1 // 1 //multi-path
#define Max_risk 1000000 // 3.20 //2000

#define per_unit_occupational_risk 0.000001         //10^(-6)
#define w1 1. //tr
#define w2 .0   //or
#define w3 .5   //system cost
#define w4 1

//#define Max_weightage_risk 100
//#define Max_Total_cost 10000

//#define SPECIMENS_LOADING_COST_PERUNIT 50


 int k,j;
 int g;
 
 float	 seedbest_best_final_distance,seedbest_best_traveling_cost,best_Total_Risk,seedbest_best_Total_FIXCHARGE,best_Total_FIXCHARGE,seedbest_overall_best_result;											
  float    seedbest_best_traveling_time,seedbest_best_best_Total_Risk,seedbest_best_TOTAL_SPECIMENS_LOADING_COST,best_TOTAL_SPECIMENS_LOADING_COST;
 float Total_travelingcost,best_traveling_time,Total_occupational_Risk,occupational_Risk;
 float TOTAL_GOODS_TRANSPORTATION_COST, Total_distance,Total_time,best_distance,best_final_distance,best_final_time,overall_best_result,best_traveling_cost;
float  Optimum_transportation_cost,seedbest_best_best_Total_occupational_Risk,best_Total_occupational_Risk;
 int z;
float SPECIMENS_LOADING_COST,TOTAL_SPECIMENS_LOADING_COST,Total_SPECIMENS_COLLECTION_WEIGHT;
float seedbest_best_best_Total_cost,best_Total_cost;
float weightage_bi_objective,weightage_risk;
float Max_Total_risk,Max_Total_occupational_Risk,Max_weightage_risk,Max_Total_cost,Transportation_risk_factor,weightage_tri_objective;

float SPECIMENS_COLLECTION_WEIGHT[node]={0,10,15,20,22,16,18,24,12,15}; //total weight=152
float SPECIMENS_LOADING_COST_PERUNIT=30.0;


float DISTANCE[node][node][node]=
{{{1000,1001,1002},{29,27,33},{32,30,27},{37,34,32},{18,26,21},{18,16,14},{37,40,35},{39,35,32},{42,47,44},{32,29,26}},

{{29,27,33},{1000,1001,1002},{22,26,28},{30,26,31},{37,36,38},{48,46,43}, {32,36,33},{44,46,47},{30,26,25},{16,15,17}},

 {{32,30,27},{22,26,28},{1000,1001,1002},{32,36,39},{27,26,23},{37,39,41},{11,16,15},{34,38,35},{42,44,47},{32,37,34}},

{{37,34,32},{30,26,31},{32,36,39},{1000,1001,1002},{22,26,28},{27,26,28},{32,36,35},{37,36,40},{24,26,22},{39,36,34}},

{{18,26,21},{37,36,38},{27,26,23},{22,26,28},{1000,1001,1002},{22,26,24},{23,26,28},{32,36,38},{16,16,18},{30,36,31}},

{{18,16,14},{48,46,43},{37,39,41},{27,26,28},{22,26,24},{1000,1001,1002},{34,36,38},{42,46,47},{34,36,38},{32,36,30}},

 {{37,40,35},{32,36,33},{11,16,15},{32,36,35},{23,26,28},{34,36,38},{1000,1001,1002},{12,16,13},{34,36,32},{22,26,20}},

{{39,35,32},{44,46,47},{34,38,35},{37,36,40},{32,36,38},{42,46,47}, {12,16,13},{1000,1001,1002},{24,26,25},{39,36,42}},

{{42,47,44},{30,26,25},{42,44,47},{24,26,22},{16,16,16},{34,36,38},{34,36,32},{24,26,25},{1000,1001,1002},{30,26,25}},

{{41,29,26},{16,15,17},{32,37,34},{39,36,34},{30,36,31},{32,36,30},{22,26,20},{39,36,42},{30,26,25},{1000,1001,1002}}};



//cost per unit distance...
float COST[node][node][node]=
{{{1000,1001,1002},{10,8,11},{9,8,11},{8,9,10},{9,7,11},{8,9,10},{11,9,8},{9,8,11},{7,9,11},{9,10,7}},

{{10,11,8},{1000,1001,1002},{8,9,8},{9,10,11},{8,10,9},{7,9,10}, {11,10,9},{8,9,8},{7,10,8},{11,10,9}},

 {{9,8,11},{8,9,8},{1000,1001,1002},{8,10,10},{9,7,11},{10,9,8},{11,9,9},{10,9,10},{8,8,8},{9,8,10}},

{{8,9,10},{9,10,11},{8,10,10},{1000,1001,1002},{9,8,10},{7,9,9},{8,10,9},{9,9,10},{8,9,10},{9,8,9}},

{{9,7,11},{8,9,10},{9,7,11},{9,8,10},{1000,1001,1002},{10,9,10},{9,8,7},{9,10,8},{7,9,9},{8,10,9}},


{{8,9,10},{7,9,10},{10,9,8},{7,9,9},{10,9,10},{1000,1001,1002},{7,8,8},{9,9,11},{10,9,8},{8,9,9}},

 {{11,9,8},{11,10,9},{11,9,9},{8,10,9},{9,8,7},{7,8,8},{1000,1001,1002},{8,9,8},{10,10,9},{11,9,8}},

{{9,8,11},{8,9,8},{10,9,10},{9,9,10},{9,10,8},{9,9,11}, {8,9,8},{1000,1001,1002},{9,8,10},{10,9,11}},

{{7,9,11},{7,10,8},{8,8,8},{8,9,10},{7,9,9},{10,9,8},{10,10,9},{9,8,10},{1000,1001,1002},{9,11,10}},

{{9,10,7},{11,10,9},{9,8,10},{9,8,9},{8,10,9},{8,9,9},{11,9,8},{10,9,11},{9,11,10},{1000,1001,1002}}};


//cost fixcharge...
float FIXCHARGE[node][node][node]=
{{{1000,1001,1002},{110,111,118},{0,0,0},{8,9,10},{9,7,11},{8,9,10},{11,9,8},{9,8,11},{7,9,11},{9,10,7}},

{{0,0,0},{1000,1001,1002},{8,9,118},{9,10,11},{8,10,9},{7,9,10}, {11,10,9},{8,9,8},{117,10,8},{11,10,9}},

 {{9,118,11},{8,9,8},{1000,1001,1002},{8,10,10},{9,7,11},{10,9,8},{11,119,9},{10,9,10},{8,8,8},{9,8,10}},

{{8,0,10},{9,10,11},{8,10,10},{1000,1001,1002},{9,8,10},{7,9,9},{8,10,9},{0,119,10},{0,0,0},{9,8,9}},

{{9,0,11},{8,9,10},{9,7,11},{9,8,10},{1000,1001,1002},{10,9,10},{9,0,7},{9,10,8},{7,112,9},{8,10,9}},


{{8,9,110},{7,119,10},{0,0,8},{7,9,0},{10,9,10},{1000,1001,1002},{7,8,8},{0,0,0},{10,9,8},{8,9,9}},

 {{11,110,8},{0,10,9},{111,9,9},{8,10,9},{9,0,7},{7,8,8},{1000,1001,1002},{8,9,8},{10,10,9},{11,0,8}},

{{9,0,0},{0,0,118},{10,9,10},{9,9,10},{0,10,8},{9,9,11}, {8,9,8},{1000,1001,1002},{9,8,10},{10,9,11}},

{{7,9,11},{7,10,8},{8,8,8},{8,0,10},{7,9,9},{10,9,8},{10,10,9},{9,8,10},{1000,1001,1002},{9,11,10}},

{{9,10,7},{11,10,9},{119,0,10},{9,8,9},{8,10,9},{0,9,9},{111,9,8},{110,9,11},{9,111,10},{1000,1001,1002}}};



//float TOLLTAX[node][node][node]=
//{{{1000,1001,1002},{29,27,33},{32,30,27},{37,34,32},{18,26,21},{18,16,14},{37,40,35},{39,35,32},{42,47,44},{32,29,26}},
//
//{{29,27,33},{1000,1001,1002},{22,26,28},{30,26,31},{37,36,38},{48,46,43}, {32,36,33},{44,46,47},{30,26,25},{16,15,17}},
//
// {{32,30,27},{22,26,28},{1000,1001,1002},{32,36,39},{27,26,23},{37,39,41},{11,16,15},{34,38,35},{42,44,47},{32,37,34}},
//
//{{37,34,32},{30,26,31},{32,36,39},{1000,1001,1002},{22,26,28},{27,26,28},{32,36,35},{37,36,40},{24,26,22},{39,36,34}},
//
//{{18,26,21},{37,36,38},{27,26,23},{22,26,28},{1000,1001,1002},{22,26,24},{23,26,28},{32,36,38},{16,16,18},{30,36,31}},
//
//{{18,16,14},{48,46,43},{37,39,41},{27,26,28},{22,26,24},{1000,1001,1002},{34,36,38},{42,46,47},{34,36,38},{32,36,30}},
//
// {{37,40,35},{32,36,33},{11,16,15},{32,36,35},{23,26,28},{34,36,38},{1000,1001,1002},{12,16,13},{34,36,32},{22,26,20}},
//
//{{39,35,32},{44,46,47},{34,38,35},{37,36,40},{32,36,38},{42,46,47}, {12,16,13},{1000,1001,1002},{24,26,25},{39,36,42}},
//
//{{42,47,44},{30,26,25},{42,44,47},{24,26,22},{16,16,16},{34,36,38},{34,36,32},{24,26,25},{1000,1001,1002},{30,26,25}},
//
//{{41,29,26},{16,15,17},{32,37,34},{39,36,34},{30,36,31},{32,36,30},{22,26,20},{39,36,42},{30,26,25},{1000,1001,1002}}};
//


//time matrix
float TIME[node][node][node]=
{{{1000,1001,1002},{44,38,46},{45,43,39},{54,49,47},{26,36,31},{25,23,19},{57,59,51},{59,55,52},{63,69,66},{51,48,45}},

{{54,52,48},{1000,1001,1002},{33,39,41},{45,38,47},{55,53,67},{59,69,65}, {46,53,50},{65,67,69},{46,39,37},{23,21,24}},

 {{48,45,41},{34,38,41},{1000,1001,1002},{48,54,58},{40,39,33},{54,56,63},{16,24,23},{49,57,52},{65,67,70},{47,54,49}},

{{55,50,47},{45,39,47},{48,54,58},{1000,1001,1002},{34,38,41},{40,38,41},{47,53,52},{54,53,60},{35,38,33},{58,53,50}},

{{26,38,32},{53,54,57},{39,38,35},{34,38,57},{1000,1001,1002},{34,38,35},{34,39,41},{48,54,56},{24,24,26},{45,54,47}},

{{26,24,22},{68,66,63},{54,59,63},{39,40,42},{34,39,34},{1000,1001,1002},{49,54,58},{62,66,68},{50,54,59},{47,48,45}},

 {{55,60,52},{46,54,49},{19,24,22},{47,54,52},{35,39,42},{50,53,57},{1000,1001,1002},{20,24,21},{50,52,47},{34,39,30}},

{{58,52,47},{64,66,67},{50,56,52},{54,55,60},{47,55,57},{62,66,67}, {20,24,21},{1000,1001,1002},{35,39,37},{59,54,62}},

{{62,67,64},{45,39,37},{62,64,67},{36,39,34},{24,24,26},{50,54,54},{50,54,47},{35,39,37},{1000,1001,1002},{45,39,37}},

{{61,45,39},{24,23,25},{47,55,50},{57,54,50},{45,54,47},{48,53,45},{34,39,30},{58,54,64},{45,39,37},{1000,1001,1002}}};



float RISK[node][node][node]=
{{{1000,1001,1002},{10,11,8},{9,8,11},{8,9,10},{9,7,11},{8,9,10},{11,9,8},{9,8,11},{7,9,11},{9,10,7}},

{{10,11,8},{1000,1001,1002},{8,9,8},{9,10,11},{8,10,9},{7,9,10}, {11,10,9},{8,9,8},{7,10,8},{11,10,9}},

 {{9,8,11},{8,9,8},{1000,1001,1002},{8,10,10},{9,7,11},{10,9,8},{11,9,9},{10,9,10},{8,8,8},{9,8,10}},

{{8,9,10},{9,10,11},{8,10,10},{1000,1001,1002},{9,8,10},{7,9,9},{8,10,9},{9,9,10},{8,9,10},{9,8,9}},

{{9,7,11},{8,9,10},{9,7,11},{9,8,10},{1000,1001,1002},{10,9,10},{9,8,7},{9,10,8},{7,9,9},{8,10,9}},


{{8,9,10},{7,9,10},{10,9,8},{7,9,9},{10,9,10},{1000,1001,1002},{7,8,8},{9,9,11},{10,9,8},{8,9,9}},

 {{11,9,8},{11,10,9},{11,9,9},{8,10,9},{9,8,7},{7,8,8},{1000,1001,1002},{8,9,8},{10,10,9},{11,9,8}},

{{9,8,11},{8,9,8},{10,9,10},{9,9,10},{9,10,8},{9,9,11}, {8,9,8},{1000,1001,1002},{9,8,10},{10,9,11}},

{{7,9,11},{7,10,8},{8,8,8},{8,9,10},{7,9,9},{10,9,8},{10,10,9},{9,8,10},{1000,1001,1002},{9,11,10}},

{{9,10,7},{11,10,9},{9,8,10},{9,8,9},{8,10,9},{8,9,9},{11,9,8},{10,9,11},{9,11,10},{1000,1001,1002}}};


 //FILE * fit;
int pv = noc;
float cumuprob[noc],prob[noc];
int nparr[noc];  /*new population array*/
 float ALPHA=0.9,ita=5.6;
double Max_Val= 999999.0;
	double total;
	 struct chrom
	 {
	  int pt[node],tv[node],green_pt[node],pr1_mutation[node];
	  int vehicle[node];
	  float fitness;//over all best fitness store
	  float fitness1;  //for risk
	  float time;
	   float Total_travelingcost;
	   float Total_Traveling_time;
	   float Total_Risk;
	   float Total_occupational_Risk;
	   float Total_cost;
	   float final_distance;
	   float final_time;
	   float TOTAL_SPECIMENS_LOADING_COST;
	   float Total_FIXCHARGE;
		  int ch_no;//store the best chromose number
	  }ch[noc],optimum,Popu_Opt_Val,Gen_Opt_Val,Final_Opt_Val;

	struct chrom popu[noc+noc];
	struct chrom npopu[noc+noc];
		struct chrom fpopu[noc];
		struct chrom obl_popu[noc+noc];


	void initialpopulation();
	void calfitness(int pv);
	void obl_calfitness(int pv);
	void selection_RW();
	void selection_probabilistic();
	void crossover_comparison(int pv);
	void cross_comparison(int p0,int p1, int pv);
	void crossover_cyclic(int pv);
	void cross_cyclic(int p0,int p1, int pv);
	void mutation(int pv);
	void mutate(int p,int pv);
	float result();
    float TOTAL_GOODS_WEIGHT;
    int best_optimal_path_new_final[node];
    void check_risk(int p0);

	int main()
		{

			int seed,z1[node],z2[node],p,k,r_node;
			float q,y2[3];
			 float seedbest=00000;
			 float seedbest1=00000;
			 int bestseed,bestgen;
			 int best_optimal_path[node];
			int best_optimal_path_new[node];

	
	for(seed=1;seed<=maxseed;seed++)
       {
       	//	  printf("\n \n for seed= %d",seed); getch();
           
		  	srand(seed);
			optimum.fitness=70000;
			initialpopulation();		
			y2[0]=00000000.0;
			/* APPLY GENETIC ALGORITHM */
			for(k=0;k<maxgen;k++)
				  {
                     calfitness(pv);
                     
					// selection_RW();
					 selection_probabilistic();
					 
					 crossover_comparison(pv);
					 //crossover_cyclic(pv);
					 
			 		 mutation(pv);
					 q=result();
					 if(y2[0]<q)
					 {
						y2[0]=q;

							best_final_distance= optimum.final_distance;
							
								best_traveling_cost=optimum.Total_travelingcost;
								 best_traveling_time=optimum.Total_Traveling_time; 
                                best_Total_Risk=optimum.Total_Risk;
                                 best_Total_occupational_Risk=optimum.Total_occupational_Risk;
                                best_Total_cost=optimum.Total_cost;

                                
					
						best_TOTAL_SPECIMENS_LOADING_COST=optimum.TOTAL_SPECIMENS_LOADING_COST;	
						best_Total_FIXCHARGE=optimum.Total_FIXCHARGE;
						
							overall_best_result=optimum.fitness;																							
						 p=k;
						for(int j=0;j<node;j++)
						  {
							z1[j]=optimum.pt[j];
						    z2[j]=optimum.vehicle[j];
						  }
					  }
				   }
     
					
			 printf("\n \n best_final_distance= %f",best_final_distance);

			printf("\n best_traveling_cost= %f",best_traveling_cost);
					printf("\n   best_final_traveling_time= %f",best_traveling_time);
					
              		printf("\n best_Total_Risk= %f",best_Total_Risk);
              			printf("\n best_Total_occupational_Risk= %f",best_Total_occupational_Risk);
                	printf("\n best_Total_cost= %f",best_Total_cost);

              			
              		
              			printf("\n best_TOTAL_SPECIMENS_LOADING_COST= %f",best_TOTAL_SPECIMENS_LOADING_COST);
              			printf("\n best_Total_FIXCHARGE= %f",best_Total_FIXCHARGE);
              			
					printf("\n best_overall_cost= %f\n",overall_best_result);

				for(int j=0;j<node;j++)
                  	{
				     	best_optimal_path[j]=z1[j];
                        Final_Opt_Val.tv[j]=z2[j];                   
					 }

			for(int j=0;j<node;j++)
        {
        printf("%d[%d]\t",best_optimal_path[j],Final_Opt_Val.tv[j]);

		}
             if(seedbest<=y2[0])
				{
				  seedbest=y2[0];
				  float best_distance=Total_distance;				 
                   bestseed=seed;
				   bestgen=p;
				   Final_Opt_Val= Gen_Opt_Val;
				   for(int j=0;j<node;j++)
                  	{
				     	best_optimal_path[j]=z1[j];
                       Final_Opt_Val.tv[j]=z2[j];
					 }
					 
					 seedbest_best_final_distance=	best_final_distance;
							
							seedbest_best_traveling_cost=	best_traveling_cost;
							
							seedbest_best_traveling_time=  best_traveling_time;
							
                            seedbest_best_best_Total_Risk=best_Total_Risk;
                            seedbest_best_best_Total_occupational_Risk=best_Total_occupational_Risk;
                             seedbest_best_best_Total_cost=best_Total_cost;
                            
                            
                           seedbest_best_TOTAL_SPECIMENS_LOADING_COST= best_TOTAL_SPECIMENS_LOADING_COST;
                           
                           seedbest_best_Total_FIXCHARGE=best_Total_FIXCHARGE;
                           
                          seedbest_overall_best_result=overall_best_result;
			    	}
      }      
        printf("\n  Final Optimum Result Found At TheGeneration =%d at the seed =%d\n",bestgen,bestseed);
		printf("\n Optimum Value =%f\n",seedbest); ;
        printf("...Final traveling path\n");
		for(int j=0;j<node;j++)
        {
        printf("%d[%d]\t",best_optimal_path[j],Final_Opt_Val.tv[j]);

		}

		printf("\n seedbest_best_final_distance =%f\n",seedbest_best_final_distance);
		
	printf("\n seedbest_best_traveling_cost =%f\n",seedbest_best_traveling_cost);
	
	printf("\n seedbest_best_TOTAL_SPECIMENS_LOADING_COST =%f\n",seedbest_best_TOTAL_SPECIMENS_LOADING_COST);
	
	printf("\n seedbest_best_Total_FIXCHARGE =%f\n",seedbest_best_Total_FIXCHARGE);
	
		printf("\n final cost (optimal) seedbest_overall_best_result =%f\n",seedbest_overall_best_result);
		
		printf("\n seedbest_best_best_Total_Risk =%f\n",seedbest_best_best_Total_Risk);
		
		printf("\n seedbest_best_best_Total_occupational_Risk =%f\n",seedbest_best_best_Total_occupational_Risk);
		
		printf("\n seedbest_best_best_Total_cost =%f\n",seedbest_best_best_Total_cost);
		
		
			printf("\n seedbest_best_traveling_time =%f\n",seedbest_best_traveling_time);
	
	getch();

    return 0;
}




		 void initialpopulation()
		 {

				  int i,j,t2,path[node],j1,flag,veh[node];
					int z,r,g;
					 float sum;


				              for(int i=0;i<noc;i++)
				     	{
						 	for(int j=0;j<node;j++)
			                 {
			  				 npopu[i].green_pt[j]=0;
			  				 popu[i].green_pt[j]=0;
			  				 }
						 }


				for(i=0;i<noc;i++)
					 {

				  //	  again://if do not satisfy constrains then again construct path//
						 t2=0;
						 path[t2]=0;   //ist node inital with 0
						 t2++;
							v: r=rand()%node;
						//printf("%d",r);
							 flag=1;
							 for(j1=0;j1<t2;j1++)
							 {
							 
								 if(r==path[j1])
								 {
								 	 flag=0;
								 }
							}
								

							if(flag==1)
							 {
							  path[t2]=r;
							  t2++;
							  }
						  if(t2==node)
						  goto k;
						  goto v;

						 k:

					 /* select vehicle/path of each path by random no. */

					  for(g=0;g<node;g++)
						 {
							z=rand()%nov;
							veh[g]=z;
						 }



					 for(g=0;g<node;g++)
					 popu[i].vehicle[g]=veh[g];

					  for(z=0;z<node;z++)
					 popu[i].pt[z]=path[z];

					 	
						 
						 
						 
		
			  sum=0.0;
			  float Total_distance=0.0;
			  float Total_time=0.0;
			  float Total_FIXCHARGE=0.0;
			   Total_SPECIMENS_COLLECTION_WEIGHT=0.0;
                  TOTAL_SPECIMENS_LOADING_COST=0.0;

			  for(j=0;j<node-1;j++)
              {
              	       Total_distance+=DISTANCE[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]];
              	       sum+=(COST[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]])*DISTANCE[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]]; // cost per unit distance * distance
                        Total_FIXCHARGE+=FIXCHARGE[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]];
                        
						Total_time+=TIME[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]];
                       Total_SPECIMENS_COLLECTION_WEIGHT=Total_SPECIMENS_COLLECTION_WEIGHT+SPECIMENS_COLLECTION_WEIGHT[j];
              }
              Total_distance+=DISTANCE[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[node-1]];
              Total_FIXCHARGE+=FIXCHARGE[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[node-1]];
              Total_time+=TIME[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[j]];          
               sum+=(COST[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[node-1]])*(DISTANCE[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[j]]);

			   			check_risk(i);
			   			if((popu[i].Total_Risk>Max_risk))  // for feasible path checking
			   			{
			   			i=i-1;
						   }	 	
					}
						
                 calfitness(pv);
//					 	printf("\n initial full population \n"); //getch();
//						for(i=0;i<noc;i++)
//						{
//						  for(j=0;j<node;j++)
//						  {
//							 printf("%d ",popu[i].pt[j]);
//							}
//							printf("\n");
//							for(j=0;j<node;j++)
//						  {
//							printf("%d ",popu[i].vehicle[j]);
//							}
//						  printf(" F[%d]=%f\n",i,popu[i].fitness);
//						}
						
			//initial with all 0 s	
			//	printf("\n OBL of initial full population \n"); //getch();		
				for(i=0;i<noc+noc;i++)
						{
						  for(j=0;j<node;j++)
						  {
						  	obl_popu[i].pt[j]=0;
						//	printf("%d ",obl_popu[i].pt[j]);
							}
						//	printf("\n");
							for(j=0;j<node;j++)
						  {
						  	obl_popu[i].vehicle[j]=0;
						//	printf("%d ",obl_popu[i].vehicle[j]);
							}
						//	printf("\n");
						  //printf(" F[%d]=%f\n",i,popu[i].fitness);
						}		
						
						
						//printf("\n OBL of initial full population \n"); getch();
						
						for(i=0;i<noc;i++)
						{
						  for(j=0;j<node;j++)
						  {
						  	obl_popu[i].pt[j]=popu[i].pt[j];
							// printf("%d ",obl_popu[i].pt[j]);
							}
						//	printf("\n");
							for(j=0;j<node;j++)
						  {
						  	obl_popu[i].vehicle[j]=popu[i].vehicle[j];
						//	printf("%d ",obl_popu[i].vehicle[j]);
							}
						//	printf("\n");
						  //printf(" F[%d]=%f\n",i,popu[i].fitness);
						}
						
					//	printf("\n OBL 2nd part ....of initial full population \n"); getch();
							for(i=noc;i<noc+noc;i++)
						{
						  for(j=1;j<node;j++)
						  {
						  	if(obl_popu[i].pt[j]!=(node-1))
						  	{
						  	obl_popu[i].pt[j]= (node-1)-popu[i-noc].pt[j];
							  
					    	}
					    	
						if	(obl_popu[i].pt[j]==0)
						{
							obl_popu[i].pt[j]=(node-1);
						}
							
						//	printf("%d ",obl_popu[i].pt[j]);
							}
						//	printf("\n");
							for(j=1;j<node;j++)
						  {
						  	obl_popu[i].vehicle[j]=popu[i-noc].vehicle[j];
							
							}
						//	printf("\n");
						  //printf(" F[%d]=%f\n",i,obl_popu[i].fitness);
						}
						

//
//      	printf("\n normal+OBL of initial full population \n"); getch();
//							
//                     for(i=0;i<noc+noc;i++)
//						{
//						  for(j=0;j<node;j++)
//						  {
//						  
//							 printf("%d ",obl_popu[i].pt[j]);
//							}
//							printf("\n");
//							for(j=0;j<node;j++)
//						  {
//							printf("%d ",obl_popu[i].vehicle[j]);
//							}
//							printf("\n");
//						}
						
						obl_calfitness(pv);
						
						for(i=noc;i<noc+noc;i++)
						{
						 	if((popu[i].Total_Risk>Max_risk))  
			   			{
			   			for(j=0;j<node;j++)
						  {
						  
							 	obl_popu[i].pt[j]= popu[i-noc].pt[j];
							 	obl_popu[i].vehicle[j]= popu[i-noc].vehicle[j];
							}
						   }
						  
						  
						  
						}
						
       // 	getch();

   //convert all the values into population 
  // printf("\n final.........normal+OBL of initial full population \n"); getch();   
	    	for(i=0;i<noc+noc;i++)
						{
						  for(j=0;j<node;j++)
						  {
						  	popu[i].pt[j]=obl_popu[i].pt[j];
						//	 printf("%d ",popu[i].pt[j]);
							}
						//	printf("\n");
							for(j=0;j<node;j++)
						  {
						  	popu[i].vehicle[j]=obl_popu[i].vehicle[j];
						//	printf("%d ",popu[i].vehicle[j]);
							}
						//	printf("\n");
						  //printf(" F[%d]=%f\n",i,popu[i].fitness);
						}
							obl_calfitness(pv);



        }
        



	void obl_calfitness(int pv)
		{
		  int i,j;
		  float sum;
		  for( i=0;i<noc+noc;i++)
			{
			  sum=0.0;
			  float Total_distance=0.0;
			  float Total_FIXCHARGE=0.0;
			  float Total_time=0.0;
			   Total_SPECIMENS_COLLECTION_WEIGHT=0.0;
                float  TOTAL_SPECIMENS_LOADING_COST=0.0;

			  for(j=0;j<node-1;j++)
              {
              	       Total_distance+=DISTANCE[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]];
              	       sum+=(COST[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]])*DISTANCE[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]]; // cost per unit distance * distance
                        Total_time+=TIME[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]];
                       Total_SPECIMENS_COLLECTION_WEIGHT=Total_SPECIMENS_COLLECTION_WEIGHT+SPECIMENS_COLLECTION_WEIGHT[j];
                       
                        Total_FIXCHARGE+=FIXCHARGE[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]];
                        
                       TOTAL_SPECIMENS_LOADING_COST+=SPECIMENS_LOADING_COST_PERUNIT*SPECIMENS_COLLECTION_WEIGHT[j];
                       
                      // printf("\n the result of =%f",TOTAL_SPECIMENS_LOADING_COST); getch();
              }
              Total_distance+=DISTANCE[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[node-1]];
              Total_FIXCHARGE+=FIXCHARGE[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[node-1]];
              
              Total_time+=TIME[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[j]];
               sum+=(COST[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[node-1]])*(DISTANCE[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[j]]);

			           popu[i].Total_Traveling_time=Total_time;
			           	 popu[i].final_distance=Total_distance;
						 popu[i].Total_travelingcost=sum;
					popu[i].fitness=popu[i].Total_travelingcost;
			     	check_risk(i);
					popu[i].Total_Risk=popu[i].Total_Risk;
					
						popu[i].TOTAL_SPECIMENS_LOADING_COST=TOTAL_SPECIMENS_LOADING_COST;	
					//	printf("\n \n \n  the result of =%f",popu[i].TOTAL_SPECIMENS_LOADING_COST); getch();					
			}
		
//			 	printf("\n full all....call fitness population\n");
//						for(i=0;i<noc+noc;i++)
//						{
//						  for(j=0;j<node;j++)
//						  {
//							 printf("%d ",popu[i].pt[j]);
//							}
//							printf("\n");
//							for(j=0;j<node;j++)
//						  {
//							printf("%d ",popu[i].vehicle[j]);
//							}
//						  printf("   F[%d]=%f\n",i,popu[i].fitness);
//						} 
					//	getch();    

		 }


	void calfitness(int pv)
		{
		  int i,j;
		  float sum;
		  for( i=0;i<noc;i++)
			{
			  sum=0.0;
			  float Total_distance=0.0;
			  float Total_FIXCHARGE=0.0;
			  float Total_time=0.0;
			   Total_SPECIMENS_COLLECTION_WEIGHT=0.0;
			   float TOTAL_SPECIMENS_LOADING_COST=0.0;
			   Total_occupational_Risk=0;
			   Max_Total_risk=0.0;
			   Max_Total_occupational_Risk=0.0;
			   Max_weightage_risk=0.0;
			   Max_Total_cost=0.0;
			   
                 // TOTAL_SPECIMENS_COLLECTION_COST=0.0;
			  for(j=0;j<node-1;j++)
              {
              	       Total_distance+=DISTANCE[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]];
              	       sum+=(COST[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]])*DISTANCE[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]]; // cost per unit distance * distance
                        Total_time+=TIME[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]];
                        
                        Total_FIXCHARGE+=FIXCHARGE[popu[i].pt[j]][popu[i].pt[j+1]][popu[i].vehicle[j]];
                        
                       Total_SPECIMENS_COLLECTION_WEIGHT=Total_SPECIMENS_COLLECTION_WEIGHT+SPECIMENS_COLLECTION_WEIGHT[j];
                       TOTAL_SPECIMENS_LOADING_COST+=SPECIMENS_LOADING_COST_PERUNIT*SPECIMENS_COLLECTION_WEIGHT[j];
                       
                       Total_occupational_Risk=Total_occupational_Risk+(SPECIMENS_COLLECTION_WEIGHT[j]*Total_time/(60*100)); //*per_unit_occupational_risk 10 (-2)*people around(100);
                       
                      // 	printf("\n the result of Total_FIXCHARGE=%f", Total_occupational_Risk); getch();
              }
              Total_distance+=DISTANCE[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[node-1]];
              Total_FIXCHARGE+=FIXCHARGE[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[node-1]];
              
              Total_time+=TIME[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[j]];
               sum+=(COST[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[node-1]])*(DISTANCE[popu[i].pt[node-1]][popu[i].pt[0]][popu[i].vehicle[j]]);
               
			           popu[i].Total_Traveling_time=Total_time;
			           	 popu[i].final_distance=Total_distance;						 
						 popu[i].Total_travelingcost=sum;
				
			    	check_risk(i);
			    	
			    	popu[i].TOTAL_SPECIMENS_LOADING_COST=TOTAL_SPECIMENS_LOADING_COST;
			    	popu[i].Total_FIXCHARGE=Total_FIXCHARGE;
			    	
			    	popu[i].Total_Risk=popu[i].Total_Risk;   //transportation risk
			    	popu[i].Total_occupational_Risk=Total_occupational_Risk;
			    	popu[i].Total_cost=popu[i].Total_travelingcost+popu[i].TOTAL_SPECIMENS_LOADING_COST+popu[i].Total_FIXCHARGE;
			    	
//			    	if(Max_Total_risk<popu[i].Total_Risk)
//			    	{
//			    	Max_Total_risk=	popu[i].Total_Risk;
//					}
//			   		if(Max_Total_occupational_Risk<popu[i].Total_occupational_Risk)
//			    	{
//			    	Max_Total_occupational_Risk=popu[i].Total_occupational_Risk;
//					}
//			    	
			    	
			  //  	weightage_risk=(w1)*(popu[i].Total_Risk)+ (w2)*(popu[i].Total_occupational_Risk);
						
			    //	weightage_risk=(w1)*(popu[i].Total_Risk/Max_Total_risk)+ (w2)*(popu[i].Total_occupational_Risk/Max_Total_occupational_Risk);
			    	
			    
//					if(Max_weightage_risk<weightage_risk)
//			    	{
//			    	Max_weightage_risk=	weightage_risk;
//					}
//			   		if(Max_Total_cost<popu[i].Total_cost)
//			    	{
//			    	Max_Total_cost=popu[i].Total_cost;
//					}	
//			    	
			    	
			    	// weightage_bi_objective= (w3)*(weightage_risk/100)+ (w4)*(popu[i].Total_cost/1000);   //Max_weightage_risk=100    Max_Total_cost=10000
			    	
			    	weightage_tri_objective=w1*((popu[i].Total_Risk-34.17)/57.32) + w2*((popu[i].Total_occupational_Risk-3.70)/3.98)+ w3*((popu[i].Total_cost-6026)/6443);
			    	
			    	weightage_bi_objective=w1*((popu[i].Total_Risk-34.17)/57.32) + w2*((popu[i].Total_occupational_Risk-3.70)/3.98);
			    	
			    //	weightage_bi_objective=w1*((popu[i].Total_Risk-34.17)/57.32) + w3*((popu[i].Total_cost-6026)/6443);
			    	
			    //	weightage_bi_objective= w2*((popu[i].Total_occupational_Risk-3.70)/3.98) + + w3*((popu[i].Total_cost-6026)/6443);;
			    	
			    // popu[i].fitness=popu[i].Total_cost;        //Total_Risk      Total_occupational_Risk      Total_cost
			     popu[i].fitness=popu[i].Total_Risk;
			    
			     //	popu[i].fitness=weightage_bi_objective;         // weightage_bi_objective; weightage_risk, weightage_tri_objective
			     	
			    	
			    //	printf("\n \n the result of weightage_tri_objective=%f", weightage_tri_objective); getch();
					
			}
		
//			 	printf("\n after call fitness population\n");
//						for(i=0;i<noc+noc;i++)
//						{
//						  for(j=0;j<node;j++)
//						  {
//							 printf("%d ",popu[i].pt[j]);
//							}
//							printf("\n");
//							for(j=0;j<node;j++)
//						  {
//							printf("%d ",popu[i].vehicle[j]);
//							}
//						  printf("   F[%d]=%f\n",i,popu[i].fitness);
//						} 
//						getch();    

		 }
		 
		 
 //****** RW SELECTION  ***************************************************************************
 //**********************************************************************************************
  void selection_RW()
	{
	  float s=0.0,r,s1=0.0;
	  int i,k,count,p,j;

	  for( i=0;i<noc+noc;i++)
	  {
	  	 s+=popu[i].fitness;
			}		
	  for( i=0;i<noc+noc;i++)
	  {
	  	prob[i]=popu[i].fitness/s;
	  }
			
	  s1=0.0;
	  for(i=0;i<noc+noc;i++)
		  {
			s1=s1+prob[i];
			cumuprob[i]=s1;
		  }
	  count=0;
	  for(i=0;i<noc+noc;i++)
		 {
			r=(rand()%1000)/1000.;
			//printf("%f",r);
			 for(k=0;k<noc+noc;k++)
			 {
				if(r<cumuprob[k])
			  {
				 nparr[count]=k;
				// printf("%d",k);
				 count++;
				 goto u;
				}
			}
		  u: 5;
		}


//	  for(i=0;i<noc+noc;i++)
//			{
//				printf("\n before selection value of i=%d",i);
//				for(j=0;j<node;j++)
//				{
//				 printf("%d  ",popu[i].pt[j]);
//				 }
//				  //npopu[i].fitness=popu[p].fitness;
//			}

     for(i=0;i<noc+noc;i++)
     {
     //	printf("\n");
      for(j=0;j<node;j++)
      {
     	npopu[i].pt[j]=popu[nparr[i]].pt[j];
     	npopu[i].vehicle[j]=popu[nparr[i]].vehicle[j];
     	
      //	printf(" %d ",npopu[i].pt[j]);
	  }
	 }
     
		
			
//				printf("\n after selection population\n");
//						for(i=0;i<noc+noc;i++)
//						{
//						  for(j=0;j<node;j++)
//						  {
//							 printf("%d ",npopu[i].pt[j]);
//							}
//							printf("\n");
//							for(j=0;j<node;j++)
//						  {
//							printf("%d ",npopu[i].vehicle[j]);
//							}
//						  printf("   F[%d]=%f\n",i,npopu[i].fitness);
//						} 
//						
//						getch(); 
					  
		  }

//*************************************************************************************************************************

//*******************************************************************************************************************************
/*BOLTZMAN PROBABILSTIC SELECTION */

void selection_probabilistic()
{
int no_genrtn=k;	
float r,b,a,k;

double p,t;
int i,j,z,t0;
b=Max_Val;
for(i=1;i<noc+noc;i++)
{
   if(popu[i].fitness<b)
   {
      b=popu[i].fitness;
      z=i;}
	  }
a1:	t0=rand()%101;
if(t0==0||t0==1||t0==2||t0==3||t0==4||t0==5)
   goto a1;
r=(rand()%1000)/1000.;
a=r;
p=(float)((float)no_genrtn/(float)maxgen);
k=(1+100.0*p);
t=t0*pow((1-a),k);

for(i=0;i<noc+noc;i++)
{
   r=(rand()%1000)/1000.;
   if(r<=ps)
   {
      npopu[i].fitness=popu[i].fitness;
      for(j=0;j<node;j++)
      {
      	npopu[i].pt[j]=popu[i].pt[j];
      	npopu[i].vehicle[j]=popu[i].vehicle[j];
	  }
          
		  }
   else if(exp((b-popu[i].fitness)/t)>r)
   {
           npopu[i].fitness=popu[i].fitness;
           for(j=0;j<node;j++)
                {
      	npopu[i].pt[j]=popu[i].pt[j];
      	npopu[i].vehicle[j]=popu[i].vehicle[j];
	  }
			   }
   else{
       npopu[i].fitness=popu[z].fitness;
       for(j=0;j<node;j++)
           {
      	npopu[i].pt[j]=popu[i].pt[j];
      	npopu[i].vehicle[j]=popu[i].vehicle[j];
	  }
		  }
	}
//	
//	printf("\nSelective population\n");
//		for(i=0;i<pv;i++)
//		{
//			//	printf("pos=%d  ",nparr[i]);
//				for(j=0;j<node;j++)
//				printf("%d ",npopu[i].pt[j]);
//			printf("\n");
//			}
//			getch();
//

}

//**********************************************************************************************************************************************

void crossover_comparison( int pv)
    {
     int i,j,pos[2],count=0;
     float r;

	

     for(int cross_prob=0;cross_prob<pc*pv/2;cross_prob++)
	 {
     for(i=0;i<pv;i++)
        {
         r=(rand()%1000)/1000.;
         if(r<=pc)
           {
            pos[count]=i;
            count++;
            if(count==2)
              {
               cross_comparison(pos[0],pos[1],pv);
               cross_prob ++;
               count=0;
              }
            }
        }

      }
      
      
              
        for(i=0;i<pv;i++)
        {
            for(int k=0;k<node;k++)
			{
             popu[i].pt[k]=npopu[i].pt[k];
             popu[i].vehicle[k]=npopu[i].vehicle[k];
			 popu[i].green_pt[k]=npopu[i].green_pt[k];
			 }
			 }
           calfitness(pv);
           
//           	printf("\n after crossover \n");
//						for(i=0;i<noc;i++)
//						{
//						  for(j=0;j<node;j++)
//						  {
//							 printf("%d ",popu[i].pt[j]);
//							}
//							printf("\n");
//							for(j=0;j<node;j++)
//						  {
//							printf("%d ",popu[i].vehicle[j]);
//							}
//						  printf("   F[%d]=%f\n",i,popu[i].fitness);
//						} 
//
//						getch(); 
    }

 void cross_comparison(int p0,int p1,int pv)
      {
       int i,j,pos,k,temp;
       
       //int pr1[node],ch1[node],pr2[node],ch2[node];
       struct chrom pr1,ch1,pr2,ch2,parent1,parent2;
       //copy 1st chromosome into pr1[]
        for(i=0;i<pv;i++)
           {
            if(p0==i)
              {
               for(j=0;j<node;j++)
               {
               	 pr1.pt[j]=npopu[i].pt[j];
               	  pr1.vehicle[j]=npopu[i].vehicle[j];
               	   
               	  
               	  parent1.pt[j]=npopu[i].pt[j];
               	  parent1.vehicle[j]=npopu[i].vehicle[j];
              
			   }

              }
           }
       //copy 2nd  chromosome into pr2[]
        for(i=0;i<pv;i++)
           {
            if(p1==i)
              {
               for(j=0;j<node;j++)
			   {
			    pr2.pt[j]=npopu[i].pt[j];
                pr2.vehicle[j]=npopu[i].vehicle[j];
                //pr2.goodsTP_Vehicle[j]=npopu[i].goodsTP_Vehicle[j];
                parent2.pt[j]=npopu[i].pt[j];
                parent2.vehicle[j]=npopu[i].vehicle[j];
               
               }
              }
           }
           
//   printf("\nThe two parents \n");         
//		   for(j=0;j<node;j++)
//		   {
//
//         printf("%d[%d]\t",pr1.pt[j], pr1.vehicle[j]);
//           }  
//      for(j=0;j<node;j++)
//       {
//       printf(" %d[%d]\t",pr2.pt[j], pr2.vehicle[j]);
//       }
//       getch();

int cmn[node];
int cmn_indx = 0;
for(i=0;i<node;i++){
    for(j=0;j<node;j++){
        if (pr1.pt[i] == pr2.pt[j]){
            cmn [cmn_indx] = pr1.pt[i];
            cmn_indx = cmn_indx+1;
            break;
        }}}
int pos1 = cmn[rand()%cmn_indx];
        pos1 =0;
       for(i=0;i<node;i++)
          {
           ch1.pt[i]=Max_Val;
           ch2.pt[i]=Max_Val;
          }

      /* AS Crossover  */
       int l;
       int temp1[node] , temp2[node],temp12[node],temp22[node];
       for( int m=0;m<node;m++){
          if(pr1.pt[m]==pos1){
            for(i=0;i<node;i++){
			   temp1[i]=pr1.pt[(i+m)%node];
                temp12[i]=pr1.vehicle[(i+m)%node];
            }}

          if(pr2.pt[m]==pos1){
			for(i=0;i<node;i++){
			   temp2[i]=pr2.pt[(i+m)%node];
               temp22[i]=pr2.vehicle[(i+m)%node];
                                      }}}

	  //printf("\nThe first parents\n");
       for(j=0;j<node;j++)
          {
           pr1.pt[j] = temp1[j];
          pr1.vehicle[j]=temp12[j];
           pr2.pt[j] = temp2[j];
          pr1.vehicle[j]=temp22[j];
          }
       ch1.pt[0]=pos1;
       ch1.vehicle[0]=pr1.vehicle[0];
      // ch1.goodsTP_Vehicle[0]=pr1.goodsTP_Vehicle[0];
       i=1;
       j=1;
       int m=1;
       while((m<node)&&(i<node)&&(j<(node)))
           {

            for(int k=m-1;k>0;k--)
               {
                if(ch1.pt[k]==pr1.pt[i])
                  {
                   for(l=m-1;l>0;l--)
                      {
                       if(ch1.pt[l]==pr2.pt[j])
                         {
                          i=i+1;
                          j=j+1;
                          // printf("\nThe first parents %d\n",m);
                          goto a;
                         }
                      }
                     /* ch1.pt[m]=pr2.pt[j];
                      ch1.vehicle[m]=pr1.vehicle[j];
                    //  ch1.goodsTP_Vehicle[m]=pr1.goodsTP_Vehicle[j];
                      j=j+1;
                      m=m+1;*/
                      i=i+1;
                      goto  a;
                  }
                else if(ch1.pt[k]==pr2.pt[j])
					   {
                        for(int d=m-1;d>0;d--)
						  {
                           if(ch1.pt[d]==pr1.pt[i])
                             {
                              i=i+1;
                              j=j+1;
                              goto a;
                             }
                          }
                     /* ch1.pt[m]=pr1.pt[i];
                      ch1.vehicle[m]=pr1.vehicle[i];
                      //ch1.goodsTP_Vehicle[m]=pr1.goodsTP_Vehicle[i];
                       i=i+1;
                      m=m+1;*/
                      j=j+1;
                      goto  a;
                     }
                }

            

if((DISTANCE[ch1.pt[m-1]][pr1.pt[i]][ch1.vehicle[m-1]]*COST[ch1.pt[m-1]][pr1.pt[i]][ch1.vehicle[m-1]]  )==(DISTANCE[ch1.pt[m-1]][pr2.pt[j]][ch1.vehicle[m-1]]*COST[ch1.pt[m-1]][pr2.pt[j]][ch1.vehicle[m-1]] )) /*product_units[pr2.pt[j]] * product_costs[pr2.pt[j]]*/
  {
   if(pr1.pt[i]==pr2.pt[j])
     {
      ch1.pt[m]=pr1.pt[i];
      ch1.vehicle[m]=pr1.vehicle[i];
      //ch1.goodsTP_Vehicle[m]=pr1.goodsTP_Vehicle[i];
      i=i+1;
      j=j+1;
      //printf("%d\t",ch1.pt[m]);
     }
   else
     {
      ch1.pt[m]=pr1.pt[i];
      ch1.vehicle[m]=pr1.vehicle[i];
     // ch1.goodsTP_Vehicle[m]=pr1.goodsTP_Vehicle[i];
      i=i+1;
      // printf("\nThe first parents cost %d\n",m);
     }
      m=m+1;
    }
else if((DISTANCE[ch1.pt[m-1]][pr1.pt[i]][ch1.vehicle[m-1]]*COST[ch1.pt[m-1]][pr1.pt[i]][ch1.vehicle[m-1]]  )<(DISTANCE[ch1.pt[m-1]][pr2.pt[j]][ch1.vehicle[m-1]]*COST[ch1.pt[m-1]][pr2.pt[j]][ch1.vehicle[m-1]] ))
       {
        ch1.pt[m]=pr1.pt[i];
        ch1.vehicle[m]=pr1.vehicle[i];
       // ch1.goodsTP_Vehicle[m]=pr1.goodsTP_Vehicle[i];
        i=i+1;
        m=m+1;
        // printf("\n i=%d m=%d\n",i,m);
       }
     else
        {
         ch1.pt[m]=pr2.pt[j];
         ch1.vehicle[m]=pr1.vehicle[j];
        // ch1.goodsTP_Vehicle[m]=pr1.goodsTP_Vehicle[j];
         j=j+1;
         m=m+1;
        }
       a: continue;
}


int pos2 = cmn[rand()%cmn_indx];

pos2 =0;
for( m=0;m<node;m++)
{
    if(pr1.pt[m]==pos2)
	{
    for(i=0;i<node;i++){
       temp1[i]=pr1.pt[(i+m)%node];
     temp12[i]=pr1.vehicle[(i+m)%node];
        if(pr2.pt[m]==pos2){
         for(i=0;i<node;i++){
           temp2[i]=pr2.pt[(i+m)%node];
         temp22[i]=pr2.vehicle[(i+m)%node];}}}

for(j=0;j<node;j++)
   {
    pr1.pt[j] = temp1[j];
    pr2.pt[j] = temp2[j];
    pr1.vehicle[j]=temp12[j];
    pr2.vehicle[j]=temp22[j];
    }

ch2.pt[0]=pos2;
ch2.vehicle[0]=pr2.vehicle[0];
//ch2.goodsTP_Vehicle[0]=pr2.goodsTP_Vehicle[0];
i=1;
j=1;
m=1;
while((m<node)&&(i<node)&&(j<node))
	 {
 	 for(int k=m-1;k>0;k--)
        {
         if(ch2.pt[k]==pr1.pt[i])
           {
            for (l=m-1;l>0;l--)
                {
                 if(ch2.pt[l]==pr2.pt[j])
                   {
                    i=i+1;
                    j=j+1;
                    goto b;
                   }
                }
           /* ch2.pt[m]=pr2.pt[j];
            ch2.vehicle[m]=pr2.vehicle[j];
           // ch2.goodsTP_Vehicle[m]=pr2.goodsTP_Vehicle[j];
            j=j+1;
            m=m+1;*/
            i=i+1;
            goto  b;
            }
         else if(ch2.pt[k]==pr2.pt[j])
                {
                 for (int d=m-1;d>0;d--)
                     {
                      if(ch2.pt[d]==pr1.pt[i])
                        {
                         i=i+1;
                         j=j+1;
			             goto b;
                        }
                     }

               /* ch2.pt[m]=pr1.pt[i];
                ch2.vehicle[m]=pr2.vehicle[i];
              //  ch2.goodsTP_Vehicle[m]=pr2.goodsTP_Vehicle[i];
                i=i+1;
                m=m+1;*/
                j=j+1;
                goto  b;
                }
            }
if((DISTANCE[ch2.pt[m-1]][pr1.pt[i]][ch2.vehicle[m-1]]*COST[ch2.pt[m-1]][pr1.pt[i]][ch2.vehicle[m-1]] )==(DISTANCE[ch2.pt[m-1]][pr2.pt[j]][ch2.vehicle[m-1]]*COST[ch2.pt[m-1]][pr2.pt[j]][ch2.vehicle[m-1]]))
    {
     if(pr1.pt[i]==pr2.pt[j])
        {
         ch2.pt[m]=pr1.pt[i];
         ch2.vehicle[m]=pr1.vehicle[i];
        // ch2.goodsTP_Vehicle[m]=pr1.goodsTP_Vehicle[i];
		 i=i+1;
         j=j+1;
        }
    else
      {
       ch2.pt[m]=pr1.pt[i];
       ch2.vehicle[m]=pr1.vehicle[i];
      // ch2.goodsTP_Vehicle[m]=pr1.goodsTP_Vehicle[i];
       i=i+1;
      }
       m=m+1;
    }
else if((DISTANCE[ch2.pt[m-1]][pr1.pt[i]][ch2.vehicle[m-1]]*COST[ch2.pt[m-1]][pr1.pt[i]][ch2.vehicle[m-1]] )<(DISTANCE[ch2.pt[m-1]][pr2.pt[j]][ch2.vehicle[m-1]]*COST[ch2.pt[m-1]][pr2.pt[j]][ch2.vehicle[m-1]]))
        {
         ch2.pt[m]=pr1.pt[i];
         ch2.vehicle[m]=pr1.vehicle[i];
        // ch2.goodsTP_Vehicle[m]=pr1.goodsTP_Vehicle[i];

         i=i+1;
         m=m+1;
        }
     else
        {
         ch2.pt[m]=pr2.pt[j];
         ch2.vehicle[m]=pr2.vehicle[j];
        // ch2.goodsTP_Vehicle[m]=pr2.goodsTP_Vehicle[j];
	     j=j+1;
         m=m+1;
        }
     b:  continue;
}





// again .. copy 1st child chromosome to the population//
 for(i=0;i<pv;i++)
 	{
     if(p0==i)
	   {
        for(j=0;j<node;j++)
        {

        npopu[i].pt[j]=ch1.pt[j];
        npopu[i].vehicle[j]=ch1.vehicle[j];
     //   npopu[i].goodsTP_Vehicle[j]=ch1.goodsTP_Vehicle[j];
    }
       }

// again copy 2nd child chromosome to the population//

	 else if(p1==i)
        {
		 for(j=0;j<node;j++)
		 {

		 npopu[i].pt[j]=ch2.pt[j];
		 npopu[i].vehicle[j]=ch2.vehicle[j];
	//	 npopu[i].goodsTP_Vehicle[j]=ch2.goodsTP_Vehicle[j];
	}
		}

    }
//.....Childs after crossover.....//
// printf("\nThe two child... \n"); 
//printf("crossing points--> %d\t%d\n",pos1,pos2);
//
//         
//		   for(j=0;j<node;j++)
//		   {
//
//         printf("%d[%d]\t",ch1.pt[j],ch1.vehicle[j]);
//           }  
//      for(j=0;j<node;j++)
//       {
//       printf(" %d[%d]\t",ch2.pt[j], ch2.vehicle[j]);
//       }
//       getch();




//***************************RISK CHECK FOR both child******************************************************************
//printf("\n welcome in cross....... \n"); getch();
 for(i=0;i<pv;i++)
        {
            for(int k=0;k<node;k++)
			{
             popu[i].pt[k]=npopu[i].pt[k];
             popu[i].vehicle[k]=npopu[i].vehicle[k];
			 popu[i].green_pt[k]=npopu[i].green_pt[k];
			 }
			 }
           calfitness(pv);
           

          
           
     //***************************RISK CHECK FOR CHILD 1******************************************************************
     //	printf("\n RISK CHECK FOR CHILD 1..\n");
      check_risk(p0);
      
     	if((popu[p0].Total_Risk>Max_risk))  //child1 replace by parent1
			   	 {
		       for(int k=0;k<node;k++)
			{
             npopu[p0].pt[k]=parent1.pt[k];
             npopu[p0].vehicle[k]=parent1.vehicle[k];
		
			 }
		       		 
         	
                }	
     
      

//***************************RISK CHECK FOR CHILD 2 ******************************************************************
  //	printf("\n For cRISK CHECK FOR CHILD 2..\n");
  check_risk(p1);
      
     	if((popu[p1].Total_Risk>Max_risk))  //child1 replace by parent2
			   {
		      for(int k=0;k<node;k++)
			{
             npopu[p1].pt[k]=parent2.pt[k];
             npopu[p1].vehicle[k]=parent2.vehicle[k];
	
			 }
         	
                }
  	 			
	
}

}
}


//*************************************************************************************************************88
//***************************** cyclic crossover *************************************************************
void crossover_cyclic(int pv)
			{
				 int i,pos[2],count=0;
					float r;
				 for(i=0;i<pv;i++)
				 {
					 r=(rand()%1000)/1000.;
				  //	 printf("r=%f",r);
					  if(r<=pc)
					 {
						pos[count]=i;
						count++;
					 //	printf("count=%d",count);
						if(count==2)
						  {
						 // printf("\npos[0]=%d,pos[1]=%d\n",pos[0],pos[1]);
								cross_cyclic(pos[0],pos[1],pv);
								count=0;
						  }
					 }
			  }
			 //display //
			 // printf("\nafter cross over\n");
			 // for(i=0;i<pv;i++)
			 // {
			  //	for(int j=0;j<node;j++)
			  //	printf("%d\t",npopu[i].pt[j]);
			 //	printf("\n");
			// }

//return (1);
		  }
 void cross_cyclic(int p0,int p1,int pv)
		  {
				int i,j,pos,k,temp;
				int pr1[node],ch1[node],pr2[node],ch2[node];

			//copy 1st chromosome into pr1[]
			for(i=0;i<pv;i++)
			{
				 if(p0==i)
				 {
				  for(j=0;j<node;j++)
				  pr1[j]=npopu[i].pt[j];
				  }

			 }

			 //copy 2nd  chromosome into pr2[]
				for(i=0;i<pv;i++)
			{
				 if(p1==i)
				 {
				  for(j=0;j<node;j++)
				  pr2[j]=npopu[i].pt[j];

				  }

			 }
			/* for(i=0;i<node;i++)
			 {
			  printf("%d ",pr1[i]);
			  }
			  printf("\n");
				 for(i=0;i<node;i++)
				 {
				printf("%d ",pr2[i]);
				}   */

			//  cross general method//
			pos=rand()%node ;

		 //	printf("cross pos=%d\n",pos);
			for(i=0;i<node;i++)
			{
			ch1[i]=10000;
			ch2[i]=10000;
			}
			/* cyclic crossover for child1*/
			for(i=0;i<node;i++)
			{
			  if(pr1[i]==pos)
				 {
					k=i;
			  l1:	temp=pr1[k];
					if(ch1[k]==temp)
					{
					 goto l2;
					}
					else
					{
					  ch1[k]=temp;
					  for(j=0;j<node;j++)
					  {
						if(pr2[j]==temp)
						{
						k=j;
						temp=pr1[k];
						goto l1;
						}
					  }
					}
				 }
			}
			l2: for(j=0;j<node;j++)
			{
			 if(ch1[j]!=pr1[j])
			 {
			 ch1[j]=pr2[j];
			 }
			}
			/* Cyclic crossover for child2*/

			 for(i=0;i<node;i++)
			{
			  if(pr2[i]==pos)
				 {
					k=i;
			  l12:	temp=pr2[k];
					if(ch2[k]==temp)
					{
					 goto l21;
					}
					else
					{
					  ch2[k]=temp;
					  for(j=0;j<node;j++)
					  {
						if(pr1[j]==temp)
						{
						k=j;
						temp=pr2[k];
						goto l12;
						}
					  }
					}
				 }
			}
			l21: for(j=0;j<node;j++)
			{
			 if(ch2[j]!=pr2[j])
			 {
			 ch2[j]=pr1[j];
			 }
			}
	  /*	  printf("\nAfter crossover\n");

			for(i=0;i<node;i++)
			printf("%d\t",ch1[i]);
			printf("\n");
			for(i=0;i<node;i++)
			printf("%d\t",ch2[i]);   */

		  /*	for(i=0;i<=pos;i++)
				 ch1[i]=pr1[i];
			 for(i=(pos+1);i<node;i++)
				 ch1[i]=pr2[i];

				for(i=0;i<=pos;i++)
				 ch2[i]=pr2[i];
			 for(i=(pos+1);i<node;i++)
				 ch2[i]=pr1[i];
									  */
			// again copy 1st child chromosome to the population//
				for(i=0;i<pv;i++)
			{
				 if(p0==i)
				 {
					for(j=0;j<node;j++)
					npopu[i].pt[j]=ch1[j];
				  }
			 }

		  // again copy 2nd child chromosome to the population//
			for(i=0;i<pv;i++)
			{
				 if(p1==i)
				 {
				  for(j=0;j<node;j++)
				  npopu[i].pt[j]=ch2[j];
				  }
			 }

	  }


//*****************************************************************************************************************************
//*************************************************************************************************************************



//************OBL based mutation************************
void mutation(int pv)
    {
     int i,p,j;
     float r,pm_gen_dpndnt;
     pm_gen_dpndnt= ((rand()%1000)/2000.)/pow((k),1/4);
     
    // printf("\n ............  the value of pm_gen_dpndnt =%f",pm_gen_dpndnt); getch();
     
     	 for(i=0;i<noc;i++)
			{
	
				for(j=0;j<node;j++)
				{
				  npopu[i].pt[j]=popu[i].pt[j];
				  npopu[i].vehicle[j]= popu[i].vehicle[j];
			
				 }
				  
			}
     
     
     for(i=0;i<pv;i++)
        {
         r=(rand()%1000)/1000.;
         if(r<=pm_gen_dpndnt)
            {
             p=i;
             mutate(p, pv);
            }
        }

//return all the values in popu*****************
     for(i=0;i<pv;i++)
        {
            for(int k=0;k<node;k++)
			{
             popu[i].pt[k]=npopu[i].pt[k];
             popu[i].vehicle[k]=npopu[i].vehicle[k];
			 popu[i].green_pt[k]=npopu[i].green_pt[k];
			 }
			 }
    
    calfitness(pv);
    
////.....Poulation aftr mutation.....//
//    	printf("\n after mutation \n");
//						for(i=0;i<noc;i++)
//						{
//						  for(j=0;j<node;j++)
//						  {
//							 printf("%d ",popu[i].pt[j]);
//							}
//							printf("\n");
//							for(j=0;j<node;j++)
//						  {
//							printf("%d ",popu[i].vehicle[j]);
//							}
//						  printf("   F[%d]=%f\n",i,popu[i].fitness);
//						} 
					//	getch(); 



}


void mutate(int p,int pv)
	 {
      int i,j,a,b,c;
      int pr1[node],pr1_mutation[node];
for(i=0;i<pv;i++)   //copy that chromosome into pr1[]//
    {
     if(p==i)
        {
         for(j=0;j<node;j++)
         {
		 
         pr1[j]=npopu[i].pt[j];
         //pr1_mutation[j]=pr1[j];
         pr1_mutation[j]=pr1[j];
         	//printf("%d ", pr1[j]);
         //	printf("\n %d ", pr1_mutation[j]);
         }
        }
    }
    
    
//     printf("\n The targeted  chromosome for mutation....\n");          
//		   for(j=0;j<node;j++)
//		   {
//
//         printf("%d\t",pr1[j]);
//           }    
//       getch();
// obl based mutate//
                       for(j=1;j<node;j++)
						  {
						  	if(pr1[j]!=node-1)
						  	{
						  		 pr1[j]=(node-1)-pr1[j];
							  }
						 						
							}


//printf("\n The targeted  chromosome for after mutation....\n");          
//		   for(j=0;j<node;j++)
//		   {
//
//         printf("%d\t",pr1[j]);
//           }    
//       getch();

// again copy this chromosome to the population//
for(i=0;i<pv;i++)
    {
     if(p==i)
        {
         for(j=0;j<node;j++)
         {

         npopu[i].pt[j]=pr1[j];
     }
        }
    }
    
    //***************************RISK CHECK FOR MUTATION*****************************************************************
          for(i=0;i<pv;i++)
        {
            for(int k=0;k<node;k++)
			{
             popu[i].pt[k]=npopu[i].pt[k];
             popu[i].vehicle[k]=npopu[i].vehicle[k];
			// popu[i].green_pt[k]=npopu[i].green_pt[k];
			 }
			 }
           calfitness(pv);
           
           
     //***************************RISK CHECK FOR MUTATION******************************************************************
      // 	printf("\n For RISK CHECK FOR MUTATION*...\n");
       	check_risk(p);
      
     	if((popu[p].Total_Risk>Max_risk))  //child1 replace by parent1
			   	{
			   	 for(j=0;j<node;j++)	 
			{
             npopu[p].pt[j]= pr1_mutation[j];
         	
               }	
               
               
       	     		   
}
		   
}








	 float result()
			  {
				float sum,w;
						  float  before_refuse_traveling_cost, before_refuse_goods_transport_cost;

				int pos,i,j;
					optimum.fitness=000000;  //for maximization
				for(i=0;i<noc;i++)
					{


						 if(popu[i].fitness>optimum.fitness)
						 {
						 	optimum=popu[i];
						 	

						 }
					 }
					// printf("\n value of optimum.fitness..........=%f ",optimum.fitness); getch();
		return optimum.fitness;
  }


//********   *********** RISK calculation *********  *******************//

                  void check_risk(int p1)
                {

              float sum=0.0;
			  float Total_distance=0.0;
			  float Total_time=0.0;
			  float Total_Risk=0.0;

			   Total_SPECIMENS_COLLECTION_WEIGHT=0.0;
                  //TOTAL_SPECIMENS_COLLECTION_TIME=0.0;
                  TOTAL_SPECIMENS_LOADING_COST=0.0;

          int p0=p1;

			//   printf("\n value of REM_GOODS_WEIGHT....=%f ",TOTAL_NON_FREEZING_WEIGHT); getch();
			  for(j=0;j<node-1;j++)
              {
              	       Total_distance+=DISTANCE[popu[p0].pt[j]][popu[p0].pt[j+1]][popu[p0].vehicle[j]];
              	       sum+=(COST[popu[p0].pt[j]][popu[p0].pt[j+1]][popu[p0].vehicle[j]])*DISTANCE[popu[p0].pt[j]][popu[p0].pt[j+1]][popu[p0].vehicle[j]]; // cost per unit distance * distance
                        Total_time+=TIME[popu[p0].pt[j]][popu[p0].pt[j+1]][popu[p0].vehicle[j]];
                       
           
                       Total_SPECIMENS_COLLECTION_WEIGHT=Total_SPECIMENS_COLLECTION_WEIGHT+SPECIMENS_COLLECTION_WEIGHT[j];
                       
                     Transportation_risk_factor=  SPECIMENS_COLLECTION_WEIGHT[j]*(Total_time/60)*DISTANCE[popu[p0].pt[j]][popu[p0].pt[j+1]][popu[p0].vehicle[j]]/100;
                         
						 
			  if(DISTANCE[popu[p0].pt[j]][popu[p0].pt[j+1]][popu[p0].vehicle[j]]>0 && DISTANCE[popu[p0].pt[j]][popu[p0].pt[j+1]][popu[p0].vehicle[j]]<=20)
                 {
                 	if(Total_SPECIMENS_COLLECTION_WEIGHT>0 && Total_SPECIMENS_COLLECTION_WEIGHT<=25)
                 	{
                 	Total_Risk+=0.08*Transportation_risk_factor;	
					 }
					 
					 else if(Total_SPECIMENS_COLLECTION_WEIGHT>26 && Total_SPECIMENS_COLLECTION_WEIGHT<=50)
                 	{
                 	Total_Risk+=0.16*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>50 && Total_SPECIMENS_COLLECTION_WEIGHT<=75)
                 	{
                 	Total_Risk+=0.25*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>75 && Total_SPECIMENS_COLLECTION_WEIGHT<=100)
                 	{
                 	Total_Risk+=0.33*Transportation_risk_factor;	
					 }
					 
					 else
					 {
					 	Total_Risk+=0.40*Transportation_risk_factor;
					 }
					 
				 } 
				 
				 
       
        if(DISTANCE[popu[p0].pt[j]][popu[p0].pt[j+1]][popu[p0].vehicle[j]]>20 && DISTANCE[popu[p0].pt[j]][popu[p0].pt[j+1]][popu[p0].vehicle[j]]<=40)
                 {
                 	if(Total_SPECIMENS_COLLECTION_WEIGHT>0 && Total_SPECIMENS_COLLECTION_WEIGHT<=25)
                 	{
                 	Total_Risk+=0.16*Transportation_risk_factor;	
					 }
					 
					 else if(Total_SPECIMENS_COLLECTION_WEIGHT>26 && Total_SPECIMENS_COLLECTION_WEIGHT<=50)
                 	{
                 	Total_Risk+=0.33*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>50 && Total_SPECIMENS_COLLECTION_WEIGHT<=75)
                 	{
                 	Total_Risk+=0.50*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>75 && Total_SPECIMENS_COLLECTION_WEIGHT<=100)
                 	{
                 	Total_Risk+=0.66*Transportation_risk_factor;	
					 }
					 
					 else
					 {
					 	Total_Risk+=0.60*Transportation_risk_factor;
					 }
					 
				 } 
				 
				 
				  if(DISTANCE[popu[p0].pt[j]][popu[p0].pt[j+1]][popu[p0].vehicle[j]]>40 && DISTANCE[popu[p0].pt[j]][popu[p0].pt[j+1]][popu[p0].vehicle[j]]<=60)
                 {
                 	if(Total_SPECIMENS_COLLECTION_WEIGHT>0 && Total_SPECIMENS_COLLECTION_WEIGHT<=25)
                 	{
                 	Total_Risk+=0.25*Transportation_risk_factor;	
					 }
					 
					 else if(Total_SPECIMENS_COLLECTION_WEIGHT>26 && Total_SPECIMENS_COLLECTION_WEIGHT<=50)
                 	{
                 	Total_Risk+=0.50*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>50 && Total_SPECIMENS_COLLECTION_WEIGHT<=75)
                 	{
                 	Total_Risk+=0.75*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>75 && Total_SPECIMENS_COLLECTION_WEIGHT<=100)
                 	{
                 	Total_Risk+=0.95*Transportation_risk_factor;	
					 }
					 
					 else
					 {
					 	Total_Risk+=0.40*Transportation_risk_factor;
					 }
					 
				 } 
       
     
       

              }
             
              Total_distance+=DISTANCE[popu[p0].pt[node-1]][popu[p0].pt[0]][popu[p0].vehicle[node-1]];
             
               sum+=(COST[popu[p0].pt[node-1]][popu[p0].pt[0]][popu[p0].vehicle[node-1]])*(DISTANCE[popu[p0].pt[node-1]][popu[p0].pt[0]][popu[p0].vehicle[j]]);

                
					  if(DISTANCE[popu[p0].pt[node-1]][popu[p0].pt[0]][popu[p0].vehicle[node-1]]>0 && DISTANCE[popu[p0].pt[node-1]][popu[p0].pt[0]][popu[p0].vehicle[node-1]]<=20)
                 {
                 	if(Total_SPECIMENS_COLLECTION_WEIGHT>0 && Total_SPECIMENS_COLLECTION_WEIGHT<=25)
                 	{
                 	Total_Risk+=0.08*Transportation_risk_factor;	
					 }
					 
					 else if(Total_SPECIMENS_COLLECTION_WEIGHT>26 && Total_SPECIMENS_COLLECTION_WEIGHT<=50)
                 	{
                 	Total_Risk+=0.16*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>50 && Total_SPECIMENS_COLLECTION_WEIGHT<=75)
                 	{
                 	Total_Risk+=0.25*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>75 && Total_SPECIMENS_COLLECTION_WEIGHT<=100)
                 	{
                 	Total_Risk+=0.33*Transportation_risk_factor;	
					 }
					 
					 else
					 {
					 	Total_Risk+=0.40*Transportation_risk_factor;
					 }
					 
				 } 
				 
				 
       
        if(DISTANCE[popu[p0].pt[node-1]][popu[p0].pt[0]][popu[p0].vehicle[node-1]]>20 && DISTANCE[popu[p0].pt[node-1]][popu[p0].pt[0]][popu[p0].vehicle[node-1]]<=40)
                 {
                 	if(Total_SPECIMENS_COLLECTION_WEIGHT>0 && Total_SPECIMENS_COLLECTION_WEIGHT<=25)
                 	{
                 	Total_Risk+=0.16*Transportation_risk_factor;	
					 }
					 
					 else if(Total_SPECIMENS_COLLECTION_WEIGHT>26 && Total_SPECIMENS_COLLECTION_WEIGHT<=50)
                 	{
                 	Total_Risk+=0.33*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>50 && Total_SPECIMENS_COLLECTION_WEIGHT<=75)
                 	{
                 	Total_Risk+=0.50*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>75 && Total_SPECIMENS_COLLECTION_WEIGHT<=100)
                 	{
                 	Total_Risk+=0.66*Transportation_risk_factor;	
					 }
					 
					 else
					 {
					 	Total_Risk+=0.60*Transportation_risk_factor;
					 }
					 
				 } 
				 
				 
				  if(DISTANCE[popu[p0].pt[node-1]][popu[p0].pt[0]][popu[p0].vehicle[node-1]]>40 && DISTANCE[popu[p0].pt[node-1]][popu[p0].pt[0]][popu[p0].vehicle[node-1]]<=60)
                 {
                 	if(Total_SPECIMENS_COLLECTION_WEIGHT>0 && Total_SPECIMENS_COLLECTION_WEIGHT<=25)
                 	{
                 	Total_Risk+=0.25*Transportation_risk_factor;	
					 }
					 
					 else if(Total_SPECIMENS_COLLECTION_WEIGHT>26 && Total_SPECIMENS_COLLECTION_WEIGHT<=50)
                 	{
                 	Total_Risk+=0.50*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>50 && Total_SPECIMENS_COLLECTION_WEIGHT<=75)
                 	{
                 	Total_Risk+=0.75*Transportation_risk_factor;	
					 }
					 
					else if(Total_SPECIMENS_COLLECTION_WEIGHT>75 && Total_SPECIMENS_COLLECTION_WEIGHT<=100)
                 	{
                 	Total_Risk+=0.95*Transportation_risk_factor;	
					 }
					 
					 else
					 {
					 	Total_Risk+=0.40*Transportation_risk_factor;
					 }
					 
				 } 
				 
				 //	printf("\n ...  Total_Risk.....=%f",Total_Risk); getch();
				 
				 	popu[p0].Total_Risk=Total_Risk;
        
  
       }
       


