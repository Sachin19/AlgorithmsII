#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct node_
{
	int index;
	struct node_* next;
}node;

node *G[200];

struct allVer
{
	int a,b;
	struct allVer* next;
};

int P[10000];

int S[1000],T[1000];


void initialise(int a[], int n){
	int i;
	for (i = 0; i < n; ++i)
	{
		a[i]=0;
	}
}
void copy(int from[], int to[],int n){
	int i=0;
	while(from[i]!=-1){
		to[i]=from[i];
		i++;
	}
	to[i]=-1;
}
void findRandomPermutation(int X[], int n){
	int i,j,t;
	for (i = 0; i < n; ++i)
	{
		X[i]=i;
	}
	srand((int)time(NULL));
	for (i = 0; i < n-1; ++i)
	{
		j = rand()%(n-i);
		t = X[i];
		X[i] = X[i+j];
		X[i+j] = t; 
	}

}

void createAllEdgeList(struct allVer **begin, int n)
{
	struct allVer *temp, *iter;
	*begin=NULL;
	iter=*begin;
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			temp=(struct allVer*)malloc(sizeof(struct allVer));
			temp->a=i;
			temp->b=j;
			temp->next=NULL;
			if(*begin==NULL)
			{
				*begin=temp;
				iter=temp;
			}
			else
			{
				iter->next=temp;
				iter=iter->next;
			}
		}
	}


}

void removeFromAllEdgeList(struct allVer **begin, int i, int j)
{
	struct allVer *temp, *prev, *nex;
	temp=*begin;
	prev=NULL;
	nex=(*begin)->next;
	while(temp!=NULL)
	{
		if((temp->a==i&&temp->b==j)||(temp->a==j&&temp->b==i))
		{
			break;
		}
		prev=temp;
		temp=temp->next;
		if(nex!=NULL)
			nex=nex->next;
	}
	if(prev==NULL)
	{
		prev=nex;
		(*begin)=nex;
		//printf("\n%d %d\n",nex->a,nex->b);
	}
	else if(nex==NULL)
	{
		prev->next=NULL;
	}
	else
	{
		prev->next=nex;
	}
	free(temp);
}

struct allVer* getFromAllEdgeList(struct allVer** begin, int no)
{
	struct allVer *temp,*prev,*nex;
	temp=*begin;
	prev=NULL;
	nex=(*begin)->next;
	int i;
	for(i=0;i<no;i++)
	{
		prev=temp;
		temp=temp->next;
		if(nex!=NULL)
			nex=nex->next;
	}
	if(prev==NULL)
	{
		prev=nex;
		*begin=nex;
	}
	else if(nex==NULL)
	{
		prev->next=NULL;
	}
	else
	{
		prev->next=nex;
	}
	return temp;
}

void addNode(int i, int j)
{
	node* temp;
	node* newNode;

	temp=G[i]->next;
	if(temp==NULL)
	{
		//printf("A");
		newNode=(node*)malloc(sizeof(node));
		newNode->index=j;
		newNode->next=NULL;
		G[i]->next=newNode;
	}
	else
	{
		//printf("B");
		while(temp->next!=NULL)
			temp=temp->next;
		newNode=(node*)malloc(sizeof(node));
		newNode->index=j;
		newNode->next=NULL;
		temp->next=newNode;
		//printf("B");
	}

	temp=G[j]->next;
	if(temp==NULL)
	{
		//printf("A");
		newNode=(node*)malloc(sizeof(node));
		newNode->index=i;
		newNode->next=NULL;
		G[j]->next=newNode;
	}
	else
	{
		//printf("B");
		while(temp->next!=NULL)
			temp=temp->next;
		newNode=(node*)malloc(sizeof(node));
		newNode->index=i;
		newNode->next=NULL;
		temp->next=newNode;
		//printf("B");
	}
}

void createGraph(int V, int E)
{
	int i,j;
	int noV=0;

	//Create an edge list
	struct allVer *beginAllEdge, *temp;

	
	createAllEdgeList(&beginAllEdge, V);
	
	
	for(i=0;i<V;i++)
	{
		G[i] = (node*)malloc(sizeof(node));
		G[i]->index = i;
		G[i]->next = NULL;
	}
	findRandomPermutation(P,V);

	//printf("ABC\n");

	for(i=1;i<V;i++)
	{
		j=rand()%i;
		//printf("%d %d\n",i,j);
		addNode(P[i],P[j]);
		noV++;
		//printf("ABC\n");
		removeFromAllEdgeList(&beginAllEdge, i, j);			//Remove edge(i,j) from the list.
	}

	//printf("ABC\n");

	int s;
	s=((V-1)*(V-2))/2;

	while(noV<E)
	{
		j=rand()%s;
		//printf("\n%d: ",j);

		/*struct allVer *temp1;
		temp1=beginAllEdge;
		while(temp1!=NULL)
		{
			printf("(%d,%d) ",temp1->a,temp1->b);
			temp1=temp1->next;
		}*/
		//printf("\n");

		temp=getFromAllEdgeList(&beginAllEdge, j); 
		addNode(P[temp->a],P[temp->b]);							//Add sth edge to graph.
		//free(temp);//Delete from the list.

		

		s--;
		noV++;
	}
}


int edgesWith(node *G[], int n, int A[], int x){
	int e=0;
	node* nd = G[x]->next;
	while(nd!=NULL){
		if(A[nd->index]==1){
			e++;
		}
		nd = nd->next;
	}
	return e;
}

