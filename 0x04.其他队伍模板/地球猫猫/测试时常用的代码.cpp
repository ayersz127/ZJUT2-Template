//�ļ����������ʱ�亯���������

#ifdef ONLINE_JUDGE
#else
    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
#endif
//���¶���stdin/stdout��in.txt/out.txt��"r"��"w"Ϊֻ����ֻд


#include<ctime>
    clock_t ST,ED;
    ST=clock();
    //��������Եĳ���
    ED=clock();
    cout<<ED-ST<<"ms"<<endl;


#include<ctime>
#include<cstdlib>
    srand(time(0));//��ʼ��
    rand();//����[0,RAND_MAX]֮����������(int)��RAND_MAX��cstdlib�еĺ궨�壬һ��Ϊ0x7fff(32767)