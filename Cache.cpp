#include<bits/stdc++.h>

using namespace std;

int lru[500][20];

int bringtotop(int set, int assoc, int x)
{
    int i,pos;
    for(i=0;i<assoc;i++)
        if(lru[set][i] == x)
            pos = i;
    for(i=pos;i<assoc-1;i++)
        lru[set][i] = lru[set][i+1];
    lru[set][assoc-1] = x;


}

bool checking(int x)
{
	if(x==0)
	{
		return true;
	}
	return false;
}
void plot(int total, int hit, int miss);

long int changebase(char hex[], int base);


int convert(char);

int main()
{
	 int cache_size, asso, block_size,i,j, no_blocks, base,r,alg, x,pos;
	 long int address;
	 float hitrate , missrate;
	 char hex[20] ;
	 int no_set;
	 int check=0, hit=0, miss=0;
	 string filename ;
	  cout<<"\n\t\t\t\t     ************Cache Simulation**********\t\t\n\n";
	 cout<<"Enter the cache_size : ";
	 cin>>cache_size;
	 if(checking(cache_size))
	 {
	 	cout<<"Invalid cache size";
	 	return 0;
	 }
	 
	 
	 cout<<"Enter the associativity : ";
	 cin>>asso;
	 
	 if(checking(asso))
	 {
	 	cout<<"Invalid Associativity";
	 	return 0;
	 }
	 
	 
	 cout<<"Enter the block size : ";
	 cin>>block_size;
	 
	 
	 if(checking(block_size))
	 {
	 	cout<<"Invalid Invalid Block_size";
	 	return 0;
	 }
	 
	 if(block_size > cache_size)
	 {
	 	cout<<"\n\nInvalid !! Cache size cannot be less than blocksize";
	 	return 0;
	 }
	 
	 
	 filename = "trace_file.csr" ;
	 base = 15;
	 
	 cout<<"\nSelect Any Technique\n";
	 cout<<"1. FIFO \n2. LRU \n3. Random\nEnter Your Choice... : ";
	 cin>>alg;

	 
	 no_blocks = cache_size / block_size; // total block
	 no_set = cache_size / (asso * block_size);

	 int cache[no_set][asso];

	 for(i=0;i<no_set;i++)
	{		
	  	for(j=0;j<asso;j++)
	  	{
	   		cache[i][j] = -10; // Eliminating all garbage values in in the cache...
  		
		  }
		}		
	
	 int fifo[no_set];

	 for(i=0;i<no_set;i++)
	 {
	 fifo[i] = 0;
	 }
	 
	for(i=0;i<no_set;i++)
	{
		for(j=0;j<asso;j++)
		{
			lru[i][j] = j;
		}
		}	
	 ifstream infile;
	 infile.open(filename.c_str(),ios::in);
	 if(!infile)
	 {
	     cout<<"Error! File not found...";
	     exit(0);

	 }

	 int set, tag, found;
	 while(!infile.eof()) //Reading each address from trace file
	 {

        if(base!=10)
        {
            infile>>hex;
            address = changebase(hex, base);
        }
        else {
            infile>>address;
		}

		  set = (address / block_size) % no_set;
		  tag = address / (block_size * no_set);


		  check++;
		  found = 0;
		  for(i=0;i<asso;i++)
			   if(cache[set][i] == tag)
			    {
			        found = 1;
			        pos = i;
			    }


		  if(found)
		  {
		      hit++;
		      if(alg == 2)
		      {
		      		bringtotop(set,asso,pos);
		      }
		  }

		  else
		  {
	            if(alg==1)
	            {
	           		i = fifo[set];

				   cache[set][i] = tag;
				   fifo[set]++;

				   if(fifo[set] == asso)
				    	fifo[set] = 0;

	            }
	            else if(alg==2)
	            {
	                i = lru[set][0];
	                cache[set][i] = tag;
	                bringtotop(set,asso,i);

	            }
	            else
	            {
	                r = rand() % asso;
	                cache[set][r] = tag;

	            }

		  }
		  

	 }
	 
	 infile.close();
	 cout<<endl << endl <<"No: of checks ---> "<<check<<endl << endl;
	 cout<<endl << endl<<" No: of hits ---> "<<hit<<endl << endl;
	 cout<<endl << endl<<" No of misses ---> "<<check-hit<<endl << endl;
	 hitrate = float(hit)/float(check);
	 missrate = float(check-hit)/float(check);
	 cout<<endl << endl<<" Miss Rate ---> "<<missrate<<endl << endl;
	 cout<<endl << endl<<" Hit Rate ---> "<<hitrate<<endl << endl;

	//getch();

		plot(check,hit, check-hit);

	 return 0;

}







int convert(char c)
{
    if(c == '1')
        return 1;

    else if(c == '2')
        return 2;

    else if(c == '3')
        return 3;

    else if(c == '4')
        return 4;

    else if(c =='5')
        return 5;

    else if(c == '6')
        return 6;

    else if(c == '7')
        return 7;

    else if(c == '8')
        return 8;

    else if(c == '9')
        return 9;

    else if(c == '0')
        return 0;

    else if( (c == 'a') || (c == 'A') )
        return 10;

    else if( (c == 'b') || (c == 'B') )
        return 11;

    else if( (c == 'c') || (c == 'C') )
        return 12;

    else if( (c == 'd') || (c == 'D') )
        return 13;

    else if( (c == 'e') || (c == 'E') )
        return 14;

    else if( (c == 'f') || (c == 'F') )
        return 15;

    else
        return 0;

}

//Function to change the base of a number system to decimal
long int changebase(char hex[], int base)
{
    int pow = 1,len,i,j;
    char temp;
    long int dec;

    for(len=0;hex[len]!='\0';len++);

    for(i=0,j=(len-1);i<j;i++,j--)
    {
        temp = hex[i];
        hex[i]=hex[j];
        hex[j]=temp;
    }


    pow = 1;
    dec = 0;
    for(i=0;i<len;i++)
    {
        if(convert(hex[i]== -1))
        {
            dec =0;
            break;
        }
        dec = dec + (pow * convert(hex[i]));
        pow*=base;

    }
    return dec;

}


//Function to plot a graph...
void plot(int total, int hit, int miss)
{

    cout<<"\n\n     ************Graph**********\n\n";

    int hit_limit,miss_limit, i;
    hit_limit = (float (hit)/total)*30;
    miss_limit = (float(miss)/total)*30;



    cout<<"\n\t^";
    cout<<"\n\t|\n";
    for(i=30;i>=0;i--)
    {
        cout<<"\t";
        cout<<"|";
        cout<<"\t\t";

        //Total hit bar
        cout<<"|";
        if(i==30)
            cout<<"----";
        else
            cout<<"    ";
        cout<<"|";

        cout<<"\t\t";
        //Hit Bar...
        if(i<=hit_limit)
            cout<<"|";
        else
            cout<<" ";

        if(i==hit_limit)
            cout<<"----";
        else
            cout<<"    ";

        if(i<=hit_limit)
            cout<<"|";
        else
            cout<<" ";



         cout<<"\t\t";
        //Miss Bar...
        if(i<=miss_limit)
            cout<<"|";
        else
            cout<<" ";

        if(i==miss_limit)
            cout<<"----";
        else
            cout<<"    ";

        if(i<=miss_limit)
            cout<<"|";
        else
            cout<<" ";

        cout<<"\n";

    }
    cout<<"\t---------------------------------------------------------------------->";
    cout<<"\n\t\t\tTotal\t\t Hits\t\tMiss\n";



}
