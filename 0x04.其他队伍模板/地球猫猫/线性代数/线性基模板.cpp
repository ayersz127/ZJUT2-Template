//

const int maxbit = 62;		//maxbit����̫��

struct L_B{
	ll lba[maxbit];
	L_B(){
        memset(lba, 0, sizeof(lba));
    }
    
	void Insert(ll val){		//����
        for(int i = maxbit - 1; i >= 0; -- i) // �Ӹ�λ���λɨ  
            if(val & (1ll << i)){ // 
                if(!lba[i]){
                    lba[i] = val;
                    break;
                }
                val ^= lba[i];
            }
    }
};
//��ԭ���ϵ�ÿ����valתΪ2���ƣ��Ӹ�λ���λɨ�����ڵ�ǰλΪ1�ģ���lba[i]�����ھ���lba[i]=x��������val=val`xor`lba[i]
//ʹ�ã� ֱ��insert  
// --------------���Ի�ģ��
