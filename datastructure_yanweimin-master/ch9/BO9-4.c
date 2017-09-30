 /* bo9-4.c ��̬���ұ�(B��)�Ļ������� */
 Status InitDSTable(BTree *DT)
 { /* �������: ����һ���յĶ�̬���ұ�DT */
   *DT=NULL;
   return OK;
 }

 void DestroyDSTable(BTree *DT)
 { /* ��ʼ����: ��̬���ұ�DT���ڡ��������: ���ٶ�̬���ұ�DT */
   int i;
   if(*DT) /* �ǿ��� */
   {
     for(i=0;i<=(*DT)->keynum;i++)
       DestroyDSTable(&(*DT)->node[i].ptr); /* �������ٵ�i������ */
     free(*DT); /* �ͷŸ���� */
     *DT=NULL; /* ��ָ�븳0 */
   }
 }

 int Search(BTree p, KeyType K)
 { /* ��p->node[1..keynum].key�в���i,ʹ��p->node[i].key��K��p->node[i+1].key */
   int i=0,j;
   for(j=1;j<=p->keynum;j++)
     if(p->node[j].key<=K)
       i=j;
   return i;
 }

 Result SearchBTree(BTree T, KeyType K)
 { /* ��m��B��T�ϲ��ҹؼ���K�����ؽ��(pt,i,tag)�������ҳɹ���������ֵ */
   /* tag=1��ָ��pt��ָ����е�i���ؼ��ֵ���K����������ֵtag=0������K�� */
   /* �ؼ���Ӧ������ָ��Pt��ָ����е�i�͵�i+1���ؼ���֮�䡣�㷨9.13 */
   BTree p=T,q=NULL; /* ��ʼ����pָ������㣬qָ��p��˫�� */
   Status found=FALSE;
   int i=0;
   Result r;
   while(p&&!found)
   {
     i=Search(p,K); /* p->node[i].key��K<p->node[i+1].key */
     if(i>0&&p->node[i].key==K) /* �ҵ�����ؼ��� */
       found=TRUE;
     else
     {
       q=p;
       p=p->node[i].ptr;
     }
   }
   r.i=i;
   if(found) /* ���ҳɹ� */
   {
     r.pt=p;
     r.tag=1;
   }
   else /*  ���Ҳ��ɹ�������K�Ĳ���λ����Ϣ */
   {
     r.pt=q;
     r.tag=0;
   }
   return r;
 }

 void Insert(BTree *q,int i,Record *r,BTree ap)
 { /* ��r->key��r��ap�ֱ���뵽q->key[i+1]��q->recptr[i+1]��q->ptr[i+1]�� */
   int j;
   for(j=(*q)->keynum;j>i;j--) /* �ճ�q->node[i+1] */
     (*q)->node[j+1]=(*q)->node[j];
   (*q)->node[i+1].key=r->key;
   (*q)->node[i+1].ptr=ap;
   (*q)->node[i+1].recptr=r;
   (*q)->keynum++;
 }

 void split(BTree *q,BTree *ap)
 { /* �����q���ѳ�������㣬ǰһ�뱣������һ�������������ap */
   int i,s=(m+1)/2;
   *ap=(BTree)malloc(sizeof(BTNode)); /* �����½��ap */
   (*ap)->node[0].ptr=(*q)->node[s].ptr; /* ��һ������ap */
   for(i=s+1;i<=m;i++)
   {
     (*ap)->node[i-s]=(*q)->node[i];
     if((*ap)->node[i-s].ptr)
       (*ap)->node[i-s].ptr->parent=*ap;
   }
   (*ap)->keynum=m-s;
   (*ap)->parent=(*q)->parent;
   (*q)->keynum=s-1; /* q��ǰһ�뱣�����޸�keynum */
 }

 void NewRoot(BTree *T,Record *r,BTree ap)
 { /* ���ɺ���Ϣ(T,r,ap)���µĸ����*T��ԭT��apΪ����ָ�� */
   BTree p;
   p=(BTree)malloc(sizeof(BTNode));
   p->node[0].ptr=*T;
   *T=p;
   if((*T)->node[0].ptr)
     (*T)->node[0].ptr->parent=*T;
   (*T)->parent=NULL;
   (*T)->keynum=1;
   (*T)->node[1].key=r->key;
   (*T)->node[1].recptr=r;
   (*T)->node[1].ptr=ap;
   if((*T)->node[1].ptr)
     (*T)->node[1].ptr->parent=*T;
 }

 void InsertBTree(BTree *T,Record *r,BTree q,int i)
 { /* ��m��B��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K��ָ��r�������� */
   /* ������,����˫�������б�Ҫ�Ľ����ѵ���,ʹT����m��B�����㷨9.14�� */
   BTree ap=NULL;
   Status finished=FALSE;
   int s;
   Record *rx;
   rx=r;
   while(q&&!finished)
   {
     Insert(&q,i,rx,ap); /* ��r->key��r��ap�ֱ���뵽q->key[i+1]��q->recptr[i+1]��q->ptr[i+1]�� */
     if(q->keynum<m)
       finished=TRUE; /* ������� */
     else
     { /* ���ѽ��*q */
       s=(m+1)/2;
       rx=q->node[s].recptr;
       split(&q,&ap); /* ��q->key[s+1..m],q->ptr[s..m]��q->recptr[s+1..m]�����½��*ap */
       q=q->parent;
       if(q)
         i=Search(q,rx->key); /* ��˫�׽��*q�в���rx->key�Ĳ���λ�� */
     }
   }
   if(!finished) /* T�ǿ���(����q��ֵΪNULL)�������ѷ���Ϊ���*q��*ap */
     NewRoot(T,rx,ap); /* ���ɺ���Ϣ(T,rx,ap)���µĸ����*T��ԭT��apΪ����ָ�� */
 }

 void TraverseDSTable(BTree DT,void(*Visit)(BTNode,int))
 { /* ��ʼ����: ��̬���ұ�DT���ڣ�Visit�ǶԽ�������Ӧ�ú��� */
   /* �������: ���ؼ��ֵ�˳���DT��ÿ�������ú���Visit()һ��������һ�� */
   int i;
   if(DT) /* �ǿ��� */
   {
     if(DT->node[0].ptr) /* �е�0������ */
       TraverseDSTable(DT->node[0].ptr,Visit);
     for(i=1;i<=DT->keynum;i++)
     {
       Visit(*DT,i);
       if(DT->node[i].ptr) /* �е�i������ */
	 TraverseDSTable(DT->node[i].ptr,Visit);
     }
   }
 }