int derandMaxCut(node* G[], int S[], int T[], int n){
	int i,j,l,r,s,t,size;
	int X[1000],S1[1000],T1[1000];

	initialise(S1,n);
	initialise(T1,n);
	s=0;
	t=0;
	size=0;
	findRandomPermutation(X,n);
	/*for (i = 0; i < n; ++i)
	{
		printf("%d ", X[i]);
	}*/
	//printf("\n");
	S[s++]=X[0];
	S1[X[0]]=1;
	for (j = 1; j < n; ++j)
	{;
		l = edgesWith(G,n,S1,X[j]);
		r = edgesWith(G,n,T1,X[j]);
		if(l<r){
			S[s++]=X[j];
			S1[X[j]]=1;
			size+=r;
		}
		else{
			T[t++]=X[j];
			T1[X[j]]=1;
			size+=l;
		}
	}
	S[s]=-1;
	T[t]=-1;
	return size;
}

void createSVG(node *G[], int S[], int T[], int n){
	FILE *fp;
	fp = fopen("maxcut.svg","w");
	fprintf(fp,"<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	int S1[1000],T1[1000],x[1000],y[1000];
	int i=0,cx,cy;
	node *temp;
	initialise(S1,n);
	initialise(T1,n);
	while(S[i]!=-1){
		S1[S[i++]]=1;
	}
	i=0;
	while(T[i]!=-1){
		T1[T[i++]]=1;
	}
	srand((unsigned)time(NULL));

	for (i = 0; i < n; ++i)
	{
		temp = G[i];
		if(S1[i]==1){
				cx = rand()%400;
				cy = rand()%600;
				x[i]=cx;
				y[i]=cy;
				fprintf(fp,"\t<circle cx=\"%d\" cy=\"%d\" r=\"4\" stroke=\"red\" stroke-width=\"2\" fill=\"red\" />\n",cx,cy);
				fprintf(fp,"\t<text x=\"%d\" y=\"%d\" fill=\"black\">%d</text>\n",cx,cy-10,i+1);
		}
		else if(T1[i]==1){
				cx = (rand()%400)+500;
				cy = rand()%600;
				x[i]=cx;
				y[i]=cy;
				fprintf(fp,"\t<circle cx=\"%d\" cy=\"%d\" r=\"4\" stroke=\"blue\" stroke-width=\"2\" fill=\"blue\" />\n",cx,cy);
				fprintf(fp,"\t<text x=\"%d\" y=\"%d\" fill=\"black\">%d</text>\n",cx,cy-10,i+1);
		}
	}
	for (i = 0; i < n; ++i)
	{
		temp = G[i];
		while(temp!=NULL){
			if(i<temp->index){
			if(S1[i]==1){
				if(T1[temp->index]==1){
					fprintf(fp,"\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:red;stroke-width:1\"/>\n",x[i],y[i],x[temp->index],y[temp->index]);
				}
				else{
					fprintf(fp,"\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:gray;stroke-width:1\"/>\n",x[i],y[i],x[temp->index],y[temp->index]);	
				}
			}
			else if(T1[i]==1){

				if(S1[temp->index]==1){
					fprintf(fp,"\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:red;stroke-width:1\"/>\n",x[i],y[i],x[temp->index],y[temp->index]);

				}
				else{
					//print gray line
					fprintf(fp,"\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:gray;stroke-width:1\"/>\n",x[i],y[i],x[temp->index],y[temp->index]);
					
				}
			}
			}
			temp=temp->next;
		}
	}
	fprintf(fp,"</svg>");
	fclose(fp);
}

int main(){
	int m,n,i,j,k,S[1000],T[1000],Sprev[1000],Tprev[1000],size,maxedge;
	float alpha;
	printf("Enter the number of nodes n: ");
	scanf("%d",&n);
	maxedge = (n*(n-1))/2;
	printf("Enter the number of edges m (maximum %d): ",maxedge);
	scanf("%d",&m);
	if(m>maxedge){
		printf("These many edges not possible. Exiting...\n ");
	}
	printf("Enter the value of alpha(0.1, 1, 10): ");
	scanf("%f",&alpha);

	createGraph(n,m);
	printf("\nA file named graph.txt is generated in the directory which contains the details of the graph.\n");
	i=0;
	j = (int)ceil(alpha*n);
	size=derandMaxCut(G,S,T,n);
	i++;
	copy(S,Sprev,n);
	copy(T,Tprev,n);
	while(i<j){
		k = derandMaxCut(G,S,T,n);
		if(k>size){
			size = k;
			copy(S,Sprev,n);
			copy(T,Tprev,n);
		}
		i++;
	}
	printf("Maxcut.svg generated..\nThe size of the maxcut is: %d\n",size);
	node* temp;
	FILE* fp = fopen("graph.txt","w");
	for (i = 0; i < n; ++i)
	{
		temp = G[i]->next;
		fprintf(fp,"%d: ",i);
		while(temp!=NULL){
			fprintf(fp,"%d ",temp->index);
			temp=temp->next;
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	i=0;
	printf("The two sets S and T are:\nS:");
	while(S[i]!=-1){
		printf("%d ",S[i]);
		i++;
	}
	printf("\n");
	i=0;
	printf("T:");
	while(T[i]!=-1){
		printf("%d ",T[i]);
		i++;
	}
	printf("\n");
	createSVG(G,T,S,n);
	return 0;
